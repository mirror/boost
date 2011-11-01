//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_GET_HPP
#define BOOST_CHRONO_IO_DURATION_GET_HPP

#include <boost/chrono/config.hpp>
#include <string>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/mpl/if.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/assert.hpp>
#include <locale>

/**
 * Duration formatting facet for input.
 */
namespace boost
{
  namespace chrono
  {

    namespace detail
    {
      template <class Rep, bool = is_scalar<Rep>::value>
      struct duration_io_intermediate
      {
        typedef Rep type;
      };

      template <class Rep>
      struct duration_io_intermediate<Rep, true>
      {
        typedef typename mpl::if_c<is_floating_point<Rep>::value, long double, typename mpl::if_c<
            is_signed<Rep>::value, long long, unsigned long long>::type>::type type;
      };

      template <typename intermediate_type>
      typename enable_if<is_integral<intermediate_type>, bool>::type
      reduce(intermediate_type& r, unsigned long long& den, std::ios_base::iostate& err)
      {
        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

          // Reduce r * num / den
        common_type_t t = math::gcd<common_type_t>(common_type_t(r), common_type_t(den));
        r /= t;
        den /= t;
        if (den != 1)
        {
          // Conversion to Period is integral and not exact
          err |= std::ios_base::failbit;
          return false;
        }
        return true;
      }
      template <typename intermediate_type>
      typename disable_if<is_integral<intermediate_type>, bool>::type
      reduce(intermediate_type& , unsigned long long& , std::ios_base::iostate& )
      {
        return true;
      }

    }

    /**
     * @c duration_get is used to parse a character sequence, extracting
     * components of a duration into a class duration.
     * Each get member parses a format as produced by a corresponding format specifier to time_put<>::put.
     * If the sequence being parsed matches the correct format, the
     * corresponding member of the class duration argument are set to the
     * value used to produce the sequence;
     * otherwise either an error is reported or unspecified values are assigned.
     * In other words, user confirmation is required for reliable parsing of
     * user-entered durations, but machine-generated formats can be parsed
     * reliably. This allows parsers to be aggressive about interpreting user
     * variations on standard formats.
     *
     * If the end iterator is reached during parsing of the get() member
     * function, the member sets std::ios_base::eofbit in err.
     */
    template <class CharT, class InputIterator = std::istreambuf_iterator<CharT> >
    class duration_get: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of iterator used to scan the character buffer.
       */
      typedef InputIterator iter_type;

      /**
       * Construct a @c duration_get facet.
       * @param refs
       * @Effects Construct a @c duration_get facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */

      explicit duration_get(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @param s start input stream iterator
       * @param end end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param d the duration
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * Requires: [pattern,pat_end) shall be a valid range.
       *
       * Effects: The function starts by evaluating err = std::ios_base::goodbit.
       * It then enters a loop, reading zero or more characters from s at
       * each iteration. Unless otherwise specified below, the loop
       * terminates when the first of the following conditions holds:
       * - The expression pattern == pat_end evaluates to true.
       * - The expression err == std::ios_base::goodbit evaluates to false.
       * - The expression s == end evaluates to true, in which case the
       * function evaluates err = std::ios_base::eofbit | std::ios_base::failbit.
       * - The next element of pattern is equal to Õ%Õ, followed by a conversion
       * specifier character, format.
       * If the number of elements in the range [pattern,pat_end) is not
       * sufficient to unambiguously determine whether the conversion
       * specification is complete and valid, the function evaluates
       * err = std::ios_base::failbit. Otherwise, the function evaluates
       * s = do_get(s, end, ios, err, d). If err == std::ios_base::goodbit holds after
       * the evaluation of the expression, the function increments pattern to
       * point just past the end of the conversion specification and continues
       * looping.
       * - The expression isspace(*pattern, ios.getloc()) evaluates to true, in
       * which case the function first increments pattern until
       * pattern == pat_end || !isspace(*pattern, ios.getloc()) evaluates to true,
       * then advances s until s == end || !isspace(*s, ios.getloc()) is true,
       * and finally resumes looping.
       * - The next character read from s matches the element pointed to by
       * pattern in a case-insensitive comparison, in which case the function
       * evaluates ++pattern, ++s and continues looping. Otherwise, the function
       * evaluates err = std::ios_base::failbit.
       *
       * Returns: s
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> &d, const char_type *pattern, const char_type *pat_end) const
      {

        if (!std::has_facet<duration_units<CharT> >(ios.getloc())) ios.imbue(
            std::locale(ios.getloc(), new duration_units_default<CharT> ()));

        typedef typename detail::duration_io_intermediate<Rep>::type intermediate_type;
        intermediate_type r;
        detail::rt_ratio rt;
        bool value_found=false, unit_found=false, loc_found=false;

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        err = std::ios_base::goodbit;
        while (pattern != pat_end && err == std::ios_base::goodbit)
        {
            if (s == end)
            {
                err |= std::ios_base::failbit;
                break;
            }
            if (ct.narrow(*pattern, 0) == '%')
            {
                if (++pattern == pat_end)
                {
                    err |= std::ios_base::failbit;
                    break;
                }
                char cmd = ct.narrow(*pattern, 0);
                switch (cmd)
                {
                case 'v':
                {
                  if (value_found) {
                    err |= std::ios_base::failbit;
                    break;
                  }
                  if (value_found) {
                    err |= std::ios_base::failbit;
                    break;
                  }
                  value_found=true;
                  s=get_value(s, end, ios, err, r);
                  if ((err & std::ios_base::failbit) != 0)
                  {
                    return s;
                  }
                  break;
                }
                case 'u':
                {
                  if (unit_found) {
                    err |= std::ios_base::failbit;
                    break;
                  }
                  unit_found=true;
                  s = get_unit<Rep>(s, end, ios, err, rt);
                  if ((err & std::ios_base::failbit) != 0)
                  {
                    return s;
                  }                  break;
                }
                case 'x':
                {
                  if (unit_found || value_found || loc_found) {
                    err |= std::ios_base::failbit;
                    break;
                  }
                  loc_found=true;
                  std::basic_string<CharT> pat = std::use_facet<duration_units<CharT> >(ios.getloc()).get_pattern();
                  if (pattern+1 != pat_end)
                  pat.append(pattern+1, pat_end);
                  pattern = pat.data();
                  pat_end = pattern + pat.size();
                  break;
                }
                default:
                  BOOST_ASSERT(false && "Boost::Chrono internal error.");
                  break;
                }

                ++pattern;
            }
            else if (ct.is(std::ctype_base::space, *pattern))
            {
                for (++pattern; pattern != pat_end && ct.is(std::ctype_base::space, *pattern); ++pattern)
                    ;
                for (        ;    s != end    && ct.is(std::ctype_base::space, *s);    ++s)
                    ;
            }
            else if (ct.toupper(*s) == ct.toupper(*pattern))
            {
                ++s;
                ++pattern;
            }
            else {
                err |= std::ios_base::failbit;
            }

        }

        unsigned long long num = rt.num;
        unsigned long long den = rt.den;

        // r should be multiplied by (num/den) / Period
        // Reduce (num/den) / Period to lowest terms
        unsigned long long gcd_n1_n2 = math::gcd<unsigned long long>(num, Period::num);
        unsigned long long gcd_d1_d2 = math::gcd<unsigned long long>(den, Period::den);
        num /= gcd_n1_n2;
        den /= gcd_d1_d2;
        unsigned long long n2 = Period::num / gcd_n1_n2;
        unsigned long long d2 = Period::den / gcd_d1_d2;
        if (num > (std::numeric_limits<unsigned long long>::max)() / d2 || den > (std::numeric_limits<
            unsigned long long>::max)() / n2)
        {
          // (num/den) / Period overflows
          err |= std::ios_base::failbit;
          return s;
        }
        num *= d2;
        den *= n2;

        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

        // num / den is now factor to multiply by r
        if (!detail::reduce(r, den, err))
          return s;

        if (r > ( (duration_values<common_type_t>::max)() / num))
        {
          // Conversion to Period overflowed
          err |= std::ios_base::failbit;
          return s;
        }
        common_type_t t = r * num;
        t /= den;
        if (t > 0)
        {
          Rep pt = t;
          if ( (duration_values<Rep>::max)() < pt)
          {
            // Conversion to Period overflowed
            err |= std::ios_base::failbit;
            return s;
          }
        }
        // Success!  Store it.
        r = Rep(t);
        d = duration<Rep, Period> (r);


        return s;
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Effects imbue in @c ios the @c duration_units_default facet if not already present.
       * Retrieves Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return get(s, end, ios, err, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> & d) const
      {
        if (!std::has_facet<duration_units<CharT> >(ios.getloc())) ios.imbue(
            std::locale(ios.getloc(), new duration_units_default<CharT> ()));

        std::basic_string < CharT > str = std::use_facet<duration_units<CharT> >(ios.getloc()).get_pattern();
        return get(s, end, ios, err, d, str.data(), str.data() + str.size());
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep>
      iter_type get_value(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err, Rep& r) const
      {
        return std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r);
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @param pattern
       * @Effects Calls do_put_unit(s, ios, d).
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep>
      iter_type get_unit(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          detail::rt_ratio &rt) const
      {
        if (!std::has_facet<duration_units<CharT> >(is.getloc()))
          is.imbue(std::locale(is.getloc(), new duration_units_default<CharT> ()));
        duration_units<CharT> const &facet = std::use_facet<duration_units<CharT> >(is.getloc());

        if (*i == '[')
        {
          // parse [N/D]s or [N/D]seconds format
          ++i;
          i=std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.num);
          if ((err & std::ios_base::failbit) != 0)
          {
            return i;
          }

          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          CharT x = *i++;
          if (x != '/')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          i=std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.den);
          if ((err & std::ios_base::failbit) != 0)
          {
            return i;
          }
          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          if (*i != ']')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          ++i;
          if (i==e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          const std::basic_string<CharT> units[] =
          {
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 1),
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 0),
              facet.template get_plural_form<ratio<1> >(duration_style::symbol, 0)
          };
          // FIXME is this necessary?????
          err = std::ios_base::goodbit;
          const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e, units,
              units + sizeof (units) / sizeof (units[0]),
              //~ std::use_facet<std::ctype<CharT> >(loc),
              err);
          switch ( (k - units) / 3)
          {
          case 0:
            break;
          default:
            err |= std::ios_base::failbit;
            return i;
          }
        }
        else
        {
          // parse SI name, short or long

          const std::basic_string<CharT> units[] =
          {
              facet.template get_plural_form<atto>(duration_style::prefix, 1),
              facet.template get_plural_form<atto>(duration_style::prefix, 0),
              facet.template get_plural_form<atto>(duration_style::symbol, 0),
              facet.template get_plural_form<femto>(duration_style::prefix, 1),
              facet.template get_plural_form<femto>(duration_style::prefix, 0),
              facet.template get_plural_form<femto>(duration_style::symbol, 0),
              facet.template get_plural_form<pico>(duration_style::prefix, 1),
              facet.template get_plural_form<pico>(duration_style::prefix, 0),
              facet.template get_plural_form<pico>(duration_style::symbol, 0),
              facet.template get_plural_form<nano>(duration_style::prefix, 1),
              facet.template get_plural_form<nano>(duration_style::prefix, 0),
              facet.template get_plural_form<nano>(duration_style::symbol, 0),
              facet.template get_plural_form<micro>(duration_style::prefix, 1),
              facet.template get_plural_form<micro>(duration_style::prefix, 0),
              facet.template get_plural_form<micro>(duration_style::symbol, 0),
              facet.template get_plural_form<milli>(duration_style::prefix, 1),
              facet.template get_plural_form<milli>(duration_style::prefix, 0),
              facet.template get_plural_form<milli>(duration_style::symbol, 0),
              facet.template get_plural_form<centi>(duration_style::prefix, 1),
              facet.template get_plural_form<centi>(duration_style::prefix, 0),
              facet.template get_plural_form<centi>(duration_style::symbol, 0),
              facet.template get_plural_form<deci>(duration_style::prefix, 1),
              facet.template get_plural_form<deci>(duration_style::prefix, 0),
              facet.template get_plural_form<deci>(duration_style::symbol, 0),
              facet.template get_plural_form<deca>(duration_style::prefix, 1),
              facet.template get_plural_form<deca>(duration_style::prefix, 0),
              facet.template get_plural_form<deca>(duration_style::symbol, 0),
              facet.template get_plural_form<hecto>(duration_style::prefix, 1),
              facet.template get_plural_form<hecto>(duration_style::prefix, 0),
              facet.template get_plural_form<hecto>(duration_style::symbol, 0),
              facet.template get_plural_form<kilo>(duration_style::prefix, 1),
              facet.template get_plural_form<kilo>(duration_style::prefix, 0),
              facet.template get_plural_form<kilo>(duration_style::symbol, 0),
              facet.template get_plural_form<mega>(duration_style::prefix, 1),
              facet.template get_plural_form<mega>(duration_style::prefix, 0),
              facet.template get_plural_form<mega>(duration_style::symbol, 0),
              facet.template get_plural_form<giga>(duration_style::prefix, 1),
              facet.template get_plural_form<giga>(duration_style::prefix, 0),
              facet.template get_plural_form<giga>(duration_style::symbol, 0),
              facet.template get_plural_form<tera>(duration_style::prefix, 1),
              facet.template get_plural_form<tera>(duration_style::prefix, 0),
              facet.template get_plural_form<tera>(duration_style::symbol, 0),
              facet.template get_plural_form<peta>(duration_style::prefix, 1),
              facet.template get_plural_form<peta>(duration_style::prefix, 0),
              facet.template get_plural_form<peta>(duration_style::symbol, 0),
              facet.template get_plural_form<exa>(duration_style::prefix, 1),
              facet.template get_plural_form<exa>(duration_style::prefix, 0),
              facet.template get_plural_form<exa>(duration_style::symbol, 0),
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 1),
              facet.template get_plural_form<ratio<1> >(duration_style::prefix, 0),
              facet.template get_plural_form<ratio<1> >(duration_style::symbol, 0),
              facet.template get_plural_form<ratio<60> >(duration_style::prefix, 1),
              facet.template get_plural_form<ratio<60> >(duration_style::prefix, 0),
              facet.template get_plural_form<ratio<60> >(duration_style::symbol, 0),
              facet.template get_plural_form<ratio<3600> >(duration_style::prefix, 1),
              facet.template get_plural_form<ratio<3600> >(duration_style::prefix, 0),
              facet.template get_plural_form<ratio<3600> >(duration_style::symbol, 0)
              };
          err = std::ios_base::goodbit;
          const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e, units,
              units + sizeof (units) / sizeof (units[0]),
              //~ std::use_facet<std::ctype<CharT> >(loc),
              err);

          switch ( (k - units) / 3)
          {
          case 0:
            rt = detail::rt_ratio(atto());
            break;
          case 1:
            rt = detail::rt_ratio(femto());
            break;
          case 2:
            rt = detail::rt_ratio(pico());
            break;
          case 3:
            rt = detail::rt_ratio(nano());
            break;
          case 4:
            rt = detail::rt_ratio(micro());
            break;
          case 5:
            rt = detail::rt_ratio(milli());
            break;
          case 6:
            rt = detail::rt_ratio(centi());
            break;
          case 7:
            rt = detail::rt_ratio(deci());
            break;
          case 8:
            rt = detail::rt_ratio(deca());
            break;
          case 9:
            rt = detail::rt_ratio(hecto());
            break;
          case 10:
            rt = detail::rt_ratio(kilo());
            break;
          case 11:
            rt = detail::rt_ratio(mega());
            break;
          case 12:
            rt = detail::rt_ratio(giga());
            break;
          case 13:
            rt = detail::rt_ratio(tera());
            break;
          case 14:
            rt = detail::rt_ratio(peta());
            break;
          case 15:
            rt = detail::rt_ratio(exa());
            break;
          case 16:
            rt = detail::rt_ratio(ratio<1>());
            break;
          case 17:
            rt = detail::rt_ratio(ratio<60>());
            break;
          case 18:
            rt = detail::rt_ratio(ratio<3600>());
            break;
          default:
            err = std::ios_base::failbit;
            return i;
          }
        }
        // unit is num/den

        return i;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~duration_get()
      {
      }
    };

    /**
     * Unique identifier for this type of facet.
     */
    template <class CharT, class OutputIterator>
    std::locale::id duration_get<CharT, OutputIterator>::id;

  } // chrono
}
// boost

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
