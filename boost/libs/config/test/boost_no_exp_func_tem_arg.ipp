//  (C) Copyright John Maddock 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  MACRO:         BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
//  TITLE:         non-deduced function template parameters
//  DESCRIPTION:   Can only use deduced template arguments when 
//                 calling function template instantiations.

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)
#error "This is known to be buggy under VC6"
#endif


namespace boost_no_explicit_function_template_arguments{

struct foo
{
  template<class T> int bar(){return 0;}
  template<int I>   int bar(){return 1;}
};

int test_0()
{
  return 0;
}


template <int i>
bool foo_17041(int j)
{
   return (i == j);
}

int test()
{
   foo f;
   int a = f.template bar<char>();
   int b = f.template bar<2>();
   if((a !=0) || (b != 1))return -1;

   if(0 == foo_17041<8>(8)) return -1;
   if(0 == foo_17041<4>(4)) return -1;
   if(0 == foo_17041<5>(5)) return -1;
   return 0;
}

}



