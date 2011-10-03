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

static const std::size_t size = 10000000;

template <typename Clock>
void perf(std::vector<typename Clock::time_point>& vec)
{
  typedef boost::chrono::stopwatch_reporter<boost::chrono::simple_stopwatch<boost::chrono::high_resolution_clock> > Reporter;
  Reporter rp;
  for (int i=size-1; i>=0; --i)
  {
    vec[i]=Clock::now();
    //vec[i]=typename Clock::time_point(typename Clock::time_point::duration(i));
  }
}

void perf2(std::vector<clock_t>& vec)
{
  typedef boost::chrono::stopwatch_reporter<boost::chrono::simple_stopwatch<boost::chrono::high_resolution_clock> > Reporter;
  Reporter rp;
  for (int i=size-1; i>=0; --i)
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
  for (int i=size-1; i>=0; --i)
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
  for (int i=size-1; i>1; --i)
  {
    if (vec[i]==vec[i-1]) ++cnt;
  }
  std::cout <<"Nb of values eq to preceding: "<< cnt << std::endl;
  std::cout <<"Diff last-first: "<< boost::chrono::duration_cast<boost::chrono::milliseconds>(vec[0]-vec[size-1]) << std::endl;

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
  std::cout <<"Nb of values eq to preceding: "<< cnt << std::endl;
  std::cout <<"Diff last-first: "<< vec[0]-vec[size-1] << std::endl;
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
  std::cout <<"Nb of values eq to preceding: "<< cnt << std::endl;
  std::cout <<"Diff last-first: "<< vec[0]-vec[size-1] << std::endl;
}

int main() {

  std::cout << "system_clock ";
  test<boost::chrono::system_clock>();
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  std::cout << "steady_clock " ;
  test<boost::chrono::steady_clock>();
#endif
  std::cout << "high_resolution_clock " ;
  test<boost::chrono::high_resolution_clock>();

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
  std::cout << "process_real_cpu_clock ";
  test<boost::chrono::process_real_cpu_clock>();
  std::cout << "process_user_cpu_clock ";
  test<boost::chrono::process_user_cpu_clock>();
  std::cout << "process_system_cpu_clock " ;
  test<boost::chrono::process_system_cpu_clock>();
#endif

  std::cout << "times ";
  test2();
  std::cout << "clock ";
  test3();
  return 1;
}
