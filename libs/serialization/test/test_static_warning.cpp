//  (C) Copyright Jonathan Turkanis 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version including documentation.

// note: this is a compile only test.

#include <boost/static_warning.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#pragma warning(disable:4094)

typedef char a1[2];
typedef char a2[3];

class polymorphic {
    virtual ~polymorphic();
};

class non_polymorphic {
};

// note: compilation of this program should show 8 warning messages

BOOST_STATIC_WARNING(true);
BOOST_STATIC_WARNING(sizeof(a1) == sizeof(a2)); // Warn.
BOOST_STATIC_WARNING(sizeof(a1) != sizeof(a1)); // Warn.
BOOST_STATIC_WARNING(! boost::is_polymorphic<polymorphic>::value); // Warn.
BOOST_STATIC_WARNING(boost::is_polymorphic<non_polymorphic>::value); // Warn.

void warnings() {
    BOOST_STATIC_WARNING(true);
    BOOST_STATIC_WARNING(sizeof(a1) == sizeof(a2)); // Warn.
    BOOST_STATIC_WARNING(sizeof(a1) != sizeof(a1)); // Warn.
    BOOST_STATIC_WARNING(! boost::is_polymorphic<polymorphic>::value); // Warn.
    BOOST_STATIC_WARNING(boost::is_polymorphic<non_polymorphic>::value); // Warn.
}                               

int main(int /* argc */, char * /* argv */[]){
    warnings();
    return 0;
}
