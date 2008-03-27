#ifndef BOOST_DETAIL_YIELD_K_HPP_INCLUDED
#define BOOST_DETAIL_YIELD_K_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/detail/yield_k.hpp
//
//  Copyright (c) 2008 Peter Dimov
//
//  void yield( unsigned k );
//
//  Typical use:
//
//  for( unsigned k = 0; !try_lock(); ++k ) yield( k );
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/config.hpp>

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ )

#if defined( BOOST_USE_WINDOWS_H )
# include <windows.h>
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1310
  extern "C" void _mm_pause();
#endif

namespace boost
{

namespace detail
{

#if !defined( BOOST_USE_WINDOWS_H )
  extern "C" void __stdcall Sleep( unsigned ms );
#endif

void yield( unsigned k )
{
    if( k < 4 )
    {
    }
#if defined(_MSC_VER) && _MSC_VER >= 1310
    else if( k < 16 )
    {
        _mm_pause();
    }
#endif
    else if( k < 32 )
    {
        Sleep( 0 );
    }
    else
    {
        Sleep( 1 );
    }
}

} // namespace detail

} // namespace boost

#elif defined( BOOST_HAS_PTHREADS )

#include <sched.h>
#include <time.h>

namespace boost
{

namespace detail
{

void yield( unsigned k )
{
    if( k < 4 )
    {
    }
#if defined( __GNUC__ ) && ( defined( __i386__ ) || defined( __x86_64__ ) )
    else if( k < 16 )
    {
        __asm__ __volatile__( "rep; nop" ::: "memory" );
    }
#endif
    else if( k < 32 || k & 1 )
    {
        sched_yield();
    }
    else
    {
        struct timespec rqtp = { 0 };

        rqtp.tv_sec = 0;
        rqtp.tv_nsec = 1000;

        nanosleep( &rqtp, 0 );
    }
}

} // namespace detail

} // namespace boost

#else

namespace boost
{

namespace detail
{

inline void yield( unsigned )
{
}

} // namespace detail

} // namespace boost

#endif

#endif // #ifndef BOOST_DETAIL_YIELD_K_HPP_INCLUDED
