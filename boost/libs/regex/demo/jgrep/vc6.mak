
#
# very simple makefile for Visual C++ 6
#

jgrep.exe: main.cpp jgrep.cpp jgrep.h
	cl -GX -GR -O2 -I..\..\..\..\ jgrep.cpp main.cpp /link /LIBPATH:..\..\lib\vc6 user32.lib








