/* boost random_demo.cpp profane demo
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 *
 * A short demo program how to use the random number library.
 */

#include <iostream>
#include <fstream>
#include <ctime>            // std::time

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/uniform_01.hpp>

// Sun CC doesn't handle boost::iterator_adaptor yet
#if !defined(__SUNPRO_CC) || (__SUNPRO_CC > 0x530)
#include <boost/generator_iterator.hpp>
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
  using ::time;
}
#endif

// try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::minstd_rand base_generator_type;

// This is a reproducible simulation experiment.
void experiment(base_generator_type & generator)
{
  typedef boost::uniform_smallint<base_generator_type> generator_type;
  generator_type die_gen(generator, 1, 6);

#if !defined(__SUNPRO_CC) || (__SUNPRO_CC > 0x530)
  // For an STL iterator interface, use iterator_adaptors.hpp
  boost::generator_iterator_generator<generator_type>::type
    die = boost::make_generator_iterator(die_gen);
  for(int i = 0; i < 10; i++)
    std::cout << *die++ << " ";
  std::cout << '\n';
#endif
}

int main()
{
  // initialize by reproducible seed
  // Make sure it's unsigned, otherwise the wrong overload may be selected
  // with mt19937.
  base_generator_type generator(42u);

  std::cout << "10 samples of a uniform distribution in [0..1):\n";
  boost::uniform_01<base_generator_type> uni(generator);
  std::cout.setf(std::ios::fixed);

  // Random number generators have an STL Generator interface
  for(int i = 0; i < 10; i++)
    std::cout << uni() << '\n';

  /*
   * Change seed to something else
   * Make sure the seed is unsigned, otherwise the wrong overload may be
   * selected with mt19937.
   *
   * Caveat: std::time(0) is not a very good truly-random seed.  When
   * called in rapid succession, it could return the same values, and
   * thus the same random number sequences could ensue.  If not the same
   * values are returned, the values differ only slightly in the
   * lowest bits.  A linear congruential generator with a small factor
   * wrapped in a uniform_smallint (see experiment) will produce the same
   * values for the first few iterations.   This is because uniform_smallint
   * takes only the highest bits of the generator, and the generator itself
   * needs a few iterations to spread the initial entropy from the lowest bits
   * to the whole state.
   */
  generator.seed(static_cast<unsigned int>(std::time(0)));

  std::cout << "\nexperiment: roll a die 10 times:\n";
  base_generator_type saved_generator = generator;
  experiment(generator);

  std::cout << "redo the experiment to verify it:\n";
  experiment(saved_generator);

  // after that, both generators are equivalent
  assert(generator == saved_generator);

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  {
    // save the generator state for future use,
    // can be read again at any time via operator>>
    std::ofstream file("rng.saved", std::ofstream::trunc);
    file << generator;
  }
#endif
  // Some compilers don't pay attention to std:3.6.1/5 and issue a
  // warning here if "return 0;" is omitted.
  return 0;
}
