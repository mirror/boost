// Copyright David Abrahams 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef COUNTING_ITERATOR_DWA200348_HPP
# define COUNTING_ITERATOR_DWA200348_HPP

# include <boost/iterator/iterator_adaptor.hpp>
# include <boost/detail/numeric_traits.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/apply_if.hpp>

namespace boost {

template <class Incrementable, class Category, class Difference> class counting_iterator;

namespace detail
{
  // Try to detect numeric types at compile time in ways compatible
  // with the limitations of the compiler and library.
  template <class T>
  struct is_numeric_impl
  {
      // For a while, this wasn't true, but we rely on it below. This is a regression assert.
      BOOST_STATIC_ASSERT(::boost::is_integral<char>::value);
      
# ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      
#  if defined(BOOST_HAS_LONG_LONG)
      BOOST_STATIC_CONSTANT(
          bool, value = (
              std::numeric_limits<T>::is_specialized
            | boost::is_same<T,long long>::value
            | boost::is_same<T,unsigned long long>::value
              ));
#  else
      BOOST_STATIC_CONSTANT(bool, value = std::numeric_limits<T>::is_specialized);
#  endif
      
# else
      
#  if !defined(__BORLANDC__)
      BOOST_STATIC_CONSTANT(
          bool, value = (
              boost::is_convertible<int,T>::value
           && boost::is_convertible<T,int>::value
      ));
#  else
    BOOST_STATIC_CONSTANT(bool, value = ::boost::is_arithmetic<T>::value);
#  endif
      
# endif
  };

  template <class T>
  struct is_numeric
    : mpl::bool_<(::boost::detail::is_numeric_impl<T>::value)>
  {};
  
  template <class T>
  struct numeric_difference
  {
      typedef typename boost::detail::numeric_traits<T>::difference_type type;
  };

  BOOST_STATIC_ASSERT(is_numeric<int>::value);
  template <class Incrementable, class Category, class Difference>
  struct counting_iterator_base
  {
      typedef typename mpl::apply_if<
          is_same<Category, use_default>
        , mpl::apply_if<
              is_numeric<Incrementable>
            , mpl::identity<std::random_access_iterator_tag>
            , BOOST_ITERATOR_CATEGORY<Incrementable>
          >
        , mpl::identity<Category>
      >::type category;
      
      typedef typename mpl::apply_if<
          is_same<Difference, use_default>
        , mpl::apply_if<
              is_numeric<Incrementable>
            , numeric_difference<Incrementable>
            , iterator_difference<Incrementable>
          >
        , mpl::identity<Difference>
      >::type difference;
      
      typedef iterator_adaptor<
          counting_iterator<Incrementable, Category, Difference> // self
        , Incrementable                                          // Base
        , Incrementable                                          // value_type
        , category
        , Incrementable const&                                   // reference
        , difference
      > type;
  };

  // Template class distance_policy_select -- choose a policy for computing the
  // distance between counting_iterators at compile-time based on whether or not
  // the iterator wraps an integer or an iterator, using "poor man's partial
  // specialization".

  template <bool is_integer> struct distance_policy_select;

  // A policy for wrapped iterators
  template <class Difference, class Incrementable1, class Incrementable2>
  struct iterator_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return boost::detail::distance(x, y);
      }
  };

  // A policy for wrapped numbers
  template <class Difference, class Incrementable1, class Incrementable2>
  struct number_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return numeric_distance(x, y);
      }
  };
}

template <class Incrementable, class Category = use_default, class Difference = use_default>
class counting_iterator
  : public detail::counting_iterator_base<Incrementable, Category, Difference>::type
{
    typedef typename detail::counting_iterator_base<Incrementable, Category, Difference>::type super_t;
    friend class iterator_core_access;

 public:
    typedef typename super_t::difference_type difference_type;

    counting_iterator() { }
    
    counting_iterator(counting_iterator const& rhs) : super_t(rhs.base()) {}

    counting_iterator(Incrementable x)
      : super_t(x)
    {
    }

# if 0
    template<class OtherIncrementable>
    counting_iterator(
        counting_iterator<OtherIncrementable> const& t
      , typename enable_if_convertible<OtherIncrementable, Incrementable>::type* = 0
    )
      : super_t(t.base())
    {}
# endif 

 private:
    
    typename super_t::reference dereference() const
    {
        return this->base_reference();
    }

    template <class OtherIncrementable>
    difference_type
    distance_to(counting_iterator<OtherIncrementable> const& y) const
    {
      typedef typename mpl::if_<
          detail::is_numeric<Incrementable>
        , detail::number_distance<difference_type, Incrementable, OtherIncrementable>
        , detail::iterator_distance<difference_type, Incrementable, OtherIncrementable>
      >::type d;

      return d::distance(this->base(), y.base());
    }
};

// Manufacture a counting iterator for an arbitrary incrementable type
template <class Incrementable>
inline counting_iterator<Incrementable>
make_counting_iterator(Incrementable x)
{
  typedef counting_iterator<Incrementable> result_t;
  return result_t(x);
}


} // namespace boost::iterator

#endif // COUNTING_ITERATOR_DWA200348_HPP
