// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gather
#ifndef BOOST_PARALLEL_MPI_GATHER_HPP
#define BOOST_PARALLEL_MPI_GATHER_HPP

#include <boost/parallel/mpi/exception.hpp>
#include <boost/parallel/mpi/datatype.hpp>
#include <vector>
#include <boost/parallel/mpi/packed_oarchive.hpp>
#include <boost/parallel/mpi/packed_iarchive.hpp>
#include <boost/parallel/mpi/detail/point_to_point.hpp>
#include <boost/parallel/mpi/communicator.hpp>
#include <boost/parallel/mpi/environment.hpp>
#include <boost/assert.hpp>

namespace boost { namespace parallel { namespace mpi {

namespace detail {
  // We're gathering at the root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gather to do all of the work.
  template<typename T>
  void
  gather_impl(const communicator& comm, const T& value, std::vector<T>& values,
              int root, mpl::true_)
  {
    values.resize(comm.size());

    MPI_Datatype type = get_mpi_datatype<T>();
    BOOST_MPI_CHECK_RESULT(MPI_Gather,
                           (const_cast<T*>(&value), 1, type,
                            &values[0], 1, type, root, comm));
  }

  // We're gathering from a non-root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gather to do all of the work.
  template<typename T>
  void
  gather_impl(const communicator& comm, const T& value, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>();
    BOOST_MPI_CHECK_RESULT(MPI_Gather,
                           (const_cast<T*>(&value), 1, type,
                            0, 1, type, root, comm));
  }

  // We're gathering at the root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Gather, so
  // we'll just have all of the non-root nodes send individual
  // messages to the root.
  template<typename T>
  void
  gather_impl(const communicator& comm, const T& value, std::vector<T>& values,
              int root, mpl::false_)
  {
    int tag = environment::collectives_tag();
    int size = comm.size();

    // We know we'll get "size" values
    values.clear();
    values.reserve(size);

    MPI_Status status;
    for (int src = 0; src < size; ++src) {
      if (src == root) {
        // Our own value will never be transmitted: just copy it.
        values.push_back(value);
      } else {
        // Receive archive
        packed_iarchive ia(comm);
        detail::packed_archive_recv(comm, src, tag, ia, status);

        // Unpack the data
        T value_from_src;
        ia >> value_from_src;

        // Save the result
        values.push_back(value_from_src);
      }
    }
  }

  // We're gathering at a non-root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Gather, so
  // we'll just have all of the non-root nodes send individual
  // messages to the root.
  template<typename T>
  void
  gather_impl(const communicator& comm, const T& value, int root, mpl::false_)
  {
    int tag = environment::collectives_tag();

    packed_oarchive oa(comm);
    oa << value;
    detail::packed_archive_send(comm, root, tag, oa);
  }
} // end namespace detail

template<typename T>
void
gather(const communicator& comm, const T& value, std::vector<T>& values,
       int root)
{
  if (comm.rank() == root)
    detail::gather_impl(comm, value, values, root, is_mpi_datatype<T>());
  else
    detail::gather_impl(comm, value, root, is_mpi_datatype<T>());
}

template<typename T>
void gather(const communicator& comm, const T& value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gather_impl(comm, value, root, is_mpi_datatype<T>());
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_GATHER_HPP
