//  tuple_basic.hpp -----------------------------------------------------

// Copyright (C) 1999, 2000 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

// Outside help:
// This and that, Gary Powell.
// Fixed return types for get_head/get_tail 
// ( and other bugs ) per suggestion of Jens Maurer
// simplified element type accessors + bug fix  (Jeremy Siek)
// Several changes/additions according to suggestions by Doug Gregor, 
// William Kempf, Vesa Karvonen, John Max Skaller, Ed Brey, Beman Davis,
// David Abrahams.

// Revision history:
// 2001 08 30 David Abrahams
//      Added default constructor for cons<>.
// ----------------------------------------------------------------- 

#ifndef BOOST_TUPLE_BASIC_HPP
#define BOOST_TUPLE_BASIC_HPP


#include <utility> // needed for the assignment from pair to tuple

#include "boost/type_traits/cv_traits.hpp"
							    
namespace boost {

// -- null_type --------------------------------------------------------
struct null_type {};

// a helper function to provide a const null_type type temporary
namespace detail {
namespace tuples {
  inline const null_type cnull_type() { return null_type(); }
} // end tuples
} // end detail

// - cons forward declaration -----------------------------------------------
template <class HT, class TT> struct cons; 


// - tuple forward declaration -----------------------------------------------
template <
  class T0 = null_type, class T1 = null_type, class T2 = null_type, 
  class T3 = null_type, class T4 = null_type, class T5 = null_type, 
  class T6 = null_type, class T7 = null_type, class T8 = null_type, 
  class T9 = null_type>
class tuple; 

// tuple_length forward declaration
template<class T> struct tuple_length;



namespace detail {
namespace tuples {

// -- generate error template, referencing to non-existing members of this 
// template is used to produce compilation errors intentionally
template<class T>
class generate_error;

// tuple default argument wrappers ---------------------------------------
// Work for non-reference types, intentionally not for references
template <class T>
struct default_arg {

// Non-class temporaries cannot have qualifiers.
// To prevent f to return for example const int, we remove cv-qualifiers
// from all temporaries. 
     static typename boost::remove_cv<T>::type f() { return T(); }
};

// This is just to produce a more informative error message
// The code would fail in any case
template<class T, int N>
struct default_arg<T[N]> {
  static T* f() { 
    return generate_error<T[N]>::arrays_are_not_valid_tuple_elements; }
};
   
template <class T>
struct default_arg<T&> {
  static T& f() { 
#ifndef __sgi
    return generate_error<T>::no_default_values_for_reference_types;
#else
    // MIPSpro instantiates functions even when it should not, so
    // this technique can not be used for error checking.
    // The simple workaround is to just not have this error checking
    // with MIPSpro.
    static T x;
    return x;
#endif
  }
};

// - cons getters --------------------------------------------------------
// called: element<N>::get<RETURN_TYPE>(aTuple)

template< int N >
struct element {
  template<class RET, class HT, class TT >
  inline static RET get(const cons<HT, TT>& t)
  {
    return element<N-1>::template get<RET>(t.tail);
  }
  template<class RET, class HT, class TT >
  inline static RET get(cons<HT, TT>& t)
  {
    return element<N-1>::template get<RET>(t.tail);
  }
};

template<>
struct element<0> {
  template<class RET, class HT, class TT> 
  inline static RET get(const cons<HT, TT>& t)
  {
    return t.head;
  }
  template<class RET, class HT, class TT> 
  inline static RET get(cons<HT, TT>& t)
  {
    return t.head;
  }
};

} // end of namespace tuples
} // end of namespace detail


// -cons type accessors ----------------------------------------
// typename tuple_element<N,T>::type gets the type of the 
// Nth element ot T, first element is at index 0
// -------------------------------------------------------

template<int N, class T>
struct tuple_element
{
private:
  typedef typename T::tail_type Next;
public:
  typedef typename tuple_element<N-1, Next>::type type;
};
template<class T>
struct tuple_element<0,T>
{
  typedef typename T::head_type type;
};

// -get function templates -----------------------------------------------
// Usage: get<N>(aTuple)

// -- some traits classes for get functions

// access traits lifted from detail namespace to be part of the interface,
// (Joel de Guzman's suggestion). Rationale: get functions are part of the
// interface, so should the way to express their return types be.

template <class T> struct tuple_access_traits {
  typedef const T& const_type;
  typedef T& non_const_type;

  typedef const typename boost::remove_cv<T>::type& parameter_type;
// used as the tuple constructors parameter types
// Rationale: non-reference tuple element types can be cv-qualified.
// It should be possible to initialize such types with temporaries,
// and when binding temporaries to references, the reference must
// be non-volatile and const. 8.5.3. (5)
};

template <class T> struct tuple_access_traits<T&> {

  typedef T& const_type;
  typedef T& non_const_type;
   
  typedef T& parameter_type;   
};


// get function for non-const cons-lists, returns a reference to the element

template<int N, class HT, class TT>
inline typename tuple_access_traits<
                  typename tuple_element<N, cons<HT, TT> >::type
                >::non_const_type
get(cons<HT, TT>& c) { 
  return detail::tuples::element<N>::template 
         get<
           typename tuple_access_traits<
             typename tuple_element<N, cons<HT, TT> >::type
           >::non_const_type>(c); 
} 

// get function for const cons-lists, returns a const reference to
// the element. If the element is a reference, returns the reference
// as such (that is, can return a non-const reference)
template<int N, class HT, class TT>
inline typename tuple_access_traits<
                  typename tuple_element<N, cons<HT, TT> >::type
                >::const_type
get(const cons<HT, TT>& c) { 
  return detail::tuples::element<N>::template 
         get<
           typename tuple_access_traits<
             typename tuple_element<N, cons<HT, TT> >::type
         >::const_type>(c);
} 




// -- the cons template  --------------------------------------------------

template <class HT, class TT>
struct cons {

