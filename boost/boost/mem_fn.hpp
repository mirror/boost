#ifndef BOOST_MEM_FN_HPP_INCLUDED
#define BOOST_MEM_FN_HPP_INCLUDED

#if _MSC_VER+0 >= 1020
#pragma once
#endif

//
//  mem_fn.hpp - a generalization of std::mem_fun[_ref]
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2001 David Abrahams
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

#include <boost/config.hpp>

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

template <class R>
struct mf
{
    
// mf0_

    template<class T, class F = R (T::*) ()> class mf0_
    {
     public:

        typedef R result_type;
        typedef T * first_argument_type;

     private:
    
        F f_;

     public:
    
        explicit mf0_(F f): f_(f) {}

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

// cmf0_

    template<class T, class F = R (T::*) () const> class cmf0_
    {
     public:

        typedef R result_type;
        typedef T const * first_argument_type;

     private:
    
        F f_;

     public:
    
        explicit cmf0_(F f): f_(f) {}

        template<class U> R operator()(U const & u) const
        {
            return (get_pointer(u)->*f_)();
        }

        R operator()(T const & t) const
        {
            return (t.*f_)();
        }
    };

// mf1_

    template<class T, class A1, class F = R (T::*) (A1)> class mf1_
    {
     public:

        typedef R result_type;
        typedef T * first_argument_type;
        typedef A1 second_argument_type;

     private:
    
        F f_;

     public:
    
        explicit mf1_(F f): f_(f) {}

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

// cmf1_

    template<class T, class A1, class F = R (T::*) (A1) const> class cmf1_
    {
     public:

        typedef R result_type;
        typedef T const * first_argument_type;
        typedef A1 second_argument_type;

     private:
    
        F f_;

     public:
    
        explicit cmf1_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1) const
        {
            return (get_pointer(u)->*f_)(a1);
        }

        R operator()(T const & t, A1 a1) const
        {
            return (t.*f_)(a1);
        }
    };

// mf2_

    template<class T, class A1, class A2, class F = R (T::*) (A1, A2)> class mf2_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf2_(F f): f_(f) {}

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

// cmf2_

    template<class T, class A1, class A2, class F = R (T::*) (A1, A2) const> class cmf2_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf2_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2) const
        {
            return (get_pointer(u)->*f_)(a1, a2);
        }

        R operator()(T const & t, A1 a1, A2 a2) const
        {
            return (t.*f_)(a1, a2);
        }
    };

// mf3_

    template<class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3)> class mf3_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf3_(F f): f_(f) {}

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

// cmf3_

    template<class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3) const> class cmf3_
    {
     public:

        typedef R result_type;

     private:

        F f_;

     public:

        explicit cmf3_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
        {
            return (get_pointer(u)->*f_)(a1, a2, a3);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3) const
        {
            return (t.*f_)(a1, a2, a3);
        }
    };

// mf4_

    template<class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4)> class mf4_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf4_(F f): f_(f) {}

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

// cmf4_

    template<class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4) const> class cmf4_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf4_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            return (get_pointer(u)->*f_)(a1, a2, a3, a4);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            return (t.*f_)(a1, a2, a3, a4);
        }
    };

// mf5_

    template<class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5)> class mf5_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf5_(F f): f_(f) {}

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

// cmf5_

    template<class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5) const> class cmf5_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf5_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            return (t.*f_)(a1, a2, a3, a4, a5);
        }
    };

// mf6_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6)> class mf6_
    {
     public:

        typedef R result_type;

     private:

        F f_;

     public:

        explicit mf6_(F f): f_(f) {}

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

// cmf6_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6) const> class cmf6_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf6_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            return (t.*f_)(a1, a2, a3, a4, a5, a6);
        }
    };

// mf7_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7)> class mf7_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf7_(F f): f_(f) {}

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

// cmf7_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7) const> class cmf7_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf7_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            return (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            return (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
        }
    };

// mf8_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8)> class mf8_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf8_(F f): f_(f) {}

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

// cmf8_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const> class cmf8_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf8_(F f): f_(f) {}

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

};

template <>
struct mf<void>
{
    typedef void R;
    
// mf0_

    template<class T, class F = R (T::*) ()> class mf0_
    {
     public:

        typedef R result_type;
        typedef T * first_argument_type;

     private:
    
        F f_;

     public:
    
        explicit mf0_(F f): f_(f) {}

        R operator()(T * p) const
        {
            (p->*f_)();
        }

        template<class U> R operator()(U & u) const
        {
            (get_pointer(u)->*f_)();
        }

        R operator()(T & t) const
        {
            (t.*f_)();
        }
    };

// cmf0_

    template<class T, class F = R (T::*) () const> class cmf0_
    {
     public:

        typedef R result_type;
        typedef T const * first_argument_type;

     private:
    
        F f_;

     public:
    
        explicit cmf0_(F f): f_(f) {}

        template<class U> R operator()(U const & u) const
        {
            (get_pointer(u)->*f_)();
        }

        R operator()(T const & t) const
        {
            (t.*f_)();
        }
    };

// mf1_

