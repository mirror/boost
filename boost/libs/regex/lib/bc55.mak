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

all : bcb5 bcb5\bcb5re300 bcb5\bcb5re300.lib bcb5\bcb5re300m bcb5\bcb5re300m.lib bcb5\bcb5re300lm bcb5\bcb5re300lm.lib bcb5\bcb5re300l bcb5\bcb5re300l.lib

clean :  bcb5re300_clean bcb5re300m_clean bcb5re300lm_clean bcb5re300l_clean

install : all
	copy bcb5\bcb5re300.lib $(BCROOT)\lib
	copy bcb5\bcb5re300m.lib $(BCROOT)\lib
	copy bcb5\bcb5re300lm.lib $(BCROOT)\lib
	copy bcb5\bcb5re300lm.dll $(BCROOT)\bin
	copy bcb5\bcb5re300l.lib $(BCROOT)\lib
	copy bcb5\bcb5re300l.dll $(BCROOT)\bin

bcb5 :
	-mkdir bcb5


########################################################
#
# section for bcb5re300.lib
#
########################################################
bcb5\bcb5re300\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300 : 
	-mkdir bcb5\bcb5re300

bcb5re300_clean :
	del bcb5\bcb5re300\*.obj
	del bcb5\bcb5re300\*.il?
	del bcb5\bcb5re300\*.csm
	del bcb5\bcb5re300\*.tds

bcb5\bcb5re300.lib : bcb5\bcb5re300\c_regex_traits.obj bcb5\bcb5re300\c_regex_traits_common.obj bcb5\bcb5re300\cpp_regex_traits.obj bcb5\bcb5re300\cregex.obj bcb5\bcb5re300\fileiter.obj bcb5\bcb5re300\posix_api.obj bcb5\bcb5re300\regex.obj bcb5\bcb5re300\regex_debug.obj bcb5\bcb5re300\regex_synch.obj bcb5\bcb5re300\w32_regex_traits.obj bcb5\bcb5re300\wide_posix_api.obj
	tlib @&&|
/P32 /u /a $(XSFLAGS) bcb5\bcb5re300.lib  +bcb5\bcb5re300\c_regex_traits.obj +bcb5\bcb5re300\c_regex_traits_common.obj +bcb5\bcb5re300\cpp_regex_traits.obj +bcb5\bcb5re300\cregex.obj +bcb5\bcb5re300\fileiter.obj +bcb5\bcb5re300\posix_api.obj +bcb5\bcb5re300\regex.obj +bcb5\bcb5re300\regex_debug.obj +bcb5\bcb5re300\regex_synch.obj +bcb5\bcb5re300\w32_regex_traits.obj +bcb5\bcb5re300\wide_posix_api.obj
|

########################################################
#
# section for bcb5re300m.lib
#
########################################################
bcb5\bcb5re300m\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300m\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300m\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300m\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300m\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300m\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300m\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300m\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300m\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300m\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300m\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; $(CXXFLAGS) -obcb5\bcb5re300m\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300m : 
	-mkdir bcb5\bcb5re300m

bcb5re300m_clean :
	del bcb5\bcb5re300m\*.obj
	del bcb5\bcb5re300m\*.il?
	del bcb5\bcb5re300m\*.csm
	del bcb5\bcb5re300m\*.tds

bcb5\bcb5re300m.lib : bcb5\bcb5re300m\c_regex_traits.obj bcb5\bcb5re300m\c_regex_traits_common.obj bcb5\bcb5re300m\cpp_regex_traits.obj bcb5\bcb5re300m\cregex.obj bcb5\bcb5re300m\fileiter.obj bcb5\bcb5re300m\posix_api.obj bcb5\bcb5re300m\regex.obj bcb5\bcb5re300m\regex_debug.obj bcb5\bcb5re300m\regex_synch.obj bcb5\bcb5re300m\w32_regex_traits.obj bcb5\bcb5re300m\wide_posix_api.obj
	tlib @&&|
/P32 /u /a $(XSFLAGS) bcb5\bcb5re300m.lib  +bcb5\bcb5re300m\c_regex_traits.obj +bcb5\bcb5re300m\c_regex_traits_common.obj +bcb5\bcb5re300m\cpp_regex_traits.obj +bcb5\bcb5re300m\cregex.obj +bcb5\bcb5re300m\fileiter.obj +bcb5\bcb5re300m\posix_api.obj +bcb5\bcb5re300m\regex.obj +bcb5\bcb5re300m\regex_debug.obj +bcb5\bcb5re300m\regex_synch.obj +bcb5\bcb5re300m\w32_regex_traits.obj +bcb5\bcb5re300m\wide_posix_api.obj
|

