///////////////////////////////////////////////////////////////////////////////
// fold_to_xxx.hpp
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_FOLD_TO_XXX_HPP_EAN_04_01_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_FOLD_TO_XXX_HPP_EAN_04_01_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/matches.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<typename Tag, typename Grammar, template<typename> class Generator>
    struct fold_to_xxx_recurse
      : proto::or_<
            proto::transform::fold<
                proto::binary_expr<
                    Tag
                  , fold_to_xxx_recurse<Tag, Grammar, Generator>
                  , fold_to_xxx_recurse<Tag, Grammar, Generator>
                >
            >
          , Generator<Grammar>
        >
    {};

    template<typename Tag, typename Grammar, template<typename> class Generator>
    struct fold_to_xxx
      : proto::transform::fold<
            proto::binary_expr<
                Tag
              , fold_to_xxx_recurse<Tag, Grammar, Generator>
              , fold_to_xxx_recurse<Tag, Grammar, Generator>
            >
        >
    {};

    template<typename Tag, typename Grammar, template<typename> class Generator>
    struct reverse_fold_to_xxx_recurse
      : proto::or_<
            proto::transform::reverse_fold<
                proto::binary_expr<
                    Tag
                  , reverse_fold_to_xxx_recurse<Tag, Grammar, Generator>
                  , reverse_fold_to_xxx_recurse<Tag, Grammar, Generator>
                >
            >
          , Generator<Grammar>
        >
    {};

    template<typename Tag, typename Grammar, template<typename> class Generator>
    struct reverse_fold_to_xxx
      : proto::transform::reverse_fold<
            proto::binary_expr<
                Tag
              , reverse_fold_to_xxx_recurse<Tag, Grammar, Generator>
              , reverse_fold_to_xxx_recurse<Tag, Grammar, Generator>
            >
        >
    {};

}}}

#endif
