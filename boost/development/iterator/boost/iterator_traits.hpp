#ifndef BOOST_ITERATOR_TRAITS_HPP
#define BOOST_ITERATOR_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/type_traits.hpp>

namespace boost {
  
  template <typename Iterator>
  struct iterator_traits {
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::return_category return_category;
    typedef typename Iterator::motion_category motion_category;
  };

  // Motion Categories
  struct single_pass_iterator_tag { };
  struct forward_iterator_tag : public single_pass_iterator_tag { };
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
  
  // Return Type Categories
  struct readable_iterator_tag { };
  struct writable_iterator_tag { };
  struct mutable_lvalue_iterator_tag : virtual public writable_iterator_tag,
    virtual public readable_iterator_tag { };
  struct constant_lvalue_iterator_tag : public readable_iterator_tag { };
  
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

  namespace detail {
    template <bool IsConst>
    struct pointer_return_category {
      typedef constant_lvalue_iterator_tag type;
    };
    template <>
    struct pointer_return_category<false> {
      typedef mutable_lvalue_iterator_tag type;
    };
  } // namespace detail

  template <typename T>
  struct iterator_traits<T*> {
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef typename detail::pointer_return_category<is_const<T>::value>::type
      return_category;
    typedef random_access_iterator_tag motion_category;
  };

#endif

} // namespace boost

#endif // BOOST_ITERATOR_TRAITS_HPP
