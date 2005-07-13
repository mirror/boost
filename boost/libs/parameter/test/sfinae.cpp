// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/parameter.hpp>
#include <cassert>
#include <string>
#include <boost/type_traits/is_convertible.hpp>
#include <iostream>

#ifndef BOOST_NO_SFINAE
# include <boost/utility/enable_if.hpp>
# include <boost/type_traits/is_same.hpp>
#endif 

namespace test
{
  using namespace boost::parameter;

  struct name_;
  struct value_;

#if !(BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__GNUC__, == 2))
  namespace
  {
    keyword<name_>& name = instance();
    keyword<value_>& value = instance();
  }
#else
  namespace
  {
    keyword<name_>& name = keyword<name_>::get();
    keyword<value_>& value = keyword<value_>::get();
  }
# if BOOST_WORKAROUND(BOOST_MSVC, == 1200)
  using test::name;  // required for vc6 :(
  using test::value;
# endif 
#endif

  
  struct f_parameters
    : parameters<
          optional<
              name_
            , boost::is_convertible<boost::mpl::_, std::string>
          >
        , optional<
              value_
            , boost::is_convertible<boost::mpl::_, float>
          >
      >
  {};

  template <class T> struct not_implemented;
  
  template<class P>
  void f_impl(P const& p)
  {
      std::string s = p[name | "bar"];
      float v = p[value | 3.f];

      assert(s == "foo");
      assert(v == 3.f);
  }

  void f()
  {
      f_impl(f_parameters()());
  }

  using boost::parameter::aux::void_;
  
  template<class A0>
  void f(A0 const& a0
         , typename f_parameters::restrict<A0
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
         ,void_,void_,void_,void_
#endif 
         >::type args = f_parameters())
  {
      f_impl(args(a0));
  }

  template<class A0, class A1>
  void f(A0 const& a0, A1 const& a1
      , typename f_parameters::restrict<A0, A1
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
         ,void_,void_,void_
#endif 
         >::type args = f_parameters())
  {
      f_impl(args(a0, a1));
  }

#ifndef BOOST_NO_SFINAE
  // On compilers that actually support SFINAE, add another overload
  // that is an equally good match and can only be in the overload set
  // when the others are not.  This tests that the SFINAE is actually
  // working.  On all other compilers we're just checking that
  // everything about SFINAE-enabled code will work, except of course
  // the SFINAE.
  template<class A0, class A1>
  typename boost::enable_if<boost::is_same<int,A0>, int>::type
  f(A0 const& a0, A1 const& a1)
  {
      return 0;
  }
#endif 
} // namespace test

int main()
{
    using test::name;
    using test::value;    
    using test::f;

    f("foo");
    f("foo", 3.f);
    f(value = 3.f, name = "foo");

#ifndef BOOST_NO_SFINAE
    return f(3, 4);
#else 
    return 0;
#endif 
}

