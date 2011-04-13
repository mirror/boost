
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_SCOPE_DETAIL_LET_LOCAL_GEN_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_LET_LOCAL_GEN_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/scope/detail/preprocessed/let_local_gen.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SCOPE_DETAIL_LET_LOCAL_GEN_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_LET_LOCAL_GEN_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/let_local_gen_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/let_local_gen.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <BOOST_PHOENIX_typename_A>
        let_actor_gen<
            typename detail::make_locals<BOOST_PHOENIX_A>::type
        > const
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            return detail::make_locals<BOOST_PHOENIX_A>::make(BOOST_PHOENIX_a);
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES
