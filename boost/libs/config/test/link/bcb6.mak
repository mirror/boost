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

all : bcb6 bcb6\liblink_test_bcb6_ss bcb6\liblink_test_bcb6_ss.lib bcb6\liblink_test_bcb6_ss.exe bcb6\liblink_test_bcb6_ms bcb6\liblink_test_bcb6_ms.lib bcb6\liblink_test_bcb6_ms.exe bcb6\link_test_bcb6_md bcb6\link_test_bcb6_md.lib bcb6\link_test_bcb6_md.exe bcb6\link_test_bcb6_sd bcb6\link_test_bcb6_sd.lib bcb6\link_test_bcb6_sd.exe bcb6\liblink_test_bcb6_md bcb6\liblink_test_bcb6_md.lib bcb6\liblink_test_bcb6_md.exe bcb6\liblink_test_bcb6_sd bcb6\liblink_test_bcb6_sd.lib bcb6\liblink_test_bcb6_sd.exe bcb6\liblink_test_bcb6_ssdd bcb6\liblink_test_bcb6_ssdd.lib bcb6\liblink_test_bcb6_ssdd.exe bcb6\liblink_test_bcb6_msdd bcb6\liblink_test_bcb6_msdd.lib bcb6\liblink_test_bcb6_msdd.exe bcb6\link_test_bcb6_mddd bcb6\link_test_bcb6_mddd.lib bcb6\link_test_bcb6_mddd.exe bcb6\link_test_bcb6_sddd bcb6\link_test_bcb6_sddd.lib bcb6\link_test_bcb6_sddd.exe bcb6\liblink_test_bcb6_mddd bcb6\liblink_test_bcb6_mddd.lib bcb6\liblink_test_bcb6_mddd.exe bcb6\liblink_test_bcb6_sddd bcb6\liblink_test_bcb6_sddd.lib bcb6\liblink_test_bcb6_sddd.exe

clean :  liblink_test_bcb6_ss_clean liblink_test_bcb6_ms_clean link_test_bcb6_md_clean link_test_bcb6_sd_clean liblink_test_bcb6_md_clean liblink_test_bcb6_sd_clean liblink_test_bcb6_ssdd_clean liblink_test_bcb6_msdd_clean link_test_bcb6_mddd_clean link_test_bcb6_sddd_clean liblink_test_bcb6_mddd_clean liblink_test_bcb6_sddd_clean

install : all
	copy bcb6\liblink_test_bcb6_ss.lib $(BCROOT)\lib
	copy bcb6\liblink_test_bcb6_ms.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_md.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_md.dll $(BCROOT)\bin
	copy bcb6\link_test_bcb6_md.tds $(BCROOT)\bin
	copy bcb6\link_test_bcb6_sd.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_sd.dll $(BCROOT)\bin
	copy bcb6\link_test_bcb6_sd.tds $(BCROOT)\bin
	copy bcb6\liblink_test_bcb6_md.lib $(BCROOT)\lib
	copy bcb6\liblink_test_bcb6_sd.lib $(BCROOT)\lib
	copy bcb6\liblink_test_bcb6_ssdd.lib $(BCROOT)\lib
	copy bcb6\liblink_test_bcb6_msdd.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_mddd.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_mddd.dll $(BCROOT)\bin
	copy bcb6\link_test_bcb6_mddd.tds $(BCROOT)\bin
	copy bcb6\link_test_bcb6_sddd.lib $(BCROOT)\lib
	copy bcb6\link_test_bcb6_sddd.dll $(BCROOT)\bin
	copy bcb6\link_test_bcb6_sddd.tds $(BCROOT)\bin
	copy bcb6\liblink_test_bcb6_mddd.lib $(BCROOT)\lib
	copy bcb6\liblink_test_bcb6_sddd.lib $(BCROOT)\lib

bcb6 :
	-@mkdir bcb6


########################################################
#
# section for liblink_test_bcb6_ss.lib
#
########################################################
bcb6\liblink_test_bcb6_ss\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb6\liblink_test_bcb6_ss\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_ss : 
	-@mkdir bcb6\liblink_test_bcb6_ss

liblink_test_bcb6_ss_clean :
	del bcb6\liblink_test_bcb6_ss\*.obj
	del bcb6\liblink_test_bcb6_ss\*.il?
	del bcb6\liblink_test_bcb6_ss\*.csm
	del bcb6\liblink_test_bcb6_ss\*.tds

