/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_DIRECTED_LINE_SEGMENT_SET_DATA_HPP
#define BOOST_POLYGON_DIRECTED_LINE_SEGMENT_SET_DATA_HPP

namespace boost { namespace polygon{
  template <typename T>
  class directed_line_segment_set_data {
  public:
    typedef T coordinate_type;
    typedef point_data<T> point_type;
    typedef directed_line_segment_data<T> directed_line_segment_type;
    typedef std::vector<directed_line_segment_type> value_type;
    typedef typename std::vector<directed_line_segment_type>::const_iterator iterator_type;

    inline directed_line_segment_set_data() : data_(), dirty_(false), unsorted_(false) {}
    inline directed_line_segment_set_data(const directed_line_segment_set_data& that): 
      data_(that.data_), dirty_(that.dirty_), unsorted_(that.unsorted_) {}
    inline directed_line_segment_set_data& operator=(const directed_line_segment_set_data& that) {
      if(this == &that) return *this;
      data_ = that.data_;
      dirty_ = that.dirty_;
      unsorted_ = that.unsorted_;
      return *this;
    }
    template <typename T2>
    inline directed_line_segment_set_data& operator=(const T2& rvalue) {
      data_.clear();
      bool unsorted = !sorted(rvalue);
      bool dirty = !dirty(rvalue);
      insert(begin(rvalue), end(rvalue));
      unsorted_ = unsorted;
      dirty_ = dirty;
      return *this;
    }

    inline bool operator==(const directed_line_segment_set_data& that) const {
      clean();
      that.clean();
      sort();
      that.sort();
      return data_ == that.data_;
    } 
    inline bool operator!=(const directed_line_segment_set_data& that) const {
      return !(*this == that);
    }

    template <typename iT>
    inline void insert(iT begin_segments, iT end_segments) {
      data_.clear();
      for(; begin_segments != end_segments; ++begin_segments) {
        insert(*begin_segments);
      }
    }

    template <typename ST>
    inline void insert(ST segment) {
      unsorted_ = true;
      dirty_ = true;
      directed_line_segment_type tmp_seg;
      assign(tmp_seg, segment);
      data_.push_back(tmp_seg);
    }

    inline void clear() { data_.clear(); unsorted_ = false; dirty_ = false; }

    inline iterator_type begin() const {
      return data_.begin();
    }

    inline iterator_type end() const {
      return data_.end();
    }

    const value_type& value() const {
      return data_;
    }

    template <typename output_container>
    inline void get(output_container& output) const {
      for(std::size_t i = 0; i < size(); ++i) {
        output.push_back(typename output_container::value_type());
        assign(output.back(), data_[i]);
      }
    }

    inline bool empty() const { return data_.empty(); }

    inline std::size_t size() const { clean(); return data_.size(); }

    inline std::size_t capacity() const { return data_.capacity(); }

    inline void reserve(std::size_t size) { return data_.reserve(size); }

    inline bool sorted() const { return !unsorted_; }

    inline bool dirty() const { return dirty_; }

    void clean() const {
      typedef T Unit;
      typedef typename scanline_base<Unit>::Point Point;
      typedef typename scanline_base<Unit>::half_edge half_edge;
      typedef int segment_id;
      std::vector<std::pair<half_edge, segment_id> > half_edges;
      std::vector<std::pair<half_edge, segment_id> > half_edges_out;
      segment_id id = 0;
      half_edges.reserve(data_.size());
      for(iterator_type itr = begin(); itr != end(); ++itr) {
        Point l = (*itr).low();
        Point h = (*itr).high();
        half_edges.push_back(std::make_pair(half_edge(l, h), id++));
      }
      half_edges_out.reserve(half_edges.size());
      //apparently no need to pre-sort data when calling validate_scan
      line_intersection<Unit>::validate_scan(half_edges_out, half_edges.begin(), half_edges.end());
      value_type result;
      result.reserve(half_edges_out.size());
      for(std::size_t i = 0; i < half_edges_out.size(); ++i) {
        id = half_edges_out[i].second;
        Point l = half_edges_out[i].first.first;
        Point h = half_edges_out[i].first.second;
        directed_line_segment_type orig_seg = data_[id];
        if(orig_seg.high() < orig_seg.low())
          std::swap(l, h);
        result.push_back(directed_line_segment_type(l, h));
      }
      std::swap(result, data_);
      dirty_ = false;
      unsorted_ = true;
    };

