/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_DIRECTED_LINE_SEGMENT_CONCEPT_HPP
#define BOOST_POLYGON_DIRECTED_LINE_SEGMENT_CONCEPT_HPP
#include "isotropy.hpp"
#include "directed_line_segment_data.hpp"
#include "directed_line_segment_traits.hpp"
#include "rectangle_concept.hpp"
#include "detail/polygon_arbitrary_formation.hpp"

namespace boost { namespace polygon{
  struct directed_line_segment_concept {};
 
  template <typename T>
  struct is_directed_line_segment_concept { typedef gtl_no type; };
  template <>
  struct is_directed_line_segment_concept<directed_line_segment_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_mutable_directed_line_segment_concept { typedef gtl_no type; };
  template <>
  struct is_mutable_directed_line_segment_concept<directed_line_segment_concept> { typedef gtl_yes type; };

  template <typename T, typename CT>
  struct directed_line_segment_distance_type_by_concept { typedef void type; };
  template <typename T>
  struct directed_line_segment_distance_type_by_concept<T, gtl_yes> { 
    typedef typename coordinate_traits<typename directed_line_segment_traits<T>::coordinate_type>::coordinate_distance type; };

  template <typename T>
  struct directed_line_segment_distance_type {
      typedef typename directed_line_segment_distance_type_by_concept<
            T, typename is_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T, typename CT>
  struct directed_line_segment_point_type_by_concept { typedef void type; };
  template <typename T>
  struct directed_line_segment_point_type_by_concept<T, gtl_yes> { 
    typedef typename directed_line_segment_traits<T>::point_type type; };

  template <typename T>
  struct directed_line_segment_point_type {
      typedef typename directed_line_segment_point_type_by_concept<
            T, typename is_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T, typename CT>
  struct directed_line_segment_coordinate_type_by_concept { typedef void type; };
  template <typename T>
  struct directed_line_segment_coordinate_type_by_concept<T, gtl_yes> { 
    typedef typename directed_line_segment_traits<T>::coordinate_type type; };

  template <typename T>
  struct directed_line_segment_coordinate_type {
      typedef typename directed_line_segment_coordinate_type_by_concept<
            T, typename is_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type type;
  };

  template <typename T>
  typename directed_line_segment_point_type<T>::type
  get(const T& segment, direction_1d dir,
  typename enable_if<typename gtl_if<typename is_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type>::type * = 0
  ) {
    return directed_line_segment_traits<T>::get(segment, dir); 
  }

  template <typename T, typename point_type>
  void 
  set(T& segment, direction_1d dir, point_type value,
  typename enable_if<typename is_mutable_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type * = 0
  ) {
    directed_line_segment_mutable_traits<T>::set(segment, dir, value); 
  }
  
  template <typename T, typename T2, typename T3>
  T
  construct(T2 low_value, T3 high_value,
            typename enable_if<typename is_mutable_directed_line_segment_concept<typename geometry_concept<T>::type>::type>::type * = 0
  ) {
    return directed_line_segment_mutable_traits<T>::construct(low_value, high_value); 
  }
  
  template <typename T, typename T2>
  T
  copy_construct(const T2& segment,
  typename enable_if< typename gtl_and<typename is_mutable_directed_line_segment_concept<typename geometry_concept<T>::type>::type,
  typename is_directed_line_segment_concept<typename geometry_concept<T2>::type>::type>::type>::type * = 0
  ) {
    return construct<T>
      (get(segment, LOW ),
       get(segment, HIGH));
  }

  template <typename T1, typename T2>
  T1 &
  assign(T1& lvalue, const T2& rvalue,
  typename enable_if< typename gtl_and< typename is_mutable_directed_line_segment_concept<typename geometry_concept<T1>::type>::type,
  typename is_directed_line_segment_concept<typename geometry_concept<T2>::type>::type>::type>::type * = 0) {
    lvalue = copy_construct<T1>(rvalue);
    return lvalue;
  }

