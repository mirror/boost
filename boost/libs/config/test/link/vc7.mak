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

all : main_dir liblink_test_vc7_ss_dir ./vc7/liblink_test_vc7_ss.lib ./vc7/liblink_test_vc7_ss.exe liblink_test_vc7_ms_dir ./vc7/liblink_test_vc7_ms.lib ./vc7/liblink_test_vc7_ms.exe liblink_test_vc7_ssd_dir ./vc7/liblink_test_vc7_ssd.lib ./vc7/liblink_test_vc7_ssd.exe liblink_test_vc7_msd_dir ./vc7/liblink_test_vc7_msd.lib ./vc7/liblink_test_vc7_msd.exe link_test_vc7_mdd_dir ./vc7/link_test_vc7_mdd.lib ./vc7/link_test_vc7_mdd.exe link_test_vc7_md_dir ./vc7/link_test_vc7_md.lib ./vc7/link_test_vc7_md.exe liblink_test_vc7_md_dir ./vc7/liblink_test_vc7_md.lib ./vc7/liblink_test_vc7_md.exe liblink_test_vc7_mdd_dir ./vc7/liblink_test_vc7_mdd.lib ./vc7/liblink_test_vc7_mdd.exe

clean :  liblink_test_vc7_ss_clean liblink_test_vc7_ms_clean liblink_test_vc7_ssd_clean liblink_test_vc7_msd_clean link_test_vc7_mdd_clean link_test_vc7_md_clean liblink_test_vc7_md_clean liblink_test_vc7_mdd_clean

install : all
	copy vc7\liblink_test_vc7_ss.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_ms.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_ssd.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_ssd.pdb "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_msd.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_msd.pdb "$(MSVCDIR)\lib"
	copy vc7\link_test_vc7_mdd.lib "$(MSVCDIR)\lib"
	copy vc7\link_test_vc7_mdd.dll "$(MSVCDIR)\bin"
	copy vc7\link_test_vc7_mdd.pdb "$(MSVCDIR)\lib"
	copy vc7\link_test_vc7_md.lib "$(MSVCDIR)\lib"
	copy vc7\link_test_vc7_md.dll "$(MSVCDIR)\bin"
	copy vc7\liblink_test_vc7_md.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_mdd.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test_vc7_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc7\$(NULL)" mkdir vc7


########################################################
#
# section for liblink_test_vc7_ss.lib
#
########################################################
vc7/liblink_test_vc7_ss/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_ss/ -Fdvc7/liblink_test_vc7_ss.pdb link_test.cpp

liblink_test_vc7_ss_dir :
	@if not exist "vc7\liblink_test_vc7_ss\$(NULL)" mkdir vc7\liblink_test_vc7_ss

liblink_test_vc7_ss_clean :
	del vc7\liblink_test_vc7_ss\*.obj
	del vc7\liblink_test_vc7_ss\*.idb
	del vc7\liblink_test_vc7_ss\*.exp
	del vc7\liblink_test_vc7_ss\*.pch

./vc7/liblink_test_vc7_ss.lib : vc7/liblink_test_vc7_ss/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_ss.lib $(XSFLAGS)  vc7/liblink_test_vc7_ss/link_test.obj

./vc7/liblink_test_vc7_ss.exe : main.cpp ./vc7/liblink_test_vc7_ss.lib
	cl $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -o ./vc7/liblink_test_vc7_ss.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_ss.exe

########################################################
#
# section for liblink_test_vc7_ms.lib
#
########################################################
vc7/liblink_test_vc7_ms/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_ms/ -Fdvc7/liblink_test_vc7_ms.pdb link_test.cpp

liblink_test_vc7_ms_dir :
	@if not exist "vc7\liblink_test_vc7_ms\$(NULL)" mkdir vc7\liblink_test_vc7_ms

liblink_test_vc7_ms_clean :
	del vc7\liblink_test_vc7_ms\*.obj
	del vc7\liblink_test_vc7_ms\*.idb
	del vc7\liblink_test_vc7_ms\*.exp
	del vc7\liblink_test_vc7_ms\*.pch

./vc7/liblink_test_vc7_ms.lib : vc7/liblink_test_vc7_ms/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_ms.lib $(XSFLAGS)  vc7/liblink_test_vc7_ms/link_test.obj

./vc7/liblink_test_vc7_ms.exe : main.cpp ./vc7/liblink_test_vc7_ms.lib
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -o ./vc7/liblink_test_vc7_ms.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_ms.exe

########################################################
#
# section for liblink_test_vc7_ssd.lib
#
########################################################
vc7/liblink_test_vc7_ssd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_ssd/ -Fdvc7/liblink_test_vc7_ssd.pdb link_test.cpp

liblink_test_vc7_ssd_dir :
	@if not exist "vc7\liblink_test_vc7_ssd\$(NULL)" mkdir vc7\liblink_test_vc7_ssd

liblink_test_vc7_ssd_clean :
	del vc7\liblink_test_vc7_ssd\*.obj
	del vc7\liblink_test_vc7_ssd\*.idb
	del vc7\liblink_test_vc7_ssd\*.exp
	del vc7\liblink_test_vc7_ssd\*.pch

./vc7/liblink_test_vc7_ssd.lib : vc7/liblink_test_vc7_ssd/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_ssd.lib $(XSFLAGS)  vc7/liblink_test_vc7_ssd/link_test.obj

./vc7/liblink_test_vc7_ssd.exe : main.cpp ./vc7/liblink_test_vc7_ssd.lib
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   $(CXXFLAGS) -o ./vc7/liblink_test_vc7_ssd.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_ssd.exe

