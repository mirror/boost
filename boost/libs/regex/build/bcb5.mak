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


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp ../../../boost/regex/v4/basic_regex.hpp ../../../boost/regex/v4/char_regex_traits.hpp ../../../boost/regex/v4/cregex.hpp ../../../boost/regex/v4/fileiter.hpp ../../../boost/regex/v4/instances.hpp ../../../boost/regex/v4/iterator_category.hpp ../../../boost/regex/v4/iterator_traits.hpp ../../../boost/regex/v4/match_flags.hpp ../../../boost/regex/v4/match_results.hpp ../../../boost/regex/v4/mem_block_cache.hpp ../../../boost/regex/v4/perl_matcher.hpp ../../../boost/regex/v4/perl_matcher_common.hpp ../../../boost/regex/v4/perl_matcher_non_recursive.hpp ../../../boost/regex/v4/perl_matcher_recursive.hpp ../../../boost/regex/v4/regbase.hpp ../../../boost/regex/v4/regex.hpp ../../../boost/regex/v4/regex_compile.hpp ../../../boost/regex/v4/regex_cstring.hpp ../../../boost/regex/v4/regex_format.hpp ../../../boost/regex/v4/regex_fwd.hpp ../../../boost/regex/v4/regex_grep.hpp ../../../boost/regex/v4/regex_iterator.hpp ../../../boost/regex/v4/regex_kmp.hpp ../../../boost/regex/v4/regex_match.hpp ../../../boost/regex/v4/regex_merge.hpp ../../../boost/regex/v4/regex_raw_buffer.hpp ../../../boost/regex/v4/regex_replace.hpp ../../../boost/regex/v4/regex_search.hpp ../../../boost/regex/v4/regex_split.hpp ../../../boost/regex/v4/regex_stack.hpp ../../../boost/regex/v4/regex_synch.hpp ../../../boost/regex/v4/regex_token_iterator.hpp ../../../boost/regex/v4/regex_traits.hpp ../../../boost/regex/v4/states.hpp ../../../boost/regex/v4/sub_match.hpp ../../../boost/regex/config/borland.hpp ../../../boost/regex/config/cstring.hpp ../../../boost/regex/config/cwchar.hpp ../../../boost/regex/config/regex_library_include.hpp

all : bcb5 bcb5\libboost_regex-bcb5-s-1_31 bcb5\libboost_regex-bcb5-s-1_31.lib bcb5\libboost_regex-bcb5-mt-s-1_31 bcb5\libboost_regex-bcb5-mt-s-1_31.lib bcb5\boost_regex-bcb5-mt-1_31 bcb5\boost_regex-bcb5-mt-1_31.lib bcb5\boost_regex-bcb5-1_31 bcb5\boost_regex-bcb5-1_31.lib bcb5\libboost_regex-bcb5-mt-1_31 bcb5\libboost_regex-bcb5-mt-1_31.lib bcb5\libboost_regex-bcb5-1_31 bcb5\libboost_regex-bcb5-1_31.lib

clean :  libboost_regex-bcb5-s-1_31_clean libboost_regex-bcb5-mt-s-1_31_clean boost_regex-bcb5-mt-1_31_clean boost_regex-bcb5-1_31_clean libboost_regex-bcb5-mt-1_31_clean libboost_regex-bcb5-1_31_clean

install : all
	copy bcb5\libboost_regex-bcb5-s-1_31.lib $(BCROOT)\lib
	copy bcb5\libboost_regex-bcb5-mt-s-1_31.lib $(BCROOT)\lib
	copy bcb5\boost_regex-bcb5-mt-1_31.lib $(BCROOT)\lib
	copy bcb5\boost_regex-bcb5-mt-1_31.dll $(BCROOT)\bin
	copy bcb5\boost_regex-bcb5-mt-1_31.tds $(BCROOT)\bin
	copy bcb5\boost_regex-bcb5-1_31.lib $(BCROOT)\lib
	copy bcb5\boost_regex-bcb5-1_31.dll $(BCROOT)\bin
	copy bcb5\boost_regex-bcb5-1_31.tds $(BCROOT)\bin
	copy bcb5\libboost_regex-bcb5-mt-1_31.lib $(BCROOT)\lib
	copy bcb5\libboost_regex-bcb5-1_31.lib $(BCROOT)\lib

bcb5 :
	-@mkdir bcb5


########################################################
#
# section for libboost_regex-bcb5-s-1_31.lib
#
########################################################
bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex-bcb5-s-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-s-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex-bcb5-s-1_31 : 
	-@mkdir bcb5\libboost_regex-bcb5-s-1_31

libboost_regex-bcb5-s-1_31_clean :
	del bcb5\libboost_regex-bcb5-s-1_31\*.obj
	del bcb5\libboost_regex-bcb5-s-1_31\*.il?
	del bcb5\libboost_regex-bcb5-s-1_31\*.csm
	del bcb5\libboost_regex-bcb5-s-1_31\*.tds

bcb5\libboost_regex-bcb5-s-1_31.lib : bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits.obj bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits_common.obj bcb5\libboost_regex-bcb5-s-1_31\cpp_regex_traits.obj bcb5\libboost_regex-bcb5-s-1_31\cregex.obj bcb5\libboost_regex-bcb5-s-1_31\fileiter.obj bcb5\libboost_regex-bcb5-s-1_31\instances.obj bcb5\libboost_regex-bcb5-s-1_31\posix_api.obj bcb5\libboost_regex-bcb5-s-1_31\regex.obj bcb5\libboost_regex-bcb5-s-1_31\regex_debug.obj bcb5\libboost_regex-bcb5-s-1_31\regex_synch.obj bcb5\libboost_regex-bcb5-s-1_31\w32_regex_traits.obj bcb5\libboost_regex-bcb5-s-1_31\wide_posix_api.obj bcb5\libboost_regex-bcb5-s-1_31\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "bcb5\libboost_regex-bcb5-s-1_31.lib"  -+"bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\c_regex_traits_common.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\cpp_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\cregex.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\fileiter.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\instances.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\posix_api.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\regex.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\regex_debug.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\regex_synch.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\w32_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\wide_posix_api.obj" -+"bcb5\libboost_regex-bcb5-s-1_31\winstances.obj"
|

########################################################
#
# section for libboost_regex-bcb5-mt-s-1_31.lib
#
########################################################
bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-s-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex-bcb5-mt-s-1_31 : 
	-@mkdir bcb5\libboost_regex-bcb5-mt-s-1_31

libboost_regex-bcb5-mt-s-1_31_clean :
	del bcb5\libboost_regex-bcb5-mt-s-1_31\*.obj
	del bcb5\libboost_regex-bcb5-mt-s-1_31\*.il?
	del bcb5\libboost_regex-bcb5-mt-s-1_31\*.csm
	del bcb5\libboost_regex-bcb5-mt-s-1_31\*.tds

bcb5\libboost_regex-bcb5-mt-s-1_31.lib : bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits.obj bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits_common.obj bcb5\libboost_regex-bcb5-mt-s-1_31\cpp_regex_traits.obj bcb5\libboost_regex-bcb5-mt-s-1_31\cregex.obj bcb5\libboost_regex-bcb5-mt-s-1_31\fileiter.obj bcb5\libboost_regex-bcb5-mt-s-1_31\instances.obj bcb5\libboost_regex-bcb5-mt-s-1_31\posix_api.obj bcb5\libboost_regex-bcb5-mt-s-1_31\regex.obj bcb5\libboost_regex-bcb5-mt-s-1_31\regex_debug.obj bcb5\libboost_regex-bcb5-mt-s-1_31\regex_synch.obj bcb5\libboost_regex-bcb5-mt-s-1_31\w32_regex_traits.obj bcb5\libboost_regex-bcb5-mt-s-1_31\wide_posix_api.obj bcb5\libboost_regex-bcb5-mt-s-1_31\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "bcb5\libboost_regex-bcb5-mt-s-1_31.lib"  -+"bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\c_regex_traits_common.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\cpp_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\cregex.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\fileiter.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\instances.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\posix_api.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\regex.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\regex_debug.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\regex_synch.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\w32_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\wide_posix_api.obj" -+"bcb5\libboost_regex-bcb5-mt-s-1_31\winstances.obj"
|

########################################################
#
# section for boost_regex-bcb5-mt-1_31.lib
#
########################################################
bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\instances.obj ../src/instances.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\regex.obj ../src/regex.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\boost_regex-bcb5-mt-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-mt-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\boost_regex-bcb5-mt-1_31 :
	-@mkdir bcb5\boost_regex-bcb5-mt-1_31

boost_regex-bcb5-mt-1_31_clean :
	del bcb5\boost_regex-bcb5-mt-1_31\*.obj
	del bcb5\boost_regex-bcb5-mt-1_31\*.il?
	del bcb5\boost_regex-bcb5-mt-1_31\*.csm
	del bcb5\boost_regex-bcb5-mt-1_31\*.tds
	del bcb5\*.tds

