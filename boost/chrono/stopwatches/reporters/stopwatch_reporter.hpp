//  boost/chrono/stopwatches/stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_STOPWATCH_REPORTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_STOPWATCH_REPORTER_HPP

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
    class basic_stopwatch_reporter: public Stopwatch
    {
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      basic_stopwatch_reporter() BOOST_CHRONO_NOEXCEPT :
        formatter_(), reported_(false)
      {
      }

      explicit basic_stopwatch_reporter(const typename Formatter::char_type* fmt) :
        formatter_(fmt), reported_(false)
      {
      }
      explicit basic_stopwatch_reporter(typename Formatter::string_type const& fmt) :
        formatter_(fmt), reported_(false)
      {
      }
      explicit basic_stopwatch_reporter(formatter_type const& fmt) :
        formatter_(fmt), reported_(false)
      {
      }

      ~basic_stopwatch_reporter() BOOST_CHRONO_NOEXCEPT
      {
        system::error_code ec;
        if (!reported())
        {
          this->report(ec);
        }
      }

      inline void report(system::error_code & ec= BOOST_CHRONO_THROWS)
      {
        reported_ = true;
        formatter_(*this, ec);
      }
      bool reported() const
      {
        return reported_;
      }

    protected:
      formatter_type formatter_;
      bool reported_;

      basic_stopwatch_reporter(const basic_stopwatch_reporter&); // = delete;
      basic_stopwatch_reporter& operator=(const basic_stopwatch_reporter&); // = delete;
    };


    template<class Stopwatch,
        class Formatter = typename stopwatch_reporter_default_formatter<
            Stopwatch>::type>
    class stopwatch_reporter;

    template<class Stopwatch, class Formatter>
    struct stopwatch_reporter_default_formatter<stopwatch_reporter<Stopwatch,
        Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class stopwatch_reporter: public basic_stopwatch_reporter<Stopwatch,
        Formatter>
    {
      typedef basic_stopwatch_reporter<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      stopwatch_reporter()
      //: base_type()
      {
      }
      explicit stopwatch_reporter(formatter_type const& fmt) :
        base_type(fmt)
      {
      }
      explicit stopwatch_reporter(const typename Formatter::char_type* fmt) :
        base_type(fmt)
      {
      }
      explicit stopwatch_reporter(typename Formatter::string_type const& fmt) :
        base_type(fmt)
      {
      }
//      typedef stopwatch_runner<stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_run;
//      typedef stopwatch_stopper<stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_stop;
//      typedef stopwatch_suspender<stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_suspend;
//      typedef stopwatch_resumer<stopwatch_reporter<Stopwatch, Formatter> >
//          scoped_resume;

    protected:

      stopwatch_reporter(const stopwatch_reporter&); // = delete;
      stopwatch_reporter& operator=(const stopwatch_reporter&); // = delete;
    };

    template<class Stopwatch,
        class Formatter = typename wstopwatch_reporter_default_formatter<
            Stopwatch>::type>
    class wstopwatch_reporter;

    template<class Stopwatch, class Formatter>
    struct wstopwatch_reporter_default_formatter<wstopwatch_reporter<
        Stopwatch, Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class wstopwatch_reporter: public basic_stopwatch_reporter<Stopwatch,
        Formatter>
    {
      typedef basic_stopwatch_reporter<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      wstopwatch_reporter() :
        base_type()
      {
      }
      explicit wstopwatch_reporter(formatter_type const& fmt) :
        base_type(fmt)
      {
      }

//      typedef stopwatch_runner<wstopwatch_reporter<Stopwatch, Formatter> >
//          scoped_run;
//      typedef stopwatch_stopper<wstopwatch_reporter<Stopwatch, Formatter> >
//          scoped_stop;
//      typedef stopwatch_suspender<wstopwatch_reporter<Stopwatch, Formatter> >
//          scoped_suspend;
//      typedef stopwatch_resumer<wstopwatch_reporter<Stopwatch, Formatter> >
//          scoped_resume;

    protected:

      //wstopwatch_reporter(); // = delete;
      wstopwatch_reporter(const wstopwatch_reporter&); // = delete;
      wstopwatch_reporter& operator=(const wstopwatch_reporter&); // = delete;
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


