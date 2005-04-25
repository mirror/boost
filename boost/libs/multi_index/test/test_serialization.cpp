/* Boost.MultiIndex test for serialization.
 *
 * Copyright 2003-2005 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_serialization.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "pre_multi_index.hpp"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/noncopyable.hpp>
#include <boost/test/test_tools.hpp>
#include <sstream>
#include <string>
#include <vector>
#include "pair_of_ints.hpp"

using namespace boost::multi_index;

template<int N>
struct all_indices_equal_helper
{
  template<class MultiIndexContainer>
  static bool compare(
    const MultiIndexContainer& m1,const MultiIndexContainer& m2)
  {
    if(!(get<N>(m1)==get<N>(m2))){
      return false;
    }
    return all_indices_equal_helper<N-1>::compare(m1,m2);
  }
};

template<>
struct all_indices_equal_helper<0>
{
  template<class MultiIndexContainer>
  static bool compare(
    const MultiIndexContainer& m1,const MultiIndexContainer& m2)
  {
    return true;
  }
};

template<class MultiIndexContainer>
bool all_indices_equal(
  const MultiIndexContainer& m1,const MultiIndexContainer& m2)
{
  BOOST_STATIC_CONSTANT(int,
    N=boost::mpl::size<
    BOOST_DEDUCED_TYPENAME MultiIndexContainer::index_type_list>::type::value);

  return all_indices_equal_helper<N-1>::compare(m1,m2);
}

template<class MultiIndexContainer>
void test_serialization(const MultiIndexContainer& m)
{
  typedef typename MultiIndexContainer::iterator       iterator;
  typedef typename MultiIndexContainer::const_iterator const_iterator;

  std::ostringstream oss;
  {
    boost::archive::text_oarchive oa(oss);
    oa<<m;

    std::vector<const_iterator> its(m.size());
    const_iterator              it_end=m.end();
    for(const_iterator it=m.begin();it!=it_end;++it){
      its.push_back(it);
      oa<<const_cast<const const_iterator&>(its.back());
    }
    oa<<const_cast<const const_iterator&>(it_end);
  }

  MultiIndexContainer m2;
  std::istringstream iss(oss.str());
  boost::archive::text_iarchive ia(iss);
  ia>>m2;
  BOOST_CHECK(all_indices_equal(m,m2));

  iterator it_end=m2.end();
  for(iterator it=m2.begin();it!=it_end;++it){
    iterator it2;
    ia>>it2;
    BOOST_CHECK(it==it2);

    /* exercise safe mode with this (unchecked) iterator */
    BOOST_CHECK(*it==*it2);
    m2.erase(it,it2);
    m2.erase(it2,it2);
    m2.erase(it2,it);
    iterator it3(++it2);
    iterator it4;
    it4=--it2;
    BOOST_CHECK(it==it4);
    BOOST_CHECK(it==project<0>(m2,it4));
  }
  iterator it2;
  ia>>it2;
  BOOST_CHECK(it_end==it2);
  BOOST_CHECK(it_end==project<0>(m2,it2));
}

void test_hashed_index_serialization()
{
  const int N=100;
  const int SHUFFLE=10232;

  typedef multi_index_container<
    int,
    indexed_by<
      hashed_unique<identity<int> >,
      sequenced<>
    >
  > hashed_set;

  typedef hashed_set::iterator       iterator;
  typedef hashed_set::local_iterator local_iterator;

  hashed_set hs;

  for(int i=0;i<N;++i){
    hs.insert(i*SHUFFLE);
  }

  std::ostringstream oss;
  {
    boost::archive::text_oarchive oa(oss);
    oa<<const_cast<const hashed_set&>(hs);

    std::vector<iterator> its(N);
    for(int i=0;i<N;++i){
      iterator it=hs.find(i*SHUFFLE);
      its.push_back(it);
      oa<<const_cast<const iterator&>(its.back());
    }
    iterator it=hs.end();
    oa<<const_cast<const iterator&>(it);

    std::vector<local_iterator> lits(2*N);
    for(std::size_t buc=0;buc<hs.bucket_count();++buc){
      for(local_iterator lit=hs.begin(buc),lit_end=hs.end(buc);
          lit!=lit_end;++lit){
        oa<<*lit;
        lits.push_back(lit);
        oa<<const_cast<const local_iterator&>(lits.back());
      }
      local_iterator lit2=hs.end(buc);
      lits.push_back(lit2);
      oa<<const_cast<const local_iterator&>(lits.back());
    }
  }

  hashed_set hs2;
  std::istringstream iss(oss.str());
  boost::archive::text_iarchive ia(iss);
  ia>>hs2;
  BOOST_CHECK(get<1>(hs)==get<1>(hs2));

  for(int j=0;j<N;++j){
    iterator it;
    ia>>it;
    BOOST_CHECK(*it==j*SHUFFLE);
  }
  iterator it;
  ia>>it;
  BOOST_CHECK(it==hs2.end());

  for(std::size_t buc=0;buc<hs2.bucket_count();++buc){
    for(std::size_t k=0;k<hs2.bucket_size(buc);++k){
      int n;
      local_iterator it;
      ia>>n;
      ia>>it;
      BOOST_CHECK(*it==n);
    }
    local_iterator it2;
    ia>>it2;
    BOOST_CHECK(it2==hs2.end(buc));
  }
}

void test_serialization()
{
  {
    typedef multi_index_container<
      int,
      indexed_by<
        sequenced<>,
        sequenced<>
      >
    > multi_index_t;

    multi_index_t m;
    for(int i=0;i<100;++i)m.push_back(i);
    m.reverse();
    test_serialization(m);

    m.clear();
    for(int j=50;j<100;++j)m.push_back(j);
    for(int k=0;k<50;++k)m.push_back(k);
    m.sort();
    test_serialization(m);
  }
  {
    typedef multi_index_container<
      int,
      indexed_by<
        sequenced<>,
        ordered_non_unique<identity<int> >
      >
    > multi_index_t;

    multi_index_t m;
    for(int i=0;i<100;++i){
      m.push_back(i);
      m.push_back(i);
      m.push_back(i);
    }
    m.reverse();
    test_serialization(m);
  }
  {
    typedef multi_index_container<
      pair_of_ints,
      indexed_by<
        ordered_unique<
          BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,first)
        >,
        ordered_non_unique<
          BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,second)
        >,
        sequenced<>
      >
    > multi_index_t;

    multi_index_t m;
    test_serialization(m);

    m.insert(pair_of_ints(4,0));
    test_serialization(m);

    m.insert(pair_of_ints(3,1));
    m.insert(pair_of_ints(2,1));
    test_serialization(m);

    m.insert(pair_of_ints(1,1));
    test_serialization(m);

    m.insert(pair_of_ints(0,0));
    test_serialization(m);

    m.insert(pair_of_ints(5,1));
    m.insert(pair_of_ints(7,1));
    m.insert(pair_of_ints(6,1));
    test_serialization(m);
    
    m.insert(pair_of_ints(8,1));
    m.insert(pair_of_ints(9,1));
    m.insert(pair_of_ints(12,1));
    m.insert(pair_of_ints(11,1));
    m.insert(pair_of_ints(10,1));
    test_serialization(m);
  }
  test_hashed_index_serialization();
}
