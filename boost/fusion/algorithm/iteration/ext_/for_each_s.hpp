/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_S_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_S_HPP_INCLUDED

#include <boost/fusion/support/void.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/view/ext_/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename Fun>
    struct segmented_for_each_fun
    {
        typedef result<void, continue_> result_type;

        explicit segmented_for_each_fun(Fun const& f)
          : fun(f)
        {}

        template<typename Range, typename State, typename Context>
        result_type operator()(Range& rng, State const&, Context const&) const
        {
            fusion::for_each(rng, fun);
            return void_();
        }

        Fun const& fun;
    };

}}}

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each_s
        {
            typedef void type;
        };
    }

    template <typename Sequence, typename F>
    inline void
    for_each_s(Sequence& seq, F const& f)
    {
        fusion::segmented_fold_until(seq, void_(), detail::segmented_for_each_fun<F>(f));
    }

    template <typename Sequence, typename F>
    inline void
    for_each_s(Sequence const& seq, F const& f)
    {
        fusion::segmented_fold_until(seq, void_(), detail::segmented_for_each_fun<F>(f));
    }
}}

#endif