########################################################
#
# section for bcb5re300lm.lib
#
########################################################
bcb5\bcb5re300lm\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300lm\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300lm\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300lm\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300lm\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300lm\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300lm\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300lm\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300lm\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300lm\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300lm\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300lm :
	-mkdir bcb5\bcb5re300lm

bcb5re300lm_clean :
	del bcb5\bcb5re300lm\*.obj
	del bcb5\bcb5re300lm\*.il?
	del bcb5\bcb5re300lm\*.csm
	del bcb5\bcb5re300lm\*.tds
	del bcb5\*.tds

bcb5\bcb5re300lm.lib : bcb5\bcb5re300lm\c_regex_traits.obj bcb5\bcb5re300lm\c_regex_traits_common.obj bcb5\bcb5re300lm\cpp_regex_traits.obj bcb5\bcb5re300lm\cregex.obj bcb5\bcb5re300lm\fileiter.obj bcb5\bcb5re300lm\posix_api.obj bcb5\bcb5re300lm\regex.obj bcb5\bcb5re300lm\regex_debug.obj bcb5\bcb5re300lm\regex_synch.obj bcb5\bcb5re300lm\w32_regex_traits.obj bcb5\bcb5re300lm\wide_posix_api.obj
	bcc32 @&&|
-DBOOST_RE_BUILD_DLL -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\bcb5re300lm.dll $(XLFLAGS)  bcb5\bcb5re300lm\c_regex_traits.obj bcb5\bcb5re300lm\c_regex_traits_common.obj bcb5\bcb5re300lm\cpp_regex_traits.obj bcb5\bcb5re300lm\cregex.obj bcb5\bcb5re300lm\fileiter.obj bcb5\bcb5re300lm\posix_api.obj bcb5\bcb5re300lm\regex.obj bcb5\bcb5re300lm\regex_debug.obj bcb5\bcb5re300lm\regex_synch.obj bcb5\bcb5re300lm\w32_regex_traits.obj bcb5\bcb5re300lm\wide_posix_api.obj $(LIBS)
|
	implib -c bcb5\bcb5re300lm.lib bcb5\bcb5re300lm.dll

########################################################
#
# section for bcb5re300l.lib
#
########################################################
bcb5\bcb5re300l\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300l\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300l\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300l\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300l\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300l\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300l\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300l\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300l\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300l\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300l\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300l :
	-mkdir bcb5\bcb5re300l

bcb5re300l_clean :
	del bcb5\bcb5re300l\*.obj
	del bcb5\bcb5re300l\*.il?
	del bcb5\bcb5re300l\*.csm
	del bcb5\bcb5re300l\*.tds
	del bcb5\*.tds

bcb5\bcb5re300l.lib : bcb5\bcb5re300l\c_regex_traits.obj bcb5\bcb5re300l\c_regex_traits_common.obj bcb5\bcb5re300l\cpp_regex_traits.obj bcb5\bcb5re300l\cregex.obj bcb5\bcb5re300l\fileiter.obj bcb5\bcb5re300l\posix_api.obj bcb5\bcb5re300l\regex.obj bcb5\bcb5re300l\regex_debug.obj bcb5\bcb5re300l\regex_synch.obj bcb5\bcb5re300l\w32_regex_traits.obj bcb5\bcb5re300l\wide_posix_api.obj
	bcc32 @&&|
-DBOOST_RE_BUILD_DLL -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../; -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\bcb5re300l.dll $(XLFLAGS)  bcb5\bcb5re300l\c_regex_traits.obj bcb5\bcb5re300l\c_regex_traits_common.obj bcb5\bcb5re300l\cpp_regex_traits.obj bcb5\bcb5re300l\cregex.obj bcb5\bcb5re300l\fileiter.obj bcb5\bcb5re300l\posix_api.obj bcb5\bcb5re300l\regex.obj bcb5\bcb5re300l\regex_debug.obj bcb5\bcb5re300l\regex_synch.obj bcb5\bcb5re300l\w32_regex_traits.obj bcb5\bcb5re300l\wide_posix_api.obj $(LIBS)
|
	implib -c bcb5\bcb5re300l.lib bcb5\bcb5re300l.dll

