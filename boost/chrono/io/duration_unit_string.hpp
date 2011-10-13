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
#include <boost/chrono/io/translate.hpp>
#include <string>

namespace boost
{
  namespace chrono
  {

    template <class Period, class CharT>
    struct duration_unit_strings
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
            / sizeof(u[0]));
        return ::boost::ratio_string<Period, CharT>::long_name()+suffix;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
            / sizeof(u[0]));
        return ::boost::ratio_string<Period, CharT>::long_name()+suffix;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return ::boost::ratio_string<Period, CharT>::short_name()+str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<1>, CharT >
    {
      static std::basic_string<CharT> plural()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
            / sizeof(u[0]));
        return ::boost::ratio_string<ratio<1>, CharT>::long_name()+suffix;
      }
      static std::basic_string<CharT> singular()
      {
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> suffix(u, u + sizeof(u)
            / sizeof(u[0]));
        return ::boost::ratio_string<ratio<1>, CharT>::long_name()+suffix;
      }
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 's');
        return str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<60>, CharT >
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
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 'm');
        return str;
      }
    };

    template <class CharT>
    struct duration_unit_strings<ratio<3600>, CharT >
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
      static std::basic_string<CharT> symbol()
      {
        static const std::basic_string<CharT> str(1, 'h');
        return str;
      }
    };


    template <class CharT, class Rep, class Period>
    std::basic_string<CharT> duration_unit(bool is_prefix, duration<Rep,Period> const& d) {
      if (is_prefix) {
          return duration_prefix_translate(
              duration_unit_strings<Period, CharT>::singular(),
              duration_unit_strings<Period, CharT>::plural(),
              d.count()
        );
      }
      else
      {
        return duration_symbol_translate(
            duration_unit_strings<Period, CharT>::symbol()
        );
      }
    }


  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
