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


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/detail/fileiter.hpp ../../../boost/regex/detail/regex_compile.hpp ../../../boost/regex/detail/regex_cstring.hpp ../../../boost/regex/detail/regex_format.hpp ../../../boost/regex/detail/regex_kmp.hpp ../../../boost/regex/detail/regex_library_include.hpp ../../../boost/regex/detail/regex_match.hpp ../../../boost/regex/detail/regex_raw_buffer.hpp ../../../boost/regex/detail/regex_split.hpp ../../../boost/regex/detail/regex_stack.hpp ../../../boost/regex/detail/regex_synch.hpp

all : main_dir vc7-re300_dir ./vc7/vc7-re300.lib vc7-re300m_dir ./vc7/vc7-re300m.lib vc7-re300d_dir ./vc7/vc7-re300d.lib vc7-re300dm_dir ./vc7/vc7-re300dm.lib vc7-re300dl_dir ./vc7/vc7-re300dl.lib vc7-re300l_dir ./vc7/vc7-re300l.lib vc7-re300ls_dir ./vc7/vc7-re300ls.lib

clean :  vc7-re300_clean vc7-re300m_clean vc7-re300d_clean vc7-re300dm_clean vc7-re300dl_clean vc7-re300l_clean vc7-re300ls_clean

install : all
	copy vc7\vc7-re300.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300.pdb "$(MSVCDIR)\lib"
	copy vc7\vc7-re300m.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300m.pdb "$(MSVCDIR)\lib"
	copy vc7\vc7-re300d.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300d.pdb "$(MSVCDIR)\lib"
	copy vc7\vc7-re300dm.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300dm.pdb "$(MSVCDIR)\lib"
	copy vc7\vc7-re300dl.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300dl.dll "$(MSVCDIR)\bin"
	copy vc7\vc7-re300dl.pdb "$(MSVCDIR)\lib"
	copy vc7\vc7-re300l.lib "$(MSVCDIR)\lib"
	copy vc7\vc7-re300l.dll "$(MSVCDIR)\bin"
	copy vc7\vc7-re300ls.lib "$(MSVCDIR)\lib"

main_dir :
	if not exist "vc7\$(NULL)" mkdir vc7


########################################################
#
# section for vc7-re300.lib
#
########################################################
vc7/vc7-re300/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/cregex.cpp

vc7/vc7-re300/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/fileiter.cpp

vc7/vc7-re300/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/posix_api.cpp

vc7/vc7-re300/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/regex.cpp

vc7/vc7-re300/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/regex_debug.cpp

vc7/vc7-re300/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/regex_synch.cpp

vc7/vc7-re300/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc7/vc7-re300/vc7-re300.pch -Fo./vc7/vc7-re300/ -Fdvc7/vc7-re300.pdb ../src/wide_posix_api.cpp

vc7-re300_dir :
	if not exist "vc7\vc7-re300\$(NULL)" mkdir vc7\vc7-re300

vc7-re300_clean :
	del vc7\vc7-re300\*.obj
	del vc7\vc7-re300\*.idb
	del vc7\vc7-re300\*.exp
	del vc7\vc7-re300\*.pch

./vc7/vc7-re300.lib : vc7/vc7-re300/c_regex_traits.obj vc7/vc7-re300/c_regex_traits_common.obj vc7/vc7-re300/cpp_regex_traits.obj vc7/vc7-re300/cregex.obj vc7/vc7-re300/fileiter.obj vc7/vc7-re300/posix_api.obj vc7/vc7-re300/regex.obj vc7/vc7-re300/regex_debug.obj vc7/vc7-re300/regex_synch.obj vc7/vc7-re300/w32_regex_traits.obj vc7/vc7-re300/wide_posix_api.obj
	link -lib /nologo /out:vc7/vc7-re300.lib $(XSFLAGS)  vc7/vc7-re300/c_regex_traits.obj vc7/vc7-re300/c_regex_traits_common.obj vc7/vc7-re300/cpp_regex_traits.obj vc7/vc7-re300/cregex.obj vc7/vc7-re300/fileiter.obj vc7/vc7-re300/posix_api.obj vc7/vc7-re300/regex.obj vc7/vc7-re300/regex_debug.obj vc7/vc7-re300/regex_synch.obj vc7/vc7-re300/w32_regex_traits.obj vc7/vc7-re300/wide_posix_api.obj

########################################################
#
# section for vc7-re300m.lib
#
########################################################
vc7/vc7-re300m/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300m/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300m/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300m/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/cregex.cpp

vc7/vc7-re300m/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/fileiter.cpp

vc7/vc7-re300m/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/posix_api.cpp

vc7/vc7-re300m/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/regex.cpp

vc7/vc7-re300m/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/regex_debug.cpp

