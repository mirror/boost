// -- algorithm.hpp -- Boost Lambda Library -----------------------------------
// Copyright (C) 2002 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
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

#ifndef BOOST_LAMBDA_ALGORITHM_HPP
#define BOOST_LAMBDA_ALGORITHM_HPP

#include "boost/lambda/core.hpp"

#include <algorithm>

namespace boost {
  namespace lambda {

namespace ll {

// for_each ---------------------------------

struct for_each : public has_sig {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<3, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::for_each(a, b, c); }
};

// find  ---------------------------------

struct find : public has_sig {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<1, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C>
  A
  operator()(A a, B b, const C& c) const
  { return ::std::find(a, b, c); }
};


// find_if  ---------------------------------

struct find_if : public has_sig {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<1, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C>
  A
  operator()(A a, B b, C c) const
  { return ::std::find_if(a, b, c); }
};

// find_end  ---------------------------------

struct find_end : public has_sig {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<1, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C, class D>
  A
  operator()(A a, B b, C c, D d) const
  { return ::std::find_end(a, b, c, d); }

  template <class A, class B, class C, class D, class E>
  A
  operator()(A a, B b, C c, D d, E e) const
  { return ::std::find_end(a, b, c, d, e); }

};

// find_first_of  ---------------------------------

struct find_first_of : public has_sig {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<1, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C, class D>
  A
  operator()(A a, B b, C c, D d) const
  { return ::std::find_first_of(a, b, c, d); }

  template <class A, class B, class C, class D, class E>
  A
  operator()(A a, B b, C c, D d, E e) const
  { return ::std::find_first_of(a, b, c, d, e); }

};


// transform --------------------------------

struct transform : public has_sig {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<
          boost::tuples::length<Args>::value - 2, 
          Args
        >::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return std::transform(a, b, c, d);}

  template <class A, class B, class C, class D, class E>
  D
  operator()(A a,  B b,  C c,  D d,  E e)
  { return std::transform(a, b, c, d, e);}

};


} // end of ll namespace

// There is no good way to call an overloaded member function in a 
// lambda expression. 
// The macro below defines a function object class for calling a
// const_iterator returning member function of a container.

#define CALL_MEMBER(X)					\
struct call_##X : public has_sig {			\
template <class Args>					\
  struct sig {						\
    typedef typename boost::remove_const<		\
      typename boost::remove_reference<			\
        typename boost::tuples::element<1, Args>::type	\
       >::type						\
     >::type::const_iterator type;			\
  };							\
							\
  template<class T>					\
  typename T::const_iterator				\
  operator()(const T& t) const				\
  {							\
    return t.X();					\
  }							\
};

// create call_begin and call_end classes
CALL_MEMBER(begin)
CALL_MEMBER(end)

#undef CALL_MEMBER

} // end of lambda namespace
} // end of boost namespace



#endif
