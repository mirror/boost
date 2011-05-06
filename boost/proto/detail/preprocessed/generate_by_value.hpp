    ///////////////////////////////////////////////////////////////////////////////
    /// \file generate_by_value.hpp
    /// Contains definition of by_value_generator_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Tag , typename Arg0 >
    struct by_value_generator_<
        proto::expr<Tag, list1<Arg0>, 1>
    >
    {
        typedef
            list1<Arg0>
        src_args;
        typedef
            list1<
                typename uncvref<Arg0 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 1> src_type;
        typedef proto::expr<Tag, dst_args, 1> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list1<Arg0>, 1>
    >
    {
        typedef
            list1<Arg0>
        src_args;
        typedef
            list1<
                typename uncvref<Arg0 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 1> src_type;
        typedef proto::basic_expr<Tag, dst_args, 1> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 >
    struct by_value_generator_<
        proto::expr<Tag, list2<Arg0 , Arg1>, 2>
    >
    {
        typedef
            list2<Arg0 , Arg1>
        src_args;
        typedef
            list2<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 2> src_type;
        typedef proto::expr<Tag, dst_args, 2> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list2<Arg0 , Arg1>, 2>
    >
    {
        typedef
            list2<Arg0 , Arg1>
        src_args;
        typedef
            list2<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 2> src_type;
        typedef proto::basic_expr<Tag, dst_args, 2> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 >
    struct by_value_generator_<
        proto::expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3>
    >
    {
        typedef
            list3<Arg0 , Arg1 , Arg2>
        src_args;
        typedef
            list3<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 3> src_type;
        typedef proto::expr<Tag, dst_args, 3> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3>
    >
    {
        typedef
            list3<Arg0 , Arg1 , Arg2>
        src_args;
        typedef
            list3<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 3> src_type;
        typedef proto::basic_expr<Tag, dst_args, 3> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct by_value_generator_<
        proto::expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4>
    >
    {
        typedef
            list4<Arg0 , Arg1 , Arg2 , Arg3>
        src_args;
        typedef
            list4<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 4> src_type;
        typedef proto::expr<Tag, dst_args, 4> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4>
    >
    {
        typedef
            list4<Arg0 , Arg1 , Arg2 , Arg3>
        src_args;
        typedef
            list4<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 4> src_type;
        typedef proto::basic_expr<Tag, dst_args, 4> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct by_value_generator_<
        proto::expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5>
    >
    {
        typedef
            list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>
        src_args;
        typedef
            list5<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 5> src_type;
        typedef proto::expr<Tag, dst_args, 5> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5>
    >
    {
        typedef
            list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>
        src_args;
        typedef
            list5<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 5> src_type;
        typedef proto::basic_expr<Tag, dst_args, 5> type;
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4
            };
            return that;
        }
    };