  template <typename T, typename T2>
  bool 
  equivalence(const T& segment1, const T2& segment2,
  typename enable_if< typename gtl_and< typename is_directed_line_segment_concept<typename geometry_concept<T>::type>::type,
  typename is_directed_line_segment_concept<typename geometry_concept<T2>::type>::type>::type>::type * = 0
  ) {
    return get(segment1, LOW) ==
      get(segment2, LOW) &&
      get(segment1, HIGH) ==
      get(segment2, HIGH); 
  }
  
  struct y_dls_on_above_or_below : gtl_yes {};

  //-1 for below, 0 for on and 1 for above
  template <typename segment_type>
  typename enable_if< typename gtl_and< y_dls_on_above_or_below, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type >::type, bool>::type 
  on_above_or_below(const segment_type& segment,
                    typename directed_line_segment_traits<segment_type>::point_type value) {
    typedef polygon_arbitrary_formation<typename directed_line_segment_traits<segment_type>::coordinate_type> paf;
    typename paf::Point pt, l, h;
    assign(pt, value);
    assign(l, low(segment));
    assign(h, high(segment));
    return paf::on_above_or_below(pt, typename paf::half_edge(l, h));
  }

  struct y_dls_contains : gtl_yes {};

  template <typename segment_type>
  typename enable_if< typename gtl_and< y_dls_contains, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type >::type, bool>::type 
  contains(const segment_type& segment,
           typename directed_line_segment_traits<segment_type>::point_type value, 
           bool consider_touch = true ) {
    if(on_above_or_below(segment, value) == 0) {
      rectangle_data<typename directed_line_segment_traits<segment_type>::coordinate_type> rect;
      set_points(rect, low(segment), high(segment));
      if(area(rect) == 0.0) {
        if(!consider_touch) {
          return !equivalence(value, low(segment)) && !equivalence(value, high(segment));
        }
      }
      return contains(rect, value, consider_touch);
    }
    return false;
  }
  
  template <typename segment_type, typename segment_type_2>
  bool 
  contains(const segment_type& segment,
           const segment_type_2& value, bool consider_touch = true,
           typename enable_if< typename gtl_and< typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
           typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type>::type * = 0
           ) {
    return contains(segment, get(value, LOW), consider_touch) &&
      contains(segment, get(value, HIGH), consider_touch);
  }
  
  // get the low point
  template <typename segment_type>
  typename directed_line_segment_point_type<segment_type>::type 
  low(const segment_type& segment,
  typename enable_if< typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type * = 0
  ) { return get(segment, LOW); }

  // get the high point
  template <typename segment_type>
  typename directed_line_segment_point_type<segment_type>::type 
  high(const segment_type& segment,
  typename enable_if< typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type * = 0
  ) { return get(segment, HIGH); }

  // get the center point
  template <typename segment_type>
  typename directed_line_segment_point_type<segment_type>::type
  center(const segment_type& segment,
  typename enable_if< typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type * = 0
  ) { 
    return construct<typename directed_line_segment_traits<segment_type>::point_type>((x(high(segment)) + x(low(segment)))/2,
                                                                                      (y(high(segment)) + y(low(segment)))/2); 

  }

  struct y_dls_low : gtl_yes {};

  // set the low point to v
  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_low, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, void>::type 
  low(segment_type& segment,
      typename directed_line_segment_traits<segment_type>::point_type v) { set(segment, LOW, v); }
  
  struct y_dls_high : gtl_yes {};

  // set the high coordinate to v
  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_high, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, void>::type 
  high(segment_type& segment,
      typename directed_line_segment_traits<segment_type>::point_type v) { set(segment, HIGH, v); }
  
  template <typename segment_type>
  typename directed_line_segment_distance_type<segment_type>::type 
  length(const segment_type& segment,
  typename enable_if< typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type * = 0
  ) { return euclidean_distance(low(segment), high(segment)); }

  struct y_dls_flip : gtl_yes {};

  struct y_dls_scale_up : gtl_yes {};

