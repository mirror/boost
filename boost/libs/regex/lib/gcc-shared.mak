#
# auto generated makefile for gcc compiler
#
# usage:
# make
#   brings libraries up to date
# make clean
#   deletes temporary object files (but not archives).
#

#
# compiler options for release build:
#
C1=-c -O2 -I../../../ -fPIC
#
# compiler options for debug build:
#
C2=-c -g -I../../../ -fPIC
#
# compiler options for link:
LINK=-shared
#
# Linker to use:
LINKER=ld



ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : gcc  gcc gcc/regex++ ./gcc/libregex++.so gcc gcc/regex++debug ./gcc/libregex++debug.so

gcc :
	mkdir -p gcc

clean :  regex++_clean regex++debug_clean

install : all



########################################################
#
# section for libregex++.a
#
########################################################
gcc/regex++/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/c_regex_traits.o $(C1) $(XCFLAGS) ../src/c_regex_traits.cpp

gcc/regex++/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/c_regex_traits_common.o $(C1) $(XCFLAGS) ../src/c_regex_traits_common.cpp

gcc/regex++/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/cpp_regex_traits.o $(C1) $(XCFLAGS) ../src/cpp_regex_traits.cpp

gcc/regex++/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/cregex.o $(C1) $(XCFLAGS) ../src/cregex.cpp

gcc/regex++/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/fileiter.o $(C1) $(XCFLAGS) ../src/fileiter.cpp

gcc/regex++/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/posix_api.o $(C1) $(XCFLAGS) ../src/posix_api.cpp

gcc/regex++/regex.o: ../src/regex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex.o $(C1) $(XCFLAGS) ../src/regex.cpp

gcc/regex++/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex_debug.o $(C1) $(XCFLAGS) ../src/regex_debug.cpp

gcc/regex++/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex_synch.o $(C1) $(XCFLAGS) ../src/regex_synch.cpp

gcc/regex++/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/w32_regex_traits.o $(C1) $(XCFLAGS) ../src/w32_regex_traits.cpp

gcc/regex++/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/wide_posix_api.o $(C1) $(XCFLAGS) ../src/wide_posix_api.cpp

gcc/regex++ : 
	mkdir -p gcc/regex++

regex++_clean :
	rm -f gcc/regex++/*.o

./gcc/libregex++.so : gcc/regex++/c_regex_traits.o gcc/regex++/c_regex_traits_common.o gcc/regex++/cpp_regex_traits.o gcc/regex++/cregex.o gcc/regex++/fileiter.o gcc/regex++/posix_api.o gcc/regex++/regex.o gcc/regex++/regex_debug.o gcc/regex++/regex_synch.o gcc/regex++/w32_regex_traits.o gcc/regex++/wide_posix_api.o
	$(LINKER) $(LINK) -o gcc/libregex++.so  gcc/regex++/c_regex_traits.o gcc/regex++/c_regex_traits_common.o gcc/regex++/cpp_regex_traits.o gcc/regex++/cregex.o gcc/regex++/fileiter.o gcc/regex++/posix_api.o gcc/regex++/regex.o gcc/regex++/regex_debug.o gcc/regex++/regex_synch.o gcc/regex++/w32_regex_traits.o gcc/regex++/wide_posix_api.o

########################################################
#
# section for libregex++debug.a
#
########################################################
gcc/regex++debug/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/c_regex_traits.o $(C2) $(XCFLAGS) ../src/c_regex_traits.cpp

gcc/regex++debug/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/c_regex_traits_common.o $(C2) $(XCFLAGS) ../src/c_regex_traits_common.cpp

gcc/regex++debug/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/cpp_regex_traits.o $(C2) $(XCFLAGS) ../src/cpp_regex_traits.cpp

gcc/regex++debug/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/cregex.o $(C2) $(XCFLAGS) ../src/cregex.cpp

gcc/regex++debug/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/fileiter.o $(C2) $(XCFLAGS) ../src/fileiter.cpp

gcc/regex++debug/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/posix_api.o $(C2) $(XCFLAGS) ../src/posix_api.cpp

gcc/regex++debug/regex.o: ../src/regex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex.o $(C2) $(XCFLAGS) ../src/regex.cpp

gcc/regex++debug/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex_debug.o $(C2) $(XCFLAGS) ../src/regex_debug.cpp

gcc/regex++debug/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex_synch.o $(C2) $(XCFLAGS) ../src/regex_synch.cpp

gcc/regex++debug/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/w32_regex_traits.o $(C2) $(XCFLAGS) ../src/w32_regex_traits.cpp

gcc/regex++debug/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/wide_posix_api.o $(C2) $(XCFLAGS) ../src/wide_posix_api.cpp

gcc/regex++debug : 
	mkdir -p gcc/regex++debug

regex++debug_clean :
	rm -f gcc/regex++debug/*.o

./gcc/libregex++debug.so : gcc/regex++debug/c_regex_traits.o gcc/regex++debug/c_regex_traits_common.o gcc/regex++debug/cpp_regex_traits.o gcc/regex++debug/cregex.o gcc/regex++debug/fileiter.o gcc/regex++debug/posix_api.o gcc/regex++debug/regex.o gcc/regex++debug/regex_debug.o gcc/regex++debug/regex_synch.o gcc/regex++debug/w32_regex_traits.o gcc/regex++debug/wide_posix_api.o
	$(LINKER) $(LINK) -o gcc/libregex++debug.so  gcc/regex++debug/c_regex_traits.o gcc/regex++debug/c_regex_traits_common.o gcc/regex++debug/cpp_regex_traits.o gcc/regex++debug/cregex.o gcc/regex++debug/fileiter.o gcc/regex++debug/posix_api.o gcc/regex++debug/regex.o gcc/regex++debug/regex_debug.o gcc/regex++debug/regex_synch.o gcc/regex++debug/w32_regex_traits.o gcc/regex++debug/wide_posix_api.o

