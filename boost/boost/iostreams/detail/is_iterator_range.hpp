// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED       
 
#include <boost/config.hpp>                   // partial spec.
#include <boost/iostreams/detail/bool_trait_def.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value.
#include <boost/range/iterator_range.hpp>         

//#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //---------------------------//
//
//namespace boost { namespace iostreams { 
//
//template<typename T>
//struct is_iterator_range : mpl::false_ { };
//
//template<typename Iter>
//struct is_iterator_range< iterator_range<Iter> >
//    : mpl::true_ 
//    { };
//
//} } // End namespaces iostreams, boost.
//
//#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //--------------------------//

// We could make this exactly equivalent to the implementation using partial
// specialization by adding a test for the condition:
//
//     is_same< T, iterator_range<typename iterator_value<T>::type> >
//
// Currently it does not seem to be worth the trouble.
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iterator_range, boost::iterator_range, 1)

//#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //-------------------------//

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
