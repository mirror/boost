/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_RVALUE_ARGS_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/fusion/sequence/container/vector/vector.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/adapter/detail/nullary_call_base.hpp>

namespace boost { namespace fusion
{
    template <class Function> class unfused_rvalue_args;

    //----- ---- --- -- - -  -   -

    struct void_;

    template <class Function> class unfused_rvalue_args
        : public detail::nullary_call_base
              <unfused_rvalue_args<Function>, Function>
    {
        Function fnc_transformed;

        template <class D, class F, bool EC, bool E>
        friend struct detail::nullary_call_base;

        typedef detail::nullary_call_base<
            fusion::unfused_rvalue_args<Function>, Function > base;

        typedef typename remove_const<typename boost::remove_reference<Function>::type>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;

      public:

        inline explicit unfused_rvalue_args(func_const_fwd_t f = function())
            : fnc_transformed(f)
        { }

        using base::operator();

        template <typename Sig>
        struct result
        { };

        template <class Self>
        struct result< Self const () >
            : base::call_const_0_result_class
        { };

        template <class Self>
        struct result< Self() >
            : base::call_0_result_class
        { };

        #define  BOOST_PP_FILENAME_1 \
            <boost/fusion/functional/adapter/unfused_rvalue_args.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (1,BOOST_FUSION_UNFUSED_RVALUE_ARGS_MAX_ARITY)
        #include BOOST_PP_ITERATE()
    };
}}

namespace boost 
{
    template<class F>
    struct result_of<boost::fusion::unfused_rvalue_args<F> const ()>
    {
        typedef typename boost::fusion::unfused_rvalue_args<F>::call_const_0_result type;
    };
    template<class F>
    struct result_of<boost::fusion::unfused_rvalue_args<F>()>
    {
        typedef typename boost::fusion::unfused_rvalue_args<F>::call_0_result type;
    };
}

#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_RVALUE_ARGS_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
////////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
////////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
            : function::template result< function const (
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::cref<T,>::type BOOST_PP_INTERCEPT) >)>
        { };

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self (BOOST_PP_ENUM_PARAMS(N,T)) >
            : function::template result< function (
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::cref<T,>::type BOOST_PP_INTERCEPT) >)>
        { };

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        inline typename function::template result<function(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& BOOST_PP_INTERCEPT)>)>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& a)) const
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        inline typename function::template result<function(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& BOOST_PP_INTERCEPT)>)>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& a)) 
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif

