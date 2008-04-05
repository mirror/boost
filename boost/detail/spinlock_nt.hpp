#ifndef BOOST_DETAIL_SPINLOCK_NT_HPP_INCLUDED
#define BOOST_DETAIL_SPINLOCK_NT_HPP_INCLUDED

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

namespace boost
{

namespace detail
{

class spinlock
{
public:

    inline bool try_lock()
    {
        return true;
    }

    inline void lock()
    {
    }

    inline void unlock()
    {
    }

public:

    class scoped_lock
    {
    private:

        scoped_lock( scoped_lock const & );
        scoped_lock & operator=( scoped_lock const & );

    public:

        explicit scoped_lock( spinlock & /*sp*/ )
        {
        }

        ~scoped_lock()
        {
        }
    };
};

} // namespace detail
} // namespace boost

#define BOOST_DETAIL_SPINLOCK_INIT {}

#endif // #ifndef BOOST_DETAIL_SPINLOCK_NT_HPP_INCLUDED
