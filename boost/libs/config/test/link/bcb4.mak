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

all : bcb4 bcb4\liblink_test_bcb4_ss bcb4\liblink_test_bcb4_ss.lib bcb4\liblink_test_bcb4_ss.exe bcb4\liblink_test_bcb4_ms bcb4\liblink_test_bcb4_ms.lib bcb4\liblink_test_bcb4_ms.exe bcb4\link_test_bcb4_md bcb4\link_test_bcb4_md.lib bcb4\link_test_bcb4_md.exe bcb4\link_test_bcb4_sd bcb4\link_test_bcb4_sd.lib bcb4\link_test_bcb4_sd.exe bcb4\liblink_test_bcb4_md bcb4\liblink_test_bcb4_md.lib bcb4\liblink_test_bcb4_md.exe bcb4\liblink_test_bcb4_sd bcb4\liblink_test_bcb4_sd.lib bcb4\liblink_test_bcb4_sd.exe

clean :  liblink_test_bcb4_ss_clean liblink_test_bcb4_ms_clean link_test_bcb4_md_clean link_test_bcb4_sd_clean liblink_test_bcb4_md_clean liblink_test_bcb4_sd_clean

install : all
	copy bcb4\liblink_test_bcb4_ss.lib $(BCROOT)\lib
	copy bcb4\liblink_test_bcb4_ms.lib $(BCROOT)\lib
	copy bcb4\link_test_bcb4_md.lib $(BCROOT)\lib
	copy bcb4\link_test_bcb4_md.dll $(BCROOT)\bin
	copy bcb4\link_test_bcb4_md.tds $(BCROOT)\bin
	copy bcb4\link_test_bcb4_sd.lib $(BCROOT)\lib
	copy bcb4\link_test_bcb4_sd.dll $(BCROOT)\bin
	copy bcb4\link_test_bcb4_sd.tds $(BCROOT)\bin
	copy bcb4\liblink_test_bcb4_md.lib $(BCROOT)\lib
	copy bcb4\liblink_test_bcb4_sd.lib $(BCROOT)\lib

bcb4 :
	-@mkdir bcb4


########################################################
#
# section for liblink_test_bcb4_ss.lib
#
########################################################
bcb4\liblink_test_bcb4_ss\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb4\liblink_test_bcb4_ss\link_test.obj link_test.cpp
|

bcb4\liblink_test_bcb4_ss : 
	-@mkdir bcb4\liblink_test_bcb4_ss

liblink_test_bcb4_ss_clean :
	del bcb4\liblink_test_bcb4_ss\*.obj
	del bcb4\liblink_test_bcb4_ss\*.il?
	del bcb4\liblink_test_bcb4_ss\*.csm
	del bcb4\liblink_test_bcb4_ss\*.tds

bcb4\liblink_test_bcb4_ss.lib : bcb4\liblink_test_bcb4_ss\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\liblink_test_bcb4_ss.lib  -+bcb4\liblink_test_bcb4_ss\link_test.obj
|

bcb4\liblink_test_bcb4_ss.exe : main.cpp bcb4\liblink_test_bcb4_ss.lib
	bcc32 $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb4 -e./bcb4/liblink_test_bcb4_ss.exe main.cpp
   bcb4\liblink_test_bcb4_ss.exe

########################################################
#
# section for liblink_test_bcb4_ms.lib
#
########################################################
bcb4\liblink_test_bcb4_ms\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb4\liblink_test_bcb4_ms\link_test.obj link_test.cpp
|

bcb4\liblink_test_bcb4_ms : 
	-@mkdir bcb4\liblink_test_bcb4_ms

liblink_test_bcb4_ms_clean :
	del bcb4\liblink_test_bcb4_ms\*.obj
	del bcb4\liblink_test_bcb4_ms\*.il?
	del bcb4\liblink_test_bcb4_ms\*.csm
	del bcb4\liblink_test_bcb4_ms\*.tds

bcb4\liblink_test_bcb4_ms.lib : bcb4\liblink_test_bcb4_ms\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\liblink_test_bcb4_ms.lib  -+bcb4\liblink_test_bcb4_ms\link_test.obj
|

bcb4\liblink_test_bcb4_ms.exe : main.cpp bcb4\liblink_test_bcb4_ms.lib
	bcc32 $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb4 -e./bcb4/liblink_test_bcb4_ms.exe main.cpp
   bcb4\liblink_test_bcb4_ms.exe

