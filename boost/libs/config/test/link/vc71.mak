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

all : main_dir liblink_test_vc71_ss_dir ./vc71/liblink_test_vc71_ss.lib ./vc71/liblink_test_vc71_ss.exe liblink_test_vc71_ms_dir ./vc71/liblink_test_vc71_ms.lib ./vc71/liblink_test_vc71_ms.exe liblink_test_vc71_ssd_dir ./vc71/liblink_test_vc71_ssd.lib ./vc71/liblink_test_vc71_ssd.exe liblink_test_vc71_msd_dir ./vc71/liblink_test_vc71_msd.lib ./vc71/liblink_test_vc71_msd.exe link_test_vc71_mdd_dir ./vc71/link_test_vc71_mdd.lib ./vc71/link_test_vc71_mdd.exe link_test_vc71_md_dir ./vc71/link_test_vc71_md.lib ./vc71/link_test_vc71_md.exe liblink_test_vc71_md_dir ./vc71/liblink_test_vc71_md.lib ./vc71/liblink_test_vc71_md.exe liblink_test_vc71_mdd_dir ./vc71/liblink_test_vc71_mdd.lib ./vc71/liblink_test_vc71_mdd.exe

clean :  liblink_test_vc71_ss_clean liblink_test_vc71_ms_clean liblink_test_vc71_ssd_clean liblink_test_vc71_msd_clean link_test_vc71_mdd_clean link_test_vc71_md_clean liblink_test_vc71_md_clean liblink_test_vc71_mdd_clean

install : all
	copy vc71\liblink_test_vc71_ss.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_ms.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_ssd.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_ssd.pdb "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_msd.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_msd.pdb "$(MSVCDIR)\lib"
	copy vc71\link_test_vc71_mdd.lib "$(MSVCDIR)\lib"
	copy vc71\link_test_vc71_mdd.dll "$(MSVCDIR)\bin"
	copy vc71\link_test_vc71_mdd.pdb "$(MSVCDIR)\lib"
	copy vc71\link_test_vc71_md.lib "$(MSVCDIR)\lib"
	copy vc71\link_test_vc71_md.dll "$(MSVCDIR)\bin"
	copy vc71\liblink_test_vc71_md.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_mdd.lib "$(MSVCDIR)\lib"
	copy vc71\liblink_test_vc71_mdd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc71\$(NULL)" mkdir vc71


########################################################
#
# section for liblink_test_vc71_ss.lib
#
########################################################
vc71/liblink_test_vc71_ss/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_ss/ -Fdvc71/liblink_test_vc71_ss.pdb link_test.cpp

liblink_test_vc71_ss_dir :
	@if not exist "vc71\liblink_test_vc71_ss\$(NULL)" mkdir vc71\liblink_test_vc71_ss

liblink_test_vc71_ss_clean :
	del vc71\liblink_test_vc71_ss\*.obj
	del vc71\liblink_test_vc71_ss\*.idb
	del vc71\liblink_test_vc71_ss\*.exp
	del vc71\liblink_test_vc71_ss\*.pch

./vc71/liblink_test_vc71_ss.lib : vc71/liblink_test_vc71_ss/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_ss.lib $(XSFLAGS)  vc71/liblink_test_vc71_ss/link_test.obj

./vc71/liblink_test_vc71_ss.exe : main.cpp ./vc71/liblink_test_vc71_ss.lib
	cl $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -o ./vc71/liblink_test_vc71_ss.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_ss.exe

########################################################
#
# section for liblink_test_vc71_ms.lib
#
########################################################
vc71/liblink_test_vc71_ms/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_ms/ -Fdvc71/liblink_test_vc71_ms.pdb link_test.cpp

liblink_test_vc71_ms_dir :
	@if not exist "vc71\liblink_test_vc71_ms\$(NULL)" mkdir vc71\liblink_test_vc71_ms

liblink_test_vc71_ms_clean :
	del vc71\liblink_test_vc71_ms\*.obj
	del vc71\liblink_test_vc71_ms\*.idb
	del vc71\liblink_test_vc71_ms\*.exp
	del vc71\liblink_test_vc71_ms\*.pch

./vc71/liblink_test_vc71_ms.lib : vc71/liblink_test_vc71_ms/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_ms.lib $(XSFLAGS)  vc71/liblink_test_vc71_ms/link_test.obj

./vc71/liblink_test_vc71_ms.exe : main.cpp ./vc71/liblink_test_vc71_ms.lib
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -o ./vc71/liblink_test_vc71_ms.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_ms.exe

########################################################
#
# section for liblink_test_vc71_ssd.lib
#
########################################################
vc71/liblink_test_vc71_ssd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_ssd/ -Fdvc71/liblink_test_vc71_ssd.pdb link_test.cpp

liblink_test_vc71_ssd_dir :
	@if not exist "vc71\liblink_test_vc71_ssd\$(NULL)" mkdir vc71\liblink_test_vc71_ssd

liblink_test_vc71_ssd_clean :
	del vc71\liblink_test_vc71_ssd\*.obj
	del vc71\liblink_test_vc71_ssd\*.idb
	del vc71\liblink_test_vc71_ssd\*.exp
	del vc71\liblink_test_vc71_ssd\*.pch

./vc71/liblink_test_vc71_ssd.lib : vc71/liblink_test_vc71_ssd/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_ssd.lib $(XSFLAGS)  vc71/liblink_test_vc71_ssd/link_test.obj

./vc71/liblink_test_vc71_ssd.exe : main.cpp ./vc71/liblink_test_vc71_ssd.lib
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   $(CXXFLAGS) -o ./vc71/liblink_test_vc71_ssd.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_ssd.exe

