#ifndef BOOST_ITERATOR_CONCEPTS_HPP
#define BOOST_ITERATOR_CONCEPTS_HPP

#include <boost/concept_check.hpp>
#include <boost/iterator_traits.hpp>

namespace boost_concepts {
  // Used a different namespace here (instead of "boost") so that the
  // concept descriptions do not take for granted the names in
  // namespace boost.


  //===========================================================================

  template <typename Iterator>
  class ReadableIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::return_category 
      return_category;

    void constraints() {
      boost::function_requires< boost::SGIAssignableConcept<Iterator> >();
      boost::function_requires< boost::EqualityComparableConcept<Iterator> >();
      boost::function_requires< boost::DefaultConstructibleConcept<Iterator> >();
      
      boost::function_requires< 
        boost::ConvertibleConcept<return_category, boost::readable_iterator_tag> >();

      reference r = *i; // or perhaps read(x)
      value_type v(r);
      boost::ignore_unused_variable_warning(v);
    }
    Iterator i;
  };
  
  template <typename Iterator, typename ValueType>
  class WritableIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::return_category 
      return_category;

    void constraints() {
      boost::function_requires< boost::SGIAssignableConcept<Iterator> >();
      boost::function_requires< boost::EqualityComparableConcept<Iterator> >();
      boost::function_requires< boost::DefaultConstructibleConcept<Iterator> >();
      
      boost::function_requires< 
        boost::ConvertibleConcept<return_category, boost::writable_iterator_tag> >();

      *i = v; // an alternative could be something like write(x, v)
    }
    ValueType v;
    Iterator i;
  };
  
  template <typename Iterator>
  class ConstantLvalueIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::return_category 
      return_category;

    void constraints() {
      boost::function_requires< ReadableIteratorConcept<Iterator> >();
      
      boost::function_requires< 
        boost::ConvertibleConcept<return_category, 
          boost::constant_lvalue_iterator_tag> >();

      typedef typename boost::require_same<reference, const value_type&>::type req;

      reference v = *i;
      boost::ignore_unused_variable_warning(v);
    }
    Iterator i;
  };

  template <typename Iterator>
  class MutableLvalueIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::return_category 
      return_category;

    void constraints() {
      boost::function_requires< ReadableIteratorConcept<Iterator> >();
      boost::function_requires< WritableIteratorConcept<Iterator, value_type> >();
      
      boost::function_requires< 
        boost::ConvertibleConcept<return_category, 
          boost::constant_lvalue_iterator_tag> >();

      typedef typename boost::require_same<reference, value_type&>::type req;

      reference v = *i;
      boost::ignore_unused_variable_warning(v);
    }
    Iterator i;
  };
  
  //===========================================================================

  template <typename Iterator>
  class SinglePassIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::motion_category 
      motion_category;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< boost::SGIAssignableConcept<Iterator> >();
      boost::function_requires< boost::EqualityComparableConcept<Iterator> >();
      boost::function_requires< boost::DefaultConstructibleConcept<Iterator> >();

      boost::function_requires< 
        boost::ConvertibleConcept<motion_category, 
          boost::single_pass_iterator_tag> >();
      
      // difference_type must be a signed integral type

      ++i;
      (void)i++;
    }
    
    Iterator i;
  };
  
  template <typename Iterator>
  class ForwardIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::motion_category 
      motion_category;

    void constraints() {
      boost::function_requires< SinglePassIteratorConcept<Iterator> >();

      boost::function_requires< 
        boost::ConvertibleConcept<motion_category, 
          boost::forward_iterator_tag> >();
    }
  };
  
  template <typename Iterator>
  class BidirectionalIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::motion_category 
      motion_category;

    void constraints() {
      boost::function_requires< ForwardIteratorConcept<Iterator> >();
      
      boost::function_requires< 
        boost::ConvertibleConcept<motion_category, 
          boost::bidirectional_iterator_tag> >();

      --i;
      (void)i--;
    }
    Iterator i;
  };

  template <typename Iterator>
  class RandomAccessIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::motion_category 
      motion_category;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< BidirectionalIteratorConcept<Iterator> >();

      boost::function_requires< 
        boost::ConvertibleConcept<motion_category, 
          boost::random_access_iterator_tag> >();

      i += n;
      i = i + n;
      i = n + i;
      i -= n;
      i = i - n;
      n = i - j;
    }
    difference_type n;
    Iterator i, j;
  };

  //===========================================================================

  template <typename Iterator>
  class ReadableRandomAccessIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< RandomAccessIteratorConcept<Iterator> >();
      boost::function_requires< ReadableIteratorConcept<Iterator> >();
      
      reference r = i[n];
      value_type v(r);
      boost::ignore_unused_variable_warning(v);
    }
    difference_type n;
    Iterator i;
  };

  template <typename Iterator>
  class WritableRandomAccessIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< RandomAccessIteratorConcept<Iterator> >();
      boost::function_requires< WritableIteratorConcept<Iterator, value_type> >();

      i[n] = v;
      boost::ignore_unused_variable_warning(v);
    }
    difference_type n;
    value_type v;
    Iterator i;
  };

  template <typename Iterator>
  class ConstantLvalueRandomAccessIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< RandomAccessIteratorConcept<Iterator> >();
      boost::function_requires< ReadableIteratorConcept<Iterator> >();

      typedef typename boost::require_same<reference, const value_type&>::type req;

      reference v = i[n];
      boost::ignore_unused_variable_warning(v);
    }
    difference_type n;
    value_type v;
    Iterator i;
  };
  
  template <typename Iterator>
  class MutableLvalueRandomAccessIteratorConcept {
  public:
    typedef typename boost::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::iterator_traits<Iterator>::reference reference;
    typedef typename boost::iterator_traits<Iterator>::difference_type
      difference_type;

    void constraints() {
      boost::function_requires< RandomAccessIteratorConcept<Iterator> >();
      boost::function_requires< WritableIteratorConcept<Iterator, value_type> >();
      boost::function_requires< ReadableIteratorConcept<Iterator> >();

      typedef typename boost::require_same<reference, value_type&>::type req;

      reference v = i[n];
      boost::ignore_unused_variable_warning(v);
    }
    difference_type n;
    value_type v;
    Iterator i;
  };
  
} // namespace boost_concepts


#endif // BOOST_ITERATOR_CONCEPTS_HPP
