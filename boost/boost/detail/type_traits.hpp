//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
// misc traits classes that operate on or describe a type.
// see libs/utility/type_traits.htm

/* Release notes:
   31st July 2000:
      Added is_convertable, alignment_of, modified is_empty.
   23rd July 2000:
      Added Borland specific fixes for reference types (Steve Cleary).
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


#ifndef BOOST_DETAIL_TYPE_TRAITS_HPP
#define BOOST_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_TYPE_TRAITS_HPP
#error Internal header file: This header must be included by <boost/type_traits.hpp> only.
#endif

#include <cstddef>
#include <climits>                         

//
// Helper macros for builitin compiler support.
// If your compiler has builtin support for any of the following
// traits concepts, then redefine the appropriate macros to pick
// up on the compiler support:
//
// (these should return false if T is cv-qualified; the type traits that use these
//  will strip cv-qualification if necessary before passing T)
// BOOST_IS_CLASS(T) should evaluate to true if T is a class or struct type
// BOOST_IS_ENUM(T) should evaluate to true if T is an enumerator type
// BOOST_IS_UNION(T) should evaluate to true if T is a union type
// BOOST_IS_POD(T) should evaluate to true if T is a POD type
// BOOST_IS_EMPTY(T) should evaluate to true if T is an empty struct or union
// BOOST_HAS_TRIVIAL_CONSTRUCTOR(T) should evaluate to true if "T x;" has no effect
// BOOST_HAS_TRIVIAL_COPY(T) should evaluate to true if T(t) <==> memcpy
// BOOST_HAS_TRIVIAL_ASSIGN(T) should evaluate to true if t = u <==> memcpy
// BOOST_HAS_TRIVIAL_DESTRUCTOR(T) should evaluate to true if ~T() has no effect

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

namespace details {
//
// implementation helper:
//
template <class T>
struct cv_traits_imp{};

template <class T>
struct cv_traits_imp<T*>
{
   static const bool is_const = false;
   static const bool is_volatile = false;
   typedef T non_const_type;
   typedef T non_volatile_type;
   typedef T unqualified_type;
   static const char* what() { return ""; }
};

template <class T>
struct cv_traits_imp<const T*>
{
   static const bool is_const = true;
   static const bool is_volatile = false;
   typedef T non_const_type;
   typedef const T non_volatile_type;
   typedef T unqualified_type;
   static const char* what() { return "const"; }
};

template <class T>
struct cv_traits_imp<volatile T*>
{
   static const bool is_const = false;
   static const bool is_volatile = true;
   typedef volatile T non_const_type;
   typedef T non_volatile_type;
   typedef T unqualified_type;
   static const char* what() { return "volatile"; }
};

template <class T>
struct cv_traits_imp<const volatile T*>
{
   static const bool is_const = true;
   static const bool is_volatile = true;
   typedef volatile T non_const_type;
   typedef const T non_volatile_type;
   typedef T unqualified_type;
   static const char* what() { return "const volatile"; }
};

} // namespace details

// * convert a type T to a non-volatile type - remove_volatile<T>
template <typename T>
struct remove_volatile
{
   typedef typename details::cv_traits_imp<T*>::non_volatile_type type;
};
template <typename T> struct remove_volatile<T&>{ typedef T& type; };

// * convert a type T to non-const type - remove_const<T>
template <typename T>
struct remove_const
{
   typedef typename details::cv_traits_imp<T*>::non_const_type type;
};
template <typename T> struct remove_const<T&>{ typedef T& type; };

//  convert a type T to a non-cv-qualified type - remove_cv<T>
template <typename T>
struct remove_cv
{
   typedef typename details::cv_traits_imp<T*>::unqualified_type type;
};
template <typename T> struct remove_cv<T&>{ typedef T& type; };

// * convert a type T to a non-reference if it is one - remove_reference<T>
template <typename T> struct remove_reference{ typedef T type; };
template <typename T> struct remove_reference<T&>{ typedef T type; };
#if (defined(__BORLANDC__) && (__BORLANDC__ <= 0x550))
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct remove_reference<T&const>{ typedef T type; };
template <typename T> struct remove_reference<T&volatile>{ typedef T type; };
template <typename T> struct remove_reference<T&const volatile>{ typedef T type; };
#endif
// * convert a type T to a reference unless it is one - add_reference<T>
template <typename T> struct add_reference{ typedef T& type; };
template <typename T> struct add_reference<T&>{ typedef T& type; };

// * convert an array type to underlying non-array type - remove_bounds<T>
template <typename T> struct remove_bounds{ typedef T type; };
template <typename T, std::size_t N> struct remove_bounds<T[N]>{ typedef T type; };

/**************************************************************************/
//
// fundamental property classes:

