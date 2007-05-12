// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_TINYXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_TINYXML_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>

#include <tinyxml.h>

namespace boost { namespace property_tree { namespace xml_parser
{

#ifdef TIXML_USE_STL
    
    template<class Ptree>
    void read_xml_node(TiXmlNode *node, Ptree &pt, int flags)
    {

        typedef typename Ptree::key_type::value_type Ch;

        if (TiXmlElement *elem = node->ToElement())
        {
            Ptree &tmp = pt.push_back(std::make_pair(elem->Value(), Ptree()))->second;
            for (TiXmlAttribute *attr = elem->FirstAttribute(); attr; attr = attr->Next())
                tmp.put(xmlattr<Ch>() + Ch('.') + attr->Name(), attr->Value());
            for (TiXmlNode *child = node->FirstChild(); child; child = child->NextSibling())
                read_xml_node(child, tmp, flags);
        }
        else if (TiXmlText *text = node->ToText())
        {
            if (flags & no_concat_text)
                pt.push_back(std::make_pair(xmltext<Ch>(), Ptree(text->Value())));
            else
                pt.data() += text->Value();
        }
        else if (TiXmlComment *comment = node->ToComment())
        {
            if (!(flags & no_comments))
                pt.push_back(std::make_pair(xmlcomment<Ch>(), Ptree(comment->Value())));
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {

        // Create and load document from stream
        TiXmlDocument doc;
        stream >> doc;
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(xml_parser_error("read error", filename, 0));
        if (doc.Error())
            BOOST_PROPERTY_TREE_THROW(xml_parser_error(doc.ErrorDesc(), filename, doc.ErrorRow()));

        // Create ptree from nodes
        Ptree local;
        for (TiXmlNode *child = doc.FirstChild(); child; child = child->NextSibling())
            read_xml_node(child, local, flags);

        // Swap local and result ptrees
        pt.swap(local);

    }

#else

    template<class Ptree>
    void read_xml_node(TiXmlNode *node, Ptree &pt, int flags)
    {

        typedef typename Ptree::key_type::value_type Ch;

        if (TiXmlElement *elem = node->ToElement())
        {
            Ptree &tmp = pt.push_back(std::make_pair(elem->Value(), Ptree()))->second;
            for (TiXmlAttribute *attr = elem->FirstAttribute(); attr; attr = attr->Next())
                tmp.put(xmlattr<Ch>() + Ch('.') + attr->Name(), attr->Value());
            for (TiXmlNode *child = node->FirstChild(); child; child = child->NextSibling())
                read_xml_node(child, tmp, flags);
        }
        else if (TiXmlText *text = node->ToText())
        {
            if (flags & no_concat_text)
                pt.push_back(std::make_pair(xmltext<Ch>(), Ptree(text->Value())));
            else
                pt.data() += text->Value();
        }
        else if (TiXmlComment *comment = node->ToComment())
        {
            if (!(flags & no_comments))
                pt.push_back(std::make_pair(xmlcomment<Ch>(), Ptree(comment->Value())));
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {

        // Load data into vector
        typedef typename Ptree::key_type::value_type Ch;
        std::vector<Ch> data(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                             std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(xml_parser_error("read error", filename, 0));
        data.push_back(Ch('\0'));
        
        // Create and load document
        TiXmlDocument doc;
        doc.Parse(&data.front());
        if (doc.Error())
            BOOST_PROPERTY_TREE_THROW(xml_parser_error(doc.ErrorDesc(), filename, doc.ErrorRow()));

        // Create ptree from nodes
        Ptree local;
        for (TiXmlNode *child = doc.FirstChild(); child; child = child->NextSibling())
            read_xml_node(child, local, flags);

        // Swap local and result ptrees
        pt.swap(local);

    }

#endif

} } }

#endif
