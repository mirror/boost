
# very basic makefile for PingPong
#
# GNU compiler GCC
#
INCLUDES= -I../../../../../boost_1_31_0 -I../../../../ -I./
CXXFLAGS= -O3 -ftemplate-depth-100  -DNDEBUG -finline-functions -Wno-inline -pthread -fPIC
CXX= $(INCLUDES) $(CXXFLAGS)
LDFLAGS=
LIBS= -L. -lboost_thread-gcc-mt

PingPong : PingPong.cpp
	g++ $(CXX) -o PingPong PingPong.cpp $(LDFLAGS) $(LIBS)




















