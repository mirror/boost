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

all : bcb5 bcb5\libboost_regex_bcb5_ss bcb5\libboost_regex_bcb5_ss.lib bcb5\libboost_regex_bcb5_ms bcb5\libboost_regex_bcb5_ms.lib bcb5\boost_regex_bcb5_md bcb5\boost_regex_bcb5_md.lib bcb5\boost_regex_bcb5_sd bcb5\boost_regex_bcb5_sd.lib bcb5\libboost_regex_bcb5_md bcb5\libboost_regex_bcb5_md.lib bcb5\libboost_regex_bcb5_sd bcb5\libboost_regex_bcb5_sd.lib

clean :  libboost_regex_bcb5_ss_clean libboost_regex_bcb5_ms_clean boost_regex_bcb5_md_clean boost_regex_bcb5_sd_clean libboost_regex_bcb5_md_clean libboost_regex_bcb5_sd_clean

install : all
	copy bcb5\libboost_regex_bcb5_ss.lib $(BCROOT)\lib
	copy bcb5\libboost_regex_bcb5_ms.lib $(BCROOT)\lib
	copy bcb5\boost_regex_bcb5_md.lib $(BCROOT)\lib
	copy bcb5\boost_regex_bcb5_md.dll $(BCROOT)\bin
	copy bcb5\boost_regex_bcb5_md.tds $(BCROOT)\bin
	copy bcb5\boost_regex_bcb5_sd.lib $(BCROOT)\lib
	copy bcb5\boost_regex_bcb5_sd.dll $(BCROOT)\bin
	copy bcb5\boost_regex_bcb5_sd.tds $(BCROOT)\bin
	copy bcb5\libboost_regex_bcb5_md.lib $(BCROOT)\lib
	copy bcb5\libboost_regex_bcb5_sd.lib $(BCROOT)\lib

bcb5 :
	-@mkdir bcb5


########################################################
#
# section for libboost_regex_bcb5_ss.lib
#
########################################################
bcb5\libboost_regex_bcb5_ss\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ss\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex_bcb5_ss\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ss\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex_bcb5_ss\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex_bcb5_ss\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex_bcb5_ss\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex_bcb5_ss\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex_bcb5_ss\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex_bcb5_ss\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex_bcb5_ss\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ss\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex_bcb5_ss\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ss\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex_bcb5_ss : 
	-@mkdir bcb5\libboost_regex_bcb5_ss

libboost_regex_bcb5_ss_clean :
	del bcb5\libboost_regex_bcb5_ss\*.obj
	del bcb5\libboost_regex_bcb5_ss\*.il?
	del bcb5\libboost_regex_bcb5_ss\*.csm
	del bcb5\libboost_regex_bcb5_ss\*.tds

bcb5\libboost_regex_bcb5_ss.lib : bcb5\libboost_regex_bcb5_ss\c_regex_traits.obj bcb5\libboost_regex_bcb5_ss\c_regex_traits_common.obj bcb5\libboost_regex_bcb5_ss\cpp_regex_traits.obj bcb5\libboost_regex_bcb5_ss\cregex.obj bcb5\libboost_regex_bcb5_ss\fileiter.obj bcb5\libboost_regex_bcb5_ss\instances.obj bcb5\libboost_regex_bcb5_ss\posix_api.obj bcb5\libboost_regex_bcb5_ss\regex.obj bcb5\libboost_regex_bcb5_ss\regex_debug.obj bcb5\libboost_regex_bcb5_ss\regex_synch.obj bcb5\libboost_regex_bcb5_ss\w32_regex_traits.obj bcb5\libboost_regex_bcb5_ss\wide_posix_api.obj bcb5\libboost_regex_bcb5_ss\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\libboost_regex_bcb5_ss.lib  -+bcb5\libboost_regex_bcb5_ss\c_regex_traits.obj -+bcb5\libboost_regex_bcb5_ss\c_regex_traits_common.obj -+bcb5\libboost_regex_bcb5_ss\cpp_regex_traits.obj -+bcb5\libboost_regex_bcb5_ss\cregex.obj -+bcb5\libboost_regex_bcb5_ss\fileiter.obj -+bcb5\libboost_regex_bcb5_ss\instances.obj -+bcb5\libboost_regex_bcb5_ss\posix_api.obj -+bcb5\libboost_regex_bcb5_ss\regex.obj -+bcb5\libboost_regex_bcb5_ss\regex_debug.obj -+bcb5\libboost_regex_bcb5_ss\regex_synch.obj -+bcb5\libboost_regex_bcb5_ss\w32_regex_traits.obj -+bcb5\libboost_regex_bcb5_ss\wide_posix_api.obj -+bcb5\libboost_regex_bcb5_ss\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb5_ms.lib
#
########################################################
bcb5\libboost_regex_bcb5_ms\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ms\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex_bcb5_ms\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ms\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex_bcb5_ms\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex_bcb5_ms\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex_bcb5_ms\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex_bcb5_ms\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex_bcb5_ms\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex_bcb5_ms\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex_bcb5_ms\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_ms\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex_bcb5_ms\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\libboost_regex_bcb5_ms\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex_bcb5_ms : 
	-@mkdir bcb5\libboost_regex_bcb5_ms

