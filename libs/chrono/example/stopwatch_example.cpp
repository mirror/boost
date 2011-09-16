//  example/stopwatch_example.cpp  ---------------------------------------------------//
//  Copyright Beman Dawes 2006, 2008
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

//#include <iostream>
#include <boost/chrono/stopwatches/simple_stopwatch.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <cmath>

using namespace boost::chrono;

int f1(long j)
{
  simple_stopwatch<> sw;

  for ( long i = 0; i < j; ++i )
    std::sqrt( 123.456L );  // burn some time

  std::cout << "f1("<< j <<") Elapsed time: " << sw.elapsed() << std::endl;
  return 0;
}
int main()
{
  simple_stopwatch<> sw;

  f1(1000);
  f1(2000);
  f1(3000);
  std::cout << "main() Elapsed time: " << sw.elapsed() << std::endl;
  return 0;
}