bcb5\boost_regex-bcb5-mt-1_31.lib : bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits_common.obj bcb5\boost_regex-bcb5-mt-1_31\cpp_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\cregex.obj bcb5\boost_regex-bcb5-mt-1_31\fileiter.obj bcb5\boost_regex-bcb5-mt-1_31\instances.obj bcb5\boost_regex-bcb5-mt-1_31\posix_api.obj bcb5\boost_regex-bcb5-mt-1_31\regex.obj bcb5\boost_regex-bcb5-mt-1_31\regex_debug.obj bcb5\boost_regex-bcb5-mt-1_31\regex_synch.obj bcb5\boost_regex-bcb5-mt-1_31\w32_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\wide_posix_api.obj bcb5\boost_regex-bcb5-mt-1_31\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\boost_regex-bcb5-mt-1_31.dll $(XLFLAGS)  bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\c_regex_traits_common.obj bcb5\boost_regex-bcb5-mt-1_31\cpp_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\cregex.obj bcb5\boost_regex-bcb5-mt-1_31\fileiter.obj bcb5\boost_regex-bcb5-mt-1_31\instances.obj bcb5\boost_regex-bcb5-mt-1_31\posix_api.obj bcb5\boost_regex-bcb5-mt-1_31\regex.obj bcb5\boost_regex-bcb5-mt-1_31\regex_debug.obj bcb5\boost_regex-bcb5-mt-1_31\regex_synch.obj bcb5\boost_regex-bcb5-mt-1_31\w32_regex_traits.obj bcb5\boost_regex-bcb5-mt-1_31\wide_posix_api.obj bcb5\boost_regex-bcb5-mt-1_31\winstances.obj $(LIBS)
|
	implib -w bcb5\boost_regex-bcb5-mt-1_31.lib bcb5\boost_regex-bcb5-mt-1_31.dll

########################################################
#
# section for boost_regex-bcb5-1_31.lib
#
########################################################
bcb5\boost_regex-bcb5-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\boost_regex-bcb5-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\boost_regex-bcb5-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\boost_regex-bcb5-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\boost_regex-bcb5-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\boost_regex-bcb5-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\instances.obj ../src/instances.cpp
|

bcb5\boost_regex-bcb5-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\boost_regex-bcb5-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\regex.obj ../src/regex.cpp
|

bcb5\boost_regex-bcb5-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\boost_regex-bcb5-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\boost_regex-bcb5-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\boost_regex-bcb5-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\boost_regex-bcb5-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex-bcb5-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\boost_regex-bcb5-1_31 :
	-@mkdir bcb5\boost_regex-bcb5-1_31

boost_regex-bcb5-1_31_clean :
	del bcb5\boost_regex-bcb5-1_31\*.obj
	del bcb5\boost_regex-bcb5-1_31\*.il?
	del bcb5\boost_regex-bcb5-1_31\*.csm
	del bcb5\boost_regex-bcb5-1_31\*.tds
	del bcb5\*.tds

bcb5\boost_regex-bcb5-1_31.lib : bcb5\boost_regex-bcb5-1_31\c_regex_traits.obj bcb5\boost_regex-bcb5-1_31\c_regex_traits_common.obj bcb5\boost_regex-bcb5-1_31\cpp_regex_traits.obj bcb5\boost_regex-bcb5-1_31\cregex.obj bcb5\boost_regex-bcb5-1_31\fileiter.obj bcb5\boost_regex-bcb5-1_31\instances.obj bcb5\boost_regex-bcb5-1_31\posix_api.obj bcb5\boost_regex-bcb5-1_31\regex.obj bcb5\boost_regex-bcb5-1_31\regex_debug.obj bcb5\boost_regex-bcb5-1_31\regex_synch.obj bcb5\boost_regex-bcb5-1_31\w32_regex_traits.obj bcb5\boost_regex-bcb5-1_31\wide_posix_api.obj bcb5\boost_regex-bcb5-1_31\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\boost_regex-bcb5-1_31.dll $(XLFLAGS)  bcb5\boost_regex-bcb5-1_31\c_regex_traits.obj bcb5\boost_regex-bcb5-1_31\c_regex_traits_common.obj bcb5\boost_regex-bcb5-1_31\cpp_regex_traits.obj bcb5\boost_regex-bcb5-1_31\cregex.obj bcb5\boost_regex-bcb5-1_31\fileiter.obj bcb5\boost_regex-bcb5-1_31\instances.obj bcb5\boost_regex-bcb5-1_31\posix_api.obj bcb5\boost_regex-bcb5-1_31\regex.obj bcb5\boost_regex-bcb5-1_31\regex_debug.obj bcb5\boost_regex-bcb5-1_31\regex_synch.obj bcb5\boost_regex-bcb5-1_31\w32_regex_traits.obj bcb5\boost_regex-bcb5-1_31\wide_posix_api.obj bcb5\boost_regex-bcb5-1_31\winstances.obj $(LIBS)
|
	implib -w bcb5\boost_regex-bcb5-1_31.lib bcb5\boost_regex-bcb5-1_31.dll

########################################################
#
# section for libboost_regex-bcb5-mt-1_31.lib
#
########################################################
bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-mt-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex-bcb5-mt-1_31 : 
	-@mkdir bcb5\libboost_regex-bcb5-mt-1_31

libboost_regex-bcb5-mt-1_31_clean :
	del bcb5\libboost_regex-bcb5-mt-1_31\*.obj
	del bcb5\libboost_regex-bcb5-mt-1_31\*.il?
	del bcb5\libboost_regex-bcb5-mt-1_31\*.csm
	del bcb5\libboost_regex-bcb5-mt-1_31\*.tds

bcb5\libboost_regex-bcb5-mt-1_31.lib : bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits.obj bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits_common.obj bcb5\libboost_regex-bcb5-mt-1_31\cpp_regex_traits.obj bcb5\libboost_regex-bcb5-mt-1_31\cregex.obj bcb5\libboost_regex-bcb5-mt-1_31\fileiter.obj bcb5\libboost_regex-bcb5-mt-1_31\instances.obj bcb5\libboost_regex-bcb5-mt-1_31\posix_api.obj bcb5\libboost_regex-bcb5-mt-1_31\regex.obj bcb5\libboost_regex-bcb5-mt-1_31\regex_debug.obj bcb5\libboost_regex-bcb5-mt-1_31\regex_synch.obj bcb5\libboost_regex-bcb5-mt-1_31\w32_regex_traits.obj bcb5\libboost_regex-bcb5-mt-1_31\wide_posix_api.obj bcb5\libboost_regex-bcb5-mt-1_31\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "bcb5\libboost_regex-bcb5-mt-1_31.lib"  -+"bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\c_regex_traits_common.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\cpp_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\cregex.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\fileiter.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\instances.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\posix_api.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\regex.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\regex_debug.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\regex_synch.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\w32_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\wide_posix_api.obj" -+"bcb5\libboost_regex-bcb5-mt-1_31\winstances.obj"
|

########################################################
#
# section for libboost_regex-bcb5-1_31.lib
#
########################################################
bcb5\libboost_regex-bcb5-1_31\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-1_31\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex-bcb5-1_31\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-1_31\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex-bcb5-1_31\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex-bcb5-1_31\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex-bcb5-1_31\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex-bcb5-1_31\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex-bcb5-1_31\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex-bcb5-1_31\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex-bcb5-1_31\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex-bcb5-1_31\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex-bcb5-1_31\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex-bcb5-1_31\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex-bcb5-1_31 : 
	-@mkdir bcb5\libboost_regex-bcb5-1_31

libboost_regex-bcb5-1_31_clean :
	del bcb5\libboost_regex-bcb5-1_31\*.obj
	del bcb5\libboost_regex-bcb5-1_31\*.il?
	del bcb5\libboost_regex-bcb5-1_31\*.csm
	del bcb5\libboost_regex-bcb5-1_31\*.tds

bcb5\libboost_regex-bcb5-1_31.lib : bcb5\libboost_regex-bcb5-1_31\c_regex_traits.obj bcb5\libboost_regex-bcb5-1_31\c_regex_traits_common.obj bcb5\libboost_regex-bcb5-1_31\cpp_regex_traits.obj bcb5\libboost_regex-bcb5-1_31\cregex.obj bcb5\libboost_regex-bcb5-1_31\fileiter.obj bcb5\libboost_regex-bcb5-1_31\instances.obj bcb5\libboost_regex-bcb5-1_31\posix_api.obj bcb5\libboost_regex-bcb5-1_31\regex.obj bcb5\libboost_regex-bcb5-1_31\regex_debug.obj bcb5\libboost_regex-bcb5-1_31\regex_synch.obj bcb5\libboost_regex-bcb5-1_31\w32_regex_traits.obj bcb5\libboost_regex-bcb5-1_31\wide_posix_api.obj bcb5\libboost_regex-bcb5-1_31\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) "bcb5\libboost_regex-bcb5-1_31.lib"  -+"bcb5\libboost_regex-bcb5-1_31\c_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-1_31\c_regex_traits_common.obj" -+"bcb5\libboost_regex-bcb5-1_31\cpp_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-1_31\cregex.obj" -+"bcb5\libboost_regex-bcb5-1_31\fileiter.obj" -+"bcb5\libboost_regex-bcb5-1_31\instances.obj" -+"bcb5\libboost_regex-bcb5-1_31\posix_api.obj" -+"bcb5\libboost_regex-bcb5-1_31\regex.obj" -+"bcb5\libboost_regex-bcb5-1_31\regex_debug.obj" -+"bcb5\libboost_regex-bcb5-1_31\regex_synch.obj" -+"bcb5\libboost_regex-bcb5-1_31\w32_regex_traits.obj" -+"bcb5\libboost_regex-bcb5-1_31\wide_posix_api.obj" -+"bcb5\libboost_regex-bcb5-1_31\winstances.obj"
|

