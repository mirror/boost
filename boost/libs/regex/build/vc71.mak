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

all : main_dir libboost_regex_vc71_ss_dir ./vc71/libboost_regex_vc71_ss.lib libboost_regex_vc71_ms_dir ./vc71/libboost_regex_vc71_ms.lib libboost_regex_vc71_ssd_dir ./vc71/libboost_regex_vc71_ssd.lib libboost_regex_vc71_msd_dir ./vc71/libboost_regex_vc71_msd.lib boost_regex_vc71_mdd_dir ./vc71/boost_regex_vc71_mdd.lib boost_regex_vc71_md_dir ./vc71/boost_regex_vc71_md.lib libboost_regex_vc71_md_dir ./vc71/libboost_regex_vc71_md.lib libboost_regex_vc71_mdd_dir ./vc71/libboost_regex_vc71_mdd.lib

clean :  libboost_regex_vc71_ss_clean libboost_regex_vc71_ms_clean libboost_regex_vc71_ssd_clean libboost_regex_vc71_msd_clean boost_regex_vc71_mdd_clean boost_regex_vc71_md_clean libboost_regex_vc71_md_clean libboost_regex_vc71_mdd_clean

install : all
	copy vc71\libboost_regex_vc71_ss.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_ms.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_ssd.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_ssd.pdb "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_msd.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_msd.pdb "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdd.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdd.dll "$(MSVCDIR)\bin"
	copy vc71\boost_regex_vc71_mdd.pdb "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_md.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_md.dll "$(MSVCDIR)\bin"
	copy vc71\libboost_regex_vc71_md.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_mdd.lib "$(MSVCDIR)\lib"
	copy vc71\libboost_regex_vc71_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc71\$(NULL)" mkdir vc71


########################################################
#
# section for libboost_regex_vc71_ss.lib
#
########################################################
vc71/libboost_regex_vc71_ss/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_ss/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_ss/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_ss/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_ss/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_ss/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_ss/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_ss/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_ss/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_ss/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_ss/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_ss/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_ss/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ss/ -Fdvc71/libboost_regex_vc71_ss.pdb ../src/winstances.cpp

libboost_regex_vc71_ss_dir :
	@if not exist "vc71\libboost_regex_vc71_ss\$(NULL)" mkdir vc71\libboost_regex_vc71_ss

libboost_regex_vc71_ss_clean :
	del vc71\libboost_regex_vc71_ss\*.obj
	del vc71\libboost_regex_vc71_ss\*.idb
	del vc71\libboost_regex_vc71_ss\*.exp
	del vc71\libboost_regex_vc71_ss\*.pch

./vc71/libboost_regex_vc71_ss.lib : vc71/libboost_regex_vc71_ss/c_regex_traits.obj vc71/libboost_regex_vc71_ss/c_regex_traits_common.obj vc71/libboost_regex_vc71_ss/cpp_regex_traits.obj vc71/libboost_regex_vc71_ss/cregex.obj vc71/libboost_regex_vc71_ss/fileiter.obj vc71/libboost_regex_vc71_ss/instances.obj vc71/libboost_regex_vc71_ss/posix_api.obj vc71/libboost_regex_vc71_ss/regex.obj vc71/libboost_regex_vc71_ss/regex_debug.obj vc71/libboost_regex_vc71_ss/regex_synch.obj vc71/libboost_regex_vc71_ss/w32_regex_traits.obj vc71/libboost_regex_vc71_ss/wide_posix_api.obj vc71/libboost_regex_vc71_ss/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_ss.lib $(XSFLAGS)  vc71/libboost_regex_vc71_ss/c_regex_traits.obj vc71/libboost_regex_vc71_ss/c_regex_traits_common.obj vc71/libboost_regex_vc71_ss/cpp_regex_traits.obj vc71/libboost_regex_vc71_ss/cregex.obj vc71/libboost_regex_vc71_ss/fileiter.obj vc71/libboost_regex_vc71_ss/instances.obj vc71/libboost_regex_vc71_ss/posix_api.obj vc71/libboost_regex_vc71_ss/regex.obj vc71/libboost_regex_vc71_ss/regex_debug.obj vc71/libboost_regex_vc71_ss/regex_synch.obj vc71/libboost_regex_vc71_ss/w32_regex_traits.obj vc71/libboost_regex_vc71_ss/wide_posix_api.obj vc71/libboost_regex_vc71_ss/winstances.obj

