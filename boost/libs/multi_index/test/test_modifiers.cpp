/* Boost.MultiIndex test for modifier memfuns.
 *
 * Copyright 2003-2005 Joaquín M López Muñoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_modifiers.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <vector>
#include "pre_multi_index.hpp"
#include "employee.hpp"
#include <boost/test/test_tools.hpp>

using namespace boost::multi_index;

void test_modifiers()
{
  employee_set              es;
  employee_set_by_name&     i1=get<name>(es);
  employee_set_by_age&      i2=get<age>(es);
  employee_set_as_inserted& i3=get<as_inserted>(es);
  employee_set_by_ssn&      i4=get<ssn>(es);

  es.insert(employee(0,"Joe",31,1123));
  BOOST_CHECK(es.insert(employee(0,"Joe",31,1123)).second==false);
  BOOST_CHECK(i1.insert(employee(0,"Joe Jr.",5,2563)).second==false);
  BOOST_CHECK(i2.insert(employee(1,"Victor",5,1123)).second==false);
  BOOST_CHECK(i3.insert(i3.begin(),employee(1,"Victor",5,1123)).second
                ==false);
  BOOST_CHECK(i3.push_front(employee(0,"Joe Jr.",5,2563)).second==false);
  BOOST_CHECK(i3.push_back(employee(0,"Joe Jr.",5,2563)).second==false);

  employee_set_by_name::iterator it1=i1.find("Joe");
  i1.insert(it1,employee(1,"Joe Jr.",5,2563));
  BOOST_CHECK(es.size()==2);

  employee_set_by_age::iterator it2=i2.find(31);
  i2.insert(it2,employee(2,"Grandda Joe",64,7881));
  BOOST_CHECK(es.size()==3);

  employee_set_as_inserted::iterator it3=i3.begin();
  i3.insert(it3,100,employee(3,"Judy",39,6201));
  BOOST_CHECK(es.size()==4);

  es.erase(employee(1,"Joe Jr.",5,2563));
  BOOST_CHECK(i2.size()==3&&i3.size()==3);

  i1.erase("Judy");
  BOOST_CHECK(es.size()==2&&i2.size()==2);

  i2.erase(it2);
  BOOST_CHECK(es.size()==1&&i1.size()==1);

  i3.pop_front();
  BOOST_CHECK(es.size()==0&&i2.size()==0);

  es.insert(employee(0,"Joe",31,1123));
  i1.erase(i1.begin());
  BOOST_CHECK(i1.size()==0);

  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(1,"Jack",31,5032));
  i2.erase(31);
  BOOST_CHECK(i2.size()==0);

  i3.push_front(employee(1,"Jack",31,5032));
  i3.push_back(employee(0,"Joe",31,1123));
  BOOST_CHECK(i3.front()==employee(1,"Jack",31,5032));
  BOOST_CHECK(i3.back()==employee(0,"Joe",31,1123));

  i3.pop_back();
  BOOST_CHECK(i3.back()==employee(1,"Jack",31,5032));
  BOOST_CHECK(es.size()==1);

  i3.pop_front();
  BOOST_CHECK(es.size()==0);

  std::vector<employee> ve;
  ve.push_back(employee(3,"Anna",31,5388));
  ve.push_back(employee(1,"Rachel",27,9012));
  ve.push_back(employee(2,"Agatha",40,1520));

  i1.insert(ve.begin(),ve.end());
  BOOST_CHECK(i2.size()==3);

  i4.erase(i4.begin(),i4.end());
  BOOST_CHECK(es.size()==0);

  i2.insert(ve.begin(),ve.end());
  BOOST_CHECK(i3.size()==3);

  BOOST_CHECK(*(i3.erase(i3.begin()))==employee(1,"Rachel",27,9012));
  BOOST_CHECK(i3.erase(i3.begin(),i3.end())==i3.end());
  BOOST_CHECK(es.size()==0);

  i3.insert(i3.end(),ve.begin(),ve.end());
  BOOST_CHECK(es.size()==3);

  es.erase(es.begin(),es.end());
  BOOST_CHECK(i2.size()==0);

  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(1,"Robert",27,5601));
  es.insert(employee(2,"John",40,7889));
  es.insert(employee(3,"Albert",20,9012));
  es.insert(employee(4,"John",57,1002));

  employee_set es_backup(es);

  employee_set es2;
  es2.insert(employee(3,"Anna",31,5388));
  es2.insert(employee(1,"Rachel",27,9012));
  es2.insert(employee(2,"Agatha",40,1520));

  employee_set es2_backup(es2);

  i1.swap(get<1>(es2));
  BOOST_CHECK(es==es2_backup&&es2==es_backup);

  i2.swap(get<2>(es2));
  BOOST_CHECK(es==es_backup&&es2==es2_backup);

  i3.swap(get<3>(es2));
  BOOST_CHECK(es==es2_backup&&es2==es_backup);

#if defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  ::boost::multi_index::detail::swap(i1,get<1>(es2));
#else
  using std::swap;
  swap(i1,get<1>(es2));
#endif

  BOOST_CHECK(es==es_backup&&es2==es2_backup);

#if defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  ::boost::multi_index::detail::swap(i2,get<2>(es2));
#else
  using std::swap;
  swap(i2,get<2>(es2));
#endif

  BOOST_CHECK(es==es2_backup&&es2==es_backup);

#if defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  ::boost::multi_index::detail::swap(i3,get<3>(es2));
#else
  using std::swap;
  swap(i3,get<3>(es2));
#endif

  BOOST_CHECK(es==es_backup&&es2==es2_backup);

  i3.clear();
  BOOST_CHECK(i3.size()==0);

  es=es2;
  i4.clear();
  BOOST_CHECK(i4.size()==0);

  es2.clear();
  BOOST_CHECK(es2.size()==0);
}
