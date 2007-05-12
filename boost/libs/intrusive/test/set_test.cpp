/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#include <boost/intrusive/set.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include "itestvalue.hpp"
#include "smart_ptr.hpp"
#include "common_functors.hpp"
#include <vector>
#include <boost/detail/lightweight_test.hpp>
#include "test_macros.hpp"

using namespace boost::intrusive;

template<class ValueTraits>
struct test_set 
{
   typedef typename ValueTraits::value_type value_type;
   static void test_all(std::vector<value_type>& values);
   static void test_sort(std::vector<value_type>& values);
   static void test_insert(std::vector<value_type>& values);
   static void test_swap(std::vector<value_type>& values);
   static void test_find(std::vector<value_type>& values);
   static void test_impl();
   static void test_clone(std::vector<value_type>& values);
};

template<class ValueTraits>
void test_set<ValueTraits>::test_all(std::vector<typename ValueTraits::value_type>& values)
{
   test_sort(values);
   test_insert(values);
   test_swap(values);
   test_find(values);
   test_impl();
   test_clone(values);
}

//test case due to an error in tree implementation:
template<class ValueTraits>
void test_set<ValueTraits>::test_impl()
{
   typedef typename ValueTraits::value_type testvalue_t;
   std::vector<testvalue_t> values (5);
   for (int i = 0; i < 5; ++i)
      values[i].value_ = i; 

   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;
   set_type testset;
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
void test_set<ValueTraits>::test_sort(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;
   set_type testset1 (values.begin(), values.end());
   {  int init_values [] = { 1, 2, 3, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset1.begin() );  }

   testset1.clear();
   BOOST_TEST (testset1.empty());

   typedef boost::intrusive::set
      <ValueTraits
      ,even_odd
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type2;
   set_type2 testset2 (&values[0], &values[0] + 6);
   {  int init_values [] = { 5, 3, 1, 4, 2 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset2.rbegin() );  }
   BOOST_TEST (testset2.begin()->value_ == 2);
   BOOST_TEST (testset2.rbegin()->value_ == 5);
}  
  
//test: insert, const_iterator, const_reverse_iterator, erase, iterator_to:
template<class ValueTraits>
void test_set<ValueTraits>::test_insert(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;
   set_type testset;
   testset.insert(&values[0] + 2, &values[0] + 5);

   const set_type& const_testset = testset;
   {  int init_values [] = { 1, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, const_testset.begin() );  }

   typename set_type::iterator i = testset.begin();
   BOOST_TEST (i->value_ == 1);

   i = testset.insert (i, values[0]);
   BOOST_TEST (&*i == &values[0]);

   {  int init_values [] = { 5, 4, 3, 1 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset.rbegin() );  }

   i = testset.iterator_to (values[2]);
   BOOST_TEST (&*i == &values[2]);

   testset.erase (i);
   {  int init_values [] = { 1, 3, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testset.begin() );  }
}  

//test: insert (seq-version), swap, erase (seq-version), size:
template<class ValueTraits>
void test_set<ValueTraits>::test_swap(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;
   set_type testset1 (&values[0], &values[0] + 2);
   set_type testset2;
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

//test: find, equal_range (lower_bound, upper_bound):
template<class ValueTraits>
void test_set<ValueTraits>::test_find(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;
   set_type testset (values.begin(), values.end());
   typedef typename set_type::iterator iterator;

   testvalue_t cmp_val;
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
void test_set<ValueTraits>
   ::test_clone(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::set
      <ValueTraits
      ,std::less<typename ValueTraits::value_type>
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > set_type;

      set_type testset1 (&values[0], &values[0] + values.size());
      set_type testset2;

      testset2.clone_from(testset1, test::new_cloner(), test::delete_destroyer());
      BOOST_TEST (testset2 == testset1);
      testset2.clear_and_destroy(test::delete_destroyer());
      BOOST_TEST (testset2.empty());
}

template<class VoidPointer, bool constant_time_size>
class test_main_template
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, constant_time_size> testvalue_t;
      static const int random_init[6] = { 3, 2, 4, 1, 5, 2 };
      std::vector<testvalue<VoidPointer, constant_time_size> > data (6);
      for (int i = 0; i < 6; ++i)
         data[i].value_ = random_init[i]; 

      test_set <typename testvalue_t::set_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_set <typename testvalue_t::set_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::set_node_> >::test_all(data);

      return 0;
   }
};

template<class VoidPointer>
class test_main_template<VoidPointer, false>
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, false> testvalue_t;
      static const int random_init[6] = { 3, 2, 4, 1, 5, 2 };
      std::vector<testvalue<VoidPointer, false> > data (6);
      for (int i = 0; i < 6; ++i)
         data[i].value_ = random_init[i]; 

      test_set <typename testvalue_t::set_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_set <typename testvalue_t::set_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::set_node_> >::test_all(data);

      test_set <typename testvalue_t::set_auto_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_set <typename testvalue_t::set_auto_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::set_auto_node_> >::test_all(data);
      return 0;
   }
};
/*
//Explicit instantiations of non-counted classes
template class boost::intrusive::set
   <set_base_raw, std::less<set_base_raw::value_type>, false>;
template class boost::intrusive::set
   <set_member_raw, std::less<set_member_raw::value_type>, false>;
template class boost::intrusive::set
   <set_auto_base_raw, std::less<set_auto_base_raw::value_type>, false>;
template class boost::intrusive::set
   <set_auto_member_raw, std::less<set_auto_member_raw::value_type>, false>;
template class boost::intrusive::set
   <set_base_smart, std::less<set_base_smart::value_type>, false>;
template class boost::intrusive::set
   <set_member_smart, std::less<set_member_smart::value_type>, false>;
template class boost::intrusive::set
   <set_auto_base_smart, std::less<set_auto_base_smart::value_type>, false>;
template class boost::intrusive::set
   <set_auto_member_smart, std::less<set_auto_member_smart::value_type>, false>;

//Explicit instantiation of counted classes
template class boost::intrusive::set
   <set_base_raw_t, std::less<set_base_raw_t::value_type>, true>;
template class boost::intrusive::set
   <set_member_raw_t, std::less<set_member_raw_t::value_type>, true>;
template class boost::intrusive::set
   <set_base_smart_t, std::less<set_base_smart_t::value_type>, true>;
template class boost::intrusive::set
   <set_member_smart_t, std::less<set_member_smart_t::value_type>, true>;
*/
int main( int, char* [] ) 
{
   test_main_template<void*, false>()();
   test_main_template<boost::intrusive::smart_ptr<void>, false>()();
   test_main_template<void*, true>()();
   test_main_template<boost::intrusive::smart_ptr<void>, true>()();
   return boost::report_errors();
}
