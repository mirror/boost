/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1>
        struct result<This(Context, A0 , A1)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1>
        typename result<new_eval(Context const &, A0 const& , A1 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const&)
                    >::construct_type(
                        eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2>
        struct result<This(Context, A0 , A1 , A2)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(Context, A0 , A1 , A2 , A3)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result<new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&)>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
        ) const
        {
            return
                new typename result<
                    new_eval(Context const &, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&)
                    >::construct_type(
                        eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx)
                );
        }
