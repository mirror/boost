// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor@gmail.com>.
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Reduce
#ifndef BOOST_PARALLEL_MPI_REDUCE_HPP
#define BOOST_PARALLEL_MPI_REDUCE_HPP

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
   * Simple reduction with MPI_Reduce                                   *
   **********************************************************************/
  // We are reducing at the root for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Reduce directly.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, T& out_value, Op op,
              int root, mpl::true_ /*is_mpi_op*/,
              mpl::true_/*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(&in_value), &out_value, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            is_mpi_op<Op, T>::op(), root, comm));
  }

  // We are reducing to the root for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Reduce directly.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, Op op, int root,
              mpl::true_ /*is_mpi_op*/, mpl::true_/*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(&in_value), 0, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            is_mpi_op<Op, T>::op(), root, comm));
  }

  // We are reducing at the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, T& out_value,
              Op op, int root, mpl::false_ /*is_mpi_op*/,
              mpl::true_/*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op(op);
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(&in_value), &out_value, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            mpi_op.get_mpi_op(), root, comm));
  }

  /**********************************************************************
   * User-defined reduction with MPI_Reduce                             *
   **********************************************************************/

  // We are reducing to the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, Op op, int root,
              mpl::false_ /*is_mpi_op*/, mpl::true_/*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op(op);
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(&in_value), 0, 1,
                            boost::parallel::mpi::get_mpi_datatype<T>(),
                            mpi_op.get_mpi_op(), root, comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/

  // Commutative reduction
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T& in_value, T& out_value,
                   Op op, int root, mpl::true_ /*is_commutative*/)
  {
    out_value = in_value;

    int size = comm.size();
    int rank = comm.rank();

    // The computation tree we will use.
    detail::computation_tree tree(rank, size, root);

    int tag = environment::collectives_tag();

    MPI_Status status;
    int children = 0;
    for (int child = tree.child_begin();
         children < tree.branching_factor() && child != root;
         ++children, child = (child + 1) % size) {
      // Receive archive
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, child, tag, ia, status);

      T incoming;
      ia >> incoming;

      out_value = op(out_value, incoming);
    }

    // For non-roots, send the result to the parent.
    if (tree.parent() != rank) {
      packed_oarchive oa(comm);
      oa << out_value;
      detail::packed_archive_send(comm, tree.parent(), tag, oa);
    }
  }

  // Commutative reduction from a non-root.
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T& in_value, Op op,
                   int root, mpl::true_ /*is_commutative*/)
  {
    T result;
    detail::tree_reduce_impl(comm, in_value, result, op, root, mpl::true_());
  }

  // Non-commutative reduction
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T& in_value, T& out_value,
                   Op op, int root, mpl::false_ /*is_commutative*/)
  {
    int tag = environment::collectives_tag();

    int left_child = root / 2;
    int right_child = (root + comm.size()) / 2;

    MPI_Status status;
    if (left_child != root) {
      // Receive value from the left child and merge it with the value
      // we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, left_child, tag, ia, status);
      T incoming;
      ia >> incoming;
      out_value = op(incoming, in_value);
    } else {
      // There was no left value, so copy our incoming value.
      out_value = in_value;
    }

    if (right_child != root) {
      // Receive value from the right child and merge it with the
      // value we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, right_child, tag, ia, status);
      T incoming;
      ia >> incoming;
      out_value = op(out_value, incoming);
    }
  }

  // Non-commutative reduction from a non-root.
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T& in_value, Op op,
                   int root, mpl::false_ /*is_commutative*/)
  {
    int size = comm.size();
    int rank = comm.rank();

    int tag = environment::collectives_tag();

    // Determine our parents and children in the commutative binary
    // computation tree.
    int grandparent = root;
    int parent = root;
    int left_bound = 0;
    int right_bound = size;
    int left_child, right_child;
    do {
      left_child = (left_bound + parent) / 2;
      right_child = (parent + right_bound) / 2;

      if (rank < parent) {
        // Go left.
        grandparent = parent;
        right_bound = parent;
        parent = left_child;
      } else if (rank > parent) {
        // Go right.
        grandparent = parent;
        left_bound = parent + 1;
        parent = right_child;
      } else {
        // We've found the parent/
        break;
      }
    } while (true);

    // Our parent is the grandparent of our children. This is a slight
    // abuse of notation, but it makes the send-to-parent below make
    // more sense.
    parent = grandparent;

    MPI_Status status;
    T out_value;
    if (left_child != rank) {
      // Receive value from the left child and merge it with the value
      // we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, left_child, tag, ia, status);
      T incoming;
      ia >> incoming;
      out_value = op(incoming, in_value);
    } else {
      // There was no left value, so copy our incoming value.
      out_value = in_value;
    }

    if (right_child != rank) {
      // Receive value from the right child and merge it with the
      // value we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, right_child, tag, ia, status);
      T incoming;
      ia >> incoming;
      out_value = op(out_value, incoming);
    }

    // Send the combined value to our parent.
    packed_oarchive oa(comm);
    oa << out_value;
    detail::packed_archive_send(comm, parent, tag, oa);
  }

  // We are reducing at the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, T& out_value, Op op,
              int root, mpl::false_ /*is_mpi_op*/,
              mpl::false_/*is_mpi_datatype*/)
  {
    detail::tree_reduce_impl(comm, in_value, out_value, op, root,
                             is_commutative<Op, T>());
  }

  // We are reducing to the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T& in_value, Op op, int root,
              mpl::false_ /*is_mpi_op*/, mpl::false_/*is_mpi_datatype*/)
  {
    detail::tree_reduce_impl(comm, in_value, op, root,
                             is_commutative<Op, T>());
  }
} // end namespace detail


template<typename T, typename Op>
void
reduce(const communicator& comm, const T& in_value, T& out_value, Op op,
       int root)
{
  if (comm.rank() == root)
    detail::reduce_impl(comm, in_value, out_value, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  else
    detail::reduce_impl(comm, in_value, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
void reduce(const communicator& comm, const T& in_value, Op op, int root)
{
  BOOST_ASSERT(comm.rank() != root);

  detail::reduce_impl(comm, in_value, op, root,
                      is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

} } } // end namespace boost::parallel::mpi

#endif // BOOST_PARALLEL_MPI_REDUCE_HPP