########################################################
#
# section for libboost_regex_vc71_ms.lib
#
########################################################
vc71/libboost_regex_vc71_ms/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_ms/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_ms/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_ms/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_ms/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_ms/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_ms/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_ms/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_ms/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_ms/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_ms/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_ms/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_ms/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ms/ -Fdvc71/libboost_regex_vc71_ms.pdb ../src/winstances.cpp

libboost_regex_vc71_ms_dir :
	@if not exist "vc71\libboost_regex_vc71_ms\$(NULL)" mkdir vc71\libboost_regex_vc71_ms

libboost_regex_vc71_ms_clean :
	del vc71\libboost_regex_vc71_ms\*.obj
	del vc71\libboost_regex_vc71_ms\*.idb
	del vc71\libboost_regex_vc71_ms\*.exp
	del vc71\libboost_regex_vc71_ms\*.pch

./vc71/libboost_regex_vc71_ms.lib : vc71/libboost_regex_vc71_ms/c_regex_traits.obj vc71/libboost_regex_vc71_ms/c_regex_traits_common.obj vc71/libboost_regex_vc71_ms/cpp_regex_traits.obj vc71/libboost_regex_vc71_ms/cregex.obj vc71/libboost_regex_vc71_ms/fileiter.obj vc71/libboost_regex_vc71_ms/instances.obj vc71/libboost_regex_vc71_ms/posix_api.obj vc71/libboost_regex_vc71_ms/regex.obj vc71/libboost_regex_vc71_ms/regex_debug.obj vc71/libboost_regex_vc71_ms/regex_synch.obj vc71/libboost_regex_vc71_ms/w32_regex_traits.obj vc71/libboost_regex_vc71_ms/wide_posix_api.obj vc71/libboost_regex_vc71_ms/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_ms.lib $(XSFLAGS)  vc71/libboost_regex_vc71_ms/c_regex_traits.obj vc71/libboost_regex_vc71_ms/c_regex_traits_common.obj vc71/libboost_regex_vc71_ms/cpp_regex_traits.obj vc71/libboost_regex_vc71_ms/cregex.obj vc71/libboost_regex_vc71_ms/fileiter.obj vc71/libboost_regex_vc71_ms/instances.obj vc71/libboost_regex_vc71_ms/posix_api.obj vc71/libboost_regex_vc71_ms/regex.obj vc71/libboost_regex_vc71_ms/regex_debug.obj vc71/libboost_regex_vc71_ms/regex_synch.obj vc71/libboost_regex_vc71_ms/w32_regex_traits.obj vc71/libboost_regex_vc71_ms/wide_posix_api.obj vc71/libboost_regex_vc71_ms/winstances.obj

########################################################
#
# section for libboost_regex_vc71_ssd.lib
#
########################################################
vc71/libboost_regex_vc71_ssd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_ssd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_ssd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_ssd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_ssd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_ssd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_ssd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_ssd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_ssd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_ssd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_ssd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_ssd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_ssd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c  $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_ssd/ -Fdvc71/libboost_regex_vc71_ssd.pdb ../src/winstances.cpp

libboost_regex_vc71_ssd_dir :
	@if not exist "vc71\libboost_regex_vc71_ssd\$(NULL)" mkdir vc71\libboost_regex_vc71_ssd

libboost_regex_vc71_ssd_clean :
	del vc71\libboost_regex_vc71_ssd\*.obj
	del vc71\libboost_regex_vc71_ssd\*.idb
	del vc71\libboost_regex_vc71_ssd\*.exp
	del vc71\libboost_regex_vc71_ssd\*.pch

