/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_26112006_1649)
#define BOOST_FUSION_DEQUE_26112006_1649

#include <boost/config.hpp>

#if (defined(BOOST_NO_DECLTYPE)             \
  || defined(BOOST_NO_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_RVALUE_REFERENCES))
# include <boost/fusion/container/deque/cpp03_deque.hpp>
#else
# if !defined(BOOST_FUSION_HAS_CPP11_DEQUE)
#   define BOOST_FUSION_HAS_CPP11_DEQUE
# endif
# include <boost/fusion/container/deque/cpp11_deque.hpp>
#endif

#endif
