/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/sg_set.hpp>
#include "itestvalue.hpp"
#include "smart_ptr.hpp"
#include "generic_set_test.hpp"

namespace boost { namespace intrusive { namespace test {

template<class T, class O1, class O2, class O3, class O4>
struct has_rebalance<boost::intrusive::sg_set<T, O1, O2, O3, O4> >
{
   static const bool value = true;
};

}}}

template< class ValueType
        , class Option1 = boost::intrusive::none
        , class Option2 = boost::intrusive::none
        , class Option3 = boost::intrusive::none
        >
struct GetContainer
{
   typedef boost::intrusive::sg_set
      < ValueType
      , Option1
      , Option2
      , Option3
      > type;
};

template< class ValueType
        , class Option1 = boost::intrusive::none
        , class Option2 = boost::intrusive::none
        , class Option3 = boost::intrusive::none
        >
struct GetContainerFixedAlpha
{
   typedef boost::intrusive::sg_set
      < ValueType
      , Option1
      , Option2
      , Option3
      , boost::intrusive::floating_point<false>
      > type;
};

template<class VoidPointer>
class test_main_template
{
   public:
   int operator()()
   {
      using namespace boost::intrusive;
      typedef testvalue<VoidPointer, true> value_type;

      test::test_generic_set < typename detail::get_base_value_traits
                  < value_type
                  , typename value_type::bs_set_base_hook_t
                  >::type
                , GetContainer
                >::test_all();
      test::test_generic_set < typename detail::get_member_value_traits
                  < value_type
                  , member_hook< value_type
                               , typename value_type::bs_set_member_hook_t
                               , &value_type::sg_set_node_
                               >
                  >::type
                , GetContainer
                >::test_all();

      test::test_generic_set < typename detail::get_base_value_traits
                  < value_type
                  , typename value_type::bs_set_base_hook_t
                  >::type
                , GetContainerFixedAlpha
                >::test_all();
      test::test_generic_set < typename detail::get_member_value_traits
                  < value_type
                  , member_hook< value_type
                               , typename value_type::bs_set_member_hook_t
                               , &value_type::sg_set_node_
                               >
                  >::type
                , GetContainerFixedAlpha
                >::test_all();
      return 0;
   }
};

int main( int, char* [] ) 
{
   test_main_template<void*>()();
   test_main_template<boost::intrusive::smart_ptr<void> >()();
   return boost::report_errors();
}
#include <boost/intrusive/detail/config_end.hpp>
