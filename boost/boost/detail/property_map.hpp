#ifndef BOOST_DETAIL_PROPERTY_MAP_HPP
#define BOOST_DETAIL_PROPERTY_MAP_HPP

#include <boost/pending/ct_if.hpp>

namespace boost {

  struct identity_property_map;

  namespace detail {

    // A helper class for constructing a property map
    // from a class that implements operator[]

    template <class T, class PA>
    struct put_get_at_helper { };

  } // namespace detail

  template <class PA, class T, class K>
  inline T 
  get(const detail::put_get_at_helper<T,PA>& pa, const K& k)
  {
    T v = static_cast<const PA&>(pa)[k];
    return v;
  }
  template <class PA, class T, class K, class V>
  inline void
  put(detail::put_get_at_helper<T,PA>& pa, K k, const V& v)
  {
    static_cast<PA&>(pa)[k] = v;
  }
  template <class PA, class T, class K>
  inline T& 
  at(detail::put_get_at_helper<T,PA>& pa, K k)
  {
    T& v = static_cast<PA&>(pa)[k];
    return v;
  }

} // namespace boost

#if 0
namespace boost {
  namespace detail {
    // The following is a set of wrapper classes that map the
    // put()/get()/at() property map interface of boost to the
    // operator[] interface used inside boost algorithms.

    template <class PA>
    class readable_adaptor
    {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      readable_adaptor(PA pa) : _pa(pa) { }

      value_type operator[](const key_type& x) {
	return get(_pa, x);
      }
    protected:
      PA _pa;
    };

    template <class PA>
    class write_proxy {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      write_proxy(PA pa, key_type key) : _pa(pa), _key(key) { }

      write_proxy<PA>& operator=(const value_type& val) {
	put(_pa, _key, val);
	return *this;
      }
    protected:
      PA _pa;
      value_type _key;
    };

    template <class PA>
    class writable_adaptor
    {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      writable_adaptor(PA pa) : _pa(pa) { }

      write_proxy<PA> operator[](const key_type& key) {
	return write_proxy<PA>(_pa, key);
      }
    protected:
      PA _pa;
    };

    template <class PA>
    class read_write_proxy {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      read_write_proxy(PA pa, key_type key) : _pa(pa), _key(key) { }

      read_write_proxy<PA> operator=(const value_type& val) {
	put(_pa, _key, val);
	return *this;
      }
      operator value_type() { 
	return get(_pa, _key); 
      }
    protected:
      PA _pa;
      key_type _key;
    };

    template <class PA>
    class read_write_adaptor
    {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      read_write_adaptor(PA pa) : _pa(pa) { }

      read_write_proxy<PA> operator[](const key_type& key) {
	return read_write_proxy<PA>(_pa, key);
      }
    protected:
      PA _pa;
    };

    template <class PA>
    class lvalue_proxy {
    public:
    typedef typename property_traits<PA>::key_type key_type;
    typedef typename property_traits<PA>::value_type value_type;

      lvalue_proxy(PA pa, key_type key) : _pa(pa), _key(key) { }

      lvalue_proxy<PA> operator=(const value_type& val) {
	at(_pa, _key) = val;
	return *this;
      }
      operator value_type&() { 
	return at(_pa, _key); 
      }
    protected:
      PA _pa;
      value_type _key;
    };

    template <class PA>
    class lvalue_adaptor
    {
    public:
      typedef typename property_traits<PA>::key_type key_type;
      typedef typename property_traits<PA>::value_type value_type;

      lvalue_adaptor(PA pa) : _pa(pa) { }

      lvalue_proxy<PA> operator[](const key_type& key) {
	return lvalue_proxy<PA>(_pa, key);
      }
    protected:
      PA _pa;
    };

    struct undefined_property_map_category { };

    // ID_PA only used with random access iterators
    template <class PA, class ID_PA = identity_property_map>
    struct property_map_adaptor {
      typedef typename property_traits<PA>::category Cat;
      enum { id = Cat::id };
      typedef
	typename ct_if<int(id) == READABLE_PA, readable_adaptor<PA>,
	  typename ct_if<int(id) == WRITABLE_PA, writable_adaptor<PA>,
	    typename ct_if<int(id)==READ_WRITE_PA, read_write_adaptor<PA>,
	      typename ct_if<int(id) == LVALUE_PA, lvalue_adaptor<PA>,
		  typename ct_if<int(id) == OP_BRACKET_PA, 
                    PA, // no adaptor needed
		    undefined_property_map_category
		  >::type
	      >::type
	    >::type
	  >::type
	>::type type;
    };

    // This won't work very well with lvalue property maps.
    // Need to figure out a way to make property_map_adaptor
    // work with VC++. -JGS
    template <class PA, class T, class K>
    class pa2dec_proxy {
    public:
      typedef K key_type;
      typedef T value_type;

      pa2dec_proxy(PA pa, key_type key) : _pa(pa), _key(key) { }

      pa2dec_proxy operator=(const value_type& val) {
	put(_pa, _key, val);
	return *this;
      }
      pa2dec_proxy& operator++() {
	T tmp = get(_pa, _key);
	++tmp;
	put(_pa, _key, tmp);
	return *this;
      }
      pa2dec_proxy operator++(int) { 
	pa2dec_proxy t = *this;
	++(*this); 
	return t; 
      }
      pa2dec_proxy& operator--() {
	T tmp = get(_pa, _key);
	++tmp;
	put(_pa, _key, tmp);
	return *this;
      }
      pa2dec_proxy operator--(int) { 
	pa2dec_proxy t = *this;
	++(*this); 
	return t; 
      }
      pa2dec_proxy operator+=(const value_type& val) {
	T tmp = get(_pa, _key);
	tmp += val;
	put(_pa, _key, tmp);
	return *this;
      }
      pa2dec_proxy operator-=(const value_type& val) {
	T tmp = get(_pa, _key);
	tmp -= val;
	put(_pa, _key, tmp);
	return *this;
      }
      operator value_type() const {
	return get(_pa, _key); 
      }
    protected:
      PA _pa;
      key_type _key;
    };
    template <class PA, class T, class K>
    inline bool operator==(const pa2dec_proxy<PA,T,K>& x,
			   const pa2dec_proxy<PA,T,K>& y)
    {
      T xv(x), yv(y);
      return xv == yv;
    }
    template <class PA, class T, class K>
    inline bool operator<(const pa2dec_proxy<PA,T,K>& x,
			  const pa2dec_proxy<PA,T,K>& y)
    {
      T xv(x), yv(y);
      return xv < yv;
    }

    template <class PA, class T, class K>
    class pa2dec_adaptor
      : public put_get_at_helper<T, pa2dec_adaptor<PA,T,K> >
    {
    public:
      typedef K key_type;
      typedef T value_type;
      typedef boost::read_write_property_map_tag category;

      //    pa2dec_adaptor() { }
      pa2dec_adaptor(PA pa) : _pa(pa) { }

      pa2dec_proxy<PA,T,K> operator[](const key_type& key) {
	return pa2dec_proxy<PA,T,K>(_pa, key);
      }

      pa2dec_proxy<PA,T,K> operator[](const key_type& key) const {
	return pa2dec_proxy<PA,T,K>(_pa, key);
      }
    protected:
      PA _pa;
    };


  } // namespace detail
} // namespace boost
#endif

#endif // BOOST_DETAIL_PROPERTY_MAP_HPP
