///////////////////////////////////////////////////////////////////////////////
// modifier.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_MODIFIER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_MODIFIER_HPP_EAN_10_04_2005

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/regex_constants.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // modifier
    template<typename ModifierT>
    struct modifier_op
    {
        typedef regex_constants::syntax_option_type opt_type;

        template<typename XprT>
        struct apply
        {
            typedef proto::binary_op<ModifierT, typename as_xpr_type<XprT>::type, modifier_tag> type;
        };

        template<typename XprT>
        typename apply<XprT>::type    
        operator ()(XprT const &xpr) const
        {
            return proto::make_op<modifier_tag>(this->mod_, as_xpr(xpr));
        }

        operator opt_type() const
        {
            return this->opt_;
        }

        ModifierT mod_;
        opt_type opt_;
    };

}}}

#endif
