//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Sun C++ compiler setup:

#    if __SUNPRO_CC >= 0x520
       //
       // Sunpro 5.1 and later:
       //
       // although sunpro 5.1 supports the syntax for
       // inline initialization it often gets the value
       // wrong, especially where the value is computed
       // from other constants (J Maddock 6th May 2001)
#      define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
       // although sunpro 5.1 supports the syntax for
       // partial specialization, it often seems to
       // bind to the wrong specialization.  Better
       // to disable it until suppport becomes more stable
       // (J Maddock 6th May 2001).
#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

       // integral constant expressions with 64 bit numbers fail
#      define BOOST_NO_INTEGRAL_INT64_T
#    endif
#    if __SUNPRO_CC <= 0x500
#      define BOOST_NO_MEMBER_TEMPLATES
#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#    endif

#define BOOST_COMPILER "Sun compiler version " BOOST_STRINGIZE(__SUNPRO_CC)

//
// versions check:
// we don't support sunpro prior to version 4:
#if __SUNPRO_CC < 0x400
#error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0x520:
#if (__SUNPRO_CC > 0x520)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


