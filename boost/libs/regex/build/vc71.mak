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


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp

all : main_dir boost_regex_vc71_sss_dir ./vc71/boost_regex_vc71_sss.lib boost_regex_vc71_mss_dir ./vc71/boost_regex_vc71_mss.lib boost_regex_vc71_sssd_dir ./vc71/boost_regex_vc71_sssd.lib boost_regex_vc71_mssd_dir ./vc71/boost_regex_vc71_mssd.lib boost_regex_vc71_mdid_dir ./vc71/boost_regex_vc71_mdid.lib boost_regex_vc71_mdi_dir ./vc71/boost_regex_vc71_mdi.lib boost_regex_vc71_mds_dir ./vc71/boost_regex_vc71_mds.lib boost_regex_vc71_mdsd_dir ./vc71/boost_regex_vc71_mdsd.lib

clean :  boost_regex_vc71_sss_clean boost_regex_vc71_mss_clean boost_regex_vc71_sssd_clean boost_regex_vc71_mssd_clean boost_regex_vc71_mdid_clean boost_regex_vc71_mdi_clean boost_regex_vc71_mds_clean boost_regex_vc71_mdsd_clean

install : all
	copy vc71\boost_regex_vc71_sss.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mss.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_sssd.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_sssd.pdb "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mssd.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mssd.pdb "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdid.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdid.dll "$(MSVCDIR)\bin"
	copy vc71\boost_regex_vc71_mdid.pdb "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdi.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdi.dll "$(MSVCDIR)\bin"
	copy vc71\boost_regex_vc71_mds.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdsd.lib "$(MSVCDIR)\lib"
	copy vc71\boost_regex_vc71_mdsd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc71\$(NULL)" mkdir vc71


########################################################
#
# section for boost_regex_vc71_sss.lib
#
########################################################
vc71/boost_regex_vc71_sss/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_sss/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_sss/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_sss/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_sss/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_sss/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/instances.cpp

vc71/boost_regex_vc71_sss/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_sss/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/regex.cpp

vc71/boost_regex_vc71_sss/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_sss/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_sss/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_sss/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_sss/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /c /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sss/boost_regex_vc71_sss.pch -Fo./vc71/boost_regex_vc71_sss/ -Fdvc71/boost_regex_vc71_sss.pdb ../src/winstances.cpp

boost_regex_vc71_sss_dir :
	@if not exist "vc71\boost_regex_vc71_sss\$(NULL)" mkdir vc71\boost_regex_vc71_sss

boost_regex_vc71_sss_clean :
	del vc71\boost_regex_vc71_sss\*.obj
	del vc71\boost_regex_vc71_sss\*.idb
	del vc71\boost_regex_vc71_sss\*.exp
	del vc71\boost_regex_vc71_sss\*.pch

./vc71/boost_regex_vc71_sss.lib : vc71/boost_regex_vc71_sss/c_regex_traits.obj vc71/boost_regex_vc71_sss/c_regex_traits_common.obj vc71/boost_regex_vc71_sss/cpp_regex_traits.obj vc71/boost_regex_vc71_sss/cregex.obj vc71/boost_regex_vc71_sss/fileiter.obj vc71/boost_regex_vc71_sss/instances.obj vc71/boost_regex_vc71_sss/posix_api.obj vc71/boost_regex_vc71_sss/regex.obj vc71/boost_regex_vc71_sss/regex_debug.obj vc71/boost_regex_vc71_sss/regex_synch.obj vc71/boost_regex_vc71_sss/w32_regex_traits.obj vc71/boost_regex_vc71_sss/wide_posix_api.obj vc71/boost_regex_vc71_sss/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_sss.lib $(XSFLAGS)  vc71/boost_regex_vc71_sss/c_regex_traits.obj vc71/boost_regex_vc71_sss/c_regex_traits_common.obj vc71/boost_regex_vc71_sss/cpp_regex_traits.obj vc71/boost_regex_vc71_sss/cregex.obj vc71/boost_regex_vc71_sss/fileiter.obj vc71/boost_regex_vc71_sss/instances.obj vc71/boost_regex_vc71_sss/posix_api.obj vc71/boost_regex_vc71_sss/regex.obj vc71/boost_regex_vc71_sss/regex_debug.obj vc71/boost_regex_vc71_sss/regex_synch.obj vc71/boost_regex_vc71_sss/w32_regex_traits.obj vc71/boost_regex_vc71_sss/wide_posix_api.obj vc71/boost_regex_vc71_sss/winstances.obj