vc7/vc7-re300m/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/regex_synch.cpp

vc7/vc7-re300m/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300m/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300m/vc7-re300m.pch -Fo./vc7/vc7-re300m/ -Fdvc7/vc7-re300m.pdb ../src/wide_posix_api.cpp

vc7-re300m_dir :
	if not exist "vc7\vc7-re300m\$(NULL)" mkdir vc7\vc7-re300m

vc7-re300m_clean :
	del vc7\vc7-re300m\*.obj
	del vc7\vc7-re300m\*.idb
	del vc7\vc7-re300m\*.exp
	del vc7\vc7-re300m\*.pch

./vc7/vc7-re300m.lib : vc7/vc7-re300m/c_regex_traits.obj vc7/vc7-re300m/c_regex_traits_common.obj vc7/vc7-re300m/cpp_regex_traits.obj vc7/vc7-re300m/cregex.obj vc7/vc7-re300m/fileiter.obj vc7/vc7-re300m/posix_api.obj vc7/vc7-re300m/regex.obj vc7/vc7-re300m/regex_debug.obj vc7/vc7-re300m/regex_synch.obj vc7/vc7-re300m/w32_regex_traits.obj vc7/vc7-re300m/wide_posix_api.obj
	link -lib /nologo /out:vc7/vc7-re300m.lib $(XSFLAGS)  vc7/vc7-re300m/c_regex_traits.obj vc7/vc7-re300m/c_regex_traits_common.obj vc7/vc7-re300m/cpp_regex_traits.obj vc7/vc7-re300m/cregex.obj vc7/vc7-re300m/fileiter.obj vc7/vc7-re300m/posix_api.obj vc7/vc7-re300m/regex.obj vc7/vc7-re300m/regex_debug.obj vc7/vc7-re300m/regex_synch.obj vc7/vc7-re300m/w32_regex_traits.obj vc7/vc7-re300m/wide_posix_api.obj

########################################################
#
# section for vc7-re300d.lib
#
########################################################
vc7/vc7-re300d/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300d/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300d/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300d/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/cregex.cpp

vc7/vc7-re300d/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/fileiter.cpp

vc7/vc7-re300d/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/posix_api.cpp

vc7/vc7-re300d/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/regex.cpp

vc7/vc7-re300d/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/regex_debug.cpp

vc7/vc7-re300d/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/regex_synch.cpp

vc7/vc7-re300d/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300d/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc7/vc7-re300d/vc7-re300d.pch -Fo./vc7/vc7-re300d/ -Fdvc7/vc7-re300d.pdb ../src/wide_posix_api.cpp

vc7-re300d_dir :
	if not exist "vc7\vc7-re300d\$(NULL)" mkdir vc7\vc7-re300d

vc7-re300d_clean :
	del vc7\vc7-re300d\*.obj
	del vc7\vc7-re300d\*.idb
	del vc7\vc7-re300d\*.exp
	del vc7\vc7-re300d\*.pch

./vc7/vc7-re300d.lib : vc7/vc7-re300d/c_regex_traits.obj vc7/vc7-re300d/c_regex_traits_common.obj vc7/vc7-re300d/cpp_regex_traits.obj vc7/vc7-re300d/cregex.obj vc7/vc7-re300d/fileiter.obj vc7/vc7-re300d/posix_api.obj vc7/vc7-re300d/regex.obj vc7/vc7-re300d/regex_debug.obj vc7/vc7-re300d/regex_synch.obj vc7/vc7-re300d/w32_regex_traits.obj vc7/vc7-re300d/wide_posix_api.obj
	link -lib /nologo /out:vc7/vc7-re300d.lib $(XSFLAGS)  vc7/vc7-re300d/c_regex_traits.obj vc7/vc7-re300d/c_regex_traits_common.obj vc7/vc7-re300d/cpp_regex_traits.obj vc7/vc7-re300d/cregex.obj vc7/vc7-re300d/fileiter.obj vc7/vc7-re300d/posix_api.obj vc7/vc7-re300d/regex.obj vc7/vc7-re300d/regex_debug.obj vc7/vc7-re300d/regex_synch.obj vc7/vc7-re300d/w32_regex_traits.obj vc7/vc7-re300d/wide_posix_api.obj

########################################################
#
# section for vc7-re300dm.lib
#
########################################################
vc7/vc7-re300dm/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300dm/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300dm/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300dm/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/cregex.cpp

vc7/vc7-re300dm/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/fileiter.cpp

vc7/vc7-re300dm/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/posix_api.cpp

vc7/vc7-re300dm/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/regex.cpp

vc7/vc7-re300dm/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/regex_debug.cpp

vc7/vc7-re300dm/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/regex_synch.cpp

