/*
 *
 * Copyright (c) 2002
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

#include "regex_comparison.hpp"
#if defined(BOOST_HAS_GRETA)
#include <cassert>
#include <boost/timer.hpp>
#include "regexpr2.h"

namespace g{

double time_match(const std::string& re, const std::string& text, bool icase)
{
   regex::rpattern e(re, (icase ? regex::MULTILINE | regex::NORMALIZE | regex::NOCASE : regex::MULTILINE | regex::NORMALIZE));
   regex::match_results what;
   boost::timer tim;
   int iter = 1;
   int counter, repeats;
   double result = 0;
   double run;
   assert(e.match(text, what));
   do
   {
      tim.restart();
      for(counter = 0; counter < iter; ++counter)
      {
         e.match(text, what);
      }
      result = tim.elapsed();
      iter *= 2;
   }while(result < 0.5);
   iter /= 2;

   // repeat test and report least value for consistency:
   for(repeats = 0; repeats < REPEAT_COUNT; ++repeats)
   {
      tim.restart();
      for(counter = 0; counter < iter; ++counter)
      {
         e.match(text, what);
      }
      run = tim.elapsed();
      result = std::min(run, result);
   }
   return result / iter;
}

double time_find_all(const std::string& re, const std::string& text, bool icase)
{
   regex::rpattern e(re, (icase ? regex::MULTILINE | regex::NORMALIZE | regex::NOCASE : regex::MULTILINE | regex::NORMALIZE));
   regex::match_results what;
   boost::timer tim;
   int iter = 1;
   int counter, repeats;
   double result = 0;
   double run;
   do
   {
      tim.restart();
      for(counter = 0; counter < iter; ++counter)
      {
         e.match(text.begin(), text.end(), what);
         while(what.backref(0).matched)
         { 
            e.match(what.backref(0).end(), text.end(), what); 
         }
      }
      result = tim.elapsed();
      iter *= 2;
   }while(result < 0.5);
   iter /= 2;

   if(result > 10)
      return result / iter;

   // repeat test and report least value for consistency:
   for(repeats = 0; repeats < REPEAT_COUNT; ++repeats)
   {
      tim.restart();
      for(counter = 0; counter < iter; ++counter)
      {
         e.match(text.begin(), text.end(), what);
         while(what.backref(0).matched)
         { 
            e.match(what.backref(0).end(), text.end(), what); 
         }
      }
      run = tim.elapsed();
      result = std::min(run, result);
   }
   return result / iter;
}

}

#else

namespace g {

double time_match(const std::string& re, const std::string& text, bool icase)
{
   return -1;
}

double time_find_all(const std::string& re, const std::string& text, bool icase)
{
   return -1;
}

}

#endif

