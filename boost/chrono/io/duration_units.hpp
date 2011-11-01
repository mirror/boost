//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_UNITS_HPP
#define BOOST_CHRONO_IO_DURATION_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <string>
#include <iostream>
//#include <locale>
#include <boost/utility/enable_if.hpp>
#include <algorithm>

namespace boost
{
  namespace chrono
  {
    template <typename Period>
    struct is_localizable: false_type
    {
    };

    template <>
    struct is_localizable<atto> : true_type
    {
    };
    template <>
    struct is_localizable<femto> : true_type
    {
    };
    template <>
    struct is_localizable<pico> : true_type
    {
    };
    template <>
    struct is_localizable<nano> : true_type
    {
    };
    template <>
    struct is_localizable<micro> : true_type
    {
    };
    template <>
    struct is_localizable<milli> : true_type
    {
    };
    template <>
    struct is_localizable<centi> : true_type
    {
    };
    template <>
    struct is_localizable<deci> : true_type
    {
    };
    template <>
    struct is_localizable<ratio<1> > : true_type
    {
    };
    template <>
    struct is_localizable<deca> : true_type
    {
    };
    template <>
    struct is_localizable<hecto> : true_type
    {
    };
    template <>
    struct is_localizable<kilo> : true_type
    {
    };
    template <>
    struct is_localizable<mega> : true_type
    {
    };
    template <>
    struct is_localizable<giga> : true_type
    {
    };
    template <>
    struct is_localizable<tera> : true_type
    {
    };
    template <>
    struct is_localizable<peta> : true_type
    {
    };
    template <>
    struct is_localizable<exa> : true_type
    {
    };
    template <>
    struct is_localizable<ratio<60> > : true_type
    {
    };
    template <>
    struct is_localizable<ratio<3600> > : true_type
    {
    };

    namespace detail
    {

      class rt_ratio
      {
      public:
        template <typename Period>
        rt_ratio(Period const&) :
          num(Period::type::num), den(Period::type::den)
        {
        }

        rt_ratio(intmax_t n = 0, intmax_t d = 0) :
          num(n), den(d)
        {
        }

        intmax_t num;
        intmax_t den;
      };
    }

    /**
     * @c duration_units facet gives useful information about the duration units,
     * as the number of plural forms, the plural form associated to a duration,
     * the text associated to a plural form and a duration's period,
     */
    template <typename CharT=char, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class duration_units: public std::locale::facet
    {
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      static std::locale::id id;

      explicit duration_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /* TBR */
      virtual bool swaps_value_unit_order() const = 0;

      /**
       *
       * @tparam Rep
       * @tparam Period
       * @Requires Rep must be explicitly convertible to int_least64_t.
       * @Requires Period is named.
       *
       * @param s
       * @param ios
       * @param d
       * @Effects puts the unit associated to the duration @c d in @c s taken in account the @c ios state flags.
       * The implementation uses the non template virtual function do_put as if
       * @code
       *   return do_put(s, ios, get_duration_style(ios), Period(), int_least64_t(d.count()));
       * @codeend
       *
       * where @get_duration_style gives the duration style associated to @ios.
       * @return s
       */
      template <typename Rep, typename Period>
      typename enable_if<is_localizable<Period> , iter_type>::type put(iter_type s, std::ios_base& ios,
          duration<Rep, Period> const& d) const
      {
        return do_put(s, ios, get_duration_style(ios), Period(), int_least64_t(d.count()));
      }

      /**
       *
       * @tparam Rep
       * @tparam Period
       * @Requires Rep must be explicitly convertible to int_least64_t.
       * @Requires Period is not named, that is its textual representation is in the form [N/D].
       *
       * @param s
       * @param ios
       * @param d
       * @Effects puts the unit associated to the duration @c d in @c s taken in account the @c ios state flags.
       * The implementation uses the non template virtual function do_put as if
       * @code
       *   return do_put(s, ios, get_duration_style(ios), detail::rt_ratio(Period()), int_least64_t(d.count()));
       * @codeend
       *
       * where @get_duration_style gives the duration style associated to @ios and
       * detail::rt_ratio is a class that flats the template ration on a run-time ration so we can use it in virtual functions.
       * @return s
       */
      template <typename Rep, typename Period>
      typename disable_if<is_localizable<Period> , iter_type>::type put(iter_type s, std::ios_base& ios,
          duration<Rep, Period> const& d) const
      {
        return do_put(s, ios, get_duration_style(ios), detail::rt_ratio(Period()), int_least64_t(d.count()));
      }

      /**
       *
       * @return the number of plural forms.
       */
      std::size_t get_plural_forms() const
      {
        return do_get_plural_forms();
      }

      /**
       *
       * @param value
       * @return the associated plural form index.
       */
      std::size_t plural_form(int_least64_t value) const
      {
        return do_get_plural_form(value);
      }

      /**
       *
       * @param style
       * @param pf
       * @return the translation associated to the plural form given as parameter.
       */
      template <typename Period>
      typename enable_if<is_localizable<Period> , std::basic_string<CharT> >::type get_plural_form(
          duration_style_type style, std::size_t pf) const
      {
        return do_get_plural_form(style, Period(), pf);
      }

      /**
       *
       * @return the pattern to be used by default.
       */
      std::basic_string<CharT> get_pattern() const
      {
        return do_get_pattern();
      }

    protected:
      virtual std::basic_string<CharT> do_get_pattern() const=0;
      virtual std::size_t do_get_plural_forms() const = 0;
      virtual std::size_t do_get_plural_form(int_least64_t value) const = 0;

      // used for ouput
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, atto, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, femto, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, pico, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, nano, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, micro, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, milli, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, centi, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, deci, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, ratio<1> , int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, deca, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, hecto, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, kilo, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, mega, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, tera, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, peta, int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, exa, int_least64_t) const = 0;
      virtual iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, detail::rt_ratio,
          int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, ratio<60> , int_least64_t) const = 0;
      virtual iter_type
      do_put(iter_type s, std::ios_base& ios, duration_style_type style, ratio<3600> , int_least64_t) const = 0;

