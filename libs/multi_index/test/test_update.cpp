/* Boost.MultiIndex test for replace(), modify() and modify_key().
 *
 * Copyright 2003-2006 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_update.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include "pre_multi_index.hpp"
#include "employee.hpp"
#include "pair_of_ints.hpp"
#include <boost/test/test_tools.hpp>

using namespace boost::multi_index;

void test_update()
{
  employee_set              es;
  employee_set_as_inserted& i=get<as_inserted>(es);
  employee_set_randomly&    r=get<randomly>(es);

  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(1,"Robert",27,5601));
  es.insert(employee(2,"John",40,7889));
  es.insert(employee(3,"Olbert",20,9012));
  es.insert(employee(4,"John",57,1002));

  employee_set::iterator             it=es.find(employee(0,"Joe",31,1123));
  employee_set_as_inserted::iterator it1=
    project<as_inserted>(es,get<name>(es).find("Olbert"));
  employee_set_randomly::iterator    it2=
    project<randomly>(es,get<age>(es).find(57));

  BOOST_CHECK(es.replace(it,*it));
  BOOST_CHECK(!es.replace(it,employee(3,"Joe",31,1123))&&it->id==0);
  BOOST_CHECK(es.replace(it,employee(0,"Joe",32,1123))&&it->age==32);
  BOOST_CHECK(i.replace(it1,employee(3,"Albert",20,9012))&&it1->name==
                "Albert");
  BOOST_CHECK(!r.replace(it2,employee(4,"John",57,5601)));

  {
    typedef multi_index_container<
      pair_of_ints,
      indexed_by<
        ordered_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,first)>,
        hashed_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,second)>,
        sequenced<> > >
    int_int_set;

    int_int_set iis;
    nth_index<int_int_set,1>::type& ii1=get<1>(iis);
    nth_index<int_int_set,2>::type& ii2=get<2>(iis);
    iis.insert(pair_of_ints(0,0));
    iis.insert(pair_of_ints(5,5));
    iis.insert(pair_of_ints(10,10));

    BOOST_CHECK(!iis.replace(iis.begin(),pair_of_ints(5,0)));
    BOOST_CHECK(!ii2.replace(ii2.begin(),pair_of_ints(0,5)));
    BOOST_CHECK(!ii1.replace(project<1>(iis,iis.begin()),pair_of_ints(5,11)));
    BOOST_CHECK(!iis.replace(iis.begin(),pair_of_ints(11,5)));
    BOOST_CHECK(!iis.replace(++iis.begin(),pair_of_ints(10,5)));
    BOOST_CHECK(!ii1.replace(
      project<1>(iis,++iis.begin()),pair_of_ints(5,10)));
    BOOST_CHECK(!iis.replace(--iis.end(),pair_of_ints(5,10)));
    BOOST_CHECK(!ii2.replace(--ii2.end(),pair_of_ints(10,5)));

    BOOST_CHECK(iis.modify(iis.begin(),increment_first));
    BOOST_CHECK(ii2.modify(ii2.begin(),increment_first));
    BOOST_CHECK(ii1.modify(project<1>(iis,iis.begin()),increment_first));
    BOOST_CHECK(ii2.modify(ii2.begin(),increment_first));

    BOOST_CHECK(!iis.modify(iis.begin(),increment_first));
    BOOST_CHECK(iis.size()==2);

    iis.insert(pair_of_ints(0,0));
    BOOST_CHECK(ii2.modify(--ii2.end(),increment_second));
    BOOST_CHECK(iis.modify(iis.begin(),increment_second));
    BOOST_CHECK(ii2.modify(--ii2.end(),increment_second));
    BOOST_CHECK(iis.modify(iis.begin(),increment_second));

    BOOST_CHECK(!ii2.modify(--ii2.end(),increment_second));
    BOOST_CHECK(ii2.size()==2);

    iis.insert(pair_of_ints(0,0));
    BOOST_CHECK(iis.modify_key(iis.begin(),increment_int));
    BOOST_CHECK(iis.modify_key(iis.begin(),increment_int));
    BOOST_CHECK(iis.modify_key(iis.begin(),increment_int));
    BOOST_CHECK(iis.modify_key(iis.begin(),increment_int));

    BOOST_CHECK(!iis.modify_key(iis.begin(),increment_int));
    BOOST_CHECK(iis.size()==2);

    nth_index_iterator<int_int_set,1>::type it=ii1.find(5);
    BOOST_CHECK(ii1.modify_key(it,increment_int));
    BOOST_CHECK(ii1.modify_key(it,increment_int));
    BOOST_CHECK(ii1.modify_key(it,increment_int));
    BOOST_CHECK(ii1.modify_key(it,increment_int));

    BOOST_CHECK(!ii1.modify_key(it,increment_int));
    BOOST_CHECK(ii1.size()==1);
  }
  {
    typedef multi_index_container<
      pair_of_ints,
      indexed_by<
        hashed_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,first)>,
        random_access<>,
        ordered_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,second)> > >
    int_int_set;

    int_int_set iis;
    nth_index<int_int_set,1>::type& ii1=get<1>(iis);
    int_int_set::iterator p1=iis.insert(pair_of_ints(0,0)).first;
    int_int_set::iterator p2=iis.insert(pair_of_ints(5,5)).first;
    int_int_set::iterator p3=iis.insert(pair_of_ints(10,10)).first;

    BOOST_CHECK(!iis.replace(p1,pair_of_ints(5,0)));
    BOOST_CHECK(!ii1.replace(ii1.begin(),pair_of_ints(0,5)));
    BOOST_CHECK(!iis.replace(p1,pair_of_ints(5,11)));
    BOOST_CHECK(!iis.replace(p1,pair_of_ints(11,5)));
    BOOST_CHECK(!iis.replace(p2,pair_of_ints(10,5)));
    BOOST_CHECK(!iis.replace(p2,pair_of_ints(5,10)));
    BOOST_CHECK(!iis.replace(p3,pair_of_ints(5,10)));
    BOOST_CHECK(!ii1.replace(--ii1.end(),pair_of_ints(10,5)));

    BOOST_CHECK(iis.modify(p1,increment_first));
    BOOST_CHECK(ii1.modify(ii1.begin(),increment_first));
    BOOST_CHECK(iis.modify(p1,increment_first));
    BOOST_CHECK(ii1.modify(ii1.begin(),increment_first));

    BOOST_CHECK(!iis.modify(p1,increment_first));
    BOOST_CHECK(iis.size()==2);

    p1=iis.insert(pair_of_ints(0,0)).first;
    BOOST_CHECK(ii1.modify(--ii1.end(),increment_second));
    BOOST_CHECK(iis.modify(p1,increment_second));
    BOOST_CHECK(ii1.modify(--ii1.end(),increment_second));
    BOOST_CHECK(iis.modify(p1,increment_second));

    BOOST_CHECK(!ii1.modify(--ii1.end(),increment_second));
    BOOST_CHECK(ii1.size()==2);
  }
}
