/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//[doc_unordered_set_code
#include <boost/intrusive/unordered_set.hpp>
#include <vector>
#include <algorithm>
#include <boost/functional/hash.hpp>

using namespace boost::intrusive;

                  //This is a derivation hook
class MyClass  :  public unordered_set_base_hook<>
{
   int int_;

   public:
   //This is a member hook
   unordered_set_member_hook<> member_hook_;

   MyClass(int i)
      :  int_(i)
   {}

   int get() const
   {  return int_;  }

   friend bool operator== (const MyClass &a, const MyClass &b)
   {  return a.get() == b.get();  }

   friend bool operator> (const MyClass &a, const MyClass &b)
   {  return a.get() > b.get();  }
};

std::size_t hash_value(const MyClass &value)
{  return std::size_t(value.get()); }

//Define an unordered_set that will store MyClass
//in reverse order using the public base hook
typedef unordered_set< unordered_set_base_hook<>::
                  value_traits<MyClass> >    BaseSet;

//Define an unordered_multiset that will store MyClass
//using the public member hook
typedef unordered_multiset< unordered_set_member_hook<>::
                       value_traits<MyClass, &MyClass::member_hook_> >  MemberMultiSet;

int main()
{
   typedef std::vector<MyClass> Vect;
   typedef Vect::iterator VectIt;
   typedef Vect::reverse_iterator VectRit;

   //Create a vector with 100 different MyClass objects,
   //each one with a different internal number
   Vect myclassvector;
   for(int i = 0; i < 100; ++i)
      myclassvector.push_back(MyClass(i));

   //Create a copy of the vector
   Vect myclassvector2(myclassvector);

   //Create a bucket array for base_set
   BaseSet::bucket_type base_buckets[100];

   //Create a bucket array for member_multi_set
   MemberMultiSet::bucket_type member_buckets[200];

   //Create a the unordered_set and unordered_multiset,
   //taking buckets as arguments
   BaseSet base_set(base_buckets, 100);
   MemberMultiSet member_multi_set(member_buckets, 200);

   //Now insert myclassvector's elements in the unordered_set
   for(VectIt it(myclassvector.begin()), itend(myclassvector.end())
      ; it != itend; ++it){
      base_set.insert(*it);
   }

   //Now insert myclassvector's and myclassvector2's elements in the unordered_multiset
   for(VectIt it(myclassvector.begin()), itend(myclassvector.end()),
             it2(myclassvector2.begin()),itend2(myclassvector2.end())
      ; it != itend; ++it, ++it2){
      member_multi_set.insert(*it);
      member_multi_set.insert(*it2);
   }

   //Now find every element
   {
      VectIt it(myclassvector.begin()), itend(myclassvector.end());

      for(; it != itend; ++it){
         //base_set should contain one element for each key
         if(base_set.count(*it) != 1)           return 1;
         //member_multi_set should contain two elements for each key
         if(member_multi_set.count(*it) != 2)   return 1;
      }
   }
   return 0;
}
//]

