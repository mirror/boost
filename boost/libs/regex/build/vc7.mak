#
# auto generated makefile for VC6 compiler
#
# usage:
# make
#   brings libraries up to date
# make install
#   brings libraries up to date and copies binaries to your VC6 /lib and /bin directories (recomended)
#

#
# Add additional compiler options here:
#
CXXFLAGS=
#
# Add additional include directories here:
#
INCLUDES=
#
# add additional linker flags here:
#
XLFLAGS=
#
# add additional static-library creation flags here:
#
XSFLAGS=

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF "$(MSVCDIR)" == ""
!ERROR Variable MSVCDIR not set.
!ENDIF


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp ../../../boost/regex/v4/basic_regex.hpp ../../../boost/regex/v4/char_regex_traits.hpp ../../../boost/regex/v4/cregex.hpp ../../../boost/regex/v4/fileiter.hpp ../../../boost/regex/v4/instances.hpp ../../../boost/regex/v4/iterator_category.hpp ../../../boost/regex/v4/iterator_traits.hpp ../../../boost/regex/v4/match_flags.hpp ../../../boost/regex/v4/match_results.hpp ../../../boost/regex/v4/mem_block_cache.hpp ../../../boost/regex/v4/perl_matcher.hpp ../../../boost/regex/v4/perl_matcher_common.hpp ../../../boost/regex/v4/perl_matcher_non_recursive.hpp ../../../boost/regex/v4/perl_matcher_recursive.hpp ../../../boost/regex/v4/regbase.hpp ../../../boost/regex/v4/regex.hpp ../../../boost/regex/v4/regex_compile.hpp ../../../boost/regex/v4/regex_cstring.hpp ../../../boost/regex/v4/regex_format.hpp ../../../boost/regex/v4/regex_fwd.hpp ../../../boost/regex/v4/regex_grep.hpp ../../../boost/regex/v4/regex_iterator.hpp ../../../boost/regex/v4/regex_kmp.hpp ../../../boost/regex/v4/regex_match.hpp ../../../boost/regex/v4/regex_merge.hpp ../../../boost/regex/v4/regex_raw_buffer.hpp ../../../boost/regex/v4/regex_replace.hpp ../../../boost/regex/v4/regex_search.hpp ../../../boost/regex/v4/regex_split.hpp ../../../boost/regex/v4/regex_stack.hpp ../../../boost/regex/v4/regex_synch.hpp ../../../boost/regex/v4/regex_token_iterator.hpp ../../../boost/regex/v4/regex_traits.hpp ../../../boost/regex/v4/states.hpp ../../../boost/regex/v4/sub_match.hpp ../../../boost/regex/config/borland.hpp ../../../boost/regex/config/cstring.hpp ../../../boost/regex/config/cwchar.hpp ../../../boost/regex/config/regex_library_include.hpp

all : main_dir libboost_regex_vc7_ss_dir ./vc7/libboost_regex_vc7_ss.lib libboost_regex_vc7_ms_dir ./vc7/libboost_regex_vc7_ms.lib libboost_regex_vc7_ssd_dir ./vc7/libboost_regex_vc7_ssd.lib libboost_regex_vc7_msd_dir ./vc7/libboost_regex_vc7_msd.lib boost_regex_vc7_mdd_dir ./vc7/boost_regex_vc7_mdd.lib boost_regex_vc7_md_dir ./vc7/boost_regex_vc7_md.lib libboost_regex_vc7_md_dir ./vc7/libboost_regex_vc7_md.lib libboost_regex_vc7_mdd_dir ./vc7/libboost_regex_vc7_mdd.lib

clean :  libboost_regex_vc7_ss_clean libboost_regex_vc7_ms_clean libboost_regex_vc7_ssd_clean libboost_regex_vc7_msd_clean boost_regex_vc7_mdd_clean boost_regex_vc7_md_clean libboost_regex_vc7_md_clean libboost_regex_vc7_mdd_clean

install : all
	copy vc7\libboost_regex_vc7_ss.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_ms.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_ssd.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_ssd.pdb "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_msd.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_msd.pdb "$(MSVCDIR)\lib"
	copy vc7\boost_regex_vc7_mdd.lib "$(MSVCDIR)\lib"
	copy vc7\boost_regex_vc7_mdd.dll "$(MSVCDIR)\bin"
	copy vc7\boost_regex_vc7_mdd.pdb "$(MSVCDIR)\lib"
	copy vc7\boost_regex_vc7_md.lib "$(MSVCDIR)\lib"
	copy vc7\boost_regex_vc7_md.dll "$(MSVCDIR)\bin"
	copy vc7\libboost_regex_vc7_md.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_mdd.lib "$(MSVCDIR)\lib"
	copy vc7\libboost_regex_vc7_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc7\$(NULL)" mkdir vc7


########################################################
#
# section for libboost_regex_vc7_ss.lib
#
########################################################
vc7/libboost_regex_vc7_ss/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_ss/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_ss/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_ss/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_ss/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_ss/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_ss/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_ss/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_ss/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_ss/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_ss/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_ss/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_ss/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ss/ -Fdvc7/libboost_regex_vc7_ss.pdb ../src/winstances.cpp

libboost_regex_vc7_ss_dir :
	@if not exist "vc7\libboost_regex_vc7_ss\$(NULL)" mkdir vc7\libboost_regex_vc7_ss

libboost_regex_vc7_ss_clean :
	del vc7\libboost_regex_vc7_ss\*.obj
	del vc7\libboost_regex_vc7_ss\*.idb
	del vc7\libboost_regex_vc7_ss\*.exp
	del vc7\libboost_regex_vc7_ss\*.pch

./vc7/libboost_regex_vc7_ss.lib : vc7/libboost_regex_vc7_ss/c_regex_traits.obj vc7/libboost_regex_vc7_ss/c_regex_traits_common.obj vc7/libboost_regex_vc7_ss/cpp_regex_traits.obj vc7/libboost_regex_vc7_ss/cregex.obj vc7/libboost_regex_vc7_ss/fileiter.obj vc7/libboost_regex_vc7_ss/instances.obj vc7/libboost_regex_vc7_ss/posix_api.obj vc7/libboost_regex_vc7_ss/regex.obj vc7/libboost_regex_vc7_ss/regex_debug.obj vc7/libboost_regex_vc7_ss/regex_synch.obj vc7/libboost_regex_vc7_ss/w32_regex_traits.obj vc7/libboost_regex_vc7_ss/wide_posix_api.obj vc7/libboost_regex_vc7_ss/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_ss.lib $(XSFLAGS)  vc7/libboost_regex_vc7_ss/c_regex_traits.obj vc7/libboost_regex_vc7_ss/c_regex_traits_common.obj vc7/libboost_regex_vc7_ss/cpp_regex_traits.obj vc7/libboost_regex_vc7_ss/cregex.obj vc7/libboost_regex_vc7_ss/fileiter.obj vc7/libboost_regex_vc7_ss/instances.obj vc7/libboost_regex_vc7_ss/posix_api.obj vc7/libboost_regex_vc7_ss/regex.obj vc7/libboost_regex_vc7_ss/regex_debug.obj vc7/libboost_regex_vc7_ss/regex_synch.obj vc7/libboost_regex_vc7_ss/w32_regex_traits.obj vc7/libboost_regex_vc7_ss/wide_posix_api.obj vc7/libboost_regex_vc7_ss/winstances.obj

########################################################
#
# section for libboost_regex_vc7_ms.lib
#
########################################################
vc7/libboost_regex_vc7_ms/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_ms/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_ms/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_ms/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_ms/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_ms/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_ms/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_ms/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_ms/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_ms/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_ms/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_ms/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_ms/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ms/ -Fdvc7/libboost_regex_vc7_ms.pdb ../src/winstances.cpp

libboost_regex_vc7_ms_dir :
	@if not exist "vc7\libboost_regex_vc7_ms\$(NULL)" mkdir vc7\libboost_regex_vc7_ms

