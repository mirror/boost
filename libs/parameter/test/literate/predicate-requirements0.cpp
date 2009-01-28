
#line 903 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>

BOOST_PARAMETER_NAME((_graph, graphs) graph)
BOOST_PARAMETER_NAME((_visitor, graphs) visitor)
BOOST_PARAMETER_NAME((_root_vertex, graphs) root_vertex)
BOOST_PARAMETER_NAME((_index_map, graphs) index_map)
BOOST_PARAMETER_NAME((_color_map, graphs) color_map)

using boost::mpl::_;

namespace boost
{
  struct incidence_graph_tag {};
  struct vertex_list_graph_tag {};

  int vertex_index = 0;

  template <class T>
  struct graph_traits
  {
      typedef int traversal_category;
      typedef int vertex_descriptor;
  };

  template <class T>
  struct property_traits
  {
      typedef int value_type;
      typedef int key_type;
  };

  template <class T = int>
  struct dfs_visitor
  {};
}
#line 859 "../../../../libs/parameter/doc/index.rst"
BOOST_PARAMETER_FUNCTION(
    (void), depth_first_search, graphs

  , (required
      (graph
       , *(boost::mpl::and_<
               boost::is_convertible<
                   boost::graph_traits<_>::traversal_category
                 , boost::incidence_graph_tag
               >
             , boost::is_convertible<
                   boost::graph_traits<_>::traversal_category
                 , boost::vertex_list_graph_tag
               >
           >) ))

    (optional
      (visitor, *, boost::dfs_visitor<>()) // not checkable

      (root_vertex
        , (typename boost::graph_traits<graphs::graph::_>::vertex_descriptor)
        , *vertices(graph).first)

      (index_map
        , *(boost::mpl::and_<
              boost::is_integral<
                  boost::property_traits<_>::value_type
              >
            , boost::is_same<
                  typename boost::graph_traits<graphs::graph::_>::vertex_descriptor
                , boost::property_traits<_>::key_type
              >
          >)
        , get(boost::vertex_index,graph))

      (in_out(color_map)
        , *(boost::is_same<
              typename boost::graph_traits<graphs::graph::_>::vertex_descriptor
            , boost::property_traits<_>::key_type
          >)
       , default_color_map(num_vertices(graph), index_map) )
    )
)
#line 940 "../../../../libs/parameter/doc/index.rst"
{}

