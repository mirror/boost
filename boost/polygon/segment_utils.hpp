/*
  Copyright 2012 Lucanus Simonson
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_SEGMENT_UTILS_HPP
#define BOOST_POLYGON_SEGMENT_UTILS_HPP

namespace boost { namespace polygon{

template <typename line_segment_type, typename line_segment_iterator_type>
void intersect_segments(std::vector<std::pair<std::size_t, line_segment_type> >& result, 
                        line_segment_iterator_type begin_segs, line_segment_iterator_type end_segs){
  typedef typename segment_traits<line_segment_type>::coordinate_type Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id_in = 0;
  half_edges.reserve(std::distance(begin_segs, end_segs));
  for(; begin_segs != end_segs; ++begin_segs) {
    Point l, h;
    assign(l, low(*begin_segs));
    assign(h, high(*begin_segs));
    half_edges.push_back(std::make_pair(half_edge(l, h), id_in++));
  }
  half_edges_out.reserve(half_edges.size());
  //apparently no need to pre-sort data when calling validate_scan
  if(half_edges.size() != 0)
    line_intersection<Unit>::validate_scan(half_edges_out, half_edges.begin(), half_edges.end());
  result.reserve(result.size() + half_edges_out.size());
  for(std::size_t i = 0; i < half_edges_out.size(); ++i) {
    std::size_t id = (std::size_t)(half_edges_out[i].second);
    Point l = half_edges_out[i].first.first;
    Point h = half_edges_out[i].first.second;
    result.push_back(std::make_pair(id, construct<line_segment_type>(l, h)));
  }
}

template <typename segment_container_type>
void intersect_segments(segment_container_type& segments) {
  typedef typename segment_container_type::value_type line_segment_type;
  typedef typename segment_traits<line_segment_type>::coordinate_type Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id_in = 0;
  half_edges.reserve(std::distance(segments.begin(), segments.end()));
  for(typename segment_container_type::iterator itr = segments.begin(); 
      itr != segments.end(); ++itr) {
    Point l, h;
    assign(l, low(*itr));
    assign(h, high(*itr));
    half_edges.push_back(std::make_pair(half_edge(l, h), id_in++));
  }
  half_edges_out.reserve(half_edges.size());
  //apparently no need to pre-sort data when calling validate_scan
  if(half_edges.size() != 0)
    line_intersection<Unit>::validate_scan(half_edges_out, half_edges.begin(), half_edges.end());
  segments.clear();
  for(std::size_t i = 0; i < half_edges_out.size(); ++i) {
    std::size_t id = (std::size_t)(half_edges_out[i].second);
    Point l = half_edges_out[i].first.first;
    Point h = half_edges_out[i].first.second;
    segments.push_back(construct<line_segment_type>(l, h));
  }
}

template <typename cT, typename line_segment_iterator_type>
std::size_t segment_intersections(cT& output_points, 
                                  line_segment_iterator_type begin_segs,
                                  line_segment_iterator_type end_segs) {
  typedef typename segment_traits<
    typename std::iterator_traits<line_segment_iterator_type>::value_type
    >::coordinate_type Unit;
  typedef typename scanline_base<Unit>::Point Point;
  typedef typename scanline_base<Unit>::half_edge half_edge;
  typedef int segment_id;
  std::vector<std::pair<half_edge, segment_id> > half_edges;
  std::vector<std::pair<half_edge, segment_id> > half_edges_out;
  segment_id id = 0;
  std::size_t range_size = std::distance(begin_segs, end_segs);
  half_edges.reserve(range_size);
  std::vector<typename std::iterator_traits<line_segment_iterator_type>::value_type> data_;
  data_.insert(data_.end(), begin_segs, end_segs);
  for(typename std::vector<typename std::iterator_traits<
        line_segment_iterator_type>::value_type>::iterator itr = data_.begin(); 
      itr != data_.end(); ++itr) {
    Point l = (*itr).low();
    Point h = (*itr).high();
    half_edges.push_back(std::make_pair(half_edge(l, h), id++));
  }
  half_edges_out.reserve(half_edges.size());
  std::vector<std::set<Point> > intersection_points(half_edges.size(), std::set<Point>());
  line_intersection<Unit>::validate_scan_divide_and_conquer(intersection_points, half_edges.begin(), half_edges.end());
  std::vector<Point> tmp_points;
  for(std::size_t i = 0; i < intersection_points.size(); ++i) {
    typename std::set<Point>::iterator itr2 = intersection_points[i].begin();
    for(; itr2 != intersection_points[i].end(); ++itr2)
      if(data_[i].low() != *itr2 && data_[i].high() != *itr2)
        tmp_points.push_back(*itr2);
  }
  polygon_sort(tmp_points.begin(), tmp_points.end());
  typename std::vector<Point>::iterator new_end = std::unique(tmp_points.begin(), tmp_points.end());
  output_points.insert(output_points.end(), tmp_points.begin(), new_end);
  return std::distance(tmp_points.begin(), new_end);
}

template <typename rectangle_type, typename line_segment_iterator_type>
bool segments_extents(rectangle_type& rect, 
                      line_segment_iterator_type begin_segs,
                      line_segment_iterator_type end_segs) {
  bool first_iteration = true;
  for( ;begin_segs != end_segs; ++begin_segs) {
    rectangle_type edge_box;
    set_points(edge_box, (*begin_segs).low(), (*begin_segs).high());
    if(first_iteration)
      rect = edge_box;
    else
      encompass(rect, edge_box);
    first_iteration = false;
  }
  return !first_iteration;
}

}}

#endif
