
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/utility/identity_type

#include <boost/utility/identity_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <map>

//[tmp_assert_abstract
#define TMP_ASSERT(metafunction) \
    BOOST_STATIC_ASSERT(metafunction::value)

template<typename T, bool b>
struct abstract {
    static const bool value = b;
    virtual void f(T const& x) = 0;
};

TMP_ASSERT(
    boost::remove_reference<            // Add and remove
        BOOST_IDENTITY_TYPE((           // reference for
            boost::add_reference<       // abstract type.
                abstract<int, true>
            >::type
        ))
    >::type
);
//]

//[tmp_assert_alternative
#define TMP_ASSERT_PAREN(parenthesized_metafunction) \
    /* use `BOOST_IDENTITY_TYPE` in macro definition instead of invocation */ \
    BOOST_STATIC_ASSERT(BOOST_IDENTITY_TYPE(parenthesized_metafunction)::value)

TMP_ASSERT_PAREN(( boost::is_const<std::map<int, char> const> ));
TMP_ASSERT( BOOST_IDENTITY_TYPE((boost::is_const<std::map<int, char> const>)) );
//]

//[tmp_assert_alternative_always
TMP_ASSERT_PAREN(( boost::is_const<int const> )); // Always extra `()`.
TMP_ASSERT( boost::is_const<int const> ); // No extra `()` and no macro.
//]

int main() { return 0; }

