// (C) Copyright Jeremy Siek 2002. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#ifndef BOOST_ITERATOR_ARCHETYPES_HPP
#define BOOST_ITERATOR_ARCHETYPES_HPP

#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/operators.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_cv.hpp>

#include <boost/mpl/aux_/msvc_eti_base.hpp>

#include <cstddef>

namespace boost
{

  template <class Value, class AccessCategory>
  struct access_archetype;

  template <class Derived, class Value, class AccessCategory, class TraversalCategory>
  struct traversal_archetype;

  namespace detail {

    template <class T>
    struct assign_proxy
    {
      assign_proxy& operator=(T);
    };

    template <class T>
    struct read_write_proxy :
      assign_proxy<T>
    {
      operator T();
    };

    template <class T>
    struct arrow_proxy
    {
      T const* operator->() const;
    };

    struct no_operator_brackets {};

    template <class ValueType>
    struct readable_operator_brackets
    {
      ValueType operator[](std::ptrdiff_t n) const;
    };

    template <class ValueType>
    struct writable_operator_brackets
    {
      read_write_proxy<ValueType> operator[](std::ptrdiff_t n) const;
    };

    template <class Value, class AccessCategory, class TraversalCategory>
    struct operator_brackets :
      mpl::if_< is_tag<random_access_traversal_tag, TraversalCategory>,
                 mpl::if_< is_tag<writable_iterator_tag, AccessCategory>,
                           writable_operator_brackets< Value >,
                           mpl::if_< is_tag<readable_iterator_tag, AccessCategory>,
                                     readable_operator_brackets<Value>,
                                     no_operator_brackets > >,
                 no_operator_brackets >::type
    {
    };

    template <class TraversalCategory>
    struct traversal_archetype_impl
    {
        template <class Derived,class Value> struct archetype;
    };

    template <class Derived, class Value, class TraversalCategory>
    struct traversal_archetype_
      : mpl::aux::msvc_eti_base<
           typename traversal_archetype_impl<TraversalCategory>::template archetype<Derived,Value>
        >::type
    {};

    template <>
    struct traversal_archetype_impl<incrementable_traversal_tag>
    {
        template<class Derived, class Value>
        struct archetype
        {
            typedef void difference_type;

            Derived& operator++();
            Derived  operator++(int) const;
        };
    };

    template <>
    struct traversal_archetype_impl<single_pass_traversal_tag>
    {
        template<class Derived, class Value>
        struct archetype
            : public equality_comparable< traversal_archetype_<Derived, Value, single_pass_traversal_tag> >,
              public traversal_archetype_<Derived, Value, incrementable_traversal_tag>
        {
        };
    };

    template <class Derived, class Value>
    bool operator==(traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&,
                    traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&);
  
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
  // doesn't seem to pick up != from equality_comparable
    template <class Derived, class Value>
    bool operator!=(traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&,
                    traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&);
#endif 
    template <>
    struct traversal_archetype_impl<forward_traversal_tag>
    {
        template<class Derived, class Value>
        struct archetype
            : public traversal_archetype_<Derived, Value, single_pass_traversal_tag>
        {
            typedef std::ptrdiff_t difference_type;
        };
    };

    template <>
    struct traversal_archetype_impl<bidirectional_traversal_tag>
    {
        template<class Derived, class Value>
        struct archetype
            : public traversal_archetype_<Derived, Value, forward_traversal_tag>
        {
            Derived& operator--();
            Derived  operator--(int) const;
        };
    };

    template <>
    struct traversal_archetype_impl<random_access_traversal_tag>
    {
        template<class Derived, class Value>
        struct archetype
            : public partially_ordered<traversal_archetype_<Derived, Value, random_access_traversal_tag> >,
              public traversal_archetype_<Derived, Value, bidirectional_traversal_tag> 
        {
            Derived& operator+=(std::ptrdiff_t);
            Derived& operator-=(std::ptrdiff_t);
        };
    };

    template <class Derived, class Value>
    Derived& operator+(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                       std::ptrdiff_t);

    template <class Derived, class Value>
    Derived& operator+(std::ptrdiff_t,
                       traversal_archetype_<Derived, Value, random_access_traversal_tag> const&);

    template <class Derived, class Value>
    Derived& operator-(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                       std::ptrdiff_t);

    template <class Derived, class Value>
    std::ptrdiff_t operator-(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                             traversal_archetype_<Derived, Value, random_access_traversal_tag> const&);

    template <class Derived, class Value>
    bool operator<(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                   traversal_archetype_<Derived, Value, random_access_traversal_tag> const&);

    struct bogus_type;

    template <class Value>
    struct convertible_type
      : mpl::if_< is_const<Value>,
                  typename remove_const<Value>::type,
                  bogus_type >
    {};

  } // namespace detail


  template <class> struct undefined;
  
  template <class AccessCategory>
  struct access_archetype_impl
  {
      template <class Value> struct archetype;
  };

  template <class Value, class AccessCategory>
  struct access_archetype
    : mpl::aux::msvc_eti_base<
          typename access_archetype_impl<AccessCategory>::template archetype<Value>
      >::type
  {
  };

  template <>
  struct access_archetype_impl<readable_iterator_tag>
  {
      template <class Value>
      struct archetype
      {
          typedef typename remove_cv<Value>::type value_type;
          typedef Value                           reference;
          typedef Value*                          pointer;

          value_type operator*() const;

          detail::arrow_proxy<Value> operator->() const;
      };
  };

  template <>
  struct access_archetype_impl<writable_iterator_tag>
  {
      template <class Value>
      struct archetype
      {
# if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
          BOOST_STATIC_ASSERT(!is_const<Value>::value);
# endif 
          typedef void value_type;
          typedef void reference;
          typedef void pointer;

          detail::assign_proxy<Value> operator*() const;
      };
  };

  template <>
  struct access_archetype_impl<readable_writable_iterator_tag>
  {
      template <class Value>
      struct archetype
        : public virtual access_archetype<Value, readable_iterator_tag>
      {
          typedef detail::read_write_proxy<Value>    reference;

          detail::read_write_proxy<Value> operator*() const;
      };
  };

  template <>
  struct access_archetype_impl<readable_lvalue_iterator_tag>
  {
      template <class Value>
      struct archetype
          : public virtual access_archetype<Value, readable_iterator_tag>
      {
          typedef Value&    reference;

          Value& operator*() const;
          Value* operator->() const;
      };
  };
  
  template <>
  struct access_archetype_impl<writable_lvalue_iterator_tag>
  {
      template <class Value>
      struct archetype
          : public virtual access_archetype<Value, readable_lvalue_iterator_tag>
      {
# if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
          BOOST_STATIC_ASSERT((!is_const<Value>::value));
# endif 
      };
  };
  

  template <class Value, class AccessCategory, class TraversalCategory>
  struct iterator_archetype;
  
  template <class Value, class AccessCategory, class TraversalCategory>
  struct traversal_archetype_base 
    : detail::operator_brackets<
          typename remove_cv<Value>::type
        , AccessCategory
        , TraversalCategory
      >
      , detail::traversal_archetype_<
            iterator_archetype<Value, AccessCategory, TraversalCategory>
          , Value
          , TraversalCategory
        >
  {
  };

  template <class Value, class AccessCategory, class TraversalCategory>
  struct iterator_archetype
    : public traversal_archetype_base<Value, AccessCategory, TraversalCategory>
    , public access_archetype<Value, AccessCategory>

      // These broken libraries require derivation from std::iterator
      // (or related magic) in order to handle iter_swap and other
      // iterator operations
# if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, < 310)          \
    || BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(0x20101))
    , public std::iterator<
         iterator_tag<AccessCategory,TraversalCategory>
       , typename access_archetype<Value, AccessCategory>::value_type
       , typename traversal_archetype_base<
             Value, AccessCategory, TraversalCategory
         >::difference_type
      >
# endif 
  {
      // Derivation from std::iterator above caused ambiguity, so now
      // we have to declare all the types here.
# if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, < 310)           \
    || BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(0x20101))
      typedef typename access_archetype<Value, AccessCategory>::value_type value_type;
      
      typedef typename access_archetype<Value, AccessCategory>::pointer pointer;
      
      typedef typename access_archetype<Value, AccessCategory>::reference reference;
      
      typedef typename traversal_archetype_base<
         Value, AccessCategory, TraversalCategory
      >::difference_type difference_type;
# endif
      
      typedef iterator_tag<AccessCategory, TraversalCategory> iterator_category; 

      iterator_archetype();
      iterator_archetype(iterator_archetype const&);

      iterator_archetype& operator=(iterator_archetype const&);

      // Optional conversion from mutable
      // iterator_archetype(iterator_archetype<typename detail::convertible_type<Value>::type, AccessCategory, TraversalCategory> const&);
  };

} // namespace boost


#endif // BOOST_ITERATOR_ARCHETYPES_HPP
