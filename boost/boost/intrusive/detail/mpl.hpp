/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_MPL_HPP
#define BOOST_INTRUSIVE_DETAIL_MPL_HPP

namespace boost {
namespace intrusive {
namespace detail {

template< bool C_ >
struct bool_
{
   static const bool value = C_;
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

typedef true_  true_type;
typedef false_ false_type;

typedef char yes_type;
struct no_type
{
   char padding[8];
};

template <bool B, class T = void>
struct enable_if_c {
  typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T>{};

template <class T, class U>
class is_convertible
{
   typedef char true_t;
   class false_t { char dummy[2]; };
   static true_t dispatch(U);
   static false_t dispatch(...);
   static T trigger();
   public:
   enum { value = sizeof(dispatch(trigger())) == sizeof(true_t) };
};

#if defined(BOOST_MSVC) || defined(__BORLANDC_)
#define BOOST_INTRUSIVE_TT_DECL __cdecl
#else
#define BOOST_INTRUSIVE_TT_DECL 
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BORLAND__)
#define BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
#endif

no_type BOOST_INTRUSIVE_TT_DECL is_function_ptr_tester(...);

template <class R >
yes_type is_function_ptr_tester(R (*)());

template <class R >
yes_type is_function_ptr_tester(R (*)( ...));

#ifdef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
template <class R >
yes_type is_function_ptr_tester(R (__stdcall*)());
template <class R >
yes_type is_function_ptr_tester(R (__stdcall*)( ...));

template <class R >
yes_type is_function_ptr_tester(R (__fastcall*)());
template <class R >
yes_type is_function_ptr_tester(R (__fastcall*)( ...));

template <class R >
yes_type is_function_ptr_tester(R (__cdecl*)());
template <class R >
yes_type is_function_ptr_tester(R (__cdecl*)( ...));
#endif

template <class R , class T0 >
yes_type is_function_ptr_tester(R (*)( T0));

template <class R , class T0 >
yes_type is_function_ptr_tester(R (*)( T0 ...));

#ifdef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
template <class R , class T0 >
yes_type is_function_ptr_tester(R (__stdcall*)( T0));
template <class R , class T0 >
yes_type is_function_ptr_tester(R (__stdcall*)( T0 ...));

template <class R , class T0 >
yes_type is_function_ptr_tester(R (__fastcall*)( T0));
template <class R , class T0 >
yes_type is_function_ptr_tester(R (__fastcall*)( T0 ...));

template <class R , class T0 >
yes_type is_function_ptr_tester(R (__cdecl*)( T0));
#endif
template <class R , class T0 , class T1 >
yes_type is_function_ptr_tester(R (*)( T0 , T1));

#ifdef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
template <class R , class T0 , class T1 >
yes_type is_function_ptr_tester(R (__stdcall*)( T0 , T1));

template <class R , class T0 , class T1 >
yes_type is_function_ptr_tester(R (__fastcall*)( T0 , T1));

template <class R , class T0 , class T1 >
yes_type is_function_ptr_tester(R (__cdecl*)( T0 , T1));
#endif

template <typename T>
struct is_unary_or_binary_function_impl
{
    static T* t;
    enum{ value = sizeof(is_function_ptr_tester(t)) == sizeof(yes_type) };
};

template <typename T>
struct is_unary_or_binary_function_impl<T&>
{  enum {value = false }; };

template<typename T>
struct is_unary_or_binary_function
{
   enum{ value = is_unary_or_binary_function_impl<T>::value }; 
};

//boost::alignment_of yields to 10K lines of preprocessed code, so we
//need an alternative
template <typename T> struct alignment_of;

template <typename T>
struct alignment_of_hack
{
    char c;
    T t;
    alignment_of_hack();
};

template <unsigned A, unsigned S>
struct alignment_logic
{
    enum{   value = A < S ? A : S  };
};

template< typename T >
struct alignment_of
{
   enum{ value = alignment_logic
            < sizeof(alignment_of_hack<T>) - sizeof(T)
            , sizeof(T)>::value   };
};

} //namespace detail 
} //namespace intrusive 
} //namespace boost 

#endif //BOOST_INTRUSIVE_DETAIL_MPL_HPP
