//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_STRING_TRAITS_HPP
#define BOOST_STRING_STD_STRING_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <string>

namespace boost {
    namespace algorithm {

//  std::basic_string<> traits  -----------------------------------------------//

        // native replace tester
        template<typename T, typename TraitsT, typename AllocT>
        yes_type has_native_replace_tester( const std::basic_string<T, TraitsT, AllocT>* );

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_LIST_TRAITS_HPP
