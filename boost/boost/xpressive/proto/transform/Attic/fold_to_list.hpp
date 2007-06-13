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

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/transform/list.hpp>
#include <boost/xpressive/proto/transform/branch.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto { namespace transform
{

    namespace detail
    {
        template<typename Tag, typename Grammar>
        struct fold_tree_
          : or_<
                trans::fold<
                    nary_expr<Tag, vararg<fold_tree_<Tag, Grammar> > >
                >
              , Grammar
            >
        {};

        template<typename Tag, typename Grammar>
        struct reverse_fold_tree_
          : or_<
                trans::reverse_fold<
                    nary_expr<Tag, vararg<reverse_fold_tree_<Tag, Grammar> > >
                >
              , Grammar
            >
        {};
    }

    /// fold_tree
    ///
    template<typename Tag, typename Grammar, typename State = void>
    struct fold_tree
      : trans::branch<
            trans::fold<
                nary_expr<Tag, vararg<detail::fold_tree_<Tag, Grammar> > >
            >
          , State
        >
    {};

    template<typename Tag, typename Grammar>
    struct fold_tree<Tag, Grammar, void>
      : trans::fold<
            nary_expr<Tag, vararg<detail::fold_tree_<Tag, Grammar> > >
        >
    {};

    /// reverse_fold_tree
    ///
    template<typename Tag, typename Grammar, typename State = void>
    struct reverse_fold_tree
      : trans::branch<
            trans::reverse_fold<
                nary_expr<Tag, vararg<detail::reverse_fold_tree_<Tag, Grammar> > >
            >
          , State
        >
    {};

    template<typename Tag, typename Grammar>
    struct reverse_fold_tree<Tag, Grammar, void>
      : trans::reverse_fold<
            nary_expr<Tag, vararg<detail::reverse_fold_tree_<Tag, Grammar> > >
        >
    {};

    /// fold_to_list
    /// TODO Find a cleaner interface
    template<typename Grammar>
    struct fold_to_list
      : fold_tree<
            typename Grammar::tag_type
          , trans::list<typename Grammar::arg0_type>
          , fusion::nil
        >
    {
        BOOST_MPL_ASSERT((
            is_same<
                typename Grammar::arg0_type
              , typename Grammar::arg1_type
            >
        ));
    };

    /// reverse_fold_to_list
    /// TODO Find a cleaner interface
    template<typename Grammar>
    struct reverse_fold_to_list
      : reverse_fold_tree<
            typename Grammar::tag_type
          , trans::list<typename Grammar::arg0_type>
          , fusion::nil
        >
    {
        BOOST_MPL_ASSERT((
            is_same<
                typename Grammar::arg0_type
              , typename Grammar::arg1_type
            >
        ));
    };

}}}

#endif