  // scale segment by factor
  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_scale_up, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  scale_up(segment_type& segment, 
           typename coordinate_traits<typename directed_line_segment_traits<segment_type>::coordinate_type>::unsigned_area_type factor) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, scale_up(l, factor));
    high(segment, scale_up(h, factor));
    return segment;
  }

  struct y_dls_scale_down : gtl_yes {};

  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_scale_down, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  scale_down(segment_type& segment, 
             typename coordinate_traits<typename directed_line_segment_traits<segment_type>::coordinate_type>::unsigned_area_type factor) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, scale_down(l, factor));
    high(segment, scale_down(h, factor));
    return segment;
  }

  struct y_dls_scale : gtl_yes {};

  template <typename segment_type, typename scaling_type>
  typename enable_if<typename gtl_and<y_dls_scale, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  scale(segment_type& segment, scaling_type factor) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, scale(l, factor));
    high(segment, scale(h, factor));
    return segment;
  }


  struct y_dls_transform : gtl_yes {};

  template <typename segment_type, typename transform_type>
  typename enable_if<typename gtl_and<y_dls_transform, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  transform(segment_type& segment, const transform_type& val) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, transform(l, val));
    high(segment, transform(h, val));
    return segment;
  }  
  // move segment by delta
  template <typename segment_type>
  segment_type&
  move(segment_type& segment, orientation_2d orient,
       typename directed_line_segment_coordinate_type<segment_type>::type displacement,
       typename enable_if<typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type * = 0
       ) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, move(l, orient, displacement));
    high(segment, move(h, orient, displacement));
    return segment;
  }
  
  struct y_dls_convolve : gtl_yes {};

  // convolve this with b
  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_convolve, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  convolve(segment_type& segment,
           const typename directed_line_segment_traits<segment_type>::point_type& b) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, convolve(l, b));
    high(segment, convolve(h, b));
    return segment;
  }

  struct y_dls_deconvolve : gtl_yes {};

  // deconvolve this with b
  template <typename segment_type>
  typename enable_if<typename gtl_and<y_dls_deconvolve, typename is_mutable_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type, segment_type>::type &
  deconvolve(segment_type& segment,
             const typename directed_line_segment_traits<segment_type>::point_type& b) {
    typename directed_line_segment_point_type<segment_type>::type l = low(segment), h = high(segment);
    low(segment, deconvolve(l, b));
    high(segment, deconvolve(h, b));
    return segment;
  }

  struct y_dls_e_dist1 : gtl_yes {};

  // distance from a point to a segment
  template <typename segment_type>
  typename enable_if< typename gtl_and<y_dls_e_dist1, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type>::type,
      typename directed_line_segment_distance_type<segment_type>::type>::type
  euclidean_distance(const segment_type& segment,
                     typename directed_line_segment_traits<segment_type>::point_type position) {
    typedef typename directed_line_segment_distance_type<segment_type>::type Unit;
    Unit x1 = x(low(segment));
    Unit y1 = y(low(segment));
    Unit x2 = x(high(segment));
    Unit y2 = y(high(segment));
    Unit X = x(position);
    Unit Y = y(position);
    Unit A = X - x1;
    Unit B = Y - y1;
    Unit C = x2 - x1;
    Unit D = y2 - y1;
    Unit length_sq = C * C + D * D;
    Unit param = (A * C + B * D)/length_sq;
    if(param > 1.0) {
      return euclidean_distance(high(segment), position);
    } else if(param < 0.0) {
      return euclidean_distance(low(segment), position);
    } 
    Unit denom = sqrt(length_sq);
    if(denom == 0.0)
      return 0.0;
    Unit result = (A * D - C * B) / denom;
    if(result < 0.0)
      result *= -1;
    return result;
  }

  struct y_dls_e_dist2 : gtl_yes {};
  
  // distance between two segments
  template <typename segment_type, typename segment_type_2>
  typename enable_if< 
    typename gtl_and_3<y_dls_e_dist2, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
                       typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type,
    typename directed_line_segment_distance_type<segment_type>::type>::type
  euclidean_distance(const segment_type& segment,
                     const segment_type_2& b) {
    typename directed_line_segment_distance_type<segment_type>::type result1 = euclidean_distance(segment, low(b)),
    result2 = euclidean_distance(segment, high(b));
    if(result2 < result1) result1 = result2;
    return result1;
  }
  
  struct y_dls_e_intersects : gtl_yes {};

  // check if Interval b intersects `this` Interval
  template <typename segment_type, typename segment_type_2>
  typename enable_if< typename gtl_and_3<y_dls_e_intersects, 
                                         typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type, 
                                         typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type
  >::type, bool> ::type 
  intersects(const segment_type& segment, const segment_type_2& b, bool consider_touch = true) {
    if(consider_touch) {
      if(low(segment) == low(b) || low(segment) == high(b) || high(segment) == low(b) || high(segment) == high(b))
        return true;
    }
    typedef polygon_arbitrary_formation<typename directed_line_segment_traits<segment_type>::coordinate_type> paf;
    typename paf::Point l, h, l2, h2;
    assign(l, low(segment));
    assign(h, high(segment));
    assign(l2, low(b));
    assign(h2, high(b));
    return paf::intersects(typename paf::half_edge(l, h), typename paf::half_edge(l2, h2));
  }

  struct y_dls_e_bintersect : gtl_yes {};

  // check if Interval b partially overlaps `this` Interval
  template <typename segment_type, typename segment_type_2>
  typename enable_if< 
    typename gtl_and_3<y_dls_e_bintersect, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
                       typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type,
    bool>::type 
  boundaries_intersect(const segment_type& segment, const segment_type_2& b, 
                       bool consider_touch = true) {
    return (contains(segment, low(b), consider_touch) || 
            contains(segment, high(b), consider_touch)) &&
      (contains(b, low(segment), consider_touch) || 
       contains(b, high(segment), consider_touch));
  }

  struct y_dls_abuts1 : gtl_yes {};

  // check if they are end to end
  template <typename segment_type, typename segment_type_2>
  typename enable_if< typename gtl_and_3<y_dls_abuts1, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
                                         typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type,
                       bool>::type 
  abuts(const segment_type& segment, const segment_type_2& b, direction_1d dir) {
    return dir.to_int() ? equivalence(low(b) , high(segment)) : equivalence(low(segment) , high(b));
  }

  struct y_dls_abuts2 : gtl_yes {};

  // check if they are end to end
  template <typename segment_type, typename segment_type_2>
  typename enable_if< 
    typename gtl_and_3<y_dls_abuts2, typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
                       typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type,
    bool>::type 
  abuts(const segment_type& segment, const segment_type_2& b) {
    return abuts(segment, b, HIGH) || abuts(segment, b, LOW);
  } 

  struct y_dls_intersect : gtl_yes {};

  // set point to the intersection of segment and b
  template <typename point_type, typename segment_type, typename segment_type_2>
    typename enable_if< typename gtl_and_4<y_dls_intersect, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
      typename is_directed_line_segment_concept<typename geometry_concept<segment_type>::type>::type,
      typename is_directed_line_segment_concept<typename geometry_concept<segment_type_2>::type>::type>::type,
                       bool>::type 
  intersection(point_type& intersection, const segment_type& segment, const segment_type_2& b, 
               bool projected = false, bool round_closest = false) {
    typedef polygon_arbitrary_formation<typename directed_line_segment_traits<segment_type>::coordinate_type> paf;
    typename paf::Point pt;
    typename paf::Point l, h, l2, h2;
    assign(l, low(segment));
    assign(h, high(segment));
    assign(l2, low(b));
    assign(h2, high(b));
    typename paf::half_edge he1(l, h), he2(l2, h2);
    typename paf::compute_intersection_pack pack;
    if(pack.compute_intersection(pt, he1, he2, projected, round_closest)) {
      assign(intersection, pt);
      return true;
    }
    return false;
  }

  template <class T>
  template <class T2>
  directed_line_segment_data<T>& directed_line_segment_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <typename T>
  struct geometry_concept<directed_line_segment_data<T> > {
    typedef directed_line_segment_concept type;
  };
}
}
#endif
