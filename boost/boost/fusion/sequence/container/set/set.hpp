/*=============================================================================
    Copyright (c) 2005 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_09162005_1104)
#define FUSION_SET_09162005_1104

#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/container/set/set_fwd.hpp>
#include <boost/fusion/sequence/container/set/detail/lookup_key.hpp>
#include <boost/fusion/sequence/container/set/detail/begin_impl.hpp>
#include <boost/fusion/sequence/container/set/detail/end_impl.hpp>
#include <boost/fusion/sequence/container/set/detail/at_key_impl.hpp>
#include <boost/fusion/sequence/container/set/detail/value_at_key_impl.hpp>
#include <boost/fusion/sequence/container/set/detail/is_associative_impl.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct set_tag;
    struct forward_sequence_tag;
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, typename T)>
    struct set : sequence_base<set<BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)> >
    {
        typedef set_tag ftag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef forward_sequence_tag category;
        typedef mpl::false_ is_view;

        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)> 
        storage_type;

        typedef typename storage_type::size size;

        set()
            : data() {}
        
        template <typename T>
        explicit set(T const& rhs)
            : data(rhs) {}

        #include <boost/fusion/sequence/container/set/detail/set_forward_ctor.hpp>
        #include <boost/fusion/sequence/container/set/detail/set_lookup.hpp>

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }
        storage_type const& get_data() const { return data; }

    private:
        
        storage_type data;
    };
}}

#endif
