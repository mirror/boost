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


ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : bcb4 bcb4\bcb4re300 bcb4\bcb4re300.lib bcb4\bcb4re300m bcb4\bcb4re300m.lib bcb4\bcb4re300v bcb4\bcb4re300v.lib bcb4\bcb4re300lv bcb4\bcb4re300lv.lib bcb4\bcb4re300lm bcb4\bcb4re300lm.lib bcb4\bcb4re300l bcb4\bcb4re300l.lib

clean :  bcb4re300_clean bcb4re300m_clean bcb4re300v_clean bcb4re300lv_clean bcb4re300lm_clean bcb4re300l_clean

install : all
	copy bcb4\bcb4re300.lib $(BCROOT)\lib
	copy bcb4\bcb4re300m.lib $(BCROOT)\lib
	copy bcb4\bcb4re300v.lib $(BCROOT)\lib
	copy bcb4\bcb4re300lv.lib $(BCROOT)\lib
	copy bcb4\bcb4re300lv.dll $(BCROOT)\bin
	copy bcb4\bcb4re300lm.lib $(BCROOT)\lib
	copy bcb4\bcb4re300lm.dll $(BCROOT)\bin
	copy bcb4\bcb4re300l.lib $(BCROOT)\lib
	copy bcb4\bcb4re300l.dll $(BCROOT)\bin

bcb4 :
	-mkdir bcb4


########################################################
#
# section for bcb4re300.lib
#
########################################################
bcb4\bcb4re300\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300 : 
	-mkdir bcb4\bcb4re300

bcb4re300_clean :
	del bcb4\bcb4re300\*.obj
	del bcb4\bcb4re300\*.il?
	del bcb4\bcb4re300\*.csm
	del bcb4\bcb4re300\*.tds

bcb4\bcb4re300.lib : bcb4\bcb4re300\c_regex_traits.obj bcb4\bcb4re300\c_regex_traits_common.obj bcb4\bcb4re300\cpp_regex_traits.obj bcb4\bcb4re300\cregex.obj bcb4\bcb4re300\fileiter.obj bcb4\bcb4re300\posix_api.obj bcb4\bcb4re300\regex.obj bcb4\bcb4re300\regex_debug.obj bcb4\bcb4re300\regex_synch.obj bcb4\bcb4re300\w32_regex_traits.obj bcb4\bcb4re300\wide_posix_api.obj
	tlib @&&|
/P32 /u /a $(XSFLAGS) bcb4\bcb4re300.lib  +bcb4\bcb4re300\c_regex_traits.obj +bcb4\bcb4re300\c_regex_traits_common.obj +bcb4\bcb4re300\cpp_regex_traits.obj +bcb4\bcb4re300\cregex.obj +bcb4\bcb4re300\fileiter.obj +bcb4\bcb4re300\posix_api.obj +bcb4\bcb4re300\regex.obj +bcb4\bcb4re300\regex_debug.obj +bcb4\bcb4re300\regex_synch.obj +bcb4\bcb4re300\w32_regex_traits.obj +bcb4\bcb4re300\wide_posix_api.obj
|

########################################################
#
# section for bcb4re300m.lib
#
########################################################
bcb4\bcb4re300m\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300m\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300m\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300m\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300m\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300m\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300m\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300m\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300m\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300m\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300m\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300m\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300m : 
	-mkdir bcb4\bcb4re300m

bcb4re300m_clean :
	del bcb4\bcb4re300m\*.obj
	del bcb4\bcb4re300m\*.il?
	del bcb4\bcb4re300m\*.csm
	del bcb4\bcb4re300m\*.tds

bcb4\bcb4re300m.lib : bcb4\bcb4re300m\c_regex_traits.obj bcb4\bcb4re300m\c_regex_traits_common.obj bcb4\bcb4re300m\cpp_regex_traits.obj bcb4\bcb4re300m\cregex.obj bcb4\bcb4re300m\fileiter.obj bcb4\bcb4re300m\posix_api.obj bcb4\bcb4re300m\regex.obj bcb4\bcb4re300m\regex_debug.obj bcb4\bcb4re300m\regex_synch.obj bcb4\bcb4re300m\w32_regex_traits.obj bcb4\bcb4re300m\wide_posix_api.obj
	tlib @&&|
