//-----------------------------------------------------------------------------
// boost mpl/test/filter_view.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/filter_view.hpp"
#include "boost/mpl/transform_view.hpp"
#include "boost/mpl/max_element.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/sizeof.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;
using mpl::_;

int main()
{
    typedef mpl::list<int,float,long,float,char[50],long double,char> types;
    typedef mpl::max_element<
          mpl::transform_view<
              mpl::filter_view< types,boost::is_float<_> >
            , mpl::sizeof_<_>
            >
        >::type iter;

    BOOST_STATIC_ASSERT((boost::is_same<iter::base::type,long double>::value));
    return 0;
}
