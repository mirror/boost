// $COPYRIGHT

#ifndef BOOST_CONCEPT_ARCHETYPES_HPP
#define BOOST_CONCEPT_ARCHETYPES_HPP

#include <iterator>

namespace boost {

  //===========================================================================
  // Basic Archetype Classes

  class dummy_constructor { };
  static dummy_constructor dummy_cons;


  // A type that models no concept.
  class null_archetype {
  private:
    null_archetype() { }
    null_archetype(const null_archetype&) { }
    null_archetype& operator=(const null_archetype&) { return *this; }
  public:
    null_archetype(dummy_constructor) { }
    friend void dummy_friend(); // just to avoid warnings
  };

  template <class T>
  class static_object {
  public:
    static T& get() {
      dummy_constructor d;
      static T x(d);
      return x;
    }
  };
  template <>
  class static_object<bool> {
  public:
    static bool& get() {
      static bool b;
      return b;
    }
  };

  template <class T, class Base = null_archetype>
  class left_equality_comparable_archetype : public Base {
  public:
    left_equality_comparable_archetype(dummy_constructor x) 
      : Base(x) { }
  };
  template <class T>
  bool operator==(const T&, const left_equality_comparable_archetype<T>&) 
    { return true; }
  template <class T>
  bool operator!=(const T&, const left_equality_comparable_archetype<T>&)
    { return true; }

  template <class Base = null_archetype>
  class equality_comparable_archetype : public Base {
  public:
    equality_comparable_archetype(dummy_constructor x) : Base(x) { }
  };
  template <class Base>
  bool operator==(const equality_comparable_archetype<Base>&,
		  const equality_comparable_archetype<Base>&) { return true; }
  template <class Base>
  bool operator!=(const equality_comparable_archetype<Base>&,
		  const equality_comparable_archetype<Base>&) { return true; }
  
  template <class T, class Base = null_archetype>
  class convertible_to : public Base {
  public:
    convertible_to(dummy_constructor x) : Base(x) { }
    operator const T&() const { return static_object<T>::get(); }
  };

  template <class Base = null_archetype>
  class default_constructible_archetype : public Base {
  public:
    default_constructible_archetype() : Base(dummy_cons) { }
    default_constructible_archetype(dummy_constructor x) : Base(x) { }
  };

  template <class Base = null_archetype>
  class copy_constructible_archetype : public Base {
  public:
    copy_constructible_archetype() : Base(dummy_cons) { }
    copy_constructible_archetype(const copy_constructible_archetype&)
      : Base(dummy_cons) { }
    copy_constructible_archetype(dummy_constructor x) : Base(x) { }
  };

  template <class Base = null_archetype>
  class assignable_archetype : public Base {
  public:
    assignable_archetype& operator=(const assignable_archetype&) {
      return *this;
    }
    assignable_archetype(dummy_constructor x) : Base(x) { }
  };
  

  //===========================================================================
  // Function Object Archetype Classes

  template <class Arg, class Return>
  class unary_function_archetype {
  public:
    const Return& operator()(const Arg&) { 
      return static_object<Return>::get(); 
    }
  };

  template <class Arg>
  class predicate_archetype {
    typedef convertible_to<bool> Return;
  public:
    const Return& operator()(const Arg&) { 
      return static_object<Return>::get(); 
    }
  };

  template <class Arg1, class Arg2>
  class binary_predicate_archetype {
    typedef convertible_to<bool> Return;
  public:
    const Return& operator()(const Arg1&, const Arg2&) { 
      return static_object<Return>::get(); 
    }
  };


  //===========================================================================
  // Iterator Archetype Classes

  template <class T>
  struct input_proxy {
    operator const T&() { return static_object<T>::get(); }
  };
  template <class T>
  class trivial_iterator_archetype
  {
    typedef trivial_iterator_archetype self;
  public:
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    typedef T value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;
    typedef void iterator_category;
#endif
    trivial_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    input_proxy<T> operator*() { return input_proxy<T>(); }
  };
} // namespace boost

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace std {
  template <class T>
  struct iterator_traits< boost::trivial_iterator_archetype<T> >
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
  class mutable_trivial_iterator_archetype
  {
    typedef mutable_trivial_iterator_archetype self;
  public:
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    typedef T value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;
    typedef void iterator_category;
#endif
    mutable_trivial_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    input_output_proxy<T> operator*() { return input_output_proxy<T>(); }
    T x;
  };
} // namespace boost

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace std {
  template <class T>
  struct iterator_traits< boost::mutable_trivial_iterator_archetype<T> >
  {
    typedef T value_type;
  };
}
#endif

namespace boost {

  template <class T>
  class input_iterator_archetype
  {
  public:
    typedef input_iterator_archetype self;
  public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
    input_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  struct output_proxy {
    template <class T>
    output_proxy& operator=(const T&) { return *this; }
  };

  class output_iterator_archetype
  {
  public:
    typedef output_iterator_archetype self;
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef output_proxy value_type;
    typedef output_proxy reference;
    typedef void pointer;
    typedef void difference_type;
    output_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return output_proxy(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };

  template <class T>
  class forward_iterator_archetype
  {
  public:
    typedef forward_iterator_archetype self;
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef void difference_type;
    forward_iterator_archetype() { }
    self& operator=(const self&) { return *this;  }
    bool operator==(const self&) const { return true; }
    bool operator!=(const self&) const { return true; }
    reference operator*() { return static_object<T>::get(); }
    self& operator++() { return *this; }
    self operator++(int) { return *this; }
  };
  

} // namespace boost

#endif // BOOST_CONCEPT_ARCHETYPES_H
