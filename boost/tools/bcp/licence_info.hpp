/*
 *
 * Copyright (c) 2003
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */

#include <boost/regex.hpp>
#include <utility>

struct licence_info
{
   boost::regex licence_signature;
   boost::regex copyright_signature;
   std::string  copyright_formatter;
   std::string  licence_name;
   std::string  licence_text;
   //
   // we should really be able to initialize licence_info as an
   // aggregate, but some compilers reject this, so use a constructor
   //instaed:
   //
   licence_info(const boost::regex& e1, 
				const boost::regex& e2, 
				const std::string& s1, 
				const std::string& s2, 
				const std::string& s3)
				: licence_signature(e1), 
				  copyright_signature(e2),
				  copyright_formatter(s1),
				  licence_name(s2),
				  licence_text(s3){}
};

std::pair<const licence_info*, int> get_licences();

std::string format_authors_name(const std::string& name);
