/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DETAIL_IS_MPL_SEQUENCE_15122005_2137)
#define FUSION_DETAIL_IS_MPL_SEQUENCE_15122005_2137

#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int_fwd.hpp>
#include <boost/mpl/long_fwd.hpp>
#include <boost/mpl/size_t_fwd.hpp>
#include <boost/mpl/integral_c_fwd.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
    struct mpl_int_detect
    {
        template <int N>
        mpl_int_detect(mpl::int_<N>) {}

        template <bool B>
        mpl_int_detect(mpl::bool_<B>) {}

        template <typename T, T N>
        mpl_int_detect(mpl::integral_c<T, N>) {}

        template <long N>
        mpl_int_detect(mpl::long_<N>) {}

        template <std::size_t N>
        mpl_int_detect(mpl::size_t<N>) {}
    };
    
    template <typename T>
    struct is_mpl_sequence
        : mpl::and_<
            mpl::not_<is_convertible<T, mpl_int_detect> >
          , mpl::not_<is_base_of<sequence_root, T> >
          , mpl::is_sequence<T> >
    {};
}}}

#endif
