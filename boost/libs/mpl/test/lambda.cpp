//-----------------------------------------------------------------------------
// boost mpl/test/lambda.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/logical.hpp"
#include "boost/mpl/comparison.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/int_c.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/size_of.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct my
{
    char a[100];
};

int main()
{
    using namespace mpl::placeholder;

    // !(x == char) && !(x == double) && x convertible to int || size_of(x) > 8
    typedef mpl::lambda<
        mpl::logical_or<
              mpl::logical_and<
                    mpl::logical_not< boost::is_same<_1, char> >
                  , mpl::logical_not< boost::is_float<_1> >
                  >
            , mpl::greater< mpl::size_of<_1>, mpl::int_c<8> >
            >
        >::type f1;

    BOOST_STATIC_ASSERT(!f1::apply<char>::type::value);
    BOOST_STATIC_ASSERT(!f1::apply<double>::type::value);
    BOOST_STATIC_ASSERT(f1::apply<long>::type::value);
    BOOST_STATIC_ASSERT(f1::apply<my>::type::value);

    // x == y || x == my || sizeof(x) == sizeof(y)
    typedef mpl::lambda<
        mpl::logical_or< 
              boost::is_same<_1, _2>
            , boost::is_same<_2, my>
            , mpl::equal_to< mpl::size_of<_1>, mpl::size_of<_2> >
            >
        >::type f2;

    BOOST_STATIC_ASSERT((!f2::apply<double,char>::type::value));
    BOOST_STATIC_ASSERT((!f2::apply<my,int>::type::value));
    BOOST_STATIC_ASSERT((!f2::apply<my,char[99]>::type::value));
    BOOST_STATIC_ASSERT((f2::apply<int,int>::type::value));
    BOOST_STATIC_ASSERT((f2::apply<my,my>::type::value));
    BOOST_STATIC_ASSERT((f2::apply<signed long, unsigned long>::type::value));

    // bind <-> lambda interaction
    typedef mpl::lambda< mpl::less<_1,_2> >::type pred;
    typedef mpl::bind2< pred, _1, mpl::int_c<4> > f3;
    
    BOOST_STATIC_ASSERT((f3::apply< mpl::int_c<3> >::type::value));
          
    return 0;
}