libboost_regex_bcb5_ms_clean :
	del bcb5\libboost_regex_bcb5_ms\*.obj
	del bcb5\libboost_regex_bcb5_ms\*.il?
	del bcb5\libboost_regex_bcb5_ms\*.csm
	del bcb5\libboost_regex_bcb5_ms\*.tds

bcb5\libboost_regex_bcb5_ms.lib : bcb5\libboost_regex_bcb5_ms\c_regex_traits.obj bcb5\libboost_regex_bcb5_ms\c_regex_traits_common.obj bcb5\libboost_regex_bcb5_ms\cpp_regex_traits.obj bcb5\libboost_regex_bcb5_ms\cregex.obj bcb5\libboost_regex_bcb5_ms\fileiter.obj bcb5\libboost_regex_bcb5_ms\instances.obj bcb5\libboost_regex_bcb5_ms\posix_api.obj bcb5\libboost_regex_bcb5_ms\regex.obj bcb5\libboost_regex_bcb5_ms\regex_debug.obj bcb5\libboost_regex_bcb5_ms\regex_synch.obj bcb5\libboost_regex_bcb5_ms\w32_regex_traits.obj bcb5\libboost_regex_bcb5_ms\wide_posix_api.obj bcb5\libboost_regex_bcb5_ms\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\libboost_regex_bcb5_ms.lib  -+bcb5\libboost_regex_bcb5_ms\c_regex_traits.obj -+bcb5\libboost_regex_bcb5_ms\c_regex_traits_common.obj -+bcb5\libboost_regex_bcb5_ms\cpp_regex_traits.obj -+bcb5\libboost_regex_bcb5_ms\cregex.obj -+bcb5\libboost_regex_bcb5_ms\fileiter.obj -+bcb5\libboost_regex_bcb5_ms\instances.obj -+bcb5\libboost_regex_bcb5_ms\posix_api.obj -+bcb5\libboost_regex_bcb5_ms\regex.obj -+bcb5\libboost_regex_bcb5_ms\regex_debug.obj -+bcb5\libboost_regex_bcb5_ms\regex_synch.obj -+bcb5\libboost_regex_bcb5_ms\w32_regex_traits.obj -+bcb5\libboost_regex_bcb5_ms\wide_posix_api.obj -+bcb5\libboost_regex_bcb5_ms\winstances.obj
|

########################################################
#
# section for boost_regex_bcb5_md.lib
#
########################################################
bcb5\boost_regex_bcb5_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\boost_regex_bcb5_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\boost_regex_bcb5_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\boost_regex_bcb5_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\cregex.obj ../src/cregex.cpp
|

bcb5\boost_regex_bcb5_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\fileiter.obj ../src/fileiter.cpp
|

bcb5\boost_regex_bcb5_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\instances.obj ../src/instances.cpp
|

