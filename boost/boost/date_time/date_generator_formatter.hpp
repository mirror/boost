#ifndef _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___
#define _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "boost/date_time/date_generators.hpp"

namespace boost {
namespace date_time {

  template <class date_type, class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class date_generator_formatter {
    public:
      typedef partial_date<date_type>          partial_date_type;
      typedef nth_kday_of_month<date_type>     nth_kday_type;
      typedef first_kday_of_month<date_type>   first_kday_type;
      typedef last_kday_of_month<date_type>    last_kday_type;
      typedef first_kday_after<date_type>      kday_after_type;
      typedef first_kday_before<date_type>     kday_before_type;

      typedef CharT char_type;
      typedef std::basic_string<char_type> string_type;
      typedef std::vector<string_type> collection_type;
      static const char_type first_string[6];
      static const char_type second_string[7];
      static const char_type third_string[6];
      static const char_type fourth_string[7];
      static const char_type fifth_string[6];
      static const char_type last_string[5];
      static const char_type before_string[8];
      static const char_type after_string[6];
      static const char_type of_string[3];

      enum phrase_elements {first=0, second, third, fourth, fifth, last,
                         before, after, of, number_of_phrase_elements};

      date_generator_formatter()
      {
        phrase_strings.push_back(string_type(first_string));
        phrase_strings.push_back(string_type(second_string));
        phrase_strings.push_back(string_type(third_string));
        phrase_strings.push_back(string_type(fourth_string));
        phrase_strings.push_back(string_type(fifth_string));
        phrase_strings.push_back(string_type(last_string));
        phrase_strings.push_back(string_type(before_string));
        phrase_strings.push_back(string_type(after_string));
        phrase_strings.push_back(string_type(of_string));
      }

      void elements(const collection_type& new_strings,
                    phrase_elements beg_pos=first)
      {
        if(beg_pos < number_of_phrase_elements) {
          typename collection_type::iterator itr = phrase_strings.begin();
          itr += beg_pos;
          std::copy(new_strings.begin(), new_strings.end(),
                    itr);
                    //phrase_strings.begin());
        }
      }

      template<class facet_type>
      OutItrT put_partial_date(OutItrT next, std::ios_base& a_ios,
                               CharT a_fill, const partial_date_type& pd,
                               const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, pd.day());
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, pd.month());
        return next;
      }

      template<class facet_type>
      OutItrT put_nth_kday(OutItrT next, std::ios_base& a_ios,
                           CharT a_fill, const nth_kday_type& nkd,
                           const facet_type& facet) const
      {
        put_string(next, phrase_strings[nkd.nth_week() -1]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, nkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, nkd.month());
        return next;
      }
      
      template<class facet_type>
      OutItrT put_first_kday(OutItrT next, std::ios_base& a_ios,
                             CharT a_fill, const first_kday_type& fkd,
                             const facet_type& facet) const
      {
        put_string(next, phrase_strings[first]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, fkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, fkd.month());
        return next;
      }

      template<class facet_type>
      OutItrT put_last_kday(OutItrT next, std::ios_base& a_ios,
                           CharT a_fill, const last_kday_type& lkd,
                           const facet_type& facet) const
      {
        put_string(next, phrase_strings[last]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, lkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, lkd.month());
        return next;
      }

      template<class facet_type>
      OutItrT put_kday_before(OutItrT next, std::ios_base& a_ios,
                              CharT a_fill, const kday_before_type& fkb,
                              const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, fkb.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, phrase_strings[before]);
        return next;
      }

      template<class facet_type>
      OutItrT put_kday_after(OutItrT next, std::ios_base& a_ios,
                             CharT a_fill, const kday_after_type& fka,
                             const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, fka.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, phrase_strings[after]);
        return next;
      }


    private:
      collection_type phrase_strings;

      //! helper function to put the various member string into stream
      OutItrT put_string(OutItrT next, const string_type& str) const
      {
        typename string_type::const_iterator itr = str.begin();
        while(itr != str.end()) {
          *next = *itr;
          ++itr;
          ++next;
        }
        return next;
      }
  };

  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::first_string[6] = 
    {'f','i','r','s','t'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::second_string[7] = 
    {'s','e','c','o','n','d'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::third_string[6] = 
    {'t','h','i','r','d'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::fourth_string[7] = 
    {'f','o','u','r','t','h'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::fifth_string[6] = 
    {'f','i','f','t','h'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::last_string[5] = 
    {'l','a','s','t'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::before_string[8] = 
    {'b','e','f','o','r','e'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::after_string[6] = 
    {'a','f','t','e','r'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::of_string[3] = 
    {'o','f'};
} } // namespaces

#endif // _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___
