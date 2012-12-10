// Boost.Polygon library interval_concept.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_CONCEPT_HPP
#define BOOST_POLYGON_INTERVAL_CONCEPT_HPP

#include "isotropy.hpp"
#include "interval_traits.hpp"

namespace boost {
namespace polygon {

struct interval_concept {};

template <typename ConceptType>
struct is_interval_concept {
  typedef gtl_no type;
};

template <>
struct is_interval_concept<interval_concept> {
  typedef gtl_yes type;
};

template <typename ConceptType>
struct is_mutable_interval_concept {
  typedef gtl_no type;
};

template <>
struct is_mutable_interval_concept<interval_concept> {
  typedef gtl_yes type;
};

template <typename GeometryType, typename BoolType>
struct interval_coordinate_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct interval_coordinate_type_by_concept<GeometryType, gtl_yes> {
  typedef typename interval_traits<GeometryType>::coordinate_type type;
};

template <typename GeometryType>
struct interval_coordinate_type {
  typedef typename interval_coordinate_type_by_concept<
    GeometryType,
    typename is_interval_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

template <typename GeometryType, typename BoolType>
struct interval_difference_type_by_concept {
  typedef void type;
};

template <typename GeometryType>
struct interval_difference_type_by_concept<GeometryType, gtl_yes> {
  typedef typename coordinate_traits<
    typename interval_traits<GeometryType>::coordinate_type
  >::coordinate_difference type;
};

template <typename GeometryType>
struct interval_difference_type {
  typedef typename interval_difference_type_by_concept<
    GeometryType,
    typename is_interval_concept<
      typename geometry_concept<GeometryType>::type
    >::type
  >::type type;
};

struct y_i_get : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}

struct y_i_set : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}

struct y_i_construct : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}

struct y_i_copy_construct : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
IntervalType1>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}

struct y_i_assign : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
IntervalType1>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}

struct y_i_low : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}

struct y_i_high : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}

struct y_i_low2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
void>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}

struct y_i_high2 : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
void>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}

struct y_i_equivalence : gtl_yes {};

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
bool>::type equivalence(
    const IntervalType1& interval1, const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}

struct y_i_contains : gtl_yes {};

template <typename interval_type>
typename enable_if< typename gtl_and< y_i_contains, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type >::type, bool>::type
contains(const interval_type& interval,
	 typename interval_coordinate_type<interval_type>::type value,
	 bool consider_touch = true ) {
  if(consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}

struct y_i_contains2 : gtl_yes {};

template <typename interval_type, typename interval_type_2>
typename enable_if< typename gtl_and_3<
      y_i_contains2,
      typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
      typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
    bool>::type
contains(const interval_type& interval,
	 const interval_type_2& value,
	 bool consider_touch = true) {
  return contains(interval, get(value, LOW), consider_touch) &&
    contains(interval, get(value, HIGH), consider_touch);
}

struct y_i_center : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}

struct y_i_delta : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}

struct y_i_flip : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(IntervalType& interval,
     typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_scale_up : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& scale_up(IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}

struct y_i_scale_down : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& scale_down(IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}

// TODO(asydorchuk): Deprecated.
struct y_i_scale : gtl_yes {};

template <typename interval_type>
typename enable_if<typename gtl_and<y_i_scale, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type, interval_type>::type &
scale(interval_type& interval, double factor) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round((double)(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round((double)low(interval)* factor));
  high(interval, (newHigh));
  return interval;
}

struct y_i_move : gtl_yes {};

template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& move(IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(static_cast<Unit>(high(interval)) + displacement));
  return interval;
}

struct y_i_convolve : gtl_yes {};

// convolve this with b
template <typename interval_type>
typename enable_if<typename gtl_and<y_i_convolve, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type, interval_type>::type &
convolve(interval_type& interval,
	 typename interval_coordinate_type<interval_type>::type b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval) + b;
  Unit newHigh = high(interval) + b;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_deconvolve : gtl_yes {};

// deconvolve this with b
template <typename interval_type>
typename enable_if<typename gtl_and<y_i_deconvolve, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type, interval_type>::type &
deconvolve(interval_type& interval,
	   typename interval_coordinate_type<interval_type>::type b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval)  - b;
  Unit newHigh = high(interval) - b;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_convolve2 : gtl_yes {};

