/* Boost.MultiIndex test for serialization, part 2.
 *
 * Copyright 2003-2006 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_serialization.hpp"
#include "test_serialization_template.hpp"

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include "pair_of_ints.hpp"

using namespace boost::multi_index;

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

void test_serialization2()
{
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
        random_access<>,
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

    /* testcase for bug reported at
     * http://lists.boost.org/boost-users/2006/05/19362.php
     */

    m.clear();
    m.insert(pair_of_ints(0,0));
    m.insert(pair_of_ints(1,0));
    m.insert(pair_of_ints(2,1));
    m.insert(pair_of_ints(4,2));
    m.insert(pair_of_ints(3,2));
    test_serialization(m);
  }
  test_hashed_index_serialization();
}
