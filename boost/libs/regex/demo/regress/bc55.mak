
# very basic makefile for regress
#
# Borland C++ tools
#
# BCROOT defines the root directory of your bcb install
#
!ifndef BCROOT
BCROOT=$(MAKEDIR)\..
!endif

BCC32   = $(BCROOT)\bin\Bcc32.exe 
TLINK32 = $(BCROOT)\bin\ILink32.exe

IDE_LinkFLAGS32 =  -L$(BCROOT)\LIB
LINKOPTS= -ap -Tpe -x
CFLAGS= -O2 -tWC -DSTRICT; -w-inl -w-aus -w-csu -w-eff -w-rch -I$(BCROOT)\include;..\..\..\..\; -L..\..\lib\bcb5

all :: r1.exe r2.exe r3.exe r4.exe r5.exe r6.exe r1m.exe r2m.exe r3m.exe r4m.exe r5m.exe r6m.exe r1l.exe r2l.exe r3l.exe r4l.exe r5l.exe r6l.exe r1lm.exe r2lm.exe r3lm.exe r4lm.exe r5lm.exe r6lm.exe
	echo testing static single threaded version....
	r1 tests.txt test1252.txt
	r2 tests.txt
	r3 tests.txt
	r4 tests.txt test1252.txt
	r5 tests.txt
	r6 tests.txt
	echo testing static multi-threaded version....
	r1m tests.txt test1252.txt
	r2m tests.txt
	r3m tests.txt
	r4m tests.txt test1252.txt
	r5m tests.txt
	r6m tests.txt
	echo testing dll single threaded version....
	r1l tests.txt test1252.txt
	r2l tests.txt
	r3l tests.txt
	r4l tests.txt test1252.txt
	r5l tests.txt
	r6l tests.txt
	echo testing dll multi-threaded version....
	r1lm tests.txt test1252.txt
	r2lm tests.txt
	r3lm tests.txt
	r4lm tests.txt test1252.txt
	r5lm tests.txt
	r6lm tests.txt


r1.exe : r1.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r1.cpp

r2.exe : r2.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r2.cpp

r3.exe : r3.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r3.cpp

r4.exe : r4.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r4.cpp

r5.exe : r5.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r5.cpp

r6.exe : r6.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) r6.cpp
	

r1m.exe : r1.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er1m.exe r1.cpp

r2m.exe : r2.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er2m.exe r2.cpp

r3m.exe : r3.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er3m.exe r3.cpp

r4m.exe : r4.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er4m.exe r4.cpp

r5m.exe : r5.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er5m.exe r5.cpp

r6m.exe : r6.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er6m.exe r6.cpp


r1l.exe : r1.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er1l.exe r1.cpp

r2l.exe : r2.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er2l.exe r2.cpp

r3l.exe : r3.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er3l.exe r3.cpp

r4l.exe : r4.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er4l.exe r4.cpp

r5l.exe : r5.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er5l.exe r5.cpp

r6l.exe : r6.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er6l.exe r6.cpp


r1lm.exe : r1.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er1lm.exe r1.cpp

r2lm.exe : r2.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er2lm.exe r2.cpp

r3lm.exe : r3.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er3lm.exe r3.cpp

r4lm.exe : r4.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er4lm.exe r4.cpp

r5lm.exe : r5.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er5lm.exe r5.cpp

r6lm.exe : r6.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er6lm.exe r6.cpp