    template<class T, class A1, class F = R (T::*) (A1)> class mf1_
    {
     public:

        typedef R result_type;
        typedef T * first_argument_type;
        typedef A1 second_argument_type;

     private:
    
        F f_;

     public:
    
        explicit mf1_(F f): f_(f) {}

        R operator()(T * p, A1 a1) const
        {
            (p->*f_)(a1);
        }

        template<class U> R operator()(U & u, A1 a1) const
        {
            (get_pointer(u)->*f_)(a1);
        }

        R operator()(T & t, A1 a1) const
        {
            (t.*f_)(a1);
        }
    };

// cmf1_

    template<class T, class A1, class F = R (T::*) (A1) const> class cmf1_
    {
     public:

        typedef R result_type;
        typedef T const * first_argument_type;
        typedef A1 second_argument_type;

     private:
    
        F f_;

     public:
    
        explicit cmf1_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1) const
        {
            (get_pointer(u)->*f_)(a1);
        }

        R operator()(T const & t, A1 a1) const
        {
            (t.*f_)(a1);
        }
    };

// mf2_

    template<class T, class A1, class A2, class F = R (T::*) (A1, A2)> class mf2_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf2_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2) const
        {
            (p->*f_)(a1, a2);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2) const
        {
            (get_pointer(u)->*f_)(a1, a2);
        }

        R operator()(T & t, A1 a1, A2 a2) const
        {
            (t.*f_)(a1, a2);
        }
    };

// cmf2_

    template<class T, class A1, class A2, class F = R (T::*) (A1, A2) const> class cmf2_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf2_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2) const
        {
            (get_pointer(u)->*f_)(a1, a2);
        }

        R operator()(T const & t, A1 a1, A2 a2) const
        {
            (t.*f_)(a1, a2);
        }
    };

// mf3_

    template<class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3)> class mf3_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf3_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3) const
        {
            (p->*f_)(a1, a2, a3);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3) const
        {
            (t.*f_)(a1, a2, a3);
        }
    };

// cmf3_

    template<class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3) const> class cmf3_
    {
     public:

        typedef R result_type;

     private:

        F f_;

     public:

        explicit cmf3_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3) const
        {
            (t.*f_)(a1, a2, a3);
        }
    };

// mf4_

    template<class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4)> class mf4_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf4_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            (p->*f_)(a1, a2, a3, a4);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            (t.*f_)(a1, a2, a3, a4);
        }
    };

// cmf4_

    template<class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4) const> class cmf4_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf4_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4) const
        {
            (t.*f_)(a1, a2, a3, a4);
        }
    };

// mf5_

    template<class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5)> class mf5_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf5_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            (p->*f_)(a1, a2, a3, a4, a5);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            (t.*f_)(a1, a2, a3, a4, a5);
        }
    };

// cmf5_

    template<class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5) const> class cmf5_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf5_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        {
            (t.*f_)(a1, a2, a3, a4, a5);
        }
    };

// mf6_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6)> class mf6_
    {
     public:

        typedef R result_type;

     private:

        F f_;

     public:

        explicit mf6_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            (p->*f_)(a1, a2, a3, a4, a5, a6);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6);
        }
    };

// cmf6_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6) const> class cmf6_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf6_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6);
        }
    };

// mf7_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7)> class mf7_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf7_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            (p->*f_)(a1, a2, a3, a4, a5, a6, a7);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
        }
    };

// cmf7_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7) const> class cmf7_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf7_(F f): f_(f) {}

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
        }
    };

// mf8_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8)> class mf8_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit mf8_(F f): f_(f) {}

        R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }

        template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }

        R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }
    };

// cmf8_

    template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const> class cmf8_
    {
     public:

        typedef R result_type;

     private:
    
        F f_;

     public:
    
        explicit cmf8_(F f): f_(f) {}

        R operator()(T const * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }

        template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (get_pointer(u)->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }

        R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        {
            (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
        }
    };
};

template<class R, class T, class F = R (T::*) ()>
class mf0: public mf<R>::template mf0_<T, F>
{
    typedef typename mf<R>::template mf0_<T, F> mf0_;
 public:
    explicit mf0(F f): mf0_(f) {}
};

template<class R, class T, class F = R (T::*) () const>
class cmf0: public mf<R>::template cmf0_<T, F>
{
    typedef typename mf<R>::template cmf0_<T, F> cmf0_;
 public:
    explicit cmf0(F f): cmf0_(f) {}
};

template<class R, class T, class A1, class F = R (T::*) (A1)>
class mf1: public mf<R>::template mf1_<T, A1, F>
{
    typedef typename mf<R>::template mf1_<T, A1, F> mf1_;
 public:
    explicit mf1(F f): mf1_(f) {}
};

template<class R, class T, class A1, class F = R (T::*) (A1) const>
class cmf1: public mf<R>::template cmf1_<T, A1, F>
{
    typedef typename mf<R>::template cmf1_<T, A1, F> cmf1_;
 public:
    explicit cmf1(F f): cmf1_(f) {}
};