//* is a type T  declared const - is_const<T>
template <typename T>
struct is_const
{
   static const bool value = details::cv_traits_imp<T*>::is_const;
};

//* is a type T declared volatile - is_volatile<T>
template <typename T>
struct is_volatile
{
   static const bool value = details::cv_traits_imp<T*>::is_volatile;
};

//* is a type T the same as type U - is_same<T,U>
template <typename T, typename U> struct is_same { static const bool value = false; };
template <typename T> struct is_same<T, T> { static const bool value = true; };

//* is a type T void - is_void<T>
template <typename T> struct is_void{ static const bool value = false; };
template <> struct is_void<void>{ static const bool value = true; };

//* is a type T an unsigned integral type described in the standard (3.9.1p3)
template <typename T> struct is_standard_unsigned_integral
{ static const bool value = false; };
template <> struct is_standard_unsigned_integral<unsigned char>
{ static const bool value = true; };
template <> struct is_standard_unsigned_integral<unsigned short>
{ static const bool value = true; };
template <> struct is_standard_unsigned_integral<unsigned int>
{ static const bool value = true; };
template <> struct is_standard_unsigned_integral<unsigned long>
{ static const bool value = true; };

//* is a type T a signed integral type described in the standard (3.9.1p2)
template <typename T> struct is_standard_signed_integral
{ static const bool value = false; };
template <> struct is_standard_signed_integral<signed char>
{ static const bool value = true; };
template <> struct is_standard_signed_integral<signed short>
{ static const bool value = true; };
template <> struct is_standard_signed_integral<signed int>
{ static const bool value = true; };
template <> struct is_standard_signed_integral<signed long>
{ static const bool value = true; };

//* is a type T an integral type described in the standard (3.9.1p7)
template <typename T> struct is_standard_integral
{ static const bool value = is_standard_unsigned_integral<T>::value ||
      is_standard_signed_integral<T>::value; };
template <> struct is_standard_integral<char>
{ static const bool value = true; };
template <> struct is_standard_integral<wchar_t>
{ static const bool value = true; };
template <> struct is_standard_integral<bool>
{ static const bool value = true; };

//* is a type T a floating-point type described in the standard (3.9.1p8)
template <typename T> struct is_standard_float
{ static const bool value = false; };
template <> struct is_standard_float<float>
{ static const bool value = true; };
template <> struct is_standard_float<double>
{ static const bool value = true; };
template <> struct is_standard_float<long double>
{ static const bool value = true; };

//* is a type T an arithmetic type described in the standard (3.9.1p8)
template <typename T> struct is_standard_arithmetic
{ static const bool value = is_standard_integral<T>::value || is_standard_float<T>::value; };

//* is a type T a fundamental type described in the standard (3.9.1)
template <typename T> struct is_standard_fundamental
{ static const bool value = is_standard_arithmetic<T>::value || is_void<T>::value; };

//* is a type T an unsigned integral type provided by a compiler extension
// specialise for compiler defined extentions:
template <typename T> struct is_extension_unsigned_integral
{ static const bool value = false; };

//* is a type T a signed integral type provided by a compiler extension
// specialise for compiler defined extentions:
template <typename T> struct is_extension_signed_integral
{ static const bool value = false; };

#ifdef ULLONG_MAX
template <> struct is_extension_unsigned_integral<unsigned long long>
{ static const bool value = true; };
template <> struct is_extension_signed_integral<long long>
{ static const bool value = true; };
#endif
#if defined(__BORLANDC__) || defined(_MSC_VER) && !defined(__MWERKS__)
template <> struct is_extension_unsigned_integral<unsigned __int64>
{ static const bool value = true; };
template <> struct is_extension_signed_integral<__int64>
{ static const bool value = true; };
#endif

