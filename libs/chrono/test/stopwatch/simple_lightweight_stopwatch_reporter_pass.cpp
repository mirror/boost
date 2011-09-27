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
#include <boost/chrono/stopwatches/reporters/lightweight_stopwatch_reporter.hpp>
#include <boost/chrono/stopwatches/reporters/system_default_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/process_default_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/thread_default_formatter.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/system/system_error.hpp>
#include <boost/detail/lightweight_test.hpp>

#if !defined(BOOST_NO_STATIC_ASSERT)
#define NOTHING ""
#endif

using namespace boost::chrono;

namespace ex
{
    template<class Rep, class Period>
    void sleep_for(const duration<Rep, Period>& d)
    {
      typedef high_resolution_clock Clock;
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
  typedef lightweight_stopwatch_reporter<simple_stopwatch<Clock> > Reporter;
  typedef Reporter Stopwatch;
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::rep, typename Stopwatch::clock::duration::rep>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::period, typename Stopwatch::clock::duration::period>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::duration, typename Stopwatch::clock::time_point::duration>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT(Stopwatch::is_steady == Stopwatch::clock::is_steady, NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::stopwatch, simple_stopwatch<Clock> >::value), NOTHING, ());
}

template <typename Clock>
void check_constructor()
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter _(fmtr);
}

template <typename Clock>
void check_constructor_ec()
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  boost::system::error_code ec;
  Reporter _(fmtr, ec);
  BOOST_TEST(ec.value()==0);
}

template <typename Clock>
void check_constructor_throws()
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter _(fmtr, boost::throws());
}

template <typename Clock>
void check_elapsed(bool check=true)
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter sw(fmtr);
  ex::sleep_for(milliseconds(100));
  typename Reporter::duration d=sw.elapsed();
  std::cout << d << std::endl;
  if (check)
    BOOST_TEST(d >= milliseconds(100));
}

template <typename Clock>
void check_report()
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter sw(fmtr);
  ex::sleep_for(milliseconds(100));
  sw.report();
}

template <typename Clock>
void check_file_line()
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef elapsed_formatter Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch,Formatter> Reporter;
  static Formatter fmtr("%1%[%2%] Elapsed time: %3%\n");
  fmtr % __FILE__ % __LINE__;

  Reporter _(fmtr);
  ex::sleep_for(milliseconds(100));
}

template <typename Clock>
void check_all(bool check=true)
{
  check_invariants<Clock>();
  check_constructor<Clock>();
  check_constructor_ec<Clock>();
  check_constructor_throws<Clock>();
  check_elapsed<Clock>(check);
  check_report<Clock>();
  check_file_line<Clock>();
}

int main()
{

  typedef simple_stopwatch<high_resolution_clock> Stopwatch;
  typedef stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter _(fmtr);

  std::cout << "high_resolution_clock=\n";
  check_all<high_resolution_clock>(false);
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  std::cout << "steady_clock=\n";
  check_all<steady_clock>(false);
#endif
  std::cout << "system_clock=\n";
  check_all<system_clock>(false);

#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
  std::cout << "thread_clock=\n";
  check_all<thread_clock>(false);
#endif
    
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
  std::cout << "process_real_cpu_clock=\n";
  check_all<process_real_cpu_clock>(false);
  std::cout << "process_user_cpu_clock=\n";
  check_all<process_user_cpu_clock>(false);
  std::cout << "process_system_cpu_clock=\n";
  check_all<process_system_cpu_clock>(false);
  std::cout << "process_cpu_clock=\n";
  check_all<process_cpu_clock>(false);
#endif

  return boost::report_errors();
}
