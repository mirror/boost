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
//[doc_erasing_and_destroying
#include <boost/intrusive/list.hpp>

//A class that can be inserted in an intrusive list
class my_class 
   :  public boost::intrusive::list_base_hook<>
{
   public:
   my_class(int i)
      :  int_(i)
   {}

   int int_;
   //...
};

//Definition of the intrusive list
typedef boost::intrusive::list< my_class::value_traits<my_class> > my_class_list;

//The predicate function
class is_even
{
   public:
   bool operator()(const my_class &c) const
   {  return 0 == (c.int_ % 2);  }
};

//The destroyer object function
class delete_destroyer
{
   public:
   void operator()(my_class *delete_this)
   {  delete delete_this;  }
};

int main()
{
   const int MaxElem = 100;

   //Fill all the nodes and insert them in the list
   my_class_list list;

   try{
      //Insert new objects in the container
      for(int i = 0; i < MaxElem; ++i){
         list.push_back(*new my_class(i));
      }

      //Now use remove_and_destroy_if to erase and delete the objects
      list.remove_and_destroy_if(is_even(), delete_destroyer());
   }
   catch(...){
      //If something throws, make sure that all the memory is freed
      list.clear_and_destroy(delete_destroyer());
      throw;
   }

   //Destroy remaining elements
   list.erase_and_destroy(list.begin(), list.end(), delete_destroyer());
   return 0;
}
//]
