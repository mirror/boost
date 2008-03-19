//
//  esft_regtest.cpp
//
//  A regression test for enable_shared_from_this
//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <memory>

class X: public boost::enable_shared_from_this< X >
{
private:

    int destroyed_;
    int deleted_;
    int expected_;

private:

    X( X const& );
    X& operator=( X const& );

public:

    static int instances;

public:

    explicit X( int expected ): destroyed_( 0 ), deleted_( 0 ), expected_( expected )
    {
        ++instances;
    }

    ~X()
    {
        BOOST_TEST( deleted_ == expected_ );
        BOOST_TEST( destroyed_ == 0 );
        ++destroyed_;
        --instances;
    }

    typedef void (*deleter_type)( X* );

    static void deleter( X * px )
    {
        ++px->deleted_;
    }

    static void deleter2( X * px )
    {
        ++px->deleted_;
        delete px;
    }
};

int X::instances = 0;

int main()
{
    BOOST_TEST( X::instances == 0 );

    {
        X x( 0 );
        BOOST_TEST( X::instances == 1 );
    }

    BOOST_TEST( X::instances == 0 );

    {
        std::auto_ptr<X> px( new X( 0 ) );
        BOOST_TEST( X::instances == 1 );
    }

    BOOST_TEST( X::instances == 0 );

    {
        boost::shared_ptr<X> px( new X( 0 ) );
        BOOST_TEST( X::instances == 1 );

        boost::weak_ptr<X> wp( px );
        BOOST_TEST( !wp.expired() );

        px.reset();

        BOOST_TEST( wp.expired() );
    }

    BOOST_TEST( X::instances == 0 );

    {
        X x( 1 );
        boost::shared_ptr<X> px( &x, X::deleter );
        BOOST_TEST( X::instances == 1 );

        X::deleter_type * pd = boost::get_deleter<X::deleter_type>( px );
        BOOST_TEST( pd != 0 && *pd == X::deleter );

        boost::weak_ptr<X> wp( px );
        BOOST_TEST( !wp.expired() );

        px.reset();

        BOOST_TEST( wp.expired() );
    }

    BOOST_TEST( X::instances == 0 );

    {
        boost::shared_ptr<X> px( new X( 1 ), X::deleter2 );
        BOOST_TEST( X::instances == 1 );

        X::deleter_type * pd = boost::get_deleter<X::deleter_type>( px );
        BOOST_TEST( pd != 0 && *pd == X::deleter2 );

        boost::weak_ptr<X> wp( px );
        BOOST_TEST( !wp.expired() );

        px.reset();

        BOOST_TEST( wp.expired() );
    }

    BOOST_TEST( X::instances == 0 );

    return boost::report_errors();
}
