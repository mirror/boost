// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains 
//      (1) the metafunction select, which mimics the effect of a chain
//          of nested mpl if_'s or eval_if's, and 
//      (2) the template eval, for use with select.
//
// -----------------------------------------------------------------------------
//
// Usage:
//      
// typedef typename select<
//                      case1,  type1,
//                      case2,  type2,
//                      ...
//                      true_,  typen
//                  >::type selection;
//
// Here case1, case2, ... are models of MPL::IntegralConstant with value type
// bool, and n <= 10 (the maxiumum number of cases used by this library is 8).
// 
// To get the effect of mpl::eval_if for a given type, wrap it with the 
// template eval. E.g.:
//
// typedef typename select<
//                      case1,  type1,
//                      case2,  type2,
//                      case3,  eval<type3>,
//                      ...
//                      true_,  typen
//                  >::type selection;
//                      
// Here type3 is a metafunction which will be applied only if it is selected.
//

#ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_SELECT_HPP_INCLUDED   

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif                  
 
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace iostreams { 

namespace detail { 
    struct lazy_base { }; 

    // Returns the given type, unless is is of the form eval<U>, in which case
    // returns the result of applying U.
    template<typename T>
    struct lazy_eval {
        template<typename U> struct apply_base_type {
            typedef typename U::base::type type;
        };
        typedef typename mpl::eval_if<
                             is_base_and_derived<detail::lazy_base, T>,
                             apply_base_type<T>,
                             mpl::identity<T>
                         >::type type;
    };

    template<>
    struct lazy_eval<mpl::void_> { typedef mpl::void_ type; };
} // End namespace detail.

template<typename T>
struct lazy : public detail::lazy_base { typedef T base; };

namespace detail { 
    // Unspecified types default to void (VC6 requires this circumlocution.)
    typedef lazy< mpl::identity<void> > select_default; 
}

template< typename Case1 = mpl::true_,
          typename Type1 = detail::select_default,
          typename Case2 = mpl::true_,
          typename Type2 = detail::select_default,
          typename Case3 = mpl::true_,
          typename Type3 = detail::select_default,
          typename Case4 = mpl::true_,
          typename Type4 = detail::select_default,
          typename Case5 = mpl::true_,
          typename Type5 = detail::select_default,
          typename Case6 = mpl::true_,
          typename Type6 = detail::select_default,
          typename Case7 = mpl::true_,
          typename Type7 = detail::select_default,
          typename Case8 = mpl::true_,
          typename Type8 = detail::select_default,
          typename Case9 = mpl::true_,
          typename Type9 = detail::select_default,
          typename Case10 = mpl::true_,
          typename Type10 = detail::select_default,
          typename Case11 = mpl::true_,
          typename Type11 = detail::select_default,
          typename Case12 = mpl::true_,
          typename Type12 = detail::select_default,
          typename Case13 = mpl::true_,
          typename Type13 = detail::select_default,
          typename Case14 = mpl::true_,
          typename Type14 = detail::select_default,
          typename Case15 = mpl::true_,
          typename Type15 = detail::select_default,
          typename Case16 = mpl::true_,
          typename Type16 = detail::select_default >
struct select {
    typedef typename
            mpl::if_<
                Case1, Type1, typename mpl::if_<
                Case2, Type2, typename mpl::if_<
                Case3, Type3, typename mpl::if_<
                Case4, Type4, typename mpl::if_<
                Case5, Type5, typename mpl::if_<
                Case6, Type6, typename mpl::if_<
                Case7, Type7, typename mpl::if_<
                Case8, Type8, typename mpl::if_<
                Case9, Type9, typename mpl::if_<
                Case10, Type10, typename mpl::if_<
                Case11, Type11, typename mpl::if_<
                Case12, Type12, typename mpl::if_<
                Case13, Type13, typename mpl::if_<
                Case14, Type14, typename mpl::if_<
                Case15, Type15, typename mpl::if_<
                Case16, Type16, mpl::void_
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
                >::type
            >::type                                 temp;
    typedef typename detail::lazy_eval<temp>::type  type;
};

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED
