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
        };
