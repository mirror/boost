// (C) Copyright David Abrahams and Jeremy Siek 2000-2001. Permission to copy,
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
// Supplies:
//
//   template <class Incrementable> class counting_iterator_traits;
//   template <class Incrementable> class counting_iterator_policies;
//
//     Iterator traits and policies for adapted iterators whose dereferenced
//     value progresses through consecutive values of Incrementable when the
//     iterator is derferenced.
//
//   template <class Incrementable>
//     iterator_adaptor<Incrementable,
//                      counting_iterator_policies<Incrementable>,
//                      counting_iterator_traits<Incrementable> >
//   counting_iterator(Incrementable);
//
//     A function which produces an adapted counting iterator over values of
//     Incrementable.
// 
// Revision History
// 24 Jan 2001  initial revision, based on Jeremy Siek's
//              boost/pending/integer_range.hpp (David Abrahams)

#ifndef BOOST_COUNTING_ITERATOR_HPP_DWA20000119
# define BOOST_COUNTING_ITERATOR_HPP_DWA20000119

# include <boost/config.hpp>
# include <boost/detail/iterator.hpp>
# include <boost/pending/iterator_adaptors.hpp>
# include <boost/type_traits.hpp>
# include <boost/detail/numeric_traits.hpp>
# ifndef BOOST_NO_LIMITS
#  include <limits>
# endif

namespace boost {

namespace detail {

  // Template class counting_iterator_traits_select -- choose an
  // iterator_category and difference_type for a counting_iterator at
  // compile-time based on whether or not it wraps an integer or an iterator,
  // using "poor man's partial specialization".
  template <bool is_integer> struct counting_iterator_traits_select;

  // Incrementable is an iterator type
  template <>
  struct counting_iterator_traits_select<false>
  {
      template <class Incrementable>
      struct traits
      {
       private:
          typedef boost::detail::iterator_traits<Incrementable> x;
       public:
          typedef typename x::iterator_category iterator_category;
          typedef typename x::difference_type difference_type;
      };
  };

  // Incrementable is a numeric type
  template <>
  struct counting_iterator_traits_select<true>
  {
      template <class Incrementable>
      struct traits
      {
          typedef typename
            boost::detail::numeric_traits<Incrementable>::difference_type
          difference_type;
          typedef std::random_access_iterator_tag iterator_category;
      };
  };

  // Template class distance_policy_select -- choose a policy for computing the
  // distance between counting_iterators at compile-time based on whether or not
  // the iterator wraps an integer or an iterator, using "poor man's partial
  // specialization".

  template <bool is_integer> struct distance_policy_select;

  // A policy for wrapped iterators
  template <>
  struct distance_policy_select<false>
  {
      template <class Distance, class Incrementable>
      struct policy {
          static Distance distance(Incrementable x, Incrementable y)
              { return boost::detail::distance(x, y); }
      };
  };

  // A policy for wrapped numbers
  template <>
  struct distance_policy_select<true>
  {
      template <class Distance, class Incrementable>
      struct policy {
          static Distance distance(Incrementable x, Incrementable y)
              { return numeric_distance(x, y); }
      };
  };

  // Compute the distance over arbitrary numeric and/or iterator types
  template <class Distance, class Incrementable>
  Distance any_distance(Incrementable start, Incrementable finish, Distance* = 0)
  {
      return distance_policy_select<
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
         std::numeric_limits<Incrementable>::is_specialized
#else
          // Causes warnings with GCC, but how else can I detect numeric types
          // at compile-time?
          (boost::is_convertible<int,Incrementable>::value &&
           boost::is_convertible<Incrementable,int>::value)
#endif
           >::template policy<Distance, Incrementable>::distance(start, finish);
  }
  
} // namespace detail

template <class Incrementable>
struct counting_iterator_traits {
 private:
    typedef typename detail::counting_iterator_traits_select<(
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
        std::numeric_limits<Incrementable>::is_specialized
#else
        // Causes warnings with GCC, but how else can I detect numeric types at
        // compile-time?
        (boost::is_convertible<int,Incrementable>::value &&
         boost::is_convertible<Incrementable,int>::value)
#endif
    )>::template traits<Incrementable> traits;
 public:
    typedef Incrementable value_type;
    typedef const Incrementable& reference;
    typedef const value_type* pointer;
    typedef typename traits::difference_type difference_type;
    typedef typename traits::iterator_category iterator_category;
};

template <class Incrementable>
struct counting_iterator_policies : public default_iterator_policies
{
    const Incrementable& dereference(type<const Incrementable&>, const Incrementable& i) const
        { return i; }

    template <class Difference, class Iterator1, class Iterator2>
    Difference distance(type<Difference>, const Iterator1& x,
                        const Iterator2& y) const
    {
        return boost::detail::any_distance<Difference>(x, y);//,(Difference*)());
    }
};

// Manufacture a counting iterator for an arbitrary incrementable type
template <class Incrementable>
inline iterator_adaptor<Incrementable,
    counting_iterator_policies<Incrementable>,
    counting_iterator_traits<Incrementable> >
counting_iterator(Incrementable x)
{
    return iterator_adaptor<Incrementable,
        counting_iterator_policies<Incrementable>,
        counting_iterator_traits<Incrementable> >(x);
}

} // namespace boost

#endif // BOOST_COUNTING_ITERATOR_HPP_DWA20000119
