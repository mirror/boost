// Boost.Polygon library voronoi_structures_test.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE voronoi_structures_test

#include <boost/test/test_case_template.hpp>
#include <boost/polygon/detail/voronoi_structures.hpp>
using namespace boost::polygon::detail;

typedef ordered_queue<int, std::greater<int> > ordered_queue_type;
typedef beach_line_node_key<int> node_key_type;
typedef beach_line_node_data<int, int> node_data_type;

BOOST_AUTO_TEST_CASE(ordered_queue_test) {
  ordered_queue_type q;
  BOOST_CHECK(q.empty());
  std::vector<int*> vi;
  for (int i = 0; i < 20; ++i)
    vi.push_back(&q.push(i));
  for (int i = 0; i < 20; ++i)
    *vi[i] <<= 1;
  BOOST_CHECK(!q.empty());
  for (int i = 0; i < 20; ++i, q.pop())
    BOOST_CHECK_EQUAL(q.top(), i << 1);
  BOOST_CHECK(q.empty());
}

BOOST_AUTO_TEST_CASE(beach_line_node_key_test) {
  node_key_type key(1);
  BOOST_CHECK_EQUAL(key.left_site(), 1);
  BOOST_CHECK_EQUAL(key.right_site(), 1);
  key.left_site(2);
  BOOST_CHECK_EQUAL(key.left_site(), 2);
  BOOST_CHECK_EQUAL(key.right_site(), 1);
  key.right_site(3);
  BOOST_CHECK_EQUAL(key.left_site(), 2);
  BOOST_CHECK_EQUAL(key.right_site(), 3);
}

BOOST_AUTO_TEST_CASE(beach_line_node_data_test) {
  node_data_type node_data(NULL);
  BOOST_CHECK(node_data.edge() == NULL);
  BOOST_CHECK(node_data.circle_event() == NULL);
  int data = 4;
  node_data.circle_event(&data);
  BOOST_CHECK(node_data.edge() == NULL);
  BOOST_CHECK(node_data.circle_event() == &data);
  node_data.edge(&data);
  BOOST_CHECK(node_data.edge() == &data);
  BOOST_CHECK(node_data.circle_event() == &data);
}
