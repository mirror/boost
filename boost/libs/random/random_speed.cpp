/* boost random_speed.cpp performance measurements
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without free provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/random.hpp>
#include <boost/progress.hpp>

/*
 * Configuration Section
 */

// define if your C library supports the non-standard drand48 family
#undef HAVE_DRAND48

// define if you have the original mt19937int.c (with commented out main())
#undef HAVE_MT19937INT_C

// set to your CPU frequency in MHz
static const double cpu_frequency = 200 * 1e6;

/*
 * End of Configuration Section
 */

/*
 * General portability note:
 * MSVC mis-compiles explicit function template instantiations.
 * For example, f<A>() and f<B>() are both compiled to call f<A>().
 * BCC is unable to implicitly convert a "const char *" to a std::string
 * when using explicit function template instantiations.
 *
 * Therefore, avoid explicit function template instantiations.
 */

// provides a run-time configurable linear congruential generator, just
// for comparison
template<class IntType>
class linear_congruential
{
public:
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  linear_congruential(IntType x0, IntType a, IntType c, IntType m)
    : _x(x0), _a(a), _c(c), _m(m) { }
  // compiler-generated copy ctor and assignment operator are fine
  void seed(IntType x0, IntType a, IntType c, IntType m)
    { _x = x0; _a = a; _c = c; _m = m; }
  void seed(IntType x0) { _x = x0; }
  result_type operator()() { _x = (_a*_x+_c) % _m; return _x; }
  result_type min() const { return _c == 0 ? 1 : 0; }
  result_type max() const { return _m -1; }

private:
  IntType _x, _a, _c, _m;
};

static void show_elapsed(double end, int iter, const std::string & name)
{
  double usec = end/iter*1e6;
  double cycles = usec * cpu_frequency/1e6;
  std::cout << name << ": " 
	    << usec*1e3 << " nsec/loop = " 
	    << cycles << " CPU cycles"
	    << std::endl;
}

template<class Result, class RNG>
static void timing(RNG & rng, int iter, const std::string& name, const Result&)
{
  volatile Result tmp; // make sure we're not optimizing too much
  boost::timer t;
  for(int i = 0; i < iter; i++)
    tmp = rng();
  show_elapsed(t.elapsed(), iter, name);
}

template<class RNG>
static void timing_sphere(RNG & rng, int iter, const std::string & name)
{
  boost::timer t;
  for(int i = 0; i < iter; i++) {
    // the special return value convention of uniform_on_sphere saves 20% CPU
    const std::vector<double> & tmp = rng();
    (void) tmp[0];
  }
  show_elapsed(t.elapsed(), iter, name);
}

template<class RNG>
void run(int iter, const std::string & name, const RNG &)
{
  RNG rng;
  std::cout << (RNG::has_fixed_range ? "fixed-range " : "");
  // BCC has trouble with string autoconversion for explicit specializations
  timing(rng, iter, std::string(name), 0l);
}

#ifdef HAVE_DRAND48
// requires non-standard C library support for srand48/lrand48
void run(int iter, const std::string & name, int)
{
  std::srand48(1);
  timing(std::lrand48, iter, name, 0l);
}
#endif

#ifdef HAVE_MT19937INT_C  // requires the original mt19937int.c
extern "C" void sgenrand(unsigned long);
extern "C" unsigned long genrand();

void run(int iter, const std::string & name, float)
{
  sgenrand(4357);
  timing(genrand, iter, name, 0u);
}
#endif

template<class Gen>
void distrib(int iter, const std::string & name, const Gen &)
{
  Gen gen;

  boost::uniform_smallint<Gen> usmallint(gen, -2, 4);
  timing(usmallint, iter, name + " uniform_smallint", 0);

  boost::uniform_int<Gen> uint(gen, -2, 4);
  timing(uint, iter, name + " uniform_int", 0);

  boost::uniform_01<Gen> uni(gen);
  timing(uni, iter, name + " uniform_01", 0.0);

  boost::uniform_real<Gen> ur(gen, -5.3, 4.8);
  timing(ur, iter, name + " uniform_real", 0.0);

  boost::geometric_distribution<Gen> geo(gen, 0.5);
  timing(geo, iter, name + " geometric", 0);

  boost::triangle_distribution<Gen> tria(gen, 1, 2, 7);
  timing(tria, iter, name + " triangle", 0.0);

  boost::exponential_distribution<Gen> ex(gen, 3);
  timing(ex, iter, name + " exponential", 0.0);

  boost::normal_distribution<Gen,double> no2(gen);
  timing(no2, iter, name + " normal polar", 0.0);

  boost::lognormal_distribution<Gen,double> lnorm(gen, 1, 1);
  timing(lnorm, iter, name + " lognormal", 0.0);

  boost::uniform_on_sphere<Gen> usph(gen, 3);
  timing_sphere(usph, iter/10, name + " uniform_on_sphere");
}


int main(int argc, char*argv[])
{
  if(argc != 2) {
    std::cerr << "usage: " << argv[0] << " iterations" << std::endl;
    return 1;
  }

  // okay, it's ugly, but it's only used here
  int iter =
#ifndef BOOST_NO_STDC_NAMESPACE
    std::
#endif
    atoi(argv[1]);

#if !defined(BOOST_NO_INT64_T) && \
    !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
  run(iter, "rand48", boost::rand48());
  linear_congruential<uint64_t>
    lcg48(uint64_t(1)<<16 | 0x330e,
	  uint64_t(0xDEECE66DUL) | (uint64_t(0x5) << 32), 0xB,
	  uint64_t(1)<<48);
  timing(lcg48, iter, "lrand48 run-time", 0l);
#endif

#ifdef HAVE_DRAND48
  // requires non-standard C library support for srand48/lrand48
  run(iter, "lrand48", 0);   // coded for lrand48()
#endif

  run(iter, "minstd_rand", boost::minstd_rand());
  run(iter, "ecuyer combined", boost::ecuyer1988());
  run(iter, "kreutzer1986", boost::kreutzer1986());

  run(iter, "hellekalek1995 (inversive)", boost::hellekalek1995());

  run(iter, "mt11213b", boost::mt11213b());
  run(iter, "mt19937", boost::mt19937());

#ifdef HAVE_MT19937INT_C
  // requires the original mt19937int.c
  run<float>(iter, "mt19937 original");   // coded for sgenrand()/genrand()
#endif

  distrib(iter, "minstd_rand", boost::minstd_rand());
  distrib(iter, "kreutzer1986", boost::kreutzer1986());
  distrib(iter, "mt19937", boost::mt19937());
};
