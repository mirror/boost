/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    namespace detail
    {
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 1>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 2>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 3>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 4>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 5>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 6>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4 , A5)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e) , proto::child_c<5>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 7>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4 , A5 , A6)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e) , proto::child_c<5>(e) , proto::child_c<6>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 8>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e) , proto::child_c<5>(e) , proto::child_c<6>(e) , proto::child_c<7>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 9>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e) , proto::child_c<5>(e) , proto::child_c<6>(e) , proto::child_c<7>(e) , proto::child_c<8>(e));
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 10>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9;
            typedef
                typename boost::result_of<
                    Fun(context_type, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(boost::phoenix::context(s, d)
                    , proto::child_c<0>(e) , proto::child_c<1>(e) , proto::child_c<2>(e) , proto::child_c<3>(e) , proto::child_c<4>(e) , proto::child_c<5>(e) , proto::child_c<6>(e) , proto::child_c<7>(e) , proto::child_c<8>(e) , proto::child_c<9>(e));
            }
        };
    }
