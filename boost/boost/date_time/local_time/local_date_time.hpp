#ifndef LOCAL_TIME_LOCAL_DATE_TIME_HPP__
#define LOCAL_TIME_LOCAL_DATE_TIME_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp" //todo remove?
#include "boost/shared_ptr.hpp"

namespace boost {
namespace local_time {

  //! simple exception for reporting when STD or DST cannot be determined
  struct ambiguous_result : public std::logic_error
  {
    ambiguous_result (std::string _msg="") :
      std::logic_error(std::string("Daylight Savings Results are ambiguous: " + _msg)) {}
  };


  template<class utc_time_type=posix_time::ptime, class tz_type=time_zone_base>
  class local_date_time_base :  public date_time::base_time<boost::posix_time::ptime, 
                                                            boost::posix_time::posix_time_system> { 
  public:
    enum DST_FLAG { NOT_DST, IS_DST, CALCULATE };
    typedef typename utc_time_type::time_duration_type time_duration_type;
    typedef typename utc_time_type::date_type date_type;
    local_date_time_base(utc_time_type t, // local_time
                         boost::shared_ptr<tz_type> tz, 
                         bool is_dst=false) : 
      date_time::base_time<boost::posix_time::ptime, 
                           boost::posix_time::posix_time_system>(construction_adjustment(t, tz, is_dst)),
      zone_(tz),
      is_dst_(is_dst)
    {} 

    //! Construct from a date and hour offset
    local_date_time_base(date_type d, 
                         time_duration_type td,
                         boost::shared_ptr<tz_type> tz, 
                         bool is_dst=false) : 
      date_time::base_time<boost::posix_time::ptime, 
                           boost::posix_time::posix_time_system>(construction_adjustment(utc_time_type(d, td), tz, is_dst)),
      zone_(tz),
      is_dst_(is_dst)
    {} 
    //! Simple destructor, releases time zone if last referer
    ~local_date_time_base() {};

    //! Copy constructor
    local_date_time_base(const local_date_time_base& rhs) : 
      date_time::base_time<boost::posix_time::ptime, 
                           boost::posix_time::posix_time_system>(rhs),
      zone_(rhs.zone_),
      is_dst_(rhs.is_dst_)
    {} 

    boost::shared_ptr<tz_type> zone() const 
    {
      return zone_;
    }
    bool is_dst() const
    {
      return is_dst_;
    }
    utc_time_type utc_time() const 
    {
      return boost::posix_time::ptime(time_); //TODO FIX the type with typdef
    }
    std::string to_string() const
    {
      std::stringstream ss;
      utc_time_type lt = *this + zone_->base_utc_offset();
      if (is_dst_) {
        lt += zone_->dst_offset();
      }
      ss << lt << " ";
      if (is_dst_) {
        ss << zone_->dst_zone_abbrev();
      }
      else {
        ss << zone_->std_zone_abbrev();
      }
      return ss.str();
    }
    /*! returns a local_date_time_base in the given time zone with the 
     * optional time_duration added. Will throw an exception
     * when STD or DST cannot be determined for resulting local_date_time_base.
     * STD or DST cannot be determined when the new local time falls
     * within the transition_zone (see: in_transition_zone) */
    local_date_time_base local_time_in(boost::shared_ptr<tz_type> new_tz, 
                                       time_duration_type td=time_duration_type(0,0,0)) const 
      throw(boost::local_time::ambiguous_result)
    {
      bool dst=false;
      utc_time_type t_point = *this + new_tz->base_utc_offset() + td;
      if(new_tz->has_dst())
      {
	utc_time_type s_point = new_tz->dst_local_start_time(t_point.date().year());
	utc_time_type e_point = new_tz->dst_local_end_time(t_point.date().year());
	if(t_point < s_point || (t_point > e_point - new_tz->dst_offset()))
	{
	  dst=false;
	}
	else{
	  dst=true;
	  t_point += new_tz->dst_offset();
	}
        // TODO -- the following case can never happen ...
// 	if(local_date_time_base(t_point, new_tz, dst).in_transition_zone())
// 	{
// 	  throw ambiguous_result("In transition zone, unable to determine STD or DST");
// 	}
      }
      return local_date_time_base(t_point, new_tz, dst);
    }
  private:
    boost::shared_ptr<tz_type> zone_;
    bool is_dst_;

    /*! Adjust the passed in time to UTC?
     */
    utc_time_type construction_adjustment(utc_time_type t, 
                                          boost::shared_ptr<tz_type> zone,
                                          bool is_dst)
    {
      if(is_dst) {
        t -= zone->dst_offset();
      } // else no adjust
      t -= zone->base_utc_offset();
      return t;
    }
    /*! true if local_time is within the dst_offset preceeding the 
     * transition end point.
     * Ex. "2003-Oct-26 01:30:00 (EST & EDT)" would be true because we are 
     * within the 1 hour before the transition time point of 02:00:00 */
    bool in_transition_zone(utc_time_type utc_time) const
    {
      utc_time_type end_time = zone_->dst_local_end_time(utc_time.date().year());
      utc_time_type t2 = utc_time + zone_->base_utc_offset();
      if(t2 < end_time &&  t2  >= end_time - zone_->dst_offset()) {
	return true;
      }
      else{
 	return false;
      }
    }
  };

  //!Use the default parameters to define local_date_time
  typedef local_date_time_base<> local_date_time;

} }



#endif
