// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/is_filter.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
# include <boost/type_traits/is_base_and_derived.hpp>
#endif

#define BOOST_IOSTREAMS_PIPABLE_TEMPLATE_PARAMS(arity) \
    BOOST_PP_ENUM_PARAMS(arity, typename T) BOOST_PP_COMMA_IF(arity) \
    /**/

#define BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
    BOOST_PP_EXPR_IF(arity, <) \
    BOOST_PP_ENUM_PARAMS(arity, T) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#define BOOST_IOSTREAMS_PIPABLE(filter, arity) \
    template<BOOST_IOSTREAMS_PIPABLE_TEMPLATE_PARAMS(arity) typename Concept> \
    ::boost::iostreams::detail::piper< \
        ::boost::iostreams::detail::concept_piper< \
            filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
        >, \
        Concept \
    > operator|( const filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity)& f, \
        const Concept& c ) \
    { \
        return ::boost::iostreams::detail::piper< \
                   ::boost::iostreams::detail::concept_piper< \
                       filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
                   >, \
                   Concept \
               >(f, c); \
    } \
    /**/

namespace boost { namespace iostreams { namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
struct piper_base { };

template<typename T>
struct is_piper 
    : is_base_and_derived<piper_base, T>
    { };
#endif

template<typename Concept>
struct concept_piper 
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    : piper_base 
#endif 
{
    concept_piper(const Concept& concept) : concept_(concept) { }
    template<typename Chain>
    void push(Chain& chn) const { chn.push(concept_); }
    const Concept& concept_;
};

template<typename Piper, typename Concept>
struct piper : Piper {
    typedef Piper    piper_type;
    typedef Concept  concept_type;
    piper(const Piper& p, const Concept& concept)
        : Piper(p), concept_(concept)
        { }
    template<typename Chain>
    void push(Chain& chn) const
    {
        Piper::push(chn);
        chn.push(concept_);
    }
    const Concept& concept_;
};

template<typename Piper, typename Filter, typename Concept>
piper<piper<Piper, Filter>, Concept>
operator|(const piper<Piper, Filter>& p, const Concept& cpt)
{
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    return piper<piper<Piper, Filter>, Concept>(p, cpt);
}

} } } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
