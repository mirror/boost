
# very basic makefile for regression tests
#
# Visual C++ 6
#
CFLAGS= /Oityb1 /GF /Gy -GX -GR -I..\..\..\..\

LFLAGS= -link /LIBPATH:..\..\lib\vc6 user32.lib

all :: r1.exe r2.exe r3.exe r4.exe r5.exe r6.exe r1m.exe r2m.exe r3m.exe r4m.exe r5m.exe r6m.exe r1l.exe r2l.exe r3l.exe r4l.exe r5l.exe r6l.exe r1d.exe r2d.exe r3d.exe r4d.exe r5d.exe r6d.exe r1md.exe r2md.exe r3md.exe r4md.exe r5md.exe r6md.exe r1lmd.exe r2lmd.exe r3lmd.exe r4lmd.exe r5lmd.exe r6lmd.exe
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
	echo testing DLL version....
	r1l tests.txt test1252.txt
	r2l tests.txt
	r3l tests.txt
	r4l tests.txt test1252.txt
	r5l tests.txt
	r6l tests.txt
	echo testing static single threaded debug version....
	r1d tests.txt test1252.txt
	r2d tests.txt
	r3d tests.txt
	r4d tests.txt test1252.txt
	r5d tests.txt
	r6d tests.txt
	echo testing static multi-threaded debug version....
	r1md tests.txt test1252.txt
	r2md tests.txt
	r3md tests.txt
	r4md tests.txt test1252.txt
	r5md tests.txt
	r6md tests.txt
	echo testing dll debug version....
	r1lmd tests.txt test1252.txt
	r2lmd tests.txt
	r3lmd tests.txt
	r4lmd tests.txt test1252.txt
	r5lmd tests.txt
	r6lmd tests.txt


r1.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r1.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r2.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r3.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r4.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r5.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6.exe : tests.cpp parse.cpp regress.cpp
	cl /ML $(CFLAGS) -o r6.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)
	

r1m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT -o r1m.exe $(CFLAGS) -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT $(CFLAGS) -o r2m.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT $(CFLAGS) -o r3m.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT $(CFLAGS) -o r4m.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT $(CFLAGS) -o r5m.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6m.exe : tests.cpp parse.cpp regress.cpp
	cl /MT /D_MT $(CFLAGS) -o r6m.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)


r1l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r1l.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r2l.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r3l.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r4l.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r5l.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6l.exe : tests.cpp parse.cpp regress.cpp
	cl /MD /D_MT /D_DLL $(CFLAGS) -o r6l.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)


r1d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r1d.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r2d.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r3d.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r4d.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r5d.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6d.exe : tests.cpp parse.cpp regress.cpp
	cl /MLd $(CFLAGS) -o r6d.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)


r1md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r1md.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r2md.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r3md.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r4md.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r5md.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6md.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r6md.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)


r1lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r1lmd.exe -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r2lmd.exe -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r3lmd.exe -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r4lmd.exe -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r5lmd.exe -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6lmd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r6lmd.exe -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)















