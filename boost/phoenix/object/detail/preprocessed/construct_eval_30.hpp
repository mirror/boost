/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1>
        struct result<This(Context, A0 , A1)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2>
        struct result<This(Context, A0 , A1 , A2)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(Context, A0 , A1 , A2 , A3)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx)
                );
        }
