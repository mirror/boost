// Copyright (C) 2002 Ronald Garcia
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//

#ifndef ITERATOR_RG071801_HPP
#define ITERATOR_RG071801_HPP

//
// iterator.hpp - implementation of iterators for the
// multi-dimensional array class
//

#include "boost/multi_array/base.hpp"
#include "boost/iterator/iterator_facade.hpp"
#include "boost/iterator/reverse_iterator.hpp"
#include <cstddef>
#include <iterator>

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// iterator components
/////////////////////////////////////////////////////////////////////////

template <class T>
struct operator_arrow_proxy
{
  operator_arrow_proxy(T const& px) : value_(px) {}
  T* operator->() const { return &value_; }
  // This function is needed for MWCW and BCC, which won't call operator->
  // again automatically per 13.3.1.2 para 8
  operator T*() const { return &value_; }
  mutable T value_;
};


template <typename T, typename TPtr, std::size_t NumDims,
          typename AccessCategory, typename Reference>
class array_iterator :
    public iterator_facade<
             array_iterator<T,TPtr,NumDims,AccessCategory,Reference>,
             typename value_accessor_generator<T,NumDims>::type::value_type,
             AccessCategory,
             ::boost::random_access_traversal_tag,
             Reference
           >,
    private value_accessor_generator<T,NumDims>::type
{
  friend class iterator_core_access;
  template <typename TT, typename TP, std::size_t N, typename AC, typename R>
    friend class array_iterator;

  typedef typename value_accessor_generator<T,NumDims>::type access_t;

  typedef  iterator_facade<
             array_iterator<T,TPtr,NumDims,AccessCategory,Reference>,
             typename access_t::value_type,
             AccessCategory,
             ::boost::random_access_traversal_tag,
             Reference
           > facade_type;

  typedef typename value_accessor_generator<T,NumDims>::type access_t;
  typedef typename access_t::index index;
  typedef typename access_t::size_type size_type;

  index idx_;
  TPtr base_;
  const size_type* extents_;
  const index* strides_;
  const index* index_base_;
 
public:
  // Typedefs to circumvent ambiguities between parent classes
  typedef typename facade_type::reference reference;
  typedef typename facade_type::value_type value_type;
  typedef typename facade_type::difference_type difference_type;

  array_iterator() {}

  array_iterator(int idx, TPtr base, const size_type* extents,
                const index* strides,
                const index* index_base) :
    idx_(idx), base_(base), extents_(extents),
    strides_(strides), index_base_(index_base) { }

  template <typename OPtr, typename ORef>
  array_iterator(const
                 array_iterator<T,OPtr,NumDims,AccessCategory,ORef>& rhs)
    : idx_(rhs.idx_), base_(rhs.base_), extents_(rhs.extents_),
    strides_(rhs.strides_), index_base_(rhs.index_base_) { }


  // RG - we make our own operator->
  operator_arrow_proxy<reference>
  operator->() const
  {
    return operator_arrow_proxy<reference>(this->dereference());
  }
  

  reference dereference() const {
    return access_t::access(boost::type<reference>(),
                            idx_,
                            base_,
                            extents_,
                            strides_,
                            index_base_);
  }
  
  void increment() { ++idx_; }
  void decrement() { --idx_; }

  template <class IteratorAdaptor>
  bool equal(IteratorAdaptor& rhs) const {
    return (idx_ == rhs.idx_) &&
      (base_ == rhs.base_) &&
      (extents_ == rhs.extents_) &&
      (strides_ == rhs.strides_) &&
      (index_base_ == rhs.index_base_);
  }

  template <class DifferenceType>
  void advance(DifferenceType n) {
    idx_ += n;
  }

  template <class IteratorAdaptor>
  typename facade_type::difference_type
  distance_to(IteratorAdaptor& rhs) const {
    return rhs.idx_ - idx_;
  }


};



template <typename T, std::size_t NumDims, typename value_type,
  typename reference_type, typename tag, typename difference_type>
struct iterator_generator {
  // RG: readable_writeable is temporary until later dim-based fixes
  typedef  array_iterator<T,T*,NumDims,
             ::boost::readable_iterator_tag,reference_type> type;
};

template <typename T,  std::size_t NumDims, typename value_type,
  typename reference_type, typename tag, typename difference_type>
struct const_iterator_generator {
  // RG: readable is temporary until later dim-based fixes
  typedef array_iterator<T,const T*,NumDims,
            readable_iterator_tag,reference_type> type;
};

template <typename T, std::size_t NumDims, typename value_type,
  typename reference_type, typename tag, typename difference_type>
struct reverse_iterator_generator {
private:
  typedef typename iterator_generator<T,NumDims,value_type,reference_type,
    tag,difference_type>::type iterator_type;
public:
  typedef ::boost::reverse_iterator<iterator_type> type;
};

template <typename T,  std::size_t NumDims, typename value_type,
  typename reference_type, typename tag, typename difference_type>
struct const_reverse_iterator_generator {
private:
  typedef typename const_iterator_generator<T,NumDims,value_type,
    reference_type,tag,difference_type>::type iterator_type;
public:
  typedef ::boost::reverse_iterator<iterator_type> type;
};


} // namespace multi_array
} // namespace detail
} // namespace boost

#endif // ITERATOR_RG071801_HPP
