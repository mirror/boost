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

all : bcb4 bcb4\libboost_regex_bcb4_ss bcb4\libboost_regex_bcb4_ss.lib bcb4\libboost_regex_bcb4_ms bcb4\libboost_regex_bcb4_ms.lib bcb4\boost_regex_bcb4_md bcb4\boost_regex_bcb4_md.lib bcb4\boost_regex_bcb4_sd bcb4\boost_regex_bcb4_sd.lib bcb4\libboost_regex_bcb4_md bcb4\libboost_regex_bcb4_md.lib bcb4\libboost_regex_bcb4_sd bcb4\libboost_regex_bcb4_sd.lib

clean :  libboost_regex_bcb4_ss_clean libboost_regex_bcb4_ms_clean boost_regex_bcb4_md_clean boost_regex_bcb4_sd_clean libboost_regex_bcb4_md_clean libboost_regex_bcb4_sd_clean

install : all
	copy bcb4\libboost_regex_bcb4_ss.lib $(BCROOT)\lib
	copy bcb4\libboost_regex_bcb4_ms.lib $(BCROOT)\lib
	copy bcb4\boost_regex_bcb4_md.lib $(BCROOT)\lib
	copy bcb4\boost_regex_bcb4_md.dll $(BCROOT)\bin
	copy bcb4\boost_regex_bcb4_md.tds $(BCROOT)\bin
	copy bcb4\boost_regex_bcb4_sd.lib $(BCROOT)\lib
	copy bcb4\boost_regex_bcb4_sd.dll $(BCROOT)\bin
	copy bcb4\boost_regex_bcb4_sd.tds $(BCROOT)\bin
	copy bcb4\libboost_regex_bcb4_md.lib $(BCROOT)\lib
	copy bcb4\libboost_regex_bcb4_sd.lib $(BCROOT)\lib

bcb4 :
	-@mkdir bcb4


########################################################
#
# section for libboost_regex_bcb4_ss.lib
#
########################################################
bcb4\libboost_regex_bcb4_ss\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ss\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\libboost_regex_bcb4_ss\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ss\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\cregex.obj ../src/cregex.cpp
|

bcb4\libboost_regex_bcb4_ss\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\fileiter.obj ../src/fileiter.cpp
|

bcb4\libboost_regex_bcb4_ss\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\instances.obj ../src/instances.cpp
|

bcb4\libboost_regex_bcb4_ss\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\posix_api.obj ../src/posix_api.cpp
|

bcb4\libboost_regex_bcb4_ss\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\regex.obj ../src/regex.cpp
|

bcb4\libboost_regex_bcb4_ss\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\libboost_regex_bcb4_ss\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\libboost_regex_bcb4_ss\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ss\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\libboost_regex_bcb4_ss\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ss\winstances.obj ../src/winstances.cpp
|

bcb4\libboost_regex_bcb4_ss : 
	-@mkdir bcb4\libboost_regex_bcb4_ss

libboost_regex_bcb4_ss_clean :
	del bcb4\libboost_regex_bcb4_ss\*.obj
	del bcb4\libboost_regex_bcb4_ss\*.il?
	del bcb4\libboost_regex_bcb4_ss\*.csm
	del bcb4\libboost_regex_bcb4_ss\*.tds

bcb4\libboost_regex_bcb4_ss.lib : bcb4\libboost_regex_bcb4_ss\c_regex_traits.obj bcb4\libboost_regex_bcb4_ss\c_regex_traits_common.obj bcb4\libboost_regex_bcb4_ss\cpp_regex_traits.obj bcb4\libboost_regex_bcb4_ss\cregex.obj bcb4\libboost_regex_bcb4_ss\fileiter.obj bcb4\libboost_regex_bcb4_ss\instances.obj bcb4\libboost_regex_bcb4_ss\posix_api.obj bcb4\libboost_regex_bcb4_ss\regex.obj bcb4\libboost_regex_bcb4_ss\regex_debug.obj bcb4\libboost_regex_bcb4_ss\regex_synch.obj bcb4\libboost_regex_bcb4_ss\w32_regex_traits.obj bcb4\libboost_regex_bcb4_ss\wide_posix_api.obj bcb4\libboost_regex_bcb4_ss\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\libboost_regex_bcb4_ss.lib  -+bcb4\libboost_regex_bcb4_ss\c_regex_traits.obj -+bcb4\libboost_regex_bcb4_ss\c_regex_traits_common.obj -+bcb4\libboost_regex_bcb4_ss\cpp_regex_traits.obj -+bcb4\libboost_regex_bcb4_ss\cregex.obj -+bcb4\libboost_regex_bcb4_ss\fileiter.obj -+bcb4\libboost_regex_bcb4_ss\instances.obj -+bcb4\libboost_regex_bcb4_ss\posix_api.obj -+bcb4\libboost_regex_bcb4_ss\regex.obj -+bcb4\libboost_regex_bcb4_ss\regex_debug.obj -+bcb4\libboost_regex_bcb4_ss\regex_synch.obj -+bcb4\libboost_regex_bcb4_ss\w32_regex_traits.obj -+bcb4\libboost_regex_bcb4_ss\wide_posix_api.obj -+bcb4\libboost_regex_bcb4_ss\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb4_ms.lib
#
########################################################
bcb4\libboost_regex_bcb4_ms\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ms\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\libboost_regex_bcb4_ms\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ms\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\cregex.obj ../src/cregex.cpp
|

