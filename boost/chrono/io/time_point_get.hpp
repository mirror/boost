//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_TIME_POINT_GET_HPP
#define BOOST_CHRONO_IO_TIME_POINT_GET_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/chrono/io/time_point_units.hpp>
#include <boost/chrono/io/duration_get.hpp>
#include <boost/assert.hpp>
#include <locale>
#include <string>

/**
 * Duration formatting facet for input.
 */
namespace boost
{
  namespace chrono
  {

    /**
     * @c time_point_get is used to parse a character sequence, extracting
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
    class time_point_get: public std::locale::facet
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
       * Construct a @c time_point_get facet.
       * @param refs
       * @Effects Construct a @c time_point_get facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */

      explicit time_point_get(size_t refs = 0) :
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

      template <class Clock, class Duration>
      iter_type get(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          time_point<Clock, Duration> &tp, const char_type *pattern, const char_type *pat_end) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          return get(facet, i, e, is, err, tp, pattern, pat_end);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return get(facet, i, e, is, err, tp, pattern, pat_end);
        }
      }

      template <class Clock, class Duration>
      iter_type get(time_point_units<CharT> const &facet, iter_type s, iter_type end, std::ios_base& ios,
          std::ios_base::iostate& err, time_point<Clock, Duration> &tp, const char_type *pattern,
          const char_type *pat_end) const
      {

        Duration d;
        bool duration_found = false, epoch_found = false, loc_found = false;

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        err = std::ios_base::goodbit;
        while (pattern != pat_end && err == std::ios_base::goodbit)
        {
          std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;
          if (s == end)
          {
            err |= std::ios_base::eofbit;
            break;
          }
          if (ct.narrow(*pattern, 0) == '%')
          {
            if (++pattern == pat_end)
            {
              err |= std::ios_base::failbit;
              return s;
            }
            char cmd = ct.narrow(*pattern, 0);
            switch (cmd)
            {
            case 'd':
            {
              if (duration_found || loc_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              duration_found = true;
              s = get_duration(s, end, ios, err, d);
              std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;
              if (err & (std::ios_base::badbit | std::ios_base::failbit))
              {
                return s;
              }
              break;
            }
            case 'e':
            {
              if (epoch_found || loc_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              epoch_found = true;
              s = get_epoch<Clock> (facet, s, end, ios, err);
              std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;
              if (err & (std::ios_base::badbit | std::ios_base::failbit))
              {
                return s;
              }
              break;
            }
              //                case 'x':
              //                {
              //                  if (duration_found || epoch_found || loc_found) {
              //                    err |= std::ios_base::failbit;
              //                    return s;
              //                  }
              //                  loc_found=true;
              //                  std::basic_string<CharT> pat = time_point_units<CharT>::imbue_if_has_not(ios).get_pattern();
              //                  if (pattern+1 != pat_end)
              //                  pat.append(pattern+1, pat_end);
              //                  pattern = pat.data();
              //                  pat_end = pattern + pat.size();
              //                  break;
              //                }
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
            for (; s != end && ct.is(std::ctype_base::space, *s); ++s)
              ;
          }
          else if (ct.toupper(*s) == ct.toupper(*pattern))
          {
            ++s;
            ++pattern;
          }
          else
          {
            err |= std::ios_base::failbit;
          }
        }

        // Success!  Store it.
        tp = time_point<Clock, Duration> (d);
        std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;

        return s;
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Effects imbue in @c ios the @c time_point_units_default facet if not already present.
       * Retrieves Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return get(s, end, ios, err, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <class Clock, class Duration>
      iter_type get(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          time_point<Clock, Duration> &tp) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, i, e, is, err, tp, str.data(), str.data() + str.size());
        }
        else
        {
          time_point_units_default<CharT> facet;
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, i, e, is, err, tp, str.data(), str.data() + str.size());
        }
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep, typename Period>
      iter_type get_duration(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          duration<Rep, Period>& d) const
      {
        if (std::has_facet<duration_get<CharT> >(is.getloc()))
        {
          duration_get<CharT> const &facet = std::use_facet<duration_get<CharT> >(is.getloc());
          return get_duration(facet, i, e, is, err, d);
        }
        else
        {
          duration_get<CharT> facet;
          return get_duration(facet, i, e, is, err, d);
        }
      }

      template <typename Rep, typename Period>
      iter_type get_duration(duration_get<CharT> const& facet, iter_type s, iter_type end, std::ios_base& ios,
          std::ios_base::iostate& err, duration<Rep, Period>& d) const
      {
        return facet.get(s, end, ios, err, d);
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
      template <class Clock>
      iter_type get_epoch(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          return get_epoch(facet, i, e, is, err);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return get_epoch(facet, i, e, is, err);
        }
      }

      template <class Clock>
      iter_type get_epoch(time_point_units<CharT> const &facet, iter_type i, iter_type e, std::ios_base&,
          std::ios_base::iostate& err) const
      {
        const std::basic_string<CharT> units = facet.get_epoch<Clock> ();
        err = std::ios_base::goodbit;
        std::ptrdiff_t k = chrono_detail::scan_keyword(i, e, &units, &units + 1,
        //~ std::use_facet<std::ctype<CharT> >(ios.getloc()),
            err) - &units;
        std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;
        if (k == 1)
        {
          err |= std::ios_base::failbit;
          return i;
        }
        std::cerr << __FILE__ << ":" << __LINE__ << " err " << err << std::endl;
        return i;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~time_point_get()
      {
      }
    };

    /**
     * Unique identifier for this type of facet.
     */
    template <class CharT, class InputIterator>
    std::locale::id time_point_get<CharT, InputIterator>::id;

  } // chrono
}
// boost

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
