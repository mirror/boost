
# very basic makefile for regression tests
# tests every library combination, static/dynamic/multimthread/singlethread/narrow/wide
#
# Sun Workshop 6 and greater:
#
CXX= CC $(INCLUDES) -I../../../../ -I./ $(CXXFLAGS) -L../../build/sunpro $(LDFLAGS)

total : r rm r/regress rm/regress rs rms rs/regress rms/regress rw rmw rw/regress rmw/regress rsw rmsw rsw/regress rmsw/regress
	echo testsing narrow character versions:
	./r/regress tests.txt
	./rm/regress tests.txt
	./rs/regress tests.txt
	./rms/regress tests.txt
	echo testsing wide character versions;
	./rw/regress tests.txt
	./rmw/regress tests.txt
	./rsw/regress tests.txt
	./rmsw/regress tests.txt

#
# delete the cache before each build.
# NB this precludes multithread builds:
#
r/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -o r/regress tests.cpp parse.cpp regress.cpp -lboost_regex$(LIBSUFFIX) $(LIBS)

rm/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -mt -o rm/regress tests.cpp parse.cpp regress.cpp -lboost_regex_mt$(LIBSUFFIX) $(LIBS)

rs/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -o rs/regress tests.cpp parse.cpp regress.cpp -Bstatic -lboost_regex$(LIBSUFFIX) -Bdynamic $(LIBS)

rms/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -mt -o rms/regress tests.cpp parse.cpp regress.cpp -Bstatic -lboost_regex_mt$(LIBSUFFIX) -Bdynamic $(LIBS)

rw/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -DTEST_UNICODE -o rw/regress tests.cpp parse.cpp regress.cpp -lboost_regex$(LIBSUFFIX) $(LIBS)

rmw/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -mt -DTEST_UNICODE -o rmw/regress tests.cpp parse.cpp regress.cpp -lboost_regex_mt$(LIBSUFFIX) $(LIBS)

rsw/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -DTEST_UNICODE -o rsw/regress tests.cpp parse.cpp regress.cpp -Bstatic -lboost_regex$(LIBSUFFIX) -Bdynamic $(LIBS)

rmsw/regress : tests.cpp parse.cpp regress.cpp
	rm -f *.o
	rm -fr SunWS_cache
	$(CXX) -O2 -mt -DTEST_UNICODE -o rmsw/regress tests.cpp parse.cpp regress.cpp -Bstatic -lboost_regex_mt$(LIBSUFFIX) -Bdynamic $(LIBS)

r:
	mkdir -p r

rm:
	mkdir -p rm

rs:
	mkdir -p rs

rms:
	mkdir -p rms

rw:
	mkdir -p rw

rmw:
	mkdir -p rmw

rsw:
	mkdir -p rsw

rmsw:
	mkdir -p rmsw

clean:
	rm -f *.o
	rm -fr SunWS_cache
	rm -fr r rm rs rms rw rmw rsw rmsw







































