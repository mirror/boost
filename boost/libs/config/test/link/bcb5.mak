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

all : bcb5 bcb5\liblink_test_bcb5_ss bcb5\liblink_test_bcb5_ss.lib bcb5\liblink_test_bcb5_ss.exe bcb5\liblink_test_bcb5_ms bcb5\liblink_test_bcb5_ms.lib bcb5\liblink_test_bcb5_ms.exe bcb5\link_test_bcb5_md bcb5\link_test_bcb5_md.lib bcb5\link_test_bcb5_md.exe bcb5\link_test_bcb5_sd bcb5\link_test_bcb5_sd.lib bcb5\link_test_bcb5_sd.exe bcb5\liblink_test_bcb5_md bcb5\liblink_test_bcb5_md.lib bcb5\liblink_test_bcb5_md.exe bcb5\liblink_test_bcb5_sd bcb5\liblink_test_bcb5_sd.lib bcb5\liblink_test_bcb5_sd.exe

clean :  liblink_test_bcb5_ss_clean liblink_test_bcb5_ms_clean link_test_bcb5_md_clean link_test_bcb5_sd_clean liblink_test_bcb5_md_clean liblink_test_bcb5_sd_clean

install : all
	copy bcb5\liblink_test_bcb5_ss.lib $(BCROOT)\lib
	copy bcb5\liblink_test_bcb5_ms.lib $(BCROOT)\lib
	copy bcb5\link_test_bcb5_md.lib $(BCROOT)\lib
	copy bcb5\link_test_bcb5_md.dll $(BCROOT)\bin
	copy bcb5\link_test_bcb5_md.tds $(BCROOT)\bin
	copy bcb5\link_test_bcb5_sd.lib $(BCROOT)\lib
	copy bcb5\link_test_bcb5_sd.dll $(BCROOT)\bin
	copy bcb5\link_test_bcb5_sd.tds $(BCROOT)\bin
	copy bcb5\liblink_test_bcb5_md.lib $(BCROOT)\lib
	copy bcb5\liblink_test_bcb5_sd.lib $(BCROOT)\lib

bcb5 :
	-@mkdir bcb5


########################################################
#
# section for liblink_test_bcb5_ss.lib
#
########################################################
bcb5\liblink_test_bcb5_ss\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb5\liblink_test_bcb5_ss\link_test.obj link_test.cpp
|

bcb5\liblink_test_bcb5_ss : 
	-@mkdir bcb5\liblink_test_bcb5_ss

liblink_test_bcb5_ss_clean :
	del bcb5\liblink_test_bcb5_ss\*.obj
	del bcb5\liblink_test_bcb5_ss\*.il?
	del bcb5\liblink_test_bcb5_ss\*.csm
	del bcb5\liblink_test_bcb5_ss\*.tds

bcb5\liblink_test_bcb5_ss.lib : bcb5\liblink_test_bcb5_ss\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\liblink_test_bcb5_ss.lib  -+bcb5\liblink_test_bcb5_ss\link_test.obj
|

bcb5\liblink_test_bcb5_ss.exe : main.cpp bcb5\liblink_test_bcb5_ss.lib
	bcc32 $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb5 -e./bcb5/liblink_test_bcb5_ss.exe main.cpp
   bcb5\liblink_test_bcb5_ss.exe

########################################################
#
# section for liblink_test_bcb5_ms.lib
#
########################################################
bcb5\liblink_test_bcb5_ms\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb5\liblink_test_bcb5_ms\link_test.obj link_test.cpp
|

bcb5\liblink_test_bcb5_ms : 
	-@mkdir bcb5\liblink_test_bcb5_ms

liblink_test_bcb5_ms_clean :
	del bcb5\liblink_test_bcb5_ms\*.obj
	del bcb5\liblink_test_bcb5_ms\*.il?
	del bcb5\liblink_test_bcb5_ms\*.csm
	del bcb5\liblink_test_bcb5_ms\*.tds

bcb5\liblink_test_bcb5_ms.lib : bcb5\liblink_test_bcb5_ms\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\liblink_test_bcb5_ms.lib  -+bcb5\liblink_test_bcb5_ms\link_test.obj
|

bcb5\liblink_test_bcb5_ms.exe : main.cpp bcb5\liblink_test_bcb5_ms.lib
	bcc32 $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb5 -e./bcb5/liblink_test_bcb5_ms.exe main.cpp
   bcb5\liblink_test_bcb5_ms.exe

########################################################
#
# section for link_test_bcb5_md.lib
#
########################################################
bcb5\link_test_bcb5_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb5\link_test_bcb5_md\link_test.obj link_test.cpp
|

bcb5\link_test_bcb5_md :
	-@mkdir bcb5\link_test_bcb5_md

link_test_bcb5_md_clean :
	del bcb5\link_test_bcb5_md\*.obj
	del bcb5\link_test_bcb5_md\*.il?
	del bcb5\link_test_bcb5_md\*.csm
	del bcb5\link_test_bcb5_md\*.tds
	del bcb5\*.tds

bcb5\link_test_bcb5_md.lib : bcb5\link_test_bcb5_md\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\link_test_bcb5_md.dll $(XLFLAGS)  bcb5\link_test_bcb5_md\link_test.obj $(LIBS)
|
	implib -w bcb5\link_test_bcb5_md.lib bcb5\link_test_bcb5_md.dll

bcb5\link_test_bcb5_md.exe : main.cpp bcb5\link_test_bcb5_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb5 -e./bcb5/link_test_bcb5_md.exe main.cpp
   bcb5\link_test_bcb5_md.exe

########################################################
#
# section for link_test_bcb5_sd.lib
#
########################################################
bcb5\link_test_bcb5_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb5\link_test_bcb5_sd\link_test.obj link_test.cpp
|

bcb5\link_test_bcb5_sd :
	-@mkdir bcb5\link_test_bcb5_sd

link_test_bcb5_sd_clean :
	del bcb5\link_test_bcb5_sd\*.obj
	del bcb5\link_test_bcb5_sd\*.il?
	del bcb5\link_test_bcb5_sd\*.csm
	del bcb5\link_test_bcb5_sd\*.tds
	del bcb5\*.tds

bcb5\link_test_bcb5_sd.lib : bcb5\link_test_bcb5_sd\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\link_test_bcb5_sd.dll $(XLFLAGS)  bcb5\link_test_bcb5_sd\link_test.obj $(LIBS)
|
	implib -w bcb5\link_test_bcb5_sd.lib bcb5\link_test_bcb5_sd.dll

bcb5\link_test_bcb5_sd.exe : main.cpp bcb5\link_test_bcb5_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb5 -e./bcb5/link_test_bcb5_sd.exe main.cpp
   bcb5\link_test_bcb5_sd.exe

########################################################
#
# section for liblink_test_bcb5_md.lib
#
########################################################
bcb5\liblink_test_bcb5_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\liblink_test_bcb5_md\link_test.obj link_test.cpp
|

bcb5\liblink_test_bcb5_md : 
	-@mkdir bcb5\liblink_test_bcb5_md

liblink_test_bcb5_md_clean :
	del bcb5\liblink_test_bcb5_md\*.obj
	del bcb5\liblink_test_bcb5_md\*.il?
	del bcb5\liblink_test_bcb5_md\*.csm
	del bcb5\liblink_test_bcb5_md\*.tds

bcb5\liblink_test_bcb5_md.lib : bcb5\liblink_test_bcb5_md\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\liblink_test_bcb5_md.lib  -+bcb5\liblink_test_bcb5_md\link_test.obj
|

bcb5\liblink_test_bcb5_md.exe : main.cpp bcb5\liblink_test_bcb5_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb5 -e./bcb5/liblink_test_bcb5_md.exe main.cpp
   bcb5\liblink_test_bcb5_md.exe

########################################################
#
# section for liblink_test_bcb5_sd.lib
#
########################################################
bcb5\liblink_test_bcb5_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\liblink_test_bcb5_sd\link_test.obj link_test.cpp
|

bcb5\liblink_test_bcb5_sd : 
	-@mkdir bcb5\liblink_test_bcb5_sd

liblink_test_bcb5_sd_clean :
	del bcb5\liblink_test_bcb5_sd\*.obj
	del bcb5\liblink_test_bcb5_sd\*.il?
	del bcb5\liblink_test_bcb5_sd\*.csm
	del bcb5\liblink_test_bcb5_sd\*.tds

bcb5\liblink_test_bcb5_sd.lib : bcb5\liblink_test_bcb5_sd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\liblink_test_bcb5_sd.lib  -+bcb5\liblink_test_bcb5_sd\link_test.obj
|

bcb5\liblink_test_bcb5_sd.exe : main.cpp bcb5\liblink_test_bcb5_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb5 -e./bcb5/liblink_test_bcb5_sd.exe main.cpp
   bcb5\liblink_test_bcb5_sd.exe

