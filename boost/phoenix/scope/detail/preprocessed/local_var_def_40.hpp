/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
        template <typename Tag0, typename A0, typename Context>
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0>
            >
          , Context
        >
            : evaluator::impl<A0 const &, Context, int>::result_type
        {};
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1
          , typename A0 , typename A1
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A1 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2
          , typename A0 , typename A1 , typename A2
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A2 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3
          , typename A0 , typename A1 , typename A2 , typename A3
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A3 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A4 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A5 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A6 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A7 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A8 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A9 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A10 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A11 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A12 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A13 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A14 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A15 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A16 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A17 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A18 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A19 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A20 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A21 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A22 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A23 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A24 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A25 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A26 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A27 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A28 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A29 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A30 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A31 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A32 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A33 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A34 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A35 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A36 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A37 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A38 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                    >
                  , Context
                >
            >
        {};
            
    
    
    
    
    
    
    
        template <
            typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38 , typename Tag39
          , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    A39 const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                    >
                  , Context
                >
            >
        {};
            
        struct local_var_def_eval
        {
            template <typename Sig>
            struct result;
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0
              , typename A0
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0
              , typename A0
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0
              , typename A0
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1
              , typename A0 , typename A1
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1
              , typename A0 , typename A1
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1
              , typename A0 , typename A1
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2
              , typename A0 , typename A1 , typename A2
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2
              , typename A0 , typename A1 , typename A2
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2
              , typename A0 , typename A1 , typename A2
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3
              , typename A0 , typename A1 , typename A2 , typename A3
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3
              , typename A0 , typename A1 , typename A2 , typename A3
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3
              , typename A0 , typename A1 , typename A2 , typename A3
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34; typedef fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > pair35;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) ) , pair35( boost::phoenix::eval(fusion::at_key<Tag35>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34; typedef fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > pair35; typedef fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > pair36;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) ) , pair35( boost::phoenix::eval(fusion::at_key<Tag35>(locals), ctx) ) , pair36( boost::phoenix::eval(fusion::at_key<Tag36>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34; typedef fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > pair35; typedef fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > pair36; typedef fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > pair37;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) ) , pair35( boost::phoenix::eval(fusion::at_key<Tag35>(locals), ctx) ) , pair36( boost::phoenix::eval(fusion::at_key<Tag36>(locals), ctx) ) , pair37( boost::phoenix::eval(fusion::at_key<Tag37>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > , fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > , fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34; typedef fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > pair35; typedef fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > pair36; typedef fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > pair37; typedef fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type > pair38;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) ) , pair35( boost::phoenix::eval(fusion::at_key<Tag35>(locals), ctx) ) , pair36( boost::phoenix::eval(fusion::at_key<Tag36>(locals), ctx) ) , pair37( boost::phoenix::eval(fusion::at_key<Tag37>(locals), ctx) ) , pair38( boost::phoenix::eval(fusion::at_key<Tag38>(locals), ctx) )
                    );
            }
    
    
    
    
    
    
    
            
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38 , typename Tag39
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > , fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type > , fusion::pair< Tag39 , typename evaluator::impl< A39 const & , Context , int >::result_type >
                    >
                    type;
            };
            template <
                typename This
              , typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38 , typename Tag39
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > , fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > , fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > , fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > , fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > , fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > , fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > , fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > , fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > , fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > , fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > , fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > , fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > , fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > , fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > , fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > , fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > , fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > , fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > , fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > , fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > , fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > , fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > , fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > , fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > , fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > , fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > , fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > , fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > , fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > , fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > , fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > , fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > , fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > , fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > , fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > , fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > , fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > , fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type > , fusion::pair< Tag39 , typename evaluator::impl< A39 const & , Context , int >::result_type >
                    >
                    type;
            };
            
            template <
                typename Tag0 , typename Tag1 , typename Tag2 , typename Tag3 , typename Tag4 , typename Tag5 , typename Tag6 , typename Tag7 , typename Tag8 , typename Tag9 , typename Tag10 , typename Tag11 , typename Tag12 , typename Tag13 , typename Tag14 , typename Tag15 , typename Tag16 , typename Tag17 , typename Tag18 , typename Tag19 , typename Tag20 , typename Tag21 , typename Tag22 , typename Tag23 , typename Tag24 , typename Tag25 , typename Tag26 , typename Tag27 , typename Tag28 , typename Tag29 , typename Tag30 , typename Tag31 , typename Tag32 , typename Tag33 , typename Tag34 , typename Tag35 , typename Tag36 , typename Tag37 , typename Tag38 , typename Tag39
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
                > const & locals
              , Context const & ctx
            ) const
            {
                typedef fusion::pair< Tag0 , typename evaluator::impl< A0 const & , Context , int >::result_type > pair0; typedef fusion::pair< Tag1 , typename evaluator::impl< A1 const & , Context , int >::result_type > pair1; typedef fusion::pair< Tag2 , typename evaluator::impl< A2 const & , Context , int >::result_type > pair2; typedef fusion::pair< Tag3 , typename evaluator::impl< A3 const & , Context , int >::result_type > pair3; typedef fusion::pair< Tag4 , typename evaluator::impl< A4 const & , Context , int >::result_type > pair4; typedef fusion::pair< Tag5 , typename evaluator::impl< A5 const & , Context , int >::result_type > pair5; typedef fusion::pair< Tag6 , typename evaluator::impl< A6 const & , Context , int >::result_type > pair6; typedef fusion::pair< Tag7 , typename evaluator::impl< A7 const & , Context , int >::result_type > pair7; typedef fusion::pair< Tag8 , typename evaluator::impl< A8 const & , Context , int >::result_type > pair8; typedef fusion::pair< Tag9 , typename evaluator::impl< A9 const & , Context , int >::result_type > pair9; typedef fusion::pair< Tag10 , typename evaluator::impl< A10 const & , Context , int >::result_type > pair10; typedef fusion::pair< Tag11 , typename evaluator::impl< A11 const & , Context , int >::result_type > pair11; typedef fusion::pair< Tag12 , typename evaluator::impl< A12 const & , Context , int >::result_type > pair12; typedef fusion::pair< Tag13 , typename evaluator::impl< A13 const & , Context , int >::result_type > pair13; typedef fusion::pair< Tag14 , typename evaluator::impl< A14 const & , Context , int >::result_type > pair14; typedef fusion::pair< Tag15 , typename evaluator::impl< A15 const & , Context , int >::result_type > pair15; typedef fusion::pair< Tag16 , typename evaluator::impl< A16 const & , Context , int >::result_type > pair16; typedef fusion::pair< Tag17 , typename evaluator::impl< A17 const & , Context , int >::result_type > pair17; typedef fusion::pair< Tag18 , typename evaluator::impl< A18 const & , Context , int >::result_type > pair18; typedef fusion::pair< Tag19 , typename evaluator::impl< A19 const & , Context , int >::result_type > pair19; typedef fusion::pair< Tag20 , typename evaluator::impl< A20 const & , Context , int >::result_type > pair20; typedef fusion::pair< Tag21 , typename evaluator::impl< A21 const & , Context , int >::result_type > pair21; typedef fusion::pair< Tag22 , typename evaluator::impl< A22 const & , Context , int >::result_type > pair22; typedef fusion::pair< Tag23 , typename evaluator::impl< A23 const & , Context , int >::result_type > pair23; typedef fusion::pair< Tag24 , typename evaluator::impl< A24 const & , Context , int >::result_type > pair24; typedef fusion::pair< Tag25 , typename evaluator::impl< A25 const & , Context , int >::result_type > pair25; typedef fusion::pair< Tag26 , typename evaluator::impl< A26 const & , Context , int >::result_type > pair26; typedef fusion::pair< Tag27 , typename evaluator::impl< A27 const & , Context , int >::result_type > pair27; typedef fusion::pair< Tag28 , typename evaluator::impl< A28 const & , Context , int >::result_type > pair28; typedef fusion::pair< Tag29 , typename evaluator::impl< A29 const & , Context , int >::result_type > pair29; typedef fusion::pair< Tag30 , typename evaluator::impl< A30 const & , Context , int >::result_type > pair30; typedef fusion::pair< Tag31 , typename evaluator::impl< A31 const & , Context , int >::result_type > pair31; typedef fusion::pair< Tag32 , typename evaluator::impl< A32 const & , Context , int >::result_type > pair32; typedef fusion::pair< Tag33 , typename evaluator::impl< A33 const & , Context , int >::result_type > pair33; typedef fusion::pair< Tag34 , typename evaluator::impl< A34 const & , Context , int >::result_type > pair34; typedef fusion::pair< Tag35 , typename evaluator::impl< A35 const & , Context , int >::result_type > pair35; typedef fusion::pair< Tag36 , typename evaluator::impl< A36 const & , Context , int >::result_type > pair36; typedef fusion::pair< Tag37 , typename evaluator::impl< A37 const & , Context , int >::result_type > pair37; typedef fusion::pair< Tag38 , typename evaluator::impl< A38 const & , Context , int >::result_type > pair38; typedef fusion::pair< Tag39 , typename evaluator::impl< A39 const & , Context , int >::result_type > pair39;
                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                fusion::pair<Tag0, A0> , fusion::pair<Tag1, A1> , fusion::pair<Tag2, A2> , fusion::pair<Tag3, A3> , fusion::pair<Tag4, A4> , fusion::pair<Tag5, A5> , fusion::pair<Tag6, A6> , fusion::pair<Tag7, A7> , fusion::pair<Tag8, A8> , fusion::pair<Tag9, A9> , fusion::pair<Tag10, A10> , fusion::pair<Tag11, A11> , fusion::pair<Tag12, A12> , fusion::pair<Tag13, A13> , fusion::pair<Tag14, A14> , fusion::pair<Tag15, A15> , fusion::pair<Tag16, A16> , fusion::pair<Tag17, A17> , fusion::pair<Tag18, A18> , fusion::pair<Tag19, A19> , fusion::pair<Tag20, A20> , fusion::pair<Tag21, A21> , fusion::pair<Tag22, A22> , fusion::pair<Tag23, A23> , fusion::pair<Tag24, A24> , fusion::pair<Tag25, A25> , fusion::pair<Tag26, A26> , fusion::pair<Tag27, A27> , fusion::pair<Tag28, A28> , fusion::pair<Tag29, A29> , fusion::pair<Tag30, A30> , fusion::pair<Tag31, A31> , fusion::pair<Tag32, A32> , fusion::pair<Tag33, A33> , fusion::pair<Tag34, A34> , fusion::pair<Tag35, A35> , fusion::pair<Tag36, A36> , fusion::pair<Tag37, A37> , fusion::pair<Tag38, A38> , fusion::pair<Tag39, A39>
                            > const&
                          , Context const&
                        )
                    >::type(
                        pair0( boost::phoenix::eval(fusion::at_key<Tag0>(locals), ctx) ) , pair1( boost::phoenix::eval(fusion::at_key<Tag1>(locals), ctx) ) , pair2( boost::phoenix::eval(fusion::at_key<Tag2>(locals), ctx) ) , pair3( boost::phoenix::eval(fusion::at_key<Tag3>(locals), ctx) ) , pair4( boost::phoenix::eval(fusion::at_key<Tag4>(locals), ctx) ) , pair5( boost::phoenix::eval(fusion::at_key<Tag5>(locals), ctx) ) , pair6( boost::phoenix::eval(fusion::at_key<Tag6>(locals), ctx) ) , pair7( boost::phoenix::eval(fusion::at_key<Tag7>(locals), ctx) ) , pair8( boost::phoenix::eval(fusion::at_key<Tag8>(locals), ctx) ) , pair9( boost::phoenix::eval(fusion::at_key<Tag9>(locals), ctx) ) , pair10( boost::phoenix::eval(fusion::at_key<Tag10>(locals), ctx) ) , pair11( boost::phoenix::eval(fusion::at_key<Tag11>(locals), ctx) ) , pair12( boost::phoenix::eval(fusion::at_key<Tag12>(locals), ctx) ) , pair13( boost::phoenix::eval(fusion::at_key<Tag13>(locals), ctx) ) , pair14( boost::phoenix::eval(fusion::at_key<Tag14>(locals), ctx) ) , pair15( boost::phoenix::eval(fusion::at_key<Tag15>(locals), ctx) ) , pair16( boost::phoenix::eval(fusion::at_key<Tag16>(locals), ctx) ) , pair17( boost::phoenix::eval(fusion::at_key<Tag17>(locals), ctx) ) , pair18( boost::phoenix::eval(fusion::at_key<Tag18>(locals), ctx) ) , pair19( boost::phoenix::eval(fusion::at_key<Tag19>(locals), ctx) ) , pair20( boost::phoenix::eval(fusion::at_key<Tag20>(locals), ctx) ) , pair21( boost::phoenix::eval(fusion::at_key<Tag21>(locals), ctx) ) , pair22( boost::phoenix::eval(fusion::at_key<Tag22>(locals), ctx) ) , pair23( boost::phoenix::eval(fusion::at_key<Tag23>(locals), ctx) ) , pair24( boost::phoenix::eval(fusion::at_key<Tag24>(locals), ctx) ) , pair25( boost::phoenix::eval(fusion::at_key<Tag25>(locals), ctx) ) , pair26( boost::phoenix::eval(fusion::at_key<Tag26>(locals), ctx) ) , pair27( boost::phoenix::eval(fusion::at_key<Tag27>(locals), ctx) ) , pair28( boost::phoenix::eval(fusion::at_key<Tag28>(locals), ctx) ) , pair29( boost::phoenix::eval(fusion::at_key<Tag29>(locals), ctx) ) , pair30( boost::phoenix::eval(fusion::at_key<Tag30>(locals), ctx) ) , pair31( boost::phoenix::eval(fusion::at_key<Tag31>(locals), ctx) ) , pair32( boost::phoenix::eval(fusion::at_key<Tag32>(locals), ctx) ) , pair33( boost::phoenix::eval(fusion::at_key<Tag33>(locals), ctx) ) , pair34( boost::phoenix::eval(fusion::at_key<Tag34>(locals), ctx) ) , pair35( boost::phoenix::eval(fusion::at_key<Tag35>(locals), ctx) ) , pair36( boost::phoenix::eval(fusion::at_key<Tag36>(locals), ctx) ) , pair37( boost::phoenix::eval(fusion::at_key<Tag37>(locals), ctx) ) , pair38( boost::phoenix::eval(fusion::at_key<Tag38>(locals), ctx) ) , pair39( boost::phoenix::eval(fusion::at_key<Tag39>(locals), ctx) )
                    );
            }
        };
