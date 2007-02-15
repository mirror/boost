/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_HAS_TYPE_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_HAS_TYPE_HPP_INCLUDED

#include <boost/mpl/aux_/has_type.hpp>

namespace boost { namespace fusion { namespace detail
{
    // Actually it's a sin... But MSVC's weird interpretation of ADL makes
    // me do this - tosh.
    using boost::mpl::aux::has_type;
}}}

#endif
