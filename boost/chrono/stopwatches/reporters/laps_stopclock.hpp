//  boost/chrono/stopwatches/reporters/laps_stopclock.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_LAPS_STOPCLOCK_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_LAPS_STOPCLOCK_HPP

#include <boost/chrono/config.hpp>

#if !defined(BOOST_ENABLE_WARNINGS) && !defined(BOOST_CHRONO_ENABLE_WARNINGS)
#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif
#endif

#include <boost/chrono/stopwatches/reporters/laps_stopwatch_default_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/stopwatch_reporter_default_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/stopwatch_reporter.hpp>
#include <boost/chrono/stopwatches/stopwatch_scoped.hpp>
#include <boost/chrono/stopwatches/laps_stopwatch.hpp>
#include <boost/chrono/stopwatches/dont_start.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>
#include <boost/cstdint.hpp>
#include <cassert>

namespace boost
{
  namespace chrono
  {

    template<class CharT, typename Clock, typename LapsCollector, class Formatter>
    class basic_laps_stopclock: public basic_stopwatch_reporter<CharT, laps_stopwatch<Clock, LapsCollector>, Formatter>
    {
    public:
      typedef basic_stopwatch_reporter<CharT, laps_stopwatch<Clock, LapsCollector>, Formatter> base_type;
      typedef Clock clock;
      typedef laps_stopwatch<Clock, LapsCollector> stopwatch;
      typedef Formatter formatter_type;

      basic_laps_stopclock()
      {
      }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
      explicit basic_laps_stopclock(system::error_code & ec) :
        base_type(ec)
      {
      }
#endif
      explicit basic_laps_stopclock(
          const dont_start_t& tag
      ) BOOST_NOEXCEPT :
      base_type(tag)
      {
      }

      explicit basic_laps_stopclock(formatter_type const& fmt) :
        base_type(fmt)
      {
      }

      explicit basic_laps_stopclock(const typename Formatter::char_type* fmt) :
        base_type(fmt)
      {
      }
      explicit basic_laps_stopclock(typename Formatter::string_type const& fmt) :
        base_type(fmt)
      {
      }
      typedef stopwatch_runner<basic_laps_stopclock<CharT,Clock, LapsCollector, Formatter> >
          scoped_run;
      typedef stopwatch_stopper<basic_laps_stopclock<CharT,Clock, LapsCollector, Formatter> >
          scoped_stop;
      typedef stopwatch_suspender<basic_laps_stopclock<CharT,Clock, LapsCollector, Formatter> >
          scoped_suspend;
      typedef stopwatch_resumer<basic_laps_stopclock<CharT,Clock, LapsCollector, Formatter> >
          scoped_resume;

    protected:

      basic_laps_stopclock(const basic_laps_stopclock&); // = delete;
      basic_laps_stopclock& operator=(const basic_laps_stopclock&); // = delete;
    };


    template<typename Clock=high_resolution_clock, typename LapsCollector=no_memory<typename Clock::duration>,
        class Formatter = typename basic_stopwatch_reporter_default_formatter<char, laps_stopwatch<Clock, LapsCollector> >::type>
    class laps_stopclock;

    template<class Stopwatch, class Formatter>
    struct basic_stopwatch_reporter_default_formatter<char, laps_stopclock<Stopwatch,
        Formatter> >
    {
      typedef Formatter type;
    };

    template<typename Clock, typename LapsCollector, class Formatter>
    class laps_stopclock: public basic_laps_stopclock<char, Clock, LapsCollector, Formatter>
    {
      typedef basic_laps_stopclock<char, Clock, LapsCollector, Formatter> base_type;
    public:
      typedef Clock clock;
      typedef typename base_type::stopwatch stopwatch;
      typedef Formatter formatter_type;

      laps_stopclock()
      {
      }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
      explicit laps_stopclock(system::error_code & ec) :
        base_type(ec)
      {
      }
#endif
      explicit laps_stopclock(
          const dont_start_t& tag
      ) BOOST_NOEXCEPT :
      base_type(tag)
      {
      }

      explicit laps_stopclock(formatter_type const& fmt) :
        base_type(fmt)
      {
      }

      explicit laps_stopclock(const typename Formatter::char_type* fmt) :
        base_type(fmt)
      {
      }
      explicit laps_stopclock(typename Formatter::string_type const& fmt) :
        base_type(fmt)
      {
      }
      typedef stopwatch_runner<laps_stopclock<Clock, LapsCollector, Formatter> >
          scoped_run;
      typedef stopwatch_stopper<laps_stopclock<Clock, LapsCollector, Formatter> >
          scoped_stop;
      typedef stopwatch_suspender<laps_stopclock<Clock, LapsCollector, Formatter> >
          scoped_suspend;
      typedef stopwatch_resumer<laps_stopclock<Clock, LapsCollector, Formatter> >
          scoped_resume;

    protected:

      laps_stopclock(const laps_stopclock&); // = delete;
      laps_stopclock& operator=(const laps_stopclock&); // = delete;
    };



  } // namespace chrono
} // namespace boost


#if !defined(BOOST_ENABLE_WARNINGS) && !defined(BOOST_CHRONO_ENABLE_WARNINGS)
#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif
#endif

#endif