bcb5\boost_regex_bcb5_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\posix_api.obj ../src/posix_api.cpp
|

bcb5\boost_regex_bcb5_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\regex.obj ../src/regex.cpp
|

bcb5\boost_regex_bcb5_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\boost_regex_bcb5_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\boost_regex_bcb5_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\boost_regex_bcb5_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\boost_regex_bcb5_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_md\winstances.obj ../src/winstances.cpp
|

bcb5\boost_regex_bcb5_md :
	-@mkdir bcb5\boost_regex_bcb5_md

boost_regex_bcb5_md_clean :
	del bcb5\boost_regex_bcb5_md\*.obj
	del bcb5\boost_regex_bcb5_md\*.il?
	del bcb5\boost_regex_bcb5_md\*.csm
	del bcb5\boost_regex_bcb5_md\*.tds
	del bcb5\*.tds

bcb5\boost_regex_bcb5_md.lib : bcb5\boost_regex_bcb5_md\c_regex_traits.obj bcb5\boost_regex_bcb5_md\c_regex_traits_common.obj bcb5\boost_regex_bcb5_md\cpp_regex_traits.obj bcb5\boost_regex_bcb5_md\cregex.obj bcb5\boost_regex_bcb5_md\fileiter.obj bcb5\boost_regex_bcb5_md\instances.obj bcb5\boost_regex_bcb5_md\posix_api.obj bcb5\boost_regex_bcb5_md\regex.obj bcb5\boost_regex_bcb5_md\regex_debug.obj bcb5\boost_regex_bcb5_md\regex_synch.obj bcb5\boost_regex_bcb5_md\w32_regex_traits.obj bcb5\boost_regex_bcb5_md\wide_posix_api.obj bcb5\boost_regex_bcb5_md\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\boost_regex_bcb5_md.dll $(XLFLAGS)  bcb5\boost_regex_bcb5_md\c_regex_traits.obj bcb5\boost_regex_bcb5_md\c_regex_traits_common.obj bcb5\boost_regex_bcb5_md\cpp_regex_traits.obj bcb5\boost_regex_bcb5_md\cregex.obj bcb5\boost_regex_bcb5_md\fileiter.obj bcb5\boost_regex_bcb5_md\instances.obj bcb5\boost_regex_bcb5_md\posix_api.obj bcb5\boost_regex_bcb5_md\regex.obj bcb5\boost_regex_bcb5_md\regex_debug.obj bcb5\boost_regex_bcb5_md\regex_synch.obj bcb5\boost_regex_bcb5_md\w32_regex_traits.obj bcb5\boost_regex_bcb5_md\wide_posix_api.obj bcb5\boost_regex_bcb5_md\winstances.obj $(LIBS)
|
	implib -w bcb5\boost_regex_bcb5_md.lib bcb5\boost_regex_bcb5_md.dll

########################################################
#
# section for boost_regex_bcb5_sd.lib
#
########################################################
bcb5\boost_regex_bcb5_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\boost_regex_bcb5_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\boost_regex_bcb5_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\boost_regex_bcb5_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\cregex.obj ../src/cregex.cpp
|

bcb5\boost_regex_bcb5_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\fileiter.obj ../src/fileiter.cpp
|

bcb5\boost_regex_bcb5_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\instances.obj ../src/instances.cpp
|

bcb5\boost_regex_bcb5_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\posix_api.obj ../src/posix_api.cpp
|

bcb5\boost_regex_bcb5_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\regex.obj ../src/regex.cpp
|

bcb5\boost_regex_bcb5_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\boost_regex_bcb5_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\boost_regex_bcb5_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\boost_regex_bcb5_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\boost_regex_bcb5_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb5\boost_regex_bcb5_sd\winstances.obj ../src/winstances.cpp
|

bcb5\boost_regex_bcb5_sd :
	-@mkdir bcb5\boost_regex_bcb5_sd

boost_regex_bcb5_sd_clean :
	del bcb5\boost_regex_bcb5_sd\*.obj
	del bcb5\boost_regex_bcb5_sd\*.il?
	del bcb5\boost_regex_bcb5_sd\*.csm
	del bcb5\boost_regex_bcb5_sd\*.tds
	del bcb5\*.tds

