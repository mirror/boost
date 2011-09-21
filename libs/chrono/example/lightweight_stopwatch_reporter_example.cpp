//  example/stopwatch_example.cpp  ---------------------------------------------------//
//  Copyright Beman Dawes 2006, 2008
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

//#include <iostream>
#include <boost/chrono/stopwatches/reporters/lightweight_stopwatch_reporter.hpp>
#include <boost/chrono/stopwatches/reporters/system_default_formatter.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <cmath>

using namespace boost::chrono;

elapsed_formatter fmtr;

int f1(long j)
{

  lightweight_stopwatch_reporter<simple_stopwatch<> > sw(fmtr);

  for ( long i = 0; i < j; ++i )
    std::sqrt( 123.456L );  // burn some time

  return 0;
}
int main()
{
  lightweight_stopwatch_reporter<simple_stopwatch<> > sw(fmtr);

  f1(1000);
  f1(2000);
  f1(3000);
  f1(4000);
  return 0;
}
