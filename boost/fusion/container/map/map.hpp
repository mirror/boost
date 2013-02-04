/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_MAIN_07212005_1106)
#define FUSION_MAP_MAIN_07212005_1106

#include <boost/fusion/container/map/map_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/map_impl.hpp>
#include <boost/fusion/container/map/detail/begin_impl.hpp>
#include <boost/fusion/container/map/detail/end_impl.hpp>
#include <boost/fusion/container/map/detail/at_impl.hpp>
#include <boost/fusion/container/map/detail/at_key_impl.hpp>
#include <boost/fusion/container/map/detail/value_at_key_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    template <typename ...T>
    struct map : detail::map_impl<0, T...>, sequence_base<map<T...>>
    {
        typedef map_tag fusion_tag;
        typedef detail::map_impl<0, T...> base_type;

        struct category : random_access_traversal_tag, associative_tag {};
        typedef mpl::int_<base_type::size> size;
        typedef mpl::false_ is_view;

        map() {};

        map(typename detail::call_param<T>::type... element)
          : base_type(element...)
        {}
    };
}}

#endif
#endif