//* is a type T an integral type provided by a compiler extension
template <typename T> struct is_extension_integral
{ static const bool value = is_extension_signed_integral<T>::value ||
      is_extension_unsigned_integral<T>::value; };

//* is a type T a floating-point type provided by a compiler extension
template <typename T> struct is_extension_float
{ static const bool value = false; };

//* is a type T an arithmetic type provided by a compiler extension
template <typename T> struct is_extension_arithmetic
{ static const bool value = is_extension_integral<T>::value || is_extension_float<T>::value; };

//* is a type T a fundamental type provided by a compiler extension
template <typename T> struct is_extension_fundamental
{ static const bool value = is_extension_arithmetic<T>::value || is_void<T>::value; };

//* is a type T an unsigned integral type provided by the compiler or standard
template <typename T> struct is_unsigned_integral
{ static const bool value = is_standard_unsigned_integral<T>::value || is_extension_unsigned_integral<T>::value; };

//* is a type T a signed integral type provided by the compiler or standard
template <typename T> struct is_signed_integral
{ static const bool value = is_standard_signed_integral<T>::value || is_extension_signed_integral<T>::value; };

//* is a type T an integral type provided by the compiler or standard
template <typename T> struct is_integral
{ static const bool value = is_standard_integral<T>::value || is_extension_integral<T>::value; };

//* is a type T a floating-point type provided by the compiler or standard
template <typename T> struct is_float
{ static const bool value = is_standard_float<T>::value || is_extension_float<T>::value; };

//* is a type T an arithmetic type provided by the compiler or standard
template <typename T> struct is_arithmetic
{ static const bool value = is_standard_arithmetic<T>::value || is_extension_arithmetic<T>::value; };

//* is a type T a fundamental type provided by the compiler or standard
template <typename T> struct is_fundamental
{ static const bool value = is_standard_fundamental<T>::value || is_extension_fundamental<T>::value; };

//* is a type T an array - is_array<T>
template <typename T> struct is_array
{ static const bool value = false; };
template <typename T, std::size_t N> struct is_array<T[N]>
{ static const bool value = true; };

//* is a type T a pointer type (including function pointers) - is_pointer<T>
template <typename T> struct is_pointer { static const bool value = false; };
template <typename T> struct is_pointer<T*> { static const bool value = true; };

//* is a type T a reference type - is_reference<T>
template <typename T> struct is_reference { static const bool value = false; };
template <typename T> struct is_reference<T&> { static const bool value = true; };
#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x551)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct is_reference<T&const> { static const bool value = true; };
template <typename T> struct is_reference<T&volatile> { static const bool value = true; };
template <typename T> struct is_reference<T&const volatile> { static const bool value = true; };
#endif

//*? is a type T a union type - is_union<T>
template <typename T> struct is_union
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = BOOST_IS_UNION(cvt);
};

//*? is a type T an enum - is_enum<T>
template <typename T> struct is_enum
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = BOOST_IS_ENUM(cvt);
};

//* is a type T a member function pointer - is_member_pointer<T>
template <typename T> struct is_member_pointer
{ static const bool value = false; };
template <typename T, typename U> struct is_member_pointer<U T::*>
{ static const bool value = true; };

//* is type T an object type (allows cv-qual)
template <typename T> struct is_object
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = !::boost::is_reference<cvt>::value
      && !::boost::is_void<cvt>::value;
};

//* is type T a standard scalar type (allows cv-qual)
template <typename T> struct is_standard_scalar
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = is_standard_arithmetic<cvt>::value
      || is_enum<cvt>::value
      || is_pointer<cvt>::value
      || is_member_pointer<cvt>::value;
};

//* is type T an extension scalar type (allows cv-qual)
template <typename T> struct is_extension_scalar
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = is_extension_arithmetic<cvt>::value
      || is_enum<cvt>::value
      || is_pointer<cvt>::value
      || is_member_pointer<cvt>::value;
};

