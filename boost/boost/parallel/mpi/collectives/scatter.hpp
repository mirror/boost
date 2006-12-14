// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatter
#ifndef BOOST_PARALLEL_MPI_SCATTER_HPP
#define BOOST_PARALLEL_MPI_SCATTER_HPP

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
  // We're scattering from the root for a type that has an associated MPI
  // datatype, so we'll use MPI_Scatter to do all of the work.
  template<typename T>
  void
  scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
               int n, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>();
    BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, root, comm));
  }

  // We're scattering from a non-root for a type that has an associated MPI
  // datatype, so we'll use MPI_Scatter to do all of the work.
  template<typename T>
  void
  scatter_impl(const communicator& comm, T* out_values, int n, int root, 
               mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>();
    BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                           (0, n, type,
                            out_values, n, type,
                            root, comm));
  }

  // We're scattering from the root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Scatter, so
  // we'll just have the root send individual messages to the other
  // processes.
  template<typename T>
  void
  scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
               int n, int root, mpl::false_)
  {
    int tag = environment::collectives_tag();
    int size = comm.size();

    for (int dest = 0; dest < size; ++dest) {
      if (dest == root) {
        // Our own values will never be transmitted: just copy them.
        std::copy(in_values + dest * n, in_values + (dest + 1) * n, out_values);
      } else {
        // Send archive
        packed_oarchive oa(comm);
        for (int i = 0; i < n; ++i)
          oa << in_values[dest * n + i];
        detail::packed_archive_send(comm, dest, tag, oa);
      }
    }
  }

  // We're scattering to a non-root for a type that does not have an
  // associated MPI datatype, so we'll need to de-serialize
  // it. Unfortunately, this means that we cannot use MPI_Scatter, so
  // we'll just have all of the non-root nodes send individual
  // messages to the root.
  template<typename T>
  void
  scatter_impl(const communicator& comm, T* out_values, int n, int root, 
               mpl::false_)
  {
    int tag = environment::collectives_tag();

    packed_iarchive ia(comm);
    MPI_Status status;
    detail::packed_archive_recv(comm, root, tag, ia, status);
    for (int i = 0; i < n; ++i)
      ia >> out_values[i];
  }
} // end namespace detail

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root)
{
  if (comm.rank() == root)
    detail::scatter_impl(comm, in_values, &out_value, 1, root, 
                         is_mpi_datatype<T>());
  else
    detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, T& out_value,
        int root)
{
  if (comm.rank() == root)
    ::boost::parallel::mpi::scatter(comm, &in_values[0], out_value, root);
  else
    ::boost::parallel::mpi::scatter(comm, static_cast<const T*>(0), out_value, 
                                    root);
}

template<typename T>
void scatter(const communicator& comm, T& out_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T* out_values, int n,
        int root)
{
  if (comm.rank() == root)
    detail::scatter_impl(comm, in_values, n, out_values, root, 
                         is_mpi_datatype<T>());
  else
    detail::scatter_impl(comm, out_values, n, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, 
        T* out_values, int n, int root)
{
  if (comm.rank() == root)
    ::boost::parallel::mpi::scatter(comm, &in_values[0], out_values, n, root);
  else
    ::boost::parallel::mpi::scatter(comm, static_cast<const T*>(0), out_values, 
                                    n, root);
}

template<typename T>
void scatter(const communicator& comm, T* out_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, out_values, n, root, is_mpi_datatype<T>());
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_SCATTER_HPP
