//  boost/chrono/stopwatches/stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_LAPS_ACCUMULATOR_SET_DEFAULT_FORMATTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_LAPS_ACCUMULATOR_SET_DEFAULT_FORMATTER_HPP

#include <boost/chrono/stopwatches/reporters/stopwatch_reporter_default_formatter.hpp>
#include <boost/chrono/stopwatches/formatters/accumulator_set_formatter.hpp>
#include <boost/chrono/stopwatches/collectors/laps_accumulator_set.hpp>
#include <boost/chrono/stopwatches/basic_stopwatch.hpp>
#include <boost/chrono/thread_clock.hpp>

namespace boost
{
  namespace chrono
  {

    template <typename Clock, typename Features, typename Weight>
    struct stopwatch_reporter_default_formatter<basic_stopwatch<Clock,laps_accumulator_set<typename Clock::duration,Features, Weight> > >
    {
      typedef accumulator_set_formatter type;
    };

    template <typename Clock, typename Features, typename Weight>
    struct wstopwatch_reporter_default_formatter<basic_stopwatch<Clock,laps_accumulator_set<typename Clock::duration,Features, Weight> > >
    {
      typedef waccumulator_set_formatter type;
    };

  } // namespace chrono
} // namespace boost


#endif


