// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_TYPEOF_HPP_INCLUDED
#define BOOST_TYPEOF_TYPEOF_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/expand.hpp>

// implementation

#include <boost/typeof/config.hpp>

// BOOST_TYPEOF, BOOST_TYPEOF_TPL

#if defined(BOOST_TYPEOF_NATIVE) && defined(BOOST_MSVC)
#   define BOOST_TYPEOF_TEXT "using msvc 'native' imlementation"
#   include <boost/typeof/message.hpp>
#	include <boost/typeof/msvc/typeof_impl.hpp>

#elif defined(BOOST_TYPEOF_COMPLIANT)
#   define BOOST_TYPEOF_TEXT "using compliant imlementation"
#   include <boost/typeof/message.hpp>
#   include <boost/typeof/typeof_impl.hpp>

#else//BOOST_TYPEOF_NATIVE

#   define BOOST_TYPEOF_TEXT "using native imlementation"
#   include <boost/typeof/message.hpp>

#	if !defined BOOST_TYPEOF_KEYWORD
#		define BOOST_TYPEOF_KEYWORD typeof
#	endif

    /* Native typeof can accept either type or value.
    Something like "int()" can be viewed either way, but 
    typeof consideres it a type.  We force it otherwise
    to ensure consistensy with emulation */

    namespace boost { namespace type_of {
        template<class T> T& ensure_obj(const T&);
    }}

#   define BOOST_TYPEOF(expr) BOOST_TYPEOF_KEYWORD(boost::type_of::ensure_obj(expr))

#	define BOOST_TYPEOF_TPL BOOST_TYPEOF

#endif

// auto
#define BOOST_AUTO(Var, Expr) BOOST_TYPEOF(Expr) Var = Expr
#define BOOST_AUTO_TPL(Var, Expr) BOOST_TYPEOF_TPL(Expr) Var = Expr

// lvalue typeof

#	include <boost/typeof/lvalue_typeof.hpp>

// type/template encoding

#if defined(BOOST_TYPEOF_COMPLIANT)
#	include <boost/typeof/type_encoding.hpp>
#	include <boost/typeof/template_encoding.hpp>
#else   //BOOST_TYPEOF_NATIVE
#	define BOOST_TYPEOF_REGISTER_TYPE(x)
#	define BOOST_TYPEOF_REGISTER_TEMPLATE(x, params)
#endif

#define BOOST_TYPEOF_UNIQUE_ID()\
    BOOST_TYPEOF_REGISTRATION_GROUP * 0x10000 + __LINE__

#define BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()\
    <boost/typeof/increment_registration_group.hpp>

// register stuff
#include <boost/typeof/register_fundamental.hpp>

#if defined(BOOST_TYPEOF_COMPLIANT)

#	include <boost/typeof/modifiers.hpp>
#	include <boost/typeof/pointers_data_members.hpp>
#	include <boost/typeof/register_functions.hpp>

#else //BOOST_TYPEOF_NATIVE

#endif

#endif//BOOST_TYPEOF_TYPEOF_HPP_INCLUDED
