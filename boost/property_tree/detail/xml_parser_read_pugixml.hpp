// ----------------------------------------------------------------------------
// Copyright (C) 2006-2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

// PugiXML-based parser. To enable it define
// BOOST_PROPERTY_TREE_XML_PARSER_PUGIXML before including xml_parser.hpp file.
// 
// PugiXML library has to be obtained separately.
// Check it out at http://code.google.com/p/pugixml/
//
// This module is derived from an example shipped as part of
// the PugiXML documentation. This example contains the following notice:
// Copyright (C) 2006, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)

#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_PUGIXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_PUGIXML_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>

#include <pugixml.hpp>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Ptree>
    void read_xml_node( pugi::xml_node node, Ptree &pt, int flags)
    {
        typedef typename Ptree::key_type::value_type Ch;

        switch ( node.type() )
        {
            case pugi::node_element:
                {
                    Ptree &tmp = pt.push_back(std::make_pair( node.name(), Ptree()))->second;
                    for ( pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute() )
                        tmp.put( xmlattr<Ch>() + "." + attr.name(), attr.value());
                    for ( pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
                        read_xml_node(child, tmp, flags);
                }
                break;
            case pugi::node_pcdata:
                {
                    if (flags & no_concat_text)
                        pt.push_back(std::make_pair(xmltext<Ch>(), Ptree( node.value() )));
                    else
                        pt.data() += node.value();
                }
                break;
            case pugi::node_comment:
                {
                    if (!(flags & no_comments))
                        pt.push_back(std::make_pair(xmlcomment<Ch>(), Ptree( node.value() )));
                }
                break;
            default:
                // skip other types
                break;
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {
        typedef typename Ptree::key_type::value_type Ch;

        // Create and load document from stream
        stream.unsetf(std::ios::skipws);

        if (!stream.good())
            throw xml_parser_error("read error", filename, 0);

        std::vector<Ch> buf;
        std::copy(std::istream_iterator<Ch>(stream), std::istream_iterator<Ch>(), std::back_inserter(buf));
        buf.push_back(0); // zero-terminate  

        unsigned int pugi_flags = pugi::parse_w3c;
        if ( flags & no_comments )
            pugi_flags = pugi_flags & ~pugi::parse_comments;

        pugi::xml_parser parser(&buf[0], pugi_flags);
        pugi::xml_node doc = parser.document();

        // Create ptree from nodes
        Ptree local;
        for ( pugi::xml_node child = doc.first_child(); child; child = child.next_sibling())
            read_xml_node( child, local, flags );

        // Swap local and result ptrees
        pt.swap(local);
    }

} } }

#endif
