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
//[doc_slist_code
#include <boost/intrusive/slist.hpp>
#include <vector>

using namespace boost::intrusive;

                  //This is a base hook
class MyClass  :  public slist_base_hook<>
{
   int int_;

   public:
   //This is a member hook
   slist_member_hook<> member_hook_;

   MyClass(int i)
      :  int_(i)
   {}

   int get() const
   {  return int_;  }
};

//Define an slist that will store MyClass using the public base hook
typedef slist< slist_base_hook<>::value_traits<MyClass> > BaseList;

//Define an slist that will store MyClass using the public member hook
typedef slist< slist_member_hook<>::value_traits<MyClass, &MyClass::member_hook_> > MemberList;

int main()
{
   typedef std::vector<MyClass> Vect;
   typedef Vect::iterator VectIt;
   typedef Vect::reverse_iterator VectRit;

   //Create several MyClass objects, each one
   //with a different internal number
   Vect myclassvector;
   for(int i = 0; i < 100; ++i)
      myclassvector.push_back(MyClass(i));

   BaseList baselist;
   MemberList memberlist;

   //Now insert them in the reverse order
   //in the base hook intrusive list
   for(VectIt it(myclassvector.begin()), itend(myclassvector.end())
      ; it != itend
      ; ++it){
      baselist.push_front(*it);
   }

   //Now insert them in the same order as in vector in the
   //member hook intrusive list
   for(BaseList::iterator it(baselist.begin()), itend(baselist.end())
      ; it != itend
      ; ++it){
      memberlist.push_front(*it);
   }

   //Now test lists
   {
      BaseList::iterator bit(baselist.begin()), bitend(baselist.end());
      MemberList::iterator mit(memberlist.begin()), mitend(memberlist.end());
      VectRit rit(myclassvector.rbegin()), ritend(myclassvector.rend());
      VectIt  it(myclassvector.begin()), itend(myclassvector.end());

      //Test the objects inserted in the base hook list
      for(; rit != ritend; ++rit, ++bit){
         if(&*bit != &*rit)   return 1;
      }

      //Test the objects inserted in the member hook list
      for(; it != itend; ++it, ++mit){
         if(&*mit != &*it)    return 1;
      }
   }

   return 0;
}
//]