libboost_regex_vc7_ms_clean :
	del vc7\libboost_regex_vc7_ms\*.obj
	del vc7\libboost_regex_vc7_ms\*.idb
	del vc7\libboost_regex_vc7_ms\*.exp
	del vc7\libboost_regex_vc7_ms\*.pch

./vc7/libboost_regex_vc7_ms.lib : vc7/libboost_regex_vc7_ms/c_regex_traits.obj vc7/libboost_regex_vc7_ms/c_regex_traits_common.obj vc7/libboost_regex_vc7_ms/cpp_regex_traits.obj vc7/libboost_regex_vc7_ms/cregex.obj vc7/libboost_regex_vc7_ms/fileiter.obj vc7/libboost_regex_vc7_ms/instances.obj vc7/libboost_regex_vc7_ms/posix_api.obj vc7/libboost_regex_vc7_ms/regex.obj vc7/libboost_regex_vc7_ms/regex_debug.obj vc7/libboost_regex_vc7_ms/regex_synch.obj vc7/libboost_regex_vc7_ms/w32_regex_traits.obj vc7/libboost_regex_vc7_ms/wide_posix_api.obj vc7/libboost_regex_vc7_ms/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_ms.lib $(XSFLAGS)  vc7/libboost_regex_vc7_ms/c_regex_traits.obj vc7/libboost_regex_vc7_ms/c_regex_traits_common.obj vc7/libboost_regex_vc7_ms/cpp_regex_traits.obj vc7/libboost_regex_vc7_ms/cregex.obj vc7/libboost_regex_vc7_ms/fileiter.obj vc7/libboost_regex_vc7_ms/instances.obj vc7/libboost_regex_vc7_ms/posix_api.obj vc7/libboost_regex_vc7_ms/regex.obj vc7/libboost_regex_vc7_ms/regex_debug.obj vc7/libboost_regex_vc7_ms/regex_synch.obj vc7/libboost_regex_vc7_ms/w32_regex_traits.obj vc7/libboost_regex_vc7_ms/wide_posix_api.obj vc7/libboost_regex_vc7_ms/winstances.obj

########################################################
#
# section for libboost_regex_vc7_ssd.lib
#
########################################################
vc7/libboost_regex_vc7_ssd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_ssd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_ssd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_ssd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_ssd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_ssd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_ssd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_ssd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_ssd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_ssd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_ssd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_ssd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_ssd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_ssd/ -Fdvc7/libboost_regex_vc7_ssd.pdb ../src/winstances.cpp

libboost_regex_vc7_ssd_dir :
	@if not exist "vc7\libboost_regex_vc7_ssd\$(NULL)" mkdir vc7\libboost_regex_vc7_ssd

libboost_regex_vc7_ssd_clean :
	del vc7\libboost_regex_vc7_ssd\*.obj
	del vc7\libboost_regex_vc7_ssd\*.idb
	del vc7\libboost_regex_vc7_ssd\*.exp
	del vc7\libboost_regex_vc7_ssd\*.pch

./vc7/libboost_regex_vc7_ssd.lib : vc7/libboost_regex_vc7_ssd/c_regex_traits.obj vc7/libboost_regex_vc7_ssd/c_regex_traits_common.obj vc7/libboost_regex_vc7_ssd/cpp_regex_traits.obj vc7/libboost_regex_vc7_ssd/cregex.obj vc7/libboost_regex_vc7_ssd/fileiter.obj vc7/libboost_regex_vc7_ssd/instances.obj vc7/libboost_regex_vc7_ssd/posix_api.obj vc7/libboost_regex_vc7_ssd/regex.obj vc7/libboost_regex_vc7_ssd/regex_debug.obj vc7/libboost_regex_vc7_ssd/regex_synch.obj vc7/libboost_regex_vc7_ssd/w32_regex_traits.obj vc7/libboost_regex_vc7_ssd/wide_posix_api.obj vc7/libboost_regex_vc7_ssd/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_ssd.lib $(XSFLAGS)  vc7/libboost_regex_vc7_ssd/c_regex_traits.obj vc7/libboost_regex_vc7_ssd/c_regex_traits_common.obj vc7/libboost_regex_vc7_ssd/cpp_regex_traits.obj vc7/libboost_regex_vc7_ssd/cregex.obj vc7/libboost_regex_vc7_ssd/fileiter.obj vc7/libboost_regex_vc7_ssd/instances.obj vc7/libboost_regex_vc7_ssd/posix_api.obj vc7/libboost_regex_vc7_ssd/regex.obj vc7/libboost_regex_vc7_ssd/regex_debug.obj vc7/libboost_regex_vc7_ssd/regex_synch.obj vc7/libboost_regex_vc7_ssd/w32_regex_traits.obj vc7/libboost_regex_vc7_ssd/wide_posix_api.obj vc7/libboost_regex_vc7_ssd/winstances.obj

