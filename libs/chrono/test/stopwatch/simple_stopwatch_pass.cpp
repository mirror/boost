//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//  Adaptation to Boost of the libcxx
//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <boost/type_traits/is_same.hpp>
#include <boost/chrono/stopwatches/simple_stopwatch.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <boost/system/system_error.hpp>
#include <boost/detail/lightweight_test.hpp>

#if !defined(BOOST_NO_STATIC_ASSERT)
#define NOTHING ""
#endif

namespace ex
{
    template<class Rep, class Period>
    void sleep_for(const boost::chrono::duration<Rep, Period>& d)
    {
      typedef boost::chrono::high_resolution_clock Clock;
      typename Clock::time_point go =
          Clock::now() + d;
      while (Clock::now() < go)
      {
      }
    }
}

template <typename Clock>
void check_invariants()
{
  typedef boost::chrono::simple_stopwatch<Clock> Stopwatch;
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::rep, typename Stopwatch::clock::duration::rep>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::period, typename Stopwatch::clock::duration::period>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::duration, typename Stopwatch::clock::time_point::duration>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT(Stopwatch::is_steady == Stopwatch::clock::is_steady, NOTHING, ());
    // to be replaced by has static member bool is_steady
}

template <typename Clock>
void check_default_constructor()
{
  typedef boost::chrono::simple_stopwatch<Clock> Stopwatch;
  Stopwatch _;
}

template <typename Clock>
void check_constructor_ec()
{
  typedef boost::chrono::simple_stopwatch<Clock> Stopwatch;
  boost::system::error_code ec;
  Stopwatch _(ec);
  BOOST_TEST(ec.value()==0);
}

template <typename Clock>
void check_constructor_throws()
{
  typedef boost::chrono::simple_stopwatch<Clock> Stopwatch;
  Stopwatch _(boost::throws());
}


template <typename Clock>
void check_elapsed(bool check=true)
{
  typedef boost::chrono::simple_stopwatch<Clock> Stopwatch;
  Stopwatch sw;
  ex::sleep_for(boost::chrono::milliseconds(100));
  typename Stopwatch::duration d=sw.elapsed();
  if (check)
    BOOST_TEST(d >= boost::chrono::milliseconds(100));
}

template <typename Clock>
void check_all(bool check=true)
{
  check_invariants<Clock>();
  check_default_constructor<Clock>();
  check_constructor_ec<Clock>();
  check_constructor_throws<Clock>();
  check_elapsed<Clock>(check);
}

int main()
{
  std::cout << "high_resolution_clock=";
  check_all<boost::chrono::high_resolution_clock>(false);
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  std::cout << "steady_clock=";
  check_all<boost::chrono::steady_clock>(false);
#endif
  std::cout << "system_clock=";
  check_all<boost::chrono::system_clock>(false);

#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
  std::cout << "thread_clock=";
  check_all<boost::chrono::thread_clock>(false);
#endif
    
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
  std::cout << "process_real_cpu_clock=";
  check_all<boost::chrono::process_real_cpu_clock>(false);
  std::cout << "process_user_cpu_clock=";
  check_all<boost::chrono::process_user_cpu_clock>(false);
  std::cout << "process_system_cpu_clock=";
  check_all<boost::chrono::process_system_cpu_clock>(false);
  std::cout << "process_cpu_clock=";
  check_all<boost::chrono::process_cpu_clock>(false);
#endif
    
  return boost::report_errors();
}