template<class R, class T, class A1, class A2, class F = R (T::*) (A1, A2)>
class mf2: public mf<R>::template mf2_<T, A1, A2, F>
{
    typedef typename mf<R>::template mf2_<T, A1, A2, F> mf2_;
 public:
    explicit mf2(F f): mf2_(f) {}
};

template<class R, class T, class A1, class A2, class F = R (T::*) (A1, A2) const>
class cmf2: public mf<R>::template cmf2_<T, A1, A2, F>
{
    typedef typename mf<R>::template cmf2_<T, A1, A2, F> cmf2_;
 public:
    explicit cmf2(F f): cmf2_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3)>
class mf3: public mf<R>::template mf3_<T, A1, A2, A3, F>
{
    typedef typename mf<R>::template mf3_<T, A1, A2, A3, F> mf3_;
 public:
    explicit mf3(F f): mf3_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class F = R (T::*) (A1, A2, A3) const>
class cmf3: public mf<R>::template cmf3_<T, A1, A2, A3, F>
{
    typedef typename mf<R>::template cmf3_<T, A1, A2, A3, F> cmf3_;
 public:
    explicit cmf3(F f): cmf3_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4)>
class mf4: public mf<R>::template mf4_<T, A1, A2, A3, A4, F>
{
    typedef typename mf<R>::template mf4_<T, A1, A2, A3, A4, F> mf4_;
 public:
    explicit mf4(F f): mf4_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class F = R (T::*) (A1, A2, A3, A4) const>
class cmf4: public mf<R>::template cmf4_<T, A1, A2, A3, A4, F>
{
    typedef typename mf<R>::template cmf4_<T, A1, A2, A3, A4, F> cmf4_;
 public:
    explicit cmf4(F f): cmf4_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5)>
class mf5: public mf<R>::template mf5_<T, A1, A2, A3, A4, A5, F>
{
    typedef typename mf<R>::template mf5_<T, A1, A2, A3, A4, A5, F> mf5_;
 public:
    explicit mf5(F f): mf5_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class F = R (T::*) (A1, A2, A3, A4, A5) const>
class cmf5: public mf<R>::template cmf5_<T, A1, A2, A3, A4, A5, F>
{
    typedef typename mf<R>::template cmf5_<T, A1, A2, A3, A4, A5, F> cmf5_;
 public:
    explicit cmf5(F f): cmf5_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6)>
class mf6: public mf<R>::template mf6_<T, A1, A2, A3, A4, A5, A6, F>
{
    typedef typename mf<R>::template mf6_<T, A1, A2, A3, A4, A5, A6, F> mf6_;
 public:
    explicit mf6(F f): mf6_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class F = R (T::*) (A1, A2, A3, A4, A5, A6) const>
class cmf6: public mf<R>::template cmf6_<T, A1, A2, A3, A4, A5, A6, F>
{
    typedef typename mf<R>::template cmf6_<T, A1, A2, A3, A4, A5, A6, F> cmf6_;
 public:
    explicit cmf6(F f): cmf6_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7)>
class mf7: public mf<R>::template mf7_<T, A1, A2, A3, A4, A5, A6, A7, F>
{
    typedef typename mf<R>::template mf7_<T, A1, A2, A3, A4, A5, A6, A7, F> mf7_;
 public:
    explicit mf7(F f): mf7_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7) const>
class cmf7: public mf<R>::template cmf7_<T, A1, A2, A3, A4, A5, A6, A7, F>
{
    typedef typename mf<R>::template cmf7_<T, A1, A2, A3, A4, A5, A6, A7, F> cmf7_;
 public:
    explicit cmf7(F f): cmf7_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8)>
class mf8: public mf<R>::template mf8_<T, A1, A2, A3, A4, A5, A6, A7, A8, F>
{
    typedef typename mf<R>::template mf8_<T, A1, A2, A3, A4, A5, A6, A7, A8, F> mf8_;
 public:
    explicit mf8(F f): mf8_(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class F = R (T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const>
class cmf8: public mf<R>::template cmf8_<T, A1, A2, A3, A4, A5, A6, A7, A8, F>
{
    typedef typename mf<R>::template cmf8_<T, A1, A2, A3, A4, A5, A6, A7, A8, F> cmf8_;
 public:
    explicit cmf8(F f): cmf8_(f) {}
};

} // namespace _mfi

// mem_fn

#if (defined(_WIN32) || defined(__WIN32__)) && defined(__MWERKS__)
# define BOOST_MEM_FN_ENABLE_STDCALL
#endif

#if defined(BOOST_MEM_FN_ENABLE_STDCALL) || (defined(BOOST_MSVC) && BOOST_MSVC <= 1300)

#if defined(BOOST_MEM_FN_ENABLE_STDCALL)
#define BOOST_MEM_FN_CC __stdcall
#include <boost/bind/mem_fn_cc.hpp>
#undef BOOST_MEM_FN_CC
#endif

#define BOOST_MEM_FN_CC
#include <boost/bind/mem_fn_cc.hpp>
#undef BOOST_MEM_FN_CC

#else

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

#endif // !defined(BOOST_MEM_FN_ENABLE_STDCALL)

} // namespace boost

#endif // #ifndef BOOST_MEM_FN_HPP_INCLUDED
