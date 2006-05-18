// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ITERATOR_HPP
#define BOOST_RANGE_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/mutable_iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
    template< typename C >
    struct range_iterator
    {
        typedef BOOST_RANGE_DEDUCED_TYPENAME 
            mpl::eval_if_c< is_const<C>::value, 
                            range_const_iterator< typename remove_const<C>::type >,
                            range_mutable_iterator<C> >::type type;
    };
    
} // namespace boost

//#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif
