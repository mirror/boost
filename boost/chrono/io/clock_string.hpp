//
//  (C) Copyright 2010 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_CLOCK_STRING_HPP
#define BOOST_CHRONO_IO_CLOCK_STRING_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <string>

namespace boost
{
  namespace chrono
  {

    template<class Clock, class CharT>
    struct clock_string;

    template<class CharT>
    struct clock_string<system_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { 's', 'y', 's', 't', 'e', 'm', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        static const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'J', 'a', 'n', ' ', '1', ',', ' ', '1', '9', '7', '0' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
    };

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY

    template<class CharT>
    struct clock_string<steady_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'm', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT u[] =
        { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'b', 'o', 'o', 't' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

#endif

#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)

    template <class CharT>
    struct clock_string<thread_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { 't', 'h', 'r', 'e', 'd', '_',
          'c', 'l','o', 'c', 'k'};
        static const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT u[] =
        { ' ', 's', 'i', 'n', 'c', 'e', ' ', 't', 'r', 'e', 'a', 'd', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p'};
        const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
        return str;
      }
    };

#endif

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)

    template<class CharT>
    struct clock_string<process_real_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'r', 'e', 'a', 'l', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

    template<class CharT>
    struct clock_string<process_user_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'u', 's', 'e', 'r', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

    template<class CharT>
    struct clock_string<process_system_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 's', 'y', 's', 't', 't', 'e', 'm', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

    template<class CharT>
    struct clock_string<process_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };
#endif

  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
