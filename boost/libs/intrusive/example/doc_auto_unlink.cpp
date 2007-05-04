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
//[doc_auto_unlink_code
#include <boost/intrusive/list.hpp>
#include <cassert>

using namespace boost::intrusive;

class MyClass  :  public list_base_hook<tag, auto_unlink>
               //This hook removes the node in the destructor
{
   int int_;

   public:
   MyClass(int i = 0)   :  int_(i)  {}
   void unlink()     {  list_base_hook<tag, auto_unlink>::unlink();  }
   bool is_linked()     {  return list_base_hook<tag, auto_unlink>::is_linked();  }
   int get() const   {  return int_;  }
};

//Define a list that will store MyClass
//using the public base hook
//The list can't have constant-time size!
typedef list< list_base_hook<tag, auto_unlink>::
   value_traits<MyClass>, false >   List;

int main()
{
   //Create the list
   List list;
   {
      //Create myclass and check it's linked
      MyClass myclass;
      assert(myclass.is_linked() == false);

      //Insert the object
      list.push_back(myclass);

      //Check that we have inserted the object
      assert(list.empty() == false);
      assert(&list.front() == &myclass);
      assert(myclass.is_linked() == true);

      //Now myclass' destructor will unlink it
      //automatically
   }

   //Check auto-unlink has been executed
   assert(list.empty() == true);

   {
      //Now test the unlink() function

      //Create myclass and check it's linked
      MyClass myclass;
      assert(myclass.is_linked() == false);

      //Insert the object
      list.push_back(myclass);

      //Check that we have inserted the object
      assert(list.empty() == false);
      assert(&list.front() == &myclass);
      assert(myclass.is_linked() == true);

      //Now unlink the node
      myclass.unlink();

      //Check auto-unlink has been executed
      assert(list.empty() == true);
   }
   return 0;
}
//]
