//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  Crippled version of type traits for compilers that don't
//  support partial specialisation. (C) John Maddock 2000

/* Release notes:
   01st October 2000:
      Fixed is_pointer, is_reference, is_const, is_volatile, is_same, is_member_pointer
      using ideas suggested from "Generic<Programming>: Mappings between Types and Values" 
      by Andrei Alexandrescu (see http://www.cuj.com/experts/1810/alexandr.html).
      Mat Marcus and Jesse Jones posted a version of is_pointer very similar to this one
      on the boost list (Copyright 2000 Adobe Systems Incorporated and others. 
      All rights reserved.).
   31st July 2000:
      Added is_convertable, alignment_of.
   23rd July 2000:
      Fixed is_void specialization. (JM)
*/

//
// partial copyright for is_convertible:
//
// Copyright (C) 2000 Jeremy Siek (jsiek@lsc.nd.edu)
// Copyright (C) 1999, 2000 Jaakko J„rvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy and use this software is granted,
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted,
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.


#ifndef BOOST_OB_TYPE_TRAITS_HPP
#define BOOST_OB_TYPE_TRAITS_HPP

#ifndef BOOST_TYPE_TRAITS_HPP
#error Internal header file: This header must be included by <boost/type_traits.hpp> only.
#endif

// **************************************************************************
// Helper macros for builitin compiler support.
// If your compiler has builtin support for any of the following
// traits concepts, then redefine the appropriate macros to pick
// up on the compiler support:

#define BOOST_IS_CLASS(T) !is_union<T>::value && \
    !is_scalar<T>::value && \
    !is_array<T>::value && \
    !is_reference<T>::value && \
    !is_void<T>::value
#define BOOST_IS_ENUM(T) false
#define BOOST_IS_UNION(T) false
#define BOOST_IS_POD(T) false
#define BOOST_IS_EMPTY(T) false
#define BOOST_HAS_TRIVIAL_CONSTRUCTOR(T) false
#define BOOST_HAS_TRIVIAL_COPY(T) false
#define BOOST_HAS_TRIVIAL_ASSIGN(T) false
#define BOOST_HAS_TRIVIAL_DESTRUCTOR(T) false


/**************************************************************************/

namespace boost{
//
// start with fundamental type operations:
// these don't actually work:
//
template <typename T>
struct remove_volatile{ typedef T type; };
template <typename T>
struct remove_const{ typedef T type; };
template <typename T>
struct remove_cv{ typedef T type; };
template <typename T> struct remove_reference{ typedef T type; };
template <typename T> struct add_reference{ typedef T& type; };
template <typename T> struct remove_bounds{ typedef T type; };

/**************************************************************************/
//
// fundamental property classes:

//* is a type T  declared const - is_const<T>
namespace detail{
   typedef char yes_result;
   typedef char (&no_result)[8];
   yes_result is_const_helper(const volatile void*);
   double is_const_helper(volatile void *);
   yes_result is_volatile_helper(const volatile void*);
   double is_volatile_helper(const void *);
}

template <typename T>
struct is_const
{ 
private:
   static T t;
public:
   enum{ value = (sizeof(detail::yes_result) == sizeof(detail::is_const_helper(&t))) }; 
};

template <typename T>
struct is_volatile
{ 
private:
   static T t;
public:
   enum{ value = (sizeof(detail::yes_result) == sizeof(detail::is_volatile_helper(&t))) }; 
};

namespace detail{
   template <class T>
   yes_result is_same_helper(T*, T*);
   no_result is_same_helper(...);
}

template <typename T, typename U> struct is_same 
{ 
private:
   static T t;
   static U u;
public:
   enum{ value = (sizeof(detail::yes_result) == sizeof(detail::is_same_helper(&t,&u))) }; 
};

template <typename T> struct is_void{ enum{ value = false }; };
template <> struct is_void<void>{ enum{ value = true }; };

//* is a type T an unsigned integral type described in the standard (3.9.1p3)
template <typename T> struct is_standard_unsigned_integral
{ enum{ value = false}; };
template <> struct is_standard_unsigned_integral<unsigned char>
{ enum{ value = true}; };
template <> struct is_standard_unsigned_integral<unsigned short>
{ enum{ value = true}; };
template <> struct is_standard_unsigned_integral<unsigned int>
{ enum{ value = true}; };
template <> struct is_standard_unsigned_integral<unsigned long>
{ enum{ value = true}; };

//* is a type T a signed integral type described in the standard (3.9.1p2)
template <typename T> struct is_standard_signed_integral
{ enum{ value = false}; };
template <> struct is_standard_signed_integral<signed char>
{ enum{ value = true}; };
template <> struct is_standard_signed_integral<signed short>
{ enum{ value = true}; };
template <> struct is_standard_signed_integral<signed int>
{ enum{ value = true}; };
template <> struct is_standard_signed_integral<signed long>
{ enum{ value = true}; };

//* is a type T an integral type described in the standard (3.9.1p7)
template <typename T> struct is_standard_integral
{ enum{ value = is_standard_unsigned_integral<T>::value ||
is_standard_signed_integral<T>::value }; };
template <> struct is_standard_integral<char>
{ enum{ value = true}; };
template <> struct is_standard_integral<wchar_t>
{ enum{ value = true}; };
template <> struct is_standard_integral<bool>
{ enum{ value = true}; };

//* is a type T a floating-point type described in the standard (3.9.1p8)
template <typename T> struct is_standard_float
{ enum{ value = false}; };
template <> struct is_standard_float<float>
{ enum{ value = true}; };
template <> struct is_standard_float<double>
{ enum{ value = true}; };
template <> struct is_standard_float<long double>
{ enum{ value = true}; };

//* is a type T an arithmetic type described in the standard (3.9.1p8)
template <typename T> struct is_standard_arithmetic
{ enum{ value = is_standard_integral<T>::value || is_standard_float<T>::value}; };

//* is a type T a fundamental type described in the standard (3.9.1)
template <typename T> struct is_standard_fundamental
{ enum{ value = is_standard_arithmetic<T>::value || is_void<T>::value}; };

//* is a type T an unsigned integral type provided by a compiler extension
// specialise for compiler defined extentions:
template <typename T> struct is_extension_unsigned_integral
{ enum{ value = false}; };

//* is a type T a signed integral type provided by a compiler extension
// specialise for compiler defined extentions:
template <typename T> struct is_extension_signed_integral
{ enum{ value = false}; };

#ifdef ULLONG_MAX
template <> struct is_extension_unsigned_integral<unsigned long long>
{ enum{ value = true}; };
template <> struct is_extension_signed_integral<long long>
{ enum{ value = true}; };
#endif
#if defined(__BORLANDC__) || defined(_MSC_VER) && !defined(__MWERKS__)
template <> struct is_extension_unsigned_integral<unsigned __int64>
{ enum{ value = true}; };
template <> struct is_extension_signed_integral<__int64>
{ enum{ value = true}; };
#endif

//* is a type T an integral type provided by a compiler extension
template <typename T> struct is_extension_integral
{ enum{ value = is_extension_signed_integral<T>::value ||
      is_extension_unsigned_integral<T>::value }; };

//* is a type T a floating-point type provided by a compiler extension
template <typename T> struct is_extension_float
{ enum{ value = false}; };

//* is a type T an arithmetic type provided by a compiler extension
template <typename T> struct is_extension_arithmetic
{ enum{ value = is_extension_integral<T>::value || is_extension_float<T>::value}; };

//* is a type T a fundamental type provided by a compiler extension
template <typename T> struct is_extension_fundamental
{ enum{ value = is_extension_arithmetic<T>::value || is_void<T>::value}; };

//* is a type T an unsigned integral type provided by the compiler or standard
template <typename T> struct is_unsigned_integral
{ enum{ value = is_standard_unsigned_integral<T>::value || is_extension_unsigned_integral<T>::value}; };

//* is a type T a signed integral type provided by the compiler or standard
template <typename T> struct is_signed_integral
{ enum{ value = is_standard_signed_integral<T>::value || is_extension_signed_integral<T>::value}; };

//* is a type T an integral type provided by the compiler or standard
template <typename T> struct is_integral
{ enum{ value = is_standard_integral<T>::value || is_extension_integral<T>::value}; };

//* is a type T a floating-point type provided by the compiler or standard
template <typename T> struct is_float
{ enum{ value = is_standard_float<T>::value || is_extension_float<T>::value}; };

//* is a type T an arithmetic type provided by the compiler or standard
template <typename T> struct is_arithmetic
{ enum{ value = is_standard_arithmetic<T>::value || is_extension_arithmetic<T>::value}; };

//* is a type T a fundamental type provided by the compiler or standard
template <typename T> struct is_fundamental
{ enum{ value = is_standard_fundamental<T>::value || is_extension_fundamental<T>::value}; };

//* is a type T an array - is_array<T>
namespace detail{
   template <class T>
   yes_result is_array_helper(const volatile T*, const volatile T*);
   double is_array_helper(...);
}
template <typename T> struct is_array
{ 
private:
   static T t;
public:
   enum{ value = (1 == sizeof(detail::is_array_helper(t, &t)))}; 
};

//* is a type T a pointer type (including function pointers) - is_pointer<T>
namespace detail{
   yes_result is_pointer_helper(const volatile void*const volatile);
   double is_pointer_helper(...);
}

template <typename T> struct is_pointer 
{ 
private:
   static T t;
public:
   enum{ value = !is_const<T>::value 
                 && !is_volatile<T>::value 
                 && (1 == sizeof(detail::is_pointer_helper(t)))}; 
};

# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
# endif // BOOST_MSVC

//* is a type T a reference type - is_reference<T>
template <typename T> struct is_reference 
{ 
private:
   typedef T const volatile cv_t;
public:
   enum{ value = !is_const<cv_t>::value || !is_volatile<cv_t>::value }; 
};
template <> struct is_reference<void> 
{ 
   enum{ value = false }; 
};

# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif // BOOST_MSVC

//*? is a type T a union type - is_union<T>
template <typename T> struct is_union
{ enum{ value = BOOST_IS_UNION(T) }; };

//*? is a type T an enum - is_enum<T>
template <typename T> struct is_enum
{ enum{ value = BOOST_IS_ENUM(T) }; };

//* is a type T a member function pointer - is_member_pointer<T>
namespace detail{
   template <class T, class U>
   yes_result is_member_pointer_helper(T (U::*));
   template <class T, class U>
   yes_result is_member_pointer_helper(T (U::*)(void));
   template <class T, class U, class A1>
   yes_result is_member_pointer_helper(T (U::*)(A1));
   template <class T, class U, class A1, class A2>
   yes_result is_member_pointer_helper(T (U::*)(A1, A2));
   double is_member_pointer_helper(...);
}
template <typename T> struct is_member_pointer
{ 
private:
   static T t;
public:
   enum{ value = (1 == sizeof(detail::is_member_pointer_helper(t))) }; 
};

//* is type T an object type (allows cv-qual)
template <typename T> struct is_object
{ enum{ value = !is_reference<T>::value && !is_void<T>::value }; };

//* is type T a standard scalar type (allows cv-qual)
template <typename T> struct is_standard_scalar
{ enum{ value = is_standard_arithmetic<T>::value
      || is_enum<T>::value
      || is_pointer<T>::value
      || is_member_pointer<T>::value }; };

//* is type T an extension scalar type (allows cv-qual)
template <typename T> struct is_extension_scalar
{ enum{ value = is_extension_arithmetic<T>::value
      || is_enum<T>::value
      || is_pointer<T>::value
      || is_member_pointer<T>::value }; };

//* is type T a builtin scalar type (allows cv-qual)
template <typename T> struct is_scalar
{ enum{ value = is_arithmetic<T>::value
      || is_enum<T>::value
      || is_pointer<T>::value
      || is_member_pointer<T>::value }; };

//*? is a type T a class type (class/struct) - is_class<T>
template <typename T> struct is_class
{ enum{ value = BOOST_IS_CLASS(T) }; };

//*? is a type T a compound type
template <typename T> struct is_compound
{ enum{ value = is_array<T>::value || is_pointer<T>::value
      || is_reference<T>::value || is_class<T>::value || is_union<T>::value
      || is_enum<T>::value || is_member_pointer<T>::value }; };

//*? is type T a POD type (allows cv-qual)
template <typename T> struct is_POD
{ enum{ value = is_scalar<T>::value  //JM 7Jan2000
      || BOOST_IS_POD(T) }; };

namespace detail{

