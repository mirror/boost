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

#include <boost/utility/result_of.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>


namespace boost { namespace fusion
{

    template <class Function, class Sequence> class unfused_typed;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template <class Derived, class Function, class Sequence,
            long Arity = result_of::size<Sequence>::value >
        struct unfused_typed_impl;
    }

    template <class Function, class Sequence>
    class unfused_typed
        : public detail::unfused_typed_impl
          < unfused_typed<Function,Sequence>, typename detail::uncr<Function>::type, 
            Sequence > 
    {
        Function fnc_transformed;

        typedef typename detail::uncr<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;

        typedef typename detail::unfused_typed_impl<
            unfused_typed<Function,Sequence>,function,Sequence > base;

        template <class D, class F, class S, long A>
        friend struct detail::unfused_typed_impl;

    public:

        inline explicit unfused_typed(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <typename Sig>
        struct result;
    }; 

    namespace detail
    {
        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,0>
        {
            typedef fusion::vector0 arg_vector_t;

        public:

            typedef typename boost::result_of<
                Function const (arg_vector_t &) > call_const_0_result;

            typedef typename boost::result_of<
                Function(arg_vector_t &) > call_0_result;

            inline typename boost::result_of< 
                Function const (arg_vector_t &) >::type
            operator()() const
            {
                arg_vector_t arg;
                return static_cast<Derived const *>(this)->fnc_transformed(arg);
            }

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
            inline typename boost::result_of<
                Function (arg_vector_t &) >::type 
            operator()() 
            {
                arg_vector_t arg;
                return static_cast<Derived *>(this)->fnc_transformed(arg);
            }
#endif
        };
    }

    #define  BOOST_PP_FILENAME_1 <boost/fusion/functional/adapter/unfused_typed.hpp>
    #define  BOOST_PP_ITERATION_LIMITS (1,BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
    #include BOOST_PP_ITERATE() 

}}

namespace boost 
{
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq> const () >
        : boost::fusion::unfused_typed<F,Seq>::call_const_0_result
    { };
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq>() >
        : boost::fusion::unfused_typed<F,Seq>::call_0_result
    { };
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
        struct unfused_typed_impl<Derived,Function,Sequence,N>
            : unfused_typed_impl<Derived,Function,
                typename result_of::pop_back<Sequence>::type, BOOST_PP_DEC(N) >
        {
            typedef typename result_of::as_vector<Sequence>::type arg_vector_t;

        protected:

            typedef typename boost::result_of<
                Function const (arg_vector_t &) > BOOST_PP_CAT(rc,N);

            typedef typename boost::result_of<
                Function(arg_vector_t &) > BOOST_PP_CAT(r,N);

        public:

            using unfused_typed_impl< Derived,Function, 
                typename result_of::pop_back<Sequence>::type, BOOST_PP_DEC(N)
                >::operator();

#define M(z,i,s)                                                                \
    typename call_param<typename result_of::value_at_c<s,i>::type>::type a##i

            inline typename boost::result_of< 
                Function const (arg_vector_t &) >::type
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) const
            {
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
                return static_cast<Derived const *>(this)->fnc_transformed(arg);
            }

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
            inline typename boost::result_of<
                Function (arg_vector_t &) >::type 
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) 
            {
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
                return static_cast<Derived *>(this)->fnc_transformed(arg);
            }
#endif

#undef M
        };

    } // namespace detail

#if N > 0
    template <class Function, class Sequence> 
        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
    struct unfused_typed<Function,Sequence>::result<
            Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
        : BOOST_PP_CAT(base::rc,N)
    { };

#   if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    template <class Function, class Sequence> 
        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
    struct unfused_typed<Function,Sequence>::result<
            Self (BOOST_PP_ENUM_PARAMS(N,T)) >
        : BOOST_PP_CAT(base::r,N)
    { };
#   endif
#endif

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif

