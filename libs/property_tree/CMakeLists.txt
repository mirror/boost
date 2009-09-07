#
# Copyright Sebastian Redl
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
#----------------------------------------------------------------------------
# This file was automatically generated from the original CMakeLists.txt file
# Add a variable to hold the headers for the library
set (lib_headers
    property_tree
)

# Add a library target to the build system
boost_library_project(
  property_tree
  #  SRCDIRS 
  TESTDIRS test
  HEADERS ${lib_headers}
  #  DOCDIRS
  #  DESCRIPTION  "Helps Boost library developers adapt to compiler idiosyncrasies; not intended for library users."
  MODULARIZED 
  #  AUTHORS  "John Maddock <john -at- johnmaddock.co.uk>"
  #  MAINTAINERS 
)