/P32 /u /a $(XSFLAGS) bcb4\bcb4re300m.lib  +bcb4\bcb4re300m\c_regex_traits.obj +bcb4\bcb4re300m\c_regex_traits_common.obj +bcb4\bcb4re300m\cpp_regex_traits.obj +bcb4\bcb4re300m\cregex.obj +bcb4\bcb4re300m\fileiter.obj +bcb4\bcb4re300m\posix_api.obj +bcb4\bcb4re300m\regex.obj +bcb4\bcb4re300m\regex_debug.obj +bcb4\bcb4re300m\regex_synch.obj +bcb4\bcb4re300m\w32_regex_traits.obj +bcb4\bcb4re300m\wide_posix_api.obj
|

########################################################
#
# section for bcb4re300v.lib
#
########################################################
bcb4\bcb4re300v\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300v\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300v\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300v\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300v\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300v\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300v\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300v\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300v\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300v\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300v\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb4\bcb4re300v\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300v : 
	-mkdir bcb4\bcb4re300v

bcb4re300v_clean :
	del bcb4\bcb4re300v\*.obj
	del bcb4\bcb4re300v\*.il?
	del bcb4\bcb4re300v\*.csm
	del bcb4\bcb4re300v\*.tds

bcb4\bcb4re300v.lib : bcb4\bcb4re300v\c_regex_traits.obj bcb4\bcb4re300v\c_regex_traits_common.obj bcb4\bcb4re300v\cpp_regex_traits.obj bcb4\bcb4re300v\cregex.obj bcb4\bcb4re300v\fileiter.obj bcb4\bcb4re300v\posix_api.obj bcb4\bcb4re300v\regex.obj bcb4\bcb4re300v\regex_debug.obj bcb4\bcb4re300v\regex_synch.obj bcb4\bcb4re300v\w32_regex_traits.obj bcb4\bcb4re300v\wide_posix_api.obj
	tlib @&&|
/P32 /u /a $(XSFLAGS) bcb4\bcb4re300v.lib  +bcb4\bcb4re300v\c_regex_traits.obj +bcb4\bcb4re300v\c_regex_traits_common.obj +bcb4\bcb4re300v\cpp_regex_traits.obj +bcb4\bcb4re300v\cregex.obj +bcb4\bcb4re300v\fileiter.obj +bcb4\bcb4re300v\posix_api.obj +bcb4\bcb4re300v\regex.obj +bcb4\bcb4re300v\regex_debug.obj +bcb4\bcb4re300v\regex_synch.obj +bcb4\bcb4re300v\w32_regex_traits.obj +bcb4\bcb4re300v\wide_posix_api.obj
|

########################################################
#
# section for bcb4re300lv.lib
#
########################################################
bcb4\bcb4re300lv\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300lv\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300lv\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300lv\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300lv\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300lv\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300lv\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300lv\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300lv\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300lv\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300lv\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lv\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300lv :
	-mkdir bcb4\bcb4re300lv

bcb4re300lv_clean :
	del bcb4\bcb4re300lv\*.obj
	del bcb4\bcb4re300lv\*.il?
	del bcb4\bcb4re300lv\*.csm
	del bcb4\bcb4re300lv\*.tds
	del bcb4\*.tds

bcb4\bcb4re300lv.lib : bcb4\bcb4re300lv\c_regex_traits.obj bcb4\bcb4re300lv\c_regex_traits_common.obj bcb4\bcb4re300lv\cpp_regex_traits.obj bcb4\bcb4re300lv\cregex.obj bcb4\bcb4re300lv\fileiter.obj bcb4\bcb4re300lv\posix_api.obj bcb4\bcb4re300lv\regex.obj bcb4\bcb4re300lv\regex_debug.obj bcb4\bcb4re300lv\regex_synch.obj bcb4\bcb4re300lv\w32_regex_traits.obj bcb4\bcb4re300lv\wide_posix_api.obj
	bcc32 @&&|
-DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\bcb4re300lv.dll $(XLFLAGS)  bcb4\bcb4re300lv\c_regex_traits.obj bcb4\bcb4re300lv\c_regex_traits_common.obj bcb4\bcb4re300lv\cpp_regex_traits.obj bcb4\bcb4re300lv\cregex.obj bcb4\bcb4re300lv\fileiter.obj bcb4\bcb4re300lv\posix_api.obj bcb4\bcb4re300lv\regex.obj bcb4\bcb4re300lv\regex_debug.obj bcb4\bcb4re300lv\regex_synch.obj bcb4\bcb4re300lv\w32_regex_traits.obj bcb4\bcb4re300lv\wide_posix_api.obj $(LIBS)
|
	implib -c bcb4\bcb4re300lv.lib bcb4\bcb4re300lv.dll

