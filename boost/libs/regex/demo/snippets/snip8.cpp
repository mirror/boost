/*
 *
 * Copyright (c) 1998-2000
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
  *   FILE         snip8.cpp
  *   VERSION      3.00
  *   DESCRIPTION: regex_split example: split a string into tokens.
  */


#include <list>
#include <boost/regex.hpp>


unsigned tokenise(std::list<std::string>& l, std::string& s)
{
   return boost::regex_split(std::back_inserter(l), s);
}

#include <iostream>
using namespace std;


#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && (__BORLANDC__ == 0x550))
//
// problem with std::getline under MSVC6sp3
istream& getline(istream& is, std::string& s)
{
   s.erase();
   char c = is.get();
   while(c != '\n')
   {
      s.append(1, c);
      c = is.get();
   }
   return is;
}
#endif


int main()
{
   string s;
   list<string> l;
   do{
      cout << "Enter text to split (or \"quit\" to exit): ";
      getline(cin, s);
      if(s == "quit") break;
      unsigned result = tokenise(l, s);
      cout << result << " tokens found" << endl;
      cout << "The remaining text is: \"" << s << "\"" << endl;
      while(l.size())
      {
         s = *(l.begin());
         l.pop_front();
         cout << s << endl;
      }
   }while(true);
   return 0;
}
