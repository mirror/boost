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
  *
  *   FILE     regress.cpp
  *   VERSION  3.03
  *
  * main() and associated code for regress.
  *
  */

#include <cstdlib>
#include <boost/regex.hpp>
#ifdef BOOST_RE_OLD_IOSTREAM
#include <fstream.h>
#else
#include <fstream>
using std::ifstream;
using std::ofstream;
//using std::cin;
//using std::cout;
using std::endl;
#endif

#ifdef __BORLANDC__
#pragma hrdstop
#endif

#include "regress.h"


//
// declare all our globals here:
//

string_type expression;
string_type search_text;
string_type format_string;
string_type merge_string;
int matches[MAX_MATCHES];

char file[MAX_PATH];
int line;
bool do_test = false;
unsigned int flags[5];
unsigned error_count = 0;

void usage()
{
   cout <<

"Usage: regress filename [filename2...]\n"
"see tests.txt for an example test script\n"
"and the script format.\n";

}

int main(int argc, char * argv[])
{
   if(argc < 2)
       usage();
   int i;
   for(i = 1; i < argc; ++i)
   {
      reset_error();
      ifstream is(argv[i]);
      if(is.good() == false)
      {
         cout << "Error unable to open file: " << argv[i] << endl << endl;
         return -1;
      }
      std::strcpy(file, argv[i]);
      line = 0;
      unsigned int tests = 0;
      while(is.good())
      {
         string_type s;
         get_line(is, s);
         ++line;
         jm_trace("Reading test script line " << line << " " << s);
         parse_input_line(s);
         if(do_test)
         {
            run_tests();
            ++tests;
         }
      }
      cout << line << " lines, " << tests << " tests completed in file " << argv[i] << endl;
   }
   return error_count;
}

#ifdef TEST_UNICODE

ostream& operator << (ostream& os, const wchar_t* s)
{
   while(*s)
   {
      os.put((char)*s);
      ++s;
   }
   return os;
}

ostream& operator << (ostream& os, const std::wstring& s)
{
   os << s.c_str();
   return os;
}

istream& get_line(istream& is, nstring_type& s, char delim)
{
   char c = (char)is.get();
   s.erase(s.begin(), s.end());
   while((c != delim) && (c != EOF))
   {
      s.append(1, c);
      c = (char)is.get();
   }
   return is;
}

istream& get_line(istream& is, string_type& s, char delim)
{
   nstring_type t;
   get_line(is, t, delim);
   s.erase(s.begin(), s.end());
   const char* i, *j;
   i = t.c_str();
   j = t.c_str() + t.size();
   wchar_t* buf = new wchar_t[MB_CUR_MAX + 1];
   int cchars;
   while(i != j)
   {
      cchars = mbtowc(buf, i, j - i);
      if(cchars == -1)
         break;
      if(cchars == 0)
         break;
      s.insert(s.end(), buf, buf + cchars);
      i += cchars;
   }
   delete[] buf;
   return is;
}


#else

istream& get_line(istream& is, string_type& s, char delim)
{
   char c = (char)is.get();
   s.erase(s.begin(), s.end());
   while((c != delim) && (c != EOF))
   {
      s.append(1, c);
      c = (char)is.get();
   }
   return is;
}

#endif

jm_debug_alloc::jm_debug_alloc()
{
   blocks = new int;
   count = new int;
   *blocks = 0;
   *count = 1;
   guard = this;
}

jm_debug_alloc::jm_debug_alloc(const jm_debug_alloc& d)
{
   blocks = d.blocks;
   count = d.count;
   ++(*count);
   guard = this;
}
jm_debug_alloc& jm_debug_alloc::operator=(const jm_debug_alloc& d)
{
   free();
   blocks = d.blocks;
   count = d.count;
   ++(*count);
   return *this;
}

jm_debug_alloc::~jm_debug_alloc()
{
   if(guard != this)
   {
      cout << "Error: attempt to destroy object already destroyed" << endl;
   }
   else
   {
      free();
      guard = 0;
   }
}
void jm_debug_alloc::free()
{
    if(--(*count) == 0)
    {
       if(*blocks)
       {
          begin_error();
          cout << "Error: " << *blocks << " blocks not freed by allocator" << endl;
       }
       delete count;
       delete blocks;
    }
}

jm_debug_alloc::pointer jm_debug_alloc::allocate(size_type n, void* hint)
{
   pointer p = new char[n + maxi(sizeof(size_type), boost::re_detail::padding_size)];
   *(size_type*)p = n;
   ++(*blocks);
   return p + maxi(sizeof(size_type), boost::re_detail::padding_size);
}
void jm_debug_alloc::deallocate(pointer p, size_type n)
{
   p -= maxi(sizeof(size_type), boost::re_detail::padding_size);
   if(*(size_type*)p != n)
   {
      begin_error();
      cout << "Error: size mismatch in allocate/deallocate calls" << endl;
   }
   --(*blocks);
   delete[] p;
}


