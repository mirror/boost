#ifndef _DATE_TIME_DATE_FACET__HPP___
#define _DATE_TIME_DATE_FACET__HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author:  Martin Andrian, Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/algorithm/string.hpp" //todo narrow this
#include "boost/date_time/period.hpp"
#include "boost/date_time/special_values_formatter.hpp"
#include "boost/date_time/period_formatter.hpp"
#include "boost/date_time/date_generator_formatter.hpp"
#include <string>
#include <vector>

namespace boost { namespace date_time {


  /*! TODO: ...
   * Format flags are:
   *
   * %A => long_weekday_format - Full name Ex: Tuesday
   * %a => short_weekday_format - Three letter abbreviation Ex: Tue
   * %B => long_month_format - Full name Ex: October
   * %b => short_month_format - Three letter abbreviation Ex: Oct
   * %x => standard_format_specifier - defined by the locale
   * %Y-%b-%d => default_date_format - YYYY-Mon-dd
   *
   * Default month format == %b
   * Default weekday format == %a
   */
  template <class date_type,
            class CharT, 
            class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class date_facet : public std::locale::facet {
  public:
    typedef typename date_type::duration_type duration_type;
    // greg_weekday is gregorian_calendar::day_of_week_type
    typedef typename date_type::day_of_week_type day_of_week_type;
    typedef typename date_type::day_type day_type;
    typedef typename date_type::month_type month_type;
    typedef boost::date_time::period<date_type,duration_type> period_type;
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef boost::date_time::period_formatter<CharT>  period_formatter_type;
    typedef boost::date_time::special_values_formatter<CharT>  special_values_formatter_type;
    typedef std::vector<std::basic_string<CharT> > input_collection_type;
    // used for the output of the date_generators
    typedef date_generator_formatter<date_type, CharT> date_gen_formatter_type;
    typedef partial_date<date_type>          partial_date_type;
    typedef nth_kday_of_month<date_type>     nth_kday_type;
    typedef first_kday_of_month<date_type>   first_kday_type;
    typedef last_kday_of_month<date_type>    last_kday_type;
    typedef first_kday_after<date_type>      kday_after_type;
    typedef first_kday_before<date_type>     kday_before_type;
    static const char_type long_weekday_format[3];
    static const char_type short_weekday_format[3];
    static const char_type long_month_format[3];
    static const char_type short_month_format[3];
    static const char_type default_period_separator[4];
    static const char_type standard_format_specifier[3];
    static const char_type iso_format_specifier[7];
    static const char_type iso_format_extended_specifier[9];
    static const char_type default_date_format[9]; // YYYY-Mon-DD
    static std::locale::id id;
    
    explicit date_facet(::size_t a_ref = 0) 
      : std::locale::facet(a_ref), 
        //m_format(standard_format_specifier)
        m_format(default_date_format),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format)
    {}

    explicit date_facet(const char_type* format,
                        const input_collection_type& short_month_names,
                        ::size_t ref_count = 0) 
      : std::locale::facet(ref_count), 
        m_format(format),
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_month_short_names(short_month_names) 
    {}

     
    explicit date_facet(const char_type* format, 
                        period_formatter_type period_formatter = period_formatter_type(), 
                        special_values_formatter_type special_values_formatter = special_values_formatter_type(),
                        date_gen_formatter_type dg_formatter = date_gen_formatter_type(),
                        ::size_t ref_count = 0)
      : std::locale::facet(ref_count), 
        m_format(format), 
        m_month_format(short_month_format),
        m_weekday_format(short_weekday_format),
        m_period_formatter(period_formatter),
        m_date_gen_formatter(dg_formatter),
        m_special_values_formatter(special_values_formatter)
     {}
    void format(const char_type* const format) {
      m_format = format;
    }
    virtual void set_iso_format()
    {
      m_format = iso_format_specifier;
    }
    virtual void set_iso_extended_format()
    {
      m_format = iso_format_extended_specifier;
    }
    void month_format(const char_type* const format) {
      m_month_format = format;
    }
    void weekday_format(const char_type* const format) {
      m_weekday_format = format;
    }
    
    void period_formatter(period_formatter_type period_formatter) {
      m_period_formatter= period_formatter;
    }
    void special_value_formatting(const special_values_formatter_type& svf) 
    {
      m_special_values_formatter = svf;
    }
    void short_weekday_names(const input_collection_type& short_weekday_names)
    {
      m_weekday_short_names = short_weekday_names;
    }
    void long_weekday_names(const input_collection_type& long_weekday_names)
    {
      m_weekday_long_names = long_weekday_names;
    }

    void short_month_names(const input_collection_type& short_month_names)
    {
      m_month_short_names = short_month_names;
    }

    void long_month_names(const input_collection_type& long_month_names)
    {
      m_month_long_names = long_month_names;
    }

