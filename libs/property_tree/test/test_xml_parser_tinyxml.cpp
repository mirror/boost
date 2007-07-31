// ----------------------------------------------------------------------------
// Copyright (C) 2002-2005 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifdef _DEBUG
    #pragma comment( lib, "tinyxmld_STL.lib" )
#else
    #pragma comment( lib, "tinyxml_STL.lib" )
#endif

#define BOOST_PROPERTY_TREE_XML_PARSER_TINYXML
#include "test_xml_parser_common.hpp"

int test_main(int argc, char *argv[])
{
    using namespace boost::property_tree;
    test_xml_parser<ptree>();
    test_xml_parser<iptree>();
    return 0;
}
