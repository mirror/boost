/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_NEXT_IMPL_HPP_INCLUDED

#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/view/ext_/detail/begin_impl.hpp>

namespace boost { namespace fusion
{
    struct segmented_iterator_tag;

    template<typename Nodes>
    struct segmented_iterator;

    namespace detail
    {
        //bool is_invalid(stack)
        //{
        //  return empty(car(stack));
        //}

        template<typename Stack>
        struct is_invalid
          : result_of::empty<typename Stack::car_type>
        {};

        ////Advance the first iterator in the range at the
        ////top of a stack of iterator ranges. Return the
        ////new stack.
        //auto pop_front_car(stack)
        //{
        //  return cons(pop_front(car(stack)), cdr(stack))
        //}

        template<typename Stack>
        struct pop_front_car
        {
            typedef typename Stack::car_type car_type;
            typedef typename result_of::pop_front<car_type>::type new_car_type;
            typedef cons<new_car_type, typename Stack::cdr_type> type;

            static type call(Stack const & stack)
            {
                return type(fusion::pop_front(stack.car), stack.cdr);
            }
        };

        template<
            typename Stack,
            typename Next   = typename pop_front_car<Stack>::type,
            bool IsInvalid  = is_invalid<Next>::value,
            int StackSize   = Stack::size::value>
        struct segmented_next_impl_recurse;

        // Handle the case where the top of the stack has no usable 
        //auto segmented_next_impl_recurse3(stack)
        //{
        //  if (size(stack) == 1)
        //    return cons(iterator_range(end(car(stack)), end(car(stack))), nil);
        //  else
        //    return segmented_next_impl_recurse(stack.cdr);
        //}

        template<
            typename Stack,
            int StackSize = Stack::size::value>
        struct segmented_next_impl_recurse3
        {
            typedef segmented_next_impl_recurse<typename Stack::cdr_type> impl;
            typedef typename impl::type type;

            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }
        };

        template<typename Stack>
        struct segmented_next_impl_recurse3<Stack, 1>
        {
            typedef typename Stack::car_type::end_type end_type;
            typedef iterator_range<end_type, end_type> range_type;
            typedef cons<range_type> type;

            static type call(Stack const & stack)
            {
                return type(range_type(stack.car.last, stack.car.last));
            }
        };

        //auto segmented_next_impl_recurse2(stack)
        //{
        //  auto res = segmented_begin_impl(front(car(stack)), stack);
        //  if (is_invalid(res))
        //    return segmented_next_impl_recurse3(stack);
        //  else
        //    return res;
        //}

        template<
            typename Stack,
            typename Range  =
                typename remove_reference<
                    typename add_const<
                        typename result_of::deref<typename Stack::car_type::begin_type>::type
                    >::type
                >::type,
            typename Result =
                typename segmented_begin_impl<Range, Stack>::type,
            bool IsInvalid  =
                is_invalid<Result>::value>
        struct segmented_next_impl_recurse2
        {
            typedef segmented_next_impl_recurse3<Stack> impl;
            typedef typename impl::type type;

            static type call(Stack const & stack)
            {
                return impl::call(stack);
            }
        };

        template<typename Stack, typename Range, typename Result>
        struct segmented_next_impl_recurse2<Stack, Range, Result, false>
        {
            typedef Result type;

            static type call(Stack const & stack)
            {
                return segmented_begin_impl<Range, Stack>::call(*stack.car.first, stack);
            }
        };

        //auto segmented_next_impl_recurse(stack)
        //{
        //  auto next = pop_front_car(stack);
        //  if (is_invalid(next))
        //    if (1 == size(stack))
        //      return next;
        //    else
        //      return segmented_next_impl_recurse(cdr(stack));
        //  else
        //    return segmented_next_impl_recurse2(next)
        //}

        template<typename Stack, typename Next, bool IsInvalid, int StackSize>
        struct segmented_next_impl_recurse
        {
            typedef
                typename segmented_next_impl_recurse<typename Stack::cdr_type>::type
            type;

            static type call(Stack const& stack)
            {
                return segmented_next_impl_recurse<typename Stack::cdr_type>::call(stack.cdr);
            }
        };

        template<typename Stack, typename Next>
        struct segmented_next_impl_recurse<Stack, Next, true, 1>
        {
            typedef Next type;

            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }
        };

        template<typename Stack, typename Next, int StackSize>
        struct segmented_next_impl_recurse<Stack, Next, false, StackSize>
        {
            typedef segmented_next_impl_recurse2<Next> impl;
            typedef typename impl::type type;

            static type call(Stack const & stack)
            {
                return impl::call(pop_front_car<Stack>::call(stack));
            }
        };

        //auto segmented_next_impl(stack)
        //{
        //  // car(stack) is a range of values, not a range of segments
        //  auto next = pop_front_car(stack);
        //  if (is_invalid(next))
        //    return segmented_next_impl_recurse(cdr(next));
        //  else
        //    return next;
        //}

        template<
            typename Stack,
            typename Next   = typename pop_front_car<Stack>::type,
            bool IsInvalid  = is_invalid<Next>::value>
        struct segmented_next_impl
        {
            typedef segmented_next_impl_recurse<typename Stack::cdr_type> impl;
            typedef typename impl::type type;

            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }
        };

        template<typename Stack, typename Next>
        struct segmented_next_impl<Stack, Next, false>
        {
            typedef Next type;

            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<segmented_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef detail::segmented_next_impl<typename It::nodes_type> impl;
                typedef segmented_iterator<typename impl::type> type;

                static type call(It const& it)
                {
                    return type(impl::call(it.nodes));
                }
            };
        };

    }
}}

#endif