########################################################
#
# section for liblink_test_vc7_msd.lib
#
########################################################
vc7/liblink_test_vc7_msd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_msd/ -Fdvc7/liblink_test_vc7_msd.pdb link_test.cpp

liblink_test_vc7_msd_dir :
	@if not exist "vc7\liblink_test_vc7_msd\$(NULL)" mkdir vc7\liblink_test_vc7_msd

liblink_test_vc7_msd_clean :
	del vc7\liblink_test_vc7_msd\*.obj
	del vc7\liblink_test_vc7_msd\*.idb
	del vc7\liblink_test_vc7_msd\*.exp
	del vc7\liblink_test_vc7_msd\*.pch

./vc7/liblink_test_vc7_msd.lib : vc7/liblink_test_vc7_msd/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_msd.lib $(XSFLAGS)  vc7/liblink_test_vc7_msd/link_test.obj

./vc7/liblink_test_vc7_msd.exe : main.cpp ./vc7/liblink_test_vc7_msd.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  $(CXXFLAGS) -o ./vc7/liblink_test_vc7_msd.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_msd.exe

########################################################
#
# section for link_test_vc7_mdd.lib
#
########################################################
vc7/link_test_vc7_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/link_test_vc7_mdd/ -Fdvc7/link_test_vc7_mdd.pdb link_test.cpp

link_test_vc7_mdd_dir :
	@if not exist "vc7\link_test_vc7_mdd\$(NULL)" mkdir vc7\link_test_vc7_mdd

link_test_vc7_mdd_clean :
	del vc7\link_test_vc7_mdd\*.obj
	del vc7\link_test_vc7_mdd\*.idb
	del vc7\link_test_vc7_mdd\*.exp
	del vc7\link_test_vc7_mdd\*.pch

./vc7/link_test_vc7_mdd.lib : vc7/link_test_vc7_mdd/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/link_test_vc7_mdd.pdb" /debug /machine:I386 /out:"vc7/link_test_vc7_mdd.dll" /implib:"vc7/link_test_vc7_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/link_test_vc7_mdd/link_test.obj

./vc7/link_test_vc7_mdd.exe : main.cpp ./vc7/link_test_vc7_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -o ./vc7/link_test_vc7_mdd.exe main.cpp /link /LIBPATH:./vc7
   vc7\link_test_vc7_mdd.exe

########################################################
#
# section for link_test_vc7_md.lib
#
########################################################
vc7/link_test_vc7_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc7/link_test_vc7_md/ -Fdvc7/link_test_vc7_md.pdb link_test.cpp

link_test_vc7_md_dir :
	@if not exist "vc7\link_test_vc7_md\$(NULL)" mkdir vc7\link_test_vc7_md

link_test_vc7_md_clean :
	del vc7\link_test_vc7_md\*.obj
	del vc7\link_test_vc7_md\*.idb
	del vc7\link_test_vc7_md\*.exp
	del vc7\link_test_vc7_md\*.pch

./vc7/link_test_vc7_md.lib : vc7/link_test_vc7_md/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/link_test_vc7_md.pdb" /debug /machine:I386 /out:"vc7/link_test_vc7_md.dll" /implib:"vc7/link_test_vc7_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/link_test_vc7_md/link_test.obj

./vc7/link_test_vc7_md.exe : main.cpp ./vc7/link_test_vc7_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc7/link_test_vc7_md.exe main.cpp /link /LIBPATH:./vc7
   vc7\link_test_vc7_md.exe

########################################################
#
# section for liblink_test_vc7_md.lib
#
########################################################
vc7/liblink_test_vc7_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_md/ -Fdvc7/liblink_test_vc7_md.pdb link_test.cpp

liblink_test_vc7_md_dir :
	@if not exist "vc7\liblink_test_vc7_md\$(NULL)" mkdir vc7\liblink_test_vc7_md

liblink_test_vc7_md_clean :
	del vc7\liblink_test_vc7_md\*.obj
	del vc7\liblink_test_vc7_md\*.idb
	del vc7\liblink_test_vc7_md\*.exp
	del vc7\liblink_test_vc7_md\*.pch

./vc7/liblink_test_vc7_md.lib : vc7/liblink_test_vc7_md/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_md.lib $(XSFLAGS)  vc7/liblink_test_vc7_md/link_test.obj

./vc7/liblink_test_vc7_md.exe : main.cpp ./vc7/liblink_test_vc7_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc7/liblink_test_vc7_md.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_md.exe

########################################################
#
# section for liblink_test_vc7_mdd.lib
#
########################################################
vc7/liblink_test_vc7_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test_vc7_mdd/ -Fdvc7/liblink_test_vc7_mdd.pdb link_test.cpp

liblink_test_vc7_mdd_dir :
	@if not exist "vc7\liblink_test_vc7_mdd\$(NULL)" mkdir vc7\liblink_test_vc7_mdd

liblink_test_vc7_mdd_clean :
	del vc7\liblink_test_vc7_mdd\*.obj
	del vc7\liblink_test_vc7_mdd\*.idb
	del vc7\liblink_test_vc7_mdd\*.exp
	del vc7\liblink_test_vc7_mdd\*.pch

./vc7/liblink_test_vc7_mdd.lib : vc7/liblink_test_vc7_mdd/link_test.obj
	link -lib /nologo /out:vc7/liblink_test_vc7_mdd.lib $(XSFLAGS)  vc7/liblink_test_vc7_mdd/link_test.obj

./vc7/liblink_test_vc7_mdd.exe : main.cpp ./vc7/liblink_test_vc7_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -o ./vc7/liblink_test_vc7_mdd.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test_vc7_mdd.exe

