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
#include <boost/intrusive/splay_set.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include "itestvalue.hpp"
#include "smart_ptr.hpp"
#include "common_functors.hpp"
#include <vector>
#include <boost/detail/lightweight_test.hpp>
#include "test_macros.hpp"
#include "test_container.hpp"
#include <set>

namespace boost { namespace intrusive { namespace test {

template<class T, class O1, class O2, class O3, class O4>
struct has_const_overloads<boost::intrusive::splay_set<T, O1, O2, O3, O4> >
{
   static const bool value = false;
};

}}}

using namespace boost::intrusive;

template<class ValueTraits>
struct test_splay_set 
{
   typedef typename ValueTraits::value_type value_type;
   static void test_all(std::vector<value_type>& values);
   static void test_sort(std::vector<value_type>& values);
   static void test_insert(std::vector<value_type>& values);
   static void test_swap(std::vector<value_type>& values);
   static void test_find(std::vector<value_type>& values);
   static void test_splay_up(std::vector<value_type>& values);
   static void test_splay_down(std::vector<value_type>& values);
   static void test_impl();
   static void test_clone(std::vector<value_type>& values);
   static void test_container_from_end(std::vector<value_type>& values);
};

template<class ValueTraits>
void test_splay_set<ValueTraits>::test_all(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   {
      splay_set_type testset(values.begin(), values.end());
      test::test_container(testset);
      testset.clear();
      testset.insert(values.begin(), values.end());
      test::test_common_unordered_and_associative_container(testset, values);
      testset.clear();
      testset.insert(values.begin(), values.end());
      test::test_associative_container(testset, values);
      testset.clear();
      testset.insert(values.begin(), values.end());
      test::test_unique_container(testset, values);
   }

   test_sort(values);
   test_insert(values);
   test_swap(values);
   test_find(values);
   test_splay_up(values);
   test_splay_down(values);
   test_impl();
   test_clone(values);
   test_container_from_end(values);
}

//test case due to an error in tree implementation:
template<class ValueTraits>
void test_splay_set<ValueTraits>::test_impl()
{
   typedef typename ValueTraits::value_type value_type;
   std::vector<value_type> values (5);
   for (int i = 0; i < 5; ++i)
      values[i].value_ = i; 

   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset;
   for (int i = 0; i < 5; ++i)
      testset.insert (values[i]);

   testset.erase (testset.iterator_to (values[0]));
   testset.erase (testset.iterator_to (values[1]));
   testset.insert (values[1]);
     
   testset.erase (testset.iterator_to (values[2]));
   testset.erase (testset.iterator_to (values[3]));
}

//test: constructor, iterator, clear, reverse_iterator, front, back, size:
template<class ValueTraits>
void test_splay_set<ValueTraits>::test_sort(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset1 (values.begin(), values.end());
   {  int init_values [] = { 1, 2, 3, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset1.begin() );  }

   testset1.clear();
   BOOST_TEST (testset1.empty());

   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , compare<even_odd>
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > set_type2;
   set_type2 testset2 (&values[0], &values[0] + 6);
   {  int init_values [] = { 5, 3, 1, 4, 2 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset2.rbegin() );  }
   BOOST_TEST (testset2.begin()->value_ == 2);
   BOOST_TEST (testset2.rbegin()->value_ == 5);
}  
  
//test: insert, const_iterator, const_reverse_iterator, erase, s_iterator_to:
template<class ValueTraits>
void test_splay_set<ValueTraits>::test_insert(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset;
   testset.insert(&values[0] + 2, &values[0] + 5);

   const splay_set_type& const_testset = testset;
   {  int init_values [] = { 1, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, const_testset.begin() );  }

   typename splay_set_type::iterator i = testset.begin();
   BOOST_TEST (i->value_ == 1);

   i = testset.insert (i, values[0]);
   BOOST_TEST (&*i == &values[0]);

   {  int init_values [] = { 5, 4, 3, 1 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset.rbegin() );  }

   i = testset.iterator_to (values[2]);
   BOOST_TEST (&*i == &values[2]);

   i = splay_set_type::s_iterator_to(values[2]);
   BOOST_TEST (&*i == &values[2]);

   testset.erase (i);
   {  int init_values [] = { 1, 3, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset.begin() );  }
}  

//test: insert (seq-version), swap, erase (seq-version), size:
template<class ValueTraits>
void test_splay_set<ValueTraits>::test_swap(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset1 (&values[0], &values[0] + 2);
   splay_set_type testset2;
   testset2.insert (&values[0] + 2, &values[0] + 6);
   testset1.swap (testset2);

   {  int init_values [] = { 1, 2, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset1.begin() );  }

   {  int init_values [] = { 2, 3 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset2.begin() );  }

   testset1.erase (testset1.iterator_to(values[5]), testset1.end());
   BOOST_TEST (testset1.size() == 1);
   //  BOOST_TEST (&testset1.front() == &values[3]);
   BOOST_TEST (&*testset1.begin() == &values[3]);
}

template<class ValueTraits>
void test_splay_set<ValueTraits>::test_splay_up
(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , size_type<std::size_t>
      , constant_time_size<value_type::constant_time_size>
      > set_type;
   typedef typename set_type::iterator iterator;
   typedef std::set<value_type> orig_set_t;
   std::size_t num_values;
   std::set<value_type> original_testset (values.begin(), values.end());
   num_values = original_testset.size();

   for(std::size_t i = 0; i != num_values; ++i){
      set_type testset (values.begin(), values.end());
      {
         iterator it = testset.begin();
         for(std::size_t j = 0; j != i; ++j, ++it){}
         testset.splay_up(it);
      }
      BOOST_TEST (testset.size() == num_values);
      iterator it = testset.begin();
      for( typename orig_set_t::const_iterator origit    = original_testset.begin()
         , origitend = original_testset.end()
         ; origit != origitend
         ; ++origit, ++it){
         BOOST_TEST(*origit == *it);
      }
   }
}