      // used for input
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, atto, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, femto, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, pico, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, nano, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, micro, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, milli, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, centi, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, deci, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<1> , std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, deca, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, hecto, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, kilo, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, mega, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, giga, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, tera, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, peta, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, exa, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<60> , std::size_t pf) const = 0;
      virtual std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<3600> , std::size_t pf) const = 0;

    };

    template <typename CharT, class OutputIterator>
    std::locale::id duration_units<CharT, OutputIterator>::id;

    ///////////////////////////
    // This class is used to define the strings for the default English
    template <typename CharT=char, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class duration_units_default: public duration_units<CharT, OutputIterator>
    {
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      explicit duration_units_default(size_t refs = 0) :
        duration_units<CharT, OutputIterator> (refs)
      {
      }
      bool swaps_value_unit_order() const
      {
        return false;
      }

    protected:
      std::size_t do_get_plural_forms() const
      {
        return 2;
      }

      std::size_t do_get_plural_form(int_least64_t value) const
      {
        return (value == -1 || value == 1) ? 0 : 1;
      }

      std::basic_string<CharT> do_get_pattern() const
      {
        static const CharT t[] =
        { '%', 'v', ' ', '%', 'u' };
        static const std::basic_string<CharT> pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, atto u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, femto u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, pico u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }

      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, nano u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, micro u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, milli u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, centi u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, deci u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base&, duration_style_type style, ratio<1> u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_plural_form(style, u, do_get_plural_form(value));
        return std::copy(str.begin(), str.end(), s);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, deca u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, hecto u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }

      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, kilo u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, mega u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, giga u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, tera u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, peta u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }
      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, exa u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_ratio_prefix(style, u);
        std::copy(str.begin(), str.end(), s);
        return do_put(s, ios, style, ratio<1> (), value);
      }

      iter_type do_put(iter_type s, std::ios_base&, duration_style_type style, ratio<60> u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_plural_form(style, u, do_get_plural_form(value));
        return std::copy(str.begin(), str.end(), s);
      }

      iter_type do_put(iter_type s, std::ios_base&, duration_style_type style, ratio<3600> u, int_least64_t value) const
      {
        std::basic_string<CharT> str = do_get_plural_form(style, u, do_get_plural_form(value));
        return std::copy(str.begin(), str.end(), s);
      }

      iter_type do_put(iter_type s, std::ios_base& ios, duration_style_type style, detail::rt_ratio rtr,
          int_least64_t value) const
      {
        *s++ = CharT('[');
        std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, ' ', rtr.num);
        *s++ = CharT('/');
        std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, ' ', rtr.den);
        *s++ = CharT(']');

        return do_put(s, ios, style, ratio<1> (), value);
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<1> , std::size_t pf) const
      {
        static const CharT t[] =
        { 's' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<60> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'm', 'i', 'n' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));

        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<3600> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'h' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, atto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, femto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, pico u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, nano u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, micro u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, milli u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, centi u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, deci u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, deca u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, hecto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, kilo u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, mega u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, giga u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, tera u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, peta u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }
      std::basic_string<CharT> do_get_plural_form(duration_style_type style, exa u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_plural_form(style, ratio<1> (), pf);
      }

    protected:

      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, atto) const
      {
        static const CharT u[] =
        { 'a', 't', 't', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'a' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, femto) const
      {
        static const CharT u[] =
        { 'f', 'e', 'm', 't', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'f' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, pico) const
      {
        static const CharT u[] =
        { 'p', 'i', 'c', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'p' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, nano) const
      {
        static const CharT u[] =
        { 'n', 'a', 'n', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'n' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, micro) const
      {
        static const CharT u[] =
        { 'm', 'i', 'c', 'r', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'u' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }

      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, milli) const
      {
        static const CharT u[] =
        { 'm', 'i', 'l', 'l', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'm' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, centi) const
      {
        static const CharT u[] =
        { 'c', 'e', 'n', 't', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'c' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, deci) const
      {
        static const CharT u[] =
        { 'd', 'e', 'c', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'd' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, deca) const
      {
        static const CharT u[] =
        { 'd', 'e', 'c', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'd', 'a' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, hecto) const
      {
        static const CharT u[] =
        { 'h', 'e', 'c', 't', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'h' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, kilo) const
      {
        static const CharT u[] =
        { 'k', 'i', 'l', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'k' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, mega) const
      {
        static const CharT u[] =
        { 'm', 'e', 'g', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'M' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, giga) const
      {
        static const CharT u[] =
        { 'g', 'i', 'g', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'G' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, tera) const
      {
        static const CharT u[] =
        { 't', 'e', 'r', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'T' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, peta) const
      {
        static const CharT u[] =
        { 'p', 'e', 't', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'P' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> do_get_ratio_prefix(duration_style_type style, exa) const
      {
        static const CharT u[] =
        { 'e', 'x', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'E' };
        static const std::basic_string<CharT> symbol(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        return prefix;
      }

    };

#if   defined BOOST_CHRONO_IS_LOCALIZABLE_VIRTUAL

  template <typename CharT, typename T>
  std::basic_string<CharT> to_basic_string(T const&v, std::locale const &loc)
  {
    std::basic_ostringstream<CharT> os;
    os.imbue(loc);
    os << v;
    return os.str();
  }

  template <typename CharT, typename Rep, typename Period>
  typename enable_if<is_localizable<Period>, std::basic_string<CharT> >::type
  to_basic_string(
      duration_style_type style,
      duration<Rep,Period> value,
      std::locale const &loc
  )
  {
    std::locale nloc;
    if (!std::has_facet<duration_units<CharT> >(loc))
    {
      nloc =std::locale(loc, new duration_units_default<CharT>());
    }
    else
    {
      nloc=loc;
    }
    duration_units<CharT> const & f = std::use_facet<duration_units<CharT> >(nloc);

    if (f.swaps_value_unit_order())
    {
      return f.to_string(style, Period(), int_least64_t(value.count())) + " " + to_basic_string<CharT>(value.count(), nloc);
    }
    else
    {
      return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, Period(), int_least64_t(value.count()));
    }
  }

  template <typename CharT, typename Rep, typename Period>
  typename disable_if<is_localizable<Period> , std::basic_string<CharT> >::type
  to_basic_string(
      duration_style_type style,
      duration<Rep,Period> value,
      std::locale const& loc
  )
  {
    std::locale nloc;
    if (!std::has_facet<duration_units<CharT> >(loc))
    {
      nloc =std::locale(loc, new duration_units_default<CharT>());
    }
    else
    {
      nloc=loc;
    }
    duration_units<CharT> const & f = std::use_facet<duration_units<CharT> >(nloc);
    if (f.swaps_value_unit_order())
    {
      return f.to_string(style, detail::rt_ratio(Period()), int_least64_t(value.count())) + " " + to_basic_string<CharT>(value.count(), nloc);
    }
    else
    {
      return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, detail::rt_ratio(Period()), int_least64_t(value.count()));
    }
  }

  template <typename CharT, typename Rep, typename Period>
  typename enable_if<is_localizable<Period>, std::basic_string<CharT> >::type
  to_basic_string(
      duration_style_type style,
      duration<process_times<Rep>,Period> value,
      std::locale const &loc
  )
  {
    std::locale nloc;
    if (!std::has_facet<duration_units<CharT> >(loc))
    {
      nloc =std::locale(loc, new duration_units_default<CharT>());
    }
    else
    {
      nloc=loc;
    }
    duration_units<CharT> const & f = std::use_facet<duration_units<CharT> >(nloc);

    if (f.swaps_value_unit_order())
    {
      return f.to_string(style, nano(), int_least64_t(value.count())) + " " + to_basic_string<CharT>(value.count(), nloc);
    }
    else
    {
      return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, nano(), int_least64_t(value.count()));
    }
  }

  template <typename CharT, typename Rep, typename Period>
  typename disable_if<is_localizable<Period> , std::basic_string<CharT> >::type
  to_basic_string(
      duration_style_type style,
      duration<process_times<Rep>,Period> value,
      std::locale const& loc
  )
  {
    std::locale nloc;
    if (!std::has_facet<duration_units<CharT> >(loc))
    {
      nloc =std::locale(loc, new duration_units_default<CharT>());
    }
    else
    {
      nloc=loc;
    }
    duration_units<CharT> const & f = std::use_facet<duration_units<CharT> >(nloc);
    if (f.swaps_value_unit_order())
    {
      return f.to_string(style, detail::rt_ratio(nano()), int_least64_t(value.count())) + " " + to_basic_string<CharT>(value.count(), nloc);
    }
    else
    {
      return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, detail::rt_ratio(nano()), int_least64_t(value.count()));
    }
  }

  template <typename CharT, typename Rep, typename Period>
  std::basic_string<CharT>
  to_basic_string(duration_style_type style, duration<Rep,Period> value)
  {
    return to_basic_string<CharT>(style, value, std::locale());
  }
#endif

  } // chrono

} // boost

#endif  // header