########################################################
#
# section for libboost_regex_vc7_msd.lib
#
########################################################
vc7/libboost_regex_vc7_msd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_msd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_msd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_msd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_msd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_msd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_msd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_msd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_msd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_msd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_msd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_msd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_msd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_msd/ -Fdvc7/libboost_regex_vc7_msd.pdb ../src/winstances.cpp

libboost_regex_vc7_msd_dir :
	@if not exist "vc7\libboost_regex_vc7_msd\$(NULL)" mkdir vc7\libboost_regex_vc7_msd

libboost_regex_vc7_msd_clean :
	del vc7\libboost_regex_vc7_msd\*.obj
	del vc7\libboost_regex_vc7_msd\*.idb
	del vc7\libboost_regex_vc7_msd\*.exp
	del vc7\libboost_regex_vc7_msd\*.pch

./vc7/libboost_regex_vc7_msd.lib : vc7/libboost_regex_vc7_msd/c_regex_traits.obj vc7/libboost_regex_vc7_msd/c_regex_traits_common.obj vc7/libboost_regex_vc7_msd/cpp_regex_traits.obj vc7/libboost_regex_vc7_msd/cregex.obj vc7/libboost_regex_vc7_msd/fileiter.obj vc7/libboost_regex_vc7_msd/instances.obj vc7/libboost_regex_vc7_msd/posix_api.obj vc7/libboost_regex_vc7_msd/regex.obj vc7/libboost_regex_vc7_msd/regex_debug.obj vc7/libboost_regex_vc7_msd/regex_synch.obj vc7/libboost_regex_vc7_msd/w32_regex_traits.obj vc7/libboost_regex_vc7_msd/wide_posix_api.obj vc7/libboost_regex_vc7_msd/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_msd.lib $(XSFLAGS)  vc7/libboost_regex_vc7_msd/c_regex_traits.obj vc7/libboost_regex_vc7_msd/c_regex_traits_common.obj vc7/libboost_regex_vc7_msd/cpp_regex_traits.obj vc7/libboost_regex_vc7_msd/cregex.obj vc7/libboost_regex_vc7_msd/fileiter.obj vc7/libboost_regex_vc7_msd/instances.obj vc7/libboost_regex_vc7_msd/posix_api.obj vc7/libboost_regex_vc7_msd/regex.obj vc7/libboost_regex_vc7_msd/regex_debug.obj vc7/libboost_regex_vc7_msd/regex_synch.obj vc7/libboost_regex_vc7_msd/w32_regex_traits.obj vc7/libboost_regex_vc7_msd/wide_posix_api.obj vc7/libboost_regex_vc7_msd/winstances.obj

########################################################
#
# section for boost_regex_vc7_mdd.lib
#
########################################################
vc7/boost_regex_vc7_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/c_regex_traits.cpp

vc7/boost_regex_vc7_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/c_regex_traits_common.cpp

vc7/boost_regex_vc7_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/cpp_regex_traits.cpp

vc7/boost_regex_vc7_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/cregex.cpp

vc7/boost_regex_vc7_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/fileiter.cpp

vc7/boost_regex_vc7_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/instances.cpp

vc7/boost_regex_vc7_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/posix_api.cpp

