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
# Add additional compiler options here:
#
XCFLAGS=
#
# add additional linker flags here:
#
XLFLAGS=
#
# add additional static-library creation flags here:
#
XSFLAGS=



ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/jm_opt.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : gcc  gcc gcc/regex++ ./gcc/libregex++.a gcc gcc/regex++debug ./gcc/libregex++debug.a

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
	g++ -o gcc/regex++/c_regex_traits.o -c -O2 -I../../../ $(XCFLAGS) ../src/c_regex_traits.cpp

gcc/regex++/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/c_regex_traits_common.o -c -O2 -I../../../ $(XCFLAGS) ../src/c_regex_traits_common.cpp

gcc/regex++/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/cpp_regex_traits.o -c -O2 -I../../../ $(XCFLAGS) ../src/cpp_regex_traits.cpp

gcc/regex++/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/cregex.o -c -O2 -I../../../ $(XCFLAGS) ../src/cregex.cpp

gcc/regex++/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/fileiter.o -c -O2 -I../../../ $(XCFLAGS) ../src/fileiter.cpp

gcc/regex++/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/posix_api.o -c -O2 -I../../../ $(XCFLAGS) ../src/posix_api.cpp

gcc/regex++/regex.o: ../src/regex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex.o -c -O2 -I../../../ $(XCFLAGS) ../src/regex.cpp

gcc/regex++/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex_debug.o -c -O2 -I../../../ $(XCFLAGS) ../src/regex_debug.cpp

gcc/regex++/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/regex_synch.o -c -O2 -I../../../ $(XCFLAGS) ../src/regex_synch.cpp

gcc/regex++/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/w32_regex_traits.o -c -O2 -I../../../ $(XCFLAGS) ../src/w32_regex_traits.cpp

gcc/regex++/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++/wide_posix_api.o -c -O2 -I../../../ $(XCFLAGS) ../src/wide_posix_api.cpp

gcc/regex++ : 
	mkdir -p gcc/regex++

regex++_clean :
	rm -f gcc/regex++/*.o

./gcc/libregex++.a : gcc/regex++/c_regex_traits.o gcc/regex++/c_regex_traits_common.o gcc/regex++/cpp_regex_traits.o gcc/regex++/cregex.o gcc/regex++/fileiter.o gcc/regex++/posix_api.o gcc/regex++/regex.o gcc/regex++/regex_debug.o gcc/regex++/regex_synch.o gcc/regex++/w32_regex_traits.o gcc/regex++/wide_posix_api.o
	ar -r $(XSFLAGS) gcc/libregex++.a  gcc/regex++/c_regex_traits.o gcc/regex++/c_regex_traits_common.o gcc/regex++/cpp_regex_traits.o gcc/regex++/cregex.o gcc/regex++/fileiter.o gcc/regex++/posix_api.o gcc/regex++/regex.o gcc/regex++/regex_debug.o gcc/regex++/regex_synch.o gcc/regex++/w32_regex_traits.o gcc/regex++/wide_posix_api.o

########################################################
#
# section for libregex++debug.a
#
########################################################
gcc/regex++debug/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/c_regex_traits.o -c -I../../../ -g $(XCFLAGS) ../src/c_regex_traits.cpp

gcc/regex++debug/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/c_regex_traits_common.o -c -I../../../ -g $(XCFLAGS) ../src/c_regex_traits_common.cpp

gcc/regex++debug/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/cpp_regex_traits.o -c -I../../../ -g $(XCFLAGS) ../src/cpp_regex_traits.cpp

gcc/regex++debug/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/cregex.o -c -I../../../ -g $(XCFLAGS) ../src/cregex.cpp

gcc/regex++debug/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/fileiter.o -c -I../../../ -g $(XCFLAGS) ../src/fileiter.cpp

gcc/regex++debug/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/posix_api.o -c -I../../../ -g $(XCFLAGS) ../src/posix_api.cpp

gcc/regex++debug/regex.o: ../src/regex.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex.o -c -I../../../ -g $(XCFLAGS) ../src/regex.cpp

gcc/regex++debug/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex_debug.o -c -I../../../ -g $(XCFLAGS) ../src/regex_debug.cpp

gcc/regex++debug/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/regex_synch.o -c -I../../../ -g $(XCFLAGS) ../src/regex_synch.cpp

gcc/regex++debug/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/w32_regex_traits.o -c -I../../../ -g $(XCFLAGS) ../src/w32_regex_traits.cpp

gcc/regex++debug/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	g++ -o gcc/regex++debug/wide_posix_api.o -c -I../../../ -g $(XCFLAGS) ../src/wide_posix_api.cpp

gcc/regex++debug : 
	mkdir -p gcc/regex++debug

regex++debug_clean :
	rm -f gcc/regex++debug/*.o

./gcc/libregex++debug.a : gcc/regex++debug/c_regex_traits.o gcc/regex++debug/c_regex_traits_common.o gcc/regex++debug/cpp_regex_traits.o gcc/regex++debug/cregex.o gcc/regex++debug/fileiter.o gcc/regex++debug/posix_api.o gcc/regex++debug/regex.o gcc/regex++debug/regex_debug.o gcc/regex++debug/regex_synch.o gcc/regex++debug/w32_regex_traits.o gcc/regex++debug/wide_posix_api.o
	ar -r $(XSFLAGS) gcc/libregex++debug.a  gcc/regex++debug/c_regex_traits.o gcc/regex++debug/c_regex_traits_common.o gcc/regex++debug/cpp_regex_traits.o gcc/regex++debug/cregex.o gcc/regex++debug/fileiter.o gcc/regex++debug/posix_api.o gcc/regex++debug/regex.o gcc/regex++debug/regex_debug.o gcc/regex++debug/regex_synch.o gcc/regex++debug/w32_regex_traits.o gcc/regex++debug/wide_posix_api.o

