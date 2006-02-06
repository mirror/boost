/* Boost.MultiIndex test for standard list operations.
 *
 * Copyright 2003-2006 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_list_ops.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <vector>
#include "pre_multi_index.hpp"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/test/test_tools.hpp>

using namespace boost::multi_index;

#undef _
#define _ ,

#undef CHECK_EQUAL
#define CHECK_EQUAL(p,check_range) \
{\
  int v[]=check_range;\
  std::size_t size_v=sizeof(v)/sizeof(int);\
  BOOST_CHECK(std::size_t(std::distance((p).begin(),(p).end()))==size_v);\
  BOOST_CHECK(std::equal((p).begin(),(p).end(),v));\
}

#undef CHECK_VOID_RANGE
#define CHECK_VOID_RANGE(p) BOOST_CHECK((p).first==(p).second)

struct is_even
{
  bool operator()(int x)const{return x%2==0;}
};

template <int m>
struct same_integral_div
{
  bool operator()(int x,int y)const{return (x/m)==(y/m);}
};

template <typename Container,typename Compare>
bool is_sorted(
  const Container& c,const Compare& comp=Compare())
{
  if(c.empty())return true;

  typedef typename Container::const_iterator const_iterator;
  for(const_iterator it(c.begin());;){
    const_iterator it2=it;
    ++it2;
    if(it2==c.end())return true;
    if(comp(*it2,*it))return false;
    it=it2;
  }
}

template<typename Sequence>
static void test_list_ops_unique_seq(BOOST_EXPLICIT_TEMPLATE_TYPE(Sequence))
{
  typedef typename nth_index<Sequence,1>::type sequenced_index;

  Sequence         ss,ss2;
  sequenced_index &si=get<1>(ss),&si2=get<1>(ss2);

  si.push_front(0);                       /* 0        */
  si.push_front(4);                       /* 40       */
  ss.insert(2);                           /* 402      */
  ss.insert(5);                           /* 4025     */
  si.push_front(3);                       /* 34025    */
  si.push_back(6);                        /* 340256   */
  si.push_back(1);                        /* 3402561  */
  si.insert(project<1>(ss,ss.find(2)),8); /* 34082561 */
  si2=si;

  CHECK_EQUAL(si,{3 _ 4 _ 0 _ 8 _ 2 _ 5 _ 6 _ 1});

  si.remove(8);
  CHECK_EQUAL(si,{3 _ 4 _ 0 _ 2 _ 5 _ 6 _ 1});

  si.remove_if(is_even());

  CHECK_EQUAL(si,{3 _ 5 _ 1});

  si.splice(si.end(),si2);
  CHECK_EQUAL(si,{3 _ 5 _ 1 _ 4 _ 0 _ 8 _ 2 _ 6});
  CHECK_EQUAL(si2,{3 _ 5 _ 1});

  si.splice(project<1>(ss,ss.find(4)),si,project<1>(ss,ss.find(8)));
  CHECK_EQUAL(si,{3 _ 5 _ 1 _ 8 _ 4 _ 0 _ 2 _ 6});
  si2.clear();
  si2.splice(si2.begin(),si,si.begin());

  si.splice(si.end(),si2,si2.begin());
  CHECK_EQUAL(si,{5 _ 1 _ 8 _ 4 _ 0 _ 2 _ 6 _ 3});
  BOOST_CHECK(si2.empty());

  si2.splice(si2.end(),si,project<1>(ss,ss.find(0)),project<1>(ss,ss.find(6)));
  CHECK_EQUAL(si,{5 _ 1 _ 8 _ 4 _ 6 _ 3});
  CHECK_EQUAL(si2,{0 _ 2});

  si.splice(si.begin(),si,si.begin(),si.begin());
  CHECK_EQUAL(si,{5 _ 1 _ 8 _ 4 _ 6 _ 3});

  si.splice(project<1>(ss,ss.find(8)),si,project<1>(ss,ss.find(4)),si.end());
  CHECK_EQUAL(si,{5 _ 1 _ 4 _ 6 _ 3 _ 8});

  si.sort();
  si2.sort();
  BOOST_CHECK(is_sorted(si,std::less<int>()));
  BOOST_CHECK(is_sorted(si2,std::less<int>()));

  si.merge(si2);
  BOOST_CHECK(is_sorted(si,std::less<int>()));
  BOOST_CHECK(si2.empty());

  {
    Sequence         ss3(ss);
    sequenced_index &si3=get<1>(ss3);

    si3.sort(std::greater<int>());
    si.reverse();
    BOOST_CHECK(si==si3);
  }

  si2.splice(si2.end(),si,project<1>(ss,ss.find(6)),project<1>(ss,ss.find(3)));
  CHECK_EQUAL(si2,{6 _ 5 _ 4});

  si.merge(si2,std::greater<int>());
  BOOST_CHECK(is_sorted(si,std::greater<int>()));
  BOOST_CHECK(si2.empty());
}

template<typename Sequence>
static void test_list_ops_non_unique_seq(
  BOOST_EXPLICIT_TEMPLATE_TYPE(Sequence))
{
  typedef typename Sequence::iterator iterator;

  Sequence ss;
  for(int i=0;i<10;++i){
    ss.push_back(i);
    ss.push_back(i);
    ss.push_front(i);
    ss.push_front(i);
  } /* 9988776655443322110000112233445566778899 */

  ss.unique();
  CHECK_EQUAL(
    ss,
    {9 _ 8 _ 7 _ 6 _ 5 _ 4 _ 3 _ 2 _ 1 _ 0 _
     1 _ 2 _ 3 _ 4 _ 5 _ 6 _ 7 _ 8 _ 9});

  iterator it=ss.begin();
  for(int j=0;j<9;++j,++it){} /* it points to o */

  Sequence ss2;
  ss2.splice(ss2.end(),ss,ss.begin(),it);
  ss2.reverse();
  ss.merge(ss2);
  CHECK_EQUAL(
    ss,
    {0 _ 1 _ 1 _ 2 _ 2 _ 3 _ 3 _ 4 _ 4 _ 5 _ 5 _
     6 _ 6 _ 7 _ 7 _ 8 _ 8 _ 9 _ 9});

  ss.unique(same_integral_div<3>());
  CHECK_EQUAL(ss,{0 _ 3 _ 6 _ 9});

  ss.unique(same_integral_div<1>());
  CHECK_EQUAL(ss,{0 _ 3 _ 6 _ 9});
}

void test_list_ops()
{
  typedef multi_index_container<
    int,
    indexed_by<
      ordered_unique<identity<int> >,
      sequenced<>
    >
  > sequenced_set;
  
  /* MSVC++ 6.0 chokes on test_list_ops_unique_seq without this
   * explicit instantiation
   */
  sequenced_set ss;
  test_list_ops_unique_seq<sequenced_set>();


  typedef multi_index_container<
    int,
    indexed_by<
      ordered_unique<identity<int> >,
      random_access<>
    >
  > random_access_set;
  
  random_access_set rs;
  test_list_ops_unique_seq<random_access_set>();

  typedef multi_index_container<
    int,
    indexed_by<sequenced<> >
  > int_list;

  int_list il;
  test_list_ops_non_unique_seq<int_list>();

  typedef multi_index_container<
    int,
    indexed_by<random_access<> >
  > int_vector;

  int_vector iv;
  test_list_ops_non_unique_seq<int_vector>();
}
