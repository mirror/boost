
# very basic makefile for timer.exe
#
# GNU compiler GCC
#
CXX= $(INCLUDES) -I../../../../ -I./ $(CXXFLAGS)

timer : regex_timer.cpp
	g++ $(CXX) -O2 -o timer regex_timer.cpp -L../../lib/gcc $(LDFLAGS) -lregex++ $(LIBS)

debug : regex_timer.cpp timer.cpp 
	g++ $(CXX) -g -o timer regex_timer.cpp -L../../lib/gcc $(LDFLAGS) -lregex++debug $(LIBS)




















