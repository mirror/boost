#ifndef BOOST_MEM_FN_HPP_INCLUDED
#define BOOST_MEM_FN_HPP_INCLUDED

#if _MSC_VER >= 1020
#pragma once
#endif

//
//  mem_fn.hpp - a generalization of std::mem_fun[_ref]
//
//  Version 1.02.0001 (2001-08-30)
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

namespace boost
{

// get_pointer(p) extracts a ->* capable pointer from p

template<class T> T * get_pointer(T * p)
{
    return p;
}

// implementation of get_pointer for boost::shared_ptr
// this will probably migrate to boost/shared_ptr.hpp

template<class T> class shared_ptr;

template<class T> T * get_pointer(shared_ptr<T> const & p)
{
    return p.get();
}

//

namespace _mfi // mem_fun_impl
{

// mf0

template<class R, class T> class mf0
{
public:

    typedef R result_type;
    typedef T * first_argument_type;

private:
    
    typedef R (T::*F) ();
    F f_;

public:
    
    explicit mf0(F f): f_(f) {}

    R operator()(T * p) const
    {
        return (p->*f_)();
    }

    template<class U> R operator()(U & u) const
    {
        return (get_pointer(u)->*f_)();
    }

    R operator()(T & t) const
    {
        return (t.*f_)();
    }
};

// cmf0

template<class R, class T> class cmf0
{
public:

    typedef R result_type;
    typedef T const * first_argument_type;

private:
    
    typedef R (T::*F) () const;
    F f_;

public:
    
    explicit cmf0(F f): f_(f) {}

    template<class U> R operator()(U const & u) const
    {
        return (get_pointer(u)->*f_)();
    }

    R operator()(T const & t) const
    {
        return (t.*f_)();
    }
};

// mf1

template<class R, class T, class A1> class mf1
{
public:

    typedef R result_type;
    typedef T * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    typedef R (T::*F) (A1);
    F f_;

public:
    
    explicit mf1(F f): f_(f) {}

    R operator()(T * p, A1 a1) const
    {
        return (p->*f_)(a1);
    }

    template<class U> R operator()(U & u, A1 a1) const
    {
        return (get_pointer(u)->*f_)(a1);
    }

    R operator()(T & t, A1 a1) const
    {
        return (t.*f_)(a1);
    }
};

// cmf1

template<class R, class T, class A1> class cmf1
{
public:

    typedef R result_type;
    typedef T const * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    typedef R (T::*F) (A1) const;
    F f_;

public:
    
    explicit cmf1(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1) const
    {
        return (get_pointer(u)->*f_)(a1);
    }

    R operator()(T const & t, A1 a1) const
    {
        return (t.*f_)(a1);
    }
};

// mf2

template<class R, class T, class A1, class A2> class mf2
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2);
    F f_;

public:
    
    explicit mf2(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2) const
    {
        return (p->*f_)(a1, a2);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2) const
    {
        return (get_pointer(u)->*f_)(a1, a2);
    }

    R operator()(T & t, A1 a1, A2 a2) const
    {
        return (t.*f_)(a1, a2);
    }
};

// cmf2

template<class R, class T, class A1, class A2> class cmf2
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2) const;
    F f_;

public:
    
    explicit cmf2(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2) const
    {
        return (get_pointer(u)->*f_)(a1, a2);
    }

    R operator()(T const & t, A1 a1, A2 a2) const
    {
        return (t.*f_)(a1, a2);
    }
};

// mf3

template<class R, class T, class A1, class A2, class A3> class mf3
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3);
    F f_;

public:
    
    explicit mf3(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3) const
    {
        return (p->*f_)(a1, a2, a3);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3) const
    {
        return (t.*f_)(a1, a2, a3);
    }
};

// cmf3

template<class R, class T, class A1, class A2, class A3> class cmf3
{
public:

    typedef R result_type;

private:

    typedef R (T::*F) (A1, A2, A3) const;
    F f_;

public:

    explicit cmf3(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3) const
    {
        return (t.*f_)(a1, a2, a3);
    }
};

// mf4

template<class R, class T, class A1, class A2, class A3, class A4> class mf4
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4);
    F f_;

public:
    
    explicit mf4(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return (p->*f_)(a1, a2, a3, a4);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return (t.*f_)(a1, a2, a3, a4);
    }
};

// cmf4

template<class R, class T, class A1, class A2, class A3, class A4> class cmf4
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4) const;
    F f_;

public:
    
    explicit cmf4(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return (t.*f_)(a1, a2, a3, a4);
    }
};

// mf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5> class mf5
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5);
    F f_;

public:
    
    explicit mf5(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        return (p->*f_)(a1, a2, a3, a4, a5);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5);
    }
};

// cmf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5> class cmf5
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5) const;
    F f_;

public:
    
    explicit cmf5(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5);
    }
};

// mf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> class mf6
{
public:

    typedef R result_type;

private:

    typedef R (T::*F) (A1, A2, A3, A4, A5, A6);
    F f_;

public:

    explicit mf6(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        return (p->*f_)(a1, a2, a3, a4, a5, a6);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6);
    }
};

// cmf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> class cmf6
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5, A6) const;
    F f_;

public:
    
    explicit cmf6(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6);
    }
};

// mf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> class mf7
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5, A6, A7);
    F f_;

public:
    
    explicit mf7(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        return (p->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }
};

// cmf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> class cmf7
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5, A6, A7) const;
    F f_;

public:
    
    explicit cmf7(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }
};

// mf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> class mf8
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5, A6, A7, A8);
    F f_;

public:
    
    explicit mf8(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }
};

// cmf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> class cmf8
{
public:

    typedef R result_type;

private:
    
    typedef R (T::*F) (A1, A2, A3, A4, A5, A6, A7, A8) const;
    F f_;

public:
    
    explicit cmf8(F f): f_(f) {}

    R operator()(T const * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        return (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }
};

} // namespace _mfi

// mem_fn

template<class R, class T> _mfi::mf0<R, T> mem_fn(R (T::*f) ())
{
    return _mfi::mf0<R, T>(f);
}

template<class R, class T> _mfi::cmf0<R, T> mem_fn(R (T::*f) () const)
{
    return _mfi::cmf0<R, T>(f);
}

template<class R, class T, class A1> _mfi::mf1<R, T, A1> mem_fn(R (T::*f) (A1))
{
    return _mfi::mf1<R, T, A1>(f);
}

template<class R, class T, class A1> _mfi::cmf1<R, T, A1> mem_fn(R (T::*f) (A1) const)
{
    return _mfi::cmf1<R, T, A1>(f);
}

template<class R, class T, class A1, class A2> _mfi::mf2<R, T, A1, A2> mem_fn(R (T::*f) (A1, A2))
{
    return _mfi::mf2<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2> _mfi::cmf2<R, T, A1, A2> mem_fn(R (T::*f) (A1, A2) const)
{
    return _mfi::cmf2<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::mf3<R, T, A1, A2, A3> mem_fn(R (T::*f) (A1, A2, A3))
{
    return _mfi::mf3<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::cmf3<R, T, A1, A2, A3> mem_fn(R (T::*f) (A1, A2, A3) const)
{
    return _mfi::cmf3<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::mf4<R, T, A1, A2, A3, A4> mem_fn(R (T::*f) (A1, A2, A3, A4))
{
    return _mfi::mf4<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::cmf4<R, T, A1, A2, A3, A4> mem_fn(R (T::*f) (A1, A2, A3, A4) const)
{
    return _mfi::cmf4<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::mf5<R, T, A1, A2, A3, A4, A5> mem_fn(R (T::*f) (A1, A2, A3, A4, A5))
{
    return _mfi::mf5<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::cmf5<R, T, A1, A2, A3, A4, A5> mem_fn(R (T::*f) (A1, A2, A3, A4, A5) const)
{
    return _mfi::cmf5<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::mf6<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6))
{
    return _mfi::mf6<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::cmf6<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6) const)
{
    return _mfi::cmf6<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::mf7<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6, A7))
{
    return _mfi::mf7<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::cmf7<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6, A7) const)
{
    return _mfi::cmf7<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::mf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6, A7, A8))
{
    return _mfi::mf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::cmf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) const)
{
    return _mfi::cmf8<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

} // namespace boost

#endif // #ifndef BOOST_MEM_FN_HPP_INCLUDED
