
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/integral_c.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#define AUX778076_OP_ARITY 2

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/workaround.hpp>
#   include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct BOOST_PP_CAT(BOOST_PP_CAT(msvc_,AUX778076_OP_PREFIX),_impl)
{
    enum msvc_wknd { value = (n AUX778076_OP_TOKEN s) };
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N, typename S > struct apply
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_NESTED_VALUE_WKND(typename N::value_type, N)
                  AUX778076_OP_TOKEN BOOST_MPL_AUX_NESTED_VALUE_WKND(typename S::value_type, S)
                )
            >
#else
        : aux::BOOST_PP_CAT(BOOST_PP_CAT(msvc_,AUX778076_OP_NAME),_impl)<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type
#endif
    {
    };
};

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN
