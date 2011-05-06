    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename This , typename A0 , typename A1>
    struct result<This(A0 , A1)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1>
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1
    >::type const
    operator ()(const A0 &a0 , const A1 &a1) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1
        >()(a0 , a1);
    }
    template<typename This , typename A0 , typename A1 , typename A2>
    struct result<This(A0 , A1 , A2)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2>
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2
        >()(a0 , a1 , a2);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3>
    struct result<This(A0 , A1 , A2 , A3)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3>
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3
        >()(a0 , a1 , a2 , a3);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct result<This(A0 , A1 , A2 , A3 , A4)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4
        >()(a0 , a1 , a2 , a3 , a4);
    }
