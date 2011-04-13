/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
namespace boost { namespace phoenix
{
    namespace tag
    {
        struct mem_fun_ptr;
    }
    namespace detail {
        namespace result_of
        {
            template <typename Object, typename MemPtr,
                typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void
                , typename Dummy = void>
            struct mem_fun_ptr_gen;
            template <typename Object, typename MemPtr>
            struct mem_fun_ptr_gen<Object, MemPtr>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0>
            struct mem_fun_ptr_gen<Object, MemPtr, A0>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
            {};
    
    
    
    
    
    
    
            template <typename Object, typename MemPtr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            struct mem_fun_ptr_gen<Object, MemPtr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
                : proto::result_of::make_expr<
                      tag::mem_fun_ptr
                    , phoenix_domain
                    , Object
                    , MemPtr
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
            {};
        }
        template <typename Object, typename MemPtr>
        struct mem_fun_ptr_gen
        {
            mem_fun_ptr_gen(Object const& obj, MemPtr ptr)
              : obj(obj)
              , ptr(ptr)
            {}
            typename result_of::mem_fun_ptr_gen<Object, MemPtr>::type const
            operator()() const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr);
            }
    
    
    
    
    
    
    
            template <typename A0>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0
            >::type const
            operator()(A0 const& a0) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0);
            }
            template <typename A0>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0
            >::type const
            operator()(A0 & a0) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1
            >::type const
            operator()(A0 const& a0 , A1 const& a1) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1);
            }
            template <typename A0 , typename A1>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1
            >::type const
            operator()(A0 & a0 , A1 & a1) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2);
            }
            template <typename A0 , typename A1 , typename A2>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
            }
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            typename result_of::mem_fun_ptr_gen<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
            >::type const
            operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18) const
            {
                return proto::make_expr<
                    tag::mem_fun_ptr, phoenix_domain>(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
            }
            Object const& obj;
            MemPtr ptr;
        };
    }
}}
