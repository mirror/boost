//  boost/chrono/stopwatches/lightweight_stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_LIGHTWEIGHT_STOPWATCH_REPORTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_LIGHTWEIGHT_STOPWATCH_REPORTER_HPP

#if !defined(BOOST_ENABLE_WARNINGS) && !defined(BOOST_CHRONO_ENABLE_WARNINGS)
#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif
#endif

#include <boost/chrono/stopwatches/reporters/stopwatch_reporter_default_formatter.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>
#include <boost/cstdint.hpp>
#include <cassert>

namespace boost
{
  namespace chrono
  {

    template<class Stopwatch, class Formatter>
    class basic_lightweight_stopwatch_reporter: public Stopwatch
    {
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      explicit basic_lightweight_stopwatch_reporter(formatter_type& fmt) BOOST_CHRONO_NOEXCEPT :
        formatter_(fmt), reported_(false)
      {
      }

      basic_lightweight_stopwatch_reporter(formatter_type& fmt, system::error_code & ec) :
      Stopwatch(ec), formatter_(fmt), reported_(false)
      {
      }

      ~basic_lightweight_stopwatch_reporter() BOOST_CHRONO_NOEXCEPT
      {
        if (!reported())
        {
          this->report();
        }
      }

      inline void report() BOOST_CHRONO_NOEXCEPT
      {
        formatter_(*this);
        reported_ = true;
      }
      inline void report(system::error_code & ec)
      {
        formatter_(*this, ec);
        reported_ = true;
      }
      bool reported() const
      {
        return reported_;
      }

    protected:
      formatter_type& formatter_;
      bool reported_;

      basic_lightweight_stopwatch_reporter(const basic_lightweight_stopwatch_reporter&); // = delete;
      basic_lightweight_stopwatch_reporter& operator=(const basic_lightweight_stopwatch_reporter&); // = delete;
    };


    template<class Stopwatch,
        class Formatter = typename stopwatch_reporter_default_formatter<
            Stopwatch>::type>
    class lightweight_stopwatch_reporter;

    template<class Stopwatch, class Formatter>
    struct stopwatch_reporter_default_formatter<lightweight_stopwatch_reporter<Stopwatch,
        Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class lightweight_stopwatch_reporter: public basic_lightweight_stopwatch_reporter<Stopwatch,
        Formatter>
    {
      typedef basic_lightweight_stopwatch_reporter<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      explicit lightweight_stopwatch_reporter(formatter_type& fmt)
      : base_type(fmt)
      {
      }

      lightweight_stopwatch_reporter(formatter_type& fmt, system::error_code & ec) :
        base_type(fmt, ec)
      {
      }

//      typedef stopwatch_runner<lightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_run;
//      typedef stopwatch_stopper<lightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_stop;
//      typedef stopwatch_suspender<lightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_suspend;
//      typedef stopwatch_resumer<lightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_resume;

    protected:

      lightweight_stopwatch_reporter(); // = delete;
      lightweight_stopwatch_reporter(const lightweight_stopwatch_reporter&); // = delete;
      lightweight_stopwatch_reporter& operator=(const lightweight_stopwatch_reporter&); // = delete;
    };

    template<class Stopwatch,
        class Formatter = typename wstopwatch_reporter_default_formatter<
            Stopwatch>::type>
    class wlightweight_stopwatch_reporter;

    template<class Stopwatch, class Formatter>
    struct wstopwatch_reporter_default_formatter<wlightweight_stopwatch_reporter<
        Stopwatch, Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class wlightweight_stopwatch_reporter: public basic_lightweight_stopwatch_reporter<Stopwatch,
        Formatter>
    {
      typedef basic_lightweight_stopwatch_reporter<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      explicit wlightweight_stopwatch_reporter(formatter_type& fmt) :
        base_type(fmt)
      {
      }
      wlightweight_stopwatch_reporter(formatter_type& fmt, system::error_code & ec) :
        base_type(fmt, ec)
      {
      }

//      typedef stopwatch_runner<wlightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_run;
//      typedef stopwatch_stopper<wlightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_stop;
//      typedef stopwatch_suspender<wlightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_suspend;
//      typedef stopwatch_resumer<wlightweight_stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_resume;

    protected:

      wlightweight_stopwatch_reporter(); // = delete;
      wlightweight_stopwatch_reporter(const wlightweight_stopwatch_reporter&); // = delete;
      wlightweight_stopwatch_reporter& operator=(const wlightweight_stopwatch_reporter&); // = delete;
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


