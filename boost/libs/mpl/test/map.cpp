
// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/begin_end.hpp>

#include <boost/mpl/aux_/test.hpp>


MPL_TEST_CASE()
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef   m_mask<char
            , m_item<int,unsigned
            , m_item<char,unsigned char
            , map0<> > > > m;
#else
    typedef   m_mask<char
            , m_item2<int,unsigned
            , m_item1<char,unsigned char
            , map0<> > > > m;
#endif

    MPL_ASSERT_RELATION( size<m>::type::value, ==, 1 );
    MPL_ASSERT_NOT(( empty<m> ));
    MPL_ASSERT(( is_same< clear<m>::type,map0<> > ));
    MPL_ASSERT(( is_same< at<m,int>::type,unsigned> ));
    MPL_ASSERT(( is_same< at<m,char>::type,void_ > ));
    MPL_ASSERT(( contains< m,pair<int,unsigned> > ));
    MPL_ASSERT_NOT(( contains< m,pair<int,int> > ));
    MPL_ASSERT_NOT(( contains< m,pair<char,unsigned char> > ));

    MPL_ASSERT_NOT(( has_key<m,char>::type ));
    MPL_ASSERT(( has_key<m,int>::type ));
    MPL_ASSERT_RELATION( (order<m,int>::type::value), ==, 3 );
    MPL_ASSERT(( is_same< item_by_order<m,3>::type,pair<int,unsigned> > ));
    MPL_ASSERT(( is_same< order<m,char>::type,void_ > ));

    typedef begin<m>::type first;
    typedef end<m>::type last;

    MPL_ASSERT(( is_same< first::type,pair<int,unsigned> > ));
    MPL_ASSERT(( is_same< next<first>::type,last > ));

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef m_item<char,long,m> m2;
#else
    typedef m_item3<char,long,m> m2;
#endif

    MPL_ASSERT_RELATION( size<m2>::type::value, ==, 2 );
    MPL_ASSERT_NOT(( empty<m2>::type ));
    MPL_ASSERT(( is_same< clear<m2>::type,map0<> > ));
    MPL_ASSERT(( is_same< at<m2,int>::type,unsigned > ));
    MPL_ASSERT(( is_same< at<m2,char>::type,long > ));

    MPL_ASSERT(( contains< m2,pair<int,unsigned> > ));
    MPL_ASSERT_NOT(( contains< m2,pair<int,int> > ));
    MPL_ASSERT_NOT(( contains< m2,pair<char,unsigned char> > ));
    MPL_ASSERT(( contains< m2,pair<char,long> > ));

    MPL_ASSERT(( has_key<m2,char>::type ));
    MPL_ASSERT_NOT(( has_key<m2,long>::type ));
    MPL_ASSERT_RELATION( (order<m2,int>::type::value), ==, 3 );
    MPL_ASSERT_RELATION( (order<m2,char>::type::value), ==, 4 );

    typedef begin<m2>::type first2;
    typedef end<m2>::type last2;

    MPL_ASSERT(( is_same<first2::type,pair<int,unsigned> > ));
    typedef next<first2>::type iter;
    MPL_ASSERT(( is_same<iter::type,pair<char,long> > ));
    MPL_ASSERT(( is_same< next<iter>::type,last2 > ));

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef insert<m2,pair<int,unsigned> >::type s2_1;
    MPL_ASSERT(( is_same<m2,s2_1> ));

    typedef insert<m2,pair<long,unsigned> >::type m3;
    MPL_ASSERT_RELATION( size<m3>::type::value, ==, 3 );
    MPL_ASSERT(( has_key<m3,long>::type ));
    MPL_ASSERT(( has_key<m3,int>::type ));
    MPL_ASSERT(( has_key<m3,char>::type ));
    MPL_ASSERT(( contains< m3,pair<long,unsigned> > ));
    MPL_ASSERT(( contains< m3,pair<int,unsigned> > ));

    typedef insert<m,pair<char,long> >::type m1;
    MPL_ASSERT_RELATION( size<m1>::type::value, ==, 2 );
    MPL_ASSERT(( is_same< at<m1,int>::type,unsigned > ));
    MPL_ASSERT(( is_same< at<m1,char>::type,long > ));

    MPL_ASSERT(( contains< m1,pair<int,unsigned> > ));
    MPL_ASSERT_NOT(( contains< m1,pair<int,int> > ));
    MPL_ASSERT_NOT(( contains< m1,pair<char,unsigned char> > ));
    MPL_ASSERT(( contains< m1,pair<char,long> > ));

    MPL_ASSERT(( is_same< m1,m2 > ));

    typedef erase_key<m1,char>::type m_1;
    MPL_ASSERT(( is_same<m,m_1> ));
    MPL_ASSERT_RELATION( size<m_1>::type::value, ==, 1 );
    MPL_ASSERT(( is_same< at<m_1,char>::type,void_ > ));
    MPL_ASSERT(( is_same< at<m_1,int>::type,unsigned > ));

    typedef erase_key<m3,char>::type m2_1;
    MPL_ASSERT_RELATION( size<m2_1>::type::value, ==, 2 );
    MPL_ASSERT(( is_same< at<m2_1,char>::type,void_ > ));
    MPL_ASSERT(( is_same< at<m2_1,int>::type,unsigned > ));
    MPL_ASSERT(( is_same< at<m2_1,long>::type,unsigned > ));
#endif
}

MPL_TEST_CASE()
{
    typedef map0<> m;
    
    MPL_ASSERT_RELATION( size<m>::type::value, ==, 0 );
    MPL_ASSERT(( empty<m>::type ));

    MPL_ASSERT(( is_same< clear<m>::type,map0<> > ));
    MPL_ASSERT(( is_same< at<m,char>::type,void_ > ));

    MPL_ASSERT_NOT(( has_key<m,char>::type ));
    MPL_ASSERT_NOT(( has_key<m,int>::type ));
    MPL_ASSERT_NOT(( has_key<m,UDT>::type ));
    MPL_ASSERT_NOT(( has_key<m,incomplete>::type ));

    MPL_ASSERT_NOT(( has_key<m,char const>::type ));
    MPL_ASSERT_NOT(( has_key<m,int const>::type ));
    MPL_ASSERT_NOT(( has_key<m,UDT const>::type ));
    MPL_ASSERT_NOT(( has_key<m,incomplete const>::type ));

    MPL_ASSERT_NOT(( has_key<m,int*>::type ));
    MPL_ASSERT_NOT(( has_key<m,UDT*>::type ));
    MPL_ASSERT_NOT(( has_key<m,incomplete*>::type ));

    MPL_ASSERT_NOT(( has_key<m,int&>::type ));
    MPL_ASSERT_NOT(( has_key<m,UDT&>::type ));
    MPL_ASSERT_NOT(( has_key<m,incomplete&>::type ));

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef insert<m,pair<char,int> >::type m1;
    MPL_ASSERT_RELATION( size<m1>::type::value, ==, 1 );
    MPL_ASSERT(( is_same< at<m1,char>::type,int > ));

    typedef erase_key<m,char>::type m0_1;
    MPL_ASSERT_RELATION( size<m0_1>::type::value, ==, 0 );
    MPL_ASSERT(( is_same< at<m0_1,char>::type,void_ > ));
#endif
}
