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

all : main_dir libboost_regex_vc6_ss_dir ./vc6/libboost_regex_vc6_ss.lib libboost_regex_vc6_ms_dir ./vc6/libboost_regex_vc6_ms.lib libboost_regex_vc6_ssd_dir ./vc6/libboost_regex_vc6_ssd.lib libboost_regex_vc6_msd_dir ./vc6/libboost_regex_vc6_msd.lib boost_regex_vc6_mdd_dir ./vc6/boost_regex_vc6_mdd.lib boost_regex_vc6_md_dir ./vc6/boost_regex_vc6_md.lib libboost_regex_vc6_md_dir ./vc6/libboost_regex_vc6_md.lib libboost_regex_vc6_mdd_dir ./vc6/libboost_regex_vc6_mdd.lib

clean :  libboost_regex_vc6_ss_clean libboost_regex_vc6_ms_clean libboost_regex_vc6_ssd_clean libboost_regex_vc6_msd_clean boost_regex_vc6_mdd_clean boost_regex_vc6_md_clean libboost_regex_vc6_md_clean libboost_regex_vc6_mdd_clean

install : all
	copy vc6\libboost_regex_vc6_ss.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_ms.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_ssd.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_ssd.pdb "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_msd.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_msd.pdb "$(MSVCDIR)\lib"
	copy vc6\boost_regex_vc6_mdd.lib "$(MSVCDIR)\lib"
	copy vc6\boost_regex_vc6_mdd.dll "$(MSVCDIR)\bin"
	copy vc6\boost_regex_vc6_mdd.pdb "$(MSVCDIR)\lib"
	copy vc6\boost_regex_vc6_md.lib "$(MSVCDIR)\lib"
	copy vc6\boost_regex_vc6_md.dll "$(MSVCDIR)\bin"
	copy vc6\libboost_regex_vc6_md.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_mdd.lib "$(MSVCDIR)\lib"
	copy vc6\libboost_regex_vc6_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc6\$(NULL)" mkdir vc6


########################################################
#
# section for libboost_regex_vc6_ss.lib
#
########################################################
vc6/libboost_regex_vc6_ss/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_ss/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_ss/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_ss/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_ss/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_ss/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_ss/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_ss/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_ss/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_ss/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_ss/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_ss/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_ss/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ss/ -Fdvc6/libboost_regex_vc6_ss.pdb ../src/winstances.cpp

libboost_regex_vc6_ss_dir :
	@if not exist "vc6\libboost_regex_vc6_ss\$(NULL)" mkdir vc6\libboost_regex_vc6_ss

libboost_regex_vc6_ss_clean :
	del vc6\libboost_regex_vc6_ss\*.obj
	del vc6\libboost_regex_vc6_ss\*.idb
	del vc6\libboost_regex_vc6_ss\*.exp
	del vc6\libboost_regex_vc6_ss\*.pch

./vc6/libboost_regex_vc6_ss.lib : vc6/libboost_regex_vc6_ss/c_regex_traits.obj vc6/libboost_regex_vc6_ss/c_regex_traits_common.obj vc6/libboost_regex_vc6_ss/cpp_regex_traits.obj vc6/libboost_regex_vc6_ss/cregex.obj vc6/libboost_regex_vc6_ss/fileiter.obj vc6/libboost_regex_vc6_ss/instances.obj vc6/libboost_regex_vc6_ss/posix_api.obj vc6/libboost_regex_vc6_ss/regex.obj vc6/libboost_regex_vc6_ss/regex_debug.obj vc6/libboost_regex_vc6_ss/regex_synch.obj vc6/libboost_regex_vc6_ss/w32_regex_traits.obj vc6/libboost_regex_vc6_ss/wide_posix_api.obj vc6/libboost_regex_vc6_ss/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_ss.lib $(XSFLAGS)  vc6/libboost_regex_vc6_ss/c_regex_traits.obj vc6/libboost_regex_vc6_ss/c_regex_traits_common.obj vc6/libboost_regex_vc6_ss/cpp_regex_traits.obj vc6/libboost_regex_vc6_ss/cregex.obj vc6/libboost_regex_vc6_ss/fileiter.obj vc6/libboost_regex_vc6_ss/instances.obj vc6/libboost_regex_vc6_ss/posix_api.obj vc6/libboost_regex_vc6_ss/regex.obj vc6/libboost_regex_vc6_ss/regex_debug.obj vc6/libboost_regex_vc6_ss/regex_synch.obj vc6/libboost_regex_vc6_ss/w32_regex_traits.obj vc6/libboost_regex_vc6_ss/wide_posix_api.obj vc6/libboost_regex_vc6_ss/winstances.obj

########################################################
#
# section for libboost_regex_vc6_ms.lib
#
########################################################
vc6/libboost_regex_vc6_ms/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_ms/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_ms/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_ms/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_ms/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_ms/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_ms/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_ms/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_ms/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_ms/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_ms/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_ms/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_ms/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ms/ -Fdvc6/libboost_regex_vc6_ms.pdb ../src/winstances.cpp

libboost_regex_vc6_ms_dir :
	@if not exist "vc6\libboost_regex_vc6_ms\$(NULL)" mkdir vc6\libboost_regex_vc6_ms

libboost_regex_vc6_ms_clean :
	del vc6\libboost_regex_vc6_ms\*.obj
	del vc6\libboost_regex_vc6_ms\*.idb
	del vc6\libboost_regex_vc6_ms\*.exp
	del vc6\libboost_regex_vc6_ms\*.pch

./vc6/libboost_regex_vc6_ms.lib : vc6/libboost_regex_vc6_ms/c_regex_traits.obj vc6/libboost_regex_vc6_ms/c_regex_traits_common.obj vc6/libboost_regex_vc6_ms/cpp_regex_traits.obj vc6/libboost_regex_vc6_ms/cregex.obj vc6/libboost_regex_vc6_ms/fileiter.obj vc6/libboost_regex_vc6_ms/instances.obj vc6/libboost_regex_vc6_ms/posix_api.obj vc6/libboost_regex_vc6_ms/regex.obj vc6/libboost_regex_vc6_ms/regex_debug.obj vc6/libboost_regex_vc6_ms/regex_synch.obj vc6/libboost_regex_vc6_ms/w32_regex_traits.obj vc6/libboost_regex_vc6_ms/wide_posix_api.obj vc6/libboost_regex_vc6_ms/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_ms.lib $(XSFLAGS)  vc6/libboost_regex_vc6_ms/c_regex_traits.obj vc6/libboost_regex_vc6_ms/c_regex_traits_common.obj vc6/libboost_regex_vc6_ms/cpp_regex_traits.obj vc6/libboost_regex_vc6_ms/cregex.obj vc6/libboost_regex_vc6_ms/fileiter.obj vc6/libboost_regex_vc6_ms/instances.obj vc6/libboost_regex_vc6_ms/posix_api.obj vc6/libboost_regex_vc6_ms/regex.obj vc6/libboost_regex_vc6_ms/regex_debug.obj vc6/libboost_regex_vc6_ms/regex_synch.obj vc6/libboost_regex_vc6_ms/w32_regex_traits.obj vc6/libboost_regex_vc6_ms/wide_posix_api.obj vc6/libboost_regex_vc6_ms/winstances.obj

########################################################
#
# section for libboost_regex_vc6_ssd.lib
#
########################################################
vc6/libboost_regex_vc6_ssd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_ssd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_ssd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_ssd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_ssd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_ssd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_ssd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_ssd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_ssd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_ssd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_ssd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_ssd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_ssd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /c  $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_ssd/ -Fdvc6/libboost_regex_vc6_ssd.pdb ../src/winstances.cpp

libboost_regex_vc6_ssd_dir :
	@if not exist "vc6\libboost_regex_vc6_ssd\$(NULL)" mkdir vc6\libboost_regex_vc6_ssd

libboost_regex_vc6_ssd_clean :
	del vc6\libboost_regex_vc6_ssd\*.obj
	del vc6\libboost_regex_vc6_ssd\*.idb
	del vc6\libboost_regex_vc6_ssd\*.exp
	del vc6\libboost_regex_vc6_ssd\*.pch

./vc6/libboost_regex_vc6_ssd.lib : vc6/libboost_regex_vc6_ssd/c_regex_traits.obj vc6/libboost_regex_vc6_ssd/c_regex_traits_common.obj vc6/libboost_regex_vc6_ssd/cpp_regex_traits.obj vc6/libboost_regex_vc6_ssd/cregex.obj vc6/libboost_regex_vc6_ssd/fileiter.obj vc6/libboost_regex_vc6_ssd/instances.obj vc6/libboost_regex_vc6_ssd/posix_api.obj vc6/libboost_regex_vc6_ssd/regex.obj vc6/libboost_regex_vc6_ssd/regex_debug.obj vc6/libboost_regex_vc6_ssd/regex_synch.obj vc6/libboost_regex_vc6_ssd/w32_regex_traits.obj vc6/libboost_regex_vc6_ssd/wide_posix_api.obj vc6/libboost_regex_vc6_ssd/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_ssd.lib $(XSFLAGS)  vc6/libboost_regex_vc6_ssd/c_regex_traits.obj vc6/libboost_regex_vc6_ssd/c_regex_traits_common.obj vc6/libboost_regex_vc6_ssd/cpp_regex_traits.obj vc6/libboost_regex_vc6_ssd/cregex.obj vc6/libboost_regex_vc6_ssd/fileiter.obj vc6/libboost_regex_vc6_ssd/instances.obj vc6/libboost_regex_vc6_ssd/posix_api.obj vc6/libboost_regex_vc6_ssd/regex.obj vc6/libboost_regex_vc6_ssd/regex_debug.obj vc6/libboost_regex_vc6_ssd/regex_synch.obj vc6/libboost_regex_vc6_ssd/w32_regex_traits.obj vc6/libboost_regex_vc6_ssd/wide_posix_api.obj vc6/libboost_regex_vc6_ssd/winstances.obj

########################################################
#
# section for libboost_regex_vc6_msd.lib
#
########################################################
vc6/libboost_regex_vc6_msd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_msd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_msd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_msd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_msd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_msd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_msd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_msd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_msd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_msd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_msd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_msd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_msd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_msd/ -Fdvc6/libboost_regex_vc6_msd.pdb ../src/winstances.cpp

libboost_regex_vc6_msd_dir :
	@if not exist "vc6\libboost_regex_vc6_msd\$(NULL)" mkdir vc6\libboost_regex_vc6_msd

libboost_regex_vc6_msd_clean :
	del vc6\libboost_regex_vc6_msd\*.obj
	del vc6\libboost_regex_vc6_msd\*.idb
	del vc6\libboost_regex_vc6_msd\*.exp
	del vc6\libboost_regex_vc6_msd\*.pch

./vc6/libboost_regex_vc6_msd.lib : vc6/libboost_regex_vc6_msd/c_regex_traits.obj vc6/libboost_regex_vc6_msd/c_regex_traits_common.obj vc6/libboost_regex_vc6_msd/cpp_regex_traits.obj vc6/libboost_regex_vc6_msd/cregex.obj vc6/libboost_regex_vc6_msd/fileiter.obj vc6/libboost_regex_vc6_msd/instances.obj vc6/libboost_regex_vc6_msd/posix_api.obj vc6/libboost_regex_vc6_msd/regex.obj vc6/libboost_regex_vc6_msd/regex_debug.obj vc6/libboost_regex_vc6_msd/regex_synch.obj vc6/libboost_regex_vc6_msd/w32_regex_traits.obj vc6/libboost_regex_vc6_msd/wide_posix_api.obj vc6/libboost_regex_vc6_msd/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_msd.lib $(XSFLAGS)  vc6/libboost_regex_vc6_msd/c_regex_traits.obj vc6/libboost_regex_vc6_msd/c_regex_traits_common.obj vc6/libboost_regex_vc6_msd/cpp_regex_traits.obj vc6/libboost_regex_vc6_msd/cregex.obj vc6/libboost_regex_vc6_msd/fileiter.obj vc6/libboost_regex_vc6_msd/instances.obj vc6/libboost_regex_vc6_msd/posix_api.obj vc6/libboost_regex_vc6_msd/regex.obj vc6/libboost_regex_vc6_msd/regex_debug.obj vc6/libboost_regex_vc6_msd/regex_synch.obj vc6/libboost_regex_vc6_msd/w32_regex_traits.obj vc6/libboost_regex_vc6_msd/wide_posix_api.obj vc6/libboost_regex_vc6_msd/winstances.obj