./vc71/libboost_regex_vc71_ssd.lib : vc71/libboost_regex_vc71_ssd/c_regex_traits.obj vc71/libboost_regex_vc71_ssd/c_regex_traits_common.obj vc71/libboost_regex_vc71_ssd/cpp_regex_traits.obj vc71/libboost_regex_vc71_ssd/cregex.obj vc71/libboost_regex_vc71_ssd/fileiter.obj vc71/libboost_regex_vc71_ssd/instances.obj vc71/libboost_regex_vc71_ssd/posix_api.obj vc71/libboost_regex_vc71_ssd/regex.obj vc71/libboost_regex_vc71_ssd/regex_debug.obj vc71/libboost_regex_vc71_ssd/regex_synch.obj vc71/libboost_regex_vc71_ssd/w32_regex_traits.obj vc71/libboost_regex_vc71_ssd/wide_posix_api.obj vc71/libboost_regex_vc71_ssd/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_ssd.lib $(XSFLAGS)  vc71/libboost_regex_vc71_ssd/c_regex_traits.obj vc71/libboost_regex_vc71_ssd/c_regex_traits_common.obj vc71/libboost_regex_vc71_ssd/cpp_regex_traits.obj vc71/libboost_regex_vc71_ssd/cregex.obj vc71/libboost_regex_vc71_ssd/fileiter.obj vc71/libboost_regex_vc71_ssd/instances.obj vc71/libboost_regex_vc71_ssd/posix_api.obj vc71/libboost_regex_vc71_ssd/regex.obj vc71/libboost_regex_vc71_ssd/regex_debug.obj vc71/libboost_regex_vc71_ssd/regex_synch.obj vc71/libboost_regex_vc71_ssd/w32_regex_traits.obj vc71/libboost_regex_vc71_ssd/wide_posix_api.obj vc71/libboost_regex_vc71_ssd/winstances.obj

########################################################
#
# section for libboost_regex_vc71_msd.lib
#
########################################################
vc71/libboost_regex_vc71_msd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_msd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_msd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_msd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_msd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_msd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_msd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_msd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_msd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_msd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_msd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_msd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_msd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_msd/ -Fdvc71/libboost_regex_vc71_msd.pdb ../src/winstances.cpp

libboost_regex_vc71_msd_dir :
	@if not exist "vc71\libboost_regex_vc71_msd\$(NULL)" mkdir vc71\libboost_regex_vc71_msd

libboost_regex_vc71_msd_clean :
	del vc71\libboost_regex_vc71_msd\*.obj
	del vc71\libboost_regex_vc71_msd\*.idb
	del vc71\libboost_regex_vc71_msd\*.exp
	del vc71\libboost_regex_vc71_msd\*.pch

./vc71/libboost_regex_vc71_msd.lib : vc71/libboost_regex_vc71_msd/c_regex_traits.obj vc71/libboost_regex_vc71_msd/c_regex_traits_common.obj vc71/libboost_regex_vc71_msd/cpp_regex_traits.obj vc71/libboost_regex_vc71_msd/cregex.obj vc71/libboost_regex_vc71_msd/fileiter.obj vc71/libboost_regex_vc71_msd/instances.obj vc71/libboost_regex_vc71_msd/posix_api.obj vc71/libboost_regex_vc71_msd/regex.obj vc71/libboost_regex_vc71_msd/regex_debug.obj vc71/libboost_regex_vc71_msd/regex_synch.obj vc71/libboost_regex_vc71_msd/w32_regex_traits.obj vc71/libboost_regex_vc71_msd/wide_posix_api.obj vc71/libboost_regex_vc71_msd/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_msd.lib $(XSFLAGS)  vc71/libboost_regex_vc71_msd/c_regex_traits.obj vc71/libboost_regex_vc71_msd/c_regex_traits_common.obj vc71/libboost_regex_vc71_msd/cpp_regex_traits.obj vc71/libboost_regex_vc71_msd/cregex.obj vc71/libboost_regex_vc71_msd/fileiter.obj vc71/libboost_regex_vc71_msd/instances.obj vc71/libboost_regex_vc71_msd/posix_api.obj vc71/libboost_regex_vc71_msd/regex.obj vc71/libboost_regex_vc71_msd/regex_debug.obj vc71/libboost_regex_vc71_msd/regex_synch.obj vc71/libboost_regex_vc71_msd/w32_regex_traits.obj vc71/libboost_regex_vc71_msd/wide_posix_api.obj vc71/libboost_regex_vc71_msd/winstances.obj

