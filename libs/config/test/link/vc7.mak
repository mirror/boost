# copyright John Maddock 2005
# Use, modification and distribution are subject to the 
# Boost Software License, Version 1.0. (See accompanying file 
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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

all : main_dir liblink_test-vc7-s-1_34_dir ./vc7/liblink_test-vc7-s-1_34.lib ./vc7/liblink_test-vc7-s-1_34.exe liblink_test-vc7-mt-s-1_34_dir ./vc7/liblink_test-vc7-mt-s-1_34.lib ./vc7/liblink_test-vc7-mt-s-1_34.exe liblink_test-vc7-sgd-1_34_dir ./vc7/liblink_test-vc7-sgd-1_34.lib ./vc7/liblink_test-vc7-sgd-1_34.exe liblink_test-vc7-mt-sgd-1_34_dir ./vc7/liblink_test-vc7-mt-sgd-1_34.lib ./vc7/liblink_test-vc7-mt-sgd-1_34.exe link_test-vc7-mt-gd-1_34_dir ./vc7/link_test-vc7-mt-gd-1_34.lib ./vc7/link_test-vc7-mt-gd-1_34.exe link_test-vc7-mt-1_34_dir ./vc7/link_test-vc7-mt-1_34.lib ./vc7/link_test-vc7-mt-1_34.exe liblink_test-vc7-mt-1_34_dir ./vc7/liblink_test-vc7-mt-1_34.lib ./vc7/liblink_test-vc7-mt-1_34.exe liblink_test-vc7-mt-gd-1_34_dir ./vc7/liblink_test-vc7-mt-gd-1_34.lib ./vc7/liblink_test-vc7-mt-gd-1_34.exe

clean :  liblink_test-vc7-s-1_34_clean liblink_test-vc7-mt-s-1_34_clean liblink_test-vc7-sgd-1_34_clean liblink_test-vc7-mt-sgd-1_34_clean link_test-vc7-mt-gd-1_34_clean link_test-vc7-mt-1_34_clean liblink_test-vc7-mt-1_34_clean liblink_test-vc7-mt-gd-1_34_clean

install : all
	copy vc7\liblink_test-vc7-s-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-mt-s-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-sgd-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-sgd-1_34.pdb "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-mt-sgd-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-mt-sgd-1_34.pdb "$(MSVCDIR)\lib"
	copy vc7\link_test-vc7-mt-gd-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\link_test-vc7-mt-gd-1_34.dll "$(MSVCDIR)\bin"
	copy vc7\link_test-vc7-mt-gd-1_34.pdb "$(MSVCDIR)\lib"
	copy vc7\link_test-vc7-mt-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\link_test-vc7-mt-1_34.dll "$(MSVCDIR)\bin"
	copy vc7\liblink_test-vc7-mt-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-mt-gd-1_34.lib "$(MSVCDIR)\lib"
	copy vc7\liblink_test-vc7-mt-gd-1_34.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc7\$(NULL)" mkdir vc7


########################################################
#
# section for liblink_test-vc7-s-1_34.lib
#
########################################################
vc7/liblink_test-vc7-s-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-s-1_34/ -Fdvc7/liblink_test-vc7-s-1_34.pdb link_test.cpp

liblink_test-vc7-s-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-s-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-s-1_34

liblink_test-vc7-s-1_34_clean :
	del vc7\liblink_test-vc7-s-1_34\*.obj
	del vc7\liblink_test-vc7-s-1_34\*.idb
	del vc7\liblink_test-vc7-s-1_34\*.exp
	del vc7\liblink_test-vc7-s-1_34\*.pch

./vc7/liblink_test-vc7-s-1_34.lib : vc7/liblink_test-vc7-s-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-s-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-s-1_34/link_test.obj

./vc7/liblink_test-vc7-s-1_34.exe : main.cpp ./vc7/liblink_test-vc7-s-1_34.lib
	cl $(INCLUDES) /nologo /ML /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-s-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-s-1_34.exe

########################################################
#
# section for liblink_test-vc7-mt-s-1_34.lib
#
########################################################
vc7/liblink_test-vc7-mt-s-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-mt-s-1_34/ -Fdvc7/liblink_test-vc7-mt-s-1_34.pdb link_test.cpp

liblink_test-vc7-mt-s-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-mt-s-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-mt-s-1_34

liblink_test-vc7-mt-s-1_34_clean :
	del vc7\liblink_test-vc7-mt-s-1_34\*.obj
	del vc7\liblink_test-vc7-mt-s-1_34\*.idb
	del vc7\liblink_test-vc7-mt-s-1_34\*.exp
	del vc7\liblink_test-vc7-mt-s-1_34\*.pch

./vc7/liblink_test-vc7-mt-s-1_34.lib : vc7/liblink_test-vc7-mt-s-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-mt-s-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-mt-s-1_34/link_test.obj

./vc7/liblink_test-vc7-mt-s-1_34.exe : main.cpp ./vc7/liblink_test-vc7-mt-s-1_34.lib
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /FD  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-mt-s-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-mt-s-1_34.exe

########################################################
#
# section for liblink_test-vc7-sgd-1_34.lib
#
########################################################
vc7/liblink_test-vc7-sgd-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-sgd-1_34/ -Fdvc7/liblink_test-vc7-sgd-1_34.pdb link_test.cpp

liblink_test-vc7-sgd-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-sgd-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-sgd-1_34

liblink_test-vc7-sgd-1_34_clean :
	del vc7\liblink_test-vc7-sgd-1_34\*.obj
	del vc7\liblink_test-vc7-sgd-1_34\*.idb
	del vc7\liblink_test-vc7-sgd-1_34\*.exp
	del vc7\liblink_test-vc7-sgd-1_34\*.pch

./vc7/liblink_test-vc7-sgd-1_34.lib : vc7/liblink_test-vc7-sgd-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-sgd-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-sgd-1_34/link_test.obj

./vc7/liblink_test-vc7-sgd-1_34.exe : main.cpp ./vc7/liblink_test-vc7-sgd-1_34.lib
	cl $(INCLUDES) /nologo /MLd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1   /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-sgd-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-sgd-1_34.exe

########################################################
#
# section for liblink_test-vc7-mt-sgd-1_34.lib
#
########################################################
vc7/liblink_test-vc7-mt-sgd-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-mt-sgd-1_34/ -Fdvc7/liblink_test-vc7-mt-sgd-1_34.pdb link_test.cpp

liblink_test-vc7-mt-sgd-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-mt-sgd-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-mt-sgd-1_34

liblink_test-vc7-mt-sgd-1_34_clean :
	del vc7\liblink_test-vc7-mt-sgd-1_34\*.obj
	del vc7\liblink_test-vc7-mt-sgd-1_34\*.idb
	del vc7\liblink_test-vc7-mt-sgd-1_34\*.exp
	del vc7\liblink_test-vc7-mt-sgd-1_34\*.pch

./vc7/liblink_test-vc7-mt-sgd-1_34.lib : vc7/liblink_test-vc7-mt-sgd-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-mt-sgd-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-mt-sgd-1_34/link_test.obj

./vc7/liblink_test-vc7-mt-sgd-1_34.exe : main.cpp ./vc7/liblink_test-vc7-mt-sgd-1_34.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /FD /GX /RTC1  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-mt-sgd-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-mt-sgd-1_34.exe

########################################################
#
# section for link_test-vc7-mt-gd-1_34.lib
#
########################################################
vc7/link_test-vc7-mt-gd-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/link_test-vc7-mt-gd-1_34/ -Fdvc7/link_test-vc7-mt-gd-1_34.pdb link_test.cpp

link_test-vc7-mt-gd-1_34_dir :
	@if not exist "vc7\link_test-vc7-mt-gd-1_34\$(NULL)" mkdir vc7\link_test-vc7-mt-gd-1_34

link_test-vc7-mt-gd-1_34_clean :
	del vc7\link_test-vc7-mt-gd-1_34\*.obj
	del vc7\link_test-vc7-mt-gd-1_34\*.idb
	del vc7\link_test-vc7-mt-gd-1_34\*.exp
	del vc7\link_test-vc7-mt-gd-1_34\*.pch

./vc7/link_test-vc7-mt-gd-1_34.lib : vc7/link_test-vc7-mt-gd-1_34/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/link_test-vc7-mt-gd-1_34.pdb" /debug /machine:I386 /out:"vc7/link_test-vc7-mt-gd-1_34.dll" /implib:"vc7/link_test-vc7-mt-gd-1_34.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/link_test-vc7-mt-gd-1_34/link_test.obj

