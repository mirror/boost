//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_ROPE_TRAITS_HPP
#define BOOST_STRING_STD_ROPE_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <rope>

namespace boost {
    namespace algorithm {

//  SGI's std::rope<> traits  -----------------------------------------------//

        // native replace tester
        template<typename T, typename TraitsT, typename AllocT>
        yes_type has_native_replace_tester( const std::rope<T, TraitsT, AllocT>* );

        // stable iterators tester
        template<typename T, typename TraitsT, typename AllocT>
        yes_type has_stable_iterators_tester( const std::rope<T, TraitsT, AllocT>* );

        // const time insert tester
        template<typename T, typename TraitsT, typename AllocT>
        yes_type has_const_time_insert_tester( const std::rope<T, TraitsT, AllocT>* );

        // const time erase tester
        template<typename T, typename TraitsT, typename AllocT>
        yes_type has_const_time_erase_tester( const std::rope<T, TraitsT, AllocT>* );

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_ROPE_TRAITS_HPP