template<class ValueTraits>
void test_splay_set<ValueTraits>::test_splay_down
(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , size_type<std::size_t>
      , constant_time_size<value_type::constant_time_size>
      > set_type;
   typedef typename set_type::iterator iterator;
   typedef std::set<value_type> orig_set_t;
   std::size_t num_values;
   std::set<value_type> original_testset (values.begin(), values.end());
   num_values = original_testset.size();

   for(std::size_t i = 0; i != num_values; ++i){
      set_type testset (values.begin(), values.end());
      BOOST_TEST(testset.size() == num_values);
      {
         iterator it = testset.begin();
         for(std::size_t j = 0; j != i; ++j, ++it){}
         BOOST_TEST(*it == *testset.splay_down(*it));
      }
      BOOST_TEST (testset.size() == num_values);
      iterator it = testset.begin();
      for( typename orig_set_t::const_iterator origit    = original_testset.begin()
         , origitend = original_testset.end()
         ; origit != origitend
         ; ++origit, ++it){
         BOOST_TEST(*origit == *it);
      }
   }
}

//test: find, equal_range (lower_bound, upper_bound):
template<class ValueTraits>
void test_splay_set<ValueTraits>::test_find(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset (values.begin(), values.end());
   typedef typename splay_set_type::iterator iterator;

   value_type cmp_val;
   cmp_val.value_ = 2;
   iterator i = testset.find (cmp_val);
   BOOST_TEST (i->value_ == 2);
   BOOST_TEST ((++i)->value_ != 2);
   std::pair<iterator,iterator> range = testset.equal_range (cmp_val);
     
   BOOST_TEST (range.first->value_ == 2);
   BOOST_TEST (range.second->value_ == 3);
   BOOST_TEST (std::distance (range.first, range.second) == 1);

   cmp_val.value_ = 7;
   BOOST_TEST (testset.find (cmp_val) == testset.end());
} 

template<class ValueTraits>
void test_splay_set<ValueTraits>
   ::test_clone(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;

   splay_set_type testset1 (&values[0], &values[0] + values.size());
   splay_set_type testset2;

   testset2.clone_from(testset1, test::new_cloner<value_type>(), test::delete_disposer<value_type>());
   BOOST_TEST (testset2 == testset1);
   testset2.clear_and_dispose(test::delete_disposer<value_type>());
   BOOST_TEST (testset2.empty());
}

template<class ValueTraits>
void test_splay_set<ValueTraits>
   ::test_container_from_end(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type value_type;
   typedef splay_set
      < value_type
      , value_traits<ValueTraits>
      , constant_time_size<value_type::constant_time_size>
      > splay_set_type;
   splay_set_type testset (&values[0], &values[0] + values.size());
   BOOST_TEST (testset == splay_set_type::container_from_end_iterator(testset.end()));
   BOOST_TEST (testset == splay_set_type::container_from_end_iterator(testset.cend()));
}

template<class VoidPointer, bool constant_time_size>
class test_main_template
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, constant_time_size> value_type;
      static const int random_init[6] = { 3, 2, 4, 1, 5, 2 };
      std::vector<testvalue<VoidPointer, constant_time_size> > data (6);
      for (int i = 0; i < 6; ++i)
         data[i].value_ = random_init[i]; 

      test_splay_set < typename detail::get_base_value_traits
                  < value_type
                  , typename value_type::splay_set_base_hook_t
                  >::type
                >::test_all(data);
      test_splay_set < typename detail::get_member_value_traits
                  < value_type
                  , member_hook< value_type
                               , typename value_type::splay_set_member_hook_t
                               , &value_type::splay_set_node_
                               >
                  >::type
                >::test_all(data);
      return 0;
   }
};

template<class VoidPointer>
class test_main_template<VoidPointer, false>
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, false> value_type;
      static const int random_init[6] = { 3, 2, 4, 1, 5, 2 };
      std::vector<testvalue<VoidPointer, false> > data (6);
      for (int i = 0; i < 6; ++i)
         data[i].value_ = random_init[i]; 

      test_splay_set < typename detail::get_base_value_traits
                  < value_type
                  , typename value_type::splay_set_base_hook_t
                  >::type
                >::test_all(data);

      test_splay_set < typename detail::get_member_value_traits
                  < value_type
                  , member_hook< value_type
                               , typename value_type::splay_set_member_hook_t
                               , &value_type::splay_set_node_
                               >
                  >::type
                >::test_all(data);

      test_splay_set < typename detail::get_base_value_traits
                  < value_type
                  , typename value_type::splay_set_auto_base_hook_t
                  >::type
                >::test_all(data);

      test_splay_set < typename detail::get_member_value_traits
                  < value_type
                  , member_hook< value_type
                               , typename value_type::splay_set_auto_member_hook_t
                               , &value_type::splay_set_auto_node_
                               >
                  >::type
                >::test_all(data);

      return 0;
   }
};

int main( int, char* [] ) 
{
   test_main_template<void*, false>()();
   test_main_template<smart_ptr<void>, false>()();
   test_main_template<void*, true>()();
   test_main_template<smart_ptr<void>, true>()();
   return boost::report_errors();
}
#include <boost/intrusive/detail/config_end.hpp>
