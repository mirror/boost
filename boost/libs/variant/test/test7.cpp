// File: test7.cpp

#include "boost/test/minimal.hpp"
#include "boost/variant.hpp"

#include "jobs.h"
#include "varout.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <map>


using namespace boost;
using namespace std;



struct jas
{
   jas(int n = 364);
   jas(const jas& other);

   ~jas();
   jas& operator=(const jas& other);

   void swap(jas& other);

   int n_;

   int sn_;
   static int s_inst_id_;
}; 

struct Tracker
{
   typedef map<const jas*,int> table_type;
   typedef table_type::iterator iterator_type;

   static table_type s_this_to_sn_;

   static void insert(const jas& j)
   {
      s_this_to_sn_[&j] = j.sn_;      
      cout << "jas( " << j.sn_ << ") Registered" << endl;
   }
   
   static void remove(const jas& j)
   {
      iterator_type iter = s_this_to_sn_.find(&j);
      BOOST_CHECK(iter != s_this_to_sn_.end());
      BOOST_CHECK( ((*iter).second) == j.sn_);

      int sn = (*iter).second;
      if(sn != j.sn_)
      {
         cout << "Mismatch: this = " << (*iter).first << ", sn_ = " << sn
            << ", other: this = " << &j << ", j.sn_ = " << j.sn_ << endl;
      }

      BOOST_CHECK(sn == j.sn_);

   

      

      s_this_to_sn_.erase(&j);
      cout << "jas( " << j.sn_ << ") Removed" << endl;
   }

   static void check()
   {
      BOOST_CHECK(s_this_to_sn_.empty());      
   }
};

Tracker::table_type Tracker::s_this_to_sn_;



jas::jas(int n) : n_(n) 
{ 
   sn_ = s_inst_id_;
   s_inst_id_ += 1;
      
   Tracker::insert(*this);
}

jas::jas(const jas& other) : n_(other.n_)
{
   sn_ = s_inst_id_;
   s_inst_id_ += 1;      

   Tracker::insert(*this);
}

jas::~jas()
{
   Tracker::remove(*this);
}

jas& jas::operator=(const jas& other)
{
   jas temp(other);
   swap(temp);

   return *this;
}

void jas::swap(jas& other)
{   
   Tracker::remove(*this);
   Tracker::remove(other);

   std::swap(n_, other.n_);
   std::swap(sn_, other.sn_);

   Tracker::insert(*this);
   Tracker::insert(other);
}

int jas::s_inst_id_ = 0;


bool operator==(const jas& a, const jas& b)
{
   return a.n_ == b.n_;
}

ostream& operator<<(ostream& out, const jas& a)
{
   cout << "jas::n_ = " << a.n_;
   return out;
}


template<typename ValueType>
struct compare_helper : boost::static_visitor<bool>
{
   compare_helper(ValueType& expected) : expected_(expected) { }

   bool operator()(const ValueType& value)
   {
      return value == expected_;
   }

   template<typename T>
   bool operator()(const T& )
   {
      return false;         
   }

   ValueType& expected_;

};

template<typename VariantType, typename ExpectedType>
void var_compare(const VariantType& v, ExpectedType expected)
{
   compare_helper<ExpectedType> ch(expected);

   bool checks = boost::apply_visitor(ch, v);
   BOOST_CHECK(checks);
}


void run()
{   
   variant<string, short> v0;

   var_compare(v0, string(""));

   v0 = 8;
   var_compare(v0, static_cast<short>(8));

   v0 = "penny lane";
   var_compare(v0, string("penny lane"));

   variant<jas, string, int> v1, v2 = jas(195);
   var_compare(v1, jas(364));

   v1 = jas(500);
   v1.swap(v2);

   var_compare(v1, jas(195));
   var_compare(v2, jas(500));


   variant<string, int> v3;
   var_compare(v3, string(""));
}


int test_main(int , char* [])
{
   run();
   Tracker::check();

   return 0;
}

