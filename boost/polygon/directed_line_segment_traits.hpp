/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_DIRECTED_LINE_SEGMENT_TRAITS_HPP
#define BOOST_POLYGON_DIRECTED_LINE_SEGMENT_TRAITS_HPP
namespace boost { namespace polygon{
  template <typename T>
  struct directed_line_segment_traits {
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::point_type point_type;

    static inline point_type get(const T& segment, direction_1d dir) {
      return segment.get(dir); 
    }
  };

  template <typename T>
  struct directed_line_segment_mutable_traits {
    template <typename Point1>
    static inline void set(T& segment, direction_1d dir, const Point1& value) {
      typename directed_line_segment_traits<T>::point_type p1;
      assign(p1, value);
      segment.set(dir, value); 
    }
    
    template <typename Point1, typename Point2>
    static inline T construct(const Point1& low_value, 
                              const Point2& high_value) {
      typename directed_line_segment_traits<T>::point_type p1, p2; 
      assign(p1, low_value);
      assign(p2, high_value);
      return T(p1, p2); 
    }
  };
}
}
#endif

