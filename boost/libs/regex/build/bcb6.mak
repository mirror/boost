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

all : bcb6 bcb6\libboost_regex_bcb6_ss bcb6\libboost_regex_bcb6_ss.lib bcb6\libboost_regex_bcb6_ms bcb6\libboost_regex_bcb6_ms.lib bcb6\boost_regex_bcb6_md bcb6\boost_regex_bcb6_md.lib bcb6\boost_regex_bcb6_sd bcb6\boost_regex_bcb6_sd.lib bcb6\libboost_regex_bcb6_md bcb6\libboost_regex_bcb6_md.lib bcb6\libboost_regex_bcb6_sd bcb6\libboost_regex_bcb6_sd.lib bcb6\libboost_regex_bcb6_ssdd bcb6\libboost_regex_bcb6_ssdd.lib bcb6\libboost_regex_bcb6_msdd bcb6\libboost_regex_bcb6_msdd.lib bcb6\boost_regex_bcb6_mddd bcb6\boost_regex_bcb6_mddd.lib bcb6\boost_regex_bcb6_sddd bcb6\boost_regex_bcb6_sddd.lib bcb6\libboost_regex_bcb6_mddd bcb6\libboost_regex_bcb6_mddd.lib bcb6\libboost_regex_bcb6_sddd bcb6\libboost_regex_bcb6_sddd.lib

clean :  libboost_regex_bcb6_ss_clean libboost_regex_bcb6_ms_clean boost_regex_bcb6_md_clean boost_regex_bcb6_sd_clean libboost_regex_bcb6_md_clean libboost_regex_bcb6_sd_clean libboost_regex_bcb6_ssdd_clean libboost_regex_bcb6_msdd_clean boost_regex_bcb6_mddd_clean boost_regex_bcb6_sddd_clean libboost_regex_bcb6_mddd_clean libboost_regex_bcb6_sddd_clean

install : all
	copy bcb6\libboost_regex_bcb6_ss.lib $(BCROOT)\lib
	copy bcb6\libboost_regex_bcb6_ms.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_md.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_md.dll $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_md.tds $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_sd.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_sd.dll $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_sd.tds $(BCROOT)\bin
	copy bcb6\libboost_regex_bcb6_md.lib $(BCROOT)\lib
	copy bcb6\libboost_regex_bcb6_sd.lib $(BCROOT)\lib
	copy bcb6\libboost_regex_bcb6_ssdd.lib $(BCROOT)\lib
	copy bcb6\libboost_regex_bcb6_msdd.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_mddd.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_mddd.dll $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_mddd.tds $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_sddd.lib $(BCROOT)\lib
	copy bcb6\boost_regex_bcb6_sddd.dll $(BCROOT)\bin
	copy bcb6\boost_regex_bcb6_sddd.tds $(BCROOT)\bin
	copy bcb6\libboost_regex_bcb6_mddd.lib $(BCROOT)\lib
	copy bcb6\libboost_regex_bcb6_sddd.lib $(BCROOT)\lib

bcb6 :
	-@mkdir bcb6


########################################################
#
# section for libboost_regex_bcb6_ss.lib
#
########################################################
bcb6\libboost_regex_bcb6_ss\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ss\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_ss\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ss\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_ss\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_ss\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_ss\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_ss\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_ss\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_ss\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_ss\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ss\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_ss\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ss\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_ss : 
	-@mkdir bcb6\libboost_regex_bcb6_ss

libboost_regex_bcb6_ss_clean :
	del bcb6\libboost_regex_bcb6_ss\*.obj
	del bcb6\libboost_regex_bcb6_ss\*.il?
	del bcb6\libboost_regex_bcb6_ss\*.csm
	del bcb6\libboost_regex_bcb6_ss\*.tds

