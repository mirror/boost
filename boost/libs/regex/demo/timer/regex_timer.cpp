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

#ifdef BOOST_RE_OLD_IOSTREAM
#include <iostream.h>
#else
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::istream;
using std::ostream;
using std::endl;
#endif

#include <algorithm>
#include <string>
#include <deque>
#include <boost/regex.hpp>
#include <boost/timer.hpp> 
#include <boost/smart_ptr.hpp>

#ifdef BOOST_MSVC
// no Koenig lookup, use using declaration instead:
using namespace boost;
#endif

#ifndef BOOST_RE_NO_WCSTRING
ostream& operator << (ostream& os, const std::wstring& s)
{
   std::wstring::const_iterator i, j;
   i = s.begin();
   j = s.end();
   while(i != j)
   {
      os.put(*i);
      ++i;
   }
   return os;
}
#endif

template <class S>
class string_out_iterator
{
   S* out;
public:
   string_out_iterator(S& s) : out(&s) {}
   string_out_iterator& operator++() { return *this; }
   string_out_iterator& operator++(int) { return *this; }
   string_out_iterator& operator*() { return *this; }
   string_out_iterator& operator=(typename S::value_type v) 
   { 
      out->append(1, v); 
      return *this; 
   }
};

#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && (__BORLANDC__ == 0x550)) || defined(__SGI_STL_PORT)
//
// problem with std::getline under MSVC6sp3
// and C++ Builder 5.5, is this really that hard?
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
   boost::regex ex;
   boost::match_results<std::string::const_iterator> sm;
#ifndef BOOST_RE_NO_WCSTRING
   std::wstring ws1, ws2;
   boost::wregex wex;
   boost::match_results<std::wstring::const_iterator> wsm;
