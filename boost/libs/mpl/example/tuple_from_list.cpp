//-----------------------------------------------------------------------------
// boost mpl/example/tuple_from_list.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/fold_backward.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/tuple/tuple.hpp"

#include <iostream>

using namespace boost::mpl;

template< typename Types > struct tuple_gen
    : fold_backward<
          Types
        , boost::tuples::null_type
        , boost::tuples::cons<_2,_1>
        >
{
};

int main()
{
    tuple_gen< list<int,char const*,bool> >::type t;
    
    boost::get<0>(t) = -1;
    boost::get<1>(t) = "text";
    boost::get<2>(t) = false;

    std::cout
        << boost::get<0>(t) << '\n'
        << boost::get<1>(t) << '\n'
        << boost::get<2>(t) << '\n'
        ;

    return 0;
}
