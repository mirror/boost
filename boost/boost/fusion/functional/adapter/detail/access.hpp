/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // boost::result_of to Fusion PFO parameter
    template <typename T> struct r2fp               { typedef T const type; };
    template <typename T> struct r2fp<T const>      { typedef T const type; };
    template <typename T> struct r2fp<T &>          { typedef T       type; };

    // remove_const< remove_reference<_> >
    template <typename T> struct uncr               { typedef T       type; };
    template <typename T> struct uncr<T const>      { typedef T       type; };
    template <typename T> struct uncr<T &>          { typedef T       type; };
    template <typename T> struct uncr<T const &>    { typedef T       type; };
}}}

#endif