bcb5\boost_regex_bcb5_sd.lib : bcb5\boost_regex_bcb5_sd\c_regex_traits.obj bcb5\boost_regex_bcb5_sd\c_regex_traits_common.obj bcb5\boost_regex_bcb5_sd\cpp_regex_traits.obj bcb5\boost_regex_bcb5_sd\cregex.obj bcb5\boost_regex_bcb5_sd\fileiter.obj bcb5\boost_regex_bcb5_sd\instances.obj bcb5\boost_regex_bcb5_sd\posix_api.obj bcb5\boost_regex_bcb5_sd\regex.obj bcb5\boost_regex_bcb5_sd\regex_debug.obj bcb5\boost_regex_bcb5_sd\regex_synch.obj bcb5\boost_regex_bcb5_sd\w32_regex_traits.obj bcb5\boost_regex_bcb5_sd\wide_posix_api.obj bcb5\boost_regex_bcb5_sd\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\boost_regex_bcb5_sd.dll $(XLFLAGS)  bcb5\boost_regex_bcb5_sd\c_regex_traits.obj bcb5\boost_regex_bcb5_sd\c_regex_traits_common.obj bcb5\boost_regex_bcb5_sd\cpp_regex_traits.obj bcb5\boost_regex_bcb5_sd\cregex.obj bcb5\boost_regex_bcb5_sd\fileiter.obj bcb5\boost_regex_bcb5_sd\instances.obj bcb5\boost_regex_bcb5_sd\posix_api.obj bcb5\boost_regex_bcb5_sd\regex.obj bcb5\boost_regex_bcb5_sd\regex_debug.obj bcb5\boost_regex_bcb5_sd\regex_synch.obj bcb5\boost_regex_bcb5_sd\w32_regex_traits.obj bcb5\boost_regex_bcb5_sd\wide_posix_api.obj bcb5\boost_regex_bcb5_sd\winstances.obj $(LIBS)
|
	implib -w bcb5\boost_regex_bcb5_sd.lib bcb5\boost_regex_bcb5_sd.dll

########################################################
#
# section for libboost_regex_bcb5_md.lib
#
########################################################
bcb5\libboost_regex_bcb5_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex_bcb5_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex_bcb5_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex_bcb5_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex_bcb5_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex_bcb5_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex_bcb5_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex_bcb5_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex_bcb5_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex_bcb5_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_md\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex_bcb5_md : 
	-@mkdir bcb5\libboost_regex_bcb5_md

libboost_regex_bcb5_md_clean :
	del bcb5\libboost_regex_bcb5_md\*.obj
	del bcb5\libboost_regex_bcb5_md\*.il?
	del bcb5\libboost_regex_bcb5_md\*.csm
	del bcb5\libboost_regex_bcb5_md\*.tds

bcb5\libboost_regex_bcb5_md.lib : bcb5\libboost_regex_bcb5_md\c_regex_traits.obj bcb5\libboost_regex_bcb5_md\c_regex_traits_common.obj bcb5\libboost_regex_bcb5_md\cpp_regex_traits.obj bcb5\libboost_regex_bcb5_md\cregex.obj bcb5\libboost_regex_bcb5_md\fileiter.obj bcb5\libboost_regex_bcb5_md\instances.obj bcb5\libboost_regex_bcb5_md\posix_api.obj bcb5\libboost_regex_bcb5_md\regex.obj bcb5\libboost_regex_bcb5_md\regex_debug.obj bcb5\libboost_regex_bcb5_md\regex_synch.obj bcb5\libboost_regex_bcb5_md\w32_regex_traits.obj bcb5\libboost_regex_bcb5_md\wide_posix_api.obj bcb5\libboost_regex_bcb5_md\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\libboost_regex_bcb5_md.lib  -+bcb5\libboost_regex_bcb5_md\c_regex_traits.obj -+bcb5\libboost_regex_bcb5_md\c_regex_traits_common.obj -+bcb5\libboost_regex_bcb5_md\cpp_regex_traits.obj -+bcb5\libboost_regex_bcb5_md\cregex.obj -+bcb5\libboost_regex_bcb5_md\fileiter.obj -+bcb5\libboost_regex_bcb5_md\instances.obj -+bcb5\libboost_regex_bcb5_md\posix_api.obj -+bcb5\libboost_regex_bcb5_md\regex.obj -+bcb5\libboost_regex_bcb5_md\regex_debug.obj -+bcb5\libboost_regex_bcb5_md\regex_synch.obj -+bcb5\libboost_regex_bcb5_md\w32_regex_traits.obj -+bcb5\libboost_regex_bcb5_md\wide_posix_api.obj -+bcb5\libboost_regex_bcb5_md\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb5_sd.lib
#
########################################################
bcb5\libboost_regex_bcb5_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\libboost_regex_bcb5_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\cregex.obj ../src/cregex.cpp
|

