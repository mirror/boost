//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

#ifndef BOOST_PROPERTY_ACCESSOR_HPP
#define BOOST_PROPERTY_ACCESSOR_HPP

#include <iterator>
#include <boost/config.hpp>
#include <boost/pending/cstddef.hpp>
#include <boost/pending/concept_checks.hpp>

namespace boost {

  //=========================================================================
  // property_traits class

  template <typename PA>
  struct property_traits {
    typedef typename PA::key_type key_type;
    typedef typename PA::value_type value_type; 
    typedef typename PA::category   category;
  };

  //=========================================================================
  // property_traits category tags

  namespace detail {
    enum ePropertyAccessorID { READABLE_PA, WRITABLE_PA, 
			       READ_WRITE_PA, LVALUE_PA, OP_BRACKET_PA, 
			       RAND_ACCESS_ITER_PA, LAST_PA };
  }
  struct readable_property_accessor_tag { enum { id = detail::READABLE_PA }; };
  struct writable_property_accessor_tag { enum { id = detail::WRITABLE_PA }; };
  struct read_write_property_accessor_tag :
    public readable_property_accessor_tag,
    public writable_property_accessor_tag
  { enum { id = detail::READ_WRITE_PA }; };

  struct lvalue_property_accessor_tag : public read_write_property_accessor_tag
  { enum { id = detail::LVALUE_PA }; };

  //additions to handle operator bracket and random access iterators
  struct readable_op_bracket_tag
    : public boost::readable_property_accessor_tag
  { enum { id = detail::OP_BRACKET_PA }; };
  struct writable_op_bracket_tag
    : public boost::writable_property_accessor_tag
  { enum { id = detail::OP_BRACKET_PA }; };
  struct read_write_op_bracket_tag
    : public boost::read_write_property_accessor_tag 
  { enum { id = detail::OP_BRACKET_PA }; };
  struct lvalue_op_bracket_tag
    : public boost::lvalue_property_accessor_tag
  { enum { id = detail::OP_BRACKET_PA }; };
#if 0 // forget why I used this...
  struct random_access_iterator_pa_tag
    : public boost::lvalue_property_accessor_tag
  { enum { id = detail::RAND_ACCESS_ITER_PA }; };    
#endif
 
  //=========================================================================
  // property_traits specialization for pointers

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  // The user will just have to create their own specializations for
  // other pointers types if the compiler does not have partial
  // specializations. Sorry!
  template <>
  struct property_traits<int*> {
    typedef int value_type;
    typedef ptrdiff_t key_type;
    typedef random_access_iterator_pa_tag   category;
  };
  template <>
  struct property_traits<std::size_t*> {
    typedef std::size_t value_type;
    typedef ptrdiff_t key_type;
    typedef random_access_iterator_pa_tag   category;
  };
#else
  template <class T>
  struct property_traits<T*> {
    typedef T value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_op_bracket_tag category;
  };
#endif

  // V must be convertible to T
  template <class T, class V>
  inline void put(T* pa, std::ptrdiff_t k, const V& val) { pa[k] = val;  }

  template <class T>
  inline const T& get(const T* pa, std::ptrdiff_t k) { return pa[k]; }

  template <class T>
  inline T& at(T* pa, std::ptrdiff_t k) { return pa[k]; }

  template <class T>
  inline const T& at(const T* pa, std::ptrdiff_t k) { return pa[k]; }

  //=========================================================================
  // concept checks for property accessors

  template <class PA, class Key>
  struct ReadablePropertyAccessor_concept
  {
    typedef typename property_traits<PA>::key_type key_type;
    typedef typename property_traits<PA>::category Category;
    typedef boost::readable_property_accessor_tag ReadableTag;
    void constraints() {
      REQUIRE2(Category, ReadableTag, Convertible);

      val = get(pa, k);
    }
    PA pa;
    Key k;
    typename property_traits<PA>::value_type val;
  };

  template <class PA, class Key>
  struct WritablePropertyAccessor_concept
  {
    typedef typename property_traits<PA>::key_type key_type;
    typedef typename property_traits<PA>::category Category;
    typedef boost::writable_property_accessor_tag WritableTag;
    void constraints() {
      REQUIRE2(Category, WritableTag, Convertible);
      put(pa, k, val);
    }
    PA pa;
    Key k;
    typename property_traits<PA>::value_type val;
  };

