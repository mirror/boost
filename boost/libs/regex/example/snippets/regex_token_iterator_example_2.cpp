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

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_token_iterator_example_2.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex_token_iterator example: spit out linked URL's.
  */


#include <fstream>
#include <iostream>
#include <iterator>
#include <boost/regex.hpp>

boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
               boost::regex::normal | boost::regbase::icase);

void load_file(std::string& s, std::istream& is)
{
   s.erase();
   //
   // attempt to grow string buffer to match file size,
   // this doesn't always work...
   s.reserve(is.rdbuf()->in_avail());
   char c;
   while(is.get(c))
   {
      // use logarithmic growth stategy, in case
      // in_avail (above) returned zero:
      if(s.capacity() == s.size())
         s.reserve(s.capacity() * 3);
      s.append(1, c);
   }
}

int main(int argc, char** argv)
{
   std::string s;
   int i;
   for(i = 1; i < argc; ++i)
   {
      std::cout << "Findings URL's in " << argv[i] << ":" << std::endl;
      s.erase();
      std::ifstream is(argv[i]);
      load_file(s, is);
      boost::regex_token_iterator<std::string::const_iterator>
         i(s.begin(), s.end(), e, 1);
      boost::regex_token_iterator<std::string::const_iterator> j;
      while(i != j)
      {
         std::cout << *i++ << std::endl;
      }
   }
   //
   // alternative method:
   // test the array-literal constructor, and split out the whole
   // match as well as $1....
   //
   for(i = 1; i < argc; ++i)
   {
      std::cout << "Findings URL's in " << argv[i] << ":" << std::endl;
      s.erase();
      std::ifstream is(argv[i]);
      load_file(s, is);
      const int subs[] = {1, 0,};
      boost::regex_token_iterator<std::string::const_iterator>
         i(s.begin(), s.end(), e, subs);
      boost::regex_token_iterator<std::string::const_iterator> j;
      while(i != j)
      {
         std::cout << *i++ << std::endl;
      }
   }

   return 0;
}


