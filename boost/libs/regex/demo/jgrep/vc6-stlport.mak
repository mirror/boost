
#
# very simple makefile for Visual C++ 6 + STLPort 4
#

jgrep.exe: main.cpp jgrep.cpp jgrep.h
	cl -GX -GR -O2 -MT -I..\..\..\..\ jgrep.cpp main.cpp /link /LIBPATH:..\..\lib\vc6-stlport user32.lib









