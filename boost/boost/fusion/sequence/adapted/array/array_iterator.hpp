/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ARRAY_ITERATOR_26122005_2250)
#define BOOST_FUSION_ARRAY_ITERATOR_26122005_2250

#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template<typename Array, std::size_t Pos>
    struct array_iterator
        : iterator_facade<array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos,>=,0);
        BOOST_MPL_ASSERT_RELATION(Pos,<=,std::size_t(Array::static_size));

        typedef mpl::size_t<Pos> index;
        typedef Array array_type;

        array_iterator(Array& a)
            : array(a) {}

        Array& array;

        template <typename Iterator>
        struct value_of
        {
            typedef typename Iterator::array_type array_type;
            typedef typename array_type::value_type type;
        };

        template <typename Iterator>
        struct deref
        {
            typedef typename Iterator::array_type array_type;
            typedef typename 
                mpl::if_<
                    is_const<array_type>
                  , typename array_type::const_reference
                  , typename array_type::reference
                >::type 
            type;

            static type
            call(Iterator const & it)
            {
                return it.array[Iterator::index::value];
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef typename Iterator::array_type array_type;
            typedef typename Iterator::index index;
            static int const index_val = index::value;
            typedef array_iterator<array_type, index_val + 1> type;

            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename Iterator>
        struct prior
        {
            typedef typename Iterator::array_type array_type;
            typedef typename Iterator::index index;
            static int const index_val = index::value;
            typedef array_iterator<array_type, index_val - 1> type;

            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::array_type array_type;
            typedef array_iterator<array_type, index::value + N::value> type;

            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename First, typename Last>
        struct distance : mpl::minus<typename Last::index, typename First::index>
        {
            typedef typename mpl::minus<
                typename Last::index, typename First::index>::type 
            type;

            static type
            call(First const&, Last const&)
            {
                return type();
            }
        };

    private:

        array_iterator<Array, Pos> operator=(const array_iterator<Array, Pos>&);
    };
}}

#endif
