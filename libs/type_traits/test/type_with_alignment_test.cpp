
//  (C) Copyright John Maddock 2000. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"
#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/alignment_of.hpp>
#  include <boost/type_traits/type_with_alignment.hpp>
#  include <boost/type_traits/is_pod.hpp>
#endif

#if defined(BOOST_MSVC) || (defined(BOOST_INTEL) && defined(_MSC_VER))
#if _MSC_VER >= 1400
#include <xmmintrin.h>
#endif
struct __declspec(align(8)) a8 { char m[8]; };
struct __declspec(align(16)) a16 { char m[16]; };
struct __declspec(align(32)) a32 { char m[32]; };
struct __declspec(align(64)) a64 { char m[64]; };
struct __declspec(align(128)) a128 { char m[128]; };
#endif

TT_TEST_BEGIN(type_with_alignment)

BOOST_MESSAGE(typeid(::tt::type_with_alignment<
                  ::tt::alignment_of<char>::value
               >::type).name());

BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<char>::value
               >::type
            >::value == ::boost::alignment_of<char>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<short>::value
               >::type
            >::value == ::boost::alignment_of<short>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int>::value
               >::type
            >::value == ::boost::alignment_of<int>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<long>::value
               >::type
            >::value == ::boost::alignment_of<long>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<float>::value
               >::type
            >::value == ::boost::alignment_of<float>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<double>::value
               >::type
            >::value == ::boost::alignment_of<double>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<long double>::value
               >::type
            >::value == ::boost::alignment_of<long double>::value);
#ifdef BOOST_HAS_LONG_LONG
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of< ::boost::long_long_type>::value
               >::type
            >::value == ::boost::alignment_of< ::boost::long_long_type>::value);
#endif
#ifdef BOOST_HAS_MS_INT64
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<__int64>::value
               >::type
            >::value == ::boost::alignment_of<__int64>::value);
#endif
#if defined(BOOST_MSVC) || (defined(BOOST_INTEL) && defined(_MSC_VER))
#if _MSC_VER >= 1400
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<__m128>::value
               >::type
            >::value == ::boost::alignment_of<__m128>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<__m64>::value
               >::type
            >::value == ::boost::alignment_of<__m64>::value);
#endif
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<a8>::value
               >::type
            >::value == ::boost::alignment_of<a8>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<a16>::value
               >::type
            >::value == ::boost::alignment_of<a16>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<a32>::value
               >::type
            >::value == ::boost::alignment_of<a32>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<a64>::value
               >::type
            >::value == ::boost::alignment_of<a64>::value);
#endif
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int[4]>::value
               >::type
            >::value == ::boost::alignment_of<int[4]>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int(*)(int)>::value
               >::type
            >::value == ::boost::alignment_of<int(*)(int)>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int*>::value
               >::type
            >::value == ::boost::alignment_of<int*>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<VB>::value
               >::type
            >::value == ::boost::alignment_of<VB>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<VD>::value
               >::type
            >::value == ::boost::alignment_of<VD>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<enum_UDT>::value
               >::type
            >::value == ::boost::alignment_of<enum_UDT>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<mf2>::value
               >::type
            >::value == ::boost::alignment_of<mf2>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<POD_UDT>::value
               >::type
            >::value == ::boost::alignment_of<POD_UDT>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<empty_UDT>::value
               >::type
            >::value == ::boost::alignment_of<empty_UDT>::value);
BOOST_CHECK(::tt::alignment_of<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<union_UDT>::value
               >::type
            >::value == ::boost::alignment_of<union_UDT>::value);

// check that the type produced are POD's:
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<char>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<short>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<long>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<float>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<double>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<long double>::value>::type
            >::value);
#ifdef BOOST_HAS_LONG_LONG
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of< ::boost::long_long_type>::value>::type
            >::value);
#endif
#ifdef BOOST_HAS_MS_INT64
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<__int64>::value>::type
            >::value);
#endif
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int[4]>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int(*)(int)>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<int*>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<VB>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<VD>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<enum_UDT>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<mf2>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<POD_UDT>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<empty_UDT>::value>::type
            >::value);
BOOST_CHECK(::tt::is_pod<
               ::tt::type_with_alignment<
                  ::tt::alignment_of<union_UDT>::value>::type
            >::value);

TT_TEST_END









