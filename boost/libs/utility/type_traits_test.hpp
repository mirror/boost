 // boost::compressed_pair test program   
    
 //  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
 //  distribute this software is granted provided this copyright notice appears   
 //  in all copies. This software is provided "as is" without express or implied   
 //  warranty, and with no claim as to its suitability for any purpose.   

// common test code for type_traits_test.cpp/call_traits_test.cpp/compressed_pair_test.cpp


#ifndef BOOST_TYPE_TRAITS_TEST_HPP
#define BOOST_TYPE_TRAITS_TEST_HPP

//
// this one is here just to suppress warnings:
//
template <class T>
bool do_compare(T i, T j)
{
   return i == j;
}

//
// this one is to verify that a constant is indeed a
// constant-integral-expression:
//
template <int>
struct ct_checker
{
};

#define BOOST_DO_JOIN( X, Y ) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2(X, Y) X##Y
#define BOOST_JOIN( X, Y ) BOOST_DO_JOIN( X, Y )

#ifdef BOOST_MSVC
#define value_test(v, x) ++test_count;\
                         if(!do_compare((int)v,(int)x)){++failures; std::cout << "checking value of " << #x << "...failed" << std::endl;}
#else
#define value_test(v, x) ++test_count;\
                         typedef ct_checker<(x)> BOOST_JOIN(this_is_a_compile_time_check_, __LINE__);\
                         if(!do_compare((int)v,(int)x)){++failures; std::cout << "checking value of " << #x << "...failed" << std::endl;}
#endif
#define value_fail(v, x) ++test_count; ++failures; std::cout << "checking value of " << #x << "...failed" << std::endl;

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define type_test(v, x)  ++test_count;\
                           if(do_compare(boost::is_same<v, x>::value, false)){\
                           ++failures; \
                           std::cout << "checking type of " << #x << "...failed" << std::endl; \
                           std::cout << "   expected type was " << #v << std::endl; \
                           std::cout << "   " << typeid(boost::is_same<v, x>).name() << "::value is false" << std::endl; }
#else
#define type_test(v, x)  ++test_count;\
                         if(typeid(v) != typeid(x)){\
                           ++failures; \
                           std::cout << "checking type of " << #x << "...failed" << std::endl; \
                           std::cout << "   expected type was " << #v << std::endl; \
                           std::cout << "   " << "typeid(" #v ") != typeid(" #x ")" << std::endl; }
#endif

template <class T>
struct test_align
{
   struct padded
   {
      char c;
      T t;
   };
   static void do_it()
   {
      padded p;
      unsigned a = reinterpret_cast<char*>(&(p.t)) - reinterpret_cast<char*>(&p);
      value_test(a, boost::alignment_of<T>::value);
   }
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct test_align<T&>
{
   static void do_it()
   {
      //
      // we can't do the usual test because we can't take the address
      // of a reference, so check that the result is the same as for a
      // pointer type instead:
      value_test(boost::alignment_of<T*>::value, boost::alignment_of<T&>::value);
   }
};
#endif

#define align_test(T) test_align<T>::do_it()

//
// define tests here
unsigned failures = 0;
unsigned test_count = 0;

//
// turn off some warnings:
#ifdef __BORLANDC__
#pragma option -w-8004
#endif

#ifdef BOOST_MSVC
#pragma warning (disable: 4018)
#endif


#endif // BOOST_TYPE_TRAITS_TEST_HPP
