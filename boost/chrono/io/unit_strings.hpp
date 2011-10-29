//
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_UNIT_STRINGS_HPP
#define BOOST_CHRONO_IO_UNIT_STRINGS_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <string>
#include <iostream>
//#include <locale>
#include <boost/utility/enable_if.hpp>

namespace boost
{
  namespace chrono
  {

    class rt_duration {
    public:
      template <typename Rep, typename Period>
      rt_duration(duration<Rep, Period> const& d)
      : num(Period::type::num)
      , den(Period::type::den)
      , count(d.count())
      {}


      intmax_t num;
      intmax_t den;
      int_least64_t count;
    };

    template <typename CharT>
    class chrono_units: public std::locale::facet
    {
    public:
      static std::locale::id id;

      explicit chrono_units(size_t refs = 0) :
        std::locale::facet(refs)
      {}

      // used for input and ouput
      virtual bool swaps_value_unit_order() const = 0;

      // used for ouput
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, atto> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, pico> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, nanoseconds value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, microseconds value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, milliseconds value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, centi> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, deci> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, seconds value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, deca> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, hecto> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, kilo> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, mega> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, tera> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, peta> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, duration<boost::int_least64_t, exa> value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, rt_duration value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, minutes value) const = 0;
      virtual std::basic_string<CharT>
      to_string(duration_style::type style, hours value) const = 0;

      // used for input
      virtual std::size_t plural_forms() const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, atto>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, pico>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, nanoseconds, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, microseconds, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, milliseconds, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, centi>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, deci>, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> plural_form(duration_style::type style, seconds, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, deca>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, hecto>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, kilo>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, mega>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, giga>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, tera>, std::size_t pf) const = 0;
//      virtual std::basic_string<CharT> plural_form(duration_style::type style, duration<boost::int_least64_t, exa>, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> plural_form(duration_style::type style, minutes, std::size_t pf) const = 0;
      virtual std::basic_string<CharT> plural_form(duration_style::type style, hours, std::size_t pf) const = 0;

      virtual std::size_t plural_form(int_least64_t value) const = 0;

    };


    template<class CharT>
    std::locale::id chrono_units<CharT>::id;

    ///////////////////////////
    // This class is used to define the strings for the default English
    template <typename CharT>
    class chrono_units_default : public chrono_units<CharT>
    {
    public:

      explicit chrono_units_default(size_t refs = 0) :
      chrono_units<CharT>(refs)
      {}

      bool swaps_value_unit_order() const
      { return false; }

      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, atto> value) const
      {
        return to_string(style, atto())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, pico> value) const
      {
        return to_string(style, pico())+to_string(style, seconds(value.count()));
      }

      std::basic_string<CharT> to_string(duration_style::type style, nanoseconds value) const
      {
        return to_string(style, nano())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, microseconds value) const
      {
        return to_string(style, micro())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, milliseconds value) const
      {
        return to_string(style, milli())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, centi> value) const
      {
        return to_string(style, centi())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, deci> value) const
      {
        return to_string(style, deci())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, seconds value) const
      {
        return plural_form(style, value, plural_form(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, deca> value) const
      {
        return to_string(style, deca())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, hecto> value) const
      {
        return to_string(style, hecto())+to_string(style, seconds(value.count()));
      }

      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, kilo> value) const
      {
        return to_string(style, kilo())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, mega> value) const
      {
        return to_string(style, mega())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, giga> value) const
      {
        return to_string(style, giga())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, tera> value) const
      {
        return to_string(style, tera())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, peta> value) const
      {
        return to_string(style, peta())+to_string(style, seconds(value.count()));
      }
      std::basic_string<CharT> to_string(duration_style::type style, duration<boost::int_least64_t, exa> value) const
      {
        return to_string(style, exa())+to_string(style, seconds(value.count()));
      }

      std::basic_string<CharT> to_string(duration_style::type style, minutes value) const
      {
        return plural_form(style, value, plural_form(value.count()));
      }

      std::basic_string<CharT> to_string(duration_style::type style, hours value) const
      {
        return plural_form(style, value, plural_form(value.count()));
      }

      std::basic_string<CharT> to_string(duration_style::type style, rt_duration value) const
      {
        std::basic_ostringstream<CharT> os;
        os << CharT('[') << value.num << CharT('/')
                            << value.den << CharT(']');
        return os.str()+to_string(style, seconds(value.count));
      }
      std::size_t plural_forms() const
      {
        return 2;
      }

      std::size_t plural_form(int_least64_t value) const
      {
        return (value==-1 || value==1) ? 0 : 1;
      }

      std::basic_string<CharT> plural_form(duration_style::type style, seconds, std::size_t pf) const
      {
        static const CharT t[] =
        { 's' };
        static const std::basic_string<CharT> symbol(t, t + sizeof(t)
            / sizeof(t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const std::basic_string<CharT> singular(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        if (pf ==0) return singular;
        if (pf ==1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> plural_form(duration_style::type style, minutes, std::size_t pf) const
      {
        static const CharT t[] =
        { 'm', 'i', 'n' };
        static const std::basic_string<CharT> symbol(t, t + sizeof(t)
            / sizeof(t[0]));

        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const std::basic_string<CharT> singular(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        if (pf ==0) return singular;
        if (pf ==1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> plural_form(duration_style::type style, hours, std::size_t pf) const
      {
        static const CharT t[] =
        { 'h' };
        static const std::basic_string<CharT> symbol(t, t + sizeof(t)
            / sizeof(t[0]));        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const std::basic_string<CharT> singular(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        if (pf ==0) return singular;
        if (pf ==1) return plural;
        // assert
        throw "exception";
      }


    protected:

      virtual std::basic_string<CharT> to_string(duration_style::type style, atto) const
      {
        static const CharT u[] =
        { 'a', 't', 't', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'a' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, pico) const
      {
        static const CharT u[] =
        { 'p', 'i', 'c', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'p' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, nano) const
      {
        static const CharT u[] =
        { 'n', 'a', 'n', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'n' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, micro) const
      {
        static const CharT u[] =
        { 'm', 'i', 'c', 'r', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'u' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }

      virtual std::basic_string<CharT> to_string(duration_style::type style, milli) const
      {
        static const CharT u[] =
        { 'm', 'i', 'l', 'l', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'm' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, centi) const
      {
        static const CharT u[] =
        { 'c', 'e', 'n', 't', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'c' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, deci) const
      {
        static const CharT u[] =
        { 'd', 'e', 'c', 'i' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'd' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, deca) const
      {
        static const CharT u[] =
        { 'd', 'e', 'c', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'd', 'a' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, hecto) const
      {
        static const CharT u[] =
        { 'h', 'e', 'c', 't', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'h' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, kilo) const
      {
        static const CharT u[] =
        { 'k', 'i', 'l', 'o' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'k' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, mega) const
      {
        static const CharT u[] =
        { 'm', 'e', 'g', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'M' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, giga) const
      {
        static const CharT u[] =
        { 'g', 'i', 'g', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'G' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, tera) const
      {
        static const CharT u[] =
        { 't', 'e', 'r', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'T' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, peta) const
      {
        static const CharT u[] =
        { 'p', 'e', 't', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'P' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }
      virtual std::basic_string<CharT> to_string(duration_style::type style, exa) const
      {
        static const CharT u[] =
        { 'e', 'x', 'a' };
        static const std::basic_string<CharT> prefix(u, u + sizeof(u)
            / sizeof(u[0]));
        static const CharT v[] =
        { 'E' };
        static const std::basic_string<CharT> symbol(v, v + sizeof(v)
            / sizeof(v[0]));

        if (style==duration_style::symbol) return symbol;
        return prefix;
      }

    };

    template <typename Period>
    struct is_localizable : false_type {};

    template <>
    struct is_localizable<atto> : true_type {};
    template <>
    struct is_localizable<femto> : true_type {};
    template <>
    struct is_localizable<pico> : true_type {};
    template <>
    struct is_localizable<nano> : true_type {};
    template <>
    struct is_localizable<micro> : true_type {};
    template <>
    struct is_localizable<milli> : true_type {};
    template <>
    struct is_localizable<centi> : true_type {};
    template <>
    struct is_localizable<deci> : true_type {};
    template <>
    struct is_localizable<ratio<1> > : true_type {};
    template <>
    struct is_localizable<deca> : true_type {};
    template <>
    struct is_localizable<hecto> : true_type {};
    template <>
    struct is_localizable<kilo> : true_type {};
    template <>
    struct is_localizable<mega> : true_type {};
    template <>
    struct is_localizable<tera> : true_type {};
    template <>
    struct is_localizable<peta> : true_type {};
    template <>
    struct is_localizable<exa> : true_type {};
    template <>
    struct is_localizable<ratio<60> > : true_type {};
    template <>
    struct is_localizable<ratio<3600> > : true_type {};


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
        duration_style::type style,
        duration<Rep,Period> value,
        std::locale const &loc
        )
    {
      std::locale nloc;
      if (!std::has_facet<chrono_units<CharT> >(loc))
        nloc =std::locale(loc, new chrono_units_default<CharT>());
      else
        nloc=loc;
      chrono_units<CharT> const & f = std::use_facet<chrono_units<CharT> >(nloc);

      if (f.swaps_value_unit_order()) {
        std::basic_string<CharT> tmp = f.to_string(style, value);
        tmp += " " + to_basic_string<CharT>(value.count(), nloc);
        return f.to_string(style, value)   + " " + to_basic_string<CharT>(value.count(), nloc);
      }
      else {
        return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, value) ;
      }
    }

    template <typename CharT, typename Rep, typename Period>
    typename disable_if<is_localizable<Period> , std::basic_string<CharT> >::type
    to_basic_string(
        duration_style::type style,
        duration<Rep,Period> value,
        std::locale const& loc
        )
    {
      std::locale nloc;
      if (!std::has_facet<chrono_units<CharT> >(loc))
        nloc =std::locale(loc, new chrono_units_default<CharT>());
      else
        nloc=loc;
      chrono_units<CharT> const & f = std::use_facet<chrono_units<CharT> >(nloc);
      if (f.swaps_value_unit_order())
        return f.to_string(style, rt_duration(value)) + " " + to_basic_string<CharT>(value.count(), nloc);
      else
        return to_basic_string<CharT>(value.count(), nloc) + " " + f.to_string(style, rt_duration(value));
    }

    template <typename CharT, typename Rep, typename Period>
    std::basic_string<CharT>
    to_basic_string(duration_style::type style, duration<Rep,Period> value)
    {
      return to_basic_string<CharT>(style, value, std::locale());
    }


  } // chrono

} // boost

#endif  // header
