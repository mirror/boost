
# very basic makefile for Camera
#
# GNU compiler GCC
#
INCLUDES= -I../../../../../boost_1_31_0 -I../../../../ -I./
CXXFLAGS= -O3 -ftemplate-depth-100  -DNDEBUG -finline-functions -Wno-inline -pthread -fPIC
CXX= $(INCLUDES) $(CXXFLAGS)
LDFLAGS=
LIBS= 
SRCS= Main.cpp Camera.cpp Configuring.cpp Precompiled.cpp Shooting.cpp
OBJS= Main.o Camera.o Configuring.o Precompiled.o Shooting.o

all: Camera

Camera: $(OBJS)
	g++ $(CXX) -o Camera $(OBJS) $(LDFLAGS) $(LIBS)


Main.o: Main.cpp
	g++ -c $(CXX) -o Main.o Main.cpp

Camera.o: Camera.cpp Camera.hpp
	g++ -c $(CXX) -o Camera.o Camera.cpp

Configuring.o: Configuring.cpp Configuring.hpp
	g++ -c $(CXX) -o Configuring.o Configuring.cpp

Precompiled.o: Precompiled.cpp Precompiled.hpp
	g++ -c $(CXX) -o Precompiled.o Precompiled.cpp

Shooting.o: Shooting.cpp Shooting.hpp
	g++ -c $(CXX) -o Shooting.o Shooting.cpp




















