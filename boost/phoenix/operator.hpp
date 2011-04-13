/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_OPERATOR_HPP
#define BOOST_PHOENIX_OPERATOR_HPP

#ifdef BOOST_PHOENIX_USE_V2_OVER_V3
#include <boost/spirit/home/phoenix/operator.hpp>
#else
#include <boost/phoenix/version.hpp>
#include <boost/phoenix/operator/arithmetic.hpp>
#include <boost/phoenix/operator/bitwise.hpp>
#include <boost/phoenix/operator/comparision.hpp>
#include <boost/phoenix/operator/if_else.hpp>
#include <boost/phoenix/operator/self.hpp>
#include <boost/phoenix/operator/logical.hpp>
#include <boost/phoenix/operator/io.hpp>
#include <boost/phoenix/operator/member.hpp>
#endif

#endif