bcb6\liblink_test_bcb6_ss.lib : bcb6\liblink_test_bcb6_ss\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_ss.lib  -+bcb6\liblink_test_bcb6_ss\link_test.obj
|

bcb6\liblink_test_bcb6_ss.exe : main.cpp bcb6\liblink_test_bcb6_ss.lib
	bcc32 $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_ss.exe main.cpp
   bcb6\liblink_test_bcb6_ss.exe

########################################################
#
# section for liblink_test_bcb6_ms.lib
#
########################################################
bcb6\liblink_test_bcb6_ms\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb6\liblink_test_bcb6_ms\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_ms : 
	-@mkdir bcb6\liblink_test_bcb6_ms

liblink_test_bcb6_ms_clean :
	del bcb6\liblink_test_bcb6_ms\*.obj
	del bcb6\liblink_test_bcb6_ms\*.il?
	del bcb6\liblink_test_bcb6_ms\*.csm
	del bcb6\liblink_test_bcb6_ms\*.tds

bcb6\liblink_test_bcb6_ms.lib : bcb6\liblink_test_bcb6_ms\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_ms.lib  -+bcb6\liblink_test_bcb6_ms\link_test.obj
|

bcb6\liblink_test_bcb6_ms.exe : main.cpp bcb6\liblink_test_bcb6_ms.lib
	bcc32 $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_ms.exe main.cpp
   bcb6\liblink_test_bcb6_ms.exe

########################################################
#
# section for link_test_bcb6_md.lib
#
########################################################
bcb6\link_test_bcb6_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb6\link_test_bcb6_md\link_test.obj link_test.cpp
|

bcb6\link_test_bcb6_md :
	-@mkdir bcb6\link_test_bcb6_md

link_test_bcb6_md_clean :
	del bcb6\link_test_bcb6_md\*.obj
	del bcb6\link_test_bcb6_md\*.il?
	del bcb6\link_test_bcb6_md\*.csm
	del bcb6\link_test_bcb6_md\*.tds
	del bcb6\*.tds

bcb6\link_test_bcb6_md.lib : bcb6\link_test_bcb6_md\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\link_test_bcb6_md.dll $(XLFLAGS)  bcb6\link_test_bcb6_md\link_test.obj $(LIBS)
|
	implib -w bcb6\link_test_bcb6_md.lib bcb6\link_test_bcb6_md.dll

bcb6\link_test_bcb6_md.exe : main.cpp bcb6\link_test_bcb6_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb6 -e./bcb6/link_test_bcb6_md.exe main.cpp
   bcb6\link_test_bcb6_md.exe

########################################################
#
# section for link_test_bcb6_sd.lib
#
########################################################
bcb6\link_test_bcb6_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb6\link_test_bcb6_sd\link_test.obj link_test.cpp
|

bcb6\link_test_bcb6_sd :
	-@mkdir bcb6\link_test_bcb6_sd

link_test_bcb6_sd_clean :
	del bcb6\link_test_bcb6_sd\*.obj
	del bcb6\link_test_bcb6_sd\*.il?
	del bcb6\link_test_bcb6_sd\*.csm
	del bcb6\link_test_bcb6_sd\*.tds
	del bcb6\*.tds

bcb6\link_test_bcb6_sd.lib : bcb6\link_test_bcb6_sd\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\link_test_bcb6_sd.dll $(XLFLAGS)  bcb6\link_test_bcb6_sd\link_test.obj $(LIBS)
|
	implib -w bcb6\link_test_bcb6_sd.lib bcb6\link_test_bcb6_sd.dll

bcb6\link_test_bcb6_sd.exe : main.cpp bcb6\link_test_bcb6_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb6 -e./bcb6/link_test_bcb6_sd.exe main.cpp
   bcb6\link_test_bcb6_sd.exe

########################################################
#
# section for liblink_test_bcb6_md.lib
#
########################################################
bcb6\liblink_test_bcb6_md\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\liblink_test_bcb6_md\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_md : 
	-@mkdir bcb6\liblink_test_bcb6_md

