//
//  bind/mem_fn_template.hpp
//
//  Do not include this header directly
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

// mf0

template<class R, class T> class BOOST_MEM_FN_NAME(mf0)
{
public:

    typedef R result_type;
    typedef T * argument_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) ();
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf0)(F f): f_(f) {}

    R operator()(T * p) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)();
    }

    template<class U> R operator()(U & u) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)();
    }

    R operator()(T & t) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)();
    }
};

// cmf0

template<class R, class T> class BOOST_MEM_FN_NAME(cmf0)
{
public:

    typedef R result_type;
    typedef T const * argument_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) () const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf0)(F f): f_(f) {}

    template<class U> R operator()(U const & u) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)();
    }

    R operator()(T const & t) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)();
    }
};

// mf1

template<class R, class T, class A1> class BOOST_MEM_FN_NAME(mf1)
{
public:

    typedef R result_type;
    typedef T * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf1)(F f): f_(f) {}

    R operator()(T * p, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1);
    }

    template<class U> R operator()(U & u, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1);
    }

    R operator()(T & t, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1);
    }
};

// cmf1

template<class R, class T, class A1> class BOOST_MEM_FN_NAME(cmf1)
{
public:

    typedef R result_type;
    typedef T const * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf1)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1);
    }

    R operator()(T const & t, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1);
    }
};

// mf2

template<class R, class T, class A1, class A2> class BOOST_MEM_FN_NAME(mf2)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf2)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2);
    }

    R operator()(T & t, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2);
    }
};

// cmf2

template<class R, class T, class A1, class A2> class BOOST_MEM_FN_NAME(cmf2)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf2)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2);
    }

    R operator()(T const & t, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2);
    }
};

// mf3

template<class R, class T, class A1, class A2, class A3> class BOOST_MEM_FN_NAME(mf3)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf3)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3);
    }
};

// cmf3

template<class R, class T, class A1, class A2, class A3> class BOOST_MEM_FN_NAME(cmf3)
{
public:

    typedef R result_type;

private:

    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3) const;
    F f_;

public:

    explicit BOOST_MEM_FN_NAME(cmf3)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3);
    }
};

// mf4

template<class R, class T, class A1, class A2, class A3, class A4> class BOOST_MEM_FN_NAME(mf4)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf4)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4);
    }
};

// cmf4

template<class R, class T, class A1, class A2, class A3, class A4> class BOOST_MEM_FN_NAME(cmf4)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf4)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4);
    }
};

// mf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5> class BOOST_MEM_FN_NAME(mf5)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf5)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5);
    }
};

// cmf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5> class BOOST_MEM_FN_NAME(cmf5)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf5)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5);
    }
};

// mf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> class BOOST_MEM_FN_NAME(mf6)
{
public:

    typedef R result_type;

private:

    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6);
    F f_;

public:

    explicit BOOST_MEM_FN_NAME(mf6)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6);
    }
};

// cmf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> class BOOST_MEM_FN_NAME(cmf6)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf6)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6);
    }
};

// mf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> class BOOST_MEM_FN_NAME(mf7)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf7)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }
};

// cmf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> class BOOST_MEM_FN_NAME(cmf7)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf7)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }
};

// mf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> class BOOST_MEM_FN_NAME(mf8)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8);
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(mf8)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }
};

// cmf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> class BOOST_MEM_FN_NAME(cmf8)
{
public:

    typedef R result_type;

private:
    
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8) const;
    F f_;

public:
    
    explicit BOOST_MEM_FN_NAME(cmf8)(F f): f_(f) {}

    R operator()(T const * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }
};