########################################################
#
# section for boost_regex_vc6_mdd.lib
#
########################################################
vc6/boost_regex_vc6_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/c_regex_traits.cpp

vc6/boost_regex_vc6_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/c_regex_traits_common.cpp

vc6/boost_regex_vc6_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/cpp_regex_traits.cpp

vc6/boost_regex_vc6_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/cregex.cpp

vc6/boost_regex_vc6_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/fileiter.cpp

vc6/boost_regex_vc6_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/instances.cpp

vc6/boost_regex_vc6_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/posix_api.cpp

vc6/boost_regex_vc6_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/regex.cpp

vc6/boost_regex_vc6_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/regex_debug.cpp

vc6/boost_regex_vc6_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/regex_synch.cpp

vc6/boost_regex_vc6_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/w32_regex_traits.cpp

vc6/boost_regex_vc6_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/wide_posix_api.cpp

vc6/boost_regex_vc6_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_mdd/ -Fdvc6/boost_regex_vc6_mdd.pdb ../src/winstances.cpp

boost_regex_vc6_mdd_dir :
	@if not exist "vc6\boost_regex_vc6_mdd\$(NULL)" mkdir vc6\boost_regex_vc6_mdd

boost_regex_vc6_mdd_clean :
	del vc6\boost_regex_vc6_mdd\*.obj
	del vc6\boost_regex_vc6_mdd\*.idb
	del vc6\boost_regex_vc6_mdd\*.exp
	del vc6\boost_regex_vc6_mdd\*.pch

./vc6/boost_regex_vc6_mdd.lib : vc6/boost_regex_vc6_mdd/c_regex_traits.obj vc6/boost_regex_vc6_mdd/c_regex_traits_common.obj vc6/boost_regex_vc6_mdd/cpp_regex_traits.obj vc6/boost_regex_vc6_mdd/cregex.obj vc6/boost_regex_vc6_mdd/fileiter.obj vc6/boost_regex_vc6_mdd/instances.obj vc6/boost_regex_vc6_mdd/posix_api.obj vc6/boost_regex_vc6_mdd/regex.obj vc6/boost_regex_vc6_mdd/regex_debug.obj vc6/boost_regex_vc6_mdd/regex_synch.obj vc6/boost_regex_vc6_mdd/w32_regex_traits.obj vc6/boost_regex_vc6_mdd/wide_posix_api.obj vc6/boost_regex_vc6_mdd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/boost_regex_vc6_mdd.pdb" /debug /machine:I386 /out:"vc6/boost_regex_vc6_mdd.dll" /implib:"vc6/boost_regex_vc6_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6/boost_regex_vc6_mdd/c_regex_traits.obj vc6/boost_regex_vc6_mdd/c_regex_traits_common.obj vc6/boost_regex_vc6_mdd/cpp_regex_traits.obj vc6/boost_regex_vc6_mdd/cregex.obj vc6/boost_regex_vc6_mdd/fileiter.obj vc6/boost_regex_vc6_mdd/instances.obj vc6/boost_regex_vc6_mdd/posix_api.obj vc6/boost_regex_vc6_mdd/regex.obj vc6/boost_regex_vc6_mdd/regex_debug.obj vc6/boost_regex_vc6_mdd/regex_synch.obj vc6/boost_regex_vc6_mdd/w32_regex_traits.obj vc6/boost_regex_vc6_mdd/wide_posix_api.obj vc6/boost_regex_vc6_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc6_md.lib
#
########################################################
vc6/boost_regex_vc6_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/c_regex_traits.cpp

vc6/boost_regex_vc6_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/c_regex_traits_common.cpp

vc6/boost_regex_vc6_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/cpp_regex_traits.cpp

vc6/boost_regex_vc6_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/cregex.cpp

vc6/boost_regex_vc6_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/fileiter.cpp

vc6/boost_regex_vc6_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/instances.cpp

vc6/boost_regex_vc6_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/posix_api.cpp

vc6/boost_regex_vc6_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/regex.cpp

vc6/boost_regex_vc6_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/regex_debug.cpp

vc6/boost_regex_vc6_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/regex_synch.cpp

vc6/boost_regex_vc6_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/w32_regex_traits.cpp

