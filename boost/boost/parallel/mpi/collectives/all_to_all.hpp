// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.8. All-to-all
#ifndef BOOST_PARALLEL_MPI_ALL_TO_ALL_HPP
#define BOOST_PARALLEL_MPI_ALL_TO_ALL_HPP

#include <boost/parallel/mpi/exception.hpp>
#include <boost/parallel/mpi/datatype.hpp>
#include <vector>
#include <boost/parallel/mpi/packed_oarchive.hpp>
#include <boost/parallel/mpi/packed_iarchive.hpp>
#include <boost/parallel/mpi/communicator.hpp>
#include <boost/parallel/mpi/environment.hpp>
#include <boost/assert.hpp>
#include <boost/parallel/mpi/collectives_fwd.hpp>
#include <boost/parallel/mpi/allocator.hpp>

namespace boost { namespace parallel { namespace mpi {


template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values,
           std::vector<T>& out_values);
           
namespace detail {
  // We're performaing an all-to-all with a type that has an
  // associated MPI datatype, so we'll use MPI_Alltoall to do all of
  // the work.
  template<typename T>
  void
  all_to_all_impl(const communicator& comm, const std::vector<T>& in_values,
                  std::vector<T>& out_values, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>();
    out_values.resize(comm.size());
    BOOST_MPI_CHECK_RESULT(MPI_Alltoall,
                           (const_cast<T*>(&in_values.front()), 1, type,
                            &out_values.front(), 1, type, comm));
  }

  // We're performing an all-to-all with a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Alltoall, so
  // we'll just have to send individual messages to the other
  // processes.
  template<typename T>
  void
  all_to_all_impl(const communicator& comm, const std::vector<T>& in_values,
                  std::vector<T>& out_values, mpl::false_)
  {
    int size = comm.size();
    int rank = comm.rank();

    out_values.resize(comm.size());

    // The amount of data to be sent to each process
    std::vector<int> send_sizes(size);

    // The displacements for each outgoing value.
    std::vector<int> send_disps(size);

    // The buffer that will store all of the outgoing values
    std::vector<char, allocator<char> > outgoing;

    // Pack the buffer with all of the outgoing values.
    for (int dest = 0; dest < size; ++dest) {
      // Keep track of the displacements
      send_disps[dest] = outgoing.size();

      // Our own value will never be transmitted, so don't pack it.
      if (dest != rank) {
        packed_oarchive oa(comm, outgoing);
        oa << in_values[dest];
      }

      // Keep track of the sizes
      send_sizes[dest] = outgoing.size() - send_disps[dest];
    }

    // Determine how much data each process will receive.
    std::vector<int> recv_sizes(size);
    all_to_all(comm, send_sizes, recv_sizes);

    // Prepare a buffer to receive the incoming data.
    std::vector<int> recv_disps(size);
    int sum = 0;
    for (int src = 0; src < size; ++src) {
      recv_disps[src] = sum;
      sum += recv_sizes[src];
    }
    std::vector<char, allocator<char> > incoming(sum > 0? sum : 1);

    // Transmit the actual data
    BOOST_MPI_CHECK_RESULT(MPI_Alltoallv,
                           (&outgoing[0], &send_sizes[0],
                            &send_disps[0], MPI_PACKED,
                            &incoming[0], &recv_sizes[0],
                            &recv_disps[0], MPI_PACKED,
                            comm));

    // Deserialize data from the iarchive
    for (int src = 0; src < size; ++src) {
      if (src == rank) out_values[src] = in_values[src];
      else {
        packed_iarchive ia(comm, incoming, boost::archive::no_header,
                           recv_disps[src]);
        ia >> out_values[src];
      }
    }
  }
} // end namespace detail

template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values,
           std::vector<T>& out_values)
{
  BOOST_ASSERT((int)in_values.size() == comm.size());
  detail::all_to_all_impl(comm, in_values, out_values, is_mpi_datatype<T>());
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_ALL_TO_ALL_HPP
