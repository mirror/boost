// Copyright Sascha Ochsenknecht 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_PROGRAM_OPTIONS_SOURCE
#include <boost/program_options/parsers.hpp>
#include <string>
#include <vector>

namespace boost { namespace program_options { namespace detail {


   template<class charT>
   std::vector<std::basic_string<charT> > 
   split(const std::basic_string<charT>& cmdline, const std::basic_string<charT>& sep)
   {
      std::vector<std::basic_string<charT> > result;
      if (!cmdline.empty()) 
      { 
         std::basic_string<charT> sub(cmdline), val;
         std::size_t pos; 

         while (sub.size() > 0) 
         {                                                     
            if ((pos = sub.find_first_of(sep)) != sub.npos) 
            {                 
               val = sub.substr(0,pos);                                               
               sub = sub.substr(pos+1);                                               
            } 
            else 
            {                                                                  
               val = sub;                                                             
               sub.erase();                                                           
            }                                                                         
            if (!val.empty()) 
            {
               result.push_back(val);
            }
         }      
      }
      return result;   
   }
   
}}}

namespace boost { namespace program_options {

   // Take a command line string and splits in into tokens, according
   // to the given collection of seperators chars.
   BOOST_PROGRAM_OPTIONS_DECL std::vector<std::string> 
   split(const std::string& cmdline, const std::string& sep)
   {
      return detail::split(cmdline, sep);
   }

#ifndef BOOST_NO_STD_WSTRING
   BOOST_PROGRAM_OPTIONS_DECL std::vector<std::wstring>
   split(const std::wstring& cmdline, const std::wstring& sep)
   {
      return detail::split(cmdline, sep);
   }
#endif

}}
