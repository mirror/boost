// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface

/** @file mpi.hpp
 *
 *  This file is a top-level convenience header that includes all of
 *  the Boost.MPI library headers. Users concerned about compile time
 *  may wish to include only specific headers from the Boost.MPI
 *  library.
 *
 */
#ifndef BOOST_MPI_HPP
#define BOOST_MPI_HPP

#include <boost/parallel/mpi/allocator.hpp>
#include <boost/parallel/mpi/collectives.hpp>
#include <boost/parallel/mpi/communicator.hpp>
#include <boost/parallel/mpi/datatype.hpp>
#include <boost/parallel/mpi/environment.hpp>
#include <boost/parallel/mpi/nonblocking.hpp>
#include <boost/parallel/mpi/operations.hpp>
#include <boost/parallel/mpi/skeleton_and_content.hpp>
#include <boost/parallel/mpi/timer.hpp>

#endif // BOOST_MPI_HPP
