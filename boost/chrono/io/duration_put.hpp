//
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_PUT_HPP
#define BOOST_CHRONO_IO_DURATION_PUT_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/io/unit_strings.hpp>
#include <locale>

namespace boost
{
  namespace chrono
  {

    template <class CharT, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class duration_put: public std::locale::facet
    {
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      /**
       * Facet constructor.
       * @param refs
       */
      explicit duration_put(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       *
       * @param s
       * @param ios
       * @param d
       * @param pattern
       * @param pat_end
       *
       * @Effects Steps through the sequence from @c pattern to @c pat_end,
       * identifying characters that are part of a pattern sequence. Each character
       * that is not part of a pattern sequence is written to @c s immediately, and
       * each pattern sequence, as it is identified, results in a call to
       * @c do_put_value or @c do_put_unit;
       * thus, pattern elements and other characters are interleaved in the output
       * in the order in which they appear in the pattern. Pattern sequences are
       * identified by converting each character @c c to a @c char value as if by
       * @c ct.narrow(c,0), where @c ct is a reference to @c ctype<charT> obtained from
       * @c ios.getloc(). The first character of each sequence is equal to @c Õ%Õ,
       * followed by a pattern specifier character @c spec, which can be @c 'v' for
       * the duration value or @c 'u' for the duration unit. .
       * For each valid pattern sequence identified, calls
       * <c>do_put_value(s, ios, d)</c> or <c>do_put_unit(s, ios, d)</c>.
       *
       * @Returns: An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put(iter_type s, std::ios_base& ios, duration<Rep, Period> const& d, const CharT* pattern,
          const CharT* pat_end) const
      {
        if (!std::has_facet<duration_units<CharT> >(ios.getloc())) ios.imbue(
            std::locale(ios.getloc(), new duration_units_default<CharT> ()));

        for (; pattern != pat_end; ++pattern)
        {
          if ( (*pattern != '%') || ( (pattern + 1) == pat_end) || (!std::strchr("uvx", * (pattern + 1))))
          {
            *s++ = *pattern;
          }
          else
          {
            ++pattern;
            switch (*pattern)
            {
            case 'v':
              std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, ' ',
                  static_cast<long int> (d.count()));
              break;
            case 'u':
            {
              std::use_facet<duration_units<CharT> >(ios.getloc()).put(s, ios, d);
              break;
            }
            case 'x':
            {
              std::basic_string<CharT> pat = std::use_facet<duration_units<CharT> >(ios.getloc()).get_pattern();
              pattern = pat.data();
              pat_end = pattern + pat.size();
              break;
            }
            default:
              break;
            }
          }
        }
        return s;
      }
      template <typename Rep, typename Period>
      iter_type put(iter_type s, std::ios_base& ios, duration<Rep, Period> const& d) const
      {
        if (!std::has_facet<duration_units<CharT> >(ios.getloc())) ios.imbue(
            std::locale(ios.getloc(), new duration_units_default<CharT> ()));

        std::basic_string<CharT> str = std::use_facet<duration_units<CharT> >(ios.getloc()).get_pattern();
        return put(s, ios, d, str.data(), str.data() + str.size());
      }

      /**
       *
       * @param s
       * @param ios
       * @param d
       * @param pattern
       * @Effects Calls do_put_value(s, f, d).
       * @Returns: An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_value(iter_type s, std::ios_base& ios, duration<Rep, Period> const& d) const
      {
        do_put_value(s, ios, d);
      }

      /**
       *
       * @param s
       * @param ios
       * @param d
       * @param pattern
       * @Effects Calls do_put_unit(s, f, d).
       * @Returns: An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_unit(iter_type s, std::ios_base& ios, duration<Rep, Period> const& d) const
      {
        do_put_unit(s, ios, d);
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;
    protected:
      /**
       *
       */
      ~duration_put()
      {
      }

      //      /**
      //       *
      //       * @param s
      //       * @param ios
      //       * @param d
      //       * @param pattern
      //       * @Effects: Formats the count() the parameter d into characters
      //       * placed on the output sequence s.
      //       * @Returns: An iterator pointing immediately after the last character produced.
      //       */
      //      virtual iter_type do_put_value(iter_type s, std::ios_base& ios, Rep d) const
      //      {
      //        stringstream str(ios.getloc());
      //        str << d.days_.count();
      //        const CharT* b = str.str().data();
      //        const CharT* e = b + str.str().size();
      //        std::copy(b, e, s);
      //        return s;
      //      }
      //      /**
      //       *
      //       * @param s
      //       * @param ios
      //       * @param d
      //       * @param pattern
      //       * @Effects: Formats the unit of the parameter d into characters
      //       * placed on the output sequence s. The unit is obtained calling to the duration_unit<CharT> facet to_string()
      //       * @Returns: An iterator pointing immediately after the last character produced.
      //       */
      //      virtual iter_type do_put_unit(iter_type s, std::ios_base& ios, duration<Rep,
      //          Period> const& d) const
      //      {
      //        // retrieve duration_units facet
      //        // get string
      //        std::basic_string<CharT> str;
      //        const CharT* b = str.data();
      //        const CharT* e = b + str.size();
      //        std::copy(b, e, s);
      //      }
    };

    template <class CharT, class OutputIterator>
    std::locale::id duration_put<CharT, OutputIterator>::id;

  } // chrono
} // boost

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
