/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEREF_IMPL_27122005_0951)
#define BOOST_FUSION_DEREF_IMPL_27122005_0951

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion {

    struct array_iterator_tag;

    template<typename Array, std::size_t Pos>
    struct array_iterator;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<array_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::array_type array_type;
                typedef typename mpl::if_<
                    is_const<array_type>, 
                    typename array_type::const_reference,
                    typename array_type::reference>::type type;

                static type
                call(Iterator const & it)
                {
                    return it.array[Iterator::index::value];
                }
            };
        };
    }
}}

#endif