########################################################
#
# section for link_test_bcb4_md.lib
#
########################################################
bcb4\link_test_bcb4_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb4\link_test_bcb4_md\link_test.obj link_test.cpp
|

bcb4\link_test_bcb4_md :
	-@mkdir bcb4\link_test_bcb4_md

link_test_bcb4_md_clean :
	del bcb4\link_test_bcb4_md\*.obj
	del bcb4\link_test_bcb4_md\*.il?
	del bcb4\link_test_bcb4_md\*.csm
	del bcb4\link_test_bcb4_md\*.tds
	del bcb4\*.tds

bcb4\link_test_bcb4_md.lib : bcb4\link_test_bcb4_md\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\link_test_bcb4_md.dll $(XLFLAGS)  bcb4\link_test_bcb4_md\link_test.obj $(LIBS)
|
	implib -w bcb4\link_test_bcb4_md.lib bcb4\link_test_bcb4_md.dll

bcb4\link_test_bcb4_md.exe : main.cpp bcb4\link_test_bcb4_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb4 -e./bcb4/link_test_bcb4_md.exe main.cpp
   bcb4\link_test_bcb4_md.exe

########################################################
#
# section for link_test_bcb4_sd.lib
#
########################################################
bcb4\link_test_bcb4_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb4\link_test_bcb4_sd\link_test.obj link_test.cpp
|

bcb4\link_test_bcb4_sd :
	-@mkdir bcb4\link_test_bcb4_sd

link_test_bcb4_sd_clean :
	del bcb4\link_test_bcb4_sd\*.obj
	del bcb4\link_test_bcb4_sd\*.il?
	del bcb4\link_test_bcb4_sd\*.csm
	del bcb4\link_test_bcb4_sd\*.tds
	del bcb4\*.tds

bcb4\link_test_bcb4_sd.lib : bcb4\link_test_bcb4_sd\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\link_test_bcb4_sd.dll $(XLFLAGS)  bcb4\link_test_bcb4_sd\link_test.obj $(LIBS)
|
	implib -w bcb4\link_test_bcb4_sd.lib bcb4\link_test_bcb4_sd.dll

bcb4\link_test_bcb4_sd.exe : main.cpp bcb4\link_test_bcb4_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb4 -e./bcb4/link_test_bcb4_sd.exe main.cpp
   bcb4\link_test_bcb4_sd.exe

########################################################
#
# section for liblink_test_bcb4_md.lib
#
########################################################
bcb4\liblink_test_bcb4_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\liblink_test_bcb4_md\link_test.obj link_test.cpp
|

bcb4\liblink_test_bcb4_md : 
	-@mkdir bcb4\liblink_test_bcb4_md

liblink_test_bcb4_md_clean :
	del bcb4\liblink_test_bcb4_md\*.obj
	del bcb4\liblink_test_bcb4_md\*.il?
	del bcb4\liblink_test_bcb4_md\*.csm
	del bcb4\liblink_test_bcb4_md\*.tds

bcb4\liblink_test_bcb4_md.lib : bcb4\liblink_test_bcb4_md\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\liblink_test_bcb4_md.lib  -+bcb4\liblink_test_bcb4_md\link_test.obj
|

bcb4\liblink_test_bcb4_md.exe : main.cpp bcb4\liblink_test_bcb4_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb4 -e./bcb4/liblink_test_bcb4_md.exe main.cpp
   bcb4\liblink_test_bcb4_md.exe

########################################################
#
# section for liblink_test_bcb4_sd.lib
#
########################################################
bcb4\liblink_test_bcb4_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\liblink_test_bcb4_sd\link_test.obj link_test.cpp
|

bcb4\liblink_test_bcb4_sd : 
	-@mkdir bcb4\liblink_test_bcb4_sd

liblink_test_bcb4_sd_clean :
	del bcb4\liblink_test_bcb4_sd\*.obj
	del bcb4\liblink_test_bcb4_sd\*.il?
	del bcb4\liblink_test_bcb4_sd\*.csm
	del bcb4\liblink_test_bcb4_sd\*.tds

bcb4\liblink_test_bcb4_sd.lib : bcb4\liblink_test_bcb4_sd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\liblink_test_bcb4_sd.lib  -+bcb4\liblink_test_bcb4_sd\link_test.obj
|

bcb4\liblink_test_bcb4_sd.exe : main.cpp bcb4\liblink_test_bcb4_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb4 -e./bcb4/liblink_test_bcb4_sd.exe main.cpp
   bcb4\liblink_test_bcb4_sd.exe

