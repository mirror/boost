///////////////////////////////////////////////////////////////////////////////
// icase.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_ICASE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_ICASE_HPP_EAN_10_04_2005

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/regex_constants.hpp>
#include <boost/xpressive/detail/static/modifier.hpp>
#include <boost/xpressive/detail/core/linker.hpp>

namespace boost { namespace xpressive
{

namespace regex_constants { namespace
{

    detail::modifier_op<detail::icase_modifier> const icase = {{}, regex_constants::icase_};

}} // namespace regex_constants::anonymous-namespace

using regex_constants::icase;

}} // namespace boost::xpressive

#endif