########################################################
#
# section for liblink_test_vc71_msd.lib
#
########################################################
vc71/liblink_test_vc71_msd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_msd/ -Fdvc71/liblink_test_vc71_msd.pdb link_test.cpp

liblink_test_vc71_msd_dir :
	@if not exist "vc71\liblink_test_vc71_msd\$(NULL)" mkdir vc71\liblink_test_vc71_msd

liblink_test_vc71_msd_clean :
	del vc71\liblink_test_vc71_msd\*.obj
	del vc71\liblink_test_vc71_msd\*.idb
	del vc71\liblink_test_vc71_msd\*.exp
	del vc71\liblink_test_vc71_msd\*.pch

./vc71/liblink_test_vc71_msd.lib : vc71/liblink_test_vc71_msd/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_msd.lib $(XSFLAGS)  vc71/liblink_test_vc71_msd/link_test.obj

./vc71/liblink_test_vc71_msd.exe : main.cpp ./vc71/liblink_test_vc71_msd.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  $(CXXFLAGS) -o ./vc71/liblink_test_vc71_msd.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_msd.exe

########################################################
#
# section for link_test_vc71_mdd.lib
#
########################################################
vc71/link_test_vc71_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc71/link_test_vc71_mdd/ -Fdvc71/link_test_vc71_mdd.pdb link_test.cpp

link_test_vc71_mdd_dir :
	@if not exist "vc71\link_test_vc71_mdd\$(NULL)" mkdir vc71\link_test_vc71_mdd

link_test_vc71_mdd_clean :
	del vc71\link_test_vc71_mdd\*.obj
	del vc71\link_test_vc71_mdd\*.idb
	del vc71\link_test_vc71_mdd\*.exp
	del vc71\link_test_vc71_mdd\*.pch

./vc71/link_test_vc71_mdd.lib : vc71/link_test_vc71_mdd/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/link_test_vc71_mdd.pdb" /debug /machine:I386 /out:"vc71/link_test_vc71_mdd.dll" /implib:"vc71/link_test_vc71_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/link_test_vc71_mdd/link_test.obj

./vc71/link_test_vc71_mdd.exe : main.cpp ./vc71/link_test_vc71_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -o ./vc71/link_test_vc71_mdd.exe main.cpp /link /LIBPATH:./vc71
   vc71\link_test_vc71_mdd.exe

########################################################
#
# section for link_test_vc71_md.lib
#
########################################################
vc71/link_test_vc71_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc71/link_test_vc71_md/ -Fdvc71/link_test_vc71_md.pdb link_test.cpp

link_test_vc71_md_dir :
	@if not exist "vc71\link_test_vc71_md\$(NULL)" mkdir vc71\link_test_vc71_md

link_test_vc71_md_clean :
	del vc71\link_test_vc71_md\*.obj
	del vc71\link_test_vc71_md\*.idb
	del vc71\link_test_vc71_md\*.exp
	del vc71\link_test_vc71_md\*.pch

./vc71/link_test_vc71_md.lib : vc71/link_test_vc71_md/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71/link_test_vc71_md.pdb" /debug /machine:I386 /out:"vc71/link_test_vc71_md.dll" /implib:"vc71/link_test_vc71_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71/link_test_vc71_md/link_test.obj

./vc71/link_test_vc71_md.exe : main.cpp ./vc71/link_test_vc71_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc71/link_test_vc71_md.exe main.cpp /link /LIBPATH:./vc71
   vc71\link_test_vc71_md.exe

########################################################
#
# section for liblink_test_vc71_md.lib
#
########################################################
vc71/liblink_test_vc71_md/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_md/ -Fdvc71/liblink_test_vc71_md.pdb link_test.cpp

liblink_test_vc71_md_dir :
	@if not exist "vc71\liblink_test_vc71_md\$(NULL)" mkdir vc71\liblink_test_vc71_md

liblink_test_vc71_md_clean :
	del vc71\liblink_test_vc71_md\*.obj
	del vc71\liblink_test_vc71_md\*.idb
	del vc71\liblink_test_vc71_md\*.exp
	del vc71\liblink_test_vc71_md\*.pch

./vc71/liblink_test_vc71_md.lib : vc71/liblink_test_vc71_md/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_md.lib $(XSFLAGS)  vc71/liblink_test_vc71_md/link_test.obj

./vc71/liblink_test_vc71_md.exe : main.cpp ./vc71/liblink_test_vc71_md.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -o ./vc71/liblink_test_vc71_md.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_md.exe

########################################################
#
# section for liblink_test_vc71_mdd.lib
#
########################################################
vc71/liblink_test_vc71_mdd/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc71/liblink_test_vc71_mdd/ -Fdvc71/liblink_test_vc71_mdd.pdb link_test.cpp

liblink_test_vc71_mdd_dir :
	@if not exist "vc71\liblink_test_vc71_mdd\$(NULL)" mkdir vc71\liblink_test_vc71_mdd

liblink_test_vc71_mdd_clean :
	del vc71\liblink_test_vc71_mdd\*.obj
	del vc71\liblink_test_vc71_mdd\*.idb
	del vc71\liblink_test_vc71_mdd\*.exp
	del vc71\liblink_test_vc71_mdd\*.pch

./vc71/liblink_test_vc71_mdd.lib : vc71/liblink_test_vc71_mdd/link_test.obj
	link -lib /nologo /out:vc71/liblink_test_vc71_mdd.lib $(XSFLAGS)  vc71/liblink_test_vc71_mdd/link_test.obj

./vc71/liblink_test_vc71_mdd.exe : main.cpp ./vc71/liblink_test_vc71_mdd.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -o ./vc71/liblink_test_vc71_mdd.exe main.cpp /link /LIBPATH:./vc71
   vc71\liblink_test_vc71_mdd.exe

