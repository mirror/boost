// Boost.Polygon library voronoi.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI
#define BOOST_POLYGON_VORONOI

#include "polygon.hpp"
#include "voronoi_builder.hpp"
#include "voronoi_diagram.hpp"

// Public methods to compute Voronoi diagram.
// PC - container of input points (should supports forward iterator).
// SC - container of input segments (should supports forward iterator).
// output - Voronoi output data structure to hold Voronoi diagram.
// Segment class should provide low(), high() methods to access its endpoints.
// The assumption is made that input doesn't contain segments that intersect
// or points lying on the segments. Also coordinates of the points and of the
// endpoints of the segments should belong to the signed integer range
// [-2^31, 2^31-1]. To use wider input coordinate range use voronoi_builder
// structure with user provided coordinate type traits.
// Complexity - O(N*logN), memory usage - O(N),
// where N is the total number of points and segments.
namespace boost {
namespace polygon {

struct voronoi_insert_point_yes : gtl_yes {};

template <typename Point, typename VB>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_insert_point_yes,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
  void
>::type
insert(const Point &point, VB *vb) {
  vb->insert_point(x(point), y(point));
}

struct voronoi_insert_points_yes : gtl_yes {};

template <typename PointIterator, typename VB>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_insert_points_yes,
    typename is_point_concept<
      typename geometry_concept<
        typename std::iterator_traits<PointIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type
insert(PointIterator first, const PointIterator last, VB *vb) {
  for (PointIterator it = first; it != last; ++it) {
    insert(*it, vb);
  }
}

struct voronoi_insert_segment_yes : gtl_yes {};

template <typename Segment, typename VB>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_insert_segment_yes,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
  void
>::type
insert(const Segment &segment, VB *vb) {
  vb->insert_segment(x(low(segment)), y(low(segment)), x(high(segment)), y(high(segment)));
}

struct voronoi_insert_segments_yes : gtl_yes {};

template <typename SegmentIterator, typename VB>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_insert_segments_yes,
    typename is_segment_concept<
      typename geometry_concept<
        typename std::iterator_traits<SegmentIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type
insert(SegmentIterator first, SegmentIterator last, VB *vb) {
  for (SegmentIterator it = first; it != last; ++it) {
    insert(*it, vb);
  }
}

struct voronoi_construct_points_yes : gtl_yes {};

template <typename PointIterator, typename VD>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_construct_points_yes,
    typename is_point_concept<
      typename geometry_concept<
        typename std::iterator_traits<PointIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type
construct_voronoi(PointIterator first, PointIterator last, VD *vd) {
  default_voronoi_builder builder;
  insert(first, last, &builder);
  builder.construct(vd);
}

struct voronoi_construct_segments_yes : gtl_yes {};

template <typename SegmentIterator, typename VD>
static inline
typename enable_if<
  typename gtl_and<
    voronoi_construct_segments_yes,
    typename is_segment_concept<
      typename geometry_concept<
        typename std::iterator_traits<SegmentIterator>::value_type
      >::type
    >::type
  >::type,
  void
>::type
construct_voronoi(SegmentIterator first, SegmentIterator last, VD *vd) {
  default_voronoi_builder builder;
  insert(first, last, &builder);
  builder.construct(vd);
}

struct voronoi_construct_points_and_segments_yes : gtl_yes {};

template <typename PointIterator, typename SegmentIterator, typename VD>
static inline 
typename enable_if<
  typename gtl_and_3<
    voronoi_construct_points_and_segments_yes,
    typename gtl_if<
      typename is_point_concept<
        typename geometry_concept<
          typename std::iterator_traits<PointIterator>::value_type
        >::type
      >::type
    >::type,
    typename gtl_if<
      typename is_segment_concept<
        typename geometry_concept<
          typename std::iterator_traits<SegmentIterator>::value_type
        >::type
      >::type
    >::type
  >::type,
  void
>::type
construct_voronoi(PointIterator p_first, PointIterator p_last,
    SegmentIterator s_first, SegmentIterator s_last, VD *vd) {
  default_voronoi_builder builder;
  insert(p_first, p_last, &builder);
  insert(s_first, s_last, &builder);
  builder.construct(vd);
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI
