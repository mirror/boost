// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the class template access_control, which
// allows the type of inheritance from a provided base class to be specified 
// using a template parameter.

#ifndef BOOST_IOSTREAMS_DETAIL_COMPOSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_COMPOSE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif        

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/io_traits.hpp>
#include <boost/iostreams/is_filter.hpp>
#include <boost/iostreams/operations.hpp>
   
namespace boost { namespace iostreams { namespace detail {

template<typename Composition, typename Concept>
struct composition {
    typedef BOOST_IOSTREAMS_CAR_TYPE(Concept) char_type;
    typedef typename
            mpl::if_< 
                is_filter<Concept>, 
                filter_tag, 
                device_tag
            >::type                    base_tag;
    typedef typename
            mpl::if_< 
                is_filter<Concept>, 
                filter_tag, 
                device_tag
            >::type                    mode_tag;
    struct category1
        : base_tag,
          dual_use_tag,
          closable_tag,
          localizable_tag 
        { };
          




};

struct null_piper { 
    template<typename Chain>
    void push(Chain& chn) const { }
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

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_COMPOSE_HPP_INCLUDED
