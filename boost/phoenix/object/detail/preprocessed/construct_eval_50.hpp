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
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44 , A45 const& a45
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx) , eval(a45, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44 , A45 const& a45 , A46 const& a46
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx) , eval(a45, ctx) , eval(a46, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44 , A45 const& a45 , A46 const& a46 , A47 const& a47
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx) , eval(a45, ctx) , eval(a46, ctx) , eval(a47, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44 , A45 const& a45 , A46 const& a46 , A47 const& a47 , A48 const& a48
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx) , eval(a45, ctx) , eval(a46, ctx) , eval(a47, ctx) , eval(a48, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48 , typename A49>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48 , typename A49>
        typename detail::result_of::target<A0>::type
        operator()(
            Context const& ctx
          , A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39 , A40 const& a40 , A41 const& a41 , A42 const& a42 , A43 const& a43 , A44 const& a44 , A45 const& a45 , A46 const& a46 , A47 const& a47 , A48 const& a48 , A49 const& a49
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    eval(a1, ctx) , eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx) , eval(a10, ctx) , eval(a11, ctx) , eval(a12, ctx) , eval(a13, ctx) , eval(a14, ctx) , eval(a15, ctx) , eval(a16, ctx) , eval(a17, ctx) , eval(a18, ctx) , eval(a19, ctx) , eval(a20, ctx) , eval(a21, ctx) , eval(a22, ctx) , eval(a23, ctx) , eval(a24, ctx) , eval(a25, ctx) , eval(a26, ctx) , eval(a27, ctx) , eval(a28, ctx) , eval(a29, ctx) , eval(a30, ctx) , eval(a31, ctx) , eval(a32, ctx) , eval(a33, ctx) , eval(a34, ctx) , eval(a35, ctx) , eval(a36, ctx) , eval(a37, ctx) , eval(a38, ctx) , eval(a39, ctx) , eval(a40, ctx) , eval(a41, ctx) , eval(a42, ctx) , eval(a43, ctx) , eval(a44, ctx) , eval(a45, ctx) , eval(a46, ctx) , eval(a47, ctx) , eval(a48, ctx) , eval(a49, ctx)
                );
        }
