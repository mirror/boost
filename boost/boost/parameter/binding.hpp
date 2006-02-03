// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARAMETER_BINDING_DWA200558_HPP
# define BOOST_PARAMETER_BINDING_DWA200558_HPP

# include <boost/mpl/apply.hpp>
# include <boost/mpl/assert.hpp>
# include <boost/mpl/and.hpp>
# include <boost/parameter/aux_/result_of0.hpp>
# include <boost/parameter/aux_/void.hpp>
#  include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { 

// A metafunction that, given an argument pack, returns the type of
// the parameter identified by the given keyword.  If no such
// parameter has been specified, returns Default
template <class Parameters, class Keyword, class Default = void_>
# if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
struct binding
# else
struct binding_eti
# endif
{
    typedef typename mpl::apply_wrap2<
        typename Parameters::binding,Keyword,Default
    >::type type;

    BOOST_MPL_ASSERT_NOT((
        mpl::and_<
            is_same<Default, void_>
          , is_same<type, void_>
        >
    ));
};

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
template <class Parameters, class Keyword, class Default = void_>
struct binding
{
    typedef typename mpl::eval_if<
        is_same<Parameters, int>
      , mpl::identity<int>
      , binding_eti<Parameters, Keyword, Default>
    >::type type;
};
# endif

// A metafunction that, given an argument pack, returns the type of
// the parameter identified by the given keyword.  If no such
// parameter has been specified, returns the type returned by invoking
// DefaultFn
template <class Parameters, class Keyword, class DefaultFn>
struct lazy_binding
{
  typedef typename mpl::apply_wrap2<
      typename Parameters::binding
    , Keyword
    , typename aux::result_of0<DefaultFn>::type
  >::type type;
};


}} // namespace boost::parameter

#endif // BOOST_PARAMETER_BINDING_DWA200558_HPP
