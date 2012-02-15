
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_

/** @file
@brief Change the compile-time configuration of this library.
*/

/**
@brief Specify the maximum number of arguments of the functions being
overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When specified by the user, this macro must be a non-negative integer number.

@See
    @RefSectId{Getting_Started, Getting Started},
    @RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 5
#endif

/**
@brief Specify the maximum number of functions that can be overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When defined by the user, this macro must be an integer number greater or
equal than 2 (because at least two distinct functions need to be specified in
order to define an overload).

@See
    @RefSectId{Getting_Started, Getting Started},
    @RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX 5
#endif
#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < 2
#error "BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX must be >= 2"
#endif

#endif // #include guard

