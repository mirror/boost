//  Boost operators.hpp header file  ----------------------------------------//

//  (C) Copyright David Abrahams 1999. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  04 Jul 00 Fixed NO_OPERATORS_IN_NAMESPACE bugs, major cleanup and
//            refactoring of compiler workarounds, additional documentation
//            (Alexy Gurtovoy and Mark Rodgers with some help and prompting from
//            Dave Abrahams) 
//  28 Jun 00 General cleanup and integration of bugfixes from Mark Rodgers and
//            Jeremy Siek (Dave Abrahams)
//  20 Jun 00 Changes to accommodate Borland C++Builder 4 and Borland C++ 5.5
//            (Mark Rodgers)
//  20 Jun 00 Minor fixes to the prior revision (Aleksey Gurtovoy)
//  10 Jun 00 Support for the base class chaining technique was added
//            (Aleksey Gurtovoy). See documentation and the comments below 
//            for the details. 
//  12 Dec 99 Initial version with iterator operators (Jeremy Siek)
//  18 Nov 99 Change name "divideable" to "dividable", remove unnecessary
//            specializations of dividable, subtractable, modable (Ed Brey) 
//  17 Nov 99 Add comments (Beman Dawes)
//            Remove unnecessary specialization of operators<> (Ed Brey)
//  15 Nov 99 Fix less_than_comparable<T,U> second operand type for first two
//            operators.(Beman Dawes)
//  12 Nov 99 Add operators templates (Ed Brey)
//  11 Nov 99 Add single template parameter version for compilers without
//            partial specialization (Beman Dawes)
//  10 Nov 99 Initial version

// 10 Jun 00:
// An additional optional template parameter was added to most of 
// operator templates to support the base class chaining technique (see 
// documentation for the details). Unfortunately, a straightforward
// implementation of this change would have broken compatibility with the
// previous version of the library by making it impossible to use the same
// template name (e.g. 'addable') for both the 1- and 2-argument versions of
// an operator template. This implementation solves the backward-compatibility
// issue at the cost of some simplicity.
//
// One of the complications is an existence of special auxiliary class template
// 'is_chained_base<>' (see 'detail' namespace below), which is used
// to determine whether its template parameter is a library's operator template
// or not. You have to specialize 'is_chained_base<>' for each new 
// operator template you add to the library.
//
// However, most of the non-trivial implementation details are hidden behind 
// several local macros defined below, and as soon as you understand them,
// you understand the whole library implementation. 

#ifndef BOOST_OPERATORS_HPP
#define BOOST_OPERATORS_HPP

#include <boost/config.hpp>
#include <boost/iterator.hpp>

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1234
#endif

namespace boost {
namespace detail {

class empty_base {};

} // namespace detail
} // namespace boost

// In this section we supply the xxxx1 and xxxx2 forms of the operator
// templates, which are explicitly targeted at the 1-type-argument and
// 2-type-argument operator forms, respectively. Some compilers get confused
// when inline friend functions are overloaded in namespaces other than the
// global namespace. When BOOST_NO_OPERATORS_IN_NAMESPACE is defined, all of
// these templates must go in the global namespace.

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost
{
#endif

//  Basic operator classes (contributed by Dave Abrahams) ------------------//

//  Note that friend functions defined in a class are implicitly inline.
//  See the C++ std, 11.4 [class.friend] paragraph 5

template <class T, class U, class B = ::boost::detail::empty_base>
struct less_than_comparable2 : B
{
     friend bool operator<=(const T& x, const U& y) { return !(x > y); }
     friend bool operator>=(const T& x, const U& y) { return !(x < y); }
     friend bool operator>(const U& x, const T& y)  { return y < x; }
     friend bool operator<(const U& x, const T& y)  { return y > x; }
     friend bool operator<=(const U& x, const T& y) { return !(y < x); }
     friend bool operator>=(const U& x, const T& y) { return !(y > x); }
};

template <class T, class B = ::boost::detail::empty_base>
struct less_than_comparable1 : B
{
     friend bool operator>(const T& x, const T& y)  { return y < x; }
     friend bool operator<=(const T& x, const T& y) { return !(y < x); }
     friend bool operator>=(const T& x, const T& y) { return !(x < y); }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct equality_comparable2 : B
{
     friend bool operator==(const U& y, const T& x) { return x == y; }
     friend bool operator!=(const U& y, const T& x) { return !(x == y); }
     friend bool operator!=(const T& y, const U& x) { return !(y == x); }
};

template <class T, class B = ::boost::detail::empty_base>
struct equality_comparable1 : B
{
     friend bool operator!=(const T& x, const T& y) { return !(x == y); }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct multipliable2 : B
{
     friend T operator*(T x, const U& y) { return x *= y; }
     friend T operator*(const U& y, T x) { return x *= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct multipliable1 : B
{
     friend T operator*(T x, const T& y) { return x *= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct addable2 : B
{
     friend T operator+(T x, const U& y) { return x += y; }
     friend T operator+(const U& y, T x) { return x += y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct addable1 : B
{
     friend T operator+(T x, const T& y) { return x += y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct subtractable2 : B
{
     friend T operator-(T x, const U& y) { return x -= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct subtractable1 : B
{
     friend T operator-(T x, const T& y) { return x -= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct dividable2 : B
{
     friend T operator/(T x, const U& y) { return x /= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct dividable1 : B
{
     friend T operator/(T x, const T& y) { return x /= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct modable2 : B
{
     friend T operator%(T x, const U& y) { return x %= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct modable1 : B
{
     friend T operator%(T x, const T& y) { return x %= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct xorable2 : B
{
     friend T operator^(T x, const U& y) { return x ^= y; }
     friend T operator^(const U& y, T x) { return x ^= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct xorable1 : B
{
     friend T operator^(T x, const T& y) { return x ^= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct andable2 : B
{
     friend T operator&(T x, const U& y) { return x &= y; }
     friend T operator&(const U& y, T x) { return x &= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct andable1 : B
{
     friend T operator&(T x, const T& y) { return x &= y; }
};

template <class T, class U, class B = ::boost::detail::empty_base>
struct orable2 : B
{
     friend T operator|(T x, const U& y) { return x |= y; }
     friend T operator|(const U& y, T x) { return x |= y; }
};

template <class T, class B = ::boost::detail::empty_base>
struct orable1 : B
{
     friend T operator|(T x, const T& y) { return x |= y; }
};

//  incrementable and decrementable contributed by Jeremy Siek

template <class T, class B = ::boost::detail::empty_base>
struct incrementable : B
{
  friend T operator++(T& x, int)
  {
    incrementable_type tmp(x);
    ++x;
    return tmp;
  }
private: // The use of this typedef works around a Borland bug
  typedef T incrementable_type;
};

template <class T, class B = ::boost::detail::empty_base>
struct decrementable : B
{
  friend T operator--(T& x, int)
  {
    decrementable_type tmp(x);
    --x;
    return tmp;
  }
private: // The use of this typedef works around a Borland bug
  typedef T decrementable_type;
};

//  Iterator operator classes (contributed by Jeremy Siek) ------------------//

template <class T, class P, class B = ::boost::detail::empty_base>
struct dereferenceable : B
{
  P operator->() const
  { 
    return &*static_cast<const T&>(*this); 
  }
};

template <class T, class I, class R, class B = ::boost::detail::empty_base>
struct indexable : B
{
  R operator[](I n) const
  {
    return *(static_cast<const T&>(*this) + n);
  }
};

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
} // namespace boost
#endif // BOOST_NO_OPERATORS_IN_NAMESPACE


// BOOST_IMPORT_TEMPLATE1/BOOST_IMPORT_TEMPLATE2 -
//
// When BOOST_NO_OPERATORS_IN_NAMESPACE is defined we need a way to import an
// operator template into the boost namespace. BOOST_IMPORT_TEMPLATE1 is used
// for one-argument forms of operator templates; BOOST_IMPORT_TEMPLATE2 for
// two-argument forms. Note that these macros expect to be invoked from within
// boost.

#if defined(BOOST_NO_OPERATORS_IN_NAMESPACE)

#  if defined(BOOST_NO_USING_TEMPLATE)

     // Because a Borland C++ 5.5 bug prevents a using declaration from working,
     // we are forced to use inheritance for that compiler.
#    define BOOST_IMPORT_TEMPLATE2(template_name)                              \
     template <class T, class U, class B = ::boost::detail::empty_base>        \
     struct template_name : ::template_name<T, U, B> {};

#    define BOOST_IMPORT_TEMPLATE1(template_name)                              \
     template <class T, class B = ::boost::detail::empty_base>                 \
     struct template_name : ::template_name<T, B> {};

#  else

     // Otherwise, bring the names in with a using-declaration to avoid
     // stressing the compiler
#    define BOOST_IMPORT_TEMPLATE2(template_name) using ::template_name;
#    define BOOST_IMPORT_TEMPLATE1(template_name) using ::template_name;

#  endif // BOOST_NO_USING_TEMPLATE

#else // !BOOST_NO_OPERATORS_IN_NAMESPACE

  // The template is already in boost so we have nothing to do.
# define BOOST_IMPORT_TEMPLATE2(template_name)
# define BOOST_IMPORT_TEMPLATE1(template_name)

#endif // BOOST_NO_OPERATORS_IN_NAMESPACE

//
// Here's where we put it all together, defining the xxxx forms of the templates
// in namespace boost. We also define specializations of is_chained_base<> for
// the xxxx, xxxx1, and xxxx2 templates, importing them into boost:: as
// neccessary.
//
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

// is_chained_base<> - a traits class used to distinguish whether an operator
// template argument is being used for base class chaining, or is specifying a
// 2nd argument type.

namespace boost {
// A type parameter is used instead of a plain bool because Borland's compiler
// didn't cope well with the more obvious non-type template parameter.
namespace detail {
  struct true_t {};
  struct false_t {};
} // namespace detail

// Unspecialized version assumes that most types are not being used for base
// class chaining. We specialize for the operator templates defined in this
// library.
template<class T> struct is_chained_base {
  typedef ::boost::detail::false_t value;
};

} // namespace boost

// Import a 2-type-argument operator template into boost (if neccessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE2(template_name2)                  \
  BOOST_IMPORT_TEMPLATE2(template_name2)                           \
  template<class T, class U, class B>                              \
  struct is_chained_base< ::boost::template_name2<T, U, B> > {     \
    typedef ::boost::detail::true_t value;                         \
  };

// Import a 1-type-argument operator template into boost (if neccessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE1(template_name1)                  \
  BOOST_IMPORT_TEMPLATE1(template_name1)                           \
  template<class T, class B>                                       \
  struct is_chained_base< ::boost::template_name1<T, B> > {        \
    typedef ::boost::detail::true_t value;                         \
  };

// BOOST_OPERATOR_TEMPLATE(template_name) defines template_name<> such that it
// can be used for specifying both 1-argument and 2-argument forms. Requires the
// existence of two previously defined class templates named '<template_name>1'
// and '<template_name>2' which must implement the corresponding 1- and 2-
// argument forms.
//
// The template type parameter O == is_chained_base<U>::value is used to
// distinguish whether the 2nd argument to <template_name> is being used for
// base class chaining from another boost operator template or is describing a
// 2nd operand type. O == true_t only when U is actually an another operator
// template from the library. Partial specialization is used to select an
// implementation in terms of either '<template_name>1' or '<template_name>2'.
//

# define BOOST_OPERATOR_TEMPLATE(template_name)                    \
template <class T                                                  \
         ,class U = T                                              \
         ,class B = ::boost::detail::empty_base                    \
         ,class O = typename is_chained_base<U>::value             \
         >                                                         \
struct template_name : template_name##2<T, U, B> {};               \
                                                                   \
template<class T, class U, class B>                                \
struct template_name<T, U, B, ::boost::detail::true_t>             \
  : template_name##1<T, U> {};                                     \
                                                                   \
template <class T, class B>                                        \
struct template_name<T, T, B, ::boost::detail::false_t>            \
  : template_name##1<T, B> {};                                     \
                                                                   \
template<class T, class U, class B, class O>                       \
struct is_chained_base< ::boost::template_name<T, U, B, O> > {     \
  typedef ::boost::detail::true_t value;                           \
};                                                                 \
                                                                   \
BOOST_OPERATOR_TEMPLATE2(template_name##2)                         \
BOOST_OPERATOR_TEMPLATE1(template_name##1)


#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#  define BOOST_OPERATOR_TEMPLATE2(template_name2) \
        BOOST_IMPORT_TEMPLATE2(template_name2)
#  define BOOST_OPERATOR_TEMPLATE1(template_name1) \
        BOOST_IMPORT_TEMPLATE1(template_name1)

   // In this case we can only assume that template_name<> is equivalent to the
   // more commonly needed template_name1<> form.
#  define BOOST_OPERATOR_TEMPLATE(template_name)                   \
   template <class T, class B = ::boost::detail::empty_base>       \
   struct template_name : template_name##1<T, B> {};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {
    
BOOST_OPERATOR_TEMPLATE(less_than_comparable)
BOOST_OPERATOR_TEMPLATE(equality_comparable)
BOOST_OPERATOR_TEMPLATE(multipliable)
BOOST_OPERATOR_TEMPLATE(addable)
BOOST_OPERATOR_TEMPLATE(subtractable)
BOOST_OPERATOR_TEMPLATE(dividable)
BOOST_OPERATOR_TEMPLATE(modable)
BOOST_OPERATOR_TEMPLATE(xorable)
BOOST_OPERATOR_TEMPLATE(andable)
BOOST_OPERATOR_TEMPLATE(orable)

BOOST_OPERATOR_TEMPLATE1(incrementable)
BOOST_OPERATOR_TEMPLATE1(decrementable)
BOOST_OPERATOR_TEMPLATE2(dereferenceable)

// indexable doesn't follow the patterns above (it has 4 template arguments), so
// we just write out the compiler hacks explicitly.
#ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
# ifdef BOOST_NO_USING_TEMPLATE
   template <class T, class I, class R, class B = ::boost::detail::empty_base>
   struct indexable : ::indexable<T,I,R,B> {};
# else
   using ::indexable;
# endif
#endif

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, class I, class R, class B>
struct is_chained_base< ::boost::indexable<T, I, R, B> > {
  typedef ::boost::detail::true_t operator_template_type;
};
#endif

#undef BOOST_OPERATOR_TEMPLATE
#undef BOOST_OPERATOR_TEMPLATE2
#undef BOOST_OPERATOR_TEMPLATE1
#undef BOOST_IMPORT_TEMPLATE1
#undef BOOST_IMPORT_TEMPLATE2

// The following 'operators' classes can only be used portably if the derived class
// declares ALL of the required member operators.
template <class T, class U>
struct operators2
    : less_than_comparable2<T,U
    , equality_comparable2<T,U
    , addable2<T,U
    , subtractable2<T,U
    , multipliable2<T,U
    , dividable2<T,U
    , modable2<T,U
    , orable2<T,U
    , andable2<T,U
    , xorable2<T,U
      > > > > > > > > > > {};

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, class U = T>
struct operators : operators2<T, U> {};

template <class T> struct operators<T, T>
#else
template <class T> struct operators
#endif
    : less_than_comparable<T
    , equality_comparable<T
    , addable<T
    , subtractable<T
    , multipliable<T
    , dividable<T
    , modable<T
    , orable<T
    , andable<T
    , xorable<T
    , incrementable<T
    , decrementable<T
      > > > > > > > > > > > > {};

//  Iterator helper classes (contributed by Jeremy Siek) -------------------//
template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct forward_iterator_helper
  : equality_comparable<T
  , incrementable<T
  , dereferenceable<T,P
  , boost::iterator<std::forward_iterator_tag, V, D
    > > > > {};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct bidirectional_iterator_helper
  : equality_comparable<T
  , incrementable<T
  , decrementable<T
  , dereferenceable<T,P
  , boost::iterator<std::bidirectional_iterator_tag, V, D
    > > > > > {};

template <class T,
          class V, 
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct random_access_iterator_helper
  : equality_comparable<T
  , less_than_comparable<T
  , incrementable<T
  , decrementable<T
  , dereferenceable<T,P
  , addable2<T,D
  , subtractable2<T,D
  , indexable<T,D,R
  , boost::iterator<std::random_access_iterator_tag, V, D
    > > > > > > > > >
{
#ifndef __BORLANDC__
  friend D requires_difference_operator(const T& x, const T& y) {
    return x - y;
  }
#endif
}; // random_access_iterator_helper

} // namespace boost

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1234
#endif

#endif // BOOST_OPERATORS_HPP