vc7/boost_regex_vc7_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/regex.cpp

vc7/boost_regex_vc7_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/regex_debug.cpp

vc7/boost_regex_vc7_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/regex_synch.cpp

vc7/boost_regex_vc7_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/w32_regex_traits.cpp

vc7/boost_regex_vc7_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/wide_posix_api.cpp

vc7/boost_regex_vc7_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_mdd/ -Fdvc7/boost_regex_vc7_mdd.pdb ../src/winstances.cpp

boost_regex_vc7_mdd_dir :
	@if not exist "vc7\boost_regex_vc7_mdd\$(NULL)" mkdir vc7\boost_regex_vc7_mdd

boost_regex_vc7_mdd_clean :
	del vc7\boost_regex_vc7_mdd\*.obj
	del vc7\boost_regex_vc7_mdd\*.idb
	del vc7\boost_regex_vc7_mdd\*.exp
	del vc7\boost_regex_vc7_mdd\*.pch

./vc7/boost_regex_vc7_mdd.lib : vc7/boost_regex_vc7_mdd/c_regex_traits.obj vc7/boost_regex_vc7_mdd/c_regex_traits_common.obj vc7/boost_regex_vc7_mdd/cpp_regex_traits.obj vc7/boost_regex_vc7_mdd/cregex.obj vc7/boost_regex_vc7_mdd/fileiter.obj vc7/boost_regex_vc7_mdd/instances.obj vc7/boost_regex_vc7_mdd/posix_api.obj vc7/boost_regex_vc7_mdd/regex.obj vc7/boost_regex_vc7_mdd/regex_debug.obj vc7/boost_regex_vc7_mdd/regex_synch.obj vc7/boost_regex_vc7_mdd/w32_regex_traits.obj vc7/boost_regex_vc7_mdd/wide_posix_api.obj vc7/boost_regex_vc7_mdd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/boost_regex_vc7_mdd.pdb" /debug /machine:I386 /out:"vc7/boost_regex_vc7_mdd.dll" /implib:"vc7/boost_regex_vc7_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/boost_regex_vc7_mdd/c_regex_traits.obj vc7/boost_regex_vc7_mdd/c_regex_traits_common.obj vc7/boost_regex_vc7_mdd/cpp_regex_traits.obj vc7/boost_regex_vc7_mdd/cregex.obj vc7/boost_regex_vc7_mdd/fileiter.obj vc7/boost_regex_vc7_mdd/instances.obj vc7/boost_regex_vc7_mdd/posix_api.obj vc7/boost_regex_vc7_mdd/regex.obj vc7/boost_regex_vc7_mdd/regex_debug.obj vc7/boost_regex_vc7_mdd/regex_synch.obj vc7/boost_regex_vc7_mdd/w32_regex_traits.obj vc7/boost_regex_vc7_mdd/wide_posix_api.obj vc7/boost_regex_vc7_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc7_md.lib
#
########################################################
vc7/boost_regex_vc7_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/c_regex_traits.cpp

vc7/boost_regex_vc7_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/c_regex_traits_common.cpp

vc7/boost_regex_vc7_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/cpp_regex_traits.cpp

vc7/boost_regex_vc7_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/cregex.cpp

vc7/boost_regex_vc7_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/fileiter.cpp

vc7/boost_regex_vc7_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/instances.cpp

vc7/boost_regex_vc7_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/posix_api.cpp

vc7/boost_regex_vc7_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/regex.cpp

vc7/boost_regex_vc7_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/regex_debug.cpp

vc7/boost_regex_vc7_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/regex_synch.cpp

vc7/boost_regex_vc7_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/w32_regex_traits.cpp

vc7/boost_regex_vc7_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/wide_posix_api.cpp

vc7/boost_regex_vc7_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/boost_regex_vc7_md/ -Fdvc7/boost_regex_vc7_md.pdb ../src/winstances.cpp

boost_regex_vc7_md_dir :
	@if not exist "vc7\boost_regex_vc7_md\$(NULL)" mkdir vc7\boost_regex_vc7_md

