
# very basic makefile for BitMachine
#
# GNU compiler GCC
#
INCLUDES= -I../../../../../boost_1_31_0 -I../../../../ -I./
CXXFLAGS= -O3 -ftemplate-depth-100  -DNDEBUG -finline-functions -Wno-inline -pthread -fPIC
CXX= $(INCLUDES) $(CXXFLAGS)
LDFLAGS=
LIBS=

BitMachine : BitMachine.cpp
	g++ $(CXX) -o BitMachine BitMachine.cpp $(LDFLAGS) $(LIBS)




