bcb6\libboost_regex_bcb6_ss.lib : bcb6\libboost_regex_bcb6_ss\c_regex_traits.obj bcb6\libboost_regex_bcb6_ss\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_ss\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_ss\cregex.obj bcb6\libboost_regex_bcb6_ss\fileiter.obj bcb6\libboost_regex_bcb6_ss\instances.obj bcb6\libboost_regex_bcb6_ss\posix_api.obj bcb6\libboost_regex_bcb6_ss\regex.obj bcb6\libboost_regex_bcb6_ss\regex_debug.obj bcb6\libboost_regex_bcb6_ss\regex_synch.obj bcb6\libboost_regex_bcb6_ss\w32_regex_traits.obj bcb6\libboost_regex_bcb6_ss\wide_posix_api.obj bcb6\libboost_regex_bcb6_ss\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_ss.lib  -+bcb6\libboost_regex_bcb6_ss\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_ss\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_ss\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_ss\cregex.obj -+bcb6\libboost_regex_bcb6_ss\fileiter.obj -+bcb6\libboost_regex_bcb6_ss\instances.obj -+bcb6\libboost_regex_bcb6_ss\posix_api.obj -+bcb6\libboost_regex_bcb6_ss\regex.obj -+bcb6\libboost_regex_bcb6_ss\regex_debug.obj -+bcb6\libboost_regex_bcb6_ss\regex_synch.obj -+bcb6\libboost_regex_bcb6_ss\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_ss\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_ss\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb6_ms.lib
#
########################################################
bcb6\libboost_regex_bcb6_ms\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ms\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_ms\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ms\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_ms\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_ms\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_ms\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_ms\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_ms\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_ms\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_ms\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ms\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_ms\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ms\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_ms : 
	-@mkdir bcb6\libboost_regex_bcb6_ms

libboost_regex_bcb6_ms_clean :
	del bcb6\libboost_regex_bcb6_ms\*.obj
	del bcb6\libboost_regex_bcb6_ms\*.il?
	del bcb6\libboost_regex_bcb6_ms\*.csm
	del bcb6\libboost_regex_bcb6_ms\*.tds

bcb6\libboost_regex_bcb6_ms.lib : bcb6\libboost_regex_bcb6_ms\c_regex_traits.obj bcb6\libboost_regex_bcb6_ms\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_ms\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_ms\cregex.obj bcb6\libboost_regex_bcb6_ms\fileiter.obj bcb6\libboost_regex_bcb6_ms\instances.obj bcb6\libboost_regex_bcb6_ms\posix_api.obj bcb6\libboost_regex_bcb6_ms\regex.obj bcb6\libboost_regex_bcb6_ms\regex_debug.obj bcb6\libboost_regex_bcb6_ms\regex_synch.obj bcb6\libboost_regex_bcb6_ms\w32_regex_traits.obj bcb6\libboost_regex_bcb6_ms\wide_posix_api.obj bcb6\libboost_regex_bcb6_ms\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_ms.lib  -+bcb6\libboost_regex_bcb6_ms\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_ms\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_ms\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_ms\cregex.obj -+bcb6\libboost_regex_bcb6_ms\fileiter.obj -+bcb6\libboost_regex_bcb6_ms\instances.obj -+bcb6\libboost_regex_bcb6_ms\posix_api.obj -+bcb6\libboost_regex_bcb6_ms\regex.obj -+bcb6\libboost_regex_bcb6_ms\regex_debug.obj -+bcb6\libboost_regex_bcb6_ms\regex_synch.obj -+bcb6\libboost_regex_bcb6_ms\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_ms\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_ms\winstances.obj
|

########################################################
#
# section for boost_regex_bcb6_md.lib
#
########################################################
bcb6\boost_regex_bcb6_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\boost_regex_bcb6_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\boost_regex_bcb6_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\boost_regex_bcb6_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\cregex.obj ../src/cregex.cpp
|

bcb6\boost_regex_bcb6_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\fileiter.obj ../src/fileiter.cpp
|

bcb6\boost_regex_bcb6_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\instances.obj ../src/instances.cpp
|

bcb6\boost_regex_bcb6_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\posix_api.obj ../src/posix_api.cpp
|

bcb6\boost_regex_bcb6_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\regex.obj ../src/regex.cpp
|

bcb6\boost_regex_bcb6_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\boost_regex_bcb6_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\boost_regex_bcb6_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\boost_regex_bcb6_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\boost_regex_bcb6_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_md\winstances.obj ../src/winstances.cpp
|

bcb6\boost_regex_bcb6_md :
	-@mkdir bcb6\boost_regex_bcb6_md

boost_regex_bcb6_md_clean :
	del bcb6\boost_regex_bcb6_md\*.obj
	del bcb6\boost_regex_bcb6_md\*.il?
	del bcb6\boost_regex_bcb6_md\*.csm
	del bcb6\boost_regex_bcb6_md\*.tds
	del bcb6\*.tds

bcb6\boost_regex_bcb6_md.lib : bcb6\boost_regex_bcb6_md\c_regex_traits.obj bcb6\boost_regex_bcb6_md\c_regex_traits_common.obj bcb6\boost_regex_bcb6_md\cpp_regex_traits.obj bcb6\boost_regex_bcb6_md\cregex.obj bcb6\boost_regex_bcb6_md\fileiter.obj bcb6\boost_regex_bcb6_md\instances.obj bcb6\boost_regex_bcb6_md\posix_api.obj bcb6\boost_regex_bcb6_md\regex.obj bcb6\boost_regex_bcb6_md\regex_debug.obj bcb6\boost_regex_bcb6_md\regex_synch.obj bcb6\boost_regex_bcb6_md\w32_regex_traits.obj bcb6\boost_regex_bcb6_md\wide_posix_api.obj bcb6\boost_regex_bcb6_md\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\boost_regex_bcb6_md.dll $(XLFLAGS)  bcb6\boost_regex_bcb6_md\c_regex_traits.obj bcb6\boost_regex_bcb6_md\c_regex_traits_common.obj bcb6\boost_regex_bcb6_md\cpp_regex_traits.obj bcb6\boost_regex_bcb6_md\cregex.obj bcb6\boost_regex_bcb6_md\fileiter.obj bcb6\boost_regex_bcb6_md\instances.obj bcb6\boost_regex_bcb6_md\posix_api.obj bcb6\boost_regex_bcb6_md\regex.obj bcb6\boost_regex_bcb6_md\regex_debug.obj bcb6\boost_regex_bcb6_md\regex_synch.obj bcb6\boost_regex_bcb6_md\w32_regex_traits.obj bcb6\boost_regex_bcb6_md\wide_posix_api.obj bcb6\boost_regex_bcb6_md\winstances.obj $(LIBS)
|
	implib -w bcb6\boost_regex_bcb6_md.lib bcb6\boost_regex_bcb6_md.dll

########################################################
#
# section for boost_regex_bcb6_sd.lib
#
########################################################
bcb6\boost_regex_bcb6_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\boost_regex_bcb6_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\cregex.obj ../src/cregex.cpp
|

bcb6\boost_regex_bcb6_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\fileiter.obj ../src/fileiter.cpp
|

bcb6\boost_regex_bcb6_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\instances.obj ../src/instances.cpp
|

bcb6\boost_regex_bcb6_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\posix_api.obj ../src/posix_api.cpp
|

bcb6\boost_regex_bcb6_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\regex.obj ../src/regex.cpp
|

bcb6\boost_regex_bcb6_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\boost_regex_bcb6_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\boost_regex_bcb6_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\boost_regex_bcb6_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sd\winstances.obj ../src/winstances.cpp
|

bcb6\boost_regex_bcb6_sd :
	-@mkdir bcb6\boost_regex_bcb6_sd

boost_regex_bcb6_sd_clean :
	del bcb6\boost_regex_bcb6_sd\*.obj
	del bcb6\boost_regex_bcb6_sd\*.il?
	del bcb6\boost_regex_bcb6_sd\*.csm
	del bcb6\boost_regex_bcb6_sd\*.tds
	del bcb6\*.tds

bcb6\boost_regex_bcb6_sd.lib : bcb6\boost_regex_bcb6_sd\c_regex_traits.obj bcb6\boost_regex_bcb6_sd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_sd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_sd\cregex.obj bcb6\boost_regex_bcb6_sd\fileiter.obj bcb6\boost_regex_bcb6_sd\instances.obj bcb6\boost_regex_bcb6_sd\posix_api.obj bcb6\boost_regex_bcb6_sd\regex.obj bcb6\boost_regex_bcb6_sd\regex_debug.obj bcb6\boost_regex_bcb6_sd\regex_synch.obj bcb6\boost_regex_bcb6_sd\w32_regex_traits.obj bcb6\boost_regex_bcb6_sd\wide_posix_api.obj bcb6\boost_regex_bcb6_sd\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\boost_regex_bcb6_sd.dll $(XLFLAGS)  bcb6\boost_regex_bcb6_sd\c_regex_traits.obj bcb6\boost_regex_bcb6_sd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_sd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_sd\cregex.obj bcb6\boost_regex_bcb6_sd\fileiter.obj bcb6\boost_regex_bcb6_sd\instances.obj bcb6\boost_regex_bcb6_sd\posix_api.obj bcb6\boost_regex_bcb6_sd\regex.obj bcb6\boost_regex_bcb6_sd\regex_debug.obj bcb6\boost_regex_bcb6_sd\regex_synch.obj bcb6\boost_regex_bcb6_sd\w32_regex_traits.obj bcb6\boost_regex_bcb6_sd\wide_posix_api.obj bcb6\boost_regex_bcb6_sd\winstances.obj $(LIBS)
|
	implib -w bcb6\boost_regex_bcb6_sd.lib bcb6\boost_regex_bcb6_sd.dll

