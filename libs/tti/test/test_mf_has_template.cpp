
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_template.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/tti/mf/mf_has_template.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                HaveMStr<_>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template
                <
                BOOST_TTI_HAS_TEMPLATE_GEN(TemplateNotExist)<_>,
                MT_BType<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                BOOST_TTI_HAS_TEMPLATE_GEN(ATPMemberTemplate)<_>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                HaveCL<_>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                BOOST_TTI_HAS_TEMPLATE_GEN(SimpleTMP)<_>,
                boost::mpl::identity<AnotherType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                boost::mpl::quote1<HaveMStr>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template
                <
                boost::mpl::quote1<BOOST_TTI_HAS_TEMPLATE_GEN(TemplateNotExist)>,
                MT_BType<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                boost::mpl::quote1<BOOST_TTI_HAS_TEMPLATE_GEN(ATPMemberTemplate)>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                boost::mpl::quote1<HaveCL>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template
                <
                boost::mpl::quote1<BOOST_TTI_HAS_TEMPLATE_GEN(SimpleTMP)>,
                boost::mpl::identity<AnotherType>
                >
              ::value
            ));
  
  return boost::report_errors();
  
  }