boost_regex_vc7_md_clean :
	del vc7\boost_regex_vc7_md\*.obj
	del vc7\boost_regex_vc7_md\*.idb
	del vc7\boost_regex_vc7_md\*.exp
	del vc7\boost_regex_vc7_md\*.pch

./vc7/boost_regex_vc7_md.lib : vc7/boost_regex_vc7_md/c_regex_traits.obj vc7/boost_regex_vc7_md/c_regex_traits_common.obj vc7/boost_regex_vc7_md/cpp_regex_traits.obj vc7/boost_regex_vc7_md/cregex.obj vc7/boost_regex_vc7_md/fileiter.obj vc7/boost_regex_vc7_md/instances.obj vc7/boost_regex_vc7_md/posix_api.obj vc7/boost_regex_vc7_md/regex.obj vc7/boost_regex_vc7_md/regex_debug.obj vc7/boost_regex_vc7_md/regex_synch.obj vc7/boost_regex_vc7_md/w32_regex_traits.obj vc7/boost_regex_vc7_md/wide_posix_api.obj vc7/boost_regex_vc7_md/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/boost_regex_vc7_md.pdb" /debug /machine:I386 /out:"vc7/boost_regex_vc7_md.dll" /implib:"vc7/boost_regex_vc7_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/boost_regex_vc7_md/c_regex_traits.obj vc7/boost_regex_vc7_md/c_regex_traits_common.obj vc7/boost_regex_vc7_md/cpp_regex_traits.obj vc7/boost_regex_vc7_md/cregex.obj vc7/boost_regex_vc7_md/fileiter.obj vc7/boost_regex_vc7_md/instances.obj vc7/boost_regex_vc7_md/posix_api.obj vc7/boost_regex_vc7_md/regex.obj vc7/boost_regex_vc7_md/regex_debug.obj vc7/boost_regex_vc7_md/regex_synch.obj vc7/boost_regex_vc7_md/w32_regex_traits.obj vc7/boost_regex_vc7_md/wide_posix_api.obj vc7/boost_regex_vc7_md/winstances.obj

########################################################
#
# section for libboost_regex_vc7_md.lib
#
########################################################
vc7/libboost_regex_vc7_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_md/ -Fdvc7/libboost_regex_vc7_md.pdb ../src/winstances.cpp

libboost_regex_vc7_md_dir :
	@if not exist "vc7\libboost_regex_vc7_md\$(NULL)" mkdir vc7\libboost_regex_vc7_md

libboost_regex_vc7_md_clean :
	del vc7\libboost_regex_vc7_md\*.obj
	del vc7\libboost_regex_vc7_md\*.idb
	del vc7\libboost_regex_vc7_md\*.exp
	del vc7\libboost_regex_vc7_md\*.pch

./vc7/libboost_regex_vc7_md.lib : vc7/libboost_regex_vc7_md/c_regex_traits.obj vc7/libboost_regex_vc7_md/c_regex_traits_common.obj vc7/libboost_regex_vc7_md/cpp_regex_traits.obj vc7/libboost_regex_vc7_md/cregex.obj vc7/libboost_regex_vc7_md/fileiter.obj vc7/libboost_regex_vc7_md/instances.obj vc7/libboost_regex_vc7_md/posix_api.obj vc7/libboost_regex_vc7_md/regex.obj vc7/libboost_regex_vc7_md/regex_debug.obj vc7/libboost_regex_vc7_md/regex_synch.obj vc7/libboost_regex_vc7_md/w32_regex_traits.obj vc7/libboost_regex_vc7_md/wide_posix_api.obj vc7/libboost_regex_vc7_md/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_md.lib $(XSFLAGS)  vc7/libboost_regex_vc7_md/c_regex_traits.obj vc7/libboost_regex_vc7_md/c_regex_traits_common.obj vc7/libboost_regex_vc7_md/cpp_regex_traits.obj vc7/libboost_regex_vc7_md/cregex.obj vc7/libboost_regex_vc7_md/fileiter.obj vc7/libboost_regex_vc7_md/instances.obj vc7/libboost_regex_vc7_md/posix_api.obj vc7/libboost_regex_vc7_md/regex.obj vc7/libboost_regex_vc7_md/regex_debug.obj vc7/libboost_regex_vc7_md/regex_synch.obj vc7/libboost_regex_vc7_md/w32_regex_traits.obj vc7/libboost_regex_vc7_md/wide_posix_api.obj vc7/libboost_regex_vc7_md/winstances.obj

