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
#include <boost/utility/addressof.hpp>
#include <list>
#include <vector>

namespace boost {

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
        maybe_get_pointer(t.get(), truth<false>());
      }

      template<typename T>
      void decode(T& t, long) const
      {
        typedef truth<(is_pointer<T>::value)> is_a_pointer;
        maybe_get_pointer(t, is_a_pointer());
      }

      // maybe_get_pointer() decides between a pointer and a non-pointer
      template<typename T>
      void maybe_get_pointer(T& t, truth<true>) const
      {
        //        add_if_trackable(t);
        maybe_get_pointer(*t, truth<false>());
      }

      template<typename T>
      void maybe_get_pointer(T& t, truth<false>) const
      {
        // Take the address of this object, because the object itself may be
        // trackable
        typedef truth<(is_base_and_derived<trackable, T>::value)> is_trackable;
        add_if_trackable(&t, is_trackable());
      }

      // add_if_trackable() adds trackable objects to the list of bound objects
      inline void add_if_trackable(const trackable* b, truth<true>) const
      {
        if (b) {
          bound_objects.push_back(b);
        }
      }

      template<typename T>
      inline void add_if_trackable(const T*, truth<false>) const
      {
      }

      mutable std::vector<const trackable*>& bound_objects;
    };
  } // end namespace detail
} // end namespace BOOST_SIGNALS_NAMESPACE

} // end namespace boost

#endif // BOOST_SIGNALS_TRACKABLE_HPP
