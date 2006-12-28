///////////////////////////////////////////////////////////////////////////////
/// \file fold_to_list.hpp
/// A higher-level transform that uses the fold, branch and list transforms
/// to fold a binary tree into a fusion cons-list.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_TO_LIST_HPP_EAN_12_17_2006
#define BOOST_PROTO_TRANSFORM_FOLD_TO_LIST_HPP_EAN_12_17_2006

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
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
                fold<
                    meta::binary_expr<
                        Tag
                      , fold_to_list_recurse<Tag, Grammar>
                      , fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , list<Grammar>
            >
        {};

        template<typename Tag, typename Grammar>
        struct fold_to_list
          : branch<
                fold<
                    meta::binary_expr<
                        Tag
                      , fold_to_list_recurse<Tag, Grammar>
                      , fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , fusion::nil
            >
        {};

        template<typename Tag, typename Grammar>
        struct reverse_fold_to_list_recurse
          : proto::or_<
                reverse_fold<
                    meta::binary_expr<
                        Tag
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , list<Grammar>
            >
        {};

        template<typename Tag, typename Grammar>
        struct reverse_fold_to_list
          : branch<
                reverse_fold<
                    meta::binary_expr<
                        Tag
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                      , reverse_fold_to_list_recurse<Tag, Grammar>
                    >
                >
              , fusion::nil
            >
        {};

    }

    template<typename Grammar>
    struct fold_to_list
      : detail::fold_to_list<
            typename Grammar::type::tag_type
          , typename Grammar::type::arg0_type
        >
    {
        BOOST_MPL_ASSERT((
            is_same<
                typename Grammar::type::arg0_type
              , typename Grammar::type::arg1_type
            >
        ));
    };

    template<typename Grammar>
    struct reverse_fold_to_list
      : detail::reverse_fold_to_list<
            typename Grammar::type::tag_type
          , typename Grammar::type::arg0_type
        >
    {
        BOOST_MPL_ASSERT((
            is_same<
                typename Grammar::type::arg0_type
              , typename Grammar::type::arg1_type
            >
        ));
    };

}}}

#endif
