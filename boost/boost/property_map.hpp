//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

#ifndef BOOST_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_HPP

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
    enum ePropertyMapID { READABLE_PA, WRITABLE_PA, 
                          READ_WRITE_PA, LVALUE_PA, OP_BRACKET_PA, 
                          RAND_ACCESS_ITER_PA, LAST_PA };
  }
  struct readable_property_map_tag { enum { id = detail::READABLE_PA }; };
  struct writable_property_map_tag { enum { id = detail::WRITABLE_PA }; };
  struct read_write_property_map_tag :
    public readable_property_map_tag,
    public writable_property_map_tag
  { enum { id = detail::READ_WRITE_PA }; };

  struct lvalue_property_map_tag : public read_write_property_map_tag
  { enum { id = detail::LVALUE_PA }; };

  //=========================================================================
  // property_traits specialization for pointers

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  // The user will just have to create their own specializations for
  // other pointers types if the compiler does not have partial
  // specializations. Sorry!
  template <>
  struct property_traits<long*> {
    typedef long value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<unsigned long*> {
    typedef unsigned long value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<int*> {
    typedef int value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<unsigned int*> {
    typedef unsigned int value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<short*> {
    typedef short value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<unsigned short*> {
    typedef unsigned short value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<char*> {
    typedef char value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<unsigned char*> {
    typedef unsigned char value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<signed char*> {
    typedef signed char value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<bool*> {
    typedef bool value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<float*> {
    typedef float value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<double*> {
    typedef double value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  template <>
  struct property_traits<long double*> {
    typedef long double value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };

  // This may need to be turned off for some older compilers that don't have
  // wchar_t intrinsically.
# ifndef BOOST_NO_INTRINSIC_WCHAR_T
  template <>
  struct property_traits<wchar_t*> {
    typedef wchar_t value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag   category;
  };
# endif

#else
  template <class T>
  struct property_traits<T*> {
    typedef T value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag category;
  };
#endif

#ifndef BOOST_MSVC
  // MSVC doesn't have Koenig lookup, so the user has to
  // do boost::get() anyways, and the using clause
  // doesn't really work for MSVC.
} // namespace boost
#endif

  // These need to go in global namespace because Koenig
  // lookup does not apply to T*.

  // V must be convertible to T
  template <class T, class V>
  inline void put(T* pa, std::ptrdiff_t k, const V& val) { pa[k] = val;  }

  template <class T>
  inline const T& get(const T* pa, std::ptrdiff_t k) { return pa[k]; }

  template <class T>
  inline T& at(T* pa, std::ptrdiff_t k) { return pa[k]; }

  template <class T>
  inline const T& at(const T* pa, std::ptrdiff_t k) { return pa[k]; }

#ifndef BOOST_MSVC
namespace boost {
  using ::put;
  using ::get;
  using ::at;
#endif

  //=========================================================================
  // concept checks for property maps

  template <class PA, class Key>
  struct ReadablePropertyMap_concept
  {
    typedef typename property_traits<PA>::key_type key_type;
    typedef typename property_traits<PA>::category Category;
    typedef boost::readable_property_map_tag ReadableTag;
    void constraints() {
      REQUIRE2(Category, ReadableTag, Convertible);

      val = get(pa, k);
    }
    PA pa;
    Key k;
    typename property_traits<PA>::value_type val;
  };

  template <class PA, class Key>
  struct WritablePropertyMap_concept
  {
    typedef typename property_traits<PA>::key_type key_type;
    typedef typename property_traits<PA>::category Category;
    typedef boost::writable_property_map_tag WritableTag;
    void constraints() {
      REQUIRE2(Category, WritableTag, Convertible);
      put(pa, k, val);
    }
    PA pa;
    Key k;
    typename property_traits<PA>::value_type val;
  };

  template <class PA, class Key>
  struct ReadWritePropertyMap_concept
  {
    typedef typename property_traits<PA>::category Category;
    typedef boost::read_write_property_map_tag ReadWriteTag;
    void constraints() {
      REQUIRE2(PA, Key, ReadablePropertyMap);
      REQUIRE2(PA, Key, WritablePropertyMap);
      REQUIRE2(Category, ReadWriteTag, Convertible);
    }
  };

  template <class PA, class Key>
  struct LvaluePropertyMap_concept
  {
    typedef typename property_traits<PA>::category Category;
    typedef boost::lvalue_property_map_tag LvalueTag;
    typedef const typename property_traits<PA>::value_type& const_reference;
    void constraints() { 
      REQUIRE2(PA, Key, ReadWritePropertyMap);
      REQUIRE2(Category, LvalueTag, Convertible);

      const_reference ref = pa[k];
    }
    PA pa;
    Key k;
  };

  template <class PA, class Key>
  struct Mutable_LvaluePropertyMap_concept
  {
    typedef typename property_traits<PA>::category Category;
    typedef boost::lvalue_property_map_tag LvalueTag;
    typedef typename property_traits<PA>::value_type& reference;
    void constraints() { 
      REQUIRE2(PA, Key, ReadWritePropertyMap);
      REQUIRE2(Category, LvalueTag, Convertible);

      reference ref = pa[k];
    }
    PA pa;
    Key k;
  };

  struct identity_property_map;

  // A helper class for constructing a property map
  // from a class that implements operator[]

  template <class T, class PropertyMap>
  struct put_get_at_helper { };

  template <class PropertyMap, class T, class K>
  inline T 
  get(const put_get_at_helper<T,PropertyMap>& pa, const K& k)
  {
    T v = static_cast<const PropertyMap&>(pa)[k];
    return v;
  }
  template <class PropertyMap, class T, class K, class V>
  inline void
  put(put_get_at_helper<T,PropertyMap>& pa, K k, const V& v)
  {
    static_cast<PropertyMap&>(pa)[k] = v;
  }
  template <class PropertyMap, class T, class K>
  inline T& 
  at(put_get_at_helper<T,PropertyMap>& pa, K k)
  {
    T& v = static_cast<PropertyMap&>(pa)[k];
    return v;
  }

  //=========================================================================
  // Adapter to turn a RandomAccessIterator into a property map

  template <class RandomAccessIterator, 
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
     class T, class R,
#else
     class T = typename std::iterator_traits<RandomAccessIterator>::value_type,
     class R = typename std::iterator_traits<RandomAccessIterator>::reference,
#endif
     class IDfunc = identity_property_map>
  class random_access_iterator_property_map 
    : public boost::put_get_at_helper< T, 
        random_access_iterator_property_map<RandomAccessIterator,
        T, R, IDfunc> >
  {
  public:
    typedef void key_type; 
    typedef T value_type;
    typedef boost::lvalue_property_map_tag category;

    inline random_access_iterator_property_map(
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
  inline random_access_iterator_property_map<
    RAIter,
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference,
    ID >
  make_iterator_property_map(RAIter iter, ID id) {
    REQUIRE(RAIter, RandomAccessIterator);
    typedef random_access_iterator_property_map<
    RAIter,
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference,
    ID >    PA;
    return PA(iter, id);
  }
#endif
  template <class RAIter, class Value, class ID>
  inline random_access_iterator_property_map<
    RAIter, Value, Value&, ID>
  make_iterator_property_map(RAIter iter, ID id, Value) {
    REQUIRE(RAIter, RandomAccessIterator);
    typedef random_access_iterator_property_map<
      RAIter, Value, Value&, ID> PMap;
    return PMap(iter, id);
  }


  //=========================================================================
  // A property map that applies the identity function
  struct identity_property_map
    : public boost::put_get_at_helper<std::size_t, 
        identity_property_map>
  {
    typedef void key_type;
    typedef std::size_t value_type; // ? -JGS
    typedef boost::readable_property_map_tag category;

    template <class Vertex>
    inline Vertex operator[](const Vertex& v) const { return v; }
  };

  //=========================================================================
  // A property map that does not do anything, for
  // when you have to supply a property map, but don't need it.
  class dummy_property_map 
    : public boost::put_get_at_helper< int, dummy_property_map  > 
  {
  public:
    typedef void          key_type; 
    typedef int    value_type;
    typedef boost::lvalue_property_map_tag category;
    inline dummy_property_map() : c(0) { }
    inline dummy_property_map(value_type cc) : c(cc) { }
    inline dummy_property_map(const dummy_property_map& x)
      : c(x.c) { }
    template <class Vertex>
    inline value_type& operator[](Vertex) { return c; }
    template <class Vertex>
    inline const value_type& operator[](Vertex)  const { return c; }
   protected:
    value_type c;
  };


} // namespace boost


#endif /* BOOST_PROPERTY_MAP_HPP */