vc7/vc7-re300dm/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300dm/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dm/vc7-re300dm.pch -Fo./vc7/vc7-re300dm/ -Fdvc7/vc7-re300dm.pdb ../src/wide_posix_api.cpp

vc7-re300dm_dir :
	if not exist "vc7\vc7-re300dm\$(NULL)" mkdir vc7\vc7-re300dm

vc7-re300dm_clean :
	del vc7\vc7-re300dm\*.obj
	del vc7\vc7-re300dm\*.idb
	del vc7\vc7-re300dm\*.exp
	del vc7\vc7-re300dm\*.pch

./vc7/vc7-re300dm.lib : vc7/vc7-re300dm/c_regex_traits.obj vc7/vc7-re300dm/c_regex_traits_common.obj vc7/vc7-re300dm/cpp_regex_traits.obj vc7/vc7-re300dm/cregex.obj vc7/vc7-re300dm/fileiter.obj vc7/vc7-re300dm/posix_api.obj vc7/vc7-re300dm/regex.obj vc7/vc7-re300dm/regex_debug.obj vc7/vc7-re300dm/regex_synch.obj vc7/vc7-re300dm/w32_regex_traits.obj vc7/vc7-re300dm/wide_posix_api.obj
	link -lib /nologo /out:vc7/vc7-re300dm.lib $(XSFLAGS)  vc7/vc7-re300dm/c_regex_traits.obj vc7/vc7-re300dm/c_regex_traits_common.obj vc7/vc7-re300dm/cpp_regex_traits.obj vc7/vc7-re300dm/cregex.obj vc7/vc7-re300dm/fileiter.obj vc7/vc7-re300dm/posix_api.obj vc7/vc7-re300dm/regex.obj vc7/vc7-re300dm/regex_debug.obj vc7/vc7-re300dm/regex_synch.obj vc7/vc7-re300dm/w32_regex_traits.obj vc7/vc7-re300dm/wide_posix_api.obj

########################################################
#
# section for vc7-re300dl.lib
#
########################################################
vc7/vc7-re300dl/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300dl/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300dl/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300dl/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/cregex.cpp

vc7/vc7-re300dl/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/fileiter.cpp

vc7/vc7-re300dl/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/posix_api.cpp

vc7/vc7-re300dl/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/regex.cpp

vc7/vc7-re300dl/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/regex_debug.cpp

vc7/vc7-re300dl/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/regex_synch.cpp

vc7/vc7-re300dl/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300dl/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc7/vc7-re300dl/vc7-re300dl.pch -Fo./vc7/vc7-re300dl/ -Fdvc7/vc7-re300dl.pdb ../src/wide_posix_api.cpp

vc7-re300dl_dir :
	if not exist "vc7\vc7-re300dl\$(NULL)" mkdir vc7\vc7-re300dl

vc7-re300dl_clean :
	del vc7\vc7-re300dl\*.obj
	del vc7\vc7-re300dl\*.idb
	del vc7\vc7-re300dl\*.exp
	del vc7\vc7-re300dl\*.pch

./vc7/vc7-re300dl.lib : vc7/vc7-re300dl/c_regex_traits.obj vc7/vc7-re300dl/c_regex_traits_common.obj vc7/vc7-re300dl/cpp_regex_traits.obj vc7/vc7-re300dl/cregex.obj vc7/vc7-re300dl/fileiter.obj vc7/vc7-re300dl/posix_api.obj vc7/vc7-re300dl/regex.obj vc7/vc7-re300dl/regex_debug.obj vc7/vc7-re300dl/regex_synch.obj vc7/vc7-re300dl/w32_regex_traits.obj vc7/vc7-re300dl/wide_posix_api.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/vc7-re300dl.pdb" /debug /machine:I386 /out:"vc7/vc7-re300dl.dll" /implib:"vc7/vc7-re300dl.lib" $(XLFLAGS)  vc7/vc7-re300dl/c_regex_traits.obj vc7/vc7-re300dl/c_regex_traits_common.obj vc7/vc7-re300dl/cpp_regex_traits.obj vc7/vc7-re300dl/cregex.obj vc7/vc7-re300dl/fileiter.obj vc7/vc7-re300dl/posix_api.obj vc7/vc7-re300dl/regex.obj vc7/vc7-re300dl/regex_debug.obj vc7/vc7-re300dl/regex_synch.obj vc7/vc7-re300dl/w32_regex_traits.obj vc7/vc7-re300dl/wide_posix_api.obj

########################################################
#
# section for vc7-re300l.lib
#
########################################################
vc7/vc7-re300l/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300l/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300l/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300l/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/cregex.cpp

vc7/vc7-re300l/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/fileiter.cpp

vc7/vc7-re300l/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/posix_api.cpp

vc7/vc7-re300l/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/regex.cpp

vc7/vc7-re300l/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/regex_debug.cpp

vc7/vc7-re300l/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/regex_synch.cpp

vc7/vc7-re300l/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300l/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300l/vc7-re300l.pch -Fo./vc7/vc7-re300l/ -Fdvc7/vc7-re300l.pdb ../src/wide_posix_api.cpp

vc7-re300l_dir :
	if not exist "vc7\vc7-re300l\$(NULL)" mkdir vc7\vc7-re300l

vc7-re300l_clean :
	del vc7\vc7-re300l\*.obj
	del vc7\vc7-re300l\*.idb
	del vc7\vc7-re300l\*.exp
	del vc7\vc7-re300l\*.pch

./vc7/vc7-re300l.lib : vc7/vc7-re300l/c_regex_traits.obj vc7/vc7-re300l/c_regex_traits_common.obj vc7/vc7-re300l/cpp_regex_traits.obj vc7/vc7-re300l/cregex.obj vc7/vc7-re300l/fileiter.obj vc7/vc7-re300l/posix_api.obj vc7/vc7-re300l/regex.obj vc7/vc7-re300l/regex_debug.obj vc7/vc7-re300l/regex_synch.obj vc7/vc7-re300l/w32_regex_traits.obj vc7/vc7-re300l/wide_posix_api.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/vc7-re300l.pdb" /debug /machine:I386 /out:"vc7/vc7-re300l.dll" /implib:"vc7/vc7-re300l.lib" $(XLFLAGS)  vc7/vc7-re300l/c_regex_traits.obj vc7/vc7-re300l/c_regex_traits_common.obj vc7/vc7-re300l/cpp_regex_traits.obj vc7/vc7-re300l/cregex.obj vc7/vc7-re300l/fileiter.obj vc7/vc7-re300l/posix_api.obj vc7/vc7-re300l/regex.obj vc7/vc7-re300l/regex_debug.obj vc7/vc7-re300l/regex_synch.obj vc7/vc7-re300l/w32_regex_traits.obj vc7/vc7-re300l/wide_posix_api.obj

########################################################
#
# section for vc7-re300ls.lib
#
########################################################
vc7/vc7-re300ls/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/c_regex_traits.cpp

vc7/vc7-re300ls/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/c_regex_traits_common.cpp

vc7/vc7-re300ls/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/cpp_regex_traits.cpp

vc7/vc7-re300ls/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/cregex.cpp

vc7/vc7-re300ls/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/fileiter.cpp

vc7/vc7-re300ls/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/posix_api.cpp

vc7/vc7-re300ls/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/regex.cpp

vc7/vc7-re300ls/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/regex_debug.cpp

vc7/vc7-re300ls/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/regex_synch.cpp

vc7/vc7-re300ls/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/w32_regex_traits.cpp

vc7/vc7-re300ls/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc7/vc7-re300ls/vc7-re300ls.pch -Fo./vc7/vc7-re300ls/ -Fdvc7/vc7-re300ls.pdb ../src/wide_posix_api.cpp

vc7-re300ls_dir :
	if not exist "vc7\vc7-re300ls\$(NULL)" mkdir vc7\vc7-re300ls

vc7-re300ls_clean :
	del vc7\vc7-re300ls\*.obj
	del vc7\vc7-re300ls\*.idb
	del vc7\vc7-re300ls\*.exp
	del vc7\vc7-re300ls\*.pch

./vc7/vc7-re300ls.lib : vc7/vc7-re300ls/c_regex_traits.obj vc7/vc7-re300ls/c_regex_traits_common.obj vc7/vc7-re300ls/cpp_regex_traits.obj vc7/vc7-re300ls/cregex.obj vc7/vc7-re300ls/fileiter.obj vc7/vc7-re300ls/posix_api.obj vc7/vc7-re300ls/regex.obj vc7/vc7-re300ls/regex_debug.obj vc7/vc7-re300ls/regex_synch.obj vc7/vc7-re300ls/w32_regex_traits.obj vc7/vc7-re300ls/wide_posix_api.obj
	link -lib /nologo /out:vc7/vc7-re300ls.lib $(XSFLAGS)  vc7/vc7-re300ls/c_regex_traits.obj vc7/vc7-re300ls/c_regex_traits_common.obj vc7/vc7-re300ls/cpp_regex_traits.obj vc7/vc7-re300ls/cregex.obj vc7/vc7-re300ls/fileiter.obj vc7/vc7-re300ls/posix_api.obj vc7/vc7-re300ls/regex.obj vc7/vc7-re300ls/regex_debug.obj vc7/vc7-re300ls/regex_synch.obj vc7/vc7-re300ls/w32_regex_traits.obj vc7/vc7-re300ls/wide_posix_api.obj

