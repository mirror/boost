
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_HPP_
#define BOOST_LOCAL_FUNCTION_CONFIG_HPP_

#ifndef DOXYGEN

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX
#define BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX 5
#endif

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX
#define BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX 10
#endif

#else // DOXYGEN

/** @file
@brief Configuration macros allow to change the behaviour of this library at
compile-time.
*/

/**
@brief Maximum number of parameters supported by local functions.

If programmers leave this configuration macro undefined, its default
value is <c>5</c> (increasing this number might increase compilation time).
When defined by programmers, this macro must be a non-negative integer number.

@Note This macro specifies the maximum number of local function parameters
excluding bound variables (which are instead specified by
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}).

@See @RefSect{Tutorial} section, @RefSectId{Getting_Started, Getting Started}
section, @RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}.
*/
#define BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX

/**
@brief Maximum number of bound variables supported by local functions.

If programmers leave this configuration macro undefined, its default
value is <c>10</c> (increasing this number might increase compilation time).
When defined by programmers, this macro must be a non-negative integer number.

@Note This macro specifies the maximum number of bound variables excluding
local function parameters (which are instead specified by
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX}).

@See @RefSect{Tutorial} section, @RefSectId{Getting_Started, Getting Started}
section, @RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX}.
*/
#define BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX

#endif // DOXYGEN

#endif // #include guard

