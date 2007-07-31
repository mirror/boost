/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BOOST_TUPLE_ITERATOR_09262006_1851)
#define FUSION_BOOST_TUPLE_ITERATOR_09262006_1851

#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;

    template <typename Cons = tuples::null_type>
    struct boost_tuple_iterator
        : iterator_facade<boost_tuple_iterator<Cons>, forward_traversal_tag>
    {
        typedef Cons cons_type;

        explicit boost_tuple_iterator(Cons& cons)
            : cons(cons) {}
        Cons& cons;

        template <typename Iterator>
        struct value_of : mpl::identity<typename Iterator::cons_type::head_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename value_of<Iterator>::type element;
    
            typedef typename 
                mpl::if_<
                    is_const<typename Iterator::cons_type>
                  , typename tuples::access_traits<element>::const_type
                  , typename tuples::access_traits<element>::non_const_type
                >::type 
            type;

            static type
            call(Iterator const& iter)
            {
                return iter.cons.get_head();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef typename Iterator::cons_type cons_type;
            typedef typename cons_type::tail_type tail_type;

            typedef boost_tuple_iterator<
                typename mpl::eval_if<
                    is_const<cons_type>
                  , add_const<tail_type>
                  , mpl::identity<tail_type>
                >::type>
            type;

            static type
            call(Iterator const& iter)
            {
                return type(iter.cons.get_tail());
            }
        };
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type>
        : iterator_facade<boost_tuple_iterator<tuples::null_type>, forward_traversal_tag>
    {
        template <typename Cons>
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type const>
        : iterator_facade<boost_tuple_iterator<tuples::null_type const>, forward_traversal_tag>
    {
        template <typename Cons>
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> >
        : iterator_facade<boost_tuple_iterator<tuples::tuple<> >, forward_traversal_tag>
    {
        template <typename Cons>
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> const>
        : iterator_facade<boost_tuple_iterator<tuples::tuple<> const>, forward_traversal_tag>
    {
        template <typename Cons>
        explicit boost_tuple_iterator(Cons const&) {}
    };
}}

#endif


