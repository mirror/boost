//
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_UNIT_STRING_HPP
#define BOOST_CHRONO_IO_DURATION_UNIT_STRING_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/translate.hpp>
#include <boost/chrono/io/unit_strings.hpp>

#include <string>
#include <locale>

namespace boost
{
  template <>
  struct ratio_string_is_localizable<ratio<60> > : true_type
  {
  };

  template <>
  struct ratio_string_id<ratio<60> > : integral_constant<int, 60>
  {
  };

  template <>
  struct ratio_string_is_localizable<ratio<3600> > : true_type
  {
  };

  template <>
  struct ratio_string_id<ratio<3600> > : integral_constant<int, 3600>
  {
  };

  namespace chrono
  {

    template <class CharT>
    struct value
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { '%', '1', '%', ' ' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
    };
    template <class CharT>
    struct period
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { '%', '2', '%' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
    };

    template <class Period, class CharT>
    struct duration_unit_strings
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> suffix(u, u + sizeof (u) / sizeof (u[0]));
        return ::boost::ratio_string<Period, CharT>::prefix() + suffix;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> suffix(u, u + sizeof (u) / sizeof (u[0]));
        return ::boost::ratio_string<Period, CharT>::prefix() + suffix;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return ::boost::ratio_string<Period, CharT>::symbol() + str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<1> , CharT>
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> suffix(u, u + sizeof (u) / sizeof (u[0]));
        return suffix;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> suffix(u, u + sizeof (u) / sizeof (u[0]));
        return suffix;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<60> , CharT>
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
      static std::basic_string<CharT> symbol()
      {
        static const CharT u[] =
        { 'm', 'i', 'n' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<3600> , CharT>
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const std::basic_string<CharT> str(u, u + sizeof (u) / sizeof (u[0]));
        return str;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 'h');
        return str;
      }
    };

    template <class CharT, class Rep, class Period>
    std::basic_string<CharT> duration_unit(std::locale const &loc, bool is_prefix, duration<Rep, Period> const& d)
    {
      if (is_prefix)
      {
        return translate(loc, ratio_string_id<Period> (), duration_unit_strings<Period, CharT>::singular(),
            duration_unit_strings<Period, CharT>::plural(), d.count());
      }
      else
      {
        return translate(loc, ratio_string_id<Period> (), duration_unit_strings<Period, CharT>::symbol());
      }
    }

    template <class CharT, class Rep, class Period>
    std::basic_string<CharT> translated_duration_unit(std::locale const &loc, bool is_prefix,
        duration<Rep, Period> const& d)
    {
      if (is_prefix)
      {
        return translate(loc, ratio_string_id<Period> (),
            value<CharT>::name() + duration_unit_strings<Period, CharT>::singular(),
            value<CharT>::name() + duration_unit_strings<Period, CharT>::plural(), d.count());
      }
      else
      {
        return translate(loc, ratio_string_id<Period> (),
            value<CharT>::name() + duration_unit_strings<Period, CharT>::symbol());
      }
    }

    template <class CharT, class Period>
    std::basic_string<CharT> translated_duration_unit(std::locale const &loc, bool is_prefix)
    {
      if (is_prefix)
      {
        return translate(loc, ratio_string_id<Period> (),
            value<CharT>::name() + period<CharT>::name() + duration_unit_strings<Period, CharT>::plural());
      }
      else
      {
        return translate(loc, ratio_string_id<Period> (),
            value<CharT>::name() + period<CharT>::name() + duration_unit_strings<Period, CharT>::symbol());
      }
    }

  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