  typedef HT head_type;
  typedef TT tail_type;

  head_type head;
  tail_type tail;

  typename tuple_access_traits<head_type>::non_const_type 
  get_head() { return head; }

  typename tuple_access_traits<tail_type>::non_const_type 
  get_tail() { return tail; }  

  typename tuple_access_traits<head_type>::const_type 
  get_head() const { return head; }
  
  typename tuple_access_traits<tail_type>::const_type 
  get_tail() const { return tail; }  

  cons() : head(detail::tuples::default_arg<HT>::f()), tail() {}
  // the argument for head is not strictly needed, but it prevents 
  // array type elements. This is good, since array type elements 
  // cannot be supported properly in any case (no assignment, 
  // copy works only if the tails are exactly the same type, ...)
  
  cons(typename tuple_access_traits<head_type>::parameter_type h,
       const tail_type& t)
    : head (h), tail(t) {}  

  template <class T1, class T2, class T3, class T4, class T5, 
            class T6, class T7, class T8, class T9, class T10>
  cons( T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, 
        T6& t6, T7& t7, T8& t8, T9& t9, T10& t10 ) 
    : head (t1), 
      tail (t2, t3, t4, t5, t6, t7, t8, t9, t10, detail::tuples::cnull_type())
      {}

  template <class HT2, class TT2>
  cons( const cons<HT2, TT2>& u ) : head(u.head), tail(u.tail) {}

  template <class HT2, class TT2>
  cons& operator=( const cons<HT2, TT2>& u ) { 
    head=u.head; tail=u.tail; return *this; 
  }

  // must define assignment operator explicitly, implicit version is 
  // illformed if HT is a reference (12.8. (12))
  cons& operator=(const cons& u) { 
    head = u.head; tail = u.tail;  return *this; 
  }

  template <class T1, class T2>
  cons& operator=( const std::pair<T1, T2>& u ) { 
    BOOST_STATIC_ASSERT(tuple_length<cons>::value == 2); // check length = 2
    head = u.first; tail.head = u.second; return *this;
  }

  // get member functions (non-const and const)
  template <int N>
  typename tuple_access_traits<
             typename tuple_element<N, cons<HT, TT> >::type
           >::non_const_type
  get() {
    return boost::get<N>(*this); // delegate to non-member get
  }

  template <int N>
  typename tuple_access_traits<
             typename tuple_element<N, cons<HT, TT> >::type
           >::const_type
  get() const {
    return boost::get<N>(*this); // delegate to non-member get
  }
};

template <class HT>
struct cons<HT, null_type> {

  typedef HT head_type;
  typedef null_type tail_type;

  head_type head;
 