bcb4\libboost_regex_bcb4_ms\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\fileiter.obj ../src/fileiter.cpp
|

bcb4\libboost_regex_bcb4_ms\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\instances.obj ../src/instances.cpp
|

bcb4\libboost_regex_bcb4_ms\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\posix_api.obj ../src/posix_api.cpp
|

bcb4\libboost_regex_bcb4_ms\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\regex.obj ../src/regex.cpp
|

bcb4\libboost_regex_bcb4_ms\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\libboost_regex_bcb4_ms\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\libboost_regex_bcb4_ms\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_ms\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\libboost_regex_bcb4_ms\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb4\libboost_regex_bcb4_ms\winstances.obj ../src/winstances.cpp
|

bcb4\libboost_regex_bcb4_ms : 
	-@mkdir bcb4\libboost_regex_bcb4_ms

libboost_regex_bcb4_ms_clean :
	del bcb4\libboost_regex_bcb4_ms\*.obj
	del bcb4\libboost_regex_bcb4_ms\*.il?
	del bcb4\libboost_regex_bcb4_ms\*.csm
	del bcb4\libboost_regex_bcb4_ms\*.tds

bcb4\libboost_regex_bcb4_ms.lib : bcb4\libboost_regex_bcb4_ms\c_regex_traits.obj bcb4\libboost_regex_bcb4_ms\c_regex_traits_common.obj bcb4\libboost_regex_bcb4_ms\cpp_regex_traits.obj bcb4\libboost_regex_bcb4_ms\cregex.obj bcb4\libboost_regex_bcb4_ms\fileiter.obj bcb4\libboost_regex_bcb4_ms\instances.obj bcb4\libboost_regex_bcb4_ms\posix_api.obj bcb4\libboost_regex_bcb4_ms\regex.obj bcb4\libboost_regex_bcb4_ms\regex_debug.obj bcb4\libboost_regex_bcb4_ms\regex_synch.obj bcb4\libboost_regex_bcb4_ms\w32_regex_traits.obj bcb4\libboost_regex_bcb4_ms\wide_posix_api.obj bcb4\libboost_regex_bcb4_ms\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\libboost_regex_bcb4_ms.lib  -+bcb4\libboost_regex_bcb4_ms\c_regex_traits.obj -+bcb4\libboost_regex_bcb4_ms\c_regex_traits_common.obj -+bcb4\libboost_regex_bcb4_ms\cpp_regex_traits.obj -+bcb4\libboost_regex_bcb4_ms\cregex.obj -+bcb4\libboost_regex_bcb4_ms\fileiter.obj -+bcb4\libboost_regex_bcb4_ms\instances.obj -+bcb4\libboost_regex_bcb4_ms\posix_api.obj -+bcb4\libboost_regex_bcb4_ms\regex.obj -+bcb4\libboost_regex_bcb4_ms\regex_debug.obj -+bcb4\libboost_regex_bcb4_ms\regex_synch.obj -+bcb4\libboost_regex_bcb4_ms\w32_regex_traits.obj -+bcb4\libboost_regex_bcb4_ms\wide_posix_api.obj -+bcb4\libboost_regex_bcb4_ms\winstances.obj
|