liblink_test_bcb6_md_clean :
	del bcb6\liblink_test_bcb6_md\*.obj
	del bcb6\liblink_test_bcb6_md\*.il?
	del bcb6\liblink_test_bcb6_md\*.csm
	del bcb6\liblink_test_bcb6_md\*.tds

bcb6\liblink_test_bcb6_md.lib : bcb6\liblink_test_bcb6_md\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_md.lib  -+bcb6\liblink_test_bcb6_md\link_test.obj
|

bcb6\liblink_test_bcb6_md.exe : main.cpp bcb6\liblink_test_bcb6_md.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_md.exe main.cpp
   bcb6\liblink_test_bcb6_md.exe

########################################################
#
# section for liblink_test_bcb6_sd.lib
#
########################################################
bcb6\liblink_test_bcb6_sd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\liblink_test_bcb6_sd\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_sd : 
	-@mkdir bcb6\liblink_test_bcb6_sd

liblink_test_bcb6_sd_clean :
	del bcb6\liblink_test_bcb6_sd\*.obj
	del bcb6\liblink_test_bcb6_sd\*.il?
	del bcb6\liblink_test_bcb6_sd\*.csm
	del bcb6\liblink_test_bcb6_sd\*.tds

bcb6\liblink_test_bcb6_sd.lib : bcb6\liblink_test_bcb6_sd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_sd.lib  -+bcb6\liblink_test_bcb6_sd\link_test.obj
|

bcb6\liblink_test_bcb6_sd.exe : main.cpp bcb6\liblink_test_bcb6_sd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_sd.exe main.cpp
   bcb6\liblink_test_bcb6_sd.exe

########################################################
#
# section for liblink_test_bcb6_ssdd.lib
#
########################################################
bcb6\liblink_test_bcb6_ssdd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb6\liblink_test_bcb6_ssdd\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_ssdd : 
	-@mkdir bcb6\liblink_test_bcb6_ssdd

liblink_test_bcb6_ssdd_clean :
	del bcb6\liblink_test_bcb6_ssdd\*.obj
	del bcb6\liblink_test_bcb6_ssdd\*.il?
	del bcb6\liblink_test_bcb6_ssdd\*.csm
	del bcb6\liblink_test_bcb6_ssdd\*.tds

bcb6\liblink_test_bcb6_ssdd.lib : bcb6\liblink_test_bcb6_ssdd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_ssdd.lib  -+bcb6\liblink_test_bcb6_ssdd\link_test.obj
|

bcb6\liblink_test_bcb6_ssdd.exe : main.cpp bcb6\liblink_test_bcb6_ssdd.lib
	bcc32 $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_ssdd.exe main.cpp
   bcb6\liblink_test_bcb6_ssdd.exe

########################################################
#
# section for liblink_test_bcb6_msdd.lib
#
########################################################
bcb6\liblink_test_bcb6_msdd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -obcb6\liblink_test_bcb6_msdd\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_msdd : 
	-@mkdir bcb6\liblink_test_bcb6_msdd

liblink_test_bcb6_msdd_clean :
	del bcb6\liblink_test_bcb6_msdd\*.obj
	del bcb6\liblink_test_bcb6_msdd\*.il?
	del bcb6\liblink_test_bcb6_msdd\*.csm
	del bcb6\liblink_test_bcb6_msdd\*.tds

bcb6\liblink_test_bcb6_msdd.lib : bcb6\liblink_test_bcb6_msdd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_msdd.lib  -+bcb6\liblink_test_bcb6_msdd\link_test.obj
|

bcb6\liblink_test_bcb6_msdd.exe : main.cpp bcb6\liblink_test_bcb6_msdd.lib
	bcc32 $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_msdd.exe main.cpp
   bcb6\liblink_test_bcb6_msdd.exe

########################################################
#
# section for link_test_bcb6_mddd.lib
#
########################################################
bcb6\link_test_bcb6_mddd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb6\link_test_bcb6_mddd\link_test.obj link_test.cpp
|

bcb6\link_test_bcb6_mddd :
	-@mkdir bcb6\link_test_bcb6_mddd

link_test_bcb6_mddd_clean :
	del bcb6\link_test_bcb6_mddd\*.obj
	del bcb6\link_test_bcb6_mddd\*.il?
	del bcb6\link_test_bcb6_mddd\*.csm
	del bcb6\link_test_bcb6_mddd\*.tds
	del bcb6\*.tds

