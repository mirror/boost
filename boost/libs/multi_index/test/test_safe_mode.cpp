/* Boost.MultiIndex test for safe_mode.
 *
 * Copyright 2003-2005 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_safe_mode.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include "pre_multi_index.hpp"
#include "employee.hpp"
#include "pair_of_ints.hpp"
#include <stdexcept>
#include <boost/test/test_tools.hpp>

using namespace boost::multi_index;

#define TRY_SAFE_MODE \
try{

#define CATCH_SAFE_MODE(err) \
  throw std::runtime_error("safe mode violation not detected");\
}catch(const safe_mode_exception& e){\
  if(e.error_code!=(err))throw std::runtime_error(\
    "safe mode violation not expected");\
}

struct change_id
{
  change_id(int new_id_):new_id(new_id_){}
  void operator()(employee& e){e.id=new_id;}

private:
  int new_id;
};

struct change_ssn
{
  change_ssn(int new_ssn_):new_ssn(new_ssn_){}
  void operator()(employee& e){e.ssn=new_ssn;}

private:
  int new_ssn;
};

typedef multi_index_container<
  pair_of_ints,
  indexed_by<
    ordered_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,first)>,
    ordered_unique<BOOST_MULTI_INDEX_MEMBER(pair_of_ints,int,second)> > >
int_int_set;

void test_safe_mode()
{
  employee_set es,es2;
  employee_set_by_name& i1=get<name>(es);
  employee_set_by_name& i2=get<name>(es2);
  employee_set_as_inserted& ii=get<as_inserted>(es);
  es.insert(employee(0,"Joe",31,1123));

  TRY_SAFE_MODE
    employee_set::iterator it;
    employee_set::iterator it2=es.begin();
    it2=it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    employee_set_by_name::iterator it2=i1.begin();
    it2=it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it;
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)
  
  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.end();
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::not_dereferenceable_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.end();
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::not_dereferenceable_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.end();
    ++it;
  CATCH_SAFE_MODE(safe_mode::not_incrementable_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.end();
    ++it;
  CATCH_SAFE_MODE(safe_mode::not_incrementable_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.begin();
    --it;
  CATCH_SAFE_MODE(safe_mode::not_decrementable_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it;
    employee_set::iterator it2;
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    employee_set_by_name::iterator it2;
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.begin();
    employee_set::iterator it2;
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.begin();
    employee_set_by_name::iterator it2;
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.begin();
    employee_set::iterator it2=es2.begin();
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::not_same_owner)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.begin();
    employee_set_by_name::iterator it2=i2.begin();
    bool b=(it==it2);
    b=true; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::not_same_owner)

  TRY_SAFE_MODE
    es.erase(es.end(),es.begin());
  CATCH_SAFE_MODE(safe_mode::invalid_range)

  TRY_SAFE_MODE
    i1.erase(i1.end(),i1.begin());
  CATCH_SAFE_MODE(safe_mode::invalid_range)

  TRY_SAFE_MODE
    employee_set::iterator it;
    es.insert(it,employee(0,"Joe",31,1123));
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    i1.insert(it,employee(0,"Joe",31,1123));
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    es.erase(es.end());
  CATCH_SAFE_MODE(safe_mode::not_dereferenceable_iterator)

  TRY_SAFE_MODE
    i1.erase(i1.end());
  CATCH_SAFE_MODE(safe_mode::not_dereferenceable_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.begin();
    es2.insert(it,employee(0,"Joe",31,1123));
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.begin();
    i2.insert(it,employee(0,"Joe",31,1123));
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set::iterator it=es.begin();
    employee_set::iterator it2=es2.end();
    es2.erase(it,it2);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=i1.begin();
    employee_set_by_name::iterator it2=i2.end();
    i2.erase(it,it2);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set::iterator it=es.insert(employee(1,"Robert",27,5601)).first;
    es.erase(it);
    es.erase(it);
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=
      i1.insert(employee(1,"Robert",27,5601)).first;
    i1.erase(it);
    i1.erase(it);
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set es3(es);
    employee_set::iterator it=es3.insert(employee(1,"Robert",27,5601)).first;
    es3.clear();
    es3.erase(it);
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set es3(es);
    employee_set_by_name::iterator it=
      get<name>(es3).insert(employee(1,"Robert",27,5601)).first;
    get<name>(es3).clear();
    get<name>(es3).erase(it);
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it;
    {
      employee_set es3;
      it=es3.insert(employee(0,"Joe",31,1123)).first;
    }
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    {
      employee_set es3;
      it=get<name>(es3).insert(employee(0,"Joe",31,1123)).first;
    }
    employee e=*it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it;
    {
      employee_set es3;
      it=es3.insert(employee(0,"Joe",31,1123)).first;
    }
    employee_set::iterator it2;
    it2=it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it;
    {
      employee_set es3;
      it=get<name>(es3).insert(employee(0,"Joe",31,1123)).first;
    }
    employee_set_by_name::iterator it2;
    it2=it;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set es3(es);
    employee_set es4;
    employee_set::iterator it=es3.begin();
    es3.swap(es4);
    es3.erase(it);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set es3(es);
    employee_set es4;
    employee_set_by_name::iterator it=get<name>(es3).begin();
    es3.swap(es4);
    get<name>(es3).erase(it);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  /* these, unlike the previous case, are indeed correct, test safe mode
   * gets it right
   */
  { 
    employee_set es3(es);
    employee_set es4;
    employee_set::iterator it=es3.begin();
    es3.swap(es4);
    es4.erase(it);
  }

  { 
    employee_set es3(es);
    employee_set es4;
    employee_set_by_name::iterator it=get<name>(es3).begin();
    es3.swap(es4);
    get<name>(es4).erase(it);
  }

  TRY_SAFE_MODE
    employee_set::iterator it=es.insert(employee(1,"Robert",27,5601)).first;
    employee_set_by_name::iterator it2=project<name>(es,it);
    es.modify_key(it,change_id(0));
    employee e=*it2;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=
      i1.insert(employee(1,"Robert",27,5601)).first;
    employee_set::iterator it2=project<0>(es,it);
    i1.modify(it,change_ssn(1123));
    employee e=*it2;
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    int_int_set iis;
    int_int_set::iterator it=iis.insert(pair_of_ints(0,0)).first;
    iis.insert(pair_of_ints(1,1));
    iis.modify(it,increment_first);
    pair_of_ints p=*it;
    p.first=0; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    int_int_set iis;
    int_int_set::iterator it=iis.insert(pair_of_ints(0,0)).first;
    iis.insert(pair_of_ints(1,1));
    iis.modify(it,increment_second);
    pair_of_ints p=*it;
    p.first=0; /* avoid warning about unused var */
  CATCH_SAFE_MODE(safe_mode::invalid_iterator)

  TRY_SAFE_MODE
    employee_set::iterator it=es.end();
    employee_set_by_name::iterator it2=project<name>(es2,it);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    employee_set_by_name::iterator it=get<name>(es).end();
    employee_set::iterator it2=project<0>(es2,it);
  CATCH_SAFE_MODE(safe_mode::not_owner)

  TRY_SAFE_MODE
    ii.splice(ii.begin(),ii,ii.begin(),ii.end());
  CATCH_SAFE_MODE(safe_mode::inside_range)

  TRY_SAFE_MODE
    ii.splice(ii.begin(),ii);
  CATCH_SAFE_MODE(safe_mode::same_container)
}
