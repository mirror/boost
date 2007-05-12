// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

// This example shows what need to be done to customize data_type of ptree.
//
// It creates my_ptree type, which is a basic_ptree having boost::any as its data
// container (instead of std::string that standard ptree has).

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/any.hpp>
#include <list>
#include <string>
#include <iostream>

// Custom translator that works with boost::any instead of std::string
struct my_translator
{

    // Custom extractor - converts data from boost::any to T
    template<class Ptree, class T> 
    bool get_value(const Ptree &pt, T &value) const
    {
        value = boost::any_cast<T>(pt.data());
        return true;    // Success
    }

    // Custom inserter - converts data from T to boost::any
    template<class Ptree, class T> 
    bool put_value(Ptree &pt, const T &value) const
    {
        pt.data() = value;
        return true;
    }

};

int main()
{
    
    using namespace boost::property_tree;
    
    // Property_tree with boost::any as data type
    // Key comparison:  std::less<std::string>
    // Key type:        std::string
    // Path type:       path
    // Data type:       boost::any
    // Translator type: my_translator
    typedef basic_ptree<std::less<std::string>, std::string, path, boost::any, my_translator> my_ptree;
    my_ptree pt;

    // Put/get int value
    pt.put("int value", 3);
    int int_value = pt.get<int>("int value");
    std::cout << "Int value: " << int_value << "\n";

    // Put/get string value
    pt.put<std::string>("string value", "foo bar");
    std::string string_value = pt.get<std::string>("string value");
    std::cout << "String value: " << string_value << "\n";

    // Put/get list<int> value
    int list_data[] = { 1, 2, 3, 4, 5 };
    pt.put<std::list<int> >("list value", std::list<int>(list_data, list_data + sizeof(list_data) / sizeof(*list_data)));
    std::list<int> list_value = pt.get<std::list<int> >("list value");
    std::cout << "List value: ";
    for (std::list<int>::iterator it = list_value.begin(); it != list_value.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}
