/* statistic_tests.cpp file
 *
 * Copyright Jens Maurer 2000, 2002
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 * Revision history
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <vector>
#include <set>
#include <algorithm>

#include <boost/cstdint.hpp>
#include <boost/random.hpp>

#include <boost/math/special_functions/gamma.hpp>

#include "statistic_tests.hpp"
#include "integrate.hpp"


double normal_density(double x)
{
  const double pi = 3.14159265358979323846;
  return 1/std::sqrt(2*pi) * std::exp(-x*x/2);
}

class chi_square_density : public std::unary_function<double, double>
{
public:
  chi_square_density(int freedom)
    : _exponent( static_cast<double>(freedom)/2-1 ),
      _factor(1/(std::pow(2, _exponent+1) * std::exp(boost::math::lgamma(_exponent+1))))
  { }

  double operator()(double x)
  {
    return _factor*std::pow(x, _exponent)*std::exp(-x/2);
  }
private:
  double _exponent, _factor;
};

// computes F(x) or F(y) - F(x)
class chi_square_probability : public distribution_function<double>
{
public:
  chi_square_probability(int freedom) : dens(freedom) {}
  double operator()(double x) { return operator()(0, x); }
  double operator()(double x, double y)
  { return trapezoid(dens, x, y, 1000); }
private:
  chi_square_density dens;
};

class uniform_distribution : public distribution_function<double>
{
public:
  uniform_distribution(double from, double to) : from(from), to(to) 
  { assert(from < to); }
  double operator()(double x) 
  { 
    if(x < from) 
      return 0;
    else if(x > to)
      return 1;
    else
      return (x-from)/(to-from);
  }
  double operator()(double x, double delta)
  { return operator()(x+delta) - operator()(x); }
private:
  double from, to;
};

class test_environment;

class test_base
{
protected:
  explicit test_base(test_environment & env) : environment(env) { }
  void check(double val) const; 
private:
  test_environment & environment;
};

class equidistribution_test : test_base
{
public:
  equidistribution_test(test_environment & env, unsigned int classes, 
                        unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(classes-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "equidistribution: " << std::flush;
    equidistribution_experiment equi(classes);
    variate_generator<RNG&, uniform_smallint<> > uint_linear(rng, uniform_smallint<>(0, classes-1));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(equi, uint_linear, n1), n2));
    check(run_experiment(test_distrib_chi_square, 
                         experiment_generator(equi, uint_linear, n1), 2*n2));

    std::cout << "  2D: " << std::flush;
    equidistribution_2d_experiment equi_2d(classes);
    unsigned int root = static_cast<unsigned int>(std::sqrt(double(classes)));
    assert(root * root == classes);
    variate_generator<RNG&, uniform_smallint<> > uint_square(rng, uniform_smallint<>(0, root-1));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(equi_2d, uint_square, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(equi_2d, uint_square, n1), 2*n2));
    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class ks_equidistribution_test : test_base
{
public:
  ks_equidistribution_test(test_environment & env, unsigned int classes)
    : test_base(env),
      test_distrib_chi_square(kolmogorov_smirnov_probability(5000), 
                              classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "KS: " << std::flush;
    // generator_reference_t<RNG> gen_ref(rng);
    RNG& gen_ref(rng);
    kolmogorov_experiment ks(n1);
    uniform_distribution ud(static_cast<double>((rng.min)()), static_cast<double>((rng.max)()));
    check(run_experiment(test_distrib_chi_square,
                         ks_experiment_generator(ks, gen_ref, ud), n2));
    check(run_experiment(test_distrib_chi_square,
                         ks_experiment_generator(ks, gen_ref, ud), 2*n2));
    std::cout << std::endl;
  }
private:
  distribution_experiment test_distrib_chi_square;
};

class runs_test : test_base
{
public:
  runs_test(test_environment & env, unsigned int classes,
            unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(classes-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "runs: up: " << std::flush;
    runs_experiment<true> r_up(classes);
    // generator_reference_t<RNG> gen_ref(rng);
    RNG& gen_ref(rng);
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(r_up, gen_ref, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(r_up, gen_ref, n1), 2*n2));

    std::cout << "  down: " << std::flush;
    runs_experiment<false> r_down(classes);
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(r_down, gen_ref, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(r_down, gen_ref, n1), 2*n2));

    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class gap_test : test_base
{
public:
  gap_test(test_environment & env, unsigned int classes,
            unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(classes-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "gaps: " << std::flush;
    gap_experiment gap(classes, 0.2, 0.8);
    // generator_reference_t<RNG> gen_ref(rng);
    RNG& gen_ref(rng);
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(gap, gen_ref, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(gap, gen_ref, n1), 2*n2));

    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class poker_test : test_base
{
public:
  poker_test(test_environment & env, unsigned int classes,
             unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(classes-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "poker: " << std::flush;
    poker_experiment poker(8, classes);
    variate_generator<RNG&, uniform_smallint<> > usmall(rng, uniform_smallint<>(0, 7));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(poker, usmall, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(poker, usmall, n1), 2*n2));
    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class coupon_collector_test : test_base
{
public:
  coupon_collector_test(test_environment & env, unsigned int classes,
                        unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(classes-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "coupon collector: " << std::flush;
    coupon_collector_experiment coupon(5, classes);

    variate_generator<RNG&, uniform_smallint<> > usmall(rng, uniform_smallint<>(0, 4));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(coupon, usmall, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(coupon, usmall, n1), 2*n2));
    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class permutation_test : test_base
{
public:
  permutation_test(test_environment & env, unsigned int classes,
                   unsigned int high_classes)
    : test_base(env), classes(classes),
      test_distrib_chi_square(chi_square_probability(fac<int>(classes)-1), 
                              high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "permutation: " << std::flush;
    permutation_experiment perm(classes);
    
    // generator_reference_t<RNG> gen_ref(rng);
    RNG& gen_ref(rng);
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(perm, gen_ref, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(perm, gen_ref, n1), 2*n2));
    std::cout << std::endl;
  }
private:
  unsigned int classes;
  distribution_experiment test_distrib_chi_square;
};

class maximum_test : test_base
{
public:
  maximum_test(test_environment & env, unsigned int high_classes)
    : test_base(env),
      test_distrib_chi_square(kolmogorov_smirnov_probability(1000),
                              high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "maximum-of-t: " << std::flush;
    maximum_experiment<RNG> mx(rng, n1, 5);    
    check(run_experiment(test_distrib_chi_square, mx, n2));
    check(run_experiment(test_distrib_chi_square, mx, 2*n2));
    std::cout << std::endl;
  }
private:
  distribution_experiment test_distrib_chi_square;
};

class birthday_test : test_base
{
public:
  birthday_test(test_environment & env, unsigned int high_classes)
    : test_base(env),
      test_distrib_chi_square(chi_square_probability(4-1), high_classes)
  { }

  template<class RNG>
  void run(RNG & rng, int n1, int n2)
  {
    using namespace boost;
    std::cout << "birthday spacing: " << std::flush;
    boost::variate_generator<RNG&, boost::uniform_int<> > uni(rng, boost::uniform_int<>(0, (1<<25)-1));
    birthday_spacing_experiment bsp(4, 512, (1<<25));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(bsp, uni, n1), n2));
    check(run_experiment(test_distrib_chi_square,
                         experiment_generator(bsp, uni, n1), 2*n2));
    std::cout << std::endl;
  }
private:
  distribution_experiment test_distrib_chi_square;
};

#ifdef BOOST_MSVC
#pragma warning(disable:4355)
#endif

class test_environment
{
public:
  static const int classes = 20;
  explicit test_environment(double confid) 
    : confidence(confid),
      confidence_chi_square_quantil(quantil(chi_square_density(classes-1), 0, confidence, 1e-4)),
      test_distrib_chi_square6(chi_square_probability(7-1), classes),
      ksequi_test(*this, classes),
      equi_test(*this, 100, classes),
      rns_test(*this, 7, classes),
      gp_test(*this, 7, classes),
      pk_test(*this, 5, classes),
      cpn_test(*this, 15, classes),
      perm_test(*this, 5, classes),
      max_test(*this, classes),
      bday_test(*this, classes)
  {
    std::cout << "Confidence level: " << confid 
              << "; 1-alpha = " << (1-confid)
              << "; chi_square(" << (classes-1) 
              << ", " << confidence_chi_square_quantil
              << ") = " 
              << chi_square_probability(classes-1)(0, confidence_chi_square_quantil)
              << std::endl;
  }
  
  bool check_confidence(double val, double chi_square_conf) const
  {
    std::cout << val;
    bool result = (val <= chi_square_conf);
    if(!result) {
      std::cout << "* [";
      double prob = (val > 10*chi_square_conf ? 1 :
                     chi_square_probability(classes-1)(0, val));
      std::cout << (1-prob) << "]";
    }
    std::cout << " " << std::flush;
    return result;
  }

  bool check(double chi_square_value) const
  {
    return check_confidence(chi_square_value, confidence_chi_square_quantil);
  }

  template<class RNG>
  void run_test(const std::string & name)
  {
    using namespace boost;

    std::cout << "Running tests on " << name << std::endl;

    RNG rng(1234567);
    typedef boost::uniform_01<RNG> UGen;

#if 1
    ksequi_test.run(rng, 5000, 250);
    equi_test.run(rng, 5000, 250);
    rns_test.run(rng, 100000, 250);
    gp_test.run(rng, 10000, 250);
    pk_test.run(rng, 5000, 250);
    cpn_test.run(rng, 500, 250);
    perm_test.run(rng, 1200, 250);
    max_test.run(rng, 1000, 250);
#endif
    bday_test.run(rng, 1000, 150);

    std::cout << std::endl;
  }

private:
  double confidence;
  double confidence_chi_square_quantil;
  distribution_experiment test_distrib_chi_square6;
  ks_equidistribution_test ksequi_test;
  equidistribution_test equi_test;
  runs_test rns_test;
  gap_test gp_test;
  poker_test pk_test;
  coupon_collector_test cpn_test;
  permutation_test perm_test;
  maximum_test max_test;
  birthday_test bday_test;
};

void test_base::check(double val) const
{ 
  environment.check(val);
}

void print_ks_table()
{
  std::cout.setf(std::ios::fixed);
  std::cout.precision(5);
  static const double all_p[] = { 0.01, 0.05, 0.25, 0.5, 0.75, 0.95, 0.99 };
  for(int n = 0; n <= 10000;  (n < 55 ? ++n : n *= 10)) {
    std::cout << std::setw(4) << n << " ";
    for(unsigned int i = 0; i < sizeof(all_p)/sizeof(all_p[0]); ++i) {
      std::cout << std::setw(8) 
                << (n == 0 ? all_p[i] : 
                    invert_monotone_inc(kolmogorov_smirnov_probability(n), all_p[i], 0, 10))
                << " ";
    }
    std::cout << std::endl;
  }
}

class program_args 
{
public:
  program_args(int argc, char** argv)
  {
    if(argc > 0) {
      names.insert(argv + 1, argv + argc);
    }
  }
  bool check(std::string test_name) const
  {
    return(names.empty() || names.find(test_name) != names.end());
  }
private:
  std::set<std::string> names;
};

int main(int argc, char* argv[])
{
  program_args args(argc, argv);
  test_environment env(0.99);

#define TEST(name)                      \
  if(args.check(#name))                 \
    env.run_test<boost::name>(#name)

  TEST(minstd_rand0);
  TEST(minstd_rand);
  TEST(rand48);
  TEST(ecuyer1988);
  TEST(kreutzer1986);
  TEST(taus88);
  TEST(hellekalek1995);
  TEST(mt11213b);
  TEST(mt19937);
  TEST(lagged_fibonacci607);
  TEST(lagged_fibonacci1279);
  TEST(lagged_fibonacci2281);
  TEST(lagged_fibonacci3217);
  TEST(lagged_fibonacci4423);
  TEST(lagged_fibonacci9689);
  TEST(lagged_fibonacci19937);
  TEST(lagged_fibonacci23209);
  TEST(lagged_fibonacci44497);
  TEST(ranlux3);
  TEST(ranlux4);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
  TEST(ranlux64_3);
  TEST(ranlux64_4);
#endif

  TEST(ranlux3_01);
  TEST(ranlux4_01);
  TEST(ranlux64_3_01);
  TEST(ranlux64_4_01);
}