bcb6\link_test_bcb6_mddd.lib : bcb6\link_test_bcb6_mddd\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\link_test_bcb6_mddd.dll $(XLFLAGS)  bcb6\link_test_bcb6_mddd\link_test.obj $(LIBS)
|
	implib -w bcb6\link_test_bcb6_mddd.lib bcb6\link_test_bcb6_mddd.dll

bcb6\link_test_bcb6_mddd.exe : main.cpp bcb6\link_test_bcb6_mddd.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb6 -e./bcb6/link_test_bcb6_mddd.exe main.cpp
   bcb6\link_test_bcb6_mddd.exe

########################################################
#
# section for link_test_bcb6_sddd.lib
#
########################################################
bcb6\link_test_bcb6_sddd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -obcb6\link_test_bcb6_sddd\link_test.obj link_test.cpp
|

bcb6\link_test_bcb6_sddd :
	-@mkdir bcb6\link_test_bcb6_sddd

link_test_bcb6_sddd_clean :
	del bcb6\link_test_bcb6_sddd\*.obj
	del bcb6\link_test_bcb6_sddd\*.il?
	del bcb6\link_test_bcb6_sddd\*.csm
	del bcb6\link_test_bcb6_sddd\*.tds
	del bcb6\*.tds

bcb6\link_test_bcb6_sddd.lib : bcb6\link_test_bcb6_sddd\link_test.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\link_test_bcb6_sddd.dll $(XLFLAGS)  bcb6\link_test_bcb6_sddd\link_test.obj $(LIBS)
|
	implib -w bcb6\link_test_bcb6_sddd.lib bcb6\link_test_bcb6_sddd.dll

bcb6\link_test_bcb6_sddd.exe : main.cpp bcb6\link_test_bcb6_sddd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_DYN_LINK -L./bcb6 -e./bcb6/link_test_bcb6_sddd.exe main.cpp
   bcb6\link_test_bcb6_sddd.exe

########################################################
#
# section for liblink_test_bcb6_mddd.lib
#
########################################################
bcb6\liblink_test_bcb6_mddd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\liblink_test_bcb6_mddd\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_mddd : 
	-@mkdir bcb6\liblink_test_bcb6_mddd

liblink_test_bcb6_mddd_clean :
	del bcb6\liblink_test_bcb6_mddd\*.obj
	del bcb6\liblink_test_bcb6_mddd\*.il?
	del bcb6\liblink_test_bcb6_mddd\*.csm
	del bcb6\liblink_test_bcb6_mddd\*.tds

bcb6\liblink_test_bcb6_mddd.lib : bcb6\liblink_test_bcb6_mddd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_mddd.lib  -+bcb6\liblink_test_bcb6_mddd\link_test.obj
|

bcb6\liblink_test_bcb6_mddd.exe : main.cpp bcb6\liblink_test_bcb6_mddd.lib
	bcc32 $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_mddd.exe main.cpp
   bcb6\liblink_test_bcb6_mddd.exe

########################################################
#
# section for liblink_test_bcb6_sddd.lib
#
########################################################
bcb6\liblink_test_bcb6_sddd\link_test.obj: link_test.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\liblink_test_bcb6_sddd\link_test.obj link_test.cpp
|

bcb6\liblink_test_bcb6_sddd : 
	-@mkdir bcb6\liblink_test_bcb6_sddd

liblink_test_bcb6_sddd_clean :
	del bcb6\liblink_test_bcb6_sddd\*.obj
	del bcb6\liblink_test_bcb6_sddd\*.il?
	del bcb6\liblink_test_bcb6_sddd\*.csm
	del bcb6\liblink_test_bcb6_sddd\*.tds

bcb6\liblink_test_bcb6_sddd.lib : bcb6\liblink_test_bcb6_sddd\link_test.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\liblink_test_bcb6_sddd.lib  -+bcb6\liblink_test_bcb6_sddd\link_test.obj
|

bcb6\liblink_test_bcb6_sddd.exe : main.cpp bcb6\liblink_test_bcb6_sddd.lib
	bcc32 $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -L./bcb6 -e./bcb6/liblink_test_bcb6_sddd.exe main.cpp
   bcb6\liblink_test_bcb6_sddd.exe

