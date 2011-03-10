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
                typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void
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
            Object const& obj;
            MemPtr ptr;
        };
    }
}}
