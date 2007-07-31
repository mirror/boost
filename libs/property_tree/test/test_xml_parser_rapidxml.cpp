// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#include "test_xml_parser_common.hpp"

int test_main(int argc, char *argv[])
{
    using namespace boost::property_tree;
    test_xml_parser<ptree>();
    test_xml_parser<iptree>();
#ifndef BOOST_NO_CWCHAR
    test_xml_parser<wptree>();
    test_xml_parser<wiptree>();
#endif
    return 0;
}