  typename tuple_access_traits<head_type>::non_const_type 
  get_head() { return head; }
  
  null_type get_tail() { return null_type(); }  

  typename tuple_access_traits<head_type>::const_type 
  get_head() const { return head; }
  
  const null_type get_tail() const { return null_type(); }  

  cons() : head(detail::tuples::default_arg<HT>::f()) {}

  cons(typename tuple_access_traits<head_type>::parameter_type h,
       const null_type& = null_type())
    : head (h) {}  

  template<class T1>
  cons(T1& t1, const null_type&, const null_type&, const null_type&, 
       const null_type&, const null_type&, const null_type&, 
       const null_type&, const null_type&, const null_type&)
  : head (t1) {}

  template <class HT2>
  cons( const cons<HT2, null_type>& u ) : head(u.head) {}
  
  template <class HT2>
  cons& operator=(const cons<HT2, null_type>& u ) 
  { head = u.head; return *this; }

  // must define assignment operator explicitely, implicit version 
  // is illformed if HT is a reference
  cons& operator=(const cons& u) { head = u.head; return *this; }

  template <int N>
  typename tuple_access_traits<
             typename tuple_element<N, cons>::type
            >::non_const_type
  get() {
    return boost::get<N>(*this);
  }

  template <int N>
  typename tuple_access_traits<
             typename tuple_element<N, cons>::type
           >::const_type
  get() const {
    return boost::get<N>(*this);
  }

};

// templates for finding out the length of the tuple -------------------

template<class T>
struct tuple_length  {
  BOOST_STATIC_CONSTANT(int, value = 1 + tuple_length<typename T::tail_type>::value);
};

template<>
struct tuple_length<null_type> {
  BOOST_STATIC_CONSTANT(int, value = 0);
};


namespace detail {
namespace tuples {

// Tuple to cons mapper --------------------------------------------------
template <class T0, class T1, class T2, class T3, class T4, 
          class T5, class T6, class T7, class T8, class T9>
struct map_tuple_to_cons
{
  typedef cons<T0, 
               typename map_tuple_to_cons<T1, T2, T3, T4, T5, 
                                          T6, T7, T8, T9, null_type>::type
              > type;
};

// The empty tuple is a null_type
template <>
struct map_tuple_to_cons<null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type>
{
  typedef null_type type;
};

} // end tuples
} // end detail

// -------------------------------------------------------------------
// -- tuple ------------------------------------------------------
template <class T0, class T1, class T2, class T3, class T4, 
          class T5, class T6, class T7, class T8, class T9>

class tuple : 
  public detail::tuples::map_tuple_to_cons<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type   
{
public:
  typedef typename 
    detail::tuples::map_tuple_to_cons<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type inherited;
  typedef typename inherited::head_type head_type;
  typedef typename inherited::tail_type tail_type;  


// tuple_access_traits<T>::parameter_type takes non-reference types as const T& 
  explicit tuple(
    typename tuple_access_traits<T0>::parameter_type t0 
      = detail::tuples::default_arg<T0>::f(),
    typename tuple_access_traits<T1>::parameter_type t1 
      = detail::tuples::default_arg<T1>::f(),
    typename tuple_access_traits<T2>::parameter_type t2 
      = detail::tuples::default_arg<T2>::f(),
    typename tuple_access_traits<T3>::parameter_type t3 
      = detail::tuples::default_arg<T3>::f(),
    typename tuple_access_traits<T4>::parameter_type t4 
      = detail::tuples::default_arg<T4>::f(),
    typename tuple_access_traits<T5>::parameter_type t5 
      = detail::tuples::default_arg<T5>::f(),
    typename tuple_access_traits<T6>::parameter_type t6 
      = detail::tuples::default_arg<T6>::f(),
    typename tuple_access_traits<T7>::parameter_type t7 
      = detail::tuples::default_arg<T7>::f(),
    typename tuple_access_traits<T8>::parameter_type t8 
      = detail::tuples::default_arg<T8>::f(),
    typename tuple_access_traits<T9>::parameter_type t9 
      = detail::tuples::default_arg<T9>::f())

        : inherited(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9) {}

  template<class U1, class U2>
  tuple(const cons<U1, U2>& p) : inherited(p) {}

  template <class U1, class U2>
  tuple& operator=(const cons<U1, U2>& k) { 
    inherited::operator=(k); 
    return *this;
  }

  template <class U1, class U2>
  tuple& operator=(const std::pair<U1, U2>& k) { 
    BOOST_STATIC_ASSERT(tuple_length<tuple>::value == 2);// check_length = 2
    this->head = k.first;
    this->tail.head = k.second; 
    return *this;
  }

};

// The empty tuple
template <>
class tuple<null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type, null_type>  : 
  public null_type 
{
public:
  typedef null_type inherited;
};


// Swallows any assignment   (by Doug Gregor)
namespace detail {
namespace tuples {

struct swallow_assign {
      
