/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_SEP_23_2009_0948PM

#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/utility/result_of.hpp>

#include <boost/type_traits/remove_reference.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/view/transform_view.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct addref
        {
            template<typename Sig>
            struct result;

            template<typename U>
            struct result<addref(U)> : boost::add_reference<U> {};

            template <typename T>
            typename boost::result_of<addref(T)>::type 
            operator()(T& x) const
            {
                return x;
            }
        };
    }

    struct nview_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template<typename Sequence, typename Indicies>
    struct nview
      : sequence_base<nview<Sequence, Indicies> >
    {
        typedef nview_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;

        typedef mpl::true_ is_view;
        typedef Indicies index_type;
        typedef typename mpl::size<Indicies>::type size;

        typedef transform_view<Sequence, detail::addref> transform_view_type;
        typedef typename result_of::as_vector<transform_view_type>::type 
            sequence_type;

        explicit nview(Sequence& val)
          : seq(as_vector(transform_view_type(val, detail::addref()))) 
        {}

        sequence_type seq;
    };

}}

// define the nview() generator functions
#include <boost/fusion/view/nview/detail/nview_impl.hpp>

#endif


