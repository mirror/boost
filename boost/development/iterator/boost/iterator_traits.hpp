#ifndef BOOST_ITERATOR_TRAITS_HPP
#define BOOST_ITERATOR_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/type_traits/conversion_traits.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/pending/ct_if.hpp>
#include <boost/detail/iterator.hpp>

namespace boost {

  // Traversal Categories
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

  struct error_iterator_tag { };

  // Inherit from iterator_base if your iterator defines its own
  // return_category and traversal_category. Otherwise, the "old style"
  // iterator category will be mapped to the return_category and
  // traversal_category.
  struct new_iterator_base { };

  namespace detail {

    struct iter_traits_from_nested_types {
      template <typename Iterator> struct bind {
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::return_category return_category;
        typedef typename Iterator::traversal_category traversal_category;
      };
    };

    template <typename ValueType>
    struct choose_lvalue_return {
      typedef typename ct_if<is_const<ValueType>::value,
			     boost::constant_lvalue_iterator_tag,
			     boost::mutable_lvalue_iterator_tag>::type type;
    };
    
    
    template <typename Category, typename ValueType>
    struct iter_category_to_return {
      typedef typename ct_if<
        is_convertible<Category*, std::forward_iterator_tag*>::value,
        typename choose_lvalue_return<ValueType>::type,
        typename ct_if<
          is_convertible<Category*, std::input_iterator_tag*>::value,
          boost::readable_iterator_tag,
          typename ct_if<
            is_convertible<Category*, std::output_iterator_tag*>::value,
            boost::writable_iterator_tag,
            boost::error_iterator_tag
          >::type
       >::type
      >::type type;
    };

    template <typename Category>
    struct iter_category_to_traversal {
      typedef typename ct_if<
        is_convertible<Category*, std::random_access_iterator_tag*>::value,
        boost::random_access_iterator_tag,
        typename ct_if<
          is_convertible<Category*, std::bidirectional_iterator_tag*>::value,
          boost::bidirectional_iterator_tag,
          typename ct_if<
            is_convertible<Category*, std::forward_iterator_tag*>::value,
            boost::forward_iterator_tag,
            boost::single_pass_iterator_tag>::type
          >::type
        >::type type;
    };

    struct iter_traits_from_old_traits {
      template <typename Iterator> class bind {
        typedef boost::detail::iterator_traits<Iterator> OldTraits;
        typedef typename OldTraits::iterator_category Cat;
      public:
        typedef typename OldTraits::value_type value_type;
        typedef typename OldTraits::reference reference;
        typedef typename OldTraits::pointer pointer;
        typedef typename OldTraits::difference_type difference_type;
        typedef iter_category_to_return<Cat,value_type>::type return_category;
        typedef iter_category_to_traversal<Cat>::type traversal_category;
      };      
    };

    template <typename Iterator>
    class choose_iter_traits {
      typedef typename ct_if<is_convertible<Iterator*,
                                            new_iterator_base*>::value,
                             iter_traits_from_nested_types,
                             iter_traits_from_old_traits>::type Choice;
    public:
      typedef typename Choice:: template bind<Iterator> type;
    };
    
  } // namespace detail
  
  template <typename Iterator>
  class iterator_traits
    : public detail::choose_iter_traits<Iterator>::type { };

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

  template <typename T>
  struct iterator_traits<T*>
  {
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef typename ct_if<is_const<T>::value,
			   boost::constant_lvalue_iterator_tag,
			   boost::mutable_lvalue_iterator_tag>::type
      return_category;
    typedef boost::random_access_iterator_tag traversal_category;
  };

#endif

} // namespace boost

#endif // BOOST_ITERATOR_TRAITS_HPP
