#ifndef BOOST_MEM_FN_CC
#error Do not include <boost/bind/mem_fn_cc.hpp> directly.
#endif

//
//  bind/mem_fn_cc.hpp - support for different calling conventions
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

template<class R, class T> _mfi::mf0<R, T, R (BOOST_MEM_FN_CC T::*) ()> mem_fn(R (BOOST_MEM_FN_CC T::*f) ())
{
    return _mfi::mf0<R, T, R (BOOST_MEM_FN_CC T::*) ()>(f);
}

template<class R, class T> _mfi::cmf0<R, T, R (BOOST_MEM_FN_CC T::*) () const> mem_fn(R (BOOST_MEM_FN_CC T::*f) () const)
{
    return _mfi::cmf0<R, T, R (BOOST_MEM_FN_CC T::*) () const>(f);
}

template<class R, class T, class A1> _mfi::mf1<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1))
{
    return _mfi::mf1<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1)>(f);
}

template<class R, class T, class A1> _mfi::cmf1<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1) const)
{
    return _mfi::cmf1<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1) const>(f);
}

template<class R, class T, class A1, class A2> _mfi::mf2<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2))
{
    return _mfi::mf2<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2)>(f);
}

template<class R, class T, class A1, class A2> _mfi::cmf2<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2) const)
{
    return _mfi::cmf2<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2) const>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::mf3<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3))
{
    return _mfi::mf3<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3)>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::cmf3<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3) const)
{
    return _mfi::cmf3<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3) const>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::mf4<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4))
{
    return _mfi::mf4<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4)>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::cmf4<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4) const)
{
    return _mfi::cmf4<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4) const>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::mf5<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5))
{
    return _mfi::mf5<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5)>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::cmf5<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5) const)
{
    return _mfi::cmf5<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5) const>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::mf6<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6))
{
    return _mfi::mf6<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6)>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::cmf6<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6) const)
{
    return _mfi::cmf6<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6) const>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::mf7<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7))
{
    return _mfi::mf7<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7)>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::cmf7<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7) const)
{
    return _mfi::cmf7<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7) const>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::mf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8)> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8))
{
    return _mfi::mf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8)>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::cmf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) const)
{
    return _mfi::cmf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const>(f);
}