########################################################
#
# section for libboost_regex_vc7_mdd.lib
#
########################################################
vc7/libboost_regex_vc7_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/c_regex_traits.cpp

vc7/libboost_regex_vc7_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/c_regex_traits_common.cpp

vc7/libboost_regex_vc7_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/cpp_regex_traits.cpp

vc7/libboost_regex_vc7_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/cregex.cpp

vc7/libboost_regex_vc7_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/fileiter.cpp

vc7/libboost_regex_vc7_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/instances.cpp

vc7/libboost_regex_vc7_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/posix_api.cpp

vc7/libboost_regex_vc7_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/regex.cpp

vc7/libboost_regex_vc7_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/regex_debug.cpp

vc7/libboost_regex_vc7_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/regex_synch.cpp

vc7/libboost_regex_vc7_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/w32_regex_traits.cpp

vc7/libboost_regex_vc7_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/wide_posix_api.cpp

vc7/libboost_regex_vc7_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc7/libboost_regex_vc7_mdd/ -Fdvc7/libboost_regex_vc7_mdd.pdb ../src/winstances.cpp

libboost_regex_vc7_mdd_dir :
	@if not exist "vc7\libboost_regex_vc7_mdd\$(NULL)" mkdir vc7\libboost_regex_vc7_mdd

libboost_regex_vc7_mdd_clean :
	del vc7\libboost_regex_vc7_mdd\*.obj
	del vc7\libboost_regex_vc7_mdd\*.idb
	del vc7\libboost_regex_vc7_mdd\*.exp
	del vc7\libboost_regex_vc7_mdd\*.pch

./vc7/libboost_regex_vc7_mdd.lib : vc7/libboost_regex_vc7_mdd/c_regex_traits.obj vc7/libboost_regex_vc7_mdd/c_regex_traits_common.obj vc7/libboost_regex_vc7_mdd/cpp_regex_traits.obj vc7/libboost_regex_vc7_mdd/cregex.obj vc7/libboost_regex_vc7_mdd/fileiter.obj vc7/libboost_regex_vc7_mdd/instances.obj vc7/libboost_regex_vc7_mdd/posix_api.obj vc7/libboost_regex_vc7_mdd/regex.obj vc7/libboost_regex_vc7_mdd/regex_debug.obj vc7/libboost_regex_vc7_mdd/regex_synch.obj vc7/libboost_regex_vc7_mdd/w32_regex_traits.obj vc7/libboost_regex_vc7_mdd/wide_posix_api.obj vc7/libboost_regex_vc7_mdd/winstances.obj
	link -lib /nologo /out:vc7/libboost_regex_vc7_mdd.lib $(XSFLAGS)  vc7/libboost_regex_vc7_mdd/c_regex_traits.obj vc7/libboost_regex_vc7_mdd/c_regex_traits_common.obj vc7/libboost_regex_vc7_mdd/cpp_regex_traits.obj vc7/libboost_regex_vc7_mdd/cregex.obj vc7/libboost_regex_vc7_mdd/fileiter.obj vc7/libboost_regex_vc7_mdd/instances.obj vc7/libboost_regex_vc7_mdd/posix_api.obj vc7/libboost_regex_vc7_mdd/regex.obj vc7/libboost_regex_vc7_mdd/regex_debug.obj vc7/libboost_regex_vc7_mdd/regex_synch.obj vc7/libboost_regex_vc7_mdd/w32_regex_traits.obj vc7/libboost_regex_vc7_mdd/wide_posix_api.obj vc7/libboost_regex_vc7_mdd/winstances.obj

