
# very basic makefile for regression tests
#
# Visual C++ 6 + full stlport 4.x
#
# we don't test single threaded builds as stlport doesn't support these...
#
CFLAGS= /Oityb1 /GF /Gy -GX -GR -I..\..\..\..\

LFLAGS= -link /LIBPATH:..\..\lib\vc6-stlport user32.lib

all :: r1m.exe r2m.exe r3m.exe r4m.exe r5m.exe r6m.exe r1l.exe r2l.exe r3l.exe r4l.exe r5l.exe r6l.exe r1md.exe r2md.exe r3md.exe r4md.exe r5md.exe r6md.exe r1lmd.exe r2lmd.exe r3lmd.exe r4lmd.exe r5lmd.exe r6lmd.exe r1mdd.exe r2mdd.exe r3mdd.exe r4mdd.exe r5mdd.exe r6mdd.exe r1lmdd.exe r2lmdd.exe r3lmdd.exe
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
	echo testing static multi-threaded stl-debug version....
	r1mdd tests.txt test1252.txt
	r2mdd tests.txt
	r3mdd tests.txt
	r4mdd tests.txt test1252.txt
	r5mdd tests.txt
	r6mdd tests.txt
	echo testing dll stl-debug version....
	r1lmdd tests.txt test1252.txt
	r2lmdd tests.txt
	r3lmdd tests.txt


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

r1lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r1lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r2lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r3lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r4lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r5lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6lmdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MDd /D_MT /D_DLL $(CFLAGS) -o r6lmdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r1mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r1mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_W32 tests.cpp parse.cpp regress.cpp $(LFLAGS)

r2mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r2mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_C tests.cpp parse.cpp regress.cpp $(LFLAGS)

r3mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r3mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_CPP tests.cpp parse.cpp regress.cpp $(LFLAGS)

r4mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r4mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_W32 -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r5mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r5mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_C -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)

r6mdd.exe : tests.cpp parse.cpp regress.cpp
	cl /MTd /D_MT $(CFLAGS) -o r6mdd.exe -D__STL_DEBUG -DBOOST_RE_TEST_LOCALE_CPP -DTEST_UNICODE tests.cpp parse.cpp regress.cpp $(LFLAGS)



