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


ALL_HEADER=

all : main_dir liblink_test_vc6_ss_dir ./vc6/liblink_test_vc6_ss.lib ./vc6/liblink_test_vc6_ss.exe liblink_test_vc6_ms_dir ./vc6/liblink_test_vc6_ms.lib ./vc6/liblink_test_vc6_ms.exe liblink_test_vc6_ssd_dir ./vc6/liblink_test_vc6_ssd.lib ./vc6/liblink_test_vc6_ssd.exe liblink_test_vc6_msd_dir ./vc6/liblink_test_vc6_msd.lib ./vc6/liblink_test_vc6_msd.exe link_test_vc6_mdd_dir ./vc6/link_test_vc6_mdd.lib ./vc6/link_test_vc6_mdd.exe link_test_vc6_md_dir ./vc6/link_test_vc6_md.lib ./vc6/link_test_vc6_md.exe liblink_test_vc6_md_dir ./vc6/liblink_test_vc6_md.lib ./vc6/liblink_test_vc6_md.exe liblink_test_vc6_mdd_dir ./vc6/liblink_test_vc6_mdd.lib ./vc6/liblink_test_vc6_mdd.exe

clean :  liblink_test_vc6_ss_clean liblink_test_vc6_ms_clean liblink_test_vc6_ssd_clean liblink_test_vc6_msd_clean link_test_vc6_mdd_clean link_test_vc6_md_clean liblink_test_vc6_md_clean liblink_test_vc6_mdd_clean

install : all
	copy vc6\liblink_test_vc6_ss.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_ms.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_ssd.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_ssd.pdb "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_msd.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_msd.pdb "$(MSVCDIR)\lib"
	copy vc6\link_test_vc6_mdd.lib "$(MSVCDIR)\lib"
	copy vc6\link_test_vc6_mdd.dll "$(MSVCDIR)\bin"
	copy vc6\link_test_vc6_mdd.pdb "$(MSVCDIR)\lib"
	copy vc6\link_test_vc6_md.lib "$(MSVCDIR)\lib"
	copy vc6\link_test_vc6_md.dll "$(MSVCDIR)\bin"
	copy vc6\liblink_test_vc6_md.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_mdd.lib "$(MSVCDIR)\lib"
	copy vc6\liblink_test_vc6_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc6\$(NULL)" mkdir vc6


########################################################
#
# section for liblink_test_vc6_ss.lib
#
########################################################
vc6/liblink_test_vc6_ss/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_ss/ -Fdvc6/liblink_test_vc6_ss.pdb link_test.cpp

liblink_test_vc6_ss_dir :
	@if not exist "vc6\liblink_test_vc6_ss\$(NULL)" mkdir vc6\liblink_test_vc6_ss

liblink_test_vc6_ss_clean :
	del vc6\liblink_test_vc6_ss\*.obj
	del vc6\liblink_test_vc6_ss\*.idb
	del vc6\liblink_test_vc6_ss\*.exp
	del vc6\liblink_test_vc6_ss\*.pch

./vc6/liblink_test_vc6_ss.lib : vc6/liblink_test_vc6_ss/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_ss.lib $(XSFLAGS)  vc6/liblink_test_vc6_ss/link_test.obj

./vc6/liblink_test_vc6_ss.exe : main.cpp ./vc6/liblink_test_vc6_ss.lib
	cl $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -o ./vc6/liblink_test_vc6_ss.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_ss.exe

########################################################
#
# section for liblink_test_vc6_ms.lib
#
########################################################
vc6/liblink_test_vc6_ms/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_ms/ -Fdvc6/liblink_test_vc6_ms.pdb link_test.cpp

liblink_test_vc6_ms_dir :
	@if not exist "vc6\liblink_test_vc6_ms\$(NULL)" mkdir vc6\liblink_test_vc6_ms

liblink_test_vc6_ms_clean :
	del vc6\liblink_test_vc6_ms\*.obj
	del vc6\liblink_test_vc6_ms\*.idb
	del vc6\liblink_test_vc6_ms\*.exp
	del vc6\liblink_test_vc6_ms\*.pch

./vc6/liblink_test_vc6_ms.lib : vc6/liblink_test_vc6_ms/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_ms.lib $(XSFLAGS)  vc6/liblink_test_vc6_ms/link_test.obj

./vc6/liblink_test_vc6_ms.exe : main.cpp ./vc6/liblink_test_vc6_ms.lib
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -o ./vc6/liblink_test_vc6_ms.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_ms.exe

########################################################
#
# section for liblink_test_vc6_ssd.lib
#
########################################################
vc6/liblink_test_vc6_ssd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX   $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_ssd/ -Fdvc6/liblink_test_vc6_ssd.pdb link_test.cpp

liblink_test_vc6_ssd_dir :
	@if not exist "vc6\liblink_test_vc6_ssd\$(NULL)" mkdir vc6\liblink_test_vc6_ssd

liblink_test_vc6_ssd_clean :
	del vc6\liblink_test_vc6_ssd\*.obj
	del vc6\liblink_test_vc6_ssd\*.idb
	del vc6\liblink_test_vc6_ssd\*.exp
	del vc6\liblink_test_vc6_ssd\*.pch

./vc6/liblink_test_vc6_ssd.lib : vc6/liblink_test_vc6_ssd/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_ssd.lib $(XSFLAGS)  vc6/liblink_test_vc6_ssd/link_test.obj

./vc6/liblink_test_vc6_ssd.exe : main.cpp ./vc6/liblink_test_vc6_ssd.lib
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX   $(CXXFLAGS) -o ./vc6/liblink_test_vc6_ssd.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_ssd.exe

########################################################
#
# section for liblink_test_vc6_msd.lib
#
########################################################
vc6/liblink_test_vc6_msd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX  $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_msd/ -Fdvc6/liblink_test_vc6_msd.pdb link_test.cpp

liblink_test_vc6_msd_dir :
	@if not exist "vc6\liblink_test_vc6_msd\$(NULL)" mkdir vc6\liblink_test_vc6_msd

liblink_test_vc6_msd_clean :
	del vc6\liblink_test_vc6_msd\*.obj
	del vc6\liblink_test_vc6_msd\*.idb
	del vc6\liblink_test_vc6_msd\*.exp
	del vc6\liblink_test_vc6_msd\*.pch

./vc6/liblink_test_vc6_msd.lib : vc6/liblink_test_vc6_msd/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_msd.lib $(XSFLAGS)  vc6/liblink_test_vc6_msd/link_test.obj

./vc6/liblink_test_vc6_msd.exe : main.cpp ./vc6/liblink_test_vc6_msd.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX  $(CXXFLAGS) -o ./vc6/liblink_test_vc6_msd.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_msd.exe

########################################################
#
# section for link_test_vc6_mdd.lib
#
########################################################
vc6/link_test_vc6_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX  $(CXXFLAGS) -Y- -Fo./vc6/link_test_vc6_mdd/ -Fdvc6/link_test_vc6_mdd.pdb link_test.cpp

link_test_vc6_mdd_dir :
	@if not exist "vc6\link_test_vc6_mdd\$(NULL)" mkdir vc6\link_test_vc6_mdd

link_test_vc6_mdd_clean :
	del vc6\link_test_vc6_mdd\*.obj
	del vc6\link_test_vc6_mdd\*.idb
	del vc6\link_test_vc6_mdd\*.exp
	del vc6\link_test_vc6_mdd\*.pch

./vc6/link_test_vc6_mdd.lib : vc6/link_test_vc6_mdd/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/link_test_vc6_mdd.pdb" /debug /machine:I386 /out:"vc6/link_test_vc6_mdd.dll" /implib:"vc6/link_test_vc6_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6/link_test_vc6_mdd/link_test.obj