########################################################
#
# section for boost_regex_vc71_mdd.lib
#
########################################################
vc71/boost_regex_vc71_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DBOOST_REGEX_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_mdd/ -Fdvc71/boost_regex_vc71_mdd.pdb ../src/winstances.cpp

boost_regex_vc71_mdd_dir :
	@if not exist "vc71\boost_regex_vc71_mdd\$(NULL)" mkdir vc71\boost_regex_vc71_mdd

boost_regex_vc71_mdd_clean :
	del vc71\boost_regex_vc71_mdd\*.obj
	del vc71\boost_regex_vc71_mdd\*.idb
	del vc71\boost_regex_vc71_mdd\*.exp
	del vc71\boost_regex_vc71_mdd\*.pch

./vc71/boost_regex_vc71_mdd.lib : vc71/boost_regex_vc71_mdd/c_regex_traits.obj vc71/boost_regex_vc71_mdd/c_regex_traits_common.obj vc71/boost_regex_vc71_mdd/cpp_regex_traits.obj vc71/boost_regex_vc71_mdd/cregex.obj vc71/boost_regex_vc71_mdd/fileiter.obj vc71/boost_regex_vc71_mdd/instances.obj vc71/boost_regex_vc71_mdd/posix_api.obj vc71/boost_regex_vc71_mdd/regex.obj vc71/boost_regex_vc71_mdd/regex_debug.obj vc71/boost_regex_vc71_mdd/regex_synch.obj vc71/boost_regex_vc71_mdd/w32_regex_traits.obj vc71/boost_regex_vc71_mdd/wide_posix_api.obj vc71/boost_regex_vc71_mdd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/boost_regex_vc71_mdd.pdb" /debug /machine:I386 /out:"vc71/boost_regex_vc71_mdd.dll" /implib:"vc71/boost_regex_vc71_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/boost_regex_vc71_mdd/c_regex_traits.obj vc71/boost_regex_vc71_mdd/c_regex_traits_common.obj vc71/boost_regex_vc71_mdd/cpp_regex_traits.obj vc71/boost_regex_vc71_mdd/cregex.obj vc71/boost_regex_vc71_mdd/fileiter.obj vc71/boost_regex_vc71_mdd/instances.obj vc71/boost_regex_vc71_mdd/posix_api.obj vc71/boost_regex_vc71_mdd/regex.obj vc71/boost_regex_vc71_mdd/regex_debug.obj vc71/boost_regex_vc71_mdd/regex_synch.obj vc71/boost_regex_vc71_mdd/w32_regex_traits.obj vc71/boost_regex_vc71_mdd/wide_posix_api.obj vc71/boost_regex_vc71_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc71_md.lib
#
########################################################
vc71/boost_regex_vc71_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/instances.cpp

vc71/boost_regex_vc71_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/regex.cpp

vc71/boost_regex_vc71_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/boost_regex_vc71_md/ -Fdvc71/boost_regex_vc71_md.pdb ../src/winstances.cpp

boost_regex_vc71_md_dir :
	@if not exist "vc71\boost_regex_vc71_md\$(NULL)" mkdir vc71\boost_regex_vc71_md

boost_regex_vc71_md_clean :
	del vc71\boost_regex_vc71_md\*.obj
	del vc71\boost_regex_vc71_md\*.idb
	del vc71\boost_regex_vc71_md\*.exp
	del vc71\boost_regex_vc71_md\*.pch

