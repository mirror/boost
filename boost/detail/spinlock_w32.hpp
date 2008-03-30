#ifndef BOOST_DETAIL_SPINLOCK_W32_HPP_INCLUDED
#define BOOST_DETAIL_SPINLOCK_W32_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/detail/interlocked.hpp>
#include <boost/detail/yield_k.hpp>

#if defined( _MSC_VER ) && _MSC_VER >= 1310
  extern "C" void _ReadWriteBarrier();
# pragma intrinsic( _ReadWriteBarrier )
#endif

namespace boost
{

namespace detail
{

class spinlock
{
public:

    long v_;

public:

    bool try_lock()
    {
        long r = BOOST_INTERLOCKED_EXCHANGE( &v_, 1 );

#if defined( _MSC_VER ) && _MSC_VER >= 1310
        _ReadWriteBarrier();
#endif

        return r == 0;
    }

    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }

    void unlock()
    {
#if defined( _MSC_VER ) && _MSC_VER >= 1310
        _ReadWriteBarrier();
#endif

        *const_cast< long volatile* >( &v_ ) = 0;
    }

public:

    class scoped_lock
    {
    private:

        spinlock & sp_;

        scoped_lock( scoped_lock const & );
        scoped_lock & operator=( scoped_lock const & );

    public:

        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }

        ~scoped_lock()
        {
            sp_.unlock();
        }
    };
};

} // namespace detail
} // namespace boost

#define BOOST_DETAIL_SPINLOCK_INIT {0}

#endif // #ifndef BOOST_DETAIL_SPINLOCK_W32_HPP_INCLUDED
