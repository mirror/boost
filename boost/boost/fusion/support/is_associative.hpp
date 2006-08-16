/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ASSOCIATIVE_09242005_1018)
#define FUSION_IS_ASSOCIATIVE_09242005_1018

#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion {
    namespace extension
    {
      template<typename Tag>
      struct is_associative_impl
      {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
      };
    }

    namespace traits
    {
      template <typename Seq>
      struct is_associative
        : extension::is_associative_impl<typename detail::tag_of<Seq>::type>::template apply<Seq>
      {};
}}}

#endif
