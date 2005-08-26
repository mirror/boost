// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

// Inclusion of this file increments BOOST_TYPEOF_REGISTRATION_GROUP 
// This method was suggested by Paul Mensonides

#ifndef BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP_HPP_INCLUDED

#   define BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP_HPP_INCLUDED
#   include <boost/preprocessor/slot/slot.hpp>
#   define BOOST_TYPEOF_REGISTRATION_GROUP 0

#else

#   define BOOST_PP_VALUE BOOST_TYPEOF_REGISTRATION_GROUP + 1
#   include BOOST_PP_ASSIGN_SLOT(1)
#   undef BOOST_TYPEOF_REGISTRATION_GROUP
#   define BOOST_TYPEOF_REGISTRATION_GROUP BOOST_PP_SLOT(1)

#endif//BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP_HPP_INCLUDED
