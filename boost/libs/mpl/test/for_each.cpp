//-----------------------------------------------------------------------------
// boost mpl/test/for_each.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/for_each.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/bind.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <cassert>

namespace mpl = boost::mpl;
using mpl::_;

struct type_printer
{
    type_printer(std::ostream& s) : f_stream(&s) {}
    template< typename U > void operator()(mpl::identity<U>)
    {
        *f_stream << typeid(U).name() << '\n';
    }

 private:
    std::ostream* f_stream;
};

struct value_printer
{
    value_printer(std::ostream& s) : f_stream(&s) {}
    template< typename U > void operator()(U x)
    {
        *f_stream << x << '\n';
    }

 private:
    std::ostream* f_stream;
};

#ifdef __ICL
# pragma warning(disable:985)
#endif

int main()
{
    typedef mpl::list<char,short,int,long,float,double> types;
    mpl::for_each< types,mpl::make_identity<_> >(type_printer(std::cout));

    typedef mpl::range_c<int,0,10> numbers;
    std::vector<int> v;

#if !defined(__BORLANDC__) && (__BORLANDC__ >= 0x561 && !defined(BOOST_STRICT_CONFIG))
    mpl::for_each<numbers,mpl::_>(
          boost::bind(&std::vector<int>::push_back, &v, _1)
        );    
#else
    void (std::vector<int>::* push_back)(int const&) = &std::vector<int>::push_back;
    mpl::for_each<numbers,mpl::_>(
          boost::bind(push_back, &v, _1)
        );
#endif

    mpl::for_each< numbers >(value_printer(std::cout));
    
    for (unsigned i = 0; i < v.size(); ++i)
        assert(v[i] == (int)i);

    return 0;
}
