///////////////////////////////////////////////////////////////////////////////
// compile.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_COMPILE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_COMPILE_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/regex_traits.hpp>
#include <boost/xpressive/detail/core/regex_impl.hpp>
#include <boost/xpressive/detail/core/linker.hpp>
#include <boost/xpressive/detail/core/optimize.hpp>
#include <boost/xpressive/detail/core/adaptor.hpp>
#include <boost/xpressive/detail/core/matcher/end_matcher.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/detail/static/productions/visitor.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // static_compile_impl2
    template<typename Xpr, typename BidiIter, typename Traits>
    void static_compile_impl2(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl, Traits const &traits)
    {
        impl->tracking_clear();
        impl->traits_ = new traits_holder<Traits>(traits);

        // "compile" the regex and wrap it in an xpression_adaptor.
        xpression_visitor<BidiIter, mpl::false_, Traits> visitor(traits, impl);
        intrusive_ptr<matchable_ex<BidiIter> const> adxpr = make_adaptor<matchable_ex<BidiIter> >(
            proto::compile(xpr, end_xpression(), visitor, seq_tag()));

        // Link and optimize the regex
        common_compile(adxpr, *impl, visitor.traits());

        // References changed, update dependencies.
        impl->tracking_update();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // static_compile_impl1
    template<typename Xpr, typename BidiIter>
    void static_compile_impl1(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl, mpl::false_)
    {
        // use default traits
        typedef typename iterator_value<BidiIter>::type char_type;
        typedef typename default_regex_traits<char_type>::type traits_type;
        traits_type traits;
        static_compile_impl2(xpr, impl, traits);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // static_compile_impl1
    template<typename Xpr, typename BidiIter>
    void static_compile_impl1(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl, mpl::true_)
    {
        // use specified traits
        typedef typename Xpr::arg0_type::locale_type locale_type;
        typedef typename regex_traits_type<locale_type, BidiIter>::type traits_type;
        static_compile_impl2(proto::right(xpr), impl, traits_type(proto::left(xpr).getloc()));
    }

    template<typename T>
    struct is_locale_modifier
      : mpl::false_
    {};

    template<typename Locale>
    struct is_locale_modifier<locale_modifier<Locale> >
      : mpl::true_
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // static_compile
    template<typename Xpr, typename BidiIter>
    void static_compile(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl)
    {
        typedef mpl::and_<
            is_same<modifier_tag, typename Xpr::tag_type>
          , is_locale_modifier<typename proto::meta::unref<typename Xpr::arg0_type>::type>
        > is_imbued;

        static_compile_impl1(xpr, impl, is_imbued());
    }

}}} // namespace boost::xpressive::detail

#endif
