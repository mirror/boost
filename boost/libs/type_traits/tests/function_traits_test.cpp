//  (C) Copyright Doug Gregor 2002. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/function_traits.hpp>
#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

template<typename T> 
struct is_int
{ 
  BOOST_STATIC_CONSTANT(bool, value = false);
};

template<> 
struct is_int<int>
{
  BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename T> 
struct is_float
{ 
  BOOST_STATIC_CONSTANT(bool, value = false);
};

template<> 
struct is_float<float>
{
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template<typename T> 
struct is_double
{ 
  BOOST_STATIC_CONSTANT(bool, value = false);
};

template<> 
struct is_double<double>
{
  BOOST_STATIC_CONSTANT(bool, value = true);
};


int test_main(int, char*[])
{
  typedef int F2(float, double);

  typedef boost::function_traits<F2> traits;

  BOOST_TEST(traits::arity == 2);

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  BOOST_TEST(is_int<traits::result_type>::value);
  BOOST_TEST(is_float<traits::arg1_type>::value);
  BOOST_TEST(is_double<traits::arg2_type>::value);
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  return 0;
}
