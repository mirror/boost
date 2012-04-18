/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_CPP03_FUSION_DEQUE_26112006_1649)
#define BOOST_CPP03_FUSION_DEQUE_26112006_1649

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/fusion/container/deque/detail/cpp11_deque_keyed_values.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>
#include <boost/fusion/container/deque/detail/value_at_impl.hpp>
#include <boost/fusion/container/deque/detail/at_impl.hpp>
#include <boost/fusion/container/deque/detail/begin_impl.hpp>
#include <boost/fusion/container/deque/detail/end_impl.hpp>
#include <boost/fusion/container/deque/detail/is_sequence_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

#include <boost/mpl/int.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    template <typename ...Elements>
    struct deque : detail::nil_keyed_element
    {
    };

    template <typename Head, typename ...Tail>
    struct deque<Head, Tail...>
      : detail::deque_keyed_values<Head, Tail...>::type
      , sequence_base<deque<Head, Tail...>>
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef typename detail::deque_keyed_values<Head, Tail...>::type base;
        typedef mpl::int_<(sizeof ...(Tail) + 1)> size;
        typedef mpl::int_<size::value> next_up;
        typedef mpl::int_<mpl::int_<((size::value == 0) ? 0 : -1)>::type::value> next_down;
        typedef mpl::false_ is_view;

        deque()
        {}

        template <typename ...Elements>
        deque(deque<Elements...> const& seq)
          : base(seq)
        {}

        explicit deque(typename add_reference<typename add_const<Head>::type>::type head
          , typename add_reference<typename add_const<Tail>::type>::type... tail)
          : base(detail::deque_keyed_values<Head, Tail...>::call(head, tail...))
        {}

        template <typename Sequence>
        explicit deque(Sequence const& seq
          , typename disable_if<is_convertible<Sequence, Head> >::type* /*dummy*/ = 0)
          : base(base::from_iterator(fusion::begin(seq)))
        {}

        template <typename ...Elements>
        deque& operator=(deque<Elements...> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque& operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }
    };
}}

#endif