// convolve this with b
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_convolve2,
		     typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  interval_type>::type &
convolve(interval_type& interval,
	 const interval_type_2& b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval)  + low(b);
  Unit newHigh = high(interval) + high(b);
  low(interval, newLow);
		       high(interval, newHigh);
		       return interval;
}

struct y_i_deconvolve2 : gtl_yes {};

// deconvolve this with b
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3< y_i_deconvolve2,
		      typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		      typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  interval_type>::type &
deconvolve(interval_type& interval,
	   const interval_type_2& b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval)  - low(b);
  Unit newHigh = high(interval) - high(b);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_reconvolve : gtl_yes {};

// reflected convolve this with b
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_reconvolve,
		     typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  interval_type>::type &
reflected_convolve(interval_type& interval,
		   const interval_type_2& b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval)  - high(b);
  Unit newHigh = high(interval) - low(b);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_redeconvolve : gtl_yes {};

// reflected deconvolve this with b
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3< y_i_redeconvolve,
		      typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		      typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  interval_type>::type &
reflected_deconvolve(interval_type& interval,
		     const interval_type_2& b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit newLow  = low(interval)  + high(b);
  Unit newHigh = high(interval) + low(b);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}

struct y_i_e_dist1 : gtl_yes {};

// distance from a coordinate to an interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_e_dist1, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     typename interval_difference_type<interval_type>::type>::type
euclidean_distance(const interval_type& interval,
		   typename interval_coordinate_type<interval_type>::type position) {
  typedef typename coordinate_traits<typename interval_difference_type<interval_type>::type>::coordinate_difference Unit;
  Unit dist[3] = {0, (Unit)low(interval) - (Unit)position, (Unit)position - (Unit)high(interval)};
  return dist[ (dist[1] > 0) + ((dist[2] > 0) << 1) ];
}

struct y_i_e_dist2 : gtl_yes {};

// distance between two intervals
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_e_dist2, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  typename interval_difference_type<interval_type>::type>::type
euclidean_distance(const interval_type& interval,
		   const interval_type_2& b) {
  typedef typename coordinate_traits<typename interval_difference_type<interval_type>::type>::coordinate_difference Unit;
  Unit dist[3] = {0, (Unit)low(interval) - (Unit)high(b), (Unit)low(b) - (Unit)high(interval)};
  return dist[ (dist[1] > 0) + ((dist[2] > 0) << 1) ];
}

struct y_i_e_intersects : gtl_yes {};

// check if Interval b intersects `this` Interval
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_e_intersects, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  bool>::type
  intersects(const interval_type& interval, const interval_type_2& b,
	     bool consider_touch = true) {
		       return consider_touch ?
			 (low(interval) <= high(b)) & (high(interval) >= low(b)) :
			 (low(interval) < high(b)) & (high(interval) > low(b));
}

struct y_i_e_bintersect : gtl_yes {};

// check if Interval b partially overlaps `this` Interval
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_e_bintersect, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  bool>::type
boundaries_intersect(const interval_type& interval, const interval_type_2& b,
		     bool consider_touch = true) {
  return (contains(interval, low(b), consider_touch) ||
	  contains(interval, high(b), consider_touch)) &&
    (contains(b, low(interval), consider_touch) ||
     contains(b, high(interval), consider_touch));
}

struct y_i_abuts1 : gtl_yes {};

// check if they are end to end
template <typename interval_type, typename interval_type_2>
typename enable_if< typename gtl_and_3<y_i_abuts1, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
				       typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
		     bool>::type
abuts(const interval_type& interval, const interval_type_2& b, direction_1d dir) {
  return dir.to_int() ? low(b) == high(interval) : low(interval) == high(b);
}

struct y_i_abuts2 : gtl_yes {};

// check if they are end to end
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_abuts2, typename is_interval_concept<typename geometry_concept<interval_type>::type>::type,
		     typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  bool>::type
abuts(const interval_type& interval, const interval_type_2& b) {
  return abuts(interval, b, HIGH) || abuts(interval, b, LOW);
}

struct y_i_intersect : gtl_yes {};

// set 'this' interval to the intersection of 'this' and b
template <typename interval_type, typename interval_type_2>
typename enable_if< typename gtl_and_3<y_i_intersect, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
				       typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
		     bool>::type