########################################################
#
# section for boost_regex_bcb4_md.lib
#
########################################################
bcb4\boost_regex_bcb4_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\boost_regex_bcb4_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\boost_regex_bcb4_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\boost_regex_bcb4_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\cregex.obj ../src/cregex.cpp
|

bcb4\boost_regex_bcb4_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\fileiter.obj ../src/fileiter.cpp
|

bcb4\boost_regex_bcb4_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\instances.obj ../src/instances.cpp
|

bcb4\boost_regex_bcb4_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\posix_api.obj ../src/posix_api.cpp
|

bcb4\boost_regex_bcb4_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\regex.obj ../src/regex.cpp
|

bcb4\boost_regex_bcb4_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\boost_regex_bcb4_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\boost_regex_bcb4_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\boost_regex_bcb4_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\boost_regex_bcb4_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_md\winstances.obj ../src/winstances.cpp
|

bcb4\boost_regex_bcb4_md :
	-@mkdir bcb4\boost_regex_bcb4_md

boost_regex_bcb4_md_clean :
	del bcb4\boost_regex_bcb4_md\*.obj
	del bcb4\boost_regex_bcb4_md\*.il?
	del bcb4\boost_regex_bcb4_md\*.csm
	del bcb4\boost_regex_bcb4_md\*.tds
	del bcb4\*.tds

bcb4\boost_regex_bcb4_md.lib : bcb4\boost_regex_bcb4_md\c_regex_traits.obj bcb4\boost_regex_bcb4_md\c_regex_traits_common.obj bcb4\boost_regex_bcb4_md\cpp_regex_traits.obj bcb4\boost_regex_bcb4_md\cregex.obj bcb4\boost_regex_bcb4_md\fileiter.obj bcb4\boost_regex_bcb4_md\instances.obj bcb4\boost_regex_bcb4_md\posix_api.obj bcb4\boost_regex_bcb4_md\regex.obj bcb4\boost_regex_bcb4_md\regex_debug.obj bcb4\boost_regex_bcb4_md\regex_synch.obj bcb4\boost_regex_bcb4_md\w32_regex_traits.obj bcb4\boost_regex_bcb4_md\wide_posix_api.obj bcb4\boost_regex_bcb4_md\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\boost_regex_bcb4_md.dll $(XLFLAGS)  bcb4\boost_regex_bcb4_md\c_regex_traits.obj bcb4\boost_regex_bcb4_md\c_regex_traits_common.obj bcb4\boost_regex_bcb4_md\cpp_regex_traits.obj bcb4\boost_regex_bcb4_md\cregex.obj bcb4\boost_regex_bcb4_md\fileiter.obj bcb4\boost_regex_bcb4_md\instances.obj bcb4\boost_regex_bcb4_md\posix_api.obj bcb4\boost_regex_bcb4_md\regex.obj bcb4\boost_regex_bcb4_md\regex_debug.obj bcb4\boost_regex_bcb4_md\regex_synch.obj bcb4\boost_regex_bcb4_md\w32_regex_traits.obj bcb4\boost_regex_bcb4_md\wide_posix_api.obj bcb4\boost_regex_bcb4_md\winstances.obj $(LIBS)
|
	implib -w bcb4\boost_regex_bcb4_md.lib bcb4\boost_regex_bcb4_md.dll

########################################################
#
# section for boost_regex_bcb4_sd.lib
#
########################################################
bcb4\boost_regex_bcb4_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\boost_regex_bcb4_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\boost_regex_bcb4_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\boost_regex_bcb4_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\cregex.obj ../src/cregex.cpp
|

bcb4\boost_regex_bcb4_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\fileiter.obj ../src/fileiter.cpp
|

bcb4\boost_regex_bcb4_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\instances.obj ../src/instances.cpp
|

bcb4\boost_regex_bcb4_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\posix_api.obj ../src/posix_api.cpp
|

bcb4\boost_regex_bcb4_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\regex.obj ../src/regex.cpp
|

bcb4\boost_regex_bcb4_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\boost_regex_bcb4_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\boost_regex_bcb4_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\boost_regex_bcb4_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\boost_regex_bcb4_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb4\boost_regex_bcb4_sd\winstances.obj ../src/winstances.cpp
|

bcb4\boost_regex_bcb4_sd :
	-@mkdir bcb4\boost_regex_bcb4_sd

