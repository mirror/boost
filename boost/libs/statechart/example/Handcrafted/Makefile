
# very basic makefile for Handcrafted
#
# GNU compiler GCC
#
INCLUDES= -I../../../../../boost_1_31_0 -I../../../../ -I./
CXXFLAGS= -O3 -ftemplate-depth-100  -DNDEBUG -finline-functions -Wno-inline -pthread -fPIC
CXX= $(INCLUDES) $(CXXFLAGS)
LDFLAGS=
LIBS= 

Handcrafted : Handcrafted.cpp
	g++ $(CXX) -o Handcrafted Handcrafted.cpp $(LDFLAGS) $(LIBS)




















