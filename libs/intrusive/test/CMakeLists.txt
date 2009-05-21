# Boost Intrusive Library Test Jamfile
#  (C) Copyright Ion Gaztanaga 2006.
# Use, modification and distribution are subject to the 
# Boost Software License, Version 1.0. (See accompanying file 
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Adapted from John Maddock's TR1 Jamfile.v2
# Copyright John Maddock 2005.
# Use, modification and distribution are subject to the 
# Boost Software License, Version 1.0. (See accompanying file 
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# this rule enumerates through all the sources and invokes
# the run rule for each source, the result is a list of all
# the run rules, which we can pass on to the test_suite rule:

file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(testfile ${SRCFILES})
  get_filename_component(testname ${testfile} NAME_WE)
  boost_test_run(${testname})
endforeach()