    void sort() const{
      if(unsorted_) {
        polygon_sort(data_.begin(), data_.end());
        unsorted_ = false;
      }
    }

    template <typename input_iterator_type>
    void set(input_iterator_type input_begin, input_iterator_type input_end) {
      clear();
      reserve(std::distance(input_begin,input_end));
      insert(input_begin, input_end);
      dirty_ = true;
      unsorted_ = true;
    }

    void set(const value_type& value) {
      data_ = value; 
      dirty_ = true;
      unsorted_ = true;
    }

    template <typename rectangle_type>
    bool extents(rectangle_type& rect) {
      if(empty()) return false;
      bool first_iteration = true;
      for(iterator_type itr = begin();
          itr != end(); ++itr) {
        rectangle_type edge_box;
        set_points(edge_box, (*itr).low(), (*itr).high());
        if(first_iteration)
          rect = edge_box;
        else
          encompass(rect, edge_box);
        first_iteration = false;
      }
      return true;
    }

    template <typename transform_type>
    inline directed_line_segment_set_data& 
    transform(const transform_type& tr) {
      for(typename value_type::iterator itr = data_.begin(); itr != data_.end(); ++itr) {
        point_type l = (*itr).low();
        point_type h = (*itr).high();
        ::boost::polygon::transform(l, tr);
        ::boost::polygon::transform(h, tr);
        (*itr).low(l);
        (*itr).high(h);
      }
      unsorted_ = true;
      return *this;
    }

    inline directed_line_segment_set_data& 
    scale_up(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      for(typename value_type::iterator itr = data_.begin(); itr != data_.end(); ++itr) {
        point_type l = (*itr).low();
        point_type h = (*itr).high();
        ::boost::polygon::scale_up(l, factor);
        ::boost::polygon::scale_up(h, factor);
        (*itr).low(l);
        (*itr).high(h);
      }
      return *this;
    }
    
    inline directed_line_segment_set_data& 
    scale_down(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      for(typename value_type::iterator itr = data_.begin(); itr != data_.end(); ++itr) {
        point_type l = (*itr).low();
        point_type h = (*itr).high();
        ::boost::polygon::scale_down(l, factor);
        ::boost::polygon::scale_down(h, factor);
        (*itr).low(l);
        (*itr).high(h);
      }
      return *this;
    }
    
    template <typename scaling_type>
    inline directed_line_segment_set_data& scale(const scaling_type& scaling) {
      for(typename value_type::iterator itr = data_.begin(); itr != data_.end(); ++itr) {
        point_type l = (*itr).low();
        point_type h = (*itr).high();
        ::boost::polygon::scale(l, scaling);
        ::boost::polygon::scale(h, scaling);
        (*itr).low(l);
        (*itr).high(h);
      }
      return *this;
    }

    template <typename cT>
    std::size_t get_intersection_points(cT& output_points) const {
      typedef T Unit;
      typedef typename scanline_base<Unit>::Point Point;
      typedef typename scanline_base<Unit>::half_edge half_edge;
      typedef int segment_id;
      std::vector<std::pair<half_edge, segment_id> > half_edges;
      std::vector<std::pair<half_edge, segment_id> > half_edges_out;
      segment_id id = 0;
      half_edges.reserve(data_.size());
      for(iterator_type itr = begin(); itr != end(); ++itr) {
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
    };


private:
    mutable value_type data_;
    mutable bool dirty_;
    mutable bool unsorted_;
};

}
}
#endif
