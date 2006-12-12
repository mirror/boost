// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor@gmail.com>.
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Scan
#ifndef BOOST_PARALLEL_MPI_SCAN_HPP
#define BOOST_PARALLEL_MPI_SCAN_HPP

#include <boost/parallel/mpi/exception.hpp>
#include <boost/parallel/mpi/datatype.hpp>

// For (de-)serializing sends and receives
#include <boost/parallel/mpi/packed_oarchive.hpp>
#include <boost/parallel/mpi/packed_iarchive.hpp>

// For packed_[io]archive sends and receives
#include <boost/parallel/mpi/detail/point_to_point.hpp>

#include <boost/parallel/mpi/communicator.hpp>
#include <boost/parallel/mpi/environment.hpp>
#include <boost/parallel/mpi/detail/computation_tree.hpp>
#include <boost/parallel/mpi/operations.hpp>
#include <algorithm>
#include <exception>
#include <boost/assert.hpp>

namespace boost { namespace parallel { namespace mpi {


/************************************************************************
 * Implementation details                                               *
 ************************************************************************/
namespace detail {
  /**********************************************************************
   * Simple prefix reduction with MPI_Scan                              *
   **********************************************************************/

  // We are performing prefix reduction for a type that has an
  // associated MPI datatype and operation, so we'll use MPI_Scan
  // directly.
  template<typename T, typename Op>
  void
  scan_impl(const communicator& comm, const T& in_value, T& out_value, Op op,
            mpl::true_ /*is_mpi_op*/, mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Scan,
                           (const_cast<T*>(&in_value), &out_value, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            is_mpi_op<Op, T>::op(), comm));
  }

  /**********************************************************************
   * User-defined prefix reduction with MPI_Scan                        *
   **********************************************************************/

  // We are performing prefix reduction for a type that has an
  // associated MPI datatype but with a custom operation. We'll use
  // MPI_Scan directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  scan_impl(const communicator& comm, const T& in_value, T& out_value,
            Op op, mpl::false_ /*is_mpi_op*/, mpl::true_ /*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op(op);
    BOOST_MPI_CHECK_RESULT(MPI_Scan,
                           (const_cast<T*>(&in_value), &out_value, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            mpi_op.get_mpi_op(), comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/

  template<typename T, typename Op>
  void
  upper_lower_scan(const communicator& comm, const T& in_value, 
                   T& out_value, Op& op, int lower, int upper)
  {
    int tag = environment::collectives_tag();
    int rank = comm.rank();

    if (lower + 1 == upper) {
      out_value = in_value;
    } else {
      int middle = (lower + upper) / 2;
      
      if (rank < middle) {
        // Lower half
        upper_lower_scan(comm, in_value, out_value, op, lower, middle);

        // If we're the last process in the lower half, send our value
        // to everyone in the upper half.
        if (rank == middle - 1) {
          for (int p = middle; p < upper; ++p)
            comm.send(p, tag, out_value);
        }
      } else {
        // Upper half
        upper_lower_scan(comm, in_value, out_value, op, middle, upper);

        // Receive value from the last process in the lower half.
        T left_value;
        comm.recv(middle - 1, tag, left_value);

        // Combine value that came from the left with our value
        out_value = op(left_value, out_value);
      }
    }
  }

  // We are performing prefix reduction for a type that has no
  // associated MPI datatype and operation, so we'll use a simple
  // upper/lower algorithm.
  template<typename T, typename Op>
  inline void
  scan_impl(const communicator& comm, const T& in_value, T& out_value, Op op,
            mpl::false_ /*is_mpi_op*/, mpl::false_/*is_mpi_datatype*/)
  {
    upper_lower_scan(comm, in_value, out_value, op, 0, comm.size());
  }
} // end namespace detail


template<typename T, typename Op>
inline void
scan(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::scan_impl(comm, in_value, out_value, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline T
scan(const communicator& comm, const T& in_value, Op op)
{
  T out_value;
  detail::scan_impl(comm, in_value, out_value, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  return out_value;
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_SCAN_HPP