########################################################
#
# section for libboost_regex_bcb6_md.lib
#
########################################################
bcb6\libboost_regex_bcb6_md\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_md\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_md\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_md\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_md\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_md\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_md\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_md\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_md\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_md\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_md\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_md\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_md\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_md\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_md : 
	-@mkdir bcb6\libboost_regex_bcb6_md

libboost_regex_bcb6_md_clean :
	del bcb6\libboost_regex_bcb6_md\*.obj
	del bcb6\libboost_regex_bcb6_md\*.il?
	del bcb6\libboost_regex_bcb6_md\*.csm
	del bcb6\libboost_regex_bcb6_md\*.tds

bcb6\libboost_regex_bcb6_md.lib : bcb6\libboost_regex_bcb6_md\c_regex_traits.obj bcb6\libboost_regex_bcb6_md\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_md\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_md\cregex.obj bcb6\libboost_regex_bcb6_md\fileiter.obj bcb6\libboost_regex_bcb6_md\instances.obj bcb6\libboost_regex_bcb6_md\posix_api.obj bcb6\libboost_regex_bcb6_md\regex.obj bcb6\libboost_regex_bcb6_md\regex_debug.obj bcb6\libboost_regex_bcb6_md\regex_synch.obj bcb6\libboost_regex_bcb6_md\w32_regex_traits.obj bcb6\libboost_regex_bcb6_md\wide_posix_api.obj bcb6\libboost_regex_bcb6_md\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_md.lib  -+bcb6\libboost_regex_bcb6_md\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_md\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_md\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_md\cregex.obj -+bcb6\libboost_regex_bcb6_md\fileiter.obj -+bcb6\libboost_regex_bcb6_md\instances.obj -+bcb6\libboost_regex_bcb6_md\posix_api.obj -+bcb6\libboost_regex_bcb6_md\regex.obj -+bcb6\libboost_regex_bcb6_md\regex_debug.obj -+bcb6\libboost_regex_bcb6_md\regex_synch.obj -+bcb6\libboost_regex_bcb6_md\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_md\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_md\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb6_sd.lib
#
########################################################
bcb6\libboost_regex_bcb6_sd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_sd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_sd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_sd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_sd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_sd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_sd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_sd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_sd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_sd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -O2 -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sd\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_sd : 
	-@mkdir bcb6\libboost_regex_bcb6_sd

libboost_regex_bcb6_sd_clean :
	del bcb6\libboost_regex_bcb6_sd\*.obj
	del bcb6\libboost_regex_bcb6_sd\*.il?
	del bcb6\libboost_regex_bcb6_sd\*.csm
	del bcb6\libboost_regex_bcb6_sd\*.tds

bcb6\libboost_regex_bcb6_sd.lib : bcb6\libboost_regex_bcb6_sd\c_regex_traits.obj bcb6\libboost_regex_bcb6_sd\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_sd\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_sd\cregex.obj bcb6\libboost_regex_bcb6_sd\fileiter.obj bcb6\libboost_regex_bcb6_sd\instances.obj bcb6\libboost_regex_bcb6_sd\posix_api.obj bcb6\libboost_regex_bcb6_sd\regex.obj bcb6\libboost_regex_bcb6_sd\regex_debug.obj bcb6\libboost_regex_bcb6_sd\regex_synch.obj bcb6\libboost_regex_bcb6_sd\w32_regex_traits.obj bcb6\libboost_regex_bcb6_sd\wide_posix_api.obj bcb6\libboost_regex_bcb6_sd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_sd.lib  -+bcb6\libboost_regex_bcb6_sd\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_sd\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_sd\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_sd\cregex.obj -+bcb6\libboost_regex_bcb6_sd\fileiter.obj -+bcb6\libboost_regex_bcb6_sd\instances.obj -+bcb6\libboost_regex_bcb6_sd\posix_api.obj -+bcb6\libboost_regex_bcb6_sd\regex.obj -+bcb6\libboost_regex_bcb6_sd\regex_debug.obj -+bcb6\libboost_regex_bcb6_sd\regex_synch.obj -+bcb6\libboost_regex_bcb6_sd\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_sd\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_sd\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb6_ssdd.lib
#
########################################################
bcb6\libboost_regex_bcb6_ssdd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ssdd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_ssdd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ssdd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_ssdd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_ssdd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_ssdd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_ssdd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_ssdd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_ssdd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_ssdd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_ssdd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_ssdd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_ssdd\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_ssdd : 
	-@mkdir bcb6\libboost_regex_bcb6_ssdd

