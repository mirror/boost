    ///////////////////////////////////////////////////////////////////////////////
    /// \file basic_expr.hpp
    /// Contains definition of basic_expr\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag, typename Arg0>
    struct basic_expr<Tag, term<Arg0>, 0>
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 0;
        typedef mpl::long_<0 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef term<Arg0> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4;
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        static basic_expr const make(A0 &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        template<typename A0>
        static basic_expr const make(A0 const &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0>
    struct basic_expr<Tag, list1<Arg0>, 1 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 1;
        typedef mpl::long_<1 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list1<Arg0> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4;
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        static basic_expr const make(A0 const &a0)
        {
            basic_expr that = {a0};
            return that;
        }
        
        
        
        typedef typename detail::address_of_hack<Tag, proto_child0>::type address_of_hack_type_;
        
        
        
        
        
        
        
        operator address_of_hack_type_() const
        {
            return boost::addressof(this->child0);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1>
    struct basic_expr<Tag, list2<Arg0 , Arg1>, 2 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 2;
        typedef mpl::long_<2 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list2<Arg0 , Arg1> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1;
        typedef void proto_child2; typedef void proto_child3; typedef void proto_child4;
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1>
        static basic_expr const make(A0 const &a0 , A1 const &a1)
        {
            basic_expr that = {a0 , a1};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2>
    struct basic_expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 3;
        typedef mpl::long_<3 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list3<Arg0 , Arg1 , Arg2> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2;
        typedef void proto_child3; typedef void proto_child4;
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2>
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2)
        {
            basic_expr that = {a0 , a1 , a2};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    struct basic_expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 4;
        typedef mpl::long_<4 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list4<Arg0 , Arg1 , Arg2 , Arg3> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3;
        typedef void proto_child4;
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3)
        {
            basic_expr that = {a0 , a1 , a2 , a3};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    struct basic_expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 5;
        typedef mpl::long_<5 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> proto_args;
        typedef basic_expr proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4;
        
        
        
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
