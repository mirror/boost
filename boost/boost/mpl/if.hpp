//-----------------------------------------------------------------------------
// boost/mpl/if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02 Boost.org
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_IF_HPP_INCLUDED
#define BOOST_MPL_IF_HPP_INCLUDED

#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(C)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    >
struct if_
{
    typedef typename if_c<
          BOOST_MPL_AUX_VALUE_WKND(C)::value
        , T1
        , T2
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(C,T1,T2))
};

#elif defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)

// MSVC6.5-specific version

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
 private:
    template<bool> struct answer        { typedef T1 type; };
    template<>     struct answer<false>	{ typedef T2 type; };
 
 public:
    typedef typename answer< C >::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename C
    , typename T1
    , typename T2
    >
struct if_
{
 private:
    template<bool> struct answer        { typedef T1 type; };
    template<>     struct answer<false>	{ typedef T2 type; };

    // agurt, 17/sep/02: in some situations MSVC 7.0 doesn't 
    // handle 'answer<C::value>' expression very well
    enum { c_ = C::value };

 public:
    typedef typename answer<c_>::type type;
};

#else

// no partial class template specialization

namespace aux {

template< bool C >
struct if_impl
{
    template< typename T1, typename T2 > struct result_
    {
        typedef T1 type;
    };
};

template<>
struct if_impl<false>
{
    template< typename T1, typename T2 > struct result_
    { 
        typedef T2 type;
    };
};

} // namespace aux

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef typename aux::if_impl< C >
        ::template result_<T1,T2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(C)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    >
struct if_
{
    typedef typename aux::if_impl< C::value >
        ::template result_<T1,T2>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(C,T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_VOID_SPEC(3, if_)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_IF_HPP_INCLUDED
