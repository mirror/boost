// Boost.Signals library
//
// Copyright (C) 2001-2002 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
 
// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS_TRACKABLE_HPP
#define BOOST_SIGNALS_TRACKABLE_HPP

#include <boost/type_traits.hpp>
#include <boost/signals/connection.hpp>
#include <boost/pending/ct_if.hpp>
#include <boost/ref.hpp>
#include <boost/mem_fn.hpp>
#include <boost/utility/addressof.hpp>
#include <list>
#include <vector>

namespace boost {

namespace detail {
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  template<typename T>
  typename ct_if<(is_pointer<T>::value), 
                 type_traits::yes_type, 
                 type_traits::no_type>::type
  is_pointerlike_helper(const T&, int); 
#else
  template<typename T>
  typename ct_if<(is_pointer<T>::value), 
                 type_traits::yes_type, 
                 type_traits::no_type>::type
  is_pointerlike_helper(const T&, long); 
#endif 

  template<typename T>
  type_traits::yes_type is_pointerlike_helper(const T*, int);

  template<typename T>
  class is_pointerlike
  {
    static T t;

  public:
    BOOST_STATIC_CONSTANT(bool, 
                          value = (sizeof(is_pointerlike_helper(t, 0)) == 
                                   sizeof(type_traits::yes_type)));
  };
} // end namespace detail

namespace BOOST_SIGNALS_NAMESPACE {
  // Base class for "trackable" objects that can be tracked when they are
  // bound in slot target functions. When a trackable object is destroyed,
  // the signal/slot connections are disconnected automatically.
  class trackable {
  private:
    static void signal_disconnected(void* obj, void* data);

    friend class detail::signal_base_impl;
    friend class detail::slot_base;
    void signal_connected(connection, BOOST_SIGNALS_NAMESPACE::detail::bound_object&) const;
    
  protected:
    trackable() : connected_signals(), dying(false) {}
    trackable(const trackable&) : connected_signals(), dying(false) {}
    ~trackable();
    
    trackable& operator=(const trackable&)
    {
      connected_signals.clear();
      return *this;
    }
    
  private:
    typedef std::list<connection> connection_list;
    typedef connection_list::iterator connection_iterator;
    
    // List of connections that this object is part of
    mutable connection_list connected_signals;
    
    // True when the object is being destroyed
    mutable bool dying;
  };

  namespace detail {
    template<bool Cond> struct truth {};

    // A visitor that adds each trackable object to a vector
    class bound_objects_visitor {
    public:
      bound_objects_visitor(std::vector<const trackable*>& v) : 
        bound_objects(v) 
      {
      }

      template<typename T>
      void operator()(const T& t) const
      {
        decode(t, 0);
      }

    private:
      // decode() decides between a reference wrapper and anything else
      template<typename T>
      void decode(const reference_wrapper<T>& t, int) const
      {
        add_if_trackable(t.get_pointer());
      }

      template<typename T>
      void decode(const T& t, long) const
      {
        typedef ::boost::detail::is_pointerlike<T> pointerlike;
        typedef truth<pointerlike::value> is_a_pointer;
        maybe_get_pointer(t, is_a_pointer());
      }

      // maybe_get_pointer() decides between pointerlike objects (raw pointers,
      // smart pointers, etc) and anything else
      template<typename T>
      void maybe_get_pointer(const T& t, truth<true>) const
      {
        // Get the actual raw pointer 
        add_if_trackable(get_pointer(t));
      }

      template<typename T>
      void maybe_get_pointer(const T& t, truth<false>) const
      {
        // Take the address of this object, because the object itself may be
        // trackable
        add_if_trackable(addressof(t));
      }

      // add_if_trackable() adds trackable objects to the list of bound objects
      inline void add_if_trackable(const trackable* b) const
      {
        if (b) {
          bound_objects.push_back(b);
        }
      }

      inline void add_if_trackable(const void*) const
      {
      }

      mutable std::vector<const trackable*>& bound_objects;
    };
  } // end namespace detail
} // end namespace BOOST_SIGNALS_NAMESPACE

} // end namespace boost

#endif // BOOST_SIGNALS_TRACKABLE_HPP
