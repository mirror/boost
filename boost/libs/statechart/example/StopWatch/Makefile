
# very basic makefile for StopWatch
#
# GNU compiler GCC
#
INCLUDES= -I$(BOOST_ROOT) -I../../../../ -I./
CXXFLAGS= -O3 -ftemplate-depth-100  -DNDEBUG -finline-functions -Wno-inline -pthread -fPIC
CXX= $(INCLUDES) $(CXXFLAGS)
LDFLAGS=
LIBS= -lc

StopWatch : StopWatch.cpp
	g++ $(CXX) -o StopWatch StopWatch.cpp $(LDFLAGS) $(LIBS)




















