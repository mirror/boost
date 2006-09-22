//
//  Copyright (c) 2005, 2006 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !BOOST_PP_IS_ITERATING

# if !defined(BOOST_FUSION_SEQUENCE_UTILITY_UNPACK_ARGS_HPP_INCLUDED)
# define BOOST_FUSION_SEQUENCE_UTILITY_UNPACK_ARGS_HPP_INCLUDED

#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/arithmetic/inc.hpp>
#   include <boost/preprocessor/arithmetic/dec.hpp>
#   include <boost/preprocessor/repetition/repeat.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#   include <boost/preprocessor/iteration/iterate.hpp>
#   include <boost/utility/result_of.hpp>
#   include <boost/mpl/int.hpp>
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/identity.hpp>
#   include <boost/type_traits/add_pointer.hpp>
#   include <boost/type_traits/is_function.hpp>
#   include <boost/type_traits/is_pointer.hpp>
#   include <boost/type_traits/remove_cv.hpp>
#   include <boost/fusion/sequence/intrinsic/begin.hpp>
#   include <boost/fusion/sequence/intrinsic/size.hpp>
#   include <boost/fusion/iterator/next.hpp>
#   include <boost/fusion/iterator/deref.hpp>
#   include <boost/fusion/sequence/utility/limits.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <class F>
        struct unpack_args_impl_helper
        {
            typedef typename remove_cv<F>::type f_nocv;

            typedef 
                typename mpl::eval_if<
                    is_pointer<f_nocv>,
                    mpl::identity<f_nocv>,
                    mpl::eval_if<
                        is_function<f_nocv>,
                        add_pointer<f_nocv>,
                        mpl::identity<F>
                    >
                >::type
            type;
        };

        template <
            class F,
            class Sequence,
            class F_ = typename unpack_args_impl_helper<F>::type,
            class Size = mpl::int_<result_of::size<Sequence>::value>
        >
        struct unpack_args_impl;

        template <class F, class Sequence, class F_>
        struct unpack_args_impl<F, Sequence, F_, mpl::int_<0> >
        {
            typedef typename boost::result_of<F_()>::type type;

            static type call(F & f, Sequence &)
            {
                return f();
            }
        };

#   define BOOST_FUSION_next_iterator(z, n, data)                               \
    typedef typename fusion::result_of::next<BOOST_PP_CAT(I, n)>::type          \
        BOOST_PP_CAT(I, BOOST_PP_INC(n));

#   define BOOST_FUSION_deref_iterator(z, n, data)                              \
    typedef typename fusion::result_of::deref<BOOST_PP_CAT(I, BOOST_PP_INC(n))  \
        >::type BOOST_PP_CAT(T, BOOST_PP_INC(n));

#   define BOOST_FUSION_next_call_iterator(z, n, data)                          \
    BOOST_PP_CAT(I, BOOST_PP_INC(n)) BOOST_PP_CAT(i, BOOST_PP_INC(n))           \
        = fusion::next(BOOST_PP_CAT(i, n));

#   define BOOST_FUSION_n BOOST_PP_ITERATION()

#   define BOOST_PP_ITERATION_PARAMS_1 (3, (1, FUSION_MAX_UNPACK_ARG_SIZE,      \
      <boost/fusion/sequence/utility/unpack_args.hpp>))

#   include BOOST_PP_ITERATE()

#   undef BOOST_FUSION_next_iterator
#   undef BOOST_FUSION_deref_iterator
#   undef BOOST_FUSION_next_call_iterator
#   undef BOOST_FUSION_n

#   undef BOOST_PP_ITERATION_PARAMS_1

    } // namespace detail

    namespace result_of
    {

        template <class F, class Sequence>
        struct unpack_args
            : detail::unpack_args_impl<F, Sequence>
        {
        };

    } // namespace result_of

    template <class F, class Sequence>
    inline typename result_of::unpack_args<F, Sequence>::type
    unpack_args(F & f, Sequence & seq)
    {
        return result_of::unpack_args<F, Sequence>::call(f, seq);
    }

    template <class F, class Sequence>
    inline typename result_of::unpack_args<F const, Sequence>::type
    unpack_args(F const & f, Sequence & seq)
    {
        return result_of::unpack_args<F const, Sequence>::call(f, seq);
    }

    template <class F, class Sequence>
    inline typename result_of::unpack_args<F, Sequence const>::type
    unpack_args(F & f, Sequence const & seq)
    {
        return result_of::unpack_args<F, Sequence const>::call(f, seq);
    }

    template <class F, class Sequence>
    inline typename result_of::unpack_args<F const, Sequence const>::type
    unpack_args(F const & f, Sequence const & seq)
    {
        return result_of::unpack_args<F const, Sequence const>::call(f, seq);
    }

}} // namespace boost::fusion

# endif // include guard

#else // BOOST_PP_IS_ITERATING

    template <class F, class Sequence, class F_>
    struct unpack_args_impl<F, Sequence, F_, mpl::int_<BOOST_FUSION_n> >
    {
        typedef typename fusion::result_of::begin<Sequence>::type I0;
        typedef typename fusion::result_of::deref<I0>::type T0;

        BOOST_PP_REPEAT(BOOST_FUSION_n, BOOST_FUSION_next_iterator, ~)
        BOOST_PP_REPEAT(BOOST_FUSION_n, BOOST_FUSION_deref_iterator, ~)

        typedef typename boost::result_of<
            F_( BOOST_PP_ENUM_PARAMS(BOOST_FUSION_n, T) )
        >::type type;

        static type call(F & f, Sequence & seq)
        {
            I0 i0 = fusion::begin(seq);

            BOOST_PP_REPEAT(BOOST_PP_DEC(BOOST_FUSION_n), BOOST_FUSION_next_call_iterator, ~)

            return f( BOOST_PP_ENUM_PARAMS(BOOST_FUSION_n, *i) );
        }
    };

#endif // BOOST_PP_IS_ITERATING
