// Copyright David Abrahams 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef STATIC_ASSERT_SAME_DWA2003530_HPP
# define STATIC_ASSERT_SAME_DWA2003530_HPP

# include <boost/type.hpp>

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, class U>
struct static_assert_same;

template <class T>
struct static_assert_same<T,T>
{
    enum { value = 1 };
};
#else
# include <boost/mpl/if.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/type_traits/is_same.hpp>

template <class T, class U>
struct static_assert_same
    : boost::mpl::if_<boost::is_same<T,U>,boost::mpl::true_,void>::type
{};
#endif

#endif // STATIC_ASSERT_SAME_DWA2003530_HPP