  template <class PA, class Key>
  struct ReadWritePropertyAccessor_concept
  {
    typedef typename property_traits<PA>::category Category;
    typedef boost::read_write_property_accessor_tag ReadWriteTag;
    void constraints() {
      REQUIRE2(PA, Key, ReadablePropertyAccessor);
      REQUIRE2(PA, Key, WritablePropertyAccessor);
      REQUIRE2(Category, ReadWriteTag, Convertible);
    }
  };

  template <class PA, class Key>
  struct LvaluePropertyAccessor_concept
  {
    typedef typename property_traits<PA>::category Category;
    typedef boost::lvalue_property_accessor_tag LvalueTag;
    void constraints() { 
      REQUIRE2(PA, Key, ReadWritePropertyAccessor);
      REQUIRE2(Category, LvalueTag, Convertible);

      val = at(pa, k);
      at(pa, k) = val;
    }
    PA pa;
    Key k;
    typename property_traits<PA>::value_type val;
  };

} // namespace boost

#include <boost/detail/property_accessor.hpp>

namespace boost {

  //=========================================================================
  // Adapter to turn a RandomAccessIterator into a property accessor

  template <class RandomAccessIterator, 
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
     class T, class R,
#else
     class T = typename std::iterator_traits<RandomAccessIterator>::value_type,
     class R = typename std::iterator_traits<RandomAccessIterator>::reference,
#endif
     class IDfunc = identity_property_accessor>
  class random_access_iterator_property_accessor 
    : public boost::detail::put_get_at_helper< T, 
        random_access_iterator_property_accessor<RandomAccessIterator,
        T, R, IDfunc> >
  {
  public:
    typedef void key_type; 
    typedef T value_type;
    typedef boost::lvalue_op_bracket_tag category;

    inline random_access_iterator_property_accessor(
      RandomAccessIterator cc = RandomAccessIterator(), 
      const IDfunc& _id = IDfunc() ) 
      : iter(cc), id(_id) { }
    template <class Key>
    inline R operator[](Key v) const { return *(iter + id[v]) ; }
  protected:
    RandomAccessIterator iter;
    IDfunc id;
  };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class RAIter, class ID>
  inline random_access_iterator_property_accessor<
    RAIter,
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference,
    ID >
  create_random_access_iter_pa(RAIter iter, ID id) {
    typedef random_access_iterator_property_accessor<
    RAIter,
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference,
    ID >    PA;
    return PA(iter, id);
  }
#else
  // add VC++ workarounds...
#endif

  //=========================================================================
  // A property accessor that applies the identity function
  struct identity_property_accessor
    : public boost::detail::put_get_at_helper<std::size_t, 
        identity_property_accessor>
  {
    typedef void key_type;
    typedef std::size_t value_type; // ? -JGS
    typedef boost::readable_op_bracket_tag category;

    template <class Vertex>
    inline Vertex operator[](Vertex v) const { return v; }
  };

  //=========================================================================
  // A property accessor that does not do anything, for
  // when you have to supply a property accessor, but don't need it.
  class dummy_property_accessor 
    : public boost::detail::put_get_at_helper< int, dummy_property_accessor  > 
  {
  public:
    typedef void          key_type; 
    typedef int    value_type;
    typedef boost::lvalue_op_bracket_tag category;
    inline dummy_property_accessor() : c(0) { }
    inline dummy_property_accessor(value_type cc) : c(cc) { }
    inline dummy_property_accessor(const dummy_property_accessor& x)
      : c(x.c) { }
    template <class Vertex>
    inline value_type& operator[](Vertex) { return c; }
    template <class Vertex>
    inline const value_type& operator[](Vertex)  const { return c; }
   protected:
    value_type c;
  };

  //=========================================================================
  // An adapter that takes a property accessor and adds operator[]
  // using a proxy class for the reference type.

  // The pa2dec_adaptor isn't very good because it
  // doesn't handle lvalue property accessors.
  // Need to use property_accessor_adaptor instead, but
  // had VC++ porting problems with that... -JGS
  template <class PA, class T, class K>
  inline detail::pa2dec_adaptor<PA, T, K>
  adapt_property_accessor(PA pa, T, K) {
    return detail::pa2dec_adaptor<PA, T, K>(pa);
  }


} // namespace boost


#endif /* BOOST_PROPERTY_ACCESSOR_HPP */