#endif
   boost::match_results<std::deque<char>::iterator> dm;
   std::string s1, s2, ts;
   std::deque<char> ds;
   boost::regex_t r;
   boost::scoped_array<boost::regmatch_t> matches;
   size_t nsubs;
   boost::timer t;
   double tim;
   bool result;
   int iters = 100;

   while(true)
   {
      cout << "Enter expression (or \"quit\" to exit): ";
      getline(cin, s1);
      if(s1 == "quit")
         break;
#ifndef BOOST_RE_NO_WCSTRING
      ws1.erase();
      std::copy(s1.begin(), s1.end(), string_out_iterator<std::wstring>(ws1));
#endif
      try{
         ex.assign(s1.begin(), s1.end());
#ifndef BOOST_RE_NO_WCSTRING
         wex.assign(ws1.begin(), ws1.end());
#endif
      }
      catch(std::exception& e)
      {
         cout << "Error in expression: \"" << e.what() << "\"" << endl;
         continue;
      }
      int code = regcomp(&r, s1.c_str(), boost::REG_PERL);
      if(code != 0)
      {
         char buf[256];
         regerror(code, &r, buf, 256);
         cout << "regcomp error: \"" << buf << "\"" << endl;
         continue;
      }
      nsubs = r.re_nsub + 1;
      matches.reset(new boost::regmatch_t[nsubs]);

      while(true)
      {
         cout << "Enter string to search (or \"quit\" to exit): ";
         getline(cin, s2);
         if(s2 == "quit")
            break;

#ifndef BOOST_RE_NO_WCSTRING
         ws2.erase();
         std::copy(s2.begin(), s2.end(), string_out_iterator<std::wstring>(ws2));
#endif
         ds.erase(ds.begin(), ds.end());
         std::copy(s2.begin(), s2.end(), std::back_inserter(ds));

         int i;
         iters = 10;
         tim = 1.1;

#if defined(_WIN32) && defined(BOOST_RE_LOCALE_W32)
         MSG msg;
         PeekMessage(&msg, 0, 0, 0, 0);
         Sleep(0);
#endif

         // cache load:
         regex_search(s2, sm, ex);

         // measure time interval for reg_expression<char>
         do{
            iters *= (tim > 0.001) ? (1.1/tim) : 100;
            t.restart();
            for(i =0; i < iters; ++i)
            {
               result = regex_search(s2, sm, ex);
            }
            tim = t.elapsed();
         }while((tim < t.elapsed_min() * 1000) || (tim < 1));

         cout << "regex time: " << (tim * 1000000 / iters) << "us" << endl;
         if(result)
         {
            for(i = 0; i < sm.size(); ++i)
            {
               ts = sm[i];
               cout << "\tmatch " << i << ": \"";
               cout << ts;
               cout << "\" (matched=" << sm[i].matched << ")" << endl;
            }
            cout << "\tmatch $`: \"";
            cout << std::string(sm[-1]);
            cout << "\" (matched=" << sm[-1].matched << ")" << endl;
            cout << "\tmatch $': \"";
            cout << std::string(sm[-2]);
            cout << "\" (matched=" << sm[-2].matched << ")" << endl << endl;
         }

#ifndef BOOST_RE_NO_WCSTRING
         // measure time interval for boost::wregex
         iters = 10;
         tim = 1.1;
         // cache load:
         regex_search(ws2, wsm, wex);
         do{
            iters *= (tim > 0.001) ? (1.1/tim) : 100;
            t.restart();
            for(i = 0; i < iters; ++i)
            {
               result = regex_search(ws2, wsm, wex);
            }
            tim = t.elapsed();
         }while((tim < t.elapsed_min() * 1000) || (tim < 1));
         cout << "wregex time: " << (tim * 1000000 / iters) << "us" << endl;
         if(result)
         {
            std::wstring tw;
            for(i = 0; i < wsm.size(); ++i)
            {
               tw.erase();
               std::copy(wsm[i].first, wsm[i].second, string_out_iterator<std::wstring>(tw));
               cout << "\tmatch " << i << ": \"" << tw;
               cout << "\" (matched=" << sm[i].matched << ")" << endl;
            }
            cout << "\tmatch $`: \"";
            tw.erase();
            std::copy(wsm[-1].first, wsm[-1].second, string_out_iterator<std::wstring>(tw));
            cout << tw;
            cout << "\" (matched=" << sm[-1].matched << ")" << endl;
            cout << "\tmatch $': \"";
            tw.erase();
            std::copy(wsm[-2].first, wsm[-2].second, string_out_iterator<std::wstring>(tw));
            cout << tw;
            cout << "\" (matched=" << sm[-2].matched << ")" << endl << endl;
         }
#endif
        
         // measure time interval for reg_expression<char> using a deque
         iters = 10;
         tim = 1.1;
         // cache load:
         regex_search(ds.begin(), ds.end(), dm, ex);
         do{
            iters *= (tim > 0.001) ? (1.1/tim) : 100;
            t.restart();
            for(i = 0; i < iters; ++i)
            {
               result = regex_search(ds.begin(), ds.end(), dm, ex);
            }
            tim = t.elapsed();
         }while((tim < t.elapsed_min() * 1000) || (tim < 1));
         cout << "regex time (search over std::deque<char>): " << (tim * 1000000 / iters) << "us" << endl;

         if(result)
         {
            for(i = 0; i < dm.size(); ++i)
            {
               ts.erase();
               std::copy(dm[i].first, dm[i].second, string_out_iterator<std::string>(ts));
               cout << "\tmatch " << i << ": \"" << ts;
               cout << "\" (matched=" << sm[i].matched << ")" << endl;
            }
            cout << "\tmatch $`: \"";
            ts.erase();
            std::copy(dm[-1].first, dm[-1].second, string_out_iterator<std::string>(ts));
            cout << ts;
            cout << "\" (matched=" << sm[-1].matched << ")" << endl;
            cout << "\tmatch $': \"";
            ts.erase();
            std::copy(dm[-2].first, dm[-2].second, string_out_iterator<std::string>(ts));
            cout << ts;
            cout << "\" (matched=" << sm[-2].matched << ")" << endl << endl;
         }
         
         // measure time interval for POSIX matcher:
         iters = 10;
         tim = 1.1;
         // cache load:
         regexec(&r, s2.c_str(), nsubs, matches.get(), 0);
         do{
            iters *= (tim > 0.001) ? (1.1/tim) : 100;
            t.restart();
            for(i = 0; i < iters; ++i)
            {
               result = regexec(&r, s2.c_str(), nsubs, matches.get(), 0);
            }
            tim = t.elapsed();
         }while((tim < t.elapsed_min() * 1000) || (tim < 1));
         cout << "POSIX regexec time: " << (tim * 1000000 / iters) << "us" << endl;

         if(result == 0)
         {
            for(i = 0; i < nsubs; ++i)
            {
               if(matches[i].rm_so >= 0)
               {
                  ts.assign(s2.begin() + matches[i].rm_so, s2.begin() + matches[i].rm_eo);
                  cout << "\tmatch " << i << ": \"" << ts << "\" (matched=" << (matches[i].rm_so != -1) << ")"<< endl;
               }
               else
                  cout << "\tmatch " << i << ": \"\" (matched=" << (matches[i].rm_so != -1) << ")" << endl;   // no match
            }
            cout << "\tmatch $`: \"";
            ts.erase();
            ts.assign(s2.begin(), s2.begin() + matches[0].rm_so);
            cout << ts;
            cout << "\" (matched=" << (matches[0].rm_so != 0) << ")" << endl;
            cout << "\tmatch $': \"";
            ts.erase();
            ts.assign(s2.begin() + matches[0].rm_eo, s2.end());
            cout << ts;
            cout << "\" (matched=" << (matches[0].rm_eo != s2.size()) << ")" << endl << endl;
         }
      }
      regfree(&r);
   }
   return 0;
}






