
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_fun.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/tti/mf/mf_has_member_function.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)<_,_>,
                boost::mpl::identity<AType>,
                void
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                FunctionReturningInt<_,_>,
                boost::mpl::identity<AType>,
                int
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                FunctionReturningInt<_,_,_>,
                boost::mpl::identity<AnotherType>,
                double,
                boost::mpl::vector<int>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)<_,_,_>,
                boost::mpl::identity<AnotherType>,
                boost::mpl::identity<AType>,
                boost::mpl::vector<int>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                AnotherIntFunction<_,_,_>,
                boost::mpl::identity<AnotherType>,
                int,
                boost::mpl::vector<boost::mpl::identity<AType> >
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)<_,_,_>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>,
                boost::mpl::vector
                  <
                  int,
                  long,
                  double
                  >
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)>,
                boost::mpl::identity<AType>,
                void
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<FunctionReturningInt>,
                boost::mpl::identity<AType>,
                int
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<FunctionReturningInt>,
                boost::mpl::identity<AnotherType>,
                double,
                boost::mpl::vector<int>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)>,
                boost::mpl::identity<AnotherType>,
                boost::mpl::identity<AType>,
                boost::mpl::vector<int>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<AnotherIntFunction>,
                boost::mpl::identity<AnotherType>,
                int,
                boost::mpl::vector<boost::mpl::identity<AType> >
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_function
                <
                boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>,
                boost::mpl::vector
                  <
                  int,
                  long,
                  double
                  >
                >
              ::value
            ));
  
  return boost::report_errors();

  }
