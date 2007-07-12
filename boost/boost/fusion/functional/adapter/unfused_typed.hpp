/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/has_type.hpp>
#include <boost/fusion/functional/adapter/detail/nullary_call_base.hpp>


namespace boost { namespace fusion
{

    template <class Function, class Sequence> class unfused_typed;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template <class Derived, class Function, class Sequence,
            long Arity, bool EnableCallOp>
        struct unfused_typed_impl;

        template <class Derived, class Function, class Sequence,
            class NextSeq = typename result_of::pop_back<Sequence>::type >
        struct unfused_typed_next_base 
        {
            // type of the next base class
            typedef unfused_typed_impl
                < Derived, Function, NextSeq, result_of::size<NextSeq>::value,
                  has_type< typename Function::template result<Function( 
                      typename result_of::as_vector<NextSeq>::type)> >::value
                >
            type; 
        };

        template <class Derived, class Function, class Sequence, long Arity>
        struct unfused_typed_impl<Derived,Function,Sequence,Arity,false>
            : unfused_typed_next_base<Derived,Function,Sequence>::type
        { };

        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,0,false>
            : nullary_call_base<Derived,Function,false>
        { };

        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,0,true>
            : nullary_call_base<Derived,Function,true>
        { };

    }

    template <class Function, class Sequence>
    class unfused_typed
        : public detail::unfused_typed_next_base
          < unfused_typed<Function,Sequence>,
            typename remove_const<typename remove_reference<Function>::type>::type, Sequence, Sequence
          >::type
    {
        Function fnc_transformed;

        template <class D, class F, class S, long A, bool EO>
        friend struct detail::unfused_typed_impl;

        template <class D, class F, bool E>
        friend struct detail::nullary_call_base;

        typedef typename remove_const<typename boost::remove_reference<Function>::type>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;

        typedef typename detail::unfused_typed_next_base<unfused_typed<
            function, Sequence>,function,Sequence,Sequence>::type base;

    public:

        inline explicit unfused_typed(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

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
    }; 

    #define  BOOST_PP_FILENAME_1 <boost/fusion/functional/adapter/unfused_typed.hpp>
    #define  BOOST_PP_ITERATION_LIMITS (1,BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
    #include BOOST_PP_ITERATE() 

}}

namespace boost 
{
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq> const () >
    {
        typedef typename boost::fusion::unfused_typed<F,Seq>::call_const_0_result type;
    };
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq>() >
    {
        typedef typename boost::fusion::unfused_typed<F,Seq>::call_0_result type;
    };
}


#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    namespace detail
    {

        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,N,true>
            : unfused_typed_next_base<Derived,Function,Sequence>::type
        {
        private:
            typedef typename unfused_typed_next_base<
                Derived,Function,Sequence>::type base;

            typedef typename remove_const<typename remove_reference<Function>::type>::type function;
            typedef typename result_of::as_vector<Sequence>::type arg_vector_t;

        protected:
            typedef typename function::
                template result<function const (arg_vector_t)> BOOST_PP_CAT(rc,N);
            typedef typename function::
                template result<function(arg_vector_t)> BOOST_PP_CAT(r,N);
        public:

            using base::operator();

#define M(z,i,s)                                                                \
    typename call_param<typename result_of::value_at_c<s,i>::type>::type a##i

            inline typename function::template result<function const (arg_vector_t)>::type 
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) const
            {
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
                return static_cast<Derived const *>(this)->fnc_transformed(arg);
            }

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
            inline typename function::template result<function(arg_vector_t)>::type 
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) 
            {
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
                return static_cast<Derived *>(this)->fnc_transformed(arg);
            }
#endif

#undef M
        };

    } // namespace detail

    template <class Function, class Sequence> 
        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
    struct unfused_typed<Function,Sequence>::result<
            Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
        : BOOST_PP_CAT(base::rc,N)
    { };

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    template <class Function, class Sequence> 
        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
    struct unfused_typed<Function,Sequence>::result<
            Self (BOOST_PP_ENUM_PARAMS(N,T)) >
        : BOOST_PP_CAT(base::r,N)
    { };
#endif

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif

