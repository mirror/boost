#ifndef BOOST_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED
#define BOOST_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED

#if _MSC_VER >= 1020
#pragma once
#endif

//
//  boost/detail/atomic_count_win32.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

namespace boost
{

namespace detail
{

// Avoid #including <windows.h>

namespace win32
{
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
}

class atomic_count
{
public:

    explicit atomic_count(long v): value_(v)
    {
    }

    long operator++()
    {
        return win32::InterlockedIncrement(&value_);
    }

    long operator--()
    {
        return win32::InterlockedDecrement(&value_);
    }

    operator long() const
    {
        return value_;
    }

private:

    atomic_count(atomic_count const &);
    atomic_count & operator=(atomic_count const &);

    volatile long value_;
};

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED
