//-----------------------------------------------------------------------------
// boost mpl/sequence_tag.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
#define BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

#include "boost/mpl/sequence_tag_fwd.hpp"
#include "boost/mpl/aux_/has_tag.hpp"
#include "boost/mpl/aux_/has_begin.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

#include "boost/type_traits/is_class.hpp"

namespace boost { namespace mpl {

namespace aux {

template< bool has_tag_, bool has_begin_ >
struct class_sequence_tag_impl
{
    // agurt 24/nov/02: MSVC 6.5 gets confused in 'sequence_tag_impl<true>' 
    // specialization below, if we name it 'result_' here
    template< typename Sequence > struct result2_;
};

#   define AUX_CLASS_SEQUENCE_TAG_SPEC(has_tag, has_begin, result_type) \
template<> struct class_sequence_tag_impl<has_tag,has_begin> \
{ \
    template< typename Sequence > struct result2_ \
    { \
        typedef result_type type; \
    }; \
}; \
/**/

AUX_CLASS_SEQUENCE_TAG_SPEC(true, true, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(true, false, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, true, nested_begin_end_tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, false, non_sequence_tag)

#   undef AUX_CLASS_SEQUENCE_TAG_SPEC


template< bool is_class_ >
struct sequence_tag_impl
{
    template< typename Sequence > struct result_
    {
        typedef non_sequence_tag type;
    };
};

template<>
struct sequence_tag_impl<true>
{
    template< typename Sequence > struct result_
        : class_sequence_tag_impl<
              ::boost::mpl::aux::has_tag<Sequence>::value
            , ::boost::mpl::aux::has_begin<Sequence>::value
            >::template result2_<Sequence>
    {
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct sequence_tag
    : aux::sequence_tag_impl<
          ::boost::is_class<Sequence>::value
        >::template result_<Sequence>
{
};

#if defined(BOOST_MPL_MSVC_ETI_BUG)
template<> struct sequence_tag<int>
{
    typedef non_sequence_tag type;
};
#endif

BOOST_MPL_AUX_VOID_SPEC(1, sequence_tag)

}} // namespace boost::mpl

#endif // BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
