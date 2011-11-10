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
     * @c time_point_units facet gives useful information about the duration units,
     * as the number of plural forms, the plural form associated to a duration,
     * the text associated to a plural form and a duration's period,
     */
    template <typename CharT=char, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class time_point_units: public std::locale::facet
    {
      static time_point_units* global_;
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      static std::locale::id id;

      explicit time_point_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @Return Gets the global time_point_units,
       * used when the stream has no associated time_point_units facet.
       * @Throws an exception if the global is 0.
      Ê
      */
      static time_point_units* global()
      {
        return global_;
      }

      /**
      If the facet is not 0, sets the new global time_point_units, after deleting the preceding one. This is used when the stream has no associated time_point_units facet.
      Otherwise throw an exception.
      */
      static void global(time_point_units* ptr)
      {
        global_ = ptr;
      }

      /**
       * Factory cloning a the global instance.
       * @return a clone of the global instance.
       */
      static time_point_units* make()
      {
        return global_->clone();;
      }

      /**
       * imbue a clone of this facet in @c ios.
       * @param ios the ios to imbue.
       */
#if defined BOOST_CHRONO_USES_DURATION_UNITS_GLOBAL
      // FIXME: This cause a linker problem on compilers other than clang-3.0 c++03 or c++0x
      static time_point_units<CharT,OutputIterator> const& imbue_if_has_not(std::ios_base& ios)
      {
        if (!std::has_facet<time_point_units<CharT,OutputIterator> >(ios.getloc()))
          ios.imbue(std::locale(ios.getloc(), make()));
        return std::use_facet<time_point_units<CharT,OutputIterator> >(ios.getloc());
      }
#else
      static inline time_point_units<CharT,OutputIterator> const& imbue_if_has_not(std::ios_base& ios);
#endif

      template <typename Clock>
      iter_type put(iter_type s, std::ios_base& ios) const
      {
        return do_put(s, ios, Clock());
      }

      /**
       *
       * @return the pattern to be used by default.
       */
      std::basic_string<CharT> get_pattern() const
      {
        return do_get_pattern();
      }

      /**
       *
       * @return the pattern to be used by default.
       */
      template <typename Clock>
      std::basic_string<CharT> get_epoch() const
      {
        return do_get_epoch(Clock());
      }

    protected:
      virtual ~time_point_units() {};
      virtual time_point_units<CharT, OutputIterator>* clone() const = 0;

      virtual std::basic_string<CharT> do_get_pattern() const=0;

      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, system_clock) const = 0;
      virtual std::basic_string<CharT> do_get_epoch(system_clock) const=0;

      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, steady_clock) const = 0;
      virtual std::basic_string<CharT> do_get_epoch(steady_clock) const=0;

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      virtual iter_type do_put(iter_type s, std::ios_base& ios, process_real_cpu_clock c) const =0;
      virtual std::basic_string<CharT> do_get_epoch(process_real_cpu_clock) const=0;
      virtual iter_type do_put(iter_type s, std::ios_base& ios, process_user_cpu_clock c) const =0;
      virtual std::basic_string<CharT> do_get_epoch(process_user_cpu_clock) const=0;
      virtual iter_type do_put(iter_type s, std::ios_base& ios, process_system_cpu_clock c) const =0;
      virtual std::basic_string<CharT> do_get_epoch(process_system_cpu_clock) const=0;
      virtual iter_type do_put(iter_type s, std::ios_base& ios, process_cpu_clock c) const =0;
      virtual std::basic_string<CharT> do_get_epoch(process_cpu_clock) const=0;
#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      virtual iter_type do_put(iter_type s, std::ios_base& ios, thread_clock c) const =0;
      virtual std::basic_string<CharT> do_get_epoch(thread_clock) const=0;
#endif

    };

    template <typename CharT, class OutputIterator>
    std::locale::id time_point_units<CharT, OutputIterator>::id;


    // This class is used to define the strings for the default English
    template <typename CharT=char, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class time_point_units_default: public time_point_units<CharT, OutputIterator>
    {
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      explicit time_point_units_default(size_t refs = 0) :
        time_point_units<CharT, OutputIterator> (refs)
      {
      }
      ~time_point_units_default() {}


    protected:
      time_point_units<CharT, OutputIterator>* clone() const
      {
        return new time_point_units_default<CharT, OutputIterator>();
      }

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


      iter_type do_put(iter_type s, std::ios_base& , system_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(system_clock ) const
      {
        return clock_string<system_clock,CharT>::since();
      }
      iter_type do_put(iter_type s, std::ios_base& , steady_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(steady_clock ) const
      {
        return clock_string<steady_clock,CharT>::since();
      }

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      iter_type do_put(iter_type s, std::ios_base& , process_real_cpu_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(process_real_cpu_clock ) const
      {
        return clock_string<process_real_cpu_clock,CharT>::since();
      }
      iter_type do_put(iter_type s, std::ios_base& , process_user_cpu_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(process_user_cpu_clock ) const
      {
        return clock_string<process_user_cpu_clock,CharT>::since();
      }
      iter_type do_put(iter_type s, std::ios_base& , process_system_cpu_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(process_system_cpu_clock ) const
      {
        return clock_string<process_system_cpu_clock,CharT>::since();
      }
      iter_type do_put(iter_type s, std::ios_base& , process_cpu_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(process_cpu_clock ) const
      {
        return clock_string<process_cpu_clock,CharT>::since();
      }

#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      iter_type do_put(iter_type s, std::ios_base& , thread_clock c) const
      {
        std::basic_string<CharT> str = do_get_epoch(c);
        return std::copy(str.begin(), str.end(), s);
      }
      std::basic_string<CharT> do_get_epoch(thread_clock ) const
      {
        return clock_string<thread_clock,CharT>::since();
      }
#endif

    };

    template <typename CharT, class OutputIterator>
    time_point_units<CharT, OutputIterator>* time_point_units<CharT, OutputIterator>::global_=new time_point_units_default<CharT, OutputIterator>();

#if ! defined BOOST_CHRONO_USES_DURATION_UNITS_GLOBAL
    template <typename CharT, class OutputIterator>
    time_point_units<CharT,OutputIterator> const&
    time_point_units<CharT, OutputIterator>::imbue_if_has_not(std::ios_base& ios)
    {
        if (!std::has_facet<time_point_units<CharT,OutputIterator> >(ios.getloc())) ios.imbue(
            std::locale(ios.getloc(), new time_point_units_default<CharT,OutputIterator>()));
        return std::use_facet<time_point_units<CharT,OutputIterator> >(ios.getloc());
    }

#endif


  } // chrono

} // boost

#endif  // header
