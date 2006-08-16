/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1442)
#define FUSION_CLEAR_10022005_1442

#include <boost/fusion/sequence/container.hpp>

namespace boost { namespace fusion { namespace detail 
{
    template <typename Tag>
    struct clear;

    template <>
    struct clear<cons_tag> : mpl::identity<list<> > {};

    template <>
    struct clear<map_tag> : mpl::identity<map<> > {};

    template <>
    struct clear<set_tag> : mpl::identity<set<> > {};

    template <>
    struct clear<vector_tag> : mpl::identity<vector<> > {};

}}}

#endif
