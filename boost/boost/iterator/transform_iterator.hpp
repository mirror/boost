// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BOOST_TRANSFORM_ITERATOR_23022003THW_HPP
#define BOOST_TRANSFORM_ITERATOR_23022003THW_HPP

#include <boost/function.hpp>
#include <boost/iterator.hpp>
#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{
  template <class UnaryFunction, class Iterator, class Reference = use_default, class Value = use_default>
  class transform_iterator;

  namespace detail 
  {

    template <class UnaryFunction>
    struct function_object_result
    {
      typedef typename UnaryFunction::result_type type;
    };

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class Return, class Argument>
    struct function_object_result<Return(*)(Argument)>
    {
      typedef Return type;
    };
#endif

    // Given the transform iterator's transformation and iterator, this
    // is the type used as its traits.
    template <class UnaryFunction, class Iterator, class Reference, class Value>
    struct transform_iterator_base
    {
    private:

      // transform_iterator does not support writable/swappable iterators
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
      BOOST_STATIC_ASSERT((is_tag< readable_iterator_tag, typename access_category<Iterator>::type >::value));
#endif
 
      typedef typename mpl::apply_if<
          is_same< Reference, use_default >
        , function_object_result<UnaryFunction>
        , mpl::identity<Reference>
      >::type result_type;

      typedef typename mpl::if_<
          is_same< Value, use_default >
        , typename remove_reference< result_type >::type
        , Value
      >::type cv_value_type;

      typedef typename mpl::if_< 
          is_reference< result_type >
        , typename mpl::if_<
              is_const< cv_value_type >
            , readable_lvalue_iterator_tag
            , writable_lvalue_iterator_tag
          >::type
        , readable_iterator_tag
      >::type maximum_access_tag;
  
      typedef typename minimum_category<
          maximum_access_tag
        , typename access_category<Iterator>::type
      >::type access_category;

    public:
      typedef iterator_adaptor<
      transform_iterator<UnaryFunction, Iterator, Reference, Value>
        , Iterator
        , cv_value_type  
        , access_category
        , result_type  
      > type;
    };
  }

  template <class UnaryFunction, class Iterator, class Reference, class Value>
  class transform_iterator
    : public detail::transform_iterator_base<UnaryFunction, Iterator, Reference, Value>::type
  {
    typedef typename
    detail::transform_iterator_base<UnaryFunction, Iterator, Reference, Value>::type
    super_t;

    friend class iterator_core_access;

  public:
    transform_iterator() { }

    transform_iterator(Iterator const& x, UnaryFunction f)
      : super_t(x), m_f(f) { }

    explicit transform_iterator(Iterator const& x)
      : super_t(x)
    {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
        // don't provide this constructor if UnaryFunction is a
        // function pointer type, since it will be 0.  Too dangerous.
        BOOST_STATIC_ASSERT(is_class<UnaryFunction>::value);
#endif 
    }

    template<class OtherIterator>
    transform_iterator(
         transform_iterator<UnaryFunction, OtherIterator, Reference, Value> const& t
       , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0
    )
      : super_t(t.base()), m_f(t.functor()) {}

    UnaryFunction functor() const
      { return m_f; }

  private:
    typename super_t::reference dereference() const
    { return m_f(*this->base()); }

    // Probably should be the initial base class so it can be
    // optimized away via EBO if it is an empty class.
    UnaryFunction m_f;
  };

  template <class UnaryFunction, class Iterator>
  transform_iterator<UnaryFunction, Iterator>
  make_transform_iterator(Iterator it, UnaryFunction fun)
  {
      return transform_iterator<UnaryFunction, Iterator>(it, fun);
  }

  template <class UnaryFunction, class Iterator>
  // don't provide this generator if UnaryFunction is a
  // function pointer type.  Too dangerous.  We should probably
  // find a cheaper test than is_class<>
  typename iterators::enable_if<
      is_class<UnaryFunction>
    , transform_iterator<UnaryFunction, Iterator>
  >::type
  make_transform_iterator(Iterator it)
  {
      return transform_iterator<UnaryFunction, Iterator>(it, UnaryFunction());
  }

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION ) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
  template <class Return, class Argument, class Iterator>
  transform_iterator< Return (*)(Argument), Iterator, Return>
  make_transform_iterator(Iterator it, Return (*fun)(Argument))
  {
    return transform_iterator<Return (*)(Argument), Iterator, Return>(it, fun);
  }
#endif

} // namespace boost

#endif // BOOST_TRANSFORM_ITERATOR_23022003THW_HPP
