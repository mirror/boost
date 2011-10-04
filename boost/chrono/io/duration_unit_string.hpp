//
//  (C) Copyright 2010 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_UNIT_STRING_HPP
#define BOOST_CHRONO_IO_DURATION_UNIT_STRING_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <string>

namespace boost
{
  namespace chrono
  {

    template <class Period, class CharT>
    struct duration_period_suffix
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }

    };

    template <class CharT>
    struct duration_period_suffix<ratio<60>, CharT >
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
    };

    template <class CharT>
    struct duration_period_suffix<ratio<3600>, CharT >
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
    };

    template <class Period, class CharT>
    struct duration_period
    {
      static std::basic_string<CharT> prefix(std::basic_string<CharT> const& translation)
      {
        return ::boost::ratio_string<Period, CharT>::long_name()+translation;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return ::boost::ratio_string<Period, CharT>::short_name()+str;
      }
    };

    template <class CharT>
    struct duration_period<ratio<1>, CharT >
    {
      static std::basic_string<CharT> prefix(std::basic_string<CharT> const& translation)
      {
        return translation;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return str;
      }
    };
    template <class CharT>
    struct duration_period<ratio<60>, CharT >
    {
      static std::basic_string<CharT> prefix(std::basic_string<CharT> const& translation)
      {
        return translation;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 'm');
        return str;
      }
    };
    template <class CharT>
    struct duration_period<ratio<3600>, CharT >
    {
      static std::basic_string<CharT> prefix(std::basic_string<CharT> const& translation)
      {
        return translation;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 'h');
        return str;
      }
    };

#if !defined BOOST_CHRONO_SPECIFIC_TRANSLATE
    template <class CharT, class Rep>
    std::basic_string<CharT> translate(CharT const *, std::basic_string<CharT> const &singular, std::basic_string<CharT> const &plural, Rep v)
    {
      if ( v > 1 ) return plural;
      else return singular;
    }
#endif

    template <class CharT, class Rep, class Period>
    std::basic_string<CharT> duration_unit_string(bool is_prefix, duration<Rep,Period> const& d) {
      if (is_prefix) {
        return duration_period<Period, CharT>::prefix(
          translate("Boost.Chrono",
              duration_period_suffix<Period, CharT>::singular(),
              duration_period_suffix<Period, CharT>::plural(),
              d.count()
          )
        );
      }
      else
      {
        return duration_period<Period, CharT>::symbol();
      }
    }


  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