########################################################
#
# section for boost_regex_vc71_mss.lib
#
########################################################
vc71/boost_regex_vc71_mss/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mss/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mss/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mss/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mss/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mss/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mss/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mss/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mss/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mss/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mss/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mss/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mss/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mss/boost_regex_vc71_mss.pch -Fo./vc71/boost_regex_vc71_mss/ -Fdvc71/boost_regex_vc71_mss.pdb ../src/winstances.cpp

boost_regex_vc71_mss_dir :
	@if not exist "vc71\boost_regex_vc71_mss\$(NULL)" mkdir vc71\boost_regex_vc71_mss

boost_regex_vc71_mss_clean :
	del vc71\boost_regex_vc71_mss\*.obj
	del vc71\boost_regex_vc71_mss\*.idb
	del vc71\boost_regex_vc71_mss\*.exp
	del vc71\boost_regex_vc71_mss\*.pch

./vc71/boost_regex_vc71_mss.lib : vc71/boost_regex_vc71_mss/c_regex_traits.obj vc71/boost_regex_vc71_mss/c_regex_traits_common.obj vc71/boost_regex_vc71_mss/cpp_regex_traits.obj vc71/boost_regex_vc71_mss/cregex.obj vc71/boost_regex_vc71_mss/fileiter.obj vc71/boost_regex_vc71_mss/instances.obj vc71/boost_regex_vc71_mss/posix_api.obj vc71/boost_regex_vc71_mss/regex.obj vc71/boost_regex_vc71_mss/regex_debug.obj vc71/boost_regex_vc71_mss/regex_synch.obj vc71/boost_regex_vc71_mss/w32_regex_traits.obj vc71/boost_regex_vc71_mss/wide_posix_api.obj vc71/boost_regex_vc71_mss/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_mss.lib $(XSFLAGS)  vc71/boost_regex_vc71_mss/c_regex_traits.obj vc71/boost_regex_vc71_mss/c_regex_traits_common.obj vc71/boost_regex_vc71_mss/cpp_regex_traits.obj vc71/boost_regex_vc71_mss/cregex.obj vc71/boost_regex_vc71_mss/fileiter.obj vc71/boost_regex_vc71_mss/instances.obj vc71/boost_regex_vc71_mss/posix_api.obj vc71/boost_regex_vc71_mss/regex.obj vc71/boost_regex_vc71_mss/regex_debug.obj vc71/boost_regex_vc71_mss/regex_synch.obj vc71/boost_regex_vc71_mss/w32_regex_traits.obj vc71/boost_regex_vc71_mss/wide_posix_api.obj vc71/boost_regex_vc71_mss/winstances.obj

########################################################
#
# section for boost_regex_vc71_sssd.lib
#
########################################################
vc71/boost_regex_vc71_sssd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_sssd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_sssd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_sssd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_sssd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_sssd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/instances.cpp

vc71/boost_regex_vc71_sssd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_sssd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/regex.cpp

vc71/boost_regex_vc71_sssd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_sssd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_sssd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_sssd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_sssd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c  $(CXXFLAGS) -Fpvc71/boost_regex_vc71_sssd/boost_regex_vc71_sssd.pch -Fo./vc71/boost_regex_vc71_sssd/ -Fdvc71/boost_regex_vc71_sssd.pdb ../src/winstances.cpp

boost_regex_vc71_sssd_dir :
	@if not exist "vc71\boost_regex_vc71_sssd\$(NULL)" mkdir vc71\boost_regex_vc71_sssd

boost_regex_vc71_sssd_clean :
	del vc71\boost_regex_vc71_sssd\*.obj
	del vc71\boost_regex_vc71_sssd\*.idb
	del vc71\boost_regex_vc71_sssd\*.exp
	del vc71\boost_regex_vc71_sssd\*.pch