  template<typename T>
  swallow_assign& operator=(const T&) {
    return *this;
  }
};
} // namespace tuples
} // namespace detail

// "ignore" allows tuple positions to be ignored when using "tie". 
namespace {
 detail::tuples::swallow_assign ignore;
}

// ---------------------------------------------------------------------------
// The call_traits for make_tuple
// Honours the reference_wrapper class.

// Must be instantiated with plain or const plain types (not with references)

// from template<class T> foo(const T& t) : make_tuple_traits<const T>::type
// from template<class T> foo(T& t) : make_tuple_traits<T>::type

// Conversions:
// T -> T, 
// references -> compile_time_error
// reference_wrapper<T> -> T&
// const reference_wrapper<T> -> T&
// array -> const ref array


template<class T>
struct make_tuple_traits {
  typedef T type; 

  // commented away, see below  (JJ)
  //  typedef typename IF<                 
  //  boost::is_function<T>::value,
  //  T&,
  //  T>::RET type;

};
 
// The is_function test was there originally for plain function types, 
// which can't be stored as such (we must either store them as references or
// pointers). Such a type could be formed if make_tuple was called with a 
// reference to a function.
// But this would mean that a const qualified function type was formed in
// the make_tuple function and hence make_tuple can't take a function
// reference as a parameter, and thus T can't be a function type.
// So is_function test was removed.
// (14.8.3. says that type deduction fails if a cv-qualified function type
// is created. (It only applies for the case of explicitly specifying template
// args, though?)) (JJ)

template<class T>
struct make_tuple_traits<T&> {
  typedef typename
     detail::tuples::generate_error<T&>::
       do_not_use_with_reference_type error;
}; 

// Arrays can't be stored as plain types; convert them to references.
// All arrays are converted to const. This is because make_tuple takes its
// parameters as const T& and thus the knowledge of the potential 
// non-constness of actual argument is lost.
template<class T, int n>  struct make_tuple_traits <T[n]> {
  typedef const T (&type)[n];
};

template<class T, int n> 
struct make_tuple_traits<const T[n]> {
  typedef const T (&type)[n];
};

template<class T, int n>  struct make_tuple_traits<volatile T[n]> {
  typedef const volatile T (&type)[n];
};

template<class T, int n> 
struct make_tuple_traits<const volatile T[n]> {
  typedef const volatile T (&type)[n];
};

template<class T> 
struct make_tuple_traits<reference_wrapper<T> >{
  typedef T& type;
};

template<class T> 
struct make_tuple_traits<const reference_wrapper<T> >{
  typedef T& type;
};




namespace detail {
namespace tuples {

// a helper traits to make the make_tuple functions shorter (Vesa Karvonen's
// suggestion)
template <
  class T0 = null_type, class T1 = null_type, class T2 = null_type, 
  class T3 = null_type, class T4 = null_type, class T5 = null_type, 
  class T6 = null_type, class T7 = null_type, class T8 = null_type, 
  class T9 = null_type
>
struct make_tuple_mapper {
  typedef
    tuple<typename make_tuple_traits<T0>::type, 
          typename make_tuple_traits<T1>::type, 
          typename make_tuple_traits<T2>::type, 
          typename make_tuple_traits<T3>::type, 
          typename make_tuple_traits<T4>::type, 
          typename make_tuple_traits<T5>::type, 
          typename make_tuple_traits<T6>::type, 
          typename make_tuple_traits<T7>::type,
          typename make_tuple_traits<T8>::type,
          typename make_tuple_traits<T9>::type> type;
};

} // end tuples
} // end detail

// -make_tuple function templates -----------------------------------
inline tuple<> make_tuple() {
  return tuple<>(); 
}

template<class T0>
inline typename boost::detail::tuples::make_tuple_mapper<T0>::type
make_tuple(const T0& t0) {
  return typename boost::detail::tuples::make_tuple_mapper<T0>::type(t0); 
}

template<class T0, class T1>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1>::type
make_tuple(const T0& t0, const T1& t1) {
  return typename boost::detail::tuples::make_tuple_mapper<T0, T1>::type(t0, t1); 
}

template<class T0, class T1, class T2>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2) {
  return typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2>::type(t0, t1, t2); 
}

