// Boost.Polygon library voronoi_test_helper.hpp file 

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef VORONOI_TEST_HELPER
#define VORONOI_TEST_HELPER

#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <vector>

#include <boost/polygon/polygon.hpp>
using namespace boost::polygon;

namespace voronoi_test_helper {

enum kOrientation {
  RIGHT = -1,
  COLLINEAR = 0,
  LEFT = 1
};

template <typename Point2D>
kOrientation get_orientation(const Point2D &point1,
                             const Point2D &point2,
                             const Point2D &point3) {
  typename Point2D::coordinate_type a = (point2.x() - point1.x()) * (point3.y() - point2.y());
  typename Point2D::coordinate_type b = (point2.y() - point1.y()) * (point3.x() - point2.x());
  if (a == b)
    return COLLINEAR;
  return (a < b) ? RIGHT : LEFT;
}

template <typename Output>
bool verify_half_edge_orientation(const Output &output) {
  typedef typename Output::point_type point_type;
  typename Output::const_edge_iterator edge_it;
  for (edge_it = output.edges().begin(); 
       edge_it != output.edges().end(); edge_it++) {
    if (edge_it->is_finite()) {
      const point_type &site_point = edge_it->cell()->point0();
      const point_type &start_point = edge_it->vertex0()->vertex();
      const point_type &end_point = edge_it->vertex1()->vertex();
      if (get_orientation(start_point, end_point, site_point) != LEFT)
        return false;
    }
  }
  return true;
}

template <typename Output>
bool verify_cell_convexity(const Output &output) {
  typedef typename Output::point_type point_type;
  typename Output::const_cell_iterator cell_it;
  for (cell_it = output.cells().begin();
       cell_it != output.cells().end(); cell_it++) {
    const typename Output::edge_type *edge = cell_it->incident_edge();
    if (edge)
      do {
        if (edge->next()->prev() != edge)
          return false;
        if (edge->cell() != &(*cell_it))
          return false;
        if (edge->vertex0() != NULL &&
            edge->vertex1() != NULL &&
            edge->vertex1() == edge->next()->vertex0() &&
            edge->next()->vertex1() != NULL) {
          const point_type &vertex1 = edge->vertex0()->vertex();
          const point_type &vertex2 = edge->vertex1()->vertex();
          const point_type &vertex3 = edge->next()->vertex1()->vertex();
          if (get_orientation(vertex1, vertex2, vertex3) != LEFT)
            return false;
        }
        edge = edge->next();
      } while(edge != cell_it->incident_edge());
  }
  return true;
}

template <typename Output>
bool verify_incident_edges_ccw_order(const Output &output) {
  typedef typename Output::point_type point_type;
  typedef typename Output::edge_type voronoi_edge_type;
  typename Output::const_vertex_iterator vertex_it;
  for (vertex_it = output.vertices().begin();
     vertex_it != output.vertices().end(); vertex_it++) {
    if (vertex_it->is_degenerate())
      continue;
    const voronoi_edge_type *edge = vertex_it->incident_edge();
    do {
      const voronoi_edge_type *edge_next1 = edge->rot_next();
      const voronoi_edge_type *edge_next2 = edge_next1->rot_next();
      const point_type &site1 = edge->cell()->point0();
      const point_type &site2 = edge_next1->cell()->point0();
      const point_type &site3 = edge_next2->cell()->point0();

      if (get_orientation(site1, site2, site3) != LEFT)
        return false;

      edge = edge->rot_next();
    } while (edge != vertex_it->incident_edge());
  }
  return true;
}

template <typename P>
struct cmp {
  bool operator()(const P& p1, const P& p2) const {
    if (p1.x() != p2.x()) 
      return p1.x() < p2.x();
    return p1.y() < p2.y();
  }
};

template <typename Output>
bool verfiy_no_line_edge_intersections(const Output &output) {
  // Create map from edges with first point less than the second one.
  // Key is the first point of the edge, value is a vector of second points
  // with the same first point.
  typedef typename Output::point_type point_type;
  cmp<point_type> comparator;
  std::map< point_type, std::vector<point_type>, cmp<point_type> > edge_map;
  typename Output::const_edge_iterator edge_it;
  for (edge_it = output.edges().begin();
       edge_it != output.edges().end(); edge_it++) {
    if (edge_it->is_finite()) {
        const point_type &vertex0 = edge_it->vertex0()->vertex();
        const point_type &vertex1 = edge_it->vertex1()->vertex();
      if (comparator(vertex0, vertex1))
        edge_map[vertex0].push_back(vertex1);
    }
  }
  return !intersection_check(edge_map);
}

template <typename Point2D>
bool intersection_check(const std::map< Point2D, std::vector<Point2D>, cmp<Point2D> > &edge_map) {
  // Iterate over map of edges and check if there are any intersections.
  // All the edges are stored by the low x value. That's why we iterate
  // left to right checking for intersections between all pairs of edges
  // that overlap in the x dimension.
  // Complexity. Approximately N*sqrt(N). Worst case N^2.
  typedef Point2D point_type;
  typedef typename point_type::coordinate_type coordinate_type;
  typedef typename std::map< point_type, std::vector<point_type>, cmp<Point2D> >::const_iterator
      edge_map_iterator;
  typedef typename std::vector<point_type>::size_type size_type;
  edge_map_iterator edge_map_it1, edge_map_it2, edge_map_it_bound;
  for (edge_map_it1 = edge_map.begin();
       edge_map_it1 != edge_map.end(); edge_map_it1++) {
    const point_type &point1 = edge_map_it1->first;
    for (size_type i = 0; i < edge_map_it1->second.size(); i++) {
      const point_type &point2 = edge_map_it1->second[i];
      coordinate_type min_y1 = (std::min)(point1.y(), point2.y());
      coordinate_type max_y1 = (std::max)(point1.y(), point2.y());

      // Find the first edge with greater or equal first point.
      edge_map_it_bound = edge_map.lower_bound(point2);

      edge_map_it2 = edge_map_it1;
      edge_map_it2++;
      for (; edge_map_it2 != edge_map_it_bound; edge_map_it2++) {
        const point_type &point3 = edge_map_it2->first;
        for (size_type j = 0; j < edge_map_it2->second.size(); j++) {
          const point_type &point4 = edge_map_it2->second[j];
          coordinate_type min_y2 = (std::min)(point3.y(), point4.y());
          coordinate_type max_y2 = (std::max)(point3.y(), point4.y());
          
          // In most cases it is enought to make 
          // simple intersection check in the y dimension.
          if (!(max_y1 > min_y2 && max_y2 > min_y1))
            continue;

          // Intersection check.
          if (get_orientation(point1, point2, point3) *
              get_orientation(point1, point2, point4) == RIGHT &&
              get_orientation(point3, point4, point1) *
              get_orientation(point3, point4, point2) == RIGHT)
            return true;
        }
      }
    }
  }
  return false;
}

enum kVerification {
  HALF_EDGE_ORIENTATION = 1,
  CELL_CONVEXITY = 2,
  INCIDENT_EDGES_CCW_ORDER = 4,
  NO_HALF_EDGE_INTERSECTIONS = 8,
  FAST_VERIFICATION = 7,
  COMPLETE_VERIFICATION = 15
};

template <typename Output>
bool verify_output(const Output &output, kVerification mask) {
  bool result = true;
  if (mask & HALF_EDGE_ORIENTATION)
    result &= verify_half_edge_orientation(output);
  if (mask & CELL_CONVEXITY)
    result &= verify_cell_convexity(output);
  if (mask & INCIDENT_EDGES_CCW_ORDER)
    result &= verify_incident_edges_ccw_order(output);
  if (mask & NO_HALF_EDGE_INTERSECTIONS)
    result &= verfiy_no_line_edge_intersections(output);
  return result;
}

template <typename PointIterator>
void save_points(PointIterator first, PointIterator last, const char *file_name) {
  std::ofstream ofs(file_name);
  ofs << std::distance(first, last) << std::endl;
  for (PointIterator it = first; it != last; ++it) {
    ofs << it->x() << " " << it->y() << std::endl;
  }
  ofs.close();
}

template <typename SegmentIterator>
void save_segments(SegmentIterator first, SegmentIterator last, const char *file_name) {
  std::ofstream ofs(file_name);
  ofs << std::distance(first, last) << std::endl;
  for (SegmentIterator it = first; it != last; ++it) {
    ofs << it->low().x() << " " << it->low().y() << " ";
    ofs << it->high().x() << " " << it->high().y() << std::endl;
  }
  ofs.close();
}

template <typename T>
void clean_segment_set(std::vector< segment_data<T> > &data) {
  typedef T Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id = 0;
  half_edges.reserve(data.size());
  for (typename std::vector< segment_data<T> >::iterator it = data.begin(); it != data.end(); ++it) {
    Point l = it->low();
    Point h = it->high();
    half_edges.push_back(std::make_pair(half_edge(l, h), id++));
  }
  half_edges_out.reserve(half_edges.size());
  //apparently no need to pre-sort data when calling validate_scan
  line_intersection<Unit>::validate_scan(half_edges_out, half_edges.begin(), half_edges.end());
  std::vector< segment_data<T> > result;
  result.reserve(half_edges_out.size());
  for (std::size_t i = 0; i < half_edges_out.size(); ++i) {
    id = half_edges_out[i].second;
    Point l = half_edges_out[i].first.first;
    Point h = half_edges_out[i].first.second;
    segment_data<T> orig_seg = data[id];
    if (orig_seg.high() < orig_seg.low())
      std::swap(l, h);
    result.push_back(segment_data<T>(l, h));
  }
  std::swap(result, data);
}

} // voronoi_test_helper

#endif
