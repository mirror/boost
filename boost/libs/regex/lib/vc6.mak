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


ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : main_dir vc6-re300_dir ./vc6/vc6-re300.lib vc6-re300m_dir ./vc6/vc6-re300m.lib vc6-re300d_dir ./vc6/vc6-re300d.lib vc6-re300dm_dir ./vc6/vc6-re300dm.lib vc6-re300dl_dir ./vc6/vc6-re300dl.lib vc6-re300l_dir ./vc6/vc6-re300l.lib

clean :  vc6-re300_clean vc6-re300m_clean vc6-re300d_clean vc6-re300dm_clean vc6-re300dl_clean vc6-re300l_clean

install : all
	copy vc6\vc6-re300.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300m.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300d.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300d.pdb "$(MSVCDIR)\lib"
	copy vc6\vc6-re300dm.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300dm.pdb "$(MSVCDIR)\lib"
	copy vc6\vc6-re300dl.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300dl.dll "$(MSVCDIR)\bin"
	copy vc6\vc6-re300dl.pdb "$(MSVCDIR)\lib"
	copy vc6\vc6-re300l.lib "$(MSVCDIR)\lib"
	copy vc6\vc6-re300l.dll "$(MSVCDIR)\bin"

main_dir :
	if not exist "vc6\$(NULL)" mkdir vc6


########################################################
#
# section for vc6-re300.lib
#
########################################################
vc6/vc6-re300/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/cregex.cpp

vc6/vc6-re300/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/fileiter.cpp

vc6/vc6-re300/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/posix_api.cpp

vc6/vc6-re300/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/regex.cpp

vc6/vc6-re300/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/regex_debug.cpp

vc6/vc6-re300/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/regex_synch.cpp

vc6/vc6-re300/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc6/vc6-re300/vc6-re300.pch -Fo./vc6/vc6-re300/ -Fdvc6/vc6-re300.pdb ../src/wide_posix_api.cpp

vc6-re300_dir :
	if not exist "vc6\vc6-re300\$(NULL)" mkdir vc6\vc6-re300

vc6-re300_clean :
	del vc6\vc6-re300\*.obj
	del vc6\vc6-re300\*.idb
	del vc6\vc6-re300\*.exp
	del vc6\vc6-re300\*.pch

./vc6/vc6-re300.lib : vc6/vc6-re300/c_regex_traits.obj vc6/vc6-re300/c_regex_traits_common.obj vc6/vc6-re300/cpp_regex_traits.obj vc6/vc6-re300/cregex.obj vc6/vc6-re300/fileiter.obj vc6/vc6-re300/posix_api.obj vc6/vc6-re300/regex.obj vc6/vc6-re300/regex_debug.obj vc6/vc6-re300/regex_synch.obj vc6/vc6-re300/w32_regex_traits.obj vc6/vc6-re300/wide_posix_api.obj
	link -lib /nologo /out:vc6/vc6-re300.lib $(XSFLAGS)  vc6/vc6-re300/c_regex_traits.obj vc6/vc6-re300/c_regex_traits_common.obj vc6/vc6-re300/cpp_regex_traits.obj vc6/vc6-re300/cregex.obj vc6/vc6-re300/fileiter.obj vc6/vc6-re300/posix_api.obj vc6/vc6-re300/regex.obj vc6/vc6-re300/regex_debug.obj vc6/vc6-re300/regex_synch.obj vc6/vc6-re300/w32_regex_traits.obj vc6/vc6-re300/wide_posix_api.obj

########################################################
#
# section for vc6-re300m.lib
#
########################################################
vc6/vc6-re300m/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300m/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300m/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300m/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/cregex.cpp

vc6/vc6-re300m/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/fileiter.cpp

vc6/vc6-re300m/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/posix_api.cpp

vc6/vc6-re300m/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/regex.cpp

vc6/vc6-re300m/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/regex_debug.cpp

vc6/vc6-re300m/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/regex_synch.cpp

vc6/vc6-re300m/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300m/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /Oityb1 /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300m/vc6-re300m.pch -Fo./vc6/vc6-re300m/ -Fdvc6/vc6-re300m.pdb ../src/wide_posix_api.cpp

vc6-re300m_dir :
	if not exist "vc6\vc6-re300m\$(NULL)" mkdir vc6\vc6-re300m

vc6-re300m_clean :
	del vc6\vc6-re300m\*.obj
	del vc6\vc6-re300m\*.idb
	del vc6\vc6-re300m\*.exp
	del vc6\vc6-re300m\*.pch

./vc6/vc6-re300m.lib : vc6/vc6-re300m/c_regex_traits.obj vc6/vc6-re300m/c_regex_traits_common.obj vc6/vc6-re300m/cpp_regex_traits.obj vc6/vc6-re300m/cregex.obj vc6/vc6-re300m/fileiter.obj vc6/vc6-re300m/posix_api.obj vc6/vc6-re300m/regex.obj vc6/vc6-re300m/regex_debug.obj vc6/vc6-re300m/regex_synch.obj vc6/vc6-re300m/w32_regex_traits.obj vc6/vc6-re300m/wide_posix_api.obj
	link -lib /nologo /out:vc6/vc6-re300m.lib $(XSFLAGS)  vc6/vc6-re300m/c_regex_traits.obj vc6/vc6-re300m/c_regex_traits_common.obj vc6/vc6-re300m/cpp_regex_traits.obj vc6/vc6-re300m/cregex.obj vc6/vc6-re300m/fileiter.obj vc6/vc6-re300m/posix_api.obj vc6/vc6-re300m/regex.obj vc6/vc6-re300m/regex_debug.obj vc6/vc6-re300m/regex_synch.obj vc6/vc6-re300m/w32_regex_traits.obj vc6/vc6-re300m/wide_posix_api.obj

########################################################
#
# section for vc6-re300d.lib
#
########################################################
vc6/vc6-re300d/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300d/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300d/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300d/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/cregex.cpp

vc6/vc6-re300d/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/fileiter.cpp

vc6/vc6-re300d/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/posix_api.cpp

vc6/vc6-re300d/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/regex.cpp

vc6/vc6-re300d/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/regex_debug.cpp

vc6/vc6-re300d/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/regex_synch.cpp

vc6/vc6-re300d/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300d/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc6/vc6-re300d/vc6-re300d.pch -Fo./vc6/vc6-re300d/ -Fdvc6/vc6-re300d.pdb ../src/wide_posix_api.cpp

vc6-re300d_dir :
	if not exist "vc6\vc6-re300d\$(NULL)" mkdir vc6\vc6-re300d

vc6-re300d_clean :
	del vc6\vc6-re300d\*.obj
	del vc6\vc6-re300d\*.idb
	del vc6\vc6-re300d\*.exp
	del vc6\vc6-re300d\*.pch

./vc6/vc6-re300d.lib : vc6/vc6-re300d/c_regex_traits.obj vc6/vc6-re300d/c_regex_traits_common.obj vc6/vc6-re300d/cpp_regex_traits.obj vc6/vc6-re300d/cregex.obj vc6/vc6-re300d/fileiter.obj vc6/vc6-re300d/posix_api.obj vc6/vc6-re300d/regex.obj vc6/vc6-re300d/regex_debug.obj vc6/vc6-re300d/regex_synch.obj vc6/vc6-re300d/w32_regex_traits.obj vc6/vc6-re300d/wide_posix_api.obj
	link -lib /nologo /out:vc6/vc6-re300d.lib $(XSFLAGS)  vc6/vc6-re300d/c_regex_traits.obj vc6/vc6-re300d/c_regex_traits_common.obj vc6/vc6-re300d/cpp_regex_traits.obj vc6/vc6-re300d/cregex.obj vc6/vc6-re300d/fileiter.obj vc6/vc6-re300d/posix_api.obj vc6/vc6-re300d/regex.obj vc6/vc6-re300d/regex_debug.obj vc6/vc6-re300d/regex_synch.obj vc6/vc6-re300d/w32_regex_traits.obj vc6/vc6-re300d/wide_posix_api.obj

########################################################
#
# section for vc6-re300dm.lib
#
########################################################
vc6/vc6-re300dm/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300dm/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300dm/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300dm/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/cregex.cpp

vc6/vc6-re300dm/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/fileiter.cpp

vc6/vc6-re300dm/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/posix_api.cpp

vc6/vc6-re300dm/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/regex.cpp

vc6/vc6-re300dm/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/regex_debug.cpp

vc6/vc6-re300dm/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/regex_synch.cpp

vc6/vc6-re300dm/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300dm/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dm/vc6-re300dm.pch -Fo./vc6/vc6-re300dm/ -Fdvc6/vc6-re300dm.pdb ../src/wide_posix_api.cpp

vc6-re300dm_dir :
	if not exist "vc6\vc6-re300dm\$(NULL)" mkdir vc6\vc6-re300dm

vc6-re300dm_clean :
	del vc6\vc6-re300dm\*.obj
	del vc6\vc6-re300dm\*.idb
	del vc6\vc6-re300dm\*.exp
	del vc6\vc6-re300dm\*.pch

./vc6/vc6-re300dm.lib : vc6/vc6-re300dm/c_regex_traits.obj vc6/vc6-re300dm/c_regex_traits_common.obj vc6/vc6-re300dm/cpp_regex_traits.obj vc6/vc6-re300dm/cregex.obj vc6/vc6-re300dm/fileiter.obj vc6/vc6-re300dm/posix_api.obj vc6/vc6-re300dm/regex.obj vc6/vc6-re300dm/regex_debug.obj vc6/vc6-re300dm/regex_synch.obj vc6/vc6-re300dm/w32_regex_traits.obj vc6/vc6-re300dm/wide_posix_api.obj
	link -lib /nologo /out:vc6/vc6-re300dm.lib $(XSFLAGS)  vc6/vc6-re300dm/c_regex_traits.obj vc6/vc6-re300dm/c_regex_traits_common.obj vc6/vc6-re300dm/cpp_regex_traits.obj vc6/vc6-re300dm/cregex.obj vc6/vc6-re300dm/fileiter.obj vc6/vc6-re300dm/posix_api.obj vc6/vc6-re300dm/regex.obj vc6/vc6-re300dm/regex_debug.obj vc6/vc6-re300dm/regex_synch.obj vc6/vc6-re300dm/w32_regex_traits.obj vc6/vc6-re300dm/wide_posix_api.obj

########################################################
#
# section for vc6-re300dl.lib
#
########################################################
vc6/vc6-re300dl/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300dl/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300dl/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300dl/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/cregex.cpp

vc6/vc6-re300dl/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/fileiter.cpp

vc6/vc6-re300dl/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/posix_api.cpp

vc6/vc6-re300dl/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/regex.cpp

vc6/vc6-re300dl/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/regex_debug.cpp

vc6/vc6-re300dl/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/regex_synch.cpp

vc6/vc6-re300dl/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300dl/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6/vc6-re300dl/vc6-re300dl.pch -Fo./vc6/vc6-re300dl/ -Fdvc6/vc6-re300dl.pdb ../src/wide_posix_api.cpp

vc6-re300dl_dir :
	if not exist "vc6\vc6-re300dl\$(NULL)" mkdir vc6\vc6-re300dl

vc6-re300dl_clean :
	del vc6\vc6-re300dl\*.obj
	del vc6\vc6-re300dl\*.idb
	del vc6\vc6-re300dl\*.exp
	del vc6\vc6-re300dl\*.pch

