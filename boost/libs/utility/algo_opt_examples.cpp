
/*
 *
 * Copyright (c) 1999
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 * This file provides some example of type_traits usage -
 * by "optimising" various algorithms:
 *
 * opt::copy - optimised for trivial copy (cf std::copy)
 * opt::fill - optimised for trivial copy/small types (cf std::fill)
 * opt::destroy_array - an example of optimisation based upon omitted destructor calls
 * opt::iter_swap - uses type_traits to determine whether the iterator is a proxy
 *                  in which case it uses a "safe" approach, otherwise calls swap
 *                  on the assumption that swap may be specialised for the pointed-to type.
 *
 */

/* Release notes:
   23rd July 2000:
      Added explicit failure for broken compilers that don't support these examples.
      Fixed broken gcc support (broken using directive).
      Reordered tests slightly.
*/

#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <iterator>
#include <vector>
#include <memory>

#include <boost/timer.hpp>
#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>

using std::cout;
using std::endl;
using std::cin;

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#error "Sorry, without template partial specialisation support there isn't anything to test here..."
#endif

namespace opt{

//
// algorithm destroy_arry:
// The reverse of std::unitialized_copy, takes a block of
// unitialized memory and calls destructors on all objects therein.
//

namespace detail{

template <bool>
struct array_destroyer
{
   template <class T>
   static void destroy_array(T* i, T* j){ do_destroy_array(i, j); }
};

template <>
struct array_destroyer<true>
{
   template <class T>
   static void destroy_array(T*, T*){}
};

template <class T>
void do_destroy_array(T* first, T* last)
{
   while(first != last)
   {
      first->~T();
      ++first;
   }
}

}; // namespace detail

template <class T>
inline void destroy_array(T* p1, T* p2)
{
   detail::array_destroyer<boost::has_trivial_destructor<T>::value>::destroy_array(p1, p2);
}

//
// unoptimised versions of destroy_array:
//
template <class T>
void destroy_array1(T* first, T* last)
{
   while(first != last)
   {
      first->~T();
      ++first;
   }
}
template <class T>
void destroy_array2(T* first, T* last)
{
   for(; first != last; ++first) first->~T();
}


//
// opt::copy
// same semantics as std::copy
// calls memcpy where appropiate.
//

namespace detail{

template <bool b>
struct copier
{
   template<typename I1, typename I2>
   static I2 do_copy(I1 first, I1 last, I2 out);
};

template <bool b>
template<typename I1, typename I2>
I2 copier<b>::do_copy(I1 first, I1 last, I2 out)
{
   while(first != last)
   {
      *out = *first;
      ++out;
      ++first;
   }
   return out;
}

template <>
struct copier<true>
{
   template<typename I1, typename I2>
   static I2* do_copy(I1* first, I1* last, I2* out)
   {
      memcpy(out, first, (last-first)*sizeof(I2));
      return out+(last-first);
   }
};


}

template<typename I1, typename I2>
inline I2 copy(I1 first, I1 last, I2 out)
{
   typedef typename boost::remove_cv<typename std::iterator_traits<I1>::value_type>::type v1_t;
   typedef typename boost::remove_cv<typename std::iterator_traits<I2>::value_type>::type v2_t;
   enum{ can_opt = boost::is_same<v1_t, v2_t>::value
                   && boost::is_pointer<I1>::value
                   && boost::is_pointer<I2>::value
                   && boost::has_trivial_assign<v1_t>::value };
   return detail::copier<can_opt>::do_copy(first, last, out);
}

//
// fill
// same as std::fill, uses memset where appropriate, along with call_traits
// to "optimise" parameter passing.
//
namespace detail{

template <bool opt>
struct filler
{
   template <typename I, typename T>
   static void do_fill(I first, I last, typename boost::call_traits<T>::param_type val);
 };

template <bool b>
template <typename I, typename T>
void filler<b>::do_fill(I first, I last, typename boost::call_traits<T>::param_type val)
{
   while(first != last)
   {
      *first = val;
      ++first;
   }
}

template <>
struct filler<true>
{
   template <typename I, typename T>
   static void do_fill(I first, I last, T val)
   {
      memset(first, val, last-first);
   }
};

}

template <class I, class T>
inline void fill(I first, I last, const T& val)
{
   enum{ can_opt = boost::is_pointer<I>::value
                   && boost::is_arithmetic<T>::value
                   && (sizeof(T) == 1) };
   typedef detail::filler<can_opt> filler_t;
   filler_t::template do_fill<I,T>(first, last, val);
}

//
// iter_swap:
// tests whether iterator is a proxying iterator or not, and
// uses optimal form accordingly:
//
namespace detail{

template <bool b>
struct swapper
{
   template <typename I>
   static void do_swap(I one, I two)
   {
      typedef typename std::iterator_traits<I>::value_type v_t;
      v_t v = *one;
      *one = *two;
      *two = v;
   }
};

#ifdef __GNUC__
using std::swap;
#endif

template <>
struct swapper<true>
{
   template <typename I>
   static void do_swap(I one, I two)
   {
      using std::swap;
      swap(*one, *two);
   }
};

}

template <typename I1, typename I2>
inline void iter_swap(I1 one, I2 two)
{
   typedef typename std::iterator_traits<I1>::reference r1_t;
   typedef typename std::iterator_traits<I2>::reference r2_t;
   enum{ can_opt = boost::is_reference<r1_t>::value && boost::is_reference<r2_t>::value && boost::is_same<r1_t, r2_t>::value };
   detail::swapper<can_opt>::do_swap(one, two);
}


};   // namespace opt

