/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_DETAIL_SP_IF_ARRAY_HPP
#define BOOST_SMART_PTR_DETAIL_SP_IF_ARRAY_HPP

#include <boost/smart_ptr/shared_ptr.hpp>

namespace boost {
    namespace detail {
        template<typename T> 
        struct sp_if_array {
        };
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        template<typename T>
        struct sp_if_array<T[]> {
            typedef boost::shared_ptr<T[]> type;
        };
#endif
    }
}

#endif
