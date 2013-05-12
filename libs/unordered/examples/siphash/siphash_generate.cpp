
// Copyright 2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is also released into the public domain.

#include "siphash.hpp"
#include <boost/random/random_device.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>

namespace hash
{
    sipkey generate_sipkey()
    {
        boost::random_device rng;
        boost::variate_generator<boost::random_device&,
            boost::uniform_int<boost::uint64_t> > gen(rng,
                boost::uniform_int<boost::uint64_t>());

        sipkey k;
        k.k0 = gen();
        k.k1 = gen();
        return k;
    }
}
