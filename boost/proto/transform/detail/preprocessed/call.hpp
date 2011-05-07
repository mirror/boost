    ///////////////////////////////////////////////////////////////////////////////
    /// \file call.hpp
    /// Contains definition of the call<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3>
    struct call<Fun(A0 , A1 , A2 , A3)> : transform<call<Fun(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct call<Fun(A0 , A1 , A2 , A3 , A4)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)));
            }
        };
    };
