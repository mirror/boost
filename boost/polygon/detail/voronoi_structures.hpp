// Boost.Polygon library detail/voronoi_structures.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES
#define BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES

#include <list>
#include <queue>
#include <vector>

namespace boost {
namespace polygon {
namespace detail {
// Event queue data structure, holds circle events.
// During algorithm run, some of the circle events disappear (become
// inactive). Priority queue data structure doesn't support
// iterators (there is no direct ability to modify its elements).
// Instead list is used to store all the circle events and priority queue
// of the iterators to the list elements is used to keep the correct circle
// events ordering.
template <typename T, typename Predicate>
class ordered_queue {
public:
  ordered_queue() {}

  bool empty() const {
    return c_.empty();
  }

  const T &top() const {
    return *c_.top();
  }

  void pop() {
    list_iterator_type it = c_.top();
    c_.pop();
    c_list_.erase(it);
  }

  T &push(const T &e) {
    c_list_.push_front(e);
    c_.push(c_list_.begin());
    return c_list_.front();
  }

  void clear() {
    while (!c_.empty())
        c_.pop();
    c_list_.clear();
  }

private:
  typedef typename std::list<T>::iterator list_iterator_type;

  struct comparison {
    bool operator() (const list_iterator_type &it1,
                     const list_iterator_type &it2) const {
      return cmp_(*it1, *it2);
    }
    Predicate cmp_;
  };

  std::priority_queue< list_iterator_type,
                       std::vector<list_iterator_type>,
                       comparison > c_;
  std::list<T> c_list_;

  //Disallow copy constructor and operator=
  ordered_queue(const ordered_queue&);
  void operator=(const ordered_queue&);
};

// Represents a bisector node made by two arcs that correspond to the left
// and right sites. Arc is defined as a curve with points equidistant from
// the site and from the sweepline. If the site is a point then arc is
// a parabola, otherwise it's a line segment. A segment site event will
// produce different bisectors based on its direction.
// In general case two sites will create two opposite bisectors. That's
// why the order of the sites is important to define the unique bisector.
// The one site is considered to be newer than the other one if it was
// processed by the algorithm later (has greater index).
template <typename Site>
class beach_line_node_key {
public:
  typedef Site site_type;

  // Constructs degenerate bisector, used to search an arc that is above
  // the given site. The input to the constructor is the new site point.
  explicit beach_line_node_key(const site_type &new_site) :
      left_site_(new_site),
      right_site_(new_site) {}

  // Constructs a new bisector. The input to the constructor is the two
  // sites that create the bisector. The order of sites is important.
  beach_line_node_key(const site_type &left_site,
                      const site_type &right_site) :
      left_site_(left_site),
      right_site_(right_site) {}

  const site_type &left_site() const {
    return left_site_;
  }

  site_type &left_site() {
    return left_site_;
  }

  beach_line_node_key& left_site(const site_type &site) {
    left_site_ = site;
    return *this;
  }

  const site_type &right_site() const {
    return right_site_;
  }

  site_type &right_site() {
    return right_site_;
  }

  beach_line_node_key& right_site(const site_type &site) {
    right_site_ = site;
    return *this;
  }

private:
  site_type left_site_;
  site_type right_site_;
};

// Represents edge data structure from the Voronoi output, that is
// associated as a value with beach line bisector in the beach
// line. Contains pointer to the circle event in the circle event
// queue if the edge corresponds to the right bisector of the circle event.
template <typename Edge, typename Circle>
class beach_line_node_data {
public:
  explicit beach_line_node_data(Edge* new_edge) :
      circle_event_(NULL),
      edge_(new_edge) {}

  Circle* circle_event() const {
    return circle_event_;
  }

  beach_line_node_data& circle_event(Circle* circle_event) {
    circle_event_ = circle_event;
    return *this;
  }

  Edge* edge() const {
    return edge_;
  }

  beach_line_node_data& edge(Edge* new_edge) {
    edge_ = new_edge;
    return *this;
  }

private:
  Circle* circle_event_;
  Edge* edge_;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES
