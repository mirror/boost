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

all : main_dir vc6-stlport-re300m_dir ./vc6-stlport/vc6-stlport-re300m.lib vc6-stlport-re300dm_dir ./vc6-stlport/vc6-stlport-re300dm.lib vc6-stlport-re300dl_dir ./vc6-stlport/vc6-stlport-re300dl.lib vc6-stlport-re300l_dir ./vc6-stlport/vc6-stlport-re300l.lib vc6-stlport-re300ls_dir ./vc6-stlport/vc6-stlport-re300ls.lib vc6-stlport-re300ddl_dir ./vc6-stlport/vc6-stlport-re300ddl.lib vc6-stlport-re300ddm_dir ./vc6-stlport/vc6-stlport-re300ddm.lib

clean :  vc6-stlport-re300m_clean vc6-stlport-re300dm_clean vc6-stlport-re300dl_clean vc6-stlport-re300l_clean vc6-stlport-re300ls_clean vc6-stlport-re300ddl_clean vc6-stlport-re300ddm_clean

install : all
	copy vc6-stlport\vc6-stlport-re300m.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300dm.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300dl.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300dl.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\vc6-stlport-re300l.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300l.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\vc6-stlport-re300ls.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300ddl.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300ddl.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\vc6-stlport-re300ddl.pdb "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300ddm.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\vc6-stlport-re300ddm.pdb "$(MSVCDIR)\lib"

main_dir :
	if not exist "vc6-stlport\$(NULL)" mkdir vc6-stlport


########################################################
#
# section for vc6-stlport-re300m.lib
#
########################################################
vc6-stlport/vc6-stlport-re300m/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300m/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300m/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300m/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300m/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300m/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300m/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300m/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300m/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300m/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300m/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300m/vc6-stlport-re300m.pch -Fo./vc6-stlport/vc6-stlport-re300m/ -Fdvc6-stlport/vc6-stlport-re300m.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300m_dir :
	if not exist "vc6-stlport\vc6-stlport-re300m\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300m

vc6-stlport-re300m_clean :
	del vc6-stlport\vc6-stlport-re300m\*.obj
	del vc6-stlport\vc6-stlport-re300m\*.idb
	del vc6-stlport\vc6-stlport-re300m\*.exp
	del vc6-stlport\vc6-stlport-re300m\*.pch

./vc6-stlport/vc6-stlport-re300m.lib : vc6-stlport/vc6-stlport-re300m/c_regex_traits.obj vc6-stlport/vc6-stlport-re300m/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300m/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300m/cregex.obj vc6-stlport/vc6-stlport-re300m/fileiter.obj vc6-stlport/vc6-stlport-re300m/posix_api.obj vc6-stlport/vc6-stlport-re300m/regex.obj vc6-stlport/vc6-stlport-re300m/regex_debug.obj vc6-stlport/vc6-stlport-re300m/regex_synch.obj vc6-stlport/vc6-stlport-re300m/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300m/wide_posix_api.obj
	link -lib /nologo /out:vc6-stlport/vc6-stlport-re300m.lib $(XSFLAGS)  vc6-stlport/vc6-stlport-re300m/c_regex_traits.obj vc6-stlport/vc6-stlport-re300m/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300m/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300m/cregex.obj vc6-stlport/vc6-stlport-re300m/fileiter.obj vc6-stlport/vc6-stlport-re300m/posix_api.obj vc6-stlport/vc6-stlport-re300m/regex.obj vc6-stlport/vc6-stlport-re300m/regex_debug.obj vc6-stlport/vc6-stlport-re300m/regex_synch.obj vc6-stlport/vc6-stlport-re300m/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300m/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300dm.lib
#
########################################################
vc6-stlport/vc6-stlport-re300dm/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dm/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300dm/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dm/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300dm/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300dm/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300dm/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300dm/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300dm/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300dm/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dm/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dm/vc6-stlport-re300dm.pch -Fo./vc6-stlport/vc6-stlport-re300dm/ -Fdvc6-stlport/vc6-stlport-re300dm.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300dm_dir :
	if not exist "vc6-stlport\vc6-stlport-re300dm\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300dm

vc6-stlport-re300dm_clean :
	del vc6-stlport\vc6-stlport-re300dm\*.obj
	del vc6-stlport\vc6-stlport-re300dm\*.idb
	del vc6-stlport\vc6-stlport-re300dm\*.exp
	del vc6-stlport\vc6-stlport-re300dm\*.pch

