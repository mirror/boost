#
# auto generated makefile for VC6+STLPort
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

!IF "$(STLPORT_PATH)" == ""
!ERROR Variable STLPORT_PATH not set.
!ENDIF


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp ../../../boost/regex/v4/basic_regex.hpp ../../../boost/regex/v4/char_regex_traits.hpp ../../../boost/regex/v4/cregex.hpp ../../../boost/regex/v4/fileiter.hpp ../../../boost/regex/v4/instances.hpp ../../../boost/regex/v4/iterator_category.hpp ../../../boost/regex/v4/iterator_traits.hpp ../../../boost/regex/v4/match_flags.hpp ../../../boost/regex/v4/match_results.hpp ../../../boost/regex/v4/mem_block_cache.hpp ../../../boost/regex/v4/perl_matcher.hpp ../../../boost/regex/v4/perl_matcher_common.hpp ../../../boost/regex/v4/perl_matcher_non_recursive.hpp ../../../boost/regex/v4/perl_matcher_recursive.hpp ../../../boost/regex/v4/regbase.hpp ../../../boost/regex/v4/regex.hpp ../../../boost/regex/v4/regex_compile.hpp ../../../boost/regex/v4/regex_cstring.hpp ../../../boost/regex/v4/regex_format.hpp ../../../boost/regex/v4/regex_fwd.hpp ../../../boost/regex/v4/regex_grep.hpp ../../../boost/regex/v4/regex_iterator.hpp ../../../boost/regex/v4/regex_kmp.hpp ../../../boost/regex/v4/regex_match.hpp ../../../boost/regex/v4/regex_merge.hpp ../../../boost/regex/v4/regex_raw_buffer.hpp ../../../boost/regex/v4/regex_replace.hpp ../../../boost/regex/v4/regex_search.hpp ../../../boost/regex/v4/regex_split.hpp ../../../boost/regex/v4/regex_stack.hpp ../../../boost/regex/v4/regex_synch.hpp ../../../boost/regex/v4/regex_token_iterator.hpp ../../../boost/regex/v4/regex_traits.hpp ../../../boost/regex/v4/states.hpp ../../../boost/regex/v4/sub_match.hpp ../../../boost/regex/config/borland.hpp ../../../boost/regex/config/cstring.hpp ../../../boost/regex/config/cwchar.hpp ../../../boost/regex/config/regex_library_include.hpp

all : main_dir libboost_regex_vc71-stlport_ms_dir ./vc71-stlport/libboost_regex_vc71-stlport_ms.lib libboost_regex_vc71-stlport_msd_dir ./vc71-stlport/libboost_regex_vc71-stlport_msd.lib boost_regex_vc71-stlport_mdd_dir ./vc71-stlport/boost_regex_vc71-stlport_mdd.lib boost_regex_vc71-stlport_md_dir ./vc71-stlport/boost_regex_vc71-stlport_md.lib libboost_regex_vc71-stlport_md_dir ./vc71-stlport/libboost_regex_vc71-stlport_md.lib libboost_regex_vc71-stlport_mdd_dir ./vc71-stlport/libboost_regex_vc71-stlport_mdd.lib boost_regex_vc71-stlport_mddd_dir ./vc71-stlport/boost_regex_vc71-stlport_mddd.lib libboost_regex_vc71-stlport_msdd_dir ./vc71-stlport/libboost_regex_vc71-stlport_msdd.lib libboost_regex_vc71-stlport_mddd_dir ./vc71-stlport/libboost_regex_vc71-stlport_mddd.lib

clean :  libboost_regex_vc71-stlport_ms_clean libboost_regex_vc71-stlport_msd_clean boost_regex_vc71-stlport_mdd_clean boost_regex_vc71-stlport_md_clean libboost_regex_vc71-stlport_md_clean libboost_regex_vc71-stlport_mdd_clean boost_regex_vc71-stlport_mddd_clean libboost_regex_vc71-stlport_msdd_clean libboost_regex_vc71-stlport_mddd_clean

install : stlport_check all
	copy vc71-stlport\libboost_regex_vc71-stlport_ms.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_msd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex_vc71-stlport_mdd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex_vc71-stlport_mdd.dll "$(MSVCDIR)\bin"
	copy vc71-stlport\boost_regex_vc71-stlport_md.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex_vc71-stlport_md.dll "$(MSVCDIR)\bin"
	copy vc71-stlport\libboost_regex_vc71-stlport_md.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_mdd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex_vc71-stlport_mddd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex_vc71-stlport_mddd.dll "$(MSVCDIR)\bin"
	copy vc71-stlport\boost_regex_vc71-stlport_mddd.pdb "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_msdd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_msdd.pdb "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_mddd.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex_vc71-stlport_mddd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc71-stlport\$(NULL)" mkdir vc71-stlport

stlport_check : $(STLPORT_PATH)\stlport\string
	echo


########################################################
#
# section for libboost_regex_vc71-stlport_ms.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_ms/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_ms/ -Fdvc71-stlport/libboost_regex_vc71-stlport_ms.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_ms_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_ms\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_ms

libboost_regex_vc71-stlport_ms_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_ms\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_ms\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_ms\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_ms\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_ms.lib : vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_ms/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_ms/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_ms/instances.obj vc71-stlport/libboost_regex_vc71-stlport_ms/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_ms/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_ms/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_ms.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_ms/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_ms/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_ms/instances.obj vc71-stlport/libboost_regex_vc71-stlport_ms/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_ms/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_ms/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_ms/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_ms/winstances.obj

########################################################
#
# section for libboost_regex_vc71-stlport_msd.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_msd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msd.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_msd_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_msd\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_msd

libboost_regex_vc71-stlport_msd_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_msd\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_msd\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_msd\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_msd\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_msd.lib : vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_msd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_msd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_msd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_msd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_msd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msd/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_msd.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_msd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_msd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_msd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_msd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_msd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_msd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msd/winstances.obj

########################################################
#
# section for boost_regex_vc71-stlport_mdd.lib
#
########################################################
vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/c_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/cregex.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/fileiter.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/instances.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/regex.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/regex_debug.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/regex_synch.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/wide_posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mdd.pdb ../src/winstances.cpp

boost_regex_vc71-stlport_mdd_dir :
	@if not exist "vc71-stlport\boost_regex_vc71-stlport_mdd\$(NULL)" mkdir vc71-stlport\boost_regex_vc71-stlport_mdd

boost_regex_vc71-stlport_mdd_clean :
	del vc71-stlport\boost_regex_vc71-stlport_mdd\*.obj
	del vc71-stlport\boost_regex_vc71-stlport_mdd\*.idb
	del vc71-stlport\boost_regex_vc71-stlport_mdd\*.exp
	del vc71-stlport\boost_regex_vc71-stlport_mdd\*.pch

./vc71-stlport/boost_regex_vc71-stlport_mdd.lib : vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_mdd/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/cregex.obj vc71-stlport/boost_regex_vc71-stlport_mdd/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_mdd/instances.obj vc71-stlport/boost_regex_vc71-stlport_mdd/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_mdd/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mdd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71-stlport/boost_regex_vc71-stlport_mdd.pdb" /debug /machine:I386 /out:"vc71-stlport/boost_regex_vc71-stlport_mdd.dll" /implib:"vc71-stlport/boost_regex_vc71-stlport_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_mdd/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/cregex.obj vc71-stlport/boost_regex_vc71-stlport_mdd/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_mdd/instances.obj vc71-stlport/boost_regex_vc71-stlport_mdd/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_mdd/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_mdd/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mdd/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc71-stlport_md.lib
#
########################################################
vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/c_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/boost_regex_vc71-stlport_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/cregex.cpp

vc71-stlport/boost_regex_vc71-stlport_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/fileiter.cpp

vc71-stlport/boost_regex_vc71-stlport_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/instances.cpp

vc71-stlport/boost_regex_vc71-stlport_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/regex.cpp

vc71-stlport/boost_regex_vc71-stlport_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/regex_debug.cpp

vc71-stlport/boost_regex_vc71-stlport_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/regex_synch.cpp

vc71-stlport/boost_regex_vc71-stlport_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/w32_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/wide_posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_md/ -Fdvc71-stlport/boost_regex_vc71-stlport_md.pdb ../src/winstances.cpp

boost_regex_vc71-stlport_md_dir :
	@if not exist "vc71-stlport\boost_regex_vc71-stlport_md\$(NULL)" mkdir vc71-stlport\boost_regex_vc71-stlport_md

boost_regex_vc71-stlport_md_clean :
	del vc71-stlport\boost_regex_vc71-stlport_md\*.obj
	del vc71-stlport\boost_regex_vc71-stlport_md\*.idb
	del vc71-stlport\boost_regex_vc71-stlport_md\*.exp
	del vc71-stlport\boost_regex_vc71-stlport_md\*.pch

./vc71-stlport/boost_regex_vc71-stlport_md.lib : vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_md/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/cregex.obj vc71-stlport/boost_regex_vc71-stlport_md/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_md/instances.obj vc71-stlport/boost_regex_vc71-stlport_md/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_md/regex.obj vc71-stlport/boost_regex_vc71-stlport_md/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_md/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_md/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_md/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71-stlport/boost_regex_vc71-stlport_md.pdb" /debug /machine:I386 /out:"vc71-stlport/boost_regex_vc71-stlport_md.dll" /implib:"vc71-stlport/boost_regex_vc71-stlport_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_md/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/cregex.obj vc71-stlport/boost_regex_vc71-stlport_md/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_md/instances.obj vc71-stlport/boost_regex_vc71-stlport_md/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_md/regex.obj vc71-stlport/boost_regex_vc71-stlport_md/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_md/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_md/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_md/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_md/winstances.obj