//
// define some global data:
//
const int array_size = 1000;
int i_array[array_size] = {0,};
const int ci_array[array_size] = {0,};
char c_array[array_size] = {0,};
const char cc_array[array_size] = { 0,};

const int iter_count = 1000000;


int main()
{
   //
   // test destroy_array,
   // compare destruction time of an array of ints
   // with unoptimised form.
   //
   cout << "Measuring times in micro-seconds per 1000 elements processed" << endl << endl;
   cout << "testing destroy_array...\n"
    "[Some compilers may be able to optimise the \"unoptimised\"\n versions as well as type_traits does.]" << endl;
   /*cache load*/ opt::destroy_array(i_array, i_array + array_size);
   boost::timer t;
   double result;
   int i;
   for(i = 0; i < iter_count; ++i)
   {
      opt::destroy_array(i_array, i_array + array_size);
   }
   result = t.elapsed();
   cout << "destroy_array<int>: " << result << endl;
   /*cache load*/ opt::destroy_array1(i_array, i_array + array_size);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::destroy_array1(i_array, i_array + array_size);
   }
   result = t.elapsed();
   cout << "destroy_array<int>(unoptimised#1): " << result << endl;
   /*cache load*/ opt::destroy_array2(i_array, i_array + array_size);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::destroy_array2(i_array, i_array + array_size);
   }
   result = t.elapsed();
   cout << "destroy_array<int>(unoptimised#2): " << result << endl << endl;

   cout << "testing fill(char)...\n"
   "[Some standard library versions may already perform this optimisation.]" << endl;
   /*cache load*/ opt::fill<char*, char>(c_array, c_array + array_size, (char)3);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::fill<char*, char>(c_array, c_array + array_size, (char)3);
   }
   result = t.elapsed();
   cout << "opt::fill<char*, char>: " << result << endl;
   /*cache load*/ std::fill(c_array, c_array + array_size, (char)3);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      std::fill(c_array, c_array + array_size, (char)3);
   }
   result = t.elapsed();
   cout << "std::fill<char*, char>: " << result << endl << endl;

   cout << "testing fill(int)...\n"
   "[Tests the effect of call_traits pass-by-value optimisation -\nthe value of this optimisation may depend upon hardware characteristics.]" << endl;
   /*cache load*/ opt::fill<int*, int>(i_array, i_array + array_size, 3);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::fill<int*, int>(i_array, i_array + array_size, 3);
   }
   result = t.elapsed();
   cout << "opt::fill<int*, int>: " << result << endl;
   /*cache load*/ std::fill(i_array, i_array + array_size, 3);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      std::fill(i_array, i_array + array_size, 3);
   }
   result = t.elapsed();
   cout << "std::fill<int*, int>: " << result << endl << endl;

   cout << "testing copy...\n"
   "[Some standard library versions may already perform this optimisation.]" << endl;
   /*cache load*/ opt::copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   }
   result = t.elapsed();
   cout << "opt::copy<const int*, int*>: " << result << endl;
   /*cache load*/ std::copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      std::copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   }
   result = t.elapsed();
   cout << "std::copy<const int*, int*>: " << result << endl;
   /*cache load*/ opt::detail::copier<false>::template do_copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::detail::copier<false>::template do_copy<const int*, int*>(ci_array, ci_array + array_size, i_array);
   }
   result = t.elapsed();
   cout << "standard \"unoptimised\" copy: " << result << endl << endl;

   /*cache load*/ opt::copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   }
   result = t.elapsed();
   cout << "opt::copy<const char*, char*>: " << result << endl;
   /*cache load*/ std::copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      std::copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   }
   result = t.elapsed();
   cout << "std::copy<const char*, char*>: " << result << endl;
   /*cache load*/ opt::detail::copier<false>::template do_copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   t.restart();
   for(i = 0; i < iter_count; ++i)
   {
      opt::detail::copier<false>::template do_copy<const char*, char*>(cc_array, cc_array + array_size, c_array);
   }
   result = t.elapsed();
   cout << "standard \"unoptimised\" copy: " << result << endl << endl;


   //
   // testing iter_swap
   // really just a check that it does in fact compile...
   std::vector<int> v1;
   v1.push_back(0);
   v1.push_back(1);
   std::vector<bool> v2;
   v2.push_back(0);
   v2.push_back(1);
   opt::iter_swap(v1.begin(), v1.begin()+1);
   opt::iter_swap(v2.begin(), v2.begin()+1);

   cout << "Press any key to exit...";
   cin.get();
}