./vc71/boost_regex_vc71_sssd.lib : vc71/boost_regex_vc71_sssd/c_regex_traits.obj vc71/boost_regex_vc71_sssd/c_regex_traits_common.obj vc71/boost_regex_vc71_sssd/cpp_regex_traits.obj vc71/boost_regex_vc71_sssd/cregex.obj vc71/boost_regex_vc71_sssd/fileiter.obj vc71/boost_regex_vc71_sssd/instances.obj vc71/boost_regex_vc71_sssd/posix_api.obj vc71/boost_regex_vc71_sssd/regex.obj vc71/boost_regex_vc71_sssd/regex_debug.obj vc71/boost_regex_vc71_sssd/regex_synch.obj vc71/boost_regex_vc71_sssd/w32_regex_traits.obj vc71/boost_regex_vc71_sssd/wide_posix_api.obj vc71/boost_regex_vc71_sssd/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_sssd.lib $(XSFLAGS)  vc71/boost_regex_vc71_sssd/c_regex_traits.obj vc71/boost_regex_vc71_sssd/c_regex_traits_common.obj vc71/boost_regex_vc71_sssd/cpp_regex_traits.obj vc71/boost_regex_vc71_sssd/cregex.obj vc71/boost_regex_vc71_sssd/fileiter.obj vc71/boost_regex_vc71_sssd/instances.obj vc71/boost_regex_vc71_sssd/posix_api.obj vc71/boost_regex_vc71_sssd/regex.obj vc71/boost_regex_vc71_sssd/regex_debug.obj vc71/boost_regex_vc71_sssd/regex_synch.obj vc71/boost_regex_vc71_sssd/w32_regex_traits.obj vc71/boost_regex_vc71_sssd/wide_posix_api.obj vc71/boost_regex_vc71_sssd/winstances.obj

########################################################
#
# section for boost_regex_vc71_mssd.lib
#
########################################################
vc71/boost_regex_vc71_mssd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mssd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mssd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mssd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mssd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mssd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mssd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mssd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mssd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mssd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mssd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mssd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mssd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mssd/boost_regex_vc71_mssd.pch -Fo./vc71/boost_regex_vc71_mssd/ -Fdvc71/boost_regex_vc71_mssd.pdb ../src/winstances.cpp

boost_regex_vc71_mssd_dir :
	@if not exist "vc71\boost_regex_vc71_mssd\$(NULL)" mkdir vc71\boost_regex_vc71_mssd

boost_regex_vc71_mssd_clean :
	del vc71\boost_regex_vc71_mssd\*.obj
	del vc71\boost_regex_vc71_mssd\*.idb
	del vc71\boost_regex_vc71_mssd\*.exp
	del vc71\boost_regex_vc71_mssd\*.pch

./vc71/boost_regex_vc71_mssd.lib : vc71/boost_regex_vc71_mssd/c_regex_traits.obj vc71/boost_regex_vc71_mssd/c_regex_traits_common.obj vc71/boost_regex_vc71_mssd/cpp_regex_traits.obj vc71/boost_regex_vc71_mssd/cregex.obj vc71/boost_regex_vc71_mssd/fileiter.obj vc71/boost_regex_vc71_mssd/instances.obj vc71/boost_regex_vc71_mssd/posix_api.obj vc71/boost_regex_vc71_mssd/regex.obj vc71/boost_regex_vc71_mssd/regex_debug.obj vc71/boost_regex_vc71_mssd/regex_synch.obj vc71/boost_regex_vc71_mssd/w32_regex_traits.obj vc71/boost_regex_vc71_mssd/wide_posix_api.obj vc71/boost_regex_vc71_mssd/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_mssd.lib $(XSFLAGS)  vc71/boost_regex_vc71_mssd/c_regex_traits.obj vc71/boost_regex_vc71_mssd/c_regex_traits_common.obj vc71/boost_regex_vc71_mssd/cpp_regex_traits.obj vc71/boost_regex_vc71_mssd/cregex.obj vc71/boost_regex_vc71_mssd/fileiter.obj vc71/boost_regex_vc71_mssd/instances.obj vc71/boost_regex_vc71_mssd/posix_api.obj vc71/boost_regex_vc71_mssd/regex.obj vc71/boost_regex_vc71_mssd/regex_debug.obj vc71/boost_regex_vc71_mssd/regex_synch.obj vc71/boost_regex_vc71_mssd/w32_regex_traits.obj vc71/boost_regex_vc71_mssd/wide_posix_api.obj vc71/boost_regex_vc71_mssd/winstances.obj