template<class T0, class T1, class T2, class T3>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3) {
  return typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3>::type
           (t0, t1, t2, t3); 
}

template<class T0, class T1, class T2, class T3, class T4>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4) {
  return typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4>::type
           (t0, t1, t2, t3, t4); 
}

template<class T0, class T1, class T2, class T3, class T4, class T5>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4, T5>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5) {
  return typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4, T5>::type
           (t0, t1, t2, t3, t4, t5); 
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4, T5, T6>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5, const T6& t6) {
  return typename boost::detail::tuples::make_tuple_mapper
           <T0, T1, T2, T3, T4, T5, T6>::type
           (t0, t1, t2, t3, t4, t5, t6); 
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
         class T7>
inline typename boost::detail::tuples::make_tuple_mapper<T0, T1, T2, T3, T4, T5, T6, T7>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5, const T6& t6, const T7& t7) {
  return typename boost::detail::tuples::make_tuple_mapper
           <T0, T1, T2, T3, T4, T5, T6, T7>::type
           (t0, t1, t2, t3, t4, t5, t6, t7); 
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
         class T7, class T8>
inline typename boost::detail::tuples::make_tuple_mapper
  <T0, T1, T2, T3, T4, T5, T6, T7, T8>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5, const T6& t6, const T7& t7,
                  const T8& t8) {
  return typename boost::detail::tuples::make_tuple_mapper
           <T0, T1, T2, T3, T4, T5, T6, T7, T8>::type
           (t0, t1, t2, t3, t4, t5, t6, t7, t8); 
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
         class T7, class T8, class T9>
inline typename boost::detail::tuples::make_tuple_mapper
  <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5, const T6& t6, const T7& t7,
                  const T8& t8, const T9& t9) {
  return typename boost::detail::tuples::make_tuple_mapper
           <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
           (t0, t1, t2, t3, t4, t5, t6, t7, t8, t9); 
}



// Tie function templates -------------------------------------------------
template<class T1>
inline tuple<T1&> tie(T1& t1) {
  return tuple<T1&> (t1);
}

template<class T1, class T2>
inline tuple<T1&, T2&> tie(T1& t1, T2& t2) {
  return tuple<T1&, T2&> (t1, t2);
}

template<class T1, class T2, class T3>
inline tuple<T1&, T2&, T3&> tie(T1& t1, T2& t2, T3& t3) {
  return tuple<T1&, T2&, T3&> (t1, t2, t3);
}

template<class T1, class T2, class T3, class T4>
inline tuple<T1&, T2&, T3&, T4&> tie(T1& t1, T2& t2, T3& t3, T4& t4) {
  return tuple<T1&, T2&, T3&, T4&> (t1, t2, t3, t4);
}

template<class T1, class T2, class T3, class T4, class T5>
inline tuple<T1&, T2&, T3&, T4&, T5&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5) {
  return tuple<T1&, T2&, T3&, T4&, T5&> (t1, t2, t3, t4, t5);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline tuple<T1&, T2&, T3&, T4&, T5&, T6&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6) {
  return tuple<T1&, T2&, T3&, T4&, T5&, T6&> (t1, t2, t3, t4, t5, t6);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7) {
  return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&> (t1, t2, t3, t4, t5, t6, t7);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, 
         class T8>
inline tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8) {
  return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&> 
           (t1, t2, t3, t4, t5, t6, t7, t8);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, 
         class T8, class T9>
inline tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, 
           T9& t9) {
  return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&> 
            (t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, 
         class T8, class T9, class T10>
inline tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&> 
tie(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, 
           T9& t9, T10& t10) {
  return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&> 
           (t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
}

} // end of namespace boost


#endif	// BOOST_TUPLE_BASIC_HPP


