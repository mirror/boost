#=============================================================================
#    Copyright (c) 2008 Dan Marsden
#  
#    Use modification and distribution are subject to the Boost Software 
#    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
#    http://www.boost.org/LICENSE_1_0.txt).
#==============================================================================

CXX=g++
CXXFLAGS=-I$(BOOST_ROOT)

all: vector_construction vector_iteration vector_intrinsic

vector_construction: vector_construction.cpp
	time $(CXX) $(CXXFLAGS) vector_construction.cpp -o vector_construction

vector_iteration: vector_iteration.cpp
	time $(CXX) $(CXXFLAGS) vector_iteration.cpp -o vector_iteration

vector_intrinsic: vector_intrinsic.cpp
	time $(CXX) $(CXXFLAGS) vector_intrinsic.cpp -o vector_intrinsic

clean:
	rm -f vector_construction vector_construction.o vector_iteration vector_iteration.o vector_intrinsic vector_intrinsic.o