./vc71/boost_regex_vc71_md.lib : vc71/boost_regex_vc71_md/c_regex_traits.obj vc71/boost_regex_vc71_md/c_regex_traits_common.obj vc71/boost_regex_vc71_md/cpp_regex_traits.obj vc71/boost_regex_vc71_md/cregex.obj vc71/boost_regex_vc71_md/fileiter.obj vc71/boost_regex_vc71_md/instances.obj vc71/boost_regex_vc71_md/posix_api.obj vc71/boost_regex_vc71_md/regex.obj vc71/boost_regex_vc71_md/regex_debug.obj vc71/boost_regex_vc71_md/regex_synch.obj vc71/boost_regex_vc71_md/w32_regex_traits.obj vc71/boost_regex_vc71_md/wide_posix_api.obj vc71/boost_regex_vc71_md/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/boost_regex_vc71_md.pdb" /debug /machine:I386 /out:"vc71/boost_regex_vc71_md.dll" /implib:"vc71/boost_regex_vc71_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/boost_regex_vc71_md/c_regex_traits.obj vc71/boost_regex_vc71_md/c_regex_traits_common.obj vc71/boost_regex_vc71_md/cpp_regex_traits.obj vc71/boost_regex_vc71_md/cregex.obj vc71/boost_regex_vc71_md/fileiter.obj vc71/boost_regex_vc71_md/instances.obj vc71/boost_regex_vc71_md/posix_api.obj vc71/boost_regex_vc71_md/regex.obj vc71/boost_regex_vc71_md/regex_debug.obj vc71/boost_regex_vc71_md/regex_synch.obj vc71/boost_regex_vc71_md/w32_regex_traits.obj vc71/boost_regex_vc71_md/wide_posix_api.obj vc71/boost_regex_vc71_md/winstances.obj

########################################################
#
# section for libboost_regex_vc71_md.lib
#
########################################################
vc71/libboost_regex_vc71_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_md/ -Fdvc71/libboost_regex_vc71_md.pdb ../src/winstances.cpp

libboost_regex_vc71_md_dir :
	@if not exist "vc71\libboost_regex_vc71_md\$(NULL)" mkdir vc71\libboost_regex_vc71_md

libboost_regex_vc71_md_clean :
	del vc71\libboost_regex_vc71_md\*.obj
	del vc71\libboost_regex_vc71_md\*.idb
	del vc71\libboost_regex_vc71_md\*.exp
	del vc71\libboost_regex_vc71_md\*.pch

./vc71/libboost_regex_vc71_md.lib : vc71/libboost_regex_vc71_md/c_regex_traits.obj vc71/libboost_regex_vc71_md/c_regex_traits_common.obj vc71/libboost_regex_vc71_md/cpp_regex_traits.obj vc71/libboost_regex_vc71_md/cregex.obj vc71/libboost_regex_vc71_md/fileiter.obj vc71/libboost_regex_vc71_md/instances.obj vc71/libboost_regex_vc71_md/posix_api.obj vc71/libboost_regex_vc71_md/regex.obj vc71/libboost_regex_vc71_md/regex_debug.obj vc71/libboost_regex_vc71_md/regex_synch.obj vc71/libboost_regex_vc71_md/w32_regex_traits.obj vc71/libboost_regex_vc71_md/wide_posix_api.obj vc71/libboost_regex_vc71_md/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_md.lib $(XSFLAGS)  vc71/libboost_regex_vc71_md/c_regex_traits.obj vc71/libboost_regex_vc71_md/c_regex_traits_common.obj vc71/libboost_regex_vc71_md/cpp_regex_traits.obj vc71/libboost_regex_vc71_md/cregex.obj vc71/libboost_regex_vc71_md/fileiter.obj vc71/libboost_regex_vc71_md/instances.obj vc71/libboost_regex_vc71_md/posix_api.obj vc71/libboost_regex_vc71_md/regex.obj vc71/libboost_regex_vc71_md/regex_debug.obj vc71/libboost_regex_vc71_md/regex_synch.obj vc71/libboost_regex_vc71_md/w32_regex_traits.obj vc71/libboost_regex_vc71_md/wide_posix_api.obj vc71/libboost_regex_vc71_md/winstances.obj