########################################################
#
# section for boost_regex_vc71_mdid.lib
#
########################################################
vc71/boost_regex_vc71_mdid/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mdid/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mdid/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mdid/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mdid/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mdid/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mdid/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mdid/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mdid/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mdid/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mdid/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mdid/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mdid/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdid/boost_regex_vc71_mdid.pch -Fo./vc71/boost_regex_vc71_mdid/ -Fdvc71/boost_regex_vc71_mdid.pdb ../src/winstances.cpp

boost_regex_vc71_mdid_dir :
	@if not exist "vc71\boost_regex_vc71_mdid\$(NULL)" mkdir vc71\boost_regex_vc71_mdid

boost_regex_vc71_mdid_clean :
	del vc71\boost_regex_vc71_mdid\*.obj
	del vc71\boost_regex_vc71_mdid\*.idb
	del vc71\boost_regex_vc71_mdid\*.exp
	del vc71\boost_regex_vc71_mdid\*.pch

./vc71/boost_regex_vc71_mdid.lib : vc71/boost_regex_vc71_mdid/c_regex_traits.obj vc71/boost_regex_vc71_mdid/c_regex_traits_common.obj vc71/boost_regex_vc71_mdid/cpp_regex_traits.obj vc71/boost_regex_vc71_mdid/cregex.obj vc71/boost_regex_vc71_mdid/fileiter.obj vc71/boost_regex_vc71_mdid/instances.obj vc71/boost_regex_vc71_mdid/posix_api.obj vc71/boost_regex_vc71_mdid/regex.obj vc71/boost_regex_vc71_mdid/regex_debug.obj vc71/boost_regex_vc71_mdid/regex_synch.obj vc71/boost_regex_vc71_mdid/w32_regex_traits.obj vc71/boost_regex_vc71_mdid/wide_posix_api.obj vc71/boost_regex_vc71_mdid/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/boost_regex_vc71_mdid.pdb" /debug /machine:I386 /out:"vc71/boost_regex_vc71_mdid.dll" /implib:"vc71/boost_regex_vc71_mdid.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/boost_regex_vc71_mdid/c_regex_traits.obj vc71/boost_regex_vc71_mdid/c_regex_traits_common.obj vc71/boost_regex_vc71_mdid/cpp_regex_traits.obj vc71/boost_regex_vc71_mdid/cregex.obj vc71/boost_regex_vc71_mdid/fileiter.obj vc71/boost_regex_vc71_mdid/instances.obj vc71/boost_regex_vc71_mdid/posix_api.obj vc71/boost_regex_vc71_mdid/regex.obj vc71/boost_regex_vc71_mdid/regex_debug.obj vc71/boost_regex_vc71_mdid/regex_synch.obj vc71/boost_regex_vc71_mdid/w32_regex_traits.obj vc71/boost_regex_vc71_mdid/wide_posix_api.obj vc71/boost_regex_vc71_mdid/winstances.obj

########################################################
#
# section for boost_regex_vc71_mdi.lib
#
########################################################
vc71/boost_regex_vc71_mdi/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mdi/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mdi/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mdi/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mdi/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mdi/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mdi/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mdi/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mdi/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mdi/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mdi/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mdi/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mdi/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdi/boost_regex_vc71_mdi.pch -Fo./vc71/boost_regex_vc71_mdi/ -Fdvc71/boost_regex_vc71_mdi.pdb ../src/winstances.cpp

boost_regex_vc71_mdi_dir :
	@if not exist "vc71\boost_regex_vc71_mdi\$(NULL)" mkdir vc71\boost_regex_vc71_mdi

boost_regex_vc71_mdi_clean :
	del vc71\boost_regex_vc71_mdi\*.obj
	del vc71\boost_regex_vc71_mdi\*.idb
	del vc71\boost_regex_vc71_mdi\*.exp
	del vc71\boost_regex_vc71_mdi\*.pch

