// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/parameter.hpp>
#include <cassert>
#include <string>
#include <boost/type_traits/is_convertible.hpp>
#include <iostream>

namespace test
{
  using namespace boost::parameter;

  keyword<struct name_> name;
  keyword<struct value_> value;
  
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
  
  template<class A0>
  void f(A0 const& a0
      , typename f_parameters::restrict<A0>::type args = f_parameters())
  {
      f_impl(args(a0));
  }

  template<class A0, class A1>
  void f(A0 const& a0, A1 const& a1
      , typename f_parameters::restrict<A0, A1>::type args = f_parameters())
  {
      f_impl(args(a0, a1));
  }

} // namespace test

int main()
{
    using test::name;
    using test::value;    
    using test::f;

    f("foo");
    f("foo", 3.f);
    f(value = 3.f, name = "foo");

    return 0;
}

