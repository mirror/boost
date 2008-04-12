//
//  sp_accept_owner_test.cpp
//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

namespace N
{

struct D;

struct X
{
    X * px_;

    D * pd_;
    void * pv_;

    X(): px_( 0 ), pd_( 0 ), pv_( 0 )
    {
    }
};

struct D
{
    template<class T> void operator()( T * p ) const { delete p; }
};

} // namespace N

#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP )

namespace N
{

#else

namespace boost
{

#endif

template<class Y> inline void sp_accept_owner( boost::shared_ptr<Y> * ps, ::N::X * px )
{
    std::cout << "sp_accept_owner( " << ps << ", " << px << " )\n";

    BOOST_TEST( ps->get() == px );

    if( px != 0 )
    {
        px->px_ = px;
    }
}

template<class Y> inline void sp_accept_owner( boost::shared_ptr<Y> * ps, ::N::X * px, ::N::D * pd )
{
    std::cout << "sp_accept_owner( " << ps << ", " << px << ", (D*)" << pd << " )\n";

    BOOST_TEST( ps->get() == px );

    if( px != 0 )
    {
        px->px_ = px;
        px->pd_ = pd;
    }
}

template<class Y> inline void sp_accept_owner( boost::shared_ptr<Y> * ps, ::N::X * px, void * pv )
{
    std::cout << "sp_accept_owner( " << ps << ", " << px << ", (void*)" << pv << " )\n";

    BOOST_TEST( ps->get() == px );

    if( px != 0 )
    {
        px->px_ = px;
        px->pv_ = pv;
    }
}

} // namespace N or boost

struct D2
{
    template<class T> void operator()( T * p ) const { delete p; }
};

template<class T> void test( T* = 0 )
{
    {
        boost::shared_ptr<T> p( static_cast< T* >( 0 ) );
    }

    {
        T * p = new T;
        boost::shared_ptr<T> q( p );

        BOOST_TEST( q->px_ == p );
        BOOST_TEST( q->pd_ == 0 );
        BOOST_TEST( q->pv_ == 0 );
    }

    {
        T * p = new T;
        boost::shared_ptr<T> q( p, N::D() );

        BOOST_TEST( q->px_ == p );
        BOOST_TEST( q->pd_ != 0 );
        BOOST_TEST( q->pv_ == 0 );
    }

    {
        T * p = new T;
        boost::shared_ptr<T> q( p, D2() );

        BOOST_TEST( q->px_ == p );
        BOOST_TEST( q->pd_ == 0 );
        BOOST_TEST( q->pv_ != 0 );
    }
}

namespace N2
{

struct Y: public virtual N::X
{
};

} // namespace N2

int main()
{
    test<N::X>();
    test<N2::Y>();

    return boost::report_errors();
}