boost_regex_bcb4_sd_clean :
	del bcb4\boost_regex_bcb4_sd\*.obj
	del bcb4\boost_regex_bcb4_sd\*.il?
	del bcb4\boost_regex_bcb4_sd\*.csm
	del bcb4\boost_regex_bcb4_sd\*.tds
	del bcb4\*.tds

bcb4\boost_regex_bcb4_sd.lib : bcb4\boost_regex_bcb4_sd\c_regex_traits.obj bcb4\boost_regex_bcb4_sd\c_regex_traits_common.obj bcb4\boost_regex_bcb4_sd\cpp_regex_traits.obj bcb4\boost_regex_bcb4_sd\cregex.obj bcb4\boost_regex_bcb4_sd\fileiter.obj bcb4\boost_regex_bcb4_sd\instances.obj bcb4\boost_regex_bcb4_sd\posix_api.obj bcb4\boost_regex_bcb4_sd\regex.obj bcb4\boost_regex_bcb4_sd\regex_debug.obj bcb4\boost_regex_bcb4_sd\regex_synch.obj bcb4\boost_regex_bcb4_sd\w32_regex_traits.obj bcb4\boost_regex_bcb4_sd\wide_posix_api.obj bcb4\boost_regex_bcb4_sd\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb4\boost_regex_bcb4_sd.dll $(XLFLAGS)  bcb4\boost_regex_bcb4_sd\c_regex_traits.obj bcb4\boost_regex_bcb4_sd\c_regex_traits_common.obj bcb4\boost_regex_bcb4_sd\cpp_regex_traits.obj bcb4\boost_regex_bcb4_sd\cregex.obj bcb4\boost_regex_bcb4_sd\fileiter.obj bcb4\boost_regex_bcb4_sd\instances.obj bcb4\boost_regex_bcb4_sd\posix_api.obj bcb4\boost_regex_bcb4_sd\regex.obj bcb4\boost_regex_bcb4_sd\regex_debug.obj bcb4\boost_regex_bcb4_sd\regex_synch.obj bcb4\boost_regex_bcb4_sd\w32_regex_traits.obj bcb4\boost_regex_bcb4_sd\wide_posix_api.obj bcb4\boost_regex_bcb4_sd\winstances.obj $(LIBS)
|
	implib -w bcb4\boost_regex_bcb4_sd.lib bcb4\boost_regex_bcb4_sd.dll

########################################################
#
# section for libboost_regex_bcb4_md.lib
#
########################################################
bcb4\libboost_regex_bcb4_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\libboost_regex_bcb4_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\cregex.obj ../src/cregex.cpp
|

bcb4\libboost_regex_bcb4_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\fileiter.obj ../src/fileiter.cpp
|

bcb4\libboost_regex_bcb4_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\instances.obj ../src/instances.cpp
|

bcb4\libboost_regex_bcb4_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\posix_api.obj ../src/posix_api.cpp
|

bcb4\libboost_regex_bcb4_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\regex.obj ../src/regex.cpp
|

bcb4\libboost_regex_bcb4_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\libboost_regex_bcb4_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\libboost_regex_bcb4_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\libboost_regex_bcb4_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_md\winstances.obj ../src/winstances.cpp
|

bcb4\libboost_regex_bcb4_md : 
	-@mkdir bcb4\libboost_regex_bcb4_md

libboost_regex_bcb4_md_clean :
	del bcb4\libboost_regex_bcb4_md\*.obj
	del bcb4\libboost_regex_bcb4_md\*.il?
	del bcb4\libboost_regex_bcb4_md\*.csm
	del bcb4\libboost_regex_bcb4_md\*.tds

