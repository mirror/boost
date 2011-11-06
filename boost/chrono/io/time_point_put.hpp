//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

/**
 * Duration formatting facet for output.
 */
#ifndef BOOST_CHRONO_IO_TIME_POINT_PUT_HPP
#define BOOST_CHRONO_IO_TIME_POINT_PUT_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/io/time_point_units.hpp>
#include <boost/chrono/io/duration_put.hpp>
#include <boost/assert.hpp>
#include <locale>

namespace boost
{
  namespace chrono
  {

    /**
     * @tparam ChatT a character type
     * @tparam OutputIterator a model of @c OutputIterator
     *
     * The @c time_point_put facet provides facilities for formatted output of duration values.
     * The member function of @c time_point_put take a duration and translate this into character string representation.
     *
     * FIXME As the facet doesn't have any data, I'm wondering if this should functions
     * shouldn't be at the namespace level or static member functions.
     * This will leverage the user to need to ensure that the facet is imbued on the ios_base.
     */
    template <class CharT, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class time_point_put: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of iterator used to write in the character buffer.
       */
      typedef OutputIterator iter_type;

      /**
       * Construct a time_point_put facet.
       * @param refs
       * @Effects Construct a time_point_put facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit time_point_put(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * @Effects Steps through the sequence from @c pattern to @c pat_end,
       * identifying characters that are part of a pattern sequence. Each character
       * that is not part of a pattern sequence is written to @c s immediately, and
       * each pattern sequence, as it is identified, results in a call to
       * @c put_value or @c put_unit;
       * thus, pattern elements and other characters are interleaved in the output
       * in the order in which they appear in the pattern. Pattern sequences are
       * identified by converting each character @c c to a @c char value as if by
       * @c ct.narrow(c,0), where @c ct is a reference to @c ctype<charT> obtained from
       * @c ios.getloc(). The first character of each sequence is equal to @c Õ%Õ,
       * followed by a pattern specifier character @c spec, which can be @c 'v' for
       * the duration value or @c 'u' for the duration unit. .
       * For each valid pattern sequence identified, calls
       * <c>put_value(s, ios, d)</c> or <c>put_unit(s, ios, d)</c>.
       *
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <class Clock, class Duration>
      iter_type put(iter_type s, std::ios_base& ios, time_point<Clock, Duration> const& tp, const CharT* pattern,
          const CharT* pat_end) const
      {
        time_point_units<CharT,OutputIterator> const& units_facet = time_point_units<CharT,OutputIterator>::imbue_if_has_not(ios);

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        for (; pattern != pat_end; ++pattern)
        {
            if (ct.narrow(*pattern, 0) == '%')
            {
                if (++pattern == pat_end)
                {
                    *s++ = pattern[-1];
                    break;
                }
                char fmt = ct.narrow(*pattern, 0);
                switch (fmt)
                {
                case 'd':
                {
                  s = put_duration(s, ios, tp.time_since_epoch());
                  break;
                }
                case 'e':
                {
                  s = put_epoch<Clock>(s, ios);
                  break;
                }
                case 'x':
                {
                  std::basic_string<CharT> pat = units_facet.get_pattern();
                  pattern = pat.data();
                  pat_end = pattern + pat.size();
                  break;
                }
                default:
                  BOOST_ASSERT(false && "Boost::Chrono internal error.");
                  break;
                }
            }
            else
                *s++ = *pattern;
        }
        return s;
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Effects imbue in @c ios the @c time_point_units_default facet if not already present.
       * Retrieves Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return put(s, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <class Clock, class Duration>
      iter_type put(iter_type s, std::ios_base& ios, time_point<Clock, Duration> const& tp) const
      {
        std::basic_string<CharT> str = time_point_units<CharT,OutputIterator>::imbue_if_has_not(ios).get_pattern();
        return put(s, ios, tp, str.data(), str.data() + str.size());
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @Effects As if std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, ' ', static_cast<long int> (d.count())).
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_duration(iter_type s, std::ios_base& ios, duration<Rep, Period> const& d) const
      {
        if (!std::has_facet<duration_put<CharT> >(ios.getloc()))
        {
          ios.imbue(std::locale(ios.getloc(), new duration_put<CharT>()));
        }
        return std::use_facet<duration_put<CharT> >(ios.getloc())
        .put(s, ios, d);
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * @param pattern
       * @Effects imbue in @c ios the @c time_point_units_default facet if not already present.
       * @Effects Calls std::use_facet<time_point_units<CharT,OutputIterator> >(ios.getloc()).put(s, ios, d).
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <typename Clock>
      iter_type put_epoch(iter_type s, std::ios_base& ios) const
      {
        return time_point_units<CharT,OutputIterator>::imbue_if_has_not(ios).template put<Clock>(s, ios);
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~time_point_put()
      {
      }

    };

    template <class CharT, class OutputIterator>
    std::locale::id time_point_put<CharT, OutputIterator>::id;

  } // chrono
} // boost

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
