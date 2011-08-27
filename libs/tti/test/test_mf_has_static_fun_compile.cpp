
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_static_fun.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/tti/mf/mf_has_static_member_function.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_static_member_function
    <
    HaveTheSIntFunction<_,_,_>,
    boost::mpl::identity<AType>,
    int,
    boost::mpl::vector
      <
      long,
      short
      >
    > aVar;
  
  boost::tti::mf_has_static_member_function
    <
    boost::mpl::quote4<Pickedname>,
    boost::mpl::identity<AType>,
    double,
    boost::mpl::vector<float>
    > aVar2;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      HaveTheSIntFunction<_,_,_>,
                      boost::mpl::identity<AType>,
                      int,
                      boost::mpl::vector
                        <
                        long,
                        double
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      TheTIntFunction<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector
                        <
                        long,
                        double
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_GEN(TSFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>,
                      boost::mpl::vector
                        <
                        NameIntType<AType>,
                        double
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      boost::mpl::quote4<HaveTheSIntFunction>,
                      boost::mpl::identity<AType>,
                      int,
                      boost::mpl::vector
                        <
                        long,
                        double
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      boost::mpl::quote4<TheTIntFunction>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector
                        <
                        long,
                        double
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      boost::mpl::quote4<BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_GEN(TSFunction)>,
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>,
                      boost::mpl::vector
                        <
                        NameIntType<AType>,
                        double
                        >
                      >
            ));
  
  return 0;

  }