    void date_gen_phrase_strings(const input_collection_type& new_strings,
                           typename date_gen_formatter_type::phrase_elements beg_pos=date_gen_formatter_type::first)
    {
      m_date_gen_formatter.elements(new_strings, beg_pos);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const date_type& d) const 
    {
      if (d.is_special()) { 
        return do_put_special(next, a_ios, fill_char, d.as_special());
      }
      //The following line of code required the date to support a to_tm function
      return do_put_tm(next, a_ios, fill_char, to_tm(d), m_format);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const month_type& m) const 
    {
      //if (d.is_special()) { 
      //  return do_put_special(next, a_ios, fill_char, d.as_special());
      //}
      //The following line of code required the date to support a to_tm function
      tm dtm;
      dtm.tm_mon = m -1;
      return do_put_tm(next, a_ios, fill_char, dtm, m_month_format);
    }

    //! puts the day of month
    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const day_type& day) const 
    {
      tm dtm;
      dtm.tm_mday = day.as_number();
      char_type tmp[3] = {'%','d'};
      string_type temp_format(tmp);
      return do_put_tm(next, a_ios, fill_char, dtm, temp_format);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const day_of_week_type& dow) const 
    {
      //if (d.is_special()) { 
      //  return do_put_special(next, a_ios, fill_char, d.as_special());
      //}
      //The following line of code required the date to support a to_tm function
      tm dtm;
      dtm.tm_wday = dow;
      return do_put_tm(next, a_ios, fill_char, dtm, m_weekday_format);
    }

    // date durations don't interact with the facet...no put code needed here.
    // todo is that really true?  What about special values?

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const period_type& p) const 
    {
      return m_period_formatter.put_period(next, a_ios, fill_char, p, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const partial_date_type& pd) const 
    {
      return m_date_gen_formatter.put_partial_date(next, a_ios, fill_char, pd, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const nth_kday_type& nkd) const 
    {
      return m_date_gen_formatter.put_nth_kday(next, a_ios, fill_char, nkd, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const first_kday_type& fkd) const 
    {
      return m_date_gen_formatter.put_first_kday(next, a_ios, fill_char, fkd, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const last_kday_type& lkd) const 
    {
      return m_date_gen_formatter.put_last_kday(next, a_ios, fill_char, lkd, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const kday_before_type& fkb) const 
    {
      return m_date_gen_formatter.put_kday_before(next, a_ios, fill_char, fkb, *this);
    }

    OutItrT put(OutItrT next, 
                std::ios_base& a_ios, 
                char_type fill_char, 
                const kday_after_type& fka) const 
    {
      return m_date_gen_formatter.put_kday_after(next, a_ios, fill_char, fka, *this);
    }
    
  protected:
    virtual OutItrT do_put_special(OutItrT next, 
                                   std::ios_base& a_ios, 
                                   char_type fill_char, 
                                   const boost::date_time::special_values sv) const 
    {
      m_special_values_formatter.put_special(next, sv);
      return next;
    }
    virtual OutItrT do_put_tm(OutItrT next, 
                              std::ios_base& a_ios, 
                              char_type fill_char, 
                              const tm& tm_value,
                              string_type a_format) const 
    {
      // update format string with custom names
      if (m_weekday_long_names.size()) {
        boost::algorithm::replace_all(a_format, 
                                      long_weekday_format, 
                                      m_weekday_long_names[tm_value.tm_wday]);
      }
      if (m_weekday_short_names.size()) {
        boost::algorithm::replace_all(a_format, 
                                      short_weekday_format, 
                                      m_weekday_short_names[tm_value.tm_wday]);

      }
      if (m_month_long_names.size()) {
        boost::algorithm::replace_all(a_format, 
                                      long_month_format, 
                                      m_month_long_names[tm_value.tm_mon]);
      }
      if (m_month_short_names.size()) {
        boost::algorithm::replace_all(a_format, 
                                      short_month_format, 
                                      m_month_short_names[tm_value.tm_mon]);
      }
      // use time_put facet to create final string
      return std::use_facet<std::time_put<CharT> >(a_ios.getloc()).put(next, a_ios, 
                                                                       fill_char, 
                                                                       &tm_value,
                                                                       &*a_format.begin(), 
                                                                       &*a_format.end());
    }
  protected:
    string_type                   m_format;
    string_type                   m_month_format;
    string_type                   m_weekday_format;
    period_formatter_type         m_period_formatter;
    date_gen_formatter_type       m_date_gen_formatter;
    special_values_formatter_type m_special_values_formatter;
    input_collection_type         m_month_short_names;
    input_collection_type         m_month_long_names;
    input_collection_type         m_weekday_short_names;
    input_collection_type         m_weekday_long_names;
  private:
  };

  template <class date_type, class CharT, class OutItrT>
  std::locale::id date_facet<date_type, CharT, OutItrT>::id;

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::long_weekday_format[3] = {'%','A'};

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::short_weekday_format[3] = {'%','a'};

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::long_month_format[3] = {'%','B'};

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::short_month_format[3] = {'%','b'};

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::default_period_separator[4] = { ' ', '/', ' '};

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::standard_format_specifier[3] = 
    {'%', 'x' };

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::iso_format_specifier[7] = 
    {'%', 'Y', '%', 'm', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::iso_format_extended_specifier[9] = 
    {'%', 'Y', '-', '%', 'm', '-', '%', 'd' };

  template <class date_type, class CharT, class OutItrT>  
  const typename date_facet<date_type, CharT, OutItrT>::char_type 
  date_facet<date_type, CharT, OutItrT>::default_date_format[9] = 
    {'%','Y','-','%','b','-','%','d'};
} }


#endif
