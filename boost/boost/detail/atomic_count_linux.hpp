#ifndef BOOST_DETAIL_ATOMIC_COUNT_LINUX_HPP_INCLUDED
#define BOOST_DETAIL_ATOMIC_COUNT_LINUX_HPP_INCLUDED

//
//  boost/detail/atomic_count_linux.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

//
// On Linux, atomic.h is usually located in /usr/include/asm
//

#include <asm/atomic.h>

namespace boost
{

namespace detail
{

class atomic_count
{
public:

    explicit atomic_count(long v)
    {
        atomic_t init = ATOMIC_INIT(v);
        value_ = init;
    }

    void operator++()
    {
        atomic_inc(&value_);
    }

    long operator--()
    {
        return !atomic_dec_and_test(&value_);
    }

    operator long() const
    {
        return atomic_read(&value_);
    }

private:

    atomic_count(atomic_count const &);
    atomic_count & operator=(atomic_count const &);

    atomic_t value_;
};

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_DETAIL_ATOMIC_COUNT_LINUX_HPP_INCLUDED
