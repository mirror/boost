// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/is_filter.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

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
        ::boost::iostreams::detail::piper< \
             ::boost::iostreams::detail::null_piper, \
             filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
        >, \
        Concept \
    > operator|( const \
                 ::boost::iostreams::detail::piper< \
                     ::boost::iostreams::detail::null_piper, \
                     filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
                 >& p, \
                 const Concept& concept ) \
    { \
        return \
        ::boost::iostreams::detail::piper< \
            ::boost::iostreams::detail::piper< \
                ::boost::iostreams::detail::null_piper, \
                filter BOOST_IOSTREAMS_PIPABLE_TEMPLATE_ARGS(arity) \
            >, \
            Concept \
        >(p, concept); \
    } \
    /**/

namespace boost { namespace iostreams { namespace detail {

struct null_piper {
    template<typename Chain>
    void push(Chain&) const { }
};

template<typename Piper, typename Concept>
struct piper {
    piper(const Concept& concept)
        : p_(0), concept_(&concept)
        {
            BOOST_STATIC_ASSERT((is_same<Piper, null_piper>::value));
        }
    piper(const Piper& p, const Concept& concept)
        : p_(&p), concept_(&concept)
        {
            BOOST_STATIC_ASSERT((!is_same<Piper, null_piper>::value));
        }
    template<typename Chain>
    void push(Chain& chn) const
        {
            if (p_) p_->push(chn);
            chn.push(*concept_);
        }
    const Piper*    p_;
    const Concept*  concept_;
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
