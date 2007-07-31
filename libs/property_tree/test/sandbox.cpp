#define _CRT_SECURE_NO_DEPRECATE
//#define BOOST_PROPERTY_TREE_XML_PARSER_PUGXML
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <iostream>

int main()
{
    using namespace boost::property_tree;
    ptree pt;
    read_xml("simple_all.xml", pt);
    write_info(std::cout, pt);
}
