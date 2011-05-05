    ///////////////////////////////////////////////////////////////////////////////
    /// \file args.hpp
    /// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
    /// class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    template< typename Arg0 >
    struct term
    {
        static const long arity = 0;
        typedef Arg0 child0;
        typedef mpl::void_ child1; typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4;
        
        
        typedef Arg0 back_;
    };
    
    
    
    
    template< typename Arg0 >
    struct list1
    {
        static const long arity = 1;
        typedef Arg0 child0;
        typedef mpl::void_ child1; typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4;
        
        
        typedef Arg0 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 >
    struct list2
    {
        static const long arity = 2;
        typedef Arg0 child0; typedef Arg1 child1;
        typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4;
        
        
        typedef Arg1 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 >
    struct list3
    {
        static const long arity = 3;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2;
        typedef mpl::void_ child3; typedef mpl::void_ child4;
        
        
        typedef Arg2 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct list4
    {
        static const long arity = 4;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3;
        typedef mpl::void_ child4;
        
        
        typedef Arg3 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct list5
    {
        static const long arity = 5;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4;
        
        
        
        typedef Arg4 back_;
    };
