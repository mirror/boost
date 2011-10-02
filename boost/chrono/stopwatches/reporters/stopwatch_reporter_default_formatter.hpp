//  boost/chrono/stopwatches/stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_DEFAULT_FORMATTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_DEFAULT_FORMATTER_HPP

#include <boost/chrono/stopwatches/reporters/clock_default_formatter.hpp>

namespace boost
{
  namespace chrono
  {

    template<class Stopwatch>
    struct stopwatch_reporter_default_formatter
    : clock_default_formatter<typename Stopwatch::clock>
    {
    };

    template<class Stopwatch>
    struct wstopwatch_reporter_default_formatter
    : wclock_default_formatter<typename Stopwatch::clock>
    {
    };

  } // namespace chrono
} // namespace boost



#endif


