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
#include <boost/timer.hpp>
#include <boost/regex.hpp>

namespace b{

double time_match(const std::string& re, const std::string& text, bool icase)
{
   boost::regex e(re, (icase ? boost::regex::perl | boost::regex::icase : boost::regex::perl));
   boost::smatch what;
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
         boost::regex_match(text, what, e);
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
         boost::regex_match(text, what, e);
      }
      run = tim.elapsed();
      result = std::min(run, result);
   }
   return result / iter;
}

bool dummy_grep_proc(const boost::smatch&)
{ return true; }

double time_find_all(const std::string& re, const std::string& text, bool icase)
{
   boost::regex e(re, (icase ? boost::regex::perl | boost::regex::icase : boost::regex::perl));
   boost::smatch what;
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
         boost::regex_grep(&dummy_grep_proc, text, e);
      }
      result = tim.elapsed();
      iter *= 2;
   }while(result < 0.5);
   iter /= 2;

   if(result >10)
      return result / iter;

   // repeat test and report least value for consistency:
   for(repeats = 0; repeats < REPEAT_COUNT; ++repeats)
   {
      tim.restart();
      for(counter = 0; counter < iter; ++counter)
      {
         boost::regex_grep(&dummy_grep_proc, text, e);
      }
      run = tim.elapsed();
      result = std::min(run, result);
   }
   return result / iter;
}

}