bcb4\libboost_regex_bcb4_md.lib : bcb4\libboost_regex_bcb4_md\c_regex_traits.obj bcb4\libboost_regex_bcb4_md\c_regex_traits_common.obj bcb4\libboost_regex_bcb4_md\cpp_regex_traits.obj bcb4\libboost_regex_bcb4_md\cregex.obj bcb4\libboost_regex_bcb4_md\fileiter.obj bcb4\libboost_regex_bcb4_md\instances.obj bcb4\libboost_regex_bcb4_md\posix_api.obj bcb4\libboost_regex_bcb4_md\regex.obj bcb4\libboost_regex_bcb4_md\regex_debug.obj bcb4\libboost_regex_bcb4_md\regex_synch.obj bcb4\libboost_regex_bcb4_md\w32_regex_traits.obj bcb4\libboost_regex_bcb4_md\wide_posix_api.obj bcb4\libboost_regex_bcb4_md\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\libboost_regex_bcb4_md.lib  -+bcb4\libboost_regex_bcb4_md\c_regex_traits.obj -+bcb4\libboost_regex_bcb4_md\c_regex_traits_common.obj -+bcb4\libboost_regex_bcb4_md\cpp_regex_traits.obj -+bcb4\libboost_regex_bcb4_md\cregex.obj -+bcb4\libboost_regex_bcb4_md\fileiter.obj -+bcb4\libboost_regex_bcb4_md\instances.obj -+bcb4\libboost_regex_bcb4_md\posix_api.obj -+bcb4\libboost_regex_bcb4_md\regex.obj -+bcb4\libboost_regex_bcb4_md\regex_debug.obj -+bcb4\libboost_regex_bcb4_md\regex_synch.obj -+bcb4\libboost_regex_bcb4_md\w32_regex_traits.obj -+bcb4\libboost_regex_bcb4_md\wide_posix_api.obj -+bcb4\libboost_regex_bcb4_md\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb4_sd.lib
#
########################################################
bcb4\libboost_regex_bcb4_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb4\libboost_regex_bcb4_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\cregex.obj ../src/cregex.cpp
|

bcb4\libboost_regex_bcb4_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\fileiter.obj ../src/fileiter.cpp
|

bcb4\libboost_regex_bcb4_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\instances.obj ../src/instances.cpp
|

bcb4\libboost_regex_bcb4_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\posix_api.obj ../src/posix_api.cpp
|

bcb4\libboost_regex_bcb4_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\regex.obj ../src/regex.cpp
|

bcb4\libboost_regex_bcb4_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb4\libboost_regex_bcb4_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb4\libboost_regex_bcb4_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb4\libboost_regex_bcb4_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb4\libboost_regex_bcb4_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb4\libboost_regex_bcb4_sd\winstances.obj ../src/winstances.cpp
|

bcb4\libboost_regex_bcb4_sd : 
	-@mkdir bcb4\libboost_regex_bcb4_sd

libboost_regex_bcb4_sd_clean :
	del bcb4\libboost_regex_bcb4_sd\*.obj
	del bcb4\libboost_regex_bcb4_sd\*.il?
	del bcb4\libboost_regex_bcb4_sd\*.csm
	del bcb4\libboost_regex_bcb4_sd\*.tds

bcb4\libboost_regex_bcb4_sd.lib : bcb4\libboost_regex_bcb4_sd\c_regex_traits.obj bcb4\libboost_regex_bcb4_sd\c_regex_traits_common.obj bcb4\libboost_regex_bcb4_sd\cpp_regex_traits.obj bcb4\libboost_regex_bcb4_sd\cregex.obj bcb4\libboost_regex_bcb4_sd\fileiter.obj bcb4\libboost_regex_bcb4_sd\instances.obj bcb4\libboost_regex_bcb4_sd\posix_api.obj bcb4\libboost_regex_bcb4_sd\regex.obj bcb4\libboost_regex_bcb4_sd\regex_debug.obj bcb4\libboost_regex_bcb4_sd\regex_synch.obj bcb4\libboost_regex_bcb4_sd\w32_regex_traits.obj bcb4\libboost_regex_bcb4_sd\wide_posix_api.obj bcb4\libboost_regex_bcb4_sd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb4\libboost_regex_bcb4_sd.lib  -+bcb4\libboost_regex_bcb4_sd\c_regex_traits.obj -+bcb4\libboost_regex_bcb4_sd\c_regex_traits_common.obj -+bcb4\libboost_regex_bcb4_sd\cpp_regex_traits.obj -+bcb4\libboost_regex_bcb4_sd\cregex.obj -+bcb4\libboost_regex_bcb4_sd\fileiter.obj -+bcb4\libboost_regex_bcb4_sd\instances.obj -+bcb4\libboost_regex_bcb4_sd\posix_api.obj -+bcb4\libboost_regex_bcb4_sd\regex.obj -+bcb4\libboost_regex_bcb4_sd\regex_debug.obj -+bcb4\libboost_regex_bcb4_sd\regex_synch.obj -+bcb4\libboost_regex_bcb4_sd\w32_regex_traits.obj -+bcb4\libboost_regex_bcb4_sd\wide_posix_api.obj -+bcb4\libboost_regex_bcb4_sd\winstances.obj
|

