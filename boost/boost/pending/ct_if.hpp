// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

// The ct_if implementation that avoids partial specialization is
// based on the IF class by Ulrich W. Eisenecker and Krzysztof
// Czarnecki.

#ifndef BOOST_CT_IF_HPP
#define BOOST_CT_IF_HPP

#include <boost/config.hpp>

namespace boost {

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  template <int cond, class A, class B>
  struct ct_if { typedef A type; };
  template <class A, class B>
  struct ct_if<0, A, B> { typedef B type; };

#else

  namespace detail {

    template <int condition, class A, class B> struct IF;
    template <int condition> struct SlectSelector;
    struct SelectFirstType;
    struct SelectSecondType;
    
    struct SelectFirstType {
      template<class A, class B>
      struct Template {	typedef A type; };
    };
    
    struct SelectSecondType {
      template<class A, class B>
      struct Template { typedef B type; };
    };
    
    template<int condition>
    struct SlectSelector {
      typedef SelectFirstType type;
    };
    
    template <>
    struct SlectSelector<0> {
      typedef SelectSecondType type;
    };

  } // namespace detail
    
  template<int condition, class A, class B>
  struct ct_if
  {
    typedef typename detail::SlectSelector<condition>::type Selector;
    typedef typename Selector::template Template<A, B>::type type;
  };
  
#endif

} // namespace boost

#endif // BOOST_CT_IF_HPP

