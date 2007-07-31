// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_WHERE_DWA2006430_HPP
# define BOOST_CONCEPT_WHERE_DWA2006430_HPP

# include <boost/parameter/aux_/parenthesized_type.hpp>
# include <boost/concept/assert.hpp>
# include <boost/preprocessor/seq/for_each.hpp>

namespace boost { 

// Template for use in handwritten assertions
template <class Model, class More>
struct where_ : More
{
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef typename More::type type;
# endif 
    BOOST_CONCEPT_ASSERT((Model));
};

// Template for use by macros, where models must be wrapped in parens.
// This isn't in namespace detail to keep extra cruft out of resulting
// error messages.
template <class ModelFn, class More>
struct _where_ : More
{
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef typename More::type type;
# endif 
    BOOST_CONCEPT_ASSERT_FN(ModelFn);
};

#define BOOST_CONCEPT_WHERE_OPEN(r,data,t) ::boost::_where_<void(*)t,
#define BOOST_CONCEPT_WHERE_CLOSE(r,data,t) >

#if defined(NDEBUG) || BOOST_WORKAROUND(BOOST_MSVC, < 1300)

# define BOOST_CONCEPT_WHERE(models, result)                                    \
    typename ::boost::parameter::aux::unaryfunptr_arg_type<void(*)result>::type

#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

// Same thing as below without the initial typename
# define BOOST_CONCEPT_WHERE(models, result)                                \
    BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_WHERE_OPEN, ~, models)              \
      ::boost::parameter::aux::unaryfunptr_arg_type<void(*)result>          \
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_WHERE_CLOSE, ~, models)::type

#else

// This just ICEs on MSVC6 :(
# define BOOST_CONCEPT_WHERE(models, result)                                \
    typename BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_WHERE_OPEN, ~, models)     \
      ::boost::parameter::aux::unaryfunptr_arg_type<void(*)result>          \
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_WHERE_CLOSE, ~, models)::type

#endif 

} // namespace boost::concept_check

#endif // BOOST_CONCEPT_WHERE_DWA2006430_HPP
