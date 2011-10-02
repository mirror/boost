//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/chrono.hpp>
#include <boost/chrono/stopwatches/reporters/stopwatch_reporter.hpp>
#include <boost/chrono/stopwatches/simple_stopwatch.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <vector>
#include <sys/time.h> //for gettimeofday and timeval
#include <sys/times.h> //for times
#include <unistd.h>

static const std::size_t size = 1000000;

template <typename Clock>
void perf(std::vector<typename Clock::time_point>& vec)
{
  typedef boost::chrono::stopwatch_reporter<boost::chrono::simple_stopwatch<boost::chrono::high_resolution_clock> > Reporter;
  Reporter rp;
  for (int i=size; i>0; --i)
  {
    vec[i]=Clock::now();
    //vec[i]=typename Clock::time_point(typename Clock::time_point::duration(i));
  }
}

void perf2(std::vector<clock_t>& vec)
{
  typedef boost::chrono::stopwatch_reporter<boost::chrono::simple_stopwatch<boost::chrono::high_resolution_clock> > Reporter;
  Reporter rp;
  for (int i=size; i>0; --i)
  {
    tms tm;
    vec[i]=::times(&tm);
    //vec[i]=typename Clock::time_point(typename Clock::time_point::duration(i));
  }
}

void perf3(std::vector<clock_t>& vec)
{
  typedef boost::chrono::stopwatch_reporter<boost::chrono::simple_stopwatch<boost::chrono::high_resolution_clock> > Reporter;
  Reporter rp;
  for (int i=size; i>0; --i)
  {
    vec[i]=::clock();
    //vec[i]=typename Clock::time_point(typename Clock::time_point::duration(i));
  }
}


template <typename Clock>
void test()
{
  std::vector<typename Clock::time_point> vec(size);
  perf<Clock>(vec);
  std::size_t cnt=0;
  for (int i=size; i>1; --i)
  {
    if (vec[i]==vec[i-1]) ++cnt;
  }
  std::cout << cnt << std::endl;
}
void test2()
{
  std::vector<clock_t> vec(size);
  perf2(vec);
  std::size_t cnt=0;
  for (int i=10; i>1; --i)
  {
    if (vec[i]==vec[i-1]) ++cnt;
    std::cout << vec[i] << " " ;
  }
  std::cout<< std::endl;
  std::cout << cnt << std::endl;
}

void test3()
{
  std::vector<clock_t> vec(size);
  perf3(vec);
  std::size_t cnt=0;
  for (int i=10; i>1; --i)
  {
    if (vec[i]==vec[i-1]) ++cnt;
    std::cout << vec[i] << " " ;
  }
  std::cout<< std::endl;
  std::cout << cnt << std::endl;
}

int main() {

  test<boost::chrono::system_clock>();
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  test<boost::chrono::steady_clock>();
#endif
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
  test<boost::chrono::process_real_cpu_clock>();
#endif
  test<boost::chrono::high_resolution_clock>();
  test2();
  test3();
  return 1;
}
