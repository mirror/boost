/* boost random_demo.cpp profane demo
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
 *
 * A short demo program how to use the random number library.
 */

#include <iostream>
#include <fstream>
#include <ctime>            // std::time
#include <boost/random.hpp>


// try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::minstd_rand base_generator_type;

// This is a reproducible simulation experiment.
void experiment(base_generator_type & generator)
{
  boost::uniform_smallint<base_generator_type> die(generator, 1, 6);

  // you can use a STL Iterator interface
  for(int i = 0; i < 10; i++)
    std::cout << *die++ << " ";
  std::cout << '\n';
}

int main()
{
  // initialize by reproducible seed
  base_generator_type generator(42);

  std::cout << "10 samples of a uniform distribution in [0..1):\n";
  boost::uniform_01<base_generator_type> uni(generator);
  std::cout.setf(std::ios::fixed);

  // you can also use a STL Generator interface
  for(int i = 0; i < 10; i++)
    std::cout << uni() << '\n';

  // change seed to something else
  // Note: this is not the preferred way of hacking around missing std::
  generator.seed(
#ifndef BOOST_NO_STDC_NAMESPACE
		 std::
#endif
		 time(0));

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