########################################################
#
# section for libboost_regex_vc71-stlport_md.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_md/ -Fdvc71-stlport/libboost_regex_vc71-stlport_md.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_md_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_md\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_md

libboost_regex_vc71-stlport_md_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_md\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_md\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_md\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_md\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_md.lib : vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_md/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_md/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_md/instances.obj vc71-stlport/libboost_regex_vc71-stlport_md/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_md/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_md/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_md.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_md/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_md/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_md/instances.obj vc71-stlport/libboost_regex_vc71-stlport_md/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_md/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_md/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_md/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_md/winstances.obj

########################################################
#
# section for libboost_regex_vc71-stlport_mdd.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mdd.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_mdd_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_mdd\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_mdd

libboost_regex_vc71-stlport_mdd_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_mdd\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_mdd\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_mdd\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_mdd\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_mdd.lib : vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_mdd.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc71-stlport_mddd.lib
#
########################################################
vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/c_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/cregex.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/fileiter.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/instances.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/regex.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/regex_debug.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/regex_synch.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/wide_posix_api.cpp

vc71-stlport/boost_regex_vc71-stlport_mddd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/boost_regex_vc71-stlport_mddd.pdb ../src/winstances.cpp

boost_regex_vc71-stlport_mddd_dir :
	@if not exist "vc71-stlport\boost_regex_vc71-stlport_mddd\$(NULL)" mkdir vc71-stlport\boost_regex_vc71-stlport_mddd

boost_regex_vc71-stlport_mddd_clean :
	del vc71-stlport\boost_regex_vc71-stlport_mddd\*.obj
	del vc71-stlport\boost_regex_vc71-stlport_mddd\*.idb
	del vc71-stlport\boost_regex_vc71-stlport_mddd\*.exp
	del vc71-stlport\boost_regex_vc71-stlport_mddd\*.pch

./vc71-stlport/boost_regex_vc71-stlport_mddd.lib : vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_mddd/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/cregex.obj vc71-stlport/boost_regex_vc71-stlport_mddd/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_mddd/instances.obj vc71-stlport/boost_regex_vc71-stlport_mddd/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_mddd/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mddd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71-stlport/boost_regex_vc71-stlport_mddd.pdb" /debug /machine:I386 /out:"vc71-stlport/boost_regex_vc71-stlport_mddd.dll" /implib:"vc71-stlport/boost_regex_vc71-stlport_mddd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/c_regex_traits_common.obj vc71-stlport/boost_regex_vc71-stlport_mddd/cpp_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/cregex.obj vc71-stlport/boost_regex_vc71-stlport_mddd/fileiter.obj vc71-stlport/boost_regex_vc71-stlport_mddd/instances.obj vc71-stlport/boost_regex_vc71-stlport_mddd/posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex_debug.obj vc71-stlport/boost_regex_vc71-stlport_mddd/regex_synch.obj vc71-stlport/boost_regex_vc71-stlport_mddd/w32_regex_traits.obj vc71-stlport/boost_regex_vc71-stlport_mddd/wide_posix_api.obj vc71-stlport/boost_regex_vc71-stlport_mddd/winstances.obj

########################################################
#
# section for libboost_regex_vc71-stlport_msdd.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_msdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_msdd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_msdd.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_msdd_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_msdd\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_msdd

libboost_regex_vc71-stlport_msdd_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_msdd\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_msdd\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_msdd\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_msdd\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_msdd.lib : vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_msdd.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_msdd/winstances.obj

########################################################
#
# section for libboost_regex_vc71-stlport_mddd.lib
#
########################################################
vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/instances.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/regex.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex_vc71-stlport_mddd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex_vc71-stlport_mddd/ -Fdvc71-stlport/libboost_regex_vc71-stlport_mddd.pdb ../src/winstances.cpp

libboost_regex_vc71-stlport_mddd_dir :
	@if not exist "vc71-stlport\libboost_regex_vc71-stlport_mddd\$(NULL)" mkdir vc71-stlport\libboost_regex_vc71-stlport_mddd

libboost_regex_vc71-stlport_mddd_clean :
	del vc71-stlport\libboost_regex_vc71-stlport_mddd\*.obj
	del vc71-stlport\libboost_regex_vc71-stlport_mddd\*.idb
	del vc71-stlport\libboost_regex_vc71-stlport_mddd\*.exp
	del vc71-stlport\libboost_regex_vc71-stlport_mddd\*.pch

./vc71-stlport/libboost_regex_vc71-stlport_mddd.lib : vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex_vc71-stlport_mddd.lib $(XSFLAGS)  vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/c_regex_traits_common.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/cpp_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/cregex.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/fileiter.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/instances.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_debug.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/regex_synch.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/w32_regex_traits.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/wide_posix_api.obj vc71-stlport/libboost_regex_vc71-stlport_mddd/winstances.obj