bcb5\libboost_regex_bcb5_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\fileiter.obj ../src/fileiter.cpp
|

bcb5\libboost_regex_bcb5_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\instances.obj ../src/instances.cpp
|

bcb5\libboost_regex_bcb5_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\posix_api.obj ../src/posix_api.cpp
|

bcb5\libboost_regex_bcb5_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\regex.obj ../src/regex.cpp
|

bcb5\libboost_regex_bcb5_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\libboost_regex_bcb5_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\libboost_regex_bcb5_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\libboost_regex_bcb5_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\libboost_regex_bcb5_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\libboost_regex_bcb5_sd\winstances.obj ../src/winstances.cpp
|

bcb5\libboost_regex_bcb5_sd : 
	-@mkdir bcb5\libboost_regex_bcb5_sd

libboost_regex_bcb5_sd_clean :
	del bcb5\libboost_regex_bcb5_sd\*.obj
	del bcb5\libboost_regex_bcb5_sd\*.il?
	del bcb5\libboost_regex_bcb5_sd\*.csm
	del bcb5\libboost_regex_bcb5_sd\*.tds

bcb5\libboost_regex_bcb5_sd.lib : bcb5\libboost_regex_bcb5_sd\c_regex_traits.obj bcb5\libboost_regex_bcb5_sd\c_regex_traits_common.obj bcb5\libboost_regex_bcb5_sd\cpp_regex_traits.obj bcb5\libboost_regex_bcb5_sd\cregex.obj bcb5\libboost_regex_bcb5_sd\fileiter.obj bcb5\libboost_regex_bcb5_sd\instances.obj bcb5\libboost_regex_bcb5_sd\posix_api.obj bcb5\libboost_regex_bcb5_sd\regex.obj bcb5\libboost_regex_bcb5_sd\regex_debug.obj bcb5\libboost_regex_bcb5_sd\regex_synch.obj bcb5\libboost_regex_bcb5_sd\w32_regex_traits.obj bcb5\libboost_regex_bcb5_sd\wide_posix_api.obj bcb5\libboost_regex_bcb5_sd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb5\libboost_regex_bcb5_sd.lib  -+bcb5\libboost_regex_bcb5_sd\c_regex_traits.obj -+bcb5\libboost_regex_bcb5_sd\c_regex_traits_common.obj -+bcb5\libboost_regex_bcb5_sd\cpp_regex_traits.obj -+bcb5\libboost_regex_bcb5_sd\cregex.obj -+bcb5\libboost_regex_bcb5_sd\fileiter.obj -+bcb5\libboost_regex_bcb5_sd\instances.obj -+bcb5\libboost_regex_bcb5_sd\posix_api.obj -+bcb5\libboost_regex_bcb5_sd\regex.obj -+bcb5\libboost_regex_bcb5_sd\regex_debug.obj -+bcb5\libboost_regex_bcb5_sd\regex_synch.obj -+bcb5\libboost_regex_bcb5_sd\w32_regex_traits.obj -+bcb5\libboost_regex_bcb5_sd\wide_posix_api.obj -+bcb5\libboost_regex_bcb5_sd\winstances.obj
|

