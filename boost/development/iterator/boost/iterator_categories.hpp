#ifndef BOOST_ITERATOR_CATEGORIES_HPP
#define BOOST_ITERATOR_CATEGORIES_HPP

#include <boost/config.hpp>
#include <boost/type_traits/conversion_traits.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/pending/ct_if.hpp>
#include <boost/detail/iterator.hpp>

namespace boost {

  // Return Type Categories
  struct readable_iterator_tag { };
  struct writable_iterator_tag { };
  struct swappable_iterator_tag { };
  struct mutable_lvalue_iterator_tag : 
    virtual public writable_iterator_tag,
    virtual public readable_iterator_tag { };
  struct constant_lvalue_iterator_tag : 
    virtual public readable_iterator_tag { };

  // Traversal Categories
  struct forward_traversal_tag { };
  struct bidirectional_traversal_tag : public forward_traversal_tag { };
  struct random_access_traversal_tag : public bidirectional_traversal_tag { };

  struct error_iterator_tag { };

  // Inherit from iterator_base if your iterator defines its own
  // return_category and traversal_category. Otherwise, the "old style"
  // iterator category will be mapped to the return_category and
  // traversal_category.
  struct new_iterator_base { };

  namespace detail {

    struct return_category_from_nested_type {
      template <typename Iterator> struct bind {
        typedef typename Iterator::return_category type;
      };
    };

    struct traversal_category_from_nested_type {
      template <typename Iterator> struct bind {
        typedef typename Iterator::traversal_category type;
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
        random_access_traversal_tag,
        typename ct_if<
          is_convertible<Category*, std::bidirectional_iterator_tag*>::value,
          bidirectional_traversal_tag,
          forward_traversal_tag
          >::type
        >::type type;
    };

    struct return_category_from_old_traits {
      template <typename Iterator> class bind {
        typedef boost::detail::iterator_traits<Iterator> OldTraits;
        typedef typename OldTraits::iterator_category Cat;
        typedef typename OldTraits::value_type value_type;
      public:
        typedef iter_category_to_return<Cat, value_type>::type type;
      };      
    };

    struct traversal_category_from_old_traits {
      template <typename Iterator> class bind {
        typedef boost::detail::iterator_traits<Iterator> OldTraits;
        typedef typename OldTraits::iterator_category Cat;
      public:
        typedef iter_category_to_traversal<Cat>::type type;
      };      
    };

    template <typename Iterator>
    class choose_return_category {
      typedef typename ct_if<is_convertible<Iterator*,
                                            new_iterator_base*>::value,
                             return_category_from_nested_type,
                             return_category_from_old_traits>::type Choice;
    public:
      typedef typename Choice:: template bind<Iterator>::type type;
    };

    template <typename Iterator>
    class choose_traversal_category {
      typedef typename ct_if<is_convertible<Iterator*,
                                            new_iterator_base*>::value,
                             traversal_category_from_nested_type,
                             traversal_category_from_old_traits>::type Choice;
    public:
      typedef typename Choice:: template bind<Iterator>::type type;
    };
    
  } // namespace detail
  
  template <class Iterator>
  struct return_category {
    typedef typename detail::choose_return_category<Iterator>::type type;
  };


  template <class Iterator>
  struct traversal_category {
    typedef typename detail::choose_traversal_category<Iterator>::type type;
  };

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

  template <typename T>
  struct return_category<T*>
  {
    typedef typename ct_if<is_const<T>::value,
      constant_lvalue_iterator_tag,
      mutable_lvalue_iterator_tag>::type type;
  };

  template <typename T>
  struct traversal_category<T*>
  {
    typedef random_access_traversal_tag type;
  };

#endif

} // namespace boost

#endif // BOOST_ITERATOR_CATEGORIES_HPP
