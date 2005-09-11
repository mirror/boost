// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter.hpp>
#include <boost/parameter/match.hpp>
#include <cassert>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <string>

namespace test
{
  using namespace boost::parameter;
  namespace mpl = boost::mpl;

  BOOST_PARAMETER_KEYWORD(tag, name)
  BOOST_PARAMETER_KEYWORD(tag, value)

  struct g_parameters
    : parameters<
          unnamed<tag::name, boost::is_convertible<mpl::_, std::string> >
        , unnamed<tag::value, boost::is_convertible<mpl::_, float> >
      >
  {};


  // Keeping this out here avoids an ICE with vc-6.x
  std::string const foo("foo");
  
  template<class Params>
  int g_(Params const& p)
  {
      assert(p[name] == foo);
      assert(p[value] == 3.14f);
      return 1;
  }
  
  template<class A0>
  int g(A0 const& a0, BOOST_PARAMETER_MATCH(g_parameters, (A0), args))
  {
      return g_(args(a0));
  }
  
  template<class A0, class A1>
  int g(A0 const& a0, A1 const& a1, BOOST_PARAMETER_MATCH(g_parameters, (A0)(A1), args))
  {
      return g_(args(a0, a1));
  }

}

#include <typeinfo>
#include <iostream>

int main()
{
   using test::g;
   using test::name;
   using test::value;

   g("foo", 3.14f);
   g(3.14f, "foo");

   g(value = 3.14f, "foo");
   g(name = "foo", 3.14f);
   g(3.14f, name = "foo");
   g(name = "foo", value = 3.14f);
   
   return 0;
}

