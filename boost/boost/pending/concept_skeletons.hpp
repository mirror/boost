// $COPYRIGHT

#ifndef BOOST_CONCEPT_SKELETONS_HPP
#define BOOST_CONCEPT_SKELETONS_HPP

#include <iterator>

namespace boost {
  template <class T>
  struct input_proxy {
    operator const T&() { return t; }
    static T t;
  };
  template <class T>
  class trivial_iterator_skeleton
  {
    typedef trivial_iterator_skeleton self;
  public:
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    typedef T value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;
    typedef void iterator_category;
#endif
    trivial_iterator_skeleton() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    input_proxy<T> operator*() { return input_proxy<T>(); }
  };
}

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace std {
  template <class T>
  struct iterator_traits< boost::trivial_iterator_skeleton<T> >
  {
    typedef T value_type;
  };
}
#endif

namespace boost {
  template <class T>
  struct input_output_proxy {
    input_output_proxy<T>& operator=(const T&) { return *this; }
    operator T() { return t; }
    T t;
  };
  template <class T>
  class mutable_trivial_iterator_skeleton
  {
    typedef mutable_trivial_iterator_skeleton self;
  public:
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    typedef T value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;
    typedef void iterator_category;
#endif
    mutable_trivial_iterator_skeleton() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    input_output_proxy<T> operator*() { return input_output_proxy<T>(); }
    T x;
  };
}

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace std {
  template <class T>
  struct iterator_traits< boost::mutable_trivial_iterator_skeleton<T> >
  {
    typedef T value_type;
  };
}
#endif

namespace boost {

  template <class T>
  class input_iterator_skeleton
  {
  public:
    typedef input_iterator_skeleton self;
  public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef void difference_type;
    input_iterator_skeleton() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return x; }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    T x;
  };

  struct output_proxy {
    template <class T>
    output_proxy& operator=(const T&) { return *this; }
  };

  class output_iterator_skeleton
  {
  public:
    typedef output_iterator_skeleton self;
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef output_proxy value_type;
    typedef output_proxy reference;
    typedef void pointer;
    typedef void difference_type;
    output_iterator_skeleton() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return output_proxy(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class forward_iterator_skeleton
  {
  public:
    typedef forward_iterator_skeleton self;
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef void difference_type;
    forward_iterator_skeleton() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return x; }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
    T x;
  };
  

} // namespace boost

#endif // BOOST_CONCEPT_SKELETONS_H
