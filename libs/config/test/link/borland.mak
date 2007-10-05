# copyright John Maddock 2005
# Use, modification and distribution are subject to the 
# Boost Software License, Version 1.0. (See accompanying file 
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# auto generated makefile for C++ Builder
#
# usage:
# make
#   brings libraries up to date
# make install
#   brings libraries up to date and copies binaries to your C++ Builder /lib and /bin directories (recomended)
# make clean
#   removes all temporary files.

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
# add additional libraries to link to here:
#
LIBS=
#
# add additional static-library creation flags here:
#
XSFLAGS=

!ifndef BCROOT
BCROOT=$(MAKEDIR)\..
!endif


ALL_HEADER=

all : borland borland\liblink_test-borland-s-1_34 borland\liblink_test-borland-s-1_34.lib borland\liblink_test-borland-s-1_34.exe borland\liblink_test-borland-mt-s-1_34 borland\liblink_test-borland-mt-s-1_34.lib borland\liblink_test-borland-mt-s-1_34.exe borland\link_test-borland-mt-1_34 borland\link_test-borland-mt-1_34.lib borland\link_test-borland-mt-1_34.exe borland\link_test-borland-1_34 borland\link_test-borland-1_34.lib borland\link_test-borland-1_34.exe borland\liblink_test-borland-mt-1_34 borland\liblink_test-borland-mt-1_34.lib borland\liblink_test-borland-mt-1_34.exe borland\liblink_test-borland-1_34 borland\liblink_test-borland-1_34.lib borland\liblink_test-borland-1_34.exe borland\liblink_test-borland-sd-1_34 borland\liblink_test-borland-sd-1_34.lib borland\liblink_test-borland-sd-1_34.exe borland\liblink_test-borland-mt-sd-1_34 borland\liblink_test-borland-mt-sd-1_34.lib borland\liblink_test-borland-mt-sd-1_34.exe borland\link_test-borland-mt-d-1_34 borland\link_test-borland-mt-d-1_34.lib borland\link_test-borland-mt-d-1_34.exe borland\link_test-borland-d-1_34 borland\link_test-borland-d-1_34.lib borland\link_test-borland-d-1_34.exe borland\liblink_test-borland-mt-d-1_34 borland\liblink_test-borland-mt-d-1_34.lib borland\liblink_test-borland-mt-d-1_34.exe borland\liblink_test-borland-d-1_34 borland\liblink_test-borland-d-1_34.lib borland\liblink_test-borland-d-1_34.exe

clean :  liblink_test-borland-s-1_34_clean liblink_test-borland-mt-s-1_34_clean link_test-borland-mt-1_34_clean link_test-borland-1_34_clean liblink_test-borland-mt-1_34_clean liblink_test-borland-1_34_clean liblink_test-borland-sd-1_34_clean liblink_test-borland-mt-sd-1_34_clean link_test-borland-mt-d-1_34_clean link_test-borland-d-1_34_clean liblink_test-borland-mt-d-1_34_clean liblink_test-borland-d-1_34_clean

install : all
	copy borland\liblink_test-borland-s-1_34.lib $(BCROOT)\lib
	copy borland\liblink_test-borland-mt-s-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-mt-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-mt-1_34.dll $(BCROOT)\bin
	copy borland\link_test-borland-mt-1_34.tds $(BCROOT)\bin
	copy borland\link_test-borland-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-1_34.dll $(BCROOT)\bin
	copy borland\link_test-borland-1_34.tds $(BCROOT)\bin
	copy borland\liblink_test-borland-mt-1_34.lib $(BCROOT)\lib
	copy borland\liblink_test-borland-1_34.lib $(BCROOT)\lib
	copy borland\liblink_test-borland-sd-1_34.lib $(BCROOT)\lib
	copy borland\liblink_test-borland-mt-sd-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-mt-d-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-mt-d-1_34.dll $(BCROOT)\bin
	copy borland\link_test-borland-mt-d-1_34.tds $(BCROOT)\bin
	copy borland\link_test-borland-d-1_34.lib $(BCROOT)\lib
	copy borland\link_test-borland-d-1_34.dll $(BCROOT)\bin
	copy borland\link_test-borland-d-1_34.tds $(BCROOT)\bin
	copy borland\liblink_test-borland-mt-d-1_34.lib $(BCROOT)\lib
	copy borland\liblink_test-borland-d-1_34.lib $(BCROOT)\lib

borland :
	-@mkdir borland


########################################################
#
# section for liblink_test-borland-s-1_34.lib
#
########################################################
borland\liblink_test-borland-s-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -oborland\liblink_test-borland-s-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-s-1_34 : 
	-@mkdir borland\liblink_test-borland-s-1_34

liblink_test-borland-s-1_34_clean :
	del borland\liblink_test-borland-s-1_34\*.obj
	del borland\liblink_test-borland-s-1_34\*.il?
	del borland\liblink_test-borland-s-1_34\*.csm
	del borland\liblink_test-borland-s-1_34\*.tds

borland\liblink_test-borland-s-1_34.lib : borland\liblink_test-borland-s-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-s-1_34.lib"  "borland\liblink_test-borland-s-1_34\link_test.obj"
|

borland\liblink_test-borland-s-1_34.exe : main.cpp borland\liblink_test-borland-s-1_34.lib
	bcc32 $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-s-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-s-1_34.exe
   borland\liblink_test-borland-s-1_34.exe

########################################################
#
# section for liblink_test-borland-mt-s-1_34.lib
#
########################################################
borland\liblink_test-borland-mt-s-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -oborland\liblink_test-borland-mt-s-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-mt-s-1_34 : 
	-@mkdir borland\liblink_test-borland-mt-s-1_34

liblink_test-borland-mt-s-1_34_clean :
	del borland\liblink_test-borland-mt-s-1_34\*.obj
	del borland\liblink_test-borland-mt-s-1_34\*.il?
	del borland\liblink_test-borland-mt-s-1_34\*.csm
	del borland\liblink_test-borland-mt-s-1_34\*.tds

borland\liblink_test-borland-mt-s-1_34.lib : borland\liblink_test-borland-mt-s-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-mt-s-1_34.lib"  "borland\liblink_test-borland-mt-s-1_34\link_test.obj"
|

borland\liblink_test-borland-mt-s-1_34.exe : main.cpp borland\liblink_test-borland-mt-s-1_34.lib
	bcc32 $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-mt-s-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-mt-s-1_34.exe
   borland\liblink_test-borland-mt-s-1_34.exe

########################################################
#
# section for link_test-borland-mt-1_34.lib
#
########################################################
borland\link_test-borland-mt-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -oborland\link_test-borland-mt-1_34\link_test.obj link_test.cpp
|

borland\link_test-borland-mt-1_34 :
	-@mkdir borland\link_test-borland-mt-1_34

link_test-borland-mt-1_34_clean :
	del borland\link_test-borland-mt-1_34\*.obj
	del borland\link_test-borland-mt-1_34\*.il?
	del borland\link_test-borland-mt-1_34\*.csm
	del borland\link_test-borland-mt-1_34\*.tds
	del borland\*.tds

borland\link_test-borland-mt-1_34.lib : borland\link_test-borland-mt-1_34\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -eborland\link_test-borland-mt-1_34.dll $(XLFLAGS)  borland\link_test-borland-mt-1_34\link_test.obj $(LIBS)
|
	implib -w borland\link_test-borland-mt-1_34.lib borland\link_test-borland-mt-1_34.dll

borland\link_test-borland-mt-1_34.exe : main.cpp borland\link_test-borland-mt-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -DBOOST_DYN_LINK -L./borland -e./borland/link_test-borland-mt-1_34.exe main.cpp
   echo running test program borland\link_test-borland-mt-1_34.exe
   borland\link_test-borland-mt-1_34.exe

########################################################
#
# section for link_test-borland-1_34.lib
#
########################################################
borland\link_test-borland-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -oborland\link_test-borland-1_34\link_test.obj link_test.cpp
|

borland\link_test-borland-1_34 :
	-@mkdir borland\link_test-borland-1_34

link_test-borland-1_34_clean :
	del borland\link_test-borland-1_34\*.obj
	del borland\link_test-borland-1_34\*.il?
	del borland\link_test-borland-1_34\*.csm
	del borland\link_test-borland-1_34\*.tds
	del borland\*.tds

borland\link_test-borland-1_34.lib : borland\link_test-borland-1_34\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -eborland\link_test-borland-1_34.dll $(XLFLAGS)  borland\link_test-borland-1_34\link_test.obj $(LIBS)
|
	implib -w borland\link_test-borland-1_34.lib borland\link_test-borland-1_34.dll

borland\link_test-borland-1_34.exe : main.cpp borland\link_test-borland-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -DBOOST_DYN_LINK -L./borland -e./borland/link_test-borland-1_34.exe main.cpp
   echo running test program borland\link_test-borland-1_34.exe
   borland\link_test-borland-1_34.exe

########################################################
#
# section for liblink_test-borland-mt-1_34.lib
#
########################################################
borland\liblink_test-borland-mt-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -oborland\liblink_test-borland-mt-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-mt-1_34 : 
	-@mkdir borland\liblink_test-borland-mt-1_34

liblink_test-borland-mt-1_34_clean :
	del borland\liblink_test-borland-mt-1_34\*.obj
	del borland\liblink_test-borland-mt-1_34\*.il?
	del borland\liblink_test-borland-mt-1_34\*.csm
	del borland\liblink_test-borland-mt-1_34\*.tds

borland\liblink_test-borland-mt-1_34.lib : borland\liblink_test-borland-mt-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-mt-1_34.lib"  "borland\liblink_test-borland-mt-1_34\link_test.obj"
|

borland\liblink_test-borland-mt-1_34.exe : main.cpp borland\liblink_test-borland-mt-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-mt-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-mt-1_34.exe
   borland\liblink_test-borland-mt-1_34.exe

########################################################
#
# section for liblink_test-borland-1_34.lib
#
########################################################
borland\liblink_test-borland-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -oborland\liblink_test-borland-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-1_34 : 
	-@mkdir borland\liblink_test-borland-1_34

liblink_test-borland-1_34_clean :
	del borland\liblink_test-borland-1_34\*.obj
	del borland\liblink_test-borland-1_34\*.il?
	del borland\liblink_test-borland-1_34\*.csm
	del borland\liblink_test-borland-1_34\*.tds

borland\liblink_test-borland-1_34.lib : borland\liblink_test-borland-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-1_34.lib"  "borland\liblink_test-borland-1_34\link_test.obj"
|

borland\liblink_test-borland-1_34.exe : main.cpp borland\liblink_test-borland-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-1_34.exe
   borland\liblink_test-borland-1_34.exe

########################################################
#
# section for liblink_test-borland-sd-1_34.lib
#
########################################################
borland\liblink_test-borland-sd-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -oborland\liblink_test-borland-sd-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-sd-1_34 : 
	-@mkdir borland\liblink_test-borland-sd-1_34

liblink_test-borland-sd-1_34_clean :
	del borland\liblink_test-borland-sd-1_34\*.obj
	del borland\liblink_test-borland-sd-1_34\*.il?
	del borland\liblink_test-borland-sd-1_34\*.csm
	del borland\liblink_test-borland-sd-1_34\*.tds

borland\liblink_test-borland-sd-1_34.lib : borland\liblink_test-borland-sd-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-sd-1_34.lib"  "borland\liblink_test-borland-sd-1_34\link_test.obj"
|

borland\liblink_test-borland-sd-1_34.exe : main.cpp borland\liblink_test-borland-sd-1_34.lib
	bcc32 $(INCLUDES) -tWM- -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-sd-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-sd-1_34.exe
   borland\liblink_test-borland-sd-1_34.exe

########################################################
#
# section for liblink_test-borland-mt-sd-1_34.lib
#
########################################################
borland\liblink_test-borland-mt-sd-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -oborland\liblink_test-borland-mt-sd-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-mt-sd-1_34 : 
	-@mkdir borland\liblink_test-borland-mt-sd-1_34

liblink_test-borland-mt-sd-1_34_clean :
	del borland\liblink_test-borland-mt-sd-1_34\*.obj
	del borland\liblink_test-borland-mt-sd-1_34\*.il?
	del borland\liblink_test-borland-mt-sd-1_34\*.csm
	del borland\liblink_test-borland-mt-sd-1_34\*.tds

borland\liblink_test-borland-mt-sd-1_34.lib : borland\liblink_test-borland-mt-sd-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-mt-sd-1_34.lib"  "borland\liblink_test-borland-mt-sd-1_34\link_test.obj"
|

borland\liblink_test-borland-mt-sd-1_34.exe : main.cpp borland\liblink_test-borland-mt-sd-1_34.lib
	bcc32 $(INCLUDES) -tWM -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-mt-sd-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-mt-sd-1_34.exe
   borland\liblink_test-borland-mt-sd-1_34.exe

########################################################
#
# section for link_test-borland-mt-d-1_34.lib
#
########################################################
borland\link_test-borland-mt-d-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -oborland\link_test-borland-mt-d-1_34\link_test.obj link_test.cpp
|

borland\link_test-borland-mt-d-1_34 :
	-@mkdir borland\link_test-borland-mt-d-1_34