./vc71/boost_regex_vc71_mdi.lib : vc71/boost_regex_vc71_mdi/c_regex_traits.obj vc71/boost_regex_vc71_mdi/c_regex_traits_common.obj vc71/boost_regex_vc71_mdi/cpp_regex_traits.obj vc71/boost_regex_vc71_mdi/cregex.obj vc71/boost_regex_vc71_mdi/fileiter.obj vc71/boost_regex_vc71_mdi/instances.obj vc71/boost_regex_vc71_mdi/posix_api.obj vc71/boost_regex_vc71_mdi/regex.obj vc71/boost_regex_vc71_mdi/regex_debug.obj vc71/boost_regex_vc71_mdi/regex_synch.obj vc71/boost_regex_vc71_mdi/w32_regex_traits.obj vc71/boost_regex_vc71_mdi/wide_posix_api.obj vc71/boost_regex_vc71_mdi/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/boost_regex_vc71_mdi.pdb" /debug /machine:I386 /out:"vc71/boost_regex_vc71_mdi.dll" /implib:"vc71/boost_regex_vc71_mdi.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/boost_regex_vc71_mdi/c_regex_traits.obj vc71/boost_regex_vc71_mdi/c_regex_traits_common.obj vc71/boost_regex_vc71_mdi/cpp_regex_traits.obj vc71/boost_regex_vc71_mdi/cregex.obj vc71/boost_regex_vc71_mdi/fileiter.obj vc71/boost_regex_vc71_mdi/instances.obj vc71/boost_regex_vc71_mdi/posix_api.obj vc71/boost_regex_vc71_mdi/regex.obj vc71/boost_regex_vc71_mdi/regex_debug.obj vc71/boost_regex_vc71_mdi/regex_synch.obj vc71/boost_regex_vc71_mdi/w32_regex_traits.obj vc71/boost_regex_vc71_mdi/wide_posix_api.obj vc71/boost_regex_vc71_mdi/winstances.obj

########################################################
#
# section for boost_regex_vc71_mds.lib
#
########################################################
vc71/boost_regex_vc71_mds/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mds/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mds/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mds/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mds/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mds/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mds/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mds/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mds/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mds/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mds/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mds/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mds/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mds/boost_regex_vc71_mds.pch -Fo./vc71/boost_regex_vc71_mds/ -Fdvc71/boost_regex_vc71_mds.pdb ../src/winstances.cpp

boost_regex_vc71_mds_dir :
	@if not exist "vc71\boost_regex_vc71_mds\$(NULL)" mkdir vc71\boost_regex_vc71_mds

boost_regex_vc71_mds_clean :
	del vc71\boost_regex_vc71_mds\*.obj
	del vc71\boost_regex_vc71_mds\*.idb
	del vc71\boost_regex_vc71_mds\*.exp
	del vc71\boost_regex_vc71_mds\*.pch

./vc71/boost_regex_vc71_mds.lib : vc71/boost_regex_vc71_mds/c_regex_traits.obj vc71/boost_regex_vc71_mds/c_regex_traits_common.obj vc71/boost_regex_vc71_mds/cpp_regex_traits.obj vc71/boost_regex_vc71_mds/cregex.obj vc71/boost_regex_vc71_mds/fileiter.obj vc71/boost_regex_vc71_mds/instances.obj vc71/boost_regex_vc71_mds/posix_api.obj vc71/boost_regex_vc71_mds/regex.obj vc71/boost_regex_vc71_mds/regex_debug.obj vc71/boost_regex_vc71_mds/regex_synch.obj vc71/boost_regex_vc71_mds/w32_regex_traits.obj vc71/boost_regex_vc71_mds/wide_posix_api.obj vc71/boost_regex_vc71_mds/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_mds.lib $(XSFLAGS)  vc71/boost_regex_vc71_mds/c_regex_traits.obj vc71/boost_regex_vc71_mds/c_regex_traits_common.obj vc71/boost_regex_vc71_mds/cpp_regex_traits.obj vc71/boost_regex_vc71_mds/cregex.obj vc71/boost_regex_vc71_mds/fileiter.obj vc71/boost_regex_vc71_mds/instances.obj vc71/boost_regex_vc71_mds/posix_api.obj vc71/boost_regex_vc71_mds/regex.obj vc71/boost_regex_vc71_mds/regex_debug.obj vc71/boost_regex_vc71_mds/regex_synch.obj vc71/boost_regex_vc71_mds/w32_regex_traits.obj vc71/boost_regex_vc71_mds/wide_posix_api.obj vc71/boost_regex_vc71_mds/winstances.obj