########################################################
#
# section for libboost_regex_vc71_mdd.lib
#
########################################################
vc71/libboost_regex_vc71_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/c_regex_traits.cpp

vc71/libboost_regex_vc71_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/c_regex_traits_common.cpp

vc71/libboost_regex_vc71_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/cpp_regex_traits.cpp

vc71/libboost_regex_vc71_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/cregex.cpp

vc71/libboost_regex_vc71_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/fileiter.cpp

vc71/libboost_regex_vc71_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/instances.cpp

vc71/libboost_regex_vc71_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/posix_api.cpp

vc71/libboost_regex_vc71_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/regex.cpp

vc71/libboost_regex_vc71_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/regex_debug.cpp

vc71/libboost_regex_vc71_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/regex_synch.cpp

vc71/libboost_regex_vc71_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/w32_regex_traits.cpp

vc71/libboost_regex_vc71_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/wide_posix_api.cpp

vc71/libboost_regex_vc71_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71/libboost_regex_vc71_mdd/ -Fdvc71/libboost_regex_vc71_mdd.pdb ../src/winstances.cpp

libboost_regex_vc71_mdd_dir :
	@if not exist "vc71\libboost_regex_vc71_mdd\$(NULL)" mkdir vc71\libboost_regex_vc71_mdd

libboost_regex_vc71_mdd_clean :
	del vc71\libboost_regex_vc71_mdd\*.obj
	del vc71\libboost_regex_vc71_mdd\*.idb
	del vc71\libboost_regex_vc71_mdd\*.exp
	del vc71\libboost_regex_vc71_mdd\*.pch

./vc71/libboost_regex_vc71_mdd.lib : vc71/libboost_regex_vc71_mdd/c_regex_traits.obj vc71/libboost_regex_vc71_mdd/c_regex_traits_common.obj vc71/libboost_regex_vc71_mdd/cpp_regex_traits.obj vc71/libboost_regex_vc71_mdd/cregex.obj vc71/libboost_regex_vc71_mdd/fileiter.obj vc71/libboost_regex_vc71_mdd/instances.obj vc71/libboost_regex_vc71_mdd/posix_api.obj vc71/libboost_regex_vc71_mdd/regex.obj vc71/libboost_regex_vc71_mdd/regex_debug.obj vc71/libboost_regex_vc71_mdd/regex_synch.obj vc71/libboost_regex_vc71_mdd/w32_regex_traits.obj vc71/libboost_regex_vc71_mdd/wide_posix_api.obj vc71/libboost_regex_vc71_mdd/winstances.obj
	link -lib /nologo /out:vc71/libboost_regex_vc71_mdd.lib $(XSFLAGS)  vc71/libboost_regex_vc71_mdd/c_regex_traits.obj vc71/libboost_regex_vc71_mdd/c_regex_traits_common.obj vc71/libboost_regex_vc71_mdd/cpp_regex_traits.obj vc71/libboost_regex_vc71_mdd/cregex.obj vc71/libboost_regex_vc71_mdd/fileiter.obj vc71/libboost_regex_vc71_mdd/instances.obj vc71/libboost_regex_vc71_mdd/posix_api.obj vc71/libboost_regex_vc71_mdd/regex.obj vc71/libboost_regex_vc71_mdd/regex_debug.obj vc71/libboost_regex_vc71_mdd/regex_synch.obj vc71/libboost_regex_vc71_mdd/w32_regex_traits.obj vc71/libboost_regex_vc71_mdd/wide_posix_api.obj vc71/libboost_regex_vc71_mdd/winstances.obj

