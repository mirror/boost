///////////////////////////////////////////////////////////////////////////////
// quant_style.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_QUANT_STYLE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_QUANT_STYLE_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/xpressive/detail/utility/width.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>

#if defined(NDEBUG) & defined(BOOST_XPR_DEBUG_STACK)
# undef BOOST_XPR_DEBUG_STACK
#endif

#ifdef BOOST_XPR_DEBUG_STACK
# define BOOST_XPR_DEBUG_STACK_ASSERT BOOST_ASSERT
#else
# define BOOST_XPR_DEBUG_STACK_ASSERT(x) static_cast<void>(0)
#endif

namespace boost { namespace xpressive { namespace detail
{

//////////////////////////////////////////////////////////////////////////
// xpression_base
//
//struct xpression_base
//{
//#ifdef BOOST_XPR_DEBUG_STACK
//    virtual ~xpression_base()
//    {
//    }
//#endif
//};

// BUGBUG
typedef void xpression_base;

BOOST_MPL_HAS_XXX_TRAIT_DEF(is_xpression)

///////////////////////////////////////////////////////////////////////////////
// is_xpr
//
template<typename Xpr>
struct is_xpr
  : has_is_xpression<Xpr>
{};

///////////////////////////////////////////////////////////////////////////////
// quant_enum
//
enum quant_enum
{
    quant_none,
    quant_fixed_width,
    quant_variable_width
};

///////////////////////////////////////////////////////////////////////////////
// quant_style
//
template<quant_enum QuantStyle, std::size_t Width = unknown_width::value, bool Pure = true>
struct quant_style
{
    typedef void is_xpression;

    // Which quantification strategy to use?
    BOOST_STATIC_CONSTANT(quant_enum, quant = QuantStyle);

    // how many characters this matcher consumes
    BOOST_STATIC_CONSTANT(std::size_t, width = Width);

    // whether this matcher has observable side-effects
    BOOST_STATIC_CONSTANT(bool, pure = Pure);

    static detail::width get_width()
    {
        return width;
    }
};

#define BOOST_XPR_QUANT_STYLE(Style, Width, Pure)\
    typedef void is_xpression;\
    BOOST_STATIC_CONSTANT(quant_enum, quant = Style);\
    BOOST_STATIC_CONSTANT(std::size_t, width = Width);\
    BOOST_STATIC_CONSTANT(bool, pure = Pure);\
    static detail::width get_width() { return width; }\
    /**/

///////////////////////////////////////////////////////////////////////////////
// quant_style_none
//  this sub-expression cannot be quantified
typedef quant_style<quant_none> quant_style_none;

///////////////////////////////////////////////////////////////////////////////
// quant_style_fixed_unknown_width
//  this sub-expression is fixed width for the purpose of quantification, but
//  the width cannot be determined at compile time. An example would be the
//  string_matcher or the mark_matcher.
typedef quant_style<quant_fixed_width> quant_style_fixed_unknown_width;

///////////////////////////////////////////////////////////////////////////////
// quant_style_variable_width
//  this sub-expression can match a variable number of characters
typedef quant_style<quant_variable_width> quant_style_variable_width;

///////////////////////////////////////////////////////////////////////////////
// quant_style_fixed_width
//  for when the sub-expression has a fixed width that is known at compile time
template<std::size_t Width>
struct quant_style_fixed_width
  : quant_style<quant_fixed_width, Width>
{
};

///////////////////////////////////////////////////////////////////////////////
// quant_style_assertion
//  a zero-width assertion.
struct quant_style_assertion
  : quant_style<quant_none, 0>
{
};

///////////////////////////////////////////////////////////////////////////////
// quant_type
//
template<typename Matcher>
struct quant_type
  : mpl::int_<Matcher::quant>
{
};

}}} // namespace boost::xpressive::detail

#endif
