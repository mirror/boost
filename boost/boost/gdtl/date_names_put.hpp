#ifndef GDTL_DATE_NAMES_PUT_HPP___
#define GDTL_DATE_NAMES_PUT_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */


#include "boost/config.hpp" //sets BOOST_NO_STD_LOCALE

//This file basically becomes a noop if locales are not supported
#ifndef BOOST_NO_STD_LOCALE

#include "boost/gdtl/special_defs.hpp"
#include "boost/gdtl/date_defs.hpp"
#include <locale>


namespace boost {
namespace gdtl {

    //! Output facet base class for gregorian dates.
    /*! This class is a base class for date facets used to localize the
     *  names of months and the names of days in the week.
     * 
     * Requirements of Config
     *  - define an enumeration month_enum that enumerates the months. 
     *    The enumeration should be '1' based eg: Jan==1
     *  - define as_short_string and as_long_string
     *
     * (see langer & kreft p334).
     * 
     */
    template<class Config,
	     class charT = char, 
	     class OutputIterator = std::ostreambuf_iterator<charT> >
    class date_names_put : public std::locale::facet
    {
    public:
      date_names_put() {};
      typedef OutputIterator iter_type;
      typedef typename Config::month_type month_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;
      //typedef typename Config::format_type format_type;
      typedef std::basic_string<charT> string_type;

      static std::locale::id id;
      void put_special_value(iter_type& oitr, special_value_enum sv) const
      {
	do_put_special_value(oitr, sv);
      }
      void put_month_short(iter_type& oitr, month_enum moy) const
      {
	do_put_month_short(oitr, moy);
      }
      void put_month_long(iter_type& oitr, month_enum moy) const
      {
	do_put_month_long(oitr, moy);
      }
      void put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
	do_put_weekday_short(oitr, wd);
      }
      void put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
	do_put_weekday_long(oitr, wd);
      }
      bool has_date_sep_chars() const
      {
	return do_has_date_sep_chars();
      }
      void year_sep_char(iter_type& oitr) const
      {
	do_year_sep_char(oitr);
      }
      //! char between year-month
      void month_sep_char(iter_type& oitr) const
      {
	do_month_sep_char(oitr);
      }
      //! Char to separate month-day
      void day_sep_char(iter_type& oitr) const
      {
	do_day_sep_char(oitr);
      }

    protected:
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
	month_type gm(moy);
	put_string(oitr, gm.as_short_string());
      }
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_long(iter_type& oitr, 
				     month_enum moy) const
      {
	month_type gm(moy);
	put_string(oitr, gm.as_long_string());
      }
      //! Default facet implementation for special value types
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
	switch (sv) {
	  case not_a_date_time: 
	  { 
	    put_string(oitr, "not-a-date-time");
            break;
          }
          case pos_infin: 
          { 
	    put_string(oitr, "+infinity");
            break;
          }
          case neg_infin: 
          { 
	    put_string(oitr, "-infinity");
            break;
          }
	}
      }
      virtual void do_put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
      }
      virtual void do_put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
      }
      virtual bool do_has_date_sep_chars() const
      {
	return true;
      }
      virtual void do_year_sep_char(iter_type& oitr) const
      {
	put_string(oitr, "-");
      }
      //! char between year-month
      virtual void do_month_sep_char(iter_type& oitr) const
      {
	put_string(oitr, "-");
      }
      //! Char to separate month-day
      virtual void do_day_sep_char(iter_type& oitr) const
      {
	put_string(oitr, "-");
      }

      void put_string(iter_type& oi, const char* const s) const
      {
	string_type s1(s);
	typename string_type::iterator si,end;
	for (si=s1.begin(), end=s1.end(); si!=end; si++, oi++) {
	  *oi = *si;
	}
      }
    };


    //! An date name output facet that takes an array of char* to define strings
    template<class Config,
	     class charT = char, 
	     class OutputIterator = std::ostreambuf_iterator<charT> >
    class all_date_names_put : public date_names_put<Config, charT, OutputIterator>
    {
    public:
      all_date_names_put(const charT* const month_short_names[],
			 const charT* const month_long_names[],
			 const charT* const special_value_names[],
			 const charT* const weekday_short_names[],
			 const charT* const weekday_long_names[]) :
	month_short_names_(month_short_names),
	month_long_names_(month_long_names),
	special_value_names_(special_value_names),
	weekday_short_names_(weekday_short_names),
	weekday_long_names_(weekday_long_names)
      {};
      typedef OutputIterator iter_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;

    protected:
      //! Generic facet that takes array of chars
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
	put_string(oitr, month_short_names_[moy-1]);
      }
      //! Long month names 
      virtual void do_put_month_long(iter_type& oitr, month_enum moy) const
      {
	put_string(oitr, month_long_names_[moy-1]);
      }
      //! Special values names
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
	put_string(oitr, special_value_names_[sv]);
      }
      virtual void do_put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
	put_string(oitr, weekday_short_names_[wd]);
      }
      virtual void do_put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
	put_string(oitr, weekday_long_names_[wd]);
      }
    private:
      const char* const* month_short_names_;
      const char* const* month_long_names_;
      const char* const* special_value_names_;
      const char* const* weekday_short_names_;
      const char* const* weekday_long_names_;
    };

} } //namespace boost::gdtl

#endif //BOOST_NO_STD_LOCALE

/* Copyright (c) 2002
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */
#endif
