// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_PUGXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_PUGXML_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <boost/property_tree/detail/pugxml.hpp>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Ptree>
    void read_xml_node(pug::xml_node node, Ptree &pt, int flags)
    {
        typedef typename Ptree::key_type::value_type Ch;
        if (node.type() == pug::node_element || 
            node.type() == pug::node_document)
        {
            Ptree &tmp = pt.push_back(std::make_pair(node.name(), empty_ptree<Ptree>()))->second;
            for (pug::xml_node::attribute_iterator it = node.attributes_begin(); it != node.attributes_end(); ++it)
                tmp.put(xmlattr<Ch>() + Ch('.') + it->name(), it->value());
            for (pug::xml_node::child_iterator it = node.children_begin(); it != node.children_end(); ++it)
                read_xml_node(*it, tmp, flags);
        }
        else if (node.type() == pug::node_pcdata)
        {
            if (flags & no_concat_text)
                pt.push_back(std::make_pair(xmltext<Ch>(), Ptree(node.value())));
            else
                pt.data() += node.value();
        }
        else if (node.type() == pug::node_comment)
        {
            if (!(flags & no_comments))
                pt.push_back(std::make_pair(xmlcomment<Ch>(), Ptree(node.value())));
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {

        typedef typename Ptree::key_type::value_type Ch;
        
        // Load data into vector
        std::vector<Ch> data(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                             std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(xml_parser_error("read error", filename, 0));
        data.push_back(Ch('\0'));

        // Parse
        pug::xml_parser parser;
        if (parser.parse(&data.front()))
        {
            Ptree local;
            pug::xml_node doc = parser.document();
            for (pug::xml_node::child_iterator it = doc.children_begin(); it != doc.children_end(); ++it)
                read_xml_node(*it, local, flags);
            local.swap(pt);
        }
        else
            BOOST_PROPERTY_TREE_THROW(xml_parser_error("parse error", filename, 0));

    }

} } }

#endif
