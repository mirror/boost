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

#ifndef BOOST_SIGNAL_HPP
#define BOOST_SIGNAL_HPP

#define BOOST_SIGNALS_MAX_ARGS 10

#include <boost/config.hpp>
#include <boost/signals/signal0.hpp>
#include <boost/signals/signal1.hpp>
#include <boost/signals/signal2.hpp>
#include <boost/signals/signal3.hpp>
#include <boost/signals/signal4.hpp>
#include <boost/signals/signal5.hpp>
#include <boost/signals/signal6.hpp>
#include <boost/signals/signal7.hpp>
#include <boost/signals/signal8.hpp>
#include <boost/signals/signal9.hpp>
#include <boost/signals/signal10.hpp>

namespace boost {
  namespace signals {
    namespace detail {
      // The unusable class is a placeholder for unused function arguments.
      struct unused {};

      // value=1 if the given type is not "unused"
      template<typename T>
      struct count_if_used
      {
        BOOST_STATIC_CONSTANT(int, value = 1);
      };
    
      // value=0 for unused types
      template<>
      struct count_if_used<unused>
      {
        BOOST_STATIC_CONSTANT(int, value = 0);
      };
    
      // Count the number of arguments (from the given set) which are not 
      // "unused" (therefore, count those arguments that are used).
      template<typename T1, typename T2, typename T3, typename T4, 
               typename T5, typename T6, typename T7, typename T8, 
               typename T9, typename T10>
      struct count_used_args
      {
        BOOST_STATIC_CONSTANT(int, value = 
                              (count_if_used<T1>::value + 
                               count_if_used<T2>::value +
                               count_if_used<T3>::value + 
                               count_if_used<T4>::value +
                               count_if_used<T5>::value + 
                               count_if_used<T6>::value +
                               count_if_used<T7>::value + 
                               count_if_used<T8>::value +
                               count_if_used<T9>::value +
                               count_if_used<T10>::value));
      };

      // Choose the appropriate underlying implementation
      template<int Args> struct real_get_signal_impl {};

      template<>
      struct real_get_signal_impl<0>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal0<R, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<1>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal1<R, T1, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<2>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal2<R, T1, T2, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<3>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal3<R, T1, T2, T3, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<4>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal4<R, T1, T2, T3, T4, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<5>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal5<R, T1, T2, T3, T4, T5, Combiner> 
          type;
        };
      };

      template<>
      struct real_get_signal_impl<6>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal6<R, T1, T2, T3, T4, T5, T6, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<7>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal7<R, T1, T2, T3, T4, T5, T6, T7, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<8>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal8<R, T1, T2, T3, T4, T5, T6, T7, T8, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<9>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal9<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, Combiner> type;
        };
      };

      template<>
      struct real_get_signal_impl<10>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Combiner = last_value<R>
        >
        struct params
        {
          typedef signal10<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, 
                           Combiner> type;
        };
      };

      template<
        typename R, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4,
        typename T5, 
        typename T6, 
        typename T7, 
        typename T8, 
        typename T9,
        typename T10,
        typename Combiner = last_value<R>
      >
      struct get_signal_impl
      {
        typedef typename real_get_signal_impl<
          (count_used_args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::value)
          >::template params<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, 
                             Combiner>::type
        type;
      };
    } // end namespace detail
  } // end namespace signals

  // Very lightweight wrapper around the signalN classes that allows signals to
  // be created where the number of arguments does not need to be part of the
  // class name.
  template<
    typename R, 
    typename T1  = signals::detail::unused, 
    typename T2  = signals::detail::unused,
    typename T3  = signals::detail::unused,
    typename T4  = signals::detail::unused,
    typename T5  = signals::detail::unused,
    typename T6  = signals::detail::unused,
    typename T7  = signals::detail::unused,
    typename T8  = signals::detail::unused,
    typename T9  = signals::detail::unused,
    typename T10 = signals::detail::unused
  >
  class signal :
    public signals::detail::get_signal_impl<R, T1, T2, T3, T4, T5, T6, T7, 
                                            T8, T9, T10>::type
  {
  public:
    template<typename Combiner>
    struct combiner {
      typedef typename signals::detail::get_signal_impl<R, T1, T2, T3, T4, T5,
                                                        T6, T7, T8, T9, T10, 
                                                        Combiner>::type
        type;
    };
  };
} // end namespace boost

#endif // BOOST_SIGNAL_HPP