libboost_regex_bcb6_ssdd_clean :
	del bcb6\libboost_regex_bcb6_ssdd\*.obj
	del bcb6\libboost_regex_bcb6_ssdd\*.il?
	del bcb6\libboost_regex_bcb6_ssdd\*.csm
	del bcb6\libboost_regex_bcb6_ssdd\*.tds

bcb6\libboost_regex_bcb6_ssdd.lib : bcb6\libboost_regex_bcb6_ssdd\c_regex_traits.obj bcb6\libboost_regex_bcb6_ssdd\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_ssdd\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_ssdd\cregex.obj bcb6\libboost_regex_bcb6_ssdd\fileiter.obj bcb6\libboost_regex_bcb6_ssdd\instances.obj bcb6\libboost_regex_bcb6_ssdd\posix_api.obj bcb6\libboost_regex_bcb6_ssdd\regex.obj bcb6\libboost_regex_bcb6_ssdd\regex_debug.obj bcb6\libboost_regex_bcb6_ssdd\regex_synch.obj bcb6\libboost_regex_bcb6_ssdd\w32_regex_traits.obj bcb6\libboost_regex_bcb6_ssdd\wide_posix_api.obj bcb6\libboost_regex_bcb6_ssdd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_ssdd.lib  -+bcb6\libboost_regex_bcb6_ssdd\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_ssdd\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_ssdd\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_ssdd\cregex.obj -+bcb6\libboost_regex_bcb6_ssdd\fileiter.obj -+bcb6\libboost_regex_bcb6_ssdd\instances.obj -+bcb6\libboost_regex_bcb6_ssdd\posix_api.obj -+bcb6\libboost_regex_bcb6_ssdd\regex.obj -+bcb6\libboost_regex_bcb6_ssdd\regex_debug.obj -+bcb6\libboost_regex_bcb6_ssdd\regex_synch.obj -+bcb6\libboost_regex_bcb6_ssdd\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_ssdd\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_ssdd\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb6_msdd.lib
#
########################################################
bcb6\libboost_regex_bcb6_msdd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_msdd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_msdd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_msdd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_msdd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_msdd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_msdd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_msdd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_msdd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_msdd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_msdd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_msdd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_msdd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_STLP_DEBUG -D_NO_VCL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb6\libboost_regex_bcb6_msdd\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_msdd : 
	-@mkdir bcb6\libboost_regex_bcb6_msdd

libboost_regex_bcb6_msdd_clean :
	del bcb6\libboost_regex_bcb6_msdd\*.obj
	del bcb6\libboost_regex_bcb6_msdd\*.il?
	del bcb6\libboost_regex_bcb6_msdd\*.csm
	del bcb6\libboost_regex_bcb6_msdd\*.tds

bcb6\libboost_regex_bcb6_msdd.lib : bcb6\libboost_regex_bcb6_msdd\c_regex_traits.obj bcb6\libboost_regex_bcb6_msdd\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_msdd\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_msdd\cregex.obj bcb6\libboost_regex_bcb6_msdd\fileiter.obj bcb6\libboost_regex_bcb6_msdd\instances.obj bcb6\libboost_regex_bcb6_msdd\posix_api.obj bcb6\libboost_regex_bcb6_msdd\regex.obj bcb6\libboost_regex_bcb6_msdd\regex_debug.obj bcb6\libboost_regex_bcb6_msdd\regex_synch.obj bcb6\libboost_regex_bcb6_msdd\w32_regex_traits.obj bcb6\libboost_regex_bcb6_msdd\wide_posix_api.obj bcb6\libboost_regex_bcb6_msdd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_msdd.lib  -+bcb6\libboost_regex_bcb6_msdd\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_msdd\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_msdd\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_msdd\cregex.obj -+bcb6\libboost_regex_bcb6_msdd\fileiter.obj -+bcb6\libboost_regex_bcb6_msdd\instances.obj -+bcb6\libboost_regex_bcb6_msdd\posix_api.obj -+bcb6\libboost_regex_bcb6_msdd\regex.obj -+bcb6\libboost_regex_bcb6_msdd\regex_debug.obj -+bcb6\libboost_regex_bcb6_msdd\regex_synch.obj -+bcb6\libboost_regex_bcb6_msdd\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_msdd\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_msdd\winstances.obj
|

########################################################
#
# section for boost_regex_bcb6_mddd.lib
#
########################################################
bcb6\boost_regex_bcb6_mddd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\boost_regex_bcb6_mddd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\boost_regex_bcb6_mddd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\boost_regex_bcb6_mddd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\cregex.obj ../src/cregex.cpp
|

bcb6\boost_regex_bcb6_mddd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\fileiter.obj ../src/fileiter.cpp
|

bcb6\boost_regex_bcb6_mddd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\instances.obj ../src/instances.cpp
|

bcb6\boost_regex_bcb6_mddd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\posix_api.obj ../src/posix_api.cpp
|

bcb6\boost_regex_bcb6_mddd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\regex.obj ../src/regex.cpp
|

bcb6\boost_regex_bcb6_mddd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\boost_regex_bcb6_mddd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\boost_regex_bcb6_mddd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\boost_regex_bcb6_mddd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\boost_regex_bcb6_mddd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_mddd\winstances.obj ../src/winstances.cpp
|

bcb6\boost_regex_bcb6_mddd :
	-@mkdir bcb6\boost_regex_bcb6_mddd

boost_regex_bcb6_mddd_clean :
	del bcb6\boost_regex_bcb6_mddd\*.obj
	del bcb6\boost_regex_bcb6_mddd\*.il?
	del bcb6\boost_regex_bcb6_mddd\*.csm
	del bcb6\boost_regex_bcb6_mddd\*.tds
	del bcb6\*.tds

bcb6\boost_regex_bcb6_mddd.lib : bcb6\boost_regex_bcb6_mddd\c_regex_traits.obj bcb6\boost_regex_bcb6_mddd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_mddd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_mddd\cregex.obj bcb6\boost_regex_bcb6_mddd\fileiter.obj bcb6\boost_regex_bcb6_mddd\instances.obj bcb6\boost_regex_bcb6_mddd\posix_api.obj bcb6\boost_regex_bcb6_mddd\regex.obj bcb6\boost_regex_bcb6_mddd\regex_debug.obj bcb6\boost_regex_bcb6_mddd\regex_synch.obj bcb6\boost_regex_bcb6_mddd\w32_regex_traits.obj bcb6\boost_regex_bcb6_mddd\wide_posix_api.obj bcb6\boost_regex_bcb6_mddd\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWM -tWR -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\boost_regex_bcb6_mddd.dll $(XLFLAGS)  bcb6\boost_regex_bcb6_mddd\c_regex_traits.obj bcb6\boost_regex_bcb6_mddd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_mddd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_mddd\cregex.obj bcb6\boost_regex_bcb6_mddd\fileiter.obj bcb6\boost_regex_bcb6_mddd\instances.obj bcb6\boost_regex_bcb6_mddd\posix_api.obj bcb6\boost_regex_bcb6_mddd\regex.obj bcb6\boost_regex_bcb6_mddd\regex_debug.obj bcb6\boost_regex_bcb6_mddd\regex_synch.obj bcb6\boost_regex_bcb6_mddd\w32_regex_traits.obj bcb6\boost_regex_bcb6_mddd\wide_posix_api.obj bcb6\boost_regex_bcb6_mddd\winstances.obj $(LIBS)
|
	implib -w bcb6\boost_regex_bcb6_mddd.lib bcb6\boost_regex_bcb6_mddd.dll

########################################################
#
# section for boost_regex_bcb6_sddd.lib
#
########################################################
bcb6\boost_regex_bcb6_sddd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sddd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\boost_regex_bcb6_sddd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sddd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\cregex.obj ../src/cregex.cpp
|

bcb6\boost_regex_bcb6_sddd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\fileiter.obj ../src/fileiter.cpp
|

bcb6\boost_regex_bcb6_sddd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\instances.obj ../src/instances.cpp
|

bcb6\boost_regex_bcb6_sddd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\posix_api.obj ../src/posix_api.cpp
|

bcb6\boost_regex_bcb6_sddd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\regex.obj ../src/regex.cpp
|

bcb6\boost_regex_bcb6_sddd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\boost_regex_bcb6_sddd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\boost_regex_bcb6_sddd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\boost_regex_bcb6_sddd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\boost_regex_bcb6_sddd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -DBOOST_REGEX_DYN_LINK -obcb6\boost_regex_bcb6_sddd\winstances.obj ../src/winstances.cpp
|