./vc6/vc6-re300dl.lib : vc6/vc6-re300dl/c_regex_traits.obj vc6/vc6-re300dl/c_regex_traits_common.obj vc6/vc6-re300dl/cpp_regex_traits.obj vc6/vc6-re300dl/cregex.obj vc6/vc6-re300dl/fileiter.obj vc6/vc6-re300dl/posix_api.obj vc6/vc6-re300dl/regex.obj vc6/vc6-re300dl/regex_debug.obj vc6/vc6-re300dl/regex_synch.obj vc6/vc6-re300dl/w32_regex_traits.obj vc6/vc6-re300dl/wide_posix_api.obj
	link @<<
	kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/vc6-re300dl.pdb" /debug /machine:I386 /out:"vc6/vc6-re300dl.dll" /implib:"vc6/vc6-re300dl.lib" /pdbtype:sept $(XLFLAGS)  vc6/vc6-re300dl/c_regex_traits.obj vc6/vc6-re300dl/c_regex_traits_common.obj vc6/vc6-re300dl/cpp_regex_traits.obj vc6/vc6-re300dl/cregex.obj vc6/vc6-re300dl/fileiter.obj vc6/vc6-re300dl/posix_api.obj vc6/vc6-re300dl/regex.obj vc6/vc6-re300dl/regex_debug.obj vc6/vc6-re300dl/regex_synch.obj vc6/vc6-re300dl/w32_regex_traits.obj vc6/vc6-re300dl/wide_posix_api.obj
<<

########################################################
#
# section for vc6-re300l.lib
#
########################################################
vc6/vc6-re300l/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/c_regex_traits.cpp

vc6/vc6-re300l/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/c_regex_traits_common.cpp

vc6/vc6-re300l/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/cpp_regex_traits.cpp

vc6/vc6-re300l/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/cregex.cpp

vc6/vc6-re300l/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/fileiter.cpp

vc6/vc6-re300l/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/posix_api.cpp

vc6/vc6-re300l/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/regex.cpp

vc6/vc6-re300l/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/regex_debug.cpp

vc6/vc6-re300l/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/regex_synch.cpp

vc6/vc6-re300l/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/w32_regex_traits.cpp

vc6/vc6-re300l/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /Oityb1 /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /DBOOST_RE_DLL_EXPORTS /DBOOST_RE_BUILD_DLL /YX /FD /c $(CXXFLAGS) -Fpvc6/vc6-re300l/vc6-re300l.pch -Fo./vc6/vc6-re300l/ -Fdvc6/vc6-re300l.pdb ../src/wide_posix_api.cpp

vc6-re300l_dir :
	if not exist "vc6\vc6-re300l\$(NULL)" mkdir vc6\vc6-re300l

vc6-re300l_clean :
	del vc6\vc6-re300l\*.obj
	del vc6\vc6-re300l\*.idb
	del vc6\vc6-re300l\*.exp
	del vc6\vc6-re300l\*.pch

./vc6/vc6-re300l.lib : vc6/vc6-re300l/c_regex_traits.obj vc6/vc6-re300l/c_regex_traits_common.obj vc6/vc6-re300l/cpp_regex_traits.obj vc6/vc6-re300l/cregex.obj vc6/vc6-re300l/fileiter.obj vc6/vc6-re300l/posix_api.obj vc6/vc6-re300l/regex.obj vc6/vc6-re300l/regex_debug.obj vc6/vc6-re300l/regex_synch.obj vc6/vc6-re300l/w32_regex_traits.obj vc6/vc6-re300l/wide_posix_api.obj
	link @<<
	kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/vc6-re300l.pdb" /debug /machine:I386 /out:"vc6/vc6-re300l.dll" /implib:"vc6/vc6-re300l.lib" /pdbtype:sept $(XLFLAGS)  vc6/vc6-re300l/c_regex_traits.obj vc6/vc6-re300l/c_regex_traits_common.obj vc6/vc6-re300l/cpp_regex_traits.obj vc6/vc6-re300l/cregex.obj vc6/vc6-re300l/fileiter.obj vc6/vc6-re300l/posix_api.obj vc6/vc6-re300l/regex.obj vc6/vc6-re300l/regex_debug.obj vc6/vc6-re300l/regex_synch.obj vc6/vc6-re300l/w32_regex_traits.obj vc6/vc6-re300l/wide_posix_api.obj
<<

