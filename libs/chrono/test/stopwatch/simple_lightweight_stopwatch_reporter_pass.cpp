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
#include <libs/chrono/test/cycle_count.hpp>
#include <boost/chrono/stopwatches/reporters/lightweight_stopwatch_reporter.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/system/system_error.hpp>
#include <boost/chrono/stopwatches/reporters/system_default_formatter.hpp>
#include <boost/detail/lightweight_test.hpp>

#if !defined(BOOST_NO_STATIC_ASSERT)
#define NOTHING ""
#endif

using namespace boost::chrono;


template <typename Reporter>
void check_invariants()
{
  typedef Reporter Stopwatch;
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::rep, typename Stopwatch::clock::duration::rep>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::period, typename Stopwatch::clock::duration::period>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::duration, typename Stopwatch::clock::time_point::duration>::value), NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT(Stopwatch::is_steady == Stopwatch::clock::is_steady, NOTHING, ());
    BOOST_CHRONO_STATIC_ASSERT((boost::is_same<typename Stopwatch::stopwatch, simple_stopwatch<typename Stopwatch::clock> >::value), NOTHING, ());
}

template <typename Reporter>
void check_constructor()
{
  static typename Reporter::formatter_type fmtr;

  Reporter _(fmtr);
}

template <typename Reporter>
void check_constructor_ec()
{
  static typename Reporter::formatter_type fmtr;

  boost::system::error_code ec;
  Reporter _(fmtr, ec);
  BOOST_TEST(ec.value()==0);
}

template <typename Reporter>
void check_constructor_throws()
{
  static typename Reporter::formatter_type fmtr;

  Reporter _(fmtr, boost::throws());
}

template <typename Reporter>
void check_elapsed(bool check=true)
{
  static typename Reporter::formatter_type fmtr;

  Reporter sw(fmtr);
  ex::sleep_for<typename Reporter::clock>(milliseconds(100));
  typename Reporter::duration d=sw.elapsed();
  std::cout << d << std::endl;
  if (check)
    BOOST_TEST(d >= milliseconds(100));
}

template <typename Reporter>
void check_report()
{
  static typename Reporter::formatter_type fmtr;

  Reporter sw(fmtr);
  ex::sleep_for<typename Reporter::clock>(milliseconds(100));
  sw.report();
}

template <typename Reporter>
void check_file_line()
{
  static typename Reporter::formatter_type fmtr("%1%[%2%] Elapsed time: %3%\n");

  fmtr % __FILE__ % __LINE__;

  Reporter _(fmtr);
  ex::sleep_for<typename Reporter::clock>(milliseconds(100));
}

template <typename Clock>
void check_all(bool check=true)
{
  typedef simple_stopwatch<Clock> Stopwatch;
  typedef typename stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  typedef elapsed_formatter FormatterE;
  typedef lightweight_stopwatch_reporter<Stopwatch,FormatterE> ReporterE;

  check_invariants<Reporter>();
  check_constructor<Reporter>();
  check_constructor_ec<Reporter>();
  check_constructor_throws<Reporter>();
  check_elapsed<Reporter>(check);
  check_report<Reporter>();
  check_file_line<ReporterE>();
}

int main()
{

  typedef simple_stopwatch<high_resolution_clock > Stopwatch;
  typedef stopwatch_reporter_default_formatter<Stopwatch>::type Formatter;
  typedef lightweight_stopwatch_reporter<Stopwatch> Reporter;
  static Formatter fmtr;

  Reporter _(fmtr);

  check_all<ex::cycle_count<1500> >(true);

  return boost::report_errors();
}