bcb6\boost_regex_bcb6_sddd :
	-@mkdir bcb6\boost_regex_bcb6_sddd

boost_regex_bcb6_sddd_clean :
	del bcb6\boost_regex_bcb6_sddd\*.obj
	del bcb6\boost_regex_bcb6_sddd\*.il?
	del bcb6\boost_regex_bcb6_sddd\*.csm
	del bcb6\boost_regex_bcb6_sddd\*.tds
	del bcb6\*.tds

bcb6\boost_regex_bcb6_sddd.lib : bcb6\boost_regex_bcb6_sddd\c_regex_traits.obj bcb6\boost_regex_bcb6_sddd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_sddd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_sddd\cregex.obj bcb6\boost_regex_bcb6_sddd\fileiter.obj bcb6\boost_regex_bcb6_sddd\instances.obj bcb6\boost_regex_bcb6_sddd\posix_api.obj bcb6\boost_regex_bcb6_sddd\regex.obj bcb6\boost_regex_bcb6_sddd\regex_debug.obj bcb6\boost_regex_bcb6_sddd\regex_synch.obj bcb6\boost_regex_bcb6_sddd\w32_regex_traits.obj bcb6\boost_regex_bcb6_sddd\wide_posix_api.obj bcb6\boost_regex_bcb6_sddd\winstances.obj
	bcc32 @&&|
-lw-dup -lw-dpl -tWD -tWR -tWM- -D_STLP_DEBUG -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb6\boost_regex_bcb6_sddd.dll $(XLFLAGS)  bcb6\boost_regex_bcb6_sddd\c_regex_traits.obj bcb6\boost_regex_bcb6_sddd\c_regex_traits_common.obj bcb6\boost_regex_bcb6_sddd\cpp_regex_traits.obj bcb6\boost_regex_bcb6_sddd\cregex.obj bcb6\boost_regex_bcb6_sddd\fileiter.obj bcb6\boost_regex_bcb6_sddd\instances.obj bcb6\boost_regex_bcb6_sddd\posix_api.obj bcb6\boost_regex_bcb6_sddd\regex.obj bcb6\boost_regex_bcb6_sddd\regex_debug.obj bcb6\boost_regex_bcb6_sddd\regex_synch.obj bcb6\boost_regex_bcb6_sddd\w32_regex_traits.obj bcb6\boost_regex_bcb6_sddd\wide_posix_api.obj bcb6\boost_regex_bcb6_sddd\winstances.obj $(LIBS)
|
	implib -w bcb6\boost_regex_bcb6_sddd.lib bcb6\boost_regex_bcb6_sddd.dll

########################################################
#
# section for libboost_regex_bcb6_mddd.lib
#
########################################################
bcb6\libboost_regex_bcb6_mddd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_mddd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_mddd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_mddd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_mddd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_mddd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_mddd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_mddd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_mddd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_mddd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_mddd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_mddd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_mddd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_mddd\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_mddd : 
	-@mkdir bcb6\libboost_regex_bcb6_mddd

libboost_regex_bcb6_mddd_clean :
	del bcb6\libboost_regex_bcb6_mddd\*.obj
	del bcb6\libboost_regex_bcb6_mddd\*.il?
	del bcb6\libboost_regex_bcb6_mddd\*.csm
	del bcb6\libboost_regex_bcb6_mddd\*.tds

bcb6\libboost_regex_bcb6_mddd.lib : bcb6\libboost_regex_bcb6_mddd\c_regex_traits.obj bcb6\libboost_regex_bcb6_mddd\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_mddd\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_mddd\cregex.obj bcb6\libboost_regex_bcb6_mddd\fileiter.obj bcb6\libboost_regex_bcb6_mddd\instances.obj bcb6\libboost_regex_bcb6_mddd\posix_api.obj bcb6\libboost_regex_bcb6_mddd\regex.obj bcb6\libboost_regex_bcb6_mddd\regex_debug.obj bcb6\libboost_regex_bcb6_mddd\regex_synch.obj bcb6\libboost_regex_bcb6_mddd\w32_regex_traits.obj bcb6\libboost_regex_bcb6_mddd\wide_posix_api.obj bcb6\libboost_regex_bcb6_mddd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_mddd.lib  -+bcb6\libboost_regex_bcb6_mddd\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_mddd\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_mddd\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_mddd\cregex.obj -+bcb6\libboost_regex_bcb6_mddd\fileiter.obj -+bcb6\libboost_regex_bcb6_mddd\instances.obj -+bcb6\libboost_regex_bcb6_mddd\posix_api.obj -+bcb6\libboost_regex_bcb6_mddd\regex.obj -+bcb6\libboost_regex_bcb6_mddd\regex_debug.obj -+bcb6\libboost_regex_bcb6_mddd\regex_synch.obj -+bcb6\libboost_regex_bcb6_mddd\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_mddd\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_mddd\winstances.obj
|

