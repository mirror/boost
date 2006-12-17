///////////////////////////////////////////////////////////////////////////////
/// \file fold.hpp
/// A higher-level transform that uses the fold, branch and list transforms
/// to fold a binary tree into a fusion cons-list.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_TO_LIST_HPP_EAN_12_17_2006
#define BOOST_PROTO_TRANSFORM_FOLD_TO_LIST_HPP_EAN_12_17_2006

#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/transform/list.hpp>
#include <boost/xpressive/proto/transform/branch.hpp>

namespace boost { namespace proto { namespace transform
{

    namespace detail
    {
        template<typename Tag, typename Grammar>
        struct fold_to_list_recurse
          : proto::or_<
                proto::trans::fold<
                    proto::meta::binary_expr<
                        Tag
                      , fold_to_list_recurse<Tag, Grammar>
                      , fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , proto::trans::list<Grammar>
            >
        {};

        template<typename Tag, typename Grammar>
        struct reverse_fold_to_list_recurse
          : proto::or_<
                proto::trans::reverse_fold<
                    proto::meta::binary_expr<
                        Tag
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , proto::trans::list<Grammar>
            >
        {};
    }

    template<typename Tag, typename Grammar>
    struct fold_to_list
      : proto::trans::branch<
            proto::trans::fold<
                proto::meta::binary_expr<
                    Tag
                  , detail::fold_to_list_recurse<Tag, Grammar>
                  , detail::fold_to_list_recurse<Tag, Grammar>
                >
            >
          , fusion::nil
        >
    {};

    template<typename Tag, typename Grammar>
    struct reverse_fold_to_list
      : proto::trans::branch<
            proto::trans::reverse_fold<
                proto::meta::binary_expr<
                    Tag
                  , detail::reverse_fold_to_list_recurse<Tag, Grammar>
                  , detail::reverse_fold_to_list_recurse<Tag, Grammar>
                >
            >
          , fusion::nil
        >
    {};

}}}

#endif