./vc6/link_test_vc6_mdd.exe : main.cpp ./vc6/link_test_vc6_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX  $(CXXFLAGS) -o ./vc6/link_test_vc6_mdd.exe main.cpp /link /LIBPATH:./vc6
   vc6\link_test_vc6_mdd.exe

########################################################
#
# section for link_test_vc6_md.lib
#
########################################################
vc6/link_test_vc6_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc6/link_test_vc6_md/ -Fdvc6/link_test_vc6_md.pdb link_test.cpp

link_test_vc6_md_dir :
	@if not exist "vc6\link_test_vc6_md\$(NULL)" mkdir vc6\link_test_vc6_md

link_test_vc6_md_clean :
	del vc6\link_test_vc6_md\*.obj
	del vc6\link_test_vc6_md\*.idb
	del vc6\link_test_vc6_md\*.exp
	del vc6\link_test_vc6_md\*.pch

./vc6/link_test_vc6_md.lib : vc6/link_test_vc6_md/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6/link_test_vc6_md.pdb" /debug /machine:I386 /out:"vc6/link_test_vc6_md.dll" /implib:"vc6/link_test_vc6_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6/link_test_vc6_md/link_test.obj

./vc6/link_test_vc6_md.exe : main.cpp ./vc6/link_test_vc6_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc6/link_test_vc6_md.exe main.cpp /link /LIBPATH:./vc6
   vc6\link_test_vc6_md.exe

########################################################
#
# section for liblink_test_vc6_md.lib
#
########################################################
vc6/liblink_test_vc6_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_md/ -Fdvc6/liblink_test_vc6_md.pdb link_test.cpp

liblink_test_vc6_md_dir :
	@if not exist "vc6\liblink_test_vc6_md\$(NULL)" mkdir vc6\liblink_test_vc6_md

liblink_test_vc6_md_clean :
	del vc6\liblink_test_vc6_md\*.obj
	del vc6\liblink_test_vc6_md\*.idb
	del vc6\liblink_test_vc6_md\*.exp
	del vc6\liblink_test_vc6_md\*.pch

./vc6/liblink_test_vc6_md.lib : vc6/liblink_test_vc6_md/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_md.lib $(XSFLAGS)  vc6/liblink_test_vc6_md/link_test.obj

./vc6/liblink_test_vc6_md.exe : main.cpp ./vc6/liblink_test_vc6_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc6/liblink_test_vc6_md.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_md.exe

########################################################
#
# section for liblink_test_vc6_mdd.lib
#
########################################################
vc6/liblink_test_vc6_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX  $(CXXFLAGS) -Y- -Fo./vc6/liblink_test_vc6_mdd/ -Fdvc6/liblink_test_vc6_mdd.pdb link_test.cpp

liblink_test_vc6_mdd_dir :
	@if not exist "vc6\liblink_test_vc6_mdd\$(NULL)" mkdir vc6\liblink_test_vc6_mdd

liblink_test_vc6_mdd_clean :
	del vc6\liblink_test_vc6_mdd\*.obj
	del vc6\liblink_test_vc6_mdd\*.idb
	del vc6\liblink_test_vc6_mdd\*.exp
	del vc6\liblink_test_vc6_mdd\*.pch

./vc6/liblink_test_vc6_mdd.lib : vc6/liblink_test_vc6_mdd/link_test.obj
	link -lib /nologo /out:vc6/liblink_test_vc6_mdd.lib $(XSFLAGS)  vc6/liblink_test_vc6_mdd/link_test.obj

./vc6/liblink_test_vc6_mdd.exe : main.cpp ./vc6/liblink_test_vc6_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX  $(CXXFLAGS) -o ./vc6/liblink_test_vc6_mdd.exe main.cpp /link /LIBPATH:./vc6
   vc6\liblink_test_vc6_mdd.exe

