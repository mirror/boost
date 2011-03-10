/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
namespace boost { namespace phoenix
{
    
    
    
    
    template <typename F>
    inline
    typename expression::function<F>::type
    bind(F f)
    {
        return function<F>(f)();
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0>
    inline
    typename expression::function<F, A0>::type const
    bind(F f, A0 const& a0)
    {
        return function<F>(f)(a0);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1>
    inline
    typename expression::function<F, A0 , A1>::type const
    bind(F f, A0 const& a0 , A1 const& a1)
    {
        return function<F>(f)(a0 , a1);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2>
    inline
    typename expression::function<F, A0 , A1 , A2>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return function<F>(f)(a0 , a1 , a2);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return function<F>(f)(a0 , a1 , a2 , a3);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4 , A5>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4 , a5);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    inline
    typename expression::function<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9)
    {
        return function<F>(f)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }
}}
