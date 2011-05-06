    ///////////////////////////////////////////////////////////////////////////////
    /// \file lambda_matches.hpp
    /// Specializations of the lambda_matches template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<
        template<typename , typename> class T
        , typename Expr0 , typename Expr1
        , typename Grammar0 , typename Grammar1
    >
    struct lambda_matches<
        T<Expr0 , Expr1>
      , T<Grammar0 , Grammar1>
        BOOST_PROTO_LAMBDA_ARITY_PARAM(2)
    >
      : and_2<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 >
        >
    {};
    template<
        template<typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2
        , typename Grammar0 , typename Grammar1 , typename Grammar2
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2>
      , T<Grammar0 , Grammar1 , Grammar2>
        BOOST_PROTO_LAMBDA_ARITY_PARAM(3)
    >
      : and_3<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 >
        >
    {};
    template<
        template<typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3>
        BOOST_PROTO_LAMBDA_ARITY_PARAM(4)
    >
      : and_4<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4>
        BOOST_PROTO_LAMBDA_ARITY_PARAM(5)
    >
      : and_5<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 >
        >
    {};
