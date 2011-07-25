/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_DIRECTED_LINE_SEGMENT_DATA_HPP
#define BOOST_POLYGON_DIRECTED_LINE_SEGMENT_DATA_HPP
#include "isotropy.hpp"
#include "point_data.hpp"
namespace boost { namespace polygon{
  template <typename T>
  class directed_line_segment_data {
  public:
    typedef T coordinate_type;
    typedef point_data<T> point_type;
    inline directed_line_segment_data()
#ifndef BOOST_POLYGON_MSVC 
      :points_() 
#endif 
    {} 
    inline directed_line_segment_data(point_type low, point_type high)
#ifndef BOOST_POLYGON_MSVC 
      :points_() 
#endif 
    {
      points_[LOW] = low; points_[HIGH] = high; 
    }
    inline directed_line_segment_data(const directed_line_segment_data& that)
#ifndef BOOST_POLYGON_MSVC 
      :points_() 
#endif 
    {
      (*this) = that; 
    }
    inline directed_line_segment_data& operator=(const directed_line_segment_data& that) {
      points_[0] = that.points_[0]; points_[1] = that.points_[1]; return *this; 
    }
    template <typename T2>
    inline directed_line_segment_data& operator=(const T2& rvalue);
    inline point_type get(direction_1d dir) const {
      return points_[dir.to_int()]; 
    }
    inline point_type low() const { return points_[0]; }
    inline point_type high() const { return points_[1]; }
    inline bool operator==(const directed_line_segment_data& that) const {
      return low() == that.low() && high() == that.high(); }
    inline bool operator!=(const directed_line_segment_data& that) const {
      return low() != that.low() || high() != that.high(); }
    inline bool operator<(const directed_line_segment_data& that) const {
      if(points_[0] < that.points_[0]) return true;
      if(points_[0] > that.points_[0]) return false;
      if(points_[1] < that.points_[1]) return true;
      return false;
    }
    inline bool operator<=(const directed_line_segment_data& that) const { return !(that < *this); }
    inline bool operator>(const directed_line_segment_data& that) const { return that < *this; }
    inline bool operator>=(const directed_line_segment_data& that) const { return !((*this) < that); }
  inline void set(direction_1d dir, point_type value) {
    points_[dir.to_int()] = value; 
  }
private:
  point_type points_[2]; 
};

}
}
#endif
