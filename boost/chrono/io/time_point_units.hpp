//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_TIME_POINT_UNITS_HPP
#define BOOST_CHRONO_IO_TIME_POINT_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <string>
#include <iostream>
#include <ios>
#include <locale>
#include <algorithm>

namespace boost
{
  namespace chrono
  {

    /**
     * @c time_point_units facet gives useful information about the time_point pattern,
     * the text associated to a time_point's epoch,
     */
    template <typename CharT=char>
    class time_point_units: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * Construct a @c time_point_units facet.
       * @param refs
       * @Effects Construct a @c time_point_units facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit time_point_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @return the pattern to be used by default calling @c do_get_pattern().
       */
      std::basic_string<CharT> get_pattern() const
      {
        return do_get_pattern();
      }

      /**
       * @return the epoch associated to the clock @c Clock calling @c do_get_epoch(Clock())
       */
      template <typename Clock>
      std::basic_string<CharT> get_epoch() const
      {
        return do_get_epoch(Clock());
      }

    protected:
      /**
       * Destroy the facet.
       */
      virtual ~time_point_units() {};

      /**
       *  customization point for getting the timepoint's pattern.
       */
      virtual std::basic_string<CharT> do_get_pattern() const=0;

      virtual std::basic_string<CharT> do_get_epoch(system_clock) const=0;

      virtual std::basic_string<CharT> do_get_epoch(steady_clock) const=0;

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      virtual std::basic_string<CharT> do_get_epoch(process_real_cpu_clock) const=0;
      virtual std::basic_string<CharT> do_get_epoch(process_user_cpu_clock) const=0;
      virtual std::basic_string<CharT> do_get_epoch(process_system_cpu_clock) const=0;
      virtual std::basic_string<CharT> do_get_epoch(process_cpu_clock) const=0;
#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      virtual std::basic_string<CharT> do_get_epoch(thread_clock) const=0;
#endif

    };

    template <typename CharT>
    std::locale::id time_point_units<CharT>::id;


    // This class is used to define the strings for the default English
    template <typename CharT=char>
    class time_point_units_default: public time_point_units<CharT>
    {
    public:
      typedef CharT char_type;

      explicit time_point_units_default(size_t refs = 0) :
        time_point_units<CharT> (refs)
      {
      }
      ~time_point_units_default() {}


    protected:
      std::basic_string<CharT> do_get_pattern() const
      {
        static const CharT t[] =
        { '%', 'd', '%', 'e' };
        static const std::basic_string<CharT> pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }
//      std::basic_string<CharT> get_date_time_pattern() const
//          {
//            static const CharT t[] =
//            { '%', 'd', '%', 'e' };
//            static const std::basic_string<CharT> pattern(t, t + sizeof (t) / sizeof (t[0]));
//
//            return pattern;
//          }


      std::basic_string<CharT> do_get_epoch(system_clock ) const
      {
        return clock_string<system_clock,CharT>::since();
      }
      std::basic_string<CharT> do_get_epoch(steady_clock ) const
      {
        return clock_string<steady_clock,CharT>::since();
      }

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      std::basic_string<CharT> do_get_epoch(process_real_cpu_clock ) const
      {
        return clock_string<process_real_cpu_clock,CharT>::since();
      }
      std::basic_string<CharT> do_get_epoch(process_user_cpu_clock ) const
      {
        return clock_string<process_user_cpu_clock,CharT>::since();
      }
      std::basic_string<CharT> do_get_epoch(process_system_cpu_clock ) const
      {
        return clock_string<process_system_cpu_clock,CharT>::since();
      }
      std::basic_string<CharT> do_get_epoch(process_cpu_clock ) const
      {
        return clock_string<process_cpu_clock,CharT>::since();
      }

#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      std::basic_string<CharT> do_get_epoch(thread_clock ) const
      {
        return clock_string<thread_clock,CharT>::since();
      }
#endif

    };


  } // chrono

} // boost

#endif  // header
