
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

all :: r1.exe r2.exe r3.exe r4.exe r5.exe r6.exe r1m.exe r2m.exe r3m.exe r4m.exe r5m.exe r6m.exe r1v.exe r2v.exe r3v.exe r4v.exe r5v.exe r6v.exe r1l.exe r2l.exe r3l.exe r4l.exe r5l.exe r6l.exe r1lm.exe r2lm.exe r3lm.exe r4lm.exe r5lm.exe r6lm.exe r1lv.exe r2lv.exe r3lv.exe r4lv.exe r5lv.exe r6lv.exe
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
	echo testing static VCL version....
	r1v tests.txt test1252.txt
	r2v tests.txt
	r3v tests.txt
	r4v tests.txt test1252.txt
	r5v tests.txt
	r6v tests.txt
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
	echo testing dll VCL version....
	r1lv tests.txt test1252.txt
	r2lv tests.txt
	r3lv tests.txt
	r4lv tests.txt test1252.txt
	r5lv tests.txt
	r6lv tests.txt


r1.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er1.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er2.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er3.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er4.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er5.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -D_NO_VCL $(CFLAGS) -er6.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp
	

r1m.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er1m.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2m.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er2m.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3m.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er3m.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4m.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er4m.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5m.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er5m.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6m.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -D_NO_VCL $(CFLAGS) -er6m.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp


r1v.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er1v.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2v.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er2v.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3v.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er3v.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4v.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er4v.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5v.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er5v.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6v.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWV $(CFLAGS) -er6v.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp


r1l.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er1l.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2l.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er2l.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3l.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er3l.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4l.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er4l.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5l.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er5l.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6l.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM- -tWR -D_NO_VCL $(CFLAGS) -er6l.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp


r1lm.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er1lm.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2lm.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er2lm.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3lm.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er3lm.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4lm.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er4lm.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5lm.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er5lm.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6lm.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -D_NO_VCL $(CFLAGS) -er6lm.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp


r1lv.exe : tests.cpp regress.cpp parse.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er1lv.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp regress.cpp parse.cpp

r2lv.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er2lv.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp

r3lv.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er3lv.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp

r4lv.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er4lv.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r5lv.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er5lv.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp

r6lv.exe : tests.cpp parse.cpp regress.cpp
	$(BCC32) -tWM -tWR -tWV -tWC $(CFLAGS) -er6lv.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp











