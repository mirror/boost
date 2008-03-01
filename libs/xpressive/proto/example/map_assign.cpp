//[ MapAssign
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This is a port of map_list_assign from the Boost.Assign library.
// It has the advantage of being more efficient at runtime by not
// building any temporary container that requires dynamic allocation.

#include <map>
#include <string>
#include <iostream>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform.hpp>

using namespace boost;
using namespace proto;

struct map_list_of_tag
{};

// A simple callable function object that inserts a
// (key,value) pair into a map.
struct insert
  : callable
{
    template<typename Sig>
    struct result;
    
    template<typename This, typename Map, typename Key, typename Value>
    struct result<This(Map, Key, Value)>
      : add_reference<Map>
    {};
    
    template<typename Map, typename Key, typename Value>
    Map &operator()(Map &map, Key const &key, Value const &value) const
    {
        map.insert(typename Map::value_type(key, value));
        return map;
    }
};

// The grammmar for valid map-list expressions, and a
// transform that populates the map.
struct MapListOf
  : or_<
        when<
            function<terminal<map_list_of_tag>, terminal<_>, terminal<_> >
          , insert(_visitor, _arg(_arg1), _arg(_arg2))
        >
      , when<
            function<MapListOf, terminal<_>, terminal<_> >
          , insert(MapListOf(_arg0), _arg(_arg1), _arg(_arg2))
        >
    >
{};

template<typename Expr>
struct map_list_of_expr;

struct map_list_of_dom
  : domain<pod_generator<map_list_of_expr>, MapListOf>
{};

// An expression wrapper that provides a conversion to a
// map that uses the MapListOf 
template<typename Expr>
struct map_list_of_expr
{
    BOOST_PROTO_EXTENDS(Expr, map_list_of_expr, map_list_of_dom)
    BOOST_PROTO_EXTENDS_FUNCTION(Expr, map_list_of_expr, map_list_of_dom)
    
    template<typename Map>
    operator Map() const
    {
        Map map;
        return MapListOf()(*this, 0, map);
    }
};

map_list_of_expr<terminal<map_list_of_tag>::type> const map_list_of = {{{}}};

int main()
{
    // Initialize a map:
    std::map<std::string, int> op = 
        map_list_of
            ("<",1)
            ("<=",2)
            (">",3)
            (">=",4)
            ("=",5)
            ("<>",6)
        ;

    std::cout << "\"<\"  --> " << op["<"] << std::endl;
    std::cout << "\"<=\" --> " << op["<="] << std::endl;
    std::cout << "\">\"  --> " << op[">"] << std::endl;
    std::cout << "\">=\" --> " << op[">="] << std::endl;
    std::cout << "\"=\"  --> " << op["="] << std::endl;
    std::cout << "\"<>\" --> " << op["<>"] << std::endl;

    return 0;
}
//]
