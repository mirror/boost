// Boost.Signals library
//
// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
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
#include <boost/ref.hpp>
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
        inline void operator()(const T& t) const
        {
          visit(t, truth<is_convertible<T, trackable*>::value>());
          visit(&t, truth<is_convertible<T*, trackable*>::value>());
        }

        template<typename T>
        inline void operator()(const boost::reference_wrapper<T>& r) const
        {
          (*this)(r.get());
        }

        inline void operator()(const trackable* b) const
        {
          if (b) {
            bound_objects.push_back(b);
          }
        }

      private:
        template<typename T>
        inline void visit(const T&, truth<false>) const
        {
        }

        template<typename T>
        inline void visit(const T& t, truth<true>) const
        {
          (*this)(static_cast<const trackable*>(t));
        }

        mutable std::vector<const trackable*>& bound_objects;
      };
    } // end namespace detail
  } // end namespace BOOST_SIGNALS_NAMESPACE
}

#endif // BOOST_SIGNALS_TRACKABLE_HPP
