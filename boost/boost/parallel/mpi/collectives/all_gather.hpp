// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.7. Gather-to-all
#ifndef BOOST_PARALLEL_MPI_ALL_GATHER_HPP
#define BOOST_PARALLEL_MPI_ALL_GATHER_HPP

#include <boost/parallel/mpi/exception.hpp>
#include <boost/parallel/mpi/datatype.hpp>
#include <vector>
#include <boost/serialization/vector.hpp>

// all_gather falls back to gather+broadcast in some cases
#include <boost/parallel/mpi/collectives/broadcast.hpp>
#include <boost/parallel/mpi/collectives/gather.hpp>

namespace boost { namespace parallel { namespace mpi {

namespace detail {
  // We're all-gathering for a type that has an associated MPI
  // datatype, so we'll use MPI_Gather to do all of the work.
  template<typename T>
  void
  all_gather_impl(const communicator& comm, const T& value,
                  std::vector<T>& values, mpl::true_)
  {
    values.resize(comm.size());

    MPI_Datatype type = boost::parallel::mpi::get_mpi_datatype<T>();
    BOOST_MPI_CHECK_RESULT(MPI_Allgather,
                           (const_cast<T*>(&value), 1, type,
                            &values[0], 1, type, comm));
  }

  // We're all-gathering for a type that has no associated MPI. So,
  // we'll do a manual gather followed by a broadcast.
  template<typename T>
  void
  all_gather_impl(const communicator& comm, const T& value,
                  std::vector<T>& values, mpl::false_)
  {
    gather(comm, value, values, 0);
    broadcast(comm, values, 0);
  }
} // end namespace detail

template<typename T>
void
all_gather(const communicator& comm, const T& value, std::vector<T>& values)
{
  detail::all_gather_impl(comm, value, values, is_mpi_datatype<T>());
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_ALL_GATHER_HPP