link_test-borland-mt-d-1_34_clean :
	del borland\link_test-borland-mt-d-1_34\*.obj
	del borland\link_test-borland-mt-d-1_34\*.il?
	del borland\link_test-borland-mt-d-1_34\*.csm
	del borland\link_test-borland-mt-d-1_34\*.tds
	del borland\*.tds

borland\link_test-borland-mt-d-1_34.lib : borland\link_test-borland-mt-d-1_34\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -eborland\link_test-borland-mt-d-1_34.dll $(XLFLAGS)  borland\link_test-borland-mt-d-1_34\link_test.obj $(LIBS)
|
	implib -w borland\link_test-borland-mt-d-1_34.lib borland\link_test-borland-mt-d-1_34.dll

borland\link_test-borland-mt-d-1_34.exe : main.cpp borland\link_test-borland-mt-d-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -DBOOST_DYN_LINK -L./borland -e./borland/link_test-borland-mt-d-1_34.exe main.cpp
   echo running test program borland\link_test-borland-mt-d-1_34.exe
   borland\link_test-borland-mt-d-1_34.exe

########################################################
#
# section for link_test-borland-d-1_34.lib
#
########################################################
borland\link_test-borland-d-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -oborland\link_test-borland-d-1_34\link_test.obj link_test.cpp
|

borland\link_test-borland-d-1_34 :
	-@mkdir borland\link_test-borland-d-1_34

link_test-borland-d-1_34_clean :
	del borland\link_test-borland-d-1_34\*.obj
	del borland\link_test-borland-d-1_34\*.il?
	del borland\link_test-borland-d-1_34\*.csm
	del borland\link_test-borland-d-1_34\*.tds
	del borland\*.tds

borland\link_test-borland-d-1_34.lib : borland\link_test-borland-d-1_34\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -eborland\link_test-borland-d-1_34.dll $(XLFLAGS)  borland\link_test-borland-d-1_34\link_test.obj $(LIBS)
|
	implib -w borland\link_test-borland-d-1_34.lib borland\link_test-borland-d-1_34.dll

borland\link_test-borland-d-1_34.exe : main.cpp borland\link_test-borland-d-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -DBOOST_DYN_LINK -L./borland -e./borland/link_test-borland-d-1_34.exe main.cpp
   echo running test program borland\link_test-borland-d-1_34.exe
   borland\link_test-borland-d-1_34.exe

########################################################
#
# section for liblink_test-borland-mt-d-1_34.lib
#
########################################################
borland\liblink_test-borland-mt-d-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -oborland\liblink_test-borland-mt-d-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-mt-d-1_34 : 
	-@mkdir borland\liblink_test-borland-mt-d-1_34

liblink_test-borland-mt-d-1_34_clean :
	del borland\liblink_test-borland-mt-d-1_34\*.obj
	del borland\liblink_test-borland-mt-d-1_34\*.il?
	del borland\liblink_test-borland-mt-d-1_34\*.csm
	del borland\liblink_test-borland-mt-d-1_34\*.tds

borland\liblink_test-borland-mt-d-1_34.lib : borland\liblink_test-borland-mt-d-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-mt-d-1_34.lib"  "borland\liblink_test-borland-mt-d-1_34\link_test.obj"
|

borland\liblink_test-borland-mt-d-1_34.exe : main.cpp borland\liblink_test-borland-mt-d-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-mt-d-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-mt-d-1_34.exe
   borland\liblink_test-borland-mt-d-1_34.exe

########################################################
#
# section for liblink_test-borland-d-1_34.lib
#
########################################################
borland\liblink_test-borland-d-1_34\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -oborland\liblink_test-borland-d-1_34\link_test.obj link_test.cpp
|

borland\liblink_test-borland-d-1_34 : 
	-@mkdir borland\liblink_test-borland-d-1_34

liblink_test-borland-d-1_34_clean :
	del borland\liblink_test-borland-d-1_34\*.obj
	del borland\liblink_test-borland-d-1_34\*.il?
	del borland\liblink_test-borland-d-1_34\*.csm
	del borland\liblink_test-borland-d-1_34\*.tds

borland\liblink_test-borland-d-1_34.lib : borland\liblink_test-borland-d-1_34\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "borland\liblink_test-borland-d-1_34.lib"  "borland\liblink_test-borland-d-1_34\link_test.obj"
|

borland\liblink_test-borland-d-1_34.exe : main.cpp borland\liblink_test-borland-d-1_34.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -L./borland -e./borland/liblink_test-borland-d-1_34.exe main.cpp
   echo running test progam borland\liblink_test-borland-d-1_34.exe
   borland\liblink_test-borland-d-1_34.exe

