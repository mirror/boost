//-----------------------------------------------------------------------------
// boost mpl/test/transform_view.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/transform_view.hpp"
#include "boost/mpl/max_element.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/sizeof.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;
using mpl::_;

int main()
{
    typedef mpl::list<int,long,char,char[50],double> types;
    typedef mpl::max_element<
          mpl::transform_view< types, mpl::sizeof_<_> >
        >::type iter;

    BOOST_STATIC_ASSERT(iter::type::value == 50);
    return 0;
}
