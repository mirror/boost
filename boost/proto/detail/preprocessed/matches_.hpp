    ///////////////////////////////////////////////////////////////////////////////
    /// \file matches_.hpp
    /// Definitions of matches_ specializations
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1> >
          : or_2<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1> >
          : detail::and_2<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 2>, proto::basic_expr<Tag, Args2, 2> >
          : and_2<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 2>, proto::basic_expr<proto::_, Args2, 2> >
          : and_2<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2> >
          : or_3<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2> >
          : detail::and_3<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 3>, proto::basic_expr<Tag, Args2, 3> >
          : and_3<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 3>, proto::basic_expr<proto::_, Args2, 3> >
          : and_3<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3> >
          : or_4<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3> >
          : detail::and_4<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 4>, proto::basic_expr<Tag, Args2, 4> >
          : and_4<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 4>, proto::basic_expr<proto::_, Args2, 4> >
          : and_4<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4> >
          : or_5<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4> >
          : detail::and_5<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 5>, proto::basic_expr<Tag, Args2, 5> >
          : and_5<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 5>, proto::basic_expr<proto::_, Args2, 5> >
          : and_5<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5> >
          : or_6<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5> >
          : detail::and_6<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6> >
          : or_7<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6> >
          : detail::and_7<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7> >
          : or_8<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7> >
          : detail::and_8<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar > , matches_< Expr , BasicExpr , typename G7::proto_grammar >
            >
        {};