intersect(interval_type& interval, const interval_type_2& b, bool consider_touch = true) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit lowVal = (std::max)(low(interval), low(b));
  Unit highVal = (std::min)(high(interval), high(b));
  bool valid = consider_touch ?
    lowVal <= highVal :
    lowVal < highVal;
  if(valid) {
    low(interval, lowVal);
    high(interval, highVal);
  }
  return valid;
}

struct y_i_g_intersect : gtl_yes {};

// set 'this' interval to the generalized intersection of 'this' and b
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_g_intersect, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		    typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  interval_type>::type &
generalized_intersect(interval_type& interval, const interval_type_2& b) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit coords[4] = {low(interval), high(interval), low(b), high(b)};
  //consider implementing faster sorting of small fixed length range
  polygon_sort(coords, coords+4);
  low(interval, coords[1]);
  high(interval, coords[2]);
  return interval;
}

struct y_i_bloat : gtl_yes {};

// bloat the Interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_bloat, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     interval_type>::type &
bloat(interval_type& interval, typename interval_coordinate_type<interval_type>::type bloating) {
  low(interval, low(interval)-bloating);
  high(interval, high(interval)+bloating);
  return interval;
}

struct y_i_bloat2 : gtl_yes {};

// bloat the specified side of `this` Interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_bloat2, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     interval_type>::type &
bloat(interval_type& interval, direction_1d dir, typename interval_coordinate_type<interval_type>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}

struct y_i_shrink : gtl_yes {};

// shrink the Interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_shrink, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     interval_type>::type &
shrink(interval_type& interval, typename interval_coordinate_type<interval_type>::type shrinking) {
  return bloat(interval, -shrinking);
}

struct y_i_shrink2 : gtl_yes {};

// shrink the specified side of `this` Interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_shrink2, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     interval_type>::type &
shrink(interval_type& interval, direction_1d dir, typename interval_coordinate_type<interval_type>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}

struct y_i_encompass : gtl_yes {};

// Enlarge `this` Interval to encompass the specified Interval
template <typename interval_type, typename interval_type_2>
typename enable_if< typename gtl_and_3<
      y_i_encompass,
      typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
      typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
    bool>::type
encompass(interval_type& interval, const interval_type_2& b) {
  bool retval = !contains(interval, b, true);
  low(interval, (std::min)(low(interval), low(b)));
  high(interval, (std::max)(high(interval), high(b)));
  return retval;
}

struct y_i_encompass2 : gtl_yes {};

// Enlarge `this` Interval to encompass the specified Interval
template <typename interval_type>
typename enable_if< typename gtl_and<y_i_encompass2, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
		     bool>::type
encompass(interval_type& interval, typename interval_coordinate_type<interval_type>::type b) {
  bool retval = !contains(interval, b, true);
  low(interval, (std::min)(low(interval), b));
  high(interval, (std::max)(high(interval), b));
  return retval;
}

struct y_i_get_half : gtl_yes {};

// gets the half of the interval as an interval
template <typename interval_type>
typename enable_if<typename gtl_and<y_i_get_half, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type>::type, interval_type>::type
get_half(const interval_type& interval, direction_1d d1d) {
  typedef typename interval_coordinate_type<interval_type>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<interval_type>((d1d == LOW) ? get(interval, LOW) : c,
				  (d1d == LOW) ? c : get(interval, HIGH));
}

struct y_i_join_with : gtl_yes {};

// returns true if the 2 intervals exactly touch at one value, like in  l1 <= h1 == l2 <= h2
// sets the argument to the joined interval
template <typename interval_type, typename interval_type_2>
typename enable_if<
  typename gtl_and_3<y_i_join_with, typename is_mutable_interval_concept<typename geometry_concept<interval_type>::type>::type,
		    typename is_interval_concept<typename geometry_concept<interval_type_2>::type>::type>::type,
  bool>::type
join_with(interval_type& interval, const interval_type_2& b) {
  if(abuts(interval, b)) {
    encompass(interval, b);
    return true;
  }
  return false;
}
}  // polygon
}  // boost
#endif  // BOOST_POLYGON_INTERVAL_CONCEPT_HPP
