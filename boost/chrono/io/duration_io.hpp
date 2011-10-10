//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_IO_HPP
#define BOOST_CHRONO_IO_DURATION_IO_HPP
#include <iostream>

#include <boost/chrono/chrono.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/mpl/if.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/chrono/io/duration_unit_string.hpp>
#include <locale>

namespace boost
{
  namespace chrono
  {

    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix_text means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    struct duration_style
    {
      enum type
      {
        prefix, symbol
      };
    };

    template<class CharT>
    class duration_punct: public std::locale::facet
    {
    public:
      typedef std::basic_string<CharT> string_type;
#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
      enum
      {
        use_long=duration_style::prefix, use_short=duration_style::symbol
      };
#endif

    private:
      duration_style::type style_;

#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
      string_type long_seconds_;
      string_type long_minutes_;
      string_type long_hours_;
      string_type short_seconds_;
      string_type short_minutes_;
      string_type short_hours_;

      template<class Period>
      string_type short_name(Period) const
      {
        return ::boost::ratio_string<Period, CharT>::short_name()
            + short_seconds_;
      }

      string_type short_name(ratio<1> ) const
      {
        return short_seconds_;
      }
      string_type short_name(ratio<60> ) const
      {
        return short_minutes_;
      }
      string_type short_name(ratio<3600> ) const
      {
        return short_hours_;
      }

      template<class Period>
      string_type long_name(Period) const
      {
        return ::boost::ratio_string<Period, CharT>::long_name()
            + long_seconds_;
      }

      string_type long_name(ratio<1> ) const
      {
        return long_seconds_;
      }
      string_type long_name(ratio<60> ) const
      {
        return long_minutes_;
      }
      string_type long_name(ratio<3600> ) const
      {
        return long_hours_;
      }

      void init_C();
#endif

    public:
      static std::locale::id id;

#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
      explicit duration_punct(int use = duration_style::prefix, size_t refs = 0) :
        std::locale::facet(refs), style_(duration_style::type(use))
      {
        init_C();
      }

      duration_punct(int use, const string_type& long_seconds, const string_type& long_minutes, const string_type& long_hours, const string_type& short_seconds, const string_type& short_minutes, const string_type& short_hours, size_t refs =
              0);

      duration_punct(int use, const duration_punct& d, size_t refs = 0);

#else
      explicit duration_punct(duration_style::type style= duration_style::prefix, size_t refs = 0) :
        std::locale::facet(refs), style_(style)
      {
      }
      duration_punct(duration_style::type style, const duration_punct&, size_t refs = 0) :
        std::locale::facet(refs), style_(style)
      {
      }
#endif




      bool is_symbol() const BOOST_NOEXCEPT
      {
        return (style_==duration_style::symbol);
      }
      bool is_prefix() const BOOST_NOEXCEPT
      {
        return (style_==duration_style::prefix);
      }
      duration_style::type get_duration_style() const BOOST_NOEXCEPT
      {
        return style_;
      }
#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED

      template<class Period>
      string_type short_name() const
      {
        return short_name(typename Period::type());
      }

      template<class Period>
      string_type long_name() const
      {
        return long_name(typename Period::type());
      }

      template<class Period>
      string_type name() const
      {
        if (is_symbol())
          return short_name<Period> ();
        else
          return long_name<Period> ();
      }
      template<class Rep, class Period>
      string_type name(duration<Rep, Period> const&) const
      {
        if (is_symbol())
          return short_name<Period> ();
        else
          return long_name<Period> ();
      }

      bool is_short_name() const
      {
        return is_symbol();
      }
      bool is_long_name() const
      {
        return is_prefix();
      }
#endif
    };

    template<class CharT>
    std::locale::id duration_punct<CharT>::id;

#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED

    template<class CharT>
    void duration_punct<CharT>::init_C()
    {
      short_seconds_ = CharT('s');
      short_minutes_ = CharT('m');
      short_hours_ = CharT('h');
      const CharT s[] =
      { 's', 'e', 'c', 'o', 'n', 'd', 's' };
      const CharT m[] =
      { 'm', 'i', 'n', 'u', 't', 'e', 's' };
      const CharT h[] =
      { 'h', 'o', 'u', 'r', 's' };
      long_seconds_.assign(s, s + sizeof(s) / sizeof(s[0]));
      long_minutes_.assign(m, m + sizeof(m) / sizeof(m[0]));
      long_hours_.assign(h, h + sizeof(h) / sizeof(h[0]));
    }