//* is type T a builtin scalar type (allows cv-qual)
template <typename T> struct is_scalar
{ 
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = is_arithmetic<cvt>::value
      || is_enum<cvt>::value
      || is_pointer<cvt>::value
      || is_member_pointer<cvt>::value; 
};

//*? is a type T a class type (class/struct) - is_class<T>
template <typename T> struct is_class
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = BOOST_IS_CLASS(cvt); 
};

//*? is a type T a compound type
template <typename T> struct is_compound
{ static const bool value = is_array<T>::value || is_pointer<T>::value
      || is_reference<T>::value || is_class<T>::value || is_union<T>::value
      || is_enum<T>::value || is_member_pointer<T>::value; };

//*? is type T a POD type (allows cv-qual)
template <typename T> struct is_POD
{ 
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = is_scalar<cvt>::value || BOOST_IS_POD(cvt); 
};
template <typename T, std::size_t sz> struct is_POD<T[sz]>
{ static const bool value = is_POD<T>::value; };

//
// is one type convertable to another?
template <class From, class To>
class is_convertible
{
 typedef char (&no)[1];
 typedef char (&yes)[2];
#  if defined(__BORLANDC__) || defined(__GNUC__)
 // This workaround for Borland breaks the EDG C++ frontend,
 // so we only use it for Borland.
 template <class T>
 struct checker
 {
   static no check(...);
   static yes check(T);
 };
 static From from;
public:
 static const bool value = sizeof( checker<To>::check(from) ) == sizeof(yes);

#  else // not __BORLANDC__
 static no check(...);
 static yes check(To);
 static From from;
public:
 static const bool value = sizeof( check(from) ) == sizeof(yes);
#  endif
 void foo(); // avoid warning about all members being private
};

template <class From>
struct is_convertible<From, void>
{
   static const bool value = false;
};
template <class To>
struct is_convertible<void, To>
{
   static const bool value = false;
};
template <>
struct is_convertible<void, void>
{
   static const bool value = true;
};
//
// get the alignment of some arbitrary type:
namespace detail{
// hack for MWCW:
template <class T>
class alignment_of_hack
{
   char c;
   T t;
   alignment_of_hack();
};
}
template <class T>
class alignment_of
{
public:
   static const unsigned value = sizeof(detail::alignment_of_hack<T>) - sizeof(T);
};
//
// references have to be treated specially, assume
// that a reference is just a special pointer:
template <class T>
class alignment_of<T&>
{
public:
   static const unsigned value = alignment_of<T*>::value;
};

//
// JM 7Jan2000
// 
namespace detail{
template <typename T, bool b, bool b2>
struct empty_helper{ static const bool value = false; };

template <typename T>
struct empty_helper_t1 : public T
{
#ifdef __MWERKS__
   empty_helper_t1();  // hh compiler bug workaround
#endif
   int i[256];
};
struct empty_helper_t2 { int i[256]; };

template <typename T>
struct empty_helper<T, true, false>
{
   static const bool value = (sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2));
};
}

//*? is type T an empty composite type (allows cv-qual)
template <typename T> struct is_empty
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   static const bool value = ::boost::detail::empty_helper<T, is_class<T>::value , is_convertible<T,int>::value>::value
                     || BOOST_IS_EMPTY(cvt);
};

//*? T has trivial default constructor (allows cv-qual)
template <typename T> struct has_trivial_constructor
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
  static const bool value = is_POD<T>::value
      || BOOST_HAS_TRIVIAL_CONSTRUCTOR(cvt);
};

//*? T has trivial copy constructor (allows cv-qual)
template <typename T> struct has_trivial_copy
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
  static const bool value = is_POD<T>::value
      || BOOST_HAS_TRIVIAL_COPY(cvt);
};

//*? T has trivial assignment operator (allows cv-qual)
template <typename T>
struct has_trivial_assign
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
  static const bool value = is_POD<T>::value
      || BOOST_HAS_TRIVIAL_ASSIGN(cvt);
};

//*? T has trivial destructor (allows cv-qual)
template <typename T>
struct has_trivial_destructor
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
  static const bool value = is_POD<T>::value
      || BOOST_HAS_TRIVIAL_DESTRUCTOR(cvt);
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

#endif // BOOST_DETAIL_TYPE_TRAITS_HPP







