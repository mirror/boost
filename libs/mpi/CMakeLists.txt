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


