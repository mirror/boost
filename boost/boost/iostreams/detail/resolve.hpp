// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/iostreams/detail/config/smart_adapter_support.hpp>

#ifdef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
# include <boost/iostreams/adapt.hpp>
#endif
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/io_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/static_assert.hpp>

#include <boost/type_traits/is_const.hpp>

namespace boost { namespace iostreams { namespace detail {

//------------------Definition of resolve_traits------------------------------//

// Deduces the return type of resolve.
template<typename Mode, typename Ch, typename T>
struct resolve_traits {
    BOOST_STATIC_ASSERT(!is_const<T>::value);
    #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
        template<typename U>
        struct get_result_type : U::template result_type<Mode, Ch> { };
    #else
        template<typename U>
        struct get_result_type {
            typedef typename U::policy_type policy_type;
            typedef typename 
                    mpl::eval_if<
                        typename U::is_unary,
                        unary_adapter_traits<Mode, Ch, policy_type>,
                        binary_adapter_traits<Mode, Ch, policy_type>
                    >::type type;
        };
    #endif // #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
    typedef typename
            mpl::eval_if<
                is_smart<BOOST_IOSTREAMS_CATEGORY(T)>,
                get_result_type<T>,
                mpl::if_<
                    is_std_io<T>,
                    typename wrapped_type<T>::type,
                    #if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
                        T
                    #else
                        const T&
                    #endif
                >
            >::type type;
};

//------------------Definition of resolve-------------------------------------//

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
do_resolve(const T& t, mpl::false_, mpl::true_) 
{ return wrap(const_cast<T&>(t)); }

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
do_resolve(const T& t, mpl::false_, mpl::false_) { return t; }

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t, mpl::false_) 
{ return do_resolve<Mode, Ch>(t, mpl::false_(), is_std_io<T>()); }

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t, mpl::true_)
{ 
// Workaround GCC bug, supposed to be fixed in GCC 3.4
#if !defined(__MWERKS__) && \
    ( defined(BOOST_INTEL) || !defined(__GNUC__) || (__GNUC__ > 3) || \
      (__GNUC__ ==  3) && (__GNUC_MINOR__ > 3) )
    return t.resolve<Mode, Ch>();
#else
    return t.template resolve<Mode, Ch>();
#endif
}

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T))
{ return resolve<Mode, Ch>(t, is_smart<BOOST_IOSTREAMS_CATEGORY(T)>()); }

} } } // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED
