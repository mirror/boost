
#ifndef DATETIME_PERIOD_FORMATTER_HPP___
#define DATETIME_PERIOD_FORMATTER_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */



namespace boost { namespace date_time {


  //! Not a facet, but a class used to specify and control period formats
  /*! Provides settings for the following:
   *   - period_separator -- default '/'
   *   - period_open_start_delimeter -- default '['
   *   - period_open_range_end_delimeter -- default ')' 
   *   - period_closed_range_end_delimeter -- default ']' 
   *   - display_as_open_range, display_as_closed_range -- default open_range
   *  Thus the default formatting for a period is as follows:
   *  [period.start()/period.last()]
   *  So for a typical date_period this would be
   *@code
   *  [2004-Jan-04/2004-Feb-01]
   *@code
   * where the date formatting is controlled by the date facet
   */
  template <class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class period_formatter { 
  public:
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef typename std::basic_string<char_type>::const_iterator const_itr_type;
    static const char_type default_period_separator[2];
    static const char_type default_period_start_delimeter[2];
    static const char_type default_period_open_range_end_delimeter[2];
    static const char_type default_period_closed_range_end_delimeter[2];

    enum range_display_options { AS_OPEN_RANGE, AS_CLOSED_RANGE };
    period_formatter(range_display_options range_option = AS_CLOSED_RANGE, 
                     const char_type* const period_separator = default_period_separator, 
                     const char_type* const period_start_delimeter = default_period_start_delimeter,
                     const char_type* const period_open_range_end_delimeter = default_period_open_range_end_delimeter,
                     const char_type* const period_closed_range_end_delimeter = default_period_closed_range_end_delimeter) :
      m_period_separator(period_separator),
      m_range_option(range_option),
      m_period_start_delimeter(period_start_delimeter),
      m_open_range_end_delimeter(period_open_range_end_delimeter),
      m_closed_range_end_delimeter(period_closed_range_end_delimeter)
    {}

    OutItrT put_period_separator(OutItrT& oitr) const 
    {
      const_itr_type ci = m_period_separator.begin();
      while (ci != m_period_separator.end()) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }
    OutItrT put_period_start_delimeter(OutItrT& oitr) const 
    {
      const_itr_type ci = m_period_start_delimeter.begin();
      while (ci != m_period_start_delimeter.end()) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }
    OutItrT put_period_end_delimeter(OutItrT& oitr) const 
    {
      
      const_itr_type ci, end;
      if (m_range_option == AS_OPEN_RANGE) {
        ci = m_open_range_end_delimeter.begin();
        end = m_open_range_end_delimeter.end();
      }
      else {
        ci = m_closed_range_end_delimeter.begin();
        end = m_closed_range_end_delimeter.end();
      }
      while (ci != end) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }
   
    range_display_options range_option() const
    {
      return m_range_option;
    }

    void 
    range_option(range_display_options option) const
    {
      m_range_option = option;
    }
      
  private:
    string_type m_period_separator;
    range_display_options m_range_option;    
    string_type m_period_start_delimeter;
    string_type m_open_range_end_delimeter;
    string_type m_closed_range_end_delimeter;
  };

  template <class CharT, class OutItrT>  
  const typename period_formatter<CharT, OutItrT>::char_type 
  period_formatter<CharT, OutItrT>::default_period_separator[2] = {'/'};

  template <class CharT, class OutItrT>  
  const typename period_formatter<CharT, OutItrT>::char_type 
  period_formatter<CharT, OutItrT>::default_period_start_delimeter[2] = {'['};

  template <class CharT, class OutItrT>  
  const typename period_formatter<CharT, OutItrT>::char_type 
  period_formatter<CharT, OutItrT>::default_period_open_range_end_delimeter[2] = {')'};

  template <class CharT, class OutItrT>  
  const typename period_formatter<CharT, OutItrT>::char_type 
  period_formatter<CharT, OutItrT>::default_period_closed_range_end_delimeter[2] = {']'};

 } } //namespace boost::date_time

#endif