./vc7/link_test-vc7-mt-gd-1_34.exe : main.cpp ./vc7/link_test-vc7-mt-gd-1_34.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /D_DEBUG /DBOOST_DYN_LINK /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/link_test-vc7-mt-gd-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\link_test-vc7-mt-gd-1_34.exe

########################################################
#
# section for link_test-vc7-mt-1_34.lib
#
########################################################
vc7/link_test-vc7-mt-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc7/link_test-vc7-mt-1_34/ -Fdvc7/link_test-vc7-mt-1_34.pdb link_test.cpp

link_test-vc7-mt-1_34_dir :
	@if not exist "vc7\link_test-vc7-mt-1_34\$(NULL)" mkdir vc7\link_test-vc7-mt-1_34

link_test-vc7-mt-1_34_clean :
	del vc7\link_test-vc7-mt-1_34\*.obj
	del vc7\link_test-vc7-mt-1_34\*.idb
	del vc7\link_test-vc7-mt-1_34\*.exp
	del vc7\link_test-vc7-mt-1_34\*.pch

./vc7/link_test-vc7-mt-1_34.lib : vc7/link_test-vc7-mt-1_34/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc7/link_test-vc7-mt-1_34.pdb" /debug /machine:I386 /out:"vc7/link_test-vc7-mt-1_34.dll" /implib:"vc7/link_test-vc7-mt-1_34.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc7/link_test-vc7-mt-1_34/link_test.obj

./vc7/link_test-vc7-mt-1_34.exe : main.cpp ./vc7/link_test-vc7-mt-1_34.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/link_test-vc7-mt-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\link_test-vc7-mt-1_34.exe

########################################################
#
# section for liblink_test-vc7-mt-1_34.lib
#
########################################################
vc7/liblink_test-vc7-mt-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-mt-1_34/ -Fdvc7/liblink_test-vc7-mt-1_34.pdb link_test.cpp

liblink_test-vc7-mt-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-mt-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-mt-1_34

liblink_test-vc7-mt-1_34_clean :
	del vc7\liblink_test-vc7-mt-1_34\*.obj
	del vc7\liblink_test-vc7-mt-1_34\*.idb
	del vc7\liblink_test-vc7-mt-1_34\*.exp
	del vc7\liblink_test-vc7-mt-1_34\*.pch

./vc7/liblink_test-vc7-mt-1_34.lib : vc7/liblink_test-vc7-mt-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-mt-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-mt-1_34/link_test.obj

./vc7/liblink_test-vc7-mt-1_34.exe : main.cpp ./vc7/liblink_test-vc7-mt-1_34.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /FD  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-mt-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-mt-1_34.exe

########################################################
#
# section for liblink_test-vc7-mt-gd-1_34.lib
#
########################################################
vc7/liblink_test-vc7-mt-gd-1_34/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  $(CXXFLAGS) -Y- -Fo./vc7/liblink_test-vc7-mt-gd-1_34/ -Fdvc7/liblink_test-vc7-mt-gd-1_34.pdb link_test.cpp

liblink_test-vc7-mt-gd-1_34_dir :
	@if not exist "vc7\liblink_test-vc7-mt-gd-1_34\$(NULL)" mkdir vc7\liblink_test-vc7-mt-gd-1_34

liblink_test-vc7-mt-gd-1_34_clean :
	del vc7\liblink_test-vc7-mt-gd-1_34\*.obj
	del vc7\liblink_test-vc7-mt-gd-1_34\*.idb
	del vc7\liblink_test-vc7-mt-gd-1_34\*.exp
	del vc7\liblink_test-vc7-mt-gd-1_34\*.pch

./vc7/liblink_test-vc7-mt-gd-1_34.lib : vc7/liblink_test-vc7-mt-gd-1_34/link_test.obj
	link -lib /nologo /out:vc7/liblink_test-vc7-mt-gd-1_34.lib $(XSFLAGS)  vc7/liblink_test-vc7-mt-gd-1_34/link_test.obj

./vc7/liblink_test-vc7-mt-gd-1_34.exe : main.cpp ./vc7/liblink_test-vc7-mt-gd-1_34.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GX /RTC1  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc7/liblink_test-vc7-mt-gd-1_34.exe main.cpp /link /LIBPATH:./vc7
   vc7\liblink_test-vc7-mt-gd-1_34.exe

