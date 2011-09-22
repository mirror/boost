//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++  to Boost

#ifndef BOOST_CHRONO_IO_TIME_POINT_IO_HPP
#define BOOST_CHRONO_IO_TIME_POINT_IO_HPP

#include <boost/chrono/io/clock_string.hpp>
#include <boost/chrono/io/duration_io.hpp>
#include <boost/chrono/chrono.hpp>
#include <locale>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/chrono/round.hpp>

namespace boost
{

  namespace chrono
  {

    struct timezone
    {
      enum type
      {
        utc, local
      };
    };
    typedef timezone::type timezone_type;

    template<class CharT>
    class time_punct: public std::locale::facet
    {
    public:
      typedef std::basic_string<CharT> string_type;

    private:
      string_type fmt_;
      chrono::timezone_type tz_;

    public:
      static std::locale::id id;

      explicit time_punct(size_t refs = 0) :
        std::locale::facet(refs), tz_(timezone::utc)
      {
      }

      time_punct(timezone_type tz, string_type fmt, size_t refs = 0)
      // todo use move semantic when available.
      :
        std::locale::facet(refs), fmt_(fmt), tz_(tz)
      {
      }

      const string_type& fmt() const BOOST_CHRONO_NOEXCEPT
      {
        return fmt_;
      }
      chrono::timezone_type get_timezone() const BOOST_CHRONO_NOEXCEPT
      {
        return tz_;
      }
    };

    template<class CharT>
    std::locale::id time_punct<CharT>::id;

    namespace detail
    {
      template<class CharT>
      struct time_manip
      {
        std::basic_string<CharT> fmt_;
        timezone tz_;

        time_manip(timezone tz, std::basic_string<CharT> fmt)
        // todo move semantics
        :
          fmt_(fmt), tz_(tz)
        {
        }
      };

      // todo move semantics
      template<class CharT, class Traits>
      std::basic_ostream<CharT, Traits>&
      operator <<(std::basic_ostream<CharT, Traits>& os, time_manip<CharT> m)
      {
        // todo move semantics
        os.imbue(std::locale(os.getloc(), new time_punct<CharT> (m.tz_, m.fmt_)));
        return os;
      }

      template<class CharT, class Traits>
      std::basic_istream<CharT, Traits>&
      operator >>(std::basic_istream<CharT, Traits>& is, time_manip<CharT> m)
      {
        // todo move semantics
        is.imbue(std::locale(is.getloc(), new time_punct<CharT> (m.tz_, m.fmt_)));
        return is;
      }

      class time_man
      {
        timezone_type form_;
      public:
        explicit time_man(timezone_type f) :
          form_(f)
        {
        }
        // explicit
        operator timezone_type() const
        {
          return form_;
        }
      };

      template<class CharT, class Traits>
      std::basic_ostream<CharT, Traits>&
      operator <<(std::basic_ostream<CharT, Traits>& os, time_man m)
      {
        os.imbue(std::locale(os.getloc(), new time_punct<CharT> (static_cast<timezone_type> (m), std::basic_string<
            CharT>())));
        return os;
      }

      template<class CharT, class Traits>
      std::basic_istream<CharT, Traits>&
      operator >>(std::basic_istream<CharT, Traits>& is, time_man m)
      {
        is.imbue(std::locale(is.getloc(), new time_punct<CharT> (static_cast<timezone_type> (m), std::basic_string<
            CharT>())));
        return is;
      }

    }

    inline detail::time_man time_fmt(timezone_type f)
    {
      return detail::time_man(f);
    }

    template<class CharT, class Traits, class Clock, class Duration>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const time_point<Clock,
        Duration>& tp)
    {
      return os << tp.time_since_epoch() << clock_string<Clock, CharT>::since();
    }

    template<class CharT, class Traits, class Clock, class Duration>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, time_point<Clock,
        Duration>& tp)
    {
      Duration d;
      is >> d;
      if (is.good())
      {
        const std::basic_string<CharT> units =
            clock_string<Clock, CharT>::since();
        std::ios_base::iostate err = std::ios_base::goodbit;
        typedef std::istreambuf_iterator<CharT, Traits> in_iterator;
        in_iterator i(is);
        in_iterator e;
        std::ptrdiff_t k =
            chrono_detail::scan_keyword(i, e, &units, &units + 1,
            //~ std::use_facet<std::ctype<CharT> >(is.getloc()),
            err) - &units;
        if (k == 1)
        {
          // failed to read epoch string
          is.setstate(err);
          return is;
        }
        tp = time_point<Clock, Duration> (d);
      } else
        is.setstate(is.failbit);
      return is;
    }

#ifndef BOOST_CHRONO_NO_UTC_TIMEPOINT

    namespace detail
    {
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
    int is_leap(int year)
    {
      if(year % 400 == 0)
      return 1;
      if(year % 100 == 0)
      return 0;
      if(year % 4 == 0)
      return 1;
      return 0;
    }
    inline int days_from_0(int year)
    {
      year--;
      return 365 * year + (year / 400) - (year/100) + (year / 4);
    }
    int days_from_1970(int year)
    {
      static const int days_from_0_to_1970 = days_from_0(1970);
      return days_from_0(year) - days_from_0_to_1970;
    }
    int days_from_1jan(int year,int month,int day)
    {
      static const int days[2][12] =
      {
        { 0,31,59,90,120,151,181,212,243,273,304,334},
        { 0,31,60,91,121,152,182,213,244,274,305,335}
      };
      return days[is_leap(year)][month-1] + day - 1;
    }

    time_t internal_timegm(std::tm const *t)
    {
      int year = t->tm_year + 1900;
      int month = t->tm_mon;
      if(month > 11)
      {
        year += month/12;
        month %= 12;
      }
      else if(month < 0)
      {
        int years_diff = (-month + 11)/12;
        year -= years_diff;
        month+=12 * years_diff;
      }
      month++;
      int day = t->tm_mday;
      int day_of_year = days_from_1jan(year,month,day);
      int days_since_epoch = days_from_1970(year) + day_of_year;

      time_t seconds_in_day = 3600 * 24;
      time_t result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;

      return result;
    }
#endif
    } // detail

    template<class _CharT, class _Traits, class _Duration>
    std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits>& os, const time_point<
        system_clock, _Duration>& tp)
    {
      typename std::basic_ostream<_CharT, _Traits>::sentry ok(os);
      if (ok)
      {
        bool failed = false;
        try
        {
          const _CharT* pb = 0; //nullptr;
          const _CharT* pe = pb;
          timezone_type tz = timezone::utc;
          typedef time_punct<_CharT> F;
          std::locale loc = os.getloc();
          if (std::has_facet<F>(loc))
          {
            const F& f = std::use_facet<F>(loc);
            pb = f.fmt().data();
            pe = pb + f.fmt().size();
            tz = f.get_timezone();
          }
          time_t t = system_clock::to_time_t(tp);
          tm tm;
          if (tz == timezone::local)
          {
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
            std::tm *tmp = 0;
            if ((tmp=localtime(&t)) == 0)
            failed = true;
            tm =*tmp;
#else
            if (localtime_r(&t, &tm) == 0)
              failed = true;
#endif
          } else
          {
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
            std::tm *tmp = 0;
            if((tmp = gmtime(&t)) == 0)
            failed = true;
            tm = *tmp;
#else
            if (gmtime_r(&t, &tm) == 0)
              failed = true;
#endif

          }
          if (!failed)
          {
            const std::time_put<_CharT>& tpf = std::use_facet<std::time_put<
                _CharT> >(loc);
            if (pb == pe)
            {
              _CharT
                  pattern[] =
                      { '%', 'Y', '-', '%', 'm', ' ', '%', 'd', ' ', '%', 'H', ':', '%', 'M', ':' };
              pb = pattern;
              pe = pb + sizeof(pattern) / sizeof(_CharT);
              failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
              if (!failed)
              {
                duration<double> d = tp - system_clock::from_time_t(t)
                    + seconds(tm.tm_sec);
                if (d.count() < 10)
                  os << _CharT('0');
                std::ios::fmtflags flgs = os.flags();
                os.setf(std::ios::fixed, std::ios::floatfield);
                os << d.count();
                os.flags(flgs);
                if (tz == timezone::local)
                {
                  _CharT sub_pattern[] =
                  { ' ', '%', 'z' };
                  pb = sub_pattern;
                  pe = pb + +sizeof(sub_pattern) / sizeof(_CharT);
                  failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
                } else
                {
                  _CharT sub_pattern[] =
                  { ' ', '+', '0', '0', '0', '0', 0 };
                  os << sub_pattern;
                }
              }
            } else
              failed = tpf.put(os, os, os.fill(), &tm, pb, pe).failed();
          }
        } catch (...)
        {
          failed = true;
        }
        if (failed)
          os.setstate(std::ios_base::failbit | std::ios_base::badbit);
      }
      return os;
    }

    namespace detail
    {

      template<class _CharT, class _InputIterator>
      minutes extract_z(_InputIterator& b, _InputIterator e, std::ios_base::iostate& err, const std::ctype<
          _CharT>& ct)
      {
        int min = 0;
        if (b != e)
        {
          char cn = ct.narrow(*b, 0);
          if (cn != '+' && cn != '-')
          {
            err |= std::ios_base::failbit;
            return minutes(0);
          }
          int sn = cn == '-' ? -1 : 1;
          int hr = 0;
          for (int i = 0; i < 2; ++i)
          {
            if (++b == e)
            {
              err |= std::ios_base::eofbit | std::ios_base::failbit;
              return minutes(0);
            }
            cn = ct.narrow(*b, 0);
            if (!('0' <= cn && cn <= '9'))
            {
              err |= std::ios_base::failbit;
              return minutes(0);
            }
            hr = hr * 10 + cn - '0';
          }
          for (int i = 0; i < 2; ++i)
          {
            if (++b == e)
            {
              err |= std::ios_base::eofbit | std::ios_base::failbit;
              return minutes(0);
            }
            cn = ct.narrow(*b, 0);
            if (!('0' <= cn && cn <= '9'))
            {
              err |= std::ios_base::failbit;
              return minutes(0);
            }
            min = min * 10 + cn - '0';
          }
          if (++b == e)
            err |= std::ios_base::eofbit;
          min += hr * 60;
          min *= sn;
        } else
          err |= std::ios_base::eofbit | std::ios_base::failbit;
        return minutes(min);
      }

    } // detail

    template<class _CharT, class _Traits, class _Duration>
    std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits>& is, time_point<
        system_clock, _Duration>& tp)
    {
      typename std::basic_istream<_CharT, _Traits>::sentry ok(is);
      if (ok)
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        try
        {
          const _CharT* pb = 0;//nullptr;
          const _CharT* pe = pb;
          typedef time_punct<_CharT> F;
          std::locale loc = is.getloc();
          timezone_type tz = timezone::utc;
          if (std::has_facet<F>(loc))
          {
            const F& f = std::use_facet<F>(loc);
            pb = f.fmt().data();
            pe = pb + f.fmt().size();
            tz = f.timezone_type();
          }
          const std::time_get<_CharT>& tg = std::use_facet<
              std::time_get<_CharT> >(loc);
          const std::ctype<_CharT>& ct =
              std::use_facet<std::ctype<_CharT> >(loc);
          tm tm; // {0}
          typedef std::istreambuf_iterator<_CharT, _Traits> _I;
          if (pb == pe)
          {
            _CharT
                pattern[] =
                    { '%', 'Y', '-', '%', 'm', '-', '%', 'd', ' ', '%', 'H', ':', '%', 'M', ':' };
            pb = pattern;
            pe = pb + sizeof(pattern) / sizeof(_CharT);
            tg.get(is, 0, is, err, &tm, pb, pe);
            if (err & std::ios_base::failbit)
              goto exit;
            double sec;
            _CharT c = _CharT();
            is >> sec;
            if (is.fail())
            {
              err |= std::ios_base::failbit;
              goto exit;
            }
            _I i(is);
            _I eof;
            c = *i;
            if (++i == eof || c != ' ')
            {
              err |= std::ios_base::failbit;
              goto exit;
            }
            minutes min = detail::extract_z(i, eof, err, ct);
            if (err & std::ios_base::failbit)
              goto exit;
            time_t t;
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
            t = detail::internal_timegm(&tm);
#else
            t = timegm(&tm);
#endif
            tp = system_clock::from_time_t(t) - min
                + round<microseconds> (duration<double> (sec));
          } else
          {
            const _CharT z[2] =
            { '%', 'z' };
            const _CharT* fz = std::search(pb, pe, z, z + 2);
            tg.get(is, 0, is, err, &tm, pb, fz);
            minutes minu(0);
            if (fz != pe)
            {
              if (err != std::ios_base::goodbit)
              {
                err |= std::ios_base::failbit;
                goto exit;
              }
              _I i(is);
              _I eof;
              minu = extract_z(i, eof, err, ct);
              if (err & std::ios_base::failbit)
                goto exit;
              if (fz + 2 != pe)
              {
                if (err != std::ios_base::goodbit)
                {
                  err |= std::ios_base::failbit;
                  goto exit;
                }
                tg.get(is, 0, is, err, &tm, fz + 2, pe);
                if (err & std::ios_base::failbit)
                  goto exit;
              }
            }
            tm.tm_isdst = -1;
            time_t t;
            if (tz == timezone::utc || fz != pe)
#if defined BOOST_WINDOWS && ! defined(__CYGWIN__)
              t = detail::internal_timegm(&tm);
#else
              t = timegm(&tm);
#endif
            else
              t = mktime(&tm);
            tp = system_clock::from_time_t(t) - minu;
          }
        } catch (...)
        {
          err |= std::ios_base::badbit | std::ios_base::failbit;
        }
        exit: is.setstate(err);
      }
      return is;
    }
#endif //UTC
  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