    template<class CharT>
    duration_punct<CharT>::duration_punct(int use, const string_type& long_seconds, const string_type& long_minutes, const string_type& long_hours, const string_type& short_seconds, const string_type& short_minutes, const string_type& short_hours, size_t refs) :
      std::locale::facet(refs), style_(duration_style::type(use)),
          long_seconds_(long_seconds), long_minutes_(long_minutes),
          long_hours_(long_hours), short_seconds_(short_seconds),
          short_minutes_(short_minutes), short_hours_(short_hours)
    {
    }

    template<class CharT>
    duration_punct<CharT>::duration_punct(int use, const duration_punct& d, size_t refs) :
      std::locale::facet(refs), style_(duration_style::type(use)),
          long_seconds_(d.long_seconds_), long_minutes_(d.long_minutes_),
          long_hours_(d.long_hours_), short_seconds_(d.short_seconds_),
          short_minutes_(d.short_minutes_), short_hours_(d.short_hours_)
    {
    }
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>&
    duration_short(std::basic_ostream<CharT, Traits>& os)
    {
      typedef duration_punct<CharT> Facet;
      std::locale loc = os.getloc();
      if (std::has_facet<Facet>(loc))
      {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.is_prefix())
          os.imbue(std::locale(loc, new Facet(duration_style::symbol, f)));
      } else
        os.imbue(std::locale(loc, new Facet(duration_style::symbol)));
      return os;
    }

    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>&
    duration_long(std::basic_ostream<CharT, Traits>& os)
    {
      typedef duration_punct<CharT> Facet;
      std::locale loc = os.getloc();
      if (std::has_facet<Facet>(loc))
      {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.is_symbol())
          os.imbue(std::locale(loc, new Facet(duration_style::prefix, f)));
      }
      return os;
    }
#endif


    /**
     * duration parameterized manipulator.
     */
    class duration_fmt
    {
      duration_style::type style_;
    public:

      /**
       * explicit manipulator constructor from a @c duration_style
       */
      explicit duration_fmt(duration_style::type style) BOOST_NOEXCEPT
      : style_(style)
      {}

#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
      /**
       * explicit conversion to the @c duration_style scoped enum.
       */
      explicit
      operator duration_style::type() const BOOST_NOEXCEPT
      { return style_;}
#endif

      /**
       * gets the @c duration_style scoped enum.
       */
      duration_style::type get_duration_style() const BOOST_NOEXCEPT
      { return style_;}
    };

    /**
     * Change the duration_punc facet associated to the output stream depending on the duration_format style parameter.
     */
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>&
    operator <<(std::basic_ostream<CharT, Traits>& os, duration_fmt d)
    {
      typedef duration_punct<CharT> Facet;
      std::locale loc = os.getloc();
      if (std::has_facet<Facet>(loc))
      {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.get_duration_style()!=d.get_duration_style())
          os.imbue(std::locale(loc, new Facet(d.get_duration_style(), f)));
      } else
        os.imbue(std::locale(loc, new Facet(d.get_duration_style())));
      return os;
    }

    /**
     * Change the duration_punc facet associated to the input stream depending on the duration_format style parameter.
     */
    template<class CharT, class Traits>
    std::basic_istream<CharT, Traits>&
    operator >>(std::basic_istream<CharT, Traits>& is, duration_fmt d)
    {
      typedef duration_punct<CharT> Facet;
      std::locale loc = is.getloc();
      if (std::has_facet<Facet>(loc))
      {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.get_duration_style()!=d.get_duration_style())
          is.imbue(std::locale(loc, new Facet(d.get_duration_style(), f)));
      } else
        is.imbue(std::locale(loc, new Facet(d.get_duration_style())));
      return is;
    }

    /**
     * duration_style i/o saver.
     *
     * See Boost.IO i/o state savers for a motivating compression.
     */
    template<typename CharT = char, typename Traits = std::char_traits<CharT> >
    struct duration_style_io_saver
    {

      //! the type of the state to restore
      typedef std::basic_ostream<CharT, Traits> state_type;
      //! the type of aspect to save
      typedef duration_style::type aspect_type;

      /**
       * Explicit construction from an i/o stream.
       *
       * Store a reference to the i/o stream and the value of the associated @c duration_style.
       */
      explicit duration_style_io_saver(state_type &s) :
      s_save_(s)
      {
        typedef duration_punct<CharT> Facet;
        std::locale loc = s_save_.getloc();
        if (!std::has_facet<Facet>(loc))
          s_save_.imbue(std::locale(loc, new Facet()));

        const Facet& f = std::use_facet<Facet>(s_save_.getloc());
        a_save_ = f.get_duration_style();
      }

      /**
       * Construction from an i/o stream and a @c duration_style to restore.
       *
       * Stores a reference to the i/o stream and the value @c duration_style to restore given as parameter.
       */
      duration_style_io_saver(state_type &s, aspect_type new_value) :
      s_save_(s), a_save_(new_value)
      {
      }

      /**
       * Destructor.
       *
       * Restores the i/o stream with the duration_style to be restored.
       */
      ~duration_style_io_saver()
      {
        this->restore();
      }

      /**
       * Restores the i/o stream with the duration_style to be restored.
       */
      void restore()
      {
        s_save_ << duration_fmt(a_save_);
      }
    private:
      state_type& s_save_;
      aspect_type a_save_;
    };

    template <class CharT, class Traits, class Rep, class Period>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const duration<Rep, Period>& d)
    {
      typename std::basic_ostream<CharT, Traits>::sentry ok(os);
      if (ok)
      {
        typedef duration_punct<CharT> Facet;
        typedef std::basic_string<CharT, Traits> string_type;

        bool failed = false;
        try
        {
          std::locale loc = os.getloc();

          if (!std::has_facet<Facet>(loc))
            os.imbue(std::locale(loc, new Facet));
          const Facet& f = std::use_facet<Facet>(os.getloc());

#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
          return os << d.count() << ' ' << f.template name<Rep,Period>(d);
#else
          return os << d.count() << ' ' << duration_unit<CharT>(f.is_prefix(), d);
#endif
        }
        catch (...)
        {
          failed = true;
        }
        if (failed)
        os.setstate(std::ios_base::failbit | std::ios_base::badbit);

      }
      return os;
    }

    namespace chrono_detail
    {
      template <class Rep, bool = is_scalar<Rep>::value>
      struct duration_io_intermediate
      {
        typedef Rep type;
      };

      template <class Rep>
      struct duration_io_intermediate<Rep, true>
      {
        typedef typename mpl::if_c
        <
        is_floating_point<Rep>::value,
        long double,
        typename mpl::if_c
        <
        is_signed<Rep>::value,
        long long,
        unsigned long long
        >::type
        >::type type;
      };

    }

    template <class CharT, class Traits, class Rep, class Period>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, duration<Rep, Period>& d)
    {
      typedef duration_punct<CharT> Facet;
      std::locale loc = is.getloc();
      if (!std::has_facet<Facet>(loc))
        is.imbue(std::locale(loc, new Facet));
      loc = is.getloc();
      const Facet& f = std::use_facet<Facet>(loc);
      typedef typename chrono_detail::duration_io_intermediate<Rep>::type intermediate_type;
      intermediate_type r;
      // read value into r
      is >> r;
      if (is.good())
      {
        // now determine unit
        typedef std::istreambuf_iterator<CharT, Traits> in_iterator;
        in_iterator i(is);
        in_iterator e;
        if (i != e && *i == ' ') // mandatory ' ' after value

        {
          ++i;
          if (i != e)
          {
            // unit is num / den (yet to be determined)
            unsigned long long num = 0;
            unsigned long long den = 0;
            if (*i == '[')
            {
              // parse [N/D]s or [N/D]seconds format
              ++i;
              CharT x;
              is >> num >> x >> den;
              if (!is.good() || (x != '/'))
              {
                is.setstate(is.failbit);
                return is;
              }
              i = in_iterator(is);
              if (*i != ']')
              {
                is.setstate(is.failbit);
                return is;
              }
              ++i;
              const std::basic_string<CharT> units[] =
              {
#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
                f.template long_name<ratio<1> >(),
                f.template short_name<ratio<1> >()
#else
                duration_unit<CharT>(true, seconds(2)),
                duration_unit<CharT>(false, seconds(1))
#endif
              };
              std::ios_base::iostate err = std::ios_base::goodbit;
              const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e,
                  units, units + sizeof(units)/sizeof(units[0]),
                  //~ std::use_facet<std::ctype<CharT> >(loc),
                  err);
              switch ((k - units) / 2)
              {
                case 0:
                break;
                default:
                is.setstate(err);
                return is;
              }
            }
            else
            {
              // parse SI name, short or long

              const std::basic_string<CharT> units[] =
              {
#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
                f.template long_name<atto>(),
                f.template short_name<atto>(),
                f.template long_name<femto>(),
                f.template short_name<femto>(),
                f.template long_name<pico>(),
                f.template short_name<pico>(),
                f.template long_name<nano>(),
                f.template short_name<nano>(),
                f.template long_name<micro>(),
                f.template short_name<micro>(),
                f.template long_name<milli>(),
                f.template short_name<milli>(),
                f.template long_name<centi>(),
                f.template short_name<centi>(),
                f.template long_name<deci>(),
                f.template short_name<deci>(),
                f.template long_name<deca>(),
                f.template short_name<deca>(),
                f.template long_name<hecto>(),
                f.template short_name<hecto>(),
                f.template long_name<kilo>(),
                f.template short_name<kilo>(),
                f.template long_name<mega>(),
                f.template short_name<mega>(),
                f.template long_name<giga>(),
                f.template short_name<giga>(),
                f.template long_name<tera>(),
                f.template short_name<tera>(),
                f.template long_name<peta>(),
                f.template short_name<peta>(),
                f.template long_name<exa>(),
                f.template short_name<exa>(),
                f.template long_name<ratio<1> >(),
                f.template short_name<ratio<1> >(),
                f.template long_name<ratio<60> >(),
                f.template short_name<ratio<60> >(),
                f.template long_name<ratio<3600> >(),
                f.template short_name<ratio<3600> >()
#else
                duration_unit<CharT>(true, duration<Rep, atto>(2)),
                duration_unit<CharT>(true, duration<Rep, atto>(1)),
                duration_unit<CharT>(false, duration<Rep, atto>(1)),
                duration_unit<CharT>(true, duration<Rep, femto>(2)),
                duration_unit<CharT>(true, duration<Rep, femto>(1)),
                duration_unit<CharT>(false, duration<Rep, femto>(1)),
                duration_unit<CharT>(true, duration<Rep, pico>(2)),
                duration_unit<CharT>(true, duration<Rep, pico>(1)),
                duration_unit<CharT>(false, duration<Rep, pico>(1)),
                duration_unit<CharT>(true, duration<Rep, nano>(2)),
                duration_unit<CharT>(true, duration<Rep, nano>(1)),
                duration_unit<CharT>(false, duration<Rep, nano>(1)),
                duration_unit<CharT>(true, duration<Rep, micro>(2)),
                duration_unit<CharT>(true, duration<Rep, micro>(1)),
                duration_unit<CharT>(false, duration<Rep, micro>(1)),
                duration_unit<CharT>(true, duration<Rep, milli>(2)),
                duration_unit<CharT>(true, duration<Rep, milli>(1)),
                duration_unit<CharT>(false, duration<Rep, milli>(1)),
                duration_unit<CharT>(true, duration<Rep, centi>(2)),
                duration_unit<CharT>(true, duration<Rep, centi>(1)),
                duration_unit<CharT>(false, duration<Rep, centi>(1)),
                duration_unit<CharT>(true, duration<Rep, deci>(2)),
                duration_unit<CharT>(true, duration<Rep, deci>(1)),
                duration_unit<CharT>(false, duration<Rep, deci>(1)),
                duration_unit<CharT>(true, duration<Rep, deca>(2)),
                duration_unit<CharT>(true, duration<Rep, deca>(1)),
                duration_unit<CharT>(false, duration<Rep, deca>(1)),
                duration_unit<CharT>(true, duration<Rep, hecto>(2)),
                duration_unit<CharT>(true, duration<Rep, hecto>(1)),
                duration_unit<CharT>(false, duration<Rep, hecto>(1)),
                duration_unit<CharT>(true, duration<Rep, kilo>(2)),
                duration_unit<CharT>(true, duration<Rep, kilo>(1)),
                duration_unit<CharT>(false, duration<Rep, kilo>(1)),
                duration_unit<CharT>(true, duration<Rep, mega>(2)),
                duration_unit<CharT>(true, duration<Rep, mega>(1)),
                duration_unit<CharT>(false, duration<Rep, mega>(1)),
                duration_unit<CharT>(true, duration<Rep, giga>(2)),
                duration_unit<CharT>(true, duration<Rep, giga>(1)),
                duration_unit<CharT>(false, duration<Rep, giga>(1)),
                duration_unit<CharT>(true, duration<Rep, giga>(2)),
                duration_unit<CharT>(true, duration<Rep, tera>(1)),
                duration_unit<CharT>(false, duration<Rep, giga>(1)),
                duration_unit<CharT>(true, duration<Rep, peta>(2)),
                duration_unit<CharT>(true, duration<Rep, peta>(1)),
                duration_unit<CharT>(false, duration<Rep, peta>(1)),
                duration_unit<CharT>(true, duration<Rep, exa>(2)),
                duration_unit<CharT>(true, duration<Rep, exa>(1)),
                duration_unit<CharT>(false, duration<Rep, exa>(1)),
                duration_unit<CharT>(true, duration<Rep, ratio<1> >(2)),
                duration_unit<CharT>(true, duration<Rep, ratio<1> >(1)),
                duration_unit<CharT>(false, duration<Rep, ratio<1> >(1)),
                duration_unit<CharT>(true, duration<Rep, ratio<60> >(2)),
                duration_unit<CharT>(true, duration<Rep, ratio<60> >(1)),
                duration_unit<CharT>(false, duration<Rep, ratio<60> >(1)),
                duration_unit<CharT>(true, duration<Rep, ratio<3600> >(2)),
                duration_unit<CharT>(true, duration<Rep, ratio<3600> >(1)),
                duration_unit<CharT>(false, duration<Rep, ratio<3600> >(1)),
#endif
                };
              std::ios_base::iostate err = std::ios_base::goodbit;
              const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e,
                  units, units + sizeof(units)/sizeof(units[0]),
                  //~ std::use_facet<std::ctype<CharT> >(loc),
                  err);
#if !defined BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
              switch ((k - units) / 2)
#else
              switch ((k - units) / 3)
#endif
              {
                case 0:
                num = 1ULL;
                den = 1000000000000000000ULL;
                break;
                case 1:
                num = 1ULL;
                den = 1000000000000000ULL;
                break;
                case 2:
                num = 1ULL;
                den = 1000000000000ULL;
                break;
                case 3:
                num = 1ULL;
                den = 1000000000ULL;
                break;
                case 4:
                num = 1ULL;
                den = 1000000ULL;
                break;
                case 5:
                num = 1ULL;
                den = 1000ULL;
                break;
                case 6:
                num = 1ULL;
                den = 100ULL;
                break;
                case 7:
                num = 1ULL;
                den = 10ULL;
                break;
                case 8:
                num = 10ULL;
                den = 1ULL;
                break;
                case 9:
                num = 100ULL;
                den = 1ULL;
                break;
                case 10:
                num = 1000ULL;
                den = 1ULL;
                break;
                case 11:
                num = 1000000ULL;
                den = 1ULL;
                break;
                case 12:
                num = 1000000000ULL;
                den = 1ULL;
                break;
                case 13:
                num = 1000000000000ULL;
                den = 1ULL;
                break;
                case 14:
                num = 1000000000000000ULL;
                den = 1ULL;
                break;
                case 15:
                num = 1000000000000000000ULL;
                den = 1ULL;
                break;
                case 16:
                num = 1;
                den = 1;
                break;
                case 17:
                num = 60;
                den = 1;
                break;
                case 18:
                num = 3600;
                den = 1;
                break;
                default:
                is.setstate(err);
                return is;
              }
            }
            // unit is num/den
            // r should be multiplied by (num/den) / Period
            // Reduce (num/den) / Period to lowest terms
            unsigned long long gcd_n1_n2 = math::gcd<unsigned long long>(num, Period::num);
            unsigned long long gcd_d1_d2 = math::gcd<unsigned long long>(den, Period::den);
            num /= gcd_n1_n2;
            den /= gcd_d1_d2;
            unsigned long long n2 = Period::num / gcd_n1_n2;
            unsigned long long d2 = Period::den / gcd_d1_d2;
            if (num > (std::numeric_limits<unsigned long long>::max)() / d2 ||
                den > (std::numeric_limits<unsigned long long>::max)() / n2)
            {
              // (num/den) / Period overflows
              is.setstate(is.failbit);
              return is;
            }
            num *= d2;
            den *= n2;
            // num / den is now factor to multiply by r
            typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;
            if (is_integral<intermediate_type>::value)
            {
              // Reduce r * num / den
              common_type_t t = math::gcd<common_type_t>(r, den);
              r /= t;
              den /= t;
              if (den != 1)
              {
                // Conversion to Period is integral and not exact
                is.setstate(is.failbit);
                return is;
              }
            }
            if (r > ((duration_values<common_type_t>::max)() / num))
            {
              // Conversion to Period overflowed
              is.setstate(is.failbit);
              return is;
            }
            common_type_t t = r * num;
            t /= den;
            if (t>0) {
              Rep pt = t;
              if ((duration_values<Rep>::max)() < pt)
              {
                // Conversion to Period overflowed
                is.setstate(is.failbit);
                return is;
              }
            }
            // Success!  Store it.
            r = Rep(t);
            d = duration<Rep, Period>(r);
          }
          else
          is.setstate(is.failbit | is.eofbit);
        }
        else
        {
          if (i == e)
          is.setstate(is.eofbit);
          is.setstate(is.failbit);
        }
      }
      else
      is.setstate(is.failbit);
      return is;
    }

  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
