//File: jobs.h

#ifndef _JOBSH_INC_
#define _JOBSH_INC_

#include <vector>
#include <sstream>
#include <algorithm>
#include <typeinfo>

#include "boost/variant/get.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

#include "varout.h"

#include "boost/detail/workaround.hpp"
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x0551))
#    pragma warn -lvc
#endif

struct total_sizeof : boost::static_visitor<int>
{
   total_sizeof() : total_(0) { }

   template<class Value>
   int operator()(const Value&) const
   {
      total_ += sizeof(Value);
      return total_;
   }

   int result() const
   {
      return total_;
   }

   mutable int total_;

}; // total_sizeof



//Function object: sum_int
//Description: Compute total sum of a series of numbers, (when called successively)
//Use sizeof(T) if applied with a non-integral type
struct sum_int : boost::static_visitor<int>
{
   
   sum_int() : total_(0) { }


   template<int n>
   struct int_to_type
   {
      BOOST_STATIC_CONSTANT(int, value = n);
   }; 

   //Integral type - add numerical value
   template<typename T>
   void add(T t, int_to_type<true> ) const
   {
      total_ += t;
   }

   //Other types - add sizeof<T>
   template<typename T>
   void add(T& , int_to_type<false> ) const
   {
      total_ += sizeof(T);
   }

   template<typename T>
   int operator()(const T& t) const
   {
      //Int_to_type is used to select the correct add() overload
      add(t, int_to_type<boost::is_integral<T>::value>());
      return total_;
   }

   int result() const
   {
      return total_;
   }

private:
   mutable int total_;

}; //sum_int






//Function object: sum_double
//Description: Compute total sum of a series of numbers, (when called successively)
//Accpetable input types: float, double (Other types are silently ignored)
struct sum_double : boost::static_visitor<double>
{
   
   sum_double() : total_(0) { }

   void operator()(float value) const
   {
      total_ += value;
   }

   void operator()(double value) const
   {
      total_ += value;
   }

   template<typename T>
   void operator()(const T&) const
   {
      //Do nothing
   }

   double result() const
   {
      return total_;
   }

private:
   mutable double total_;

}; //sum_double



struct int_printer : boost::static_visitor<std::string>
{
   
   int_printer(std::string prefix_s = "") : prefix_s_(prefix_s) { }
   int_printer(const int_printer& other) : prefix_s_(other.prefix_s_)
   {
      ost_ << other.str();
   }

   std::string operator()(int x) const
   {
      ost_ << prefix_s_ << x;
      return str();
   }

   std::string operator()(const std::vector<int>& x) const
   {
      ost_ << prefix_s_;

      //Use another Int_printer object for printing a list of all integers
      int_printer job(",");
      ost_ << std::for_each(x.begin(), x.end(), job).str();
      
      return str();
   }

   std::string str() const
   {
      return ost_.str();
   }

private:
   std::string prefix_s_;
   mutable std::ostringstream ost_;
};  //int_printer


struct int_adder : boost::static_visitor<>
{
   
   int_adder(int rhs) : rhs_(rhs) { }

   result_type operator()(int& lhs) const
   {
      lhs += rhs_;
   }

   template<typename T>
   result_type operator()(const T& ) const
   {
      //Do nothing
   }

   int rhs_;
}; //int_adder




struct held_type_name : boost::static_visitor<std::string>
{
   
   template<typename T>
   std::string operator()(const T& ) const
   {
      ost_ << '[' << typeid(T).name() << ']';
      return result();
   }

   std::string result() const
   {
      return ost_.str();
   }

   mutable std::ostringstream ost_;

}; //held_type_name




template<typename T>
struct spec 
{
   typedef T result;
};

template<typename VariantType, typename S>
inline void verify(const VariantType& vari, spec<S>, std::string str = "")
{
   BOOST_CHECK(boost::apply_visitor(total_sizeof(), vari) == sizeof(S));
   BOOST_CHECK(vari.type() == typeid(S));

   VariantType& mut_vari = const_cast<VariantType&>(vari);
   //
   // Check get<>()
   //
   BOOST_CHECK(boost::get<const S>(&vari));
   BOOST_CHECK(boost::get<S>(&mut_vari));

   const S* ptr1 = 0;
   const S* ptr2 = 0;
   int count = 0;
   try
   {
      const S& r = boost::get<const S>(vari);
      ptr1 = &r;
   }
   catch(boost::bad_get& )
   {
      count += 1;
   }

   try
   {
      S& mut_r = boost::get<S>(mut_vari);
      ptr2 = &mut_r;
   }
   catch(boost::bad_get& )
   {
      count += 1;
   }

   BOOST_CHECK(count == 0);
   BOOST_CHECK(ptr1 != 0 && ptr2 == ptr1);

   //
   // Check string content
   //
   if(str.length() > 0)
   {
      std::string temp = boost::apply_visitor(to_text(), vari);
      std::cout << "temp = " << temp << ", str = " << str << std::endl;
      BOOST_CHECK(temp == str);         
   }
}


template<typename VariantType, typename S>
inline void verify_not(const VariantType& vari, spec<S>)
{
   BOOST_CHECK(vari.type() != typeid(S));
   
   //
   // Check get<>()
   //
   BOOST_CHECK(!boost::get<const S>(&vari));

   VariantType& mut_vari = const_cast<VariantType&>(vari);
   BOOST_CHECK(!boost::get<S>(&mut_vari));

   const S* ptr1 = 0;
   const S* ptr2 = 0;
   int count = 0;
   try
   {
      const S& r = boost::get<const S>(vari);
      ptr1 = &r;
   }
   catch(boost::bad_get& )
   {
      count += 1;
   }

   try
   {
      S& mut_r = boost::get<S>(mut_vari);
      ptr2 = &mut_r;
   }
   catch(boost::bad_get& )
   {
      count += 1;
   }

   BOOST_CHECK(count == 2);
   BOOST_CHECK(ptr1 == 0 && ptr2 == 0);   
}


#endif //_JOBSH_INC_
