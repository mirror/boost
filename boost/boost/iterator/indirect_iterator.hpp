// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BOOST_INDIRECT_ITERATOR_23022003THW_HPP
#define BOOST_INDIRECT_ITERATOR_23022003THW_HPP

#include <boost/iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/iterator/iterator_traits.hpp>

#include <boost/type_traits/remove_cv.hpp>

#include <boost/python/detail/indirect_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/has_xxx.hpp>

#ifdef BOOST_MPL_NO_AUX_HAS_XXX
# include <boost/shared_ptr.hpp>
# include <boost/scoped_ptr.hpp>
# include <boost/mpl/bool.hpp>
# include <memory>
#endif 

#include <boost/iterator/detail/config_def.hpp> // must be last #include

namespace boost
{
  template <class Iter, class Value, class Category, class Reference, class Difference>
  class indirect_iterator;

  namespace detail
  {
    template <class T>
    struct iterator_is_mutable
        : mpl::not_<
              boost::python::detail::is_reference_to_const<
                 typename iterator_reference<T>::type
              >
          >
    {
    };

    // If the Value parameter is unspecified, we use this metafunction
    // to deduce the default type
    template <class Dereferenceable>
    struct default_indirect_value
    {
        typedef typename mpl::if_<
            iterator_is_mutable<Dereferenceable>
        , typename iterator_value<Dereferenceable>::type
        , typename iterator_value<Dereferenceable>::type const
        >::type type;
    };

    // If the Reference parameter is unspecified, we use this metafunction
    // to deduce the default type
    template <class Dereferenceable, class Value>
    struct default_indirect_reference
    {
        struct use_value_ref { typedef Value& type; };

        typedef typename 
        mpl::apply_if<
            is_same<Value, use_default>
            , iterator_reference<Dereferenceable>
            , use_value_ref
        >::type type;
    };
    
    template <class Iter, class Value, class Category, class Reference, class Difference>
    struct indirect_base
    {
        typedef typename iterator_traits<Iter>::value_type dereferenceable;
        
        typedef iterator_adaptor<
            indirect_iterator<Iter, Value, Category, Reference, Difference>
          , Iter
          , typename ia_dflt_help<
                Value, default_indirect_value<dereferenceable>
            >::type
          , Category
          , typename ia_dflt_help<
                Reference, default_indirect_reference<dereferenceable, Value>
            >::type
          , Difference
        > type;
    };

    template <>
    struct indirect_base<int, int, int, int, int> {};
  } // namespace detail

    
  template <
      class Iterator
    , class Value = use_default
    , class Category = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public detail::indirect_base<
        Iterator, Value, Category, Reference, Difference
      >::type
  {
      typedef typename detail::indirect_base<
          Iterator, Value, Category, Reference, Difference
      >::type super_t;

      friend class iterator_core_access;

   public:
      indirect_iterator() {}

      indirect_iterator(Iterator iter)
        : super_t(iter) {}

      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0
      )
        : super_t(y.base())
      {}

  private:    
      typename super_t::reference dereference() const
      {
# if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
          return const_cast<super_t::reference>(**this->base());
# else
          return **this->base();
# endif 
      }
  };

  template <class Iter>
  inline
  indirect_iterator<Iter> make_indirect_iterator(Iter x)
  {
    return indirect_iterator<Iter>(x);
  }

  template <class Traits, class Iter>
  inline
  indirect_iterator<Iter,Traits> make_indirect_iterator(Iter x, Traits* = 0)
  {
    return indirect_iterator<Iter, Traits>(x);
  }

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_INDIRECT_ITERATOR_23022003THW_HPP
