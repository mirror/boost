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
  BOOST_PARAMETER_KEYWORD(keywords,name);
  BOOST_PARAMETER_KEYWORD(keywords,value);
  
  using namespace boost::parameter;

  struct f_parameters
    : parameters<
          optional<
              keywords::name
            , boost::is_convertible<boost::mpl::_, std::string>
          >
        , optional<
              keywords::value
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
  void f(
      A0 const& a0
    , typename f_parameters::restrict<A0 BOOST_PARAMETER_MATCH_ARGS(1)>::type args = f_parameters())
  {
      f_impl(args(a0));
  }

  template<class A0, class A1>
  void f(
      A0 const& a0, A1 const& a1
    , typename f_parameters::restrict<A0, A1 BOOST_PARAMETER_MATCH_ARGS(2)>::type args = f_parameters())
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

