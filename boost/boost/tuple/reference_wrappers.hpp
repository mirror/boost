// -- reference_wrappers - Boost Tuple Library -----------------------------

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
//
// For more information, see http://www.boost.org 

// ----------------------------------------------------------------- 

#ifndef BOOST_TUPLE_REFERENCE_WRAPPERS_HPP
#define BOOST_TUPLE_REFERENCE_WRAPPERS_HPP

namespace boost {


// reference wrappers -------------------------------------------------------
  
// These wrappers are handle classes that hold references to objects.

// reference_wrapper is used to specify that a tuple element should be 
// a reference to the wrapped object - rather than a copy of it.
// The wrapper acts as a disguise for passing non-const reference 
// parameters via a reference to const parameter.

template<class T>
class reference_wrapper { 
  T& x; 
public:
  explicit 
  reference_wrapper(T& t) : x(t) {} 
  operator T&() const { return x; }
};

// store as a reference to T
template<class T> 
inline const reference_wrapper<T> ref(T& t) { 
  return reference_wrapper<T>(t); 
}

// store as a reference to const T
template<class T> 
inline const reference_wrapper<const T> cref(const T& t) {
  return reference_wrapper<const T>(t); 
}
   
} // end of namespace boost


#endif	// BOOST_TUPLE_REFERENCE_WRAPPERS_HPP
