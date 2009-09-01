// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef TEST_XML_PARSER_COMMON_HPP_INCLUDED
#define TEST_XML_PARSER_COMMON_HPP_INCLUDED

#include "test_utils.hpp"
#include <boost/property_tree/xml_parser.hpp>
#include "xml_parser_test_data.hpp"

struct ReadFunc
{
    template<class Ptree>
    void operator()(const std::string &filename, Ptree &pt) const
    {
        boost::property_tree::read_xml(filename, pt);
    }
};

struct WriteFunc
{
    template<class Ptree>
    void operator()(const std::string &filename, const Ptree &pt) const
    {
        boost::property_tree::write_xml(filename, pt);
    }
};

template <typename Ch> int umlautsize();
template <> inline int umlautsize<char>() { return 2; }
template <> inline int umlautsize<wchar_t>() { return 1; }

template<class Ptree>
void test_xml_parser()
{

    using namespace boost::property_tree;

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_1, NULL, 
        "testok1.xml", NULL, "testok1out.xml", 2, 0, 5
    );
    
    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_2, NULL, 
        "testok2.xml", NULL, "testok2out.xml", 5, 15, 7
    );

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_3, NULL, 
        "testok3.xml", NULL, "testok3out.xml", 787, 31376, 3831
    );

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_4, NULL, 
        "testok4.xml", NULL, "testok4out.xml", 5, 2, 20
    );

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_5, NULL, 
        "testok5.xml", NULL, "testok5out.xml",
        2, umlautsize<typename Ptree::data_type::value_type>(), 3
    );

    generic_parser_test_error<Ptree, ReadFunc, WriteFunc, xml_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_1, NULL,
        "testerr1.xml", NULL, "testerr1out.xml", 1
    );

    generic_parser_test_error<Ptree, ReadFunc, WriteFunc, xml_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_2, NULL,
        "testerr2.xml", NULL, "testerr2out.xml", 2
    );

}

#endif