########################################################
#
# section for boost_regex_vc71_mdsd.lib
#
########################################################
vc71/boost_regex_vc71_mdsd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/c_regex_traits.cpp

vc71/boost_regex_vc71_mdsd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/c_regex_traits_common.cpp

vc71/boost_regex_vc71_mdsd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/cpp_regex_traits.cpp

vc71/boost_regex_vc71_mdsd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/cregex.cpp

vc71/boost_regex_vc71_mdsd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/fileiter.cpp

vc71/boost_regex_vc71_mdsd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/instances.cpp

vc71/boost_regex_vc71_mdsd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/posix_api.cpp

vc71/boost_regex_vc71_mdsd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/regex.cpp

vc71/boost_regex_vc71_mdsd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/regex_debug.cpp

vc71/boost_regex_vc71_mdsd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/regex_synch.cpp

vc71/boost_regex_vc71_mdsd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/w32_regex_traits.cpp

vc71/boost_regex_vc71_mdsd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/wide_posix_api.cpp

vc71/boost_regex_vc71_mdsd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc71/boost_regex_vc71_mdsd/boost_regex_vc71_mdsd.pch -Fo./vc71/boost_regex_vc71_mdsd/ -Fdvc71/boost_regex_vc71_mdsd.pdb ../src/winstances.cpp

boost_regex_vc71_mdsd_dir :
	@if not exist "vc71\boost_regex_vc71_mdsd\$(NULL)" mkdir vc71\boost_regex_vc71_mdsd

boost_regex_vc71_mdsd_clean :
	del vc71\boost_regex_vc71_mdsd\*.obj
	del vc71\boost_regex_vc71_mdsd\*.idb
	del vc71\boost_regex_vc71_mdsd\*.exp
	del vc71\boost_regex_vc71_mdsd\*.pch

./vc71/boost_regex_vc71_mdsd.lib : vc71/boost_regex_vc71_mdsd/c_regex_traits.obj vc71/boost_regex_vc71_mdsd/c_regex_traits_common.obj vc71/boost_regex_vc71_mdsd/cpp_regex_traits.obj vc71/boost_regex_vc71_mdsd/cregex.obj vc71/boost_regex_vc71_mdsd/fileiter.obj vc71/boost_regex_vc71_mdsd/instances.obj vc71/boost_regex_vc71_mdsd/posix_api.obj vc71/boost_regex_vc71_mdsd/regex.obj vc71/boost_regex_vc71_mdsd/regex_debug.obj vc71/boost_regex_vc71_mdsd/regex_synch.obj vc71/boost_regex_vc71_mdsd/w32_regex_traits.obj vc71/boost_regex_vc71_mdsd/wide_posix_api.obj vc71/boost_regex_vc71_mdsd/winstances.obj
	link -lib /nologo /out:vc71/boost_regex_vc71_mdsd.lib $(XSFLAGS)  vc71/boost_regex_vc71_mdsd/c_regex_traits.obj vc71/boost_regex_vc71_mdsd/c_regex_traits_common.obj vc71/boost_regex_vc71_mdsd/cpp_regex_traits.obj vc71/boost_regex_vc71_mdsd/cregex.obj vc71/boost_regex_vc71_mdsd/fileiter.obj vc71/boost_regex_vc71_mdsd/instances.obj vc71/boost_regex_vc71_mdsd/posix_api.obj vc71/boost_regex_vc71_mdsd/regex.obj vc71/boost_regex_vc71_mdsd/regex_debug.obj vc71/boost_regex_vc71_mdsd/regex_synch.obj vc71/boost_regex_vc71_mdsd/w32_regex_traits.obj vc71/boost_regex_vc71_mdsd/wide_posix_api.obj vc71/boost_regex_vc71_mdsd/winstances.obj

