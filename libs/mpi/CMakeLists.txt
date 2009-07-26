#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
FIND_PACKAGE(MPI)

if (NOT MPI_FOUND)
 message(STATUS "MPI Not Found")
endif (NOT MPI_FOUND)


boost_library_project(
  mpi
  SRCDIRS   src
  TESTDIRS  test
  HEADERS   mpi.hpp mpi
  DOCDIRS   doc
  #  DESCRIPTION 
  MODULARIZED
  #  AUTHORS 
  #  MAINTAINERS 
  )