./vc6-stlport/vc6-stlport-re300dm.lib : vc6-stlport/vc6-stlport-re300dm/c_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300dm/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/cregex.obj vc6-stlport/vc6-stlport-re300dm/fileiter.obj vc6-stlport/vc6-stlport-re300dm/posix_api.obj vc6-stlport/vc6-stlport-re300dm/regex.obj vc6-stlport/vc6-stlport-re300dm/regex_debug.obj vc6-stlport/vc6-stlport-re300dm/regex_synch.obj vc6-stlport/vc6-stlport-re300dm/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/wide_posix_api.obj
	link -lib /nologo /out:vc6-stlport/vc6-stlport-re300dm.lib $(XSFLAGS)  vc6-stlport/vc6-stlport-re300dm/c_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300dm/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/cregex.obj vc6-stlport/vc6-stlport-re300dm/fileiter.obj vc6-stlport/vc6-stlport-re300dm/posix_api.obj vc6-stlport/vc6-stlport-re300dm/regex.obj vc6-stlport/vc6-stlport-re300dm/regex_debug.obj vc6-stlport/vc6-stlport-re300dm/regex_synch.obj vc6-stlport/vc6-stlport-re300dm/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300dm/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300dl.lib
#
########################################################
vc6-stlport/vc6-stlport-re300dl/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dl/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300dl/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dl/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300dl/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300dl/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300dl/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300dl/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300dl/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300dl/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300dl/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300dl/vc6-stlport-re300dl.pch -Fo./vc6-stlport/vc6-stlport-re300dl/ -Fdvc6-stlport/vc6-stlport-re300dl.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300dl_dir :
	if not exist "vc6-stlport\vc6-stlport-re300dl\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300dl

vc6-stlport-re300dl_clean :
	del vc6-stlport\vc6-stlport-re300dl\*.obj
	del vc6-stlport\vc6-stlport-re300dl\*.idb
	del vc6-stlport\vc6-stlport-re300dl\*.exp
	del vc6-stlport\vc6-stlport-re300dl\*.pch

./vc6-stlport/vc6-stlport-re300dl.lib : vc6-stlport/vc6-stlport-re300dl/c_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300dl/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/cregex.obj vc6-stlport/vc6-stlport-re300dl/fileiter.obj vc6-stlport/vc6-stlport-re300dl/posix_api.obj vc6-stlport/vc6-stlport-re300dl/regex.obj vc6-stlport/vc6-stlport-re300dl/regex_debug.obj vc6-stlport/vc6-stlport-re300dl/regex_synch.obj vc6-stlport/vc6-stlport-re300dl/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/wide_posix_api.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/vc6-stlport-re300dl.pdb" /debug /machine:I386 /out:"vc6-stlport/vc6-stlport-re300dl.dll" /implib:"vc6-stlport/vc6-stlport-re300dl.lib" $(XLFLAGS)  vc6-stlport/vc6-stlport-re300dl/c_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300dl/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/cregex.obj vc6-stlport/vc6-stlport-re300dl/fileiter.obj vc6-stlport/vc6-stlport-re300dl/posix_api.obj vc6-stlport/vc6-stlport-re300dl/regex.obj vc6-stlport/vc6-stlport-re300dl/regex_debug.obj vc6-stlport/vc6-stlport-re300dl/regex_synch.obj vc6-stlport/vc6-stlport-re300dl/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300dl/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300l.lib
#
########################################################
vc6-stlport/vc6-stlport-re300l/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300l/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300l/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300l/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300l/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300l/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300l/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300l/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300l/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300l/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300l/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300l/vc6-stlport-re300l.pch -Fo./vc6-stlport/vc6-stlport-re300l/ -Fdvc6-stlport/vc6-stlport-re300l.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300l_dir :
	if not exist "vc6-stlport\vc6-stlport-re300l\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300l

vc6-stlport-re300l_clean :
	del vc6-stlport\vc6-stlport-re300l\*.obj
	del vc6-stlport\vc6-stlport-re300l\*.idb
	del vc6-stlport\vc6-stlport-re300l\*.exp
	del vc6-stlport\vc6-stlport-re300l\*.pch

./vc6-stlport/vc6-stlport-re300l.lib : vc6-stlport/vc6-stlport-re300l/c_regex_traits.obj vc6-stlport/vc6-stlport-re300l/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300l/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300l/cregex.obj vc6-stlport/vc6-stlport-re300l/fileiter.obj vc6-stlport/vc6-stlport-re300l/posix_api.obj vc6-stlport/vc6-stlport-re300l/regex.obj vc6-stlport/vc6-stlport-re300l/regex_debug.obj vc6-stlport/vc6-stlport-re300l/regex_synch.obj vc6-stlport/vc6-stlport-re300l/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300l/wide_posix_api.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/vc6-stlport-re300l.pdb" /debug /machine:I386 /out:"vc6-stlport/vc6-stlport-re300l.dll" /implib:"vc6-stlport/vc6-stlport-re300l.lib" $(XLFLAGS)  vc6-stlport/vc6-stlport-re300l/c_regex_traits.obj vc6-stlport/vc6-stlport-re300l/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300l/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300l/cregex.obj vc6-stlport/vc6-stlport-re300l/fileiter.obj vc6-stlport/vc6-stlport-re300l/posix_api.obj vc6-stlport/vc6-stlport-re300l/regex.obj vc6-stlport/vc6-stlport-re300l/regex_debug.obj vc6-stlport/vc6-stlport-re300l/regex_synch.obj vc6-stlport/vc6-stlport-re300l/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300l/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300ls.lib
#
########################################################
vc6-stlport/vc6-stlport-re300ls/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ls/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300ls/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ls/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300ls/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300ls/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300ls/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300ls/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300ls/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300ls/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ls/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ls/vc6-stlport-re300ls.pch -Fo./vc6-stlport/vc6-stlport-re300ls/ -Fdvc6-stlport/vc6-stlport-re300ls.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300ls_dir :
	if not exist "vc6-stlport\vc6-stlport-re300ls\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300ls

vc6-stlport-re300ls_clean :
	del vc6-stlport\vc6-stlport-re300ls\*.obj
	del vc6-stlport\vc6-stlport-re300ls\*.idb
	del vc6-stlport\vc6-stlport-re300ls\*.exp
	del vc6-stlport\vc6-stlport-re300ls\*.pch

./vc6-stlport/vc6-stlport-re300ls.lib : vc6-stlport/vc6-stlport-re300ls/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ls/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/cregex.obj vc6-stlport/vc6-stlport-re300ls/fileiter.obj vc6-stlport/vc6-stlport-re300ls/posix_api.obj vc6-stlport/vc6-stlport-re300ls/regex.obj vc6-stlport/vc6-stlport-re300ls/regex_debug.obj vc6-stlport/vc6-stlport-re300ls/regex_synch.obj vc6-stlport/vc6-stlport-re300ls/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/wide_posix_api.obj
	link -lib /nologo /out:vc6-stlport/vc6-stlport-re300ls.lib $(XSFLAGS)  vc6-stlport/vc6-stlport-re300ls/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ls/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/cregex.obj vc6-stlport/vc6-stlport-re300ls/fileiter.obj vc6-stlport/vc6-stlport-re300ls/posix_api.obj vc6-stlport/vc6-stlport-re300ls/regex.obj vc6-stlport/vc6-stlport-re300ls/regex_debug.obj vc6-stlport/vc6-stlport-re300ls/regex_synch.obj vc6-stlport/vc6-stlport-re300ls/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ls/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300ddl.lib
#
########################################################
vc6-stlport/vc6-stlport-re300ddl/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddl/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300ddl/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddl/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300ddl/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300ddl/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300ddl/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300ddl/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300ddl/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300ddl/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddl/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D__STL_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddl/vc6-stlport-re300ddl.pch -Fo./vc6-stlport/vc6-stlport-re300ddl/ -Fdvc6-stlport/vc6-stlport-re300ddl.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300ddl_dir :
	if not exist "vc6-stlport\vc6-stlport-re300ddl\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300ddl

vc6-stlport-re300ddl_clean :
	del vc6-stlport\vc6-stlport-re300ddl\*.obj
	del vc6-stlport\vc6-stlport-re300ddl\*.idb
	del vc6-stlport\vc6-stlport-re300ddl\*.exp
	del vc6-stlport\vc6-stlport-re300ddl\*.pch

./vc6-stlport/vc6-stlport-re300ddl.lib : vc6-stlport/vc6-stlport-re300ddl/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ddl/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/cregex.obj vc6-stlport/vc6-stlport-re300ddl/fileiter.obj vc6-stlport/vc6-stlport-re300ddl/posix_api.obj vc6-stlport/vc6-stlport-re300ddl/regex.obj vc6-stlport/vc6-stlport-re300ddl/regex_debug.obj vc6-stlport/vc6-stlport-re300ddl/regex_synch.obj vc6-stlport/vc6-stlport-re300ddl/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/wide_posix_api.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/vc6-stlport-re300ddl.pdb" /debug /machine:I386 /out:"vc6-stlport/vc6-stlport-re300ddl.dll" /implib:"vc6-stlport/vc6-stlport-re300ddl.lib" $(XLFLAGS)  vc6-stlport/vc6-stlport-re300ddl/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ddl/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/cregex.obj vc6-stlport/vc6-stlport-re300ddl/fileiter.obj vc6-stlport/vc6-stlport-re300ddl/posix_api.obj vc6-stlport/vc6-stlport-re300ddl/regex.obj vc6-stlport/vc6-stlport-re300ddl/regex_debug.obj vc6-stlport/vc6-stlport-re300ddl/regex_synch.obj vc6-stlport/vc6-stlport-re300ddl/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ddl/wide_posix_api.obj

########################################################
#
# section for vc6-stlport-re300ddm.lib
#
########################################################
vc6-stlport/vc6-stlport-re300ddm/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/c_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddm/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/vc6-stlport-re300ddm/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddm/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/cregex.cpp

vc6-stlport/vc6-stlport-re300ddm/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/fileiter.cpp

vc6-stlport/vc6-stlport-re300ddm/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/posix_api.cpp

vc6-stlport/vc6-stlport-re300ddm/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/regex.cpp

vc6-stlport/vc6-stlport-re300ddm/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/regex_debug.cpp

vc6-stlport/vc6-stlport-re300ddm/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/regex_synch.cpp

vc6-stlport/vc6-stlport-re300ddm/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/w32_regex_traits.cpp

vc6-stlport/vc6-stlport-re300ddm/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /D__STL_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/vc6-stlport-re300ddm/vc6-stlport-re300ddm.pch -Fo./vc6-stlport/vc6-stlport-re300ddm/ -Fdvc6-stlport/vc6-stlport-re300ddm.pdb ../src/wide_posix_api.cpp

vc6-stlport-re300ddm_dir :
	if not exist "vc6-stlport\vc6-stlport-re300ddm\$(NULL)" mkdir vc6-stlport\vc6-stlport-re300ddm

vc6-stlport-re300ddm_clean :
	del vc6-stlport\vc6-stlport-re300ddm\*.obj
	del vc6-stlport\vc6-stlport-re300ddm\*.idb
	del vc6-stlport\vc6-stlport-re300ddm\*.exp
	del vc6-stlport\vc6-stlport-re300ddm\*.pch

./vc6-stlport/vc6-stlport-re300ddm.lib : vc6-stlport/vc6-stlport-re300ddm/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ddm/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/cregex.obj vc6-stlport/vc6-stlport-re300ddm/fileiter.obj vc6-stlport/vc6-stlport-re300ddm/posix_api.obj vc6-stlport/vc6-stlport-re300ddm/regex.obj vc6-stlport/vc6-stlport-re300ddm/regex_debug.obj vc6-stlport/vc6-stlport-re300ddm/regex_synch.obj vc6-stlport/vc6-stlport-re300ddm/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/wide_posix_api.obj
	link -lib /nologo /out:vc6-stlport/vc6-stlport-re300ddm.lib $(XSFLAGS)  vc6-stlport/vc6-stlport-re300ddm/c_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/c_regex_traits_common.obj vc6-stlport/vc6-stlport-re300ddm/cpp_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/cregex.obj vc6-stlport/vc6-stlport-re300ddm/fileiter.obj vc6-stlport/vc6-stlport-re300ddm/posix_api.obj vc6-stlport/vc6-stlport-re300ddm/regex.obj vc6-stlport/vc6-stlport-re300ddm/regex_debug.obj vc6-stlport/vc6-stlport-re300ddm/regex_synch.obj vc6-stlport/vc6-stlport-re300ddm/w32_regex_traits.obj vc6-stlport/vc6-stlport-re300ddm/wide_posix_api.obj

