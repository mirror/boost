    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr.hpp
    /// Contains overloads of make_expr() free function.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    template<typename Tag , typename A0 , typename A1>
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1
        >()(a0 , a1);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1>
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1
    >::type const
    make_expr(const C0 &c0 , const C1 &c1)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1
        >()(c0 , c1);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2>
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2
        >()(a0 , a1 , a2);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2>
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2
        >()(c0 , c1 , c2);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3>
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3
        >()(a0 , a1 , a2 , a3);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3>
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3
        >()(c0 , c1 , c2 , c3);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4
        >()(a0 , a1 , a2 , a3 , a4);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4
        >()(c0 , c1 , c2 , c3 , c4);
    }