vc6/boost_regex_vc6_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/wide_posix_api.cpp

vc6/boost_regex_vc6_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/boost_regex_vc6_md/ -Fdvc6/boost_regex_vc6_md.pdb ../src/winstances.cpp

boost_regex_vc6_md_dir :
	@if not exist "vc6\boost_regex_vc6_md\$(NULL)" mkdir vc6\boost_regex_vc6_md

boost_regex_vc6_md_clean :
	del vc6\boost_regex_vc6_md\*.obj
	del vc6\boost_regex_vc6_md\*.idb
	del vc6\boost_regex_vc6_md\*.exp
	del vc6\boost_regex_vc6_md\*.pch

./vc6/boost_regex_vc6_md.lib : vc6/boost_regex_vc6_md/c_regex_traits.obj vc6/boost_regex_vc6_md/c_regex_traits_common.obj vc6/boost_regex_vc6_md/cpp_regex_traits.obj vc6/boost_regex_vc6_md/cregex.obj vc6/boost_regex_vc6_md/fileiter.obj vc6/boost_regex_vc6_md/instances.obj vc6/boost_regex_vc6_md/posix_api.obj vc6/boost_regex_vc6_md/regex.obj vc6/boost_regex_vc6_md/regex_debug.obj vc6/boost_regex_vc6_md/regex_synch.obj vc6/boost_regex_vc6_md/w32_regex_traits.obj vc6/boost_regex_vc6_md/wide_posix_api.obj vc6/boost_regex_vc6_md/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/boost_regex_vc6_md.pdb" /debug /machine:I386 /out:"vc6/boost_regex_vc6_md.dll" /implib:"vc6/boost_regex_vc6_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6/boost_regex_vc6_md/c_regex_traits.obj vc6/boost_regex_vc6_md/c_regex_traits_common.obj vc6/boost_regex_vc6_md/cpp_regex_traits.obj vc6/boost_regex_vc6_md/cregex.obj vc6/boost_regex_vc6_md/fileiter.obj vc6/boost_regex_vc6_md/instances.obj vc6/boost_regex_vc6_md/posix_api.obj vc6/boost_regex_vc6_md/regex.obj vc6/boost_regex_vc6_md/regex_debug.obj vc6/boost_regex_vc6_md/regex_synch.obj vc6/boost_regex_vc6_md/w32_regex_traits.obj vc6/boost_regex_vc6_md/wide_posix_api.obj vc6/boost_regex_vc6_md/winstances.obj

########################################################
#
# section for libboost_regex_vc6_md.lib
#
########################################################
vc6/libboost_regex_vc6_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_md/ -Fdvc6/libboost_regex_vc6_md.pdb ../src/winstances.cpp

libboost_regex_vc6_md_dir :
	@if not exist "vc6\libboost_regex_vc6_md\$(NULL)" mkdir vc6\libboost_regex_vc6_md

libboost_regex_vc6_md_clean :
	del vc6\libboost_regex_vc6_md\*.obj
	del vc6\libboost_regex_vc6_md\*.idb
	del vc6\libboost_regex_vc6_md\*.exp
	del vc6\libboost_regex_vc6_md\*.pch

./vc6/libboost_regex_vc6_md.lib : vc6/libboost_regex_vc6_md/c_regex_traits.obj vc6/libboost_regex_vc6_md/c_regex_traits_common.obj vc6/libboost_regex_vc6_md/cpp_regex_traits.obj vc6/libboost_regex_vc6_md/cregex.obj vc6/libboost_regex_vc6_md/fileiter.obj vc6/libboost_regex_vc6_md/instances.obj vc6/libboost_regex_vc6_md/posix_api.obj vc6/libboost_regex_vc6_md/regex.obj vc6/libboost_regex_vc6_md/regex_debug.obj vc6/libboost_regex_vc6_md/regex_synch.obj vc6/libboost_regex_vc6_md/w32_regex_traits.obj vc6/libboost_regex_vc6_md/wide_posix_api.obj vc6/libboost_regex_vc6_md/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_md.lib $(XSFLAGS)  vc6/libboost_regex_vc6_md/c_regex_traits.obj vc6/libboost_regex_vc6_md/c_regex_traits_common.obj vc6/libboost_regex_vc6_md/cpp_regex_traits.obj vc6/libboost_regex_vc6_md/cregex.obj vc6/libboost_regex_vc6_md/fileiter.obj vc6/libboost_regex_vc6_md/instances.obj vc6/libboost_regex_vc6_md/posix_api.obj vc6/libboost_regex_vc6_md/regex.obj vc6/libboost_regex_vc6_md/regex_debug.obj vc6/libboost_regex_vc6_md/regex_synch.obj vc6/libboost_regex_vc6_md/w32_regex_traits.obj vc6/libboost_regex_vc6_md/wide_posix_api.obj vc6/libboost_regex_vc6_md/winstances.obj

########################################################
#
# section for libboost_regex_vc6_mdd.lib
#
########################################################
vc6/libboost_regex_vc6_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/c_regex_traits.cpp

vc6/libboost_regex_vc6_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/c_regex_traits_common.cpp

vc6/libboost_regex_vc6_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/cpp_regex_traits.cpp

vc6/libboost_regex_vc6_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/cregex.cpp

vc6/libboost_regex_vc6_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/fileiter.cpp

vc6/libboost_regex_vc6_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/instances.cpp

vc6/libboost_regex_vc6_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/posix_api.cpp

vc6/libboost_regex_vc6_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/regex.cpp

vc6/libboost_regex_vc6_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/regex_debug.cpp

vc6/libboost_regex_vc6_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/regex_synch.cpp

vc6/libboost_regex_vc6_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/w32_regex_traits.cpp

vc6/libboost_regex_vc6_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/wide_posix_api.cpp

vc6/libboost_regex_vc6_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /c $(CXXFLAGS) -Y- -Fo./vc6/libboost_regex_vc6_mdd/ -Fdvc6/libboost_regex_vc6_mdd.pdb ../src/winstances.cpp

libboost_regex_vc6_mdd_dir :
	@if not exist "vc6\libboost_regex_vc6_mdd\$(NULL)" mkdir vc6\libboost_regex_vc6_mdd

libboost_regex_vc6_mdd_clean :
	del vc6\libboost_regex_vc6_mdd\*.obj
	del vc6\libboost_regex_vc6_mdd\*.idb
	del vc6\libboost_regex_vc6_mdd\*.exp
	del vc6\libboost_regex_vc6_mdd\*.pch

./vc6/libboost_regex_vc6_mdd.lib : vc6/libboost_regex_vc6_mdd/c_regex_traits.obj vc6/libboost_regex_vc6_mdd/c_regex_traits_common.obj vc6/libboost_regex_vc6_mdd/cpp_regex_traits.obj vc6/libboost_regex_vc6_mdd/cregex.obj vc6/libboost_regex_vc6_mdd/fileiter.obj vc6/libboost_regex_vc6_mdd/instances.obj vc6/libboost_regex_vc6_mdd/posix_api.obj vc6/libboost_regex_vc6_mdd/regex.obj vc6/libboost_regex_vc6_mdd/regex_debug.obj vc6/libboost_regex_vc6_mdd/regex_synch.obj vc6/libboost_regex_vc6_mdd/w32_regex_traits.obj vc6/libboost_regex_vc6_mdd/wide_posix_api.obj vc6/libboost_regex_vc6_mdd/winstances.obj
	link -lib /nologo /out:vc6/libboost_regex_vc6_mdd.lib $(XSFLAGS)  vc6/libboost_regex_vc6_mdd/c_regex_traits.obj vc6/libboost_regex_vc6_mdd/c_regex_traits_common.obj vc6/libboost_regex_vc6_mdd/cpp_regex_traits.obj vc6/libboost_regex_vc6_mdd/cregex.obj vc6/libboost_regex_vc6_mdd/fileiter.obj vc6/libboost_regex_vc6_mdd/instances.obj vc6/libboost_regex_vc6_mdd/posix_api.obj vc6/libboost_regex_vc6_mdd/regex.obj vc6/libboost_regex_vc6_mdd/regex_debug.obj vc6/libboost_regex_vc6_mdd/regex_synch.obj vc6/libboost_regex_vc6_mdd/w32_regex_traits.obj vc6/libboost_regex_vc6_mdd/wide_posix_api.obj vc6/libboost_regex_vc6_mdd/winstances.obj

