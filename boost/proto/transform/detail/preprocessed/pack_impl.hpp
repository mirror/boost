    ///////////////////////////////////////////////////////////////////////////////
    /// \file pack_impl.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        template<typename Fun, typename Cont>
        struct expand_pattern<1, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret >
        struct expand_pattern_rest_0
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void , typename B6 = void , typename B7 = void , typename B8 = void , typename B9 = void , typename B10 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret( B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4 , B5)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4 , B5 , B6)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7 , typename B8>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7 , typename B8 , typename B9>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8 , B9>
            {
                typedef msvc_fun_workaround<Ret( B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8 , B9)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<2, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0>
        struct expand_pattern_rest_1
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void , typename B6 = void , typename B7 = void , typename B8 = void , typename B9 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3 , B4)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3 , B4 , B5)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3 , B4 , B5 , B6)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7 , typename B8>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8>
            {
                typedef msvc_fun_workaround<Ret(A0 , B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7 , B8)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<3, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1>
        struct expand_pattern_rest_2
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void , typename B6 = void , typename B7 = void , typename B8 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2 , B3 , B4)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2 , B3 , B4 , B5)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2 , B3 , B4 , B5 , B6)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , B0 , B1 , B2 , B3 , B4 , B5 , B6 , B7)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<4, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2>
        struct expand_pattern_rest_3
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void , typename B6 = void , typename B7 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1 , B2 , B3 , B4)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1 , B2 , B3 , B4 , B5)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5 , B6>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , B0 , B1 , B2 , B3 , B4 , B5 , B6)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<5, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3>
        struct expand_pattern_rest_4
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void , typename B6 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0 , B1 , B2 , B3 , B4)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5>
            struct cat<B0 , B1 , B2 , B3 , B4 , B5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , B0 , B1 , B2 , B3 , B4 , B5)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<6, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct expand_pattern_rest_5
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void , typename B5 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , B0 , B1 , B2 , B3)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3 , typename B4>
            struct cat<B0 , B1 , B2 , B3 , B4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , B0 , B1 , B2 , B3 , B4)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<7, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct expand_pattern_rest_6
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void , typename B4 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , B0 , B1 , B2)> type;
            };
            template<typename B0 , typename B1 , typename B2 , typename B3>
            struct cat<B0 , B1 , B2 , B3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , B0 , B1 , B2 , B3)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<8, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct expand_pattern_rest_7
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void , typename B3 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , B0 , B1)> type;
            };
            template<typename B0 , typename B1 , typename B2>
            struct cat<B0 , B1 , B2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , B0 , B1 , B2)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<9, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 8>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct expand_pattern_rest_8
        {
            template<typename B0 = void , typename B1 = void , typename B2 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , B0)> type;
            };
            template<typename B0 , typename B1>
            struct cat<B0 , B1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , B0 , B1)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<10, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 8>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 9>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct expand_pattern_rest_9
        {
            template<typename B0 = void , typename B1 = void>
            struct cat;
            template<typename B0>
            struct cat<B0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , B0)> type;
            };
        };