    // This workaround is necessary to handle when From is void
    // which is normally taken care of by the partial specialization
    // of the is_convertible class.
#ifdef BOOST_MSVC6_MEMBER_TEMPLATES
  struct from_not_void_conversion {
    template <class From, class To>
    struct bind {
      static no_result check(...);
      static yes_result check(To);
    public:
      void foo(); // avoid warning about all members being private
      static From from;
      enum { exists = sizeof( check(from) ) == sizeof(yes_result) };
    };
  };
  struct from_is_void_conversion {
    template <class From, class To>
    struct bind {
      enum { exists = is_void<To>::value };
    };
  };

  template <class From>
  struct conversion_helper {
    typedef from_not_void_conversion type;
  };
  template <>
  struct conversion_helper<void> {
    typedef from_is_void_conversion type;
  };
#endif
} // namespace detail

template <class From, class To>
class is_convertible
{
#ifdef BOOST_MSVC6_MEMBER_TEMPLATES
 typedef typename detail::conversion_helper<From>::type Selector;
 typedef Selector::template bind<From,To> Conversion;
public:
 enum { value = Conversion::exists };
#else
   static detail::no_result check(...);
   static detail::yes_result check(To);
 public:
   void foo(); // avoid warning about all members being private
   static From from;
   enum { value = sizeof( check(from) ) == sizeof(detail::yes_result) };
#endif
};

template <class T>
class alignment_of
{
   struct padded
   {
      char c;
      T t;
      padded();
   };
public:
   enum{ value = sizeof(padded) - sizeof(T) };
};

//*? is type T an empty composite type (allows cv-qual)
template <typename T> struct is_empty
{ enum{ value = BOOST_IS_EMPTY(T) }; };

//*? T has trivial default constructor (allows cv-qual)
template <typename T> struct has_trivial_constructor
{
  enum{ value = is_POD<T>::value || BOOST_HAS_TRIVIAL_CONSTRUCTOR(T) };
};

//*? T has trivial copy constructor (allows cv-qual)
template <typename T> struct has_trivial_copy
{
  enum{ value = is_POD<T>::value || BOOST_HAS_TRIVIAL_COPY(T) };
};

//*? T has trivial assignment operator (allows cv-qual)
template <typename T>
struct has_trivial_assign
{
  enum{ value = is_POD<T>::value || BOOST_HAS_TRIVIAL_ASSIGN(T) };
};

//*? T has trivial destructor (allows cv-qual)
template <typename T>
struct has_trivial_destructor
{
  enum{ value = is_POD<T>::value || BOOST_HAS_TRIVIAL_DESTRUCTOR(T) };
};

} // namespace boost

/**************************************************************************/

//
// undefine helper macro's:
//
#undef BOOST_IS_CLASS
#undef BOOST_IS_ENUM
#undef BOOST_IS_UNION
#undef BOOST_IS_POD
#undef BOOST_IS_EMPTY
#undef BOOST_HAS_TRIVIAL_CONSTRUCTOR
#undef BOOST_HAS_TRIVIAL_COPY
#undef BOOST_HAS_TRIVIAL_ASSIGN
#undef BOOST_HAS_TRIVIAL_DESTRUCTOR

#endif // BOOST_OB_TYPE_TRAITS_HPP