########################################################
#
# section for bcb4re300lm.lib
#
########################################################
bcb4\bcb4re300lm\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300lm\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300lm\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300lm\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300lm\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300lm\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300lm\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300lm\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300lm\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300lm\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300lm\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300lm\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300lm :
	-mkdir bcb4\bcb4re300lm

bcb4re300lm_clean :
	del bcb4\bcb4re300lm\*.obj
	del bcb4\bcb4re300lm\*.il?
	del bcb4\bcb4re300lm\*.csm
	del bcb4\bcb4re300lm\*.tds
	del bcb4\*.tds

bcb4\bcb4re300lm.lib : bcb4\bcb4re300lm\c_regex_traits.obj bcb4\bcb4re300lm\c_regex_traits_common.obj bcb4\bcb4re300lm\cpp_regex_traits.obj bcb4\bcb4re300lm\cregex.obj bcb4\bcb4re300lm\fileiter.obj bcb4\bcb4re300lm\posix_api.obj bcb4\bcb4re300lm\regex.obj bcb4\bcb4re300lm\regex_debug.obj bcb4\bcb4re300lm\regex_synch.obj bcb4\bcb4re300lm\w32_regex_traits.obj bcb4\bcb4re300lm\wide_posix_api.obj
	bcc32 @&&|
-DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\bcb4re300lm.dll $(XLFLAGS)  bcb4\bcb4re300lm\c_regex_traits.obj bcb4\bcb4re300lm\c_regex_traits_common.obj bcb4\bcb4re300lm\cpp_regex_traits.obj bcb4\bcb4re300lm\cregex.obj bcb4\bcb4re300lm\fileiter.obj bcb4\bcb4re300lm\posix_api.obj bcb4\bcb4re300lm\regex.obj bcb4\bcb4re300lm\regex_debug.obj bcb4\bcb4re300lm\regex_synch.obj bcb4\bcb4re300lm\w32_regex_traits.obj bcb4\bcb4re300lm\wide_posix_api.obj $(LIBS)
|
	implib -c bcb4\bcb4re300lm.lib bcb4\bcb4re300lm.dll

########################################################
#
# section for bcb4re300l.lib
#
########################################################
bcb4\bcb4re300l\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\bcb4re300l\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\bcb4re300l\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\bcb4re300l\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\cregex.obj ../src/cregex.cpp
|

bcb4\bcb4re300l\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\fileiter.obj ../src/fileiter.cpp
|

bcb4\bcb4re300l\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\posix_api.obj ../src/posix_api.cpp
|

bcb4\bcb4re300l\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\regex.obj ../src/regex.cpp
|

bcb4\bcb4re300l\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\bcb4re300l\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\bcb4re300l\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\bcb4re300l\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\bcb4re300l\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\bcb4re300l :
	-mkdir bcb4\bcb4re300l

bcb4re300l_clean :
	del bcb4\bcb4re300l\*.obj
	del bcb4\bcb4re300l\*.il?
	del bcb4\bcb4re300l\*.csm
	del bcb4\bcb4re300l\*.tds
	del bcb4\*.tds

bcb4\bcb4re300l.lib : bcb4\bcb4re300l\c_regex_traits.obj bcb4\bcb4re300l\c_regex_traits_common.obj bcb4\bcb4re300l\cpp_regex_traits.obj bcb4\bcb4re300l\cregex.obj bcb4\bcb4re300l\fileiter.obj bcb4\bcb4re300l\posix_api.obj bcb4\bcb4re300l\regex.obj bcb4\bcb4re300l\regex_debug.obj bcb4\bcb4re300l\regex_synch.obj bcb4\bcb4re300l\w32_regex_traits.obj bcb4\bcb4re300l\wide_posix_api.obj
	bcc32 @&&|
-DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\bcb4re300l.dll $(XLFLAGS)  bcb4\bcb4re300l\c_regex_traits.obj bcb4\bcb4re300l\c_regex_traits_common.obj bcb4\bcb4re300l\cpp_regex_traits.obj bcb4\bcb4re300l\cregex.obj bcb4\bcb4re300l\fileiter.obj bcb4\bcb4re300l\posix_api.obj bcb4\bcb4re300l\regex.obj bcb4\bcb4re300l\regex_debug.obj bcb4\bcb4re300l\regex_synch.obj bcb4\bcb4re300l\w32_regex_traits.obj bcb4\bcb4re300l\wide_posix_api.obj $(LIBS)
|
	implib -c bcb4\bcb4re300l.lib bcb4\bcb4re300l.dll