########################################################
#
# section for libboost_regex_bcb6_sddd.lib
#
########################################################
bcb6\libboost_regex_bcb6_sddd\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sddd\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb6\libboost_regex_bcb6_sddd\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sddd\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\cregex.obj ../src/cregex.cpp
|

bcb6\libboost_regex_bcb6_sddd\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\fileiter.obj ../src/fileiter.cpp
|

bcb6\libboost_regex_bcb6_sddd\instances.obj: ../src/instances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\instances.obj ../src/instances.cpp
|

bcb6\libboost_regex_bcb6_sddd\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\posix_api.obj ../src/posix_api.cpp
|

bcb6\libboost_regex_bcb6_sddd\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\regex.obj ../src/regex.cpp
|

bcb6\libboost_regex_bcb6_sddd\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\regex_debug.obj ../src/regex_debug.cpp
|

bcb6\libboost_regex_bcb6_sddd\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\regex_synch.obj ../src/regex_synch.cpp
|

bcb6\libboost_regex_bcb6_sddd\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb6\libboost_regex_bcb6_sddd\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb6\libboost_regex_bcb6_sddd\winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_STLP_DEBUG -DBOOST_REGEX_STATIC_LINK -D_NO_VCL -D_RTLDLL -v -Ve -Vx -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb6\libboost_regex_bcb6_sddd\winstances.obj ../src/winstances.cpp
|

bcb6\libboost_regex_bcb6_sddd : 
	-@mkdir bcb6\libboost_regex_bcb6_sddd

libboost_regex_bcb6_sddd_clean :
	del bcb6\libboost_regex_bcb6_sddd\*.obj
	del bcb6\libboost_regex_bcb6_sddd\*.il?
	del bcb6\libboost_regex_bcb6_sddd\*.csm
	del bcb6\libboost_regex_bcb6_sddd\*.tds

bcb6\libboost_regex_bcb6_sddd.lib : bcb6\libboost_regex_bcb6_sddd\c_regex_traits.obj bcb6\libboost_regex_bcb6_sddd\c_regex_traits_common.obj bcb6\libboost_regex_bcb6_sddd\cpp_regex_traits.obj bcb6\libboost_regex_bcb6_sddd\cregex.obj bcb6\libboost_regex_bcb6_sddd\fileiter.obj bcb6\libboost_regex_bcb6_sddd\instances.obj bcb6\libboost_regex_bcb6_sddd\posix_api.obj bcb6\libboost_regex_bcb6_sddd\regex.obj bcb6\libboost_regex_bcb6_sddd\regex_debug.obj bcb6\libboost_regex_bcb6_sddd\regex_synch.obj bcb6\libboost_regex_bcb6_sddd\w32_regex_traits.obj bcb6\libboost_regex_bcb6_sddd\wide_posix_api.obj bcb6\libboost_regex_bcb6_sddd\winstances.obj
	tlib @&&|
/P128 /C /u /a $(XSFLAGS) bcb6\libboost_regex_bcb6_sddd.lib  -+bcb6\libboost_regex_bcb6_sddd\c_regex_traits.obj -+bcb6\libboost_regex_bcb6_sddd\c_regex_traits_common.obj -+bcb6\libboost_regex_bcb6_sddd\cpp_regex_traits.obj -+bcb6\libboost_regex_bcb6_sddd\cregex.obj -+bcb6\libboost_regex_bcb6_sddd\fileiter.obj -+bcb6\libboost_regex_bcb6_sddd\instances.obj -+bcb6\libboost_regex_bcb6_sddd\posix_api.obj -+bcb6\libboost_regex_bcb6_sddd\regex.obj -+bcb6\libboost_regex_bcb6_sddd\regex_debug.obj -+bcb6\libboost_regex_bcb6_sddd\regex_synch.obj -+bcb6\libboost_regex_bcb6_sddd\w32_regex_traits.obj -+bcb6\libboost_regex_bcb6_sddd\wide_posix_api.obj -+bcb6\libboost_regex_bcb6_sddd\winstances.obj
|

