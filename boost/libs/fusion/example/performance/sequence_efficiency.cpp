/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include "measure.hpp"

#define FUSION_MAX_LIST_SIZE 30
#define FUSION_MAX_VECTOR_SIZE 30

#include <boost/fusion/algorithm/iteration/accumulate.hpp>
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/container/list.hpp>

#include <algorithm>
#include <numeric>
#include <functional>
#include <iostream>
#include <cmath>
#include <limits>

#ifdef _MSC_VER
// inline aggressively
# pragma inline_recursion(on) // turn on inline recursion
# pragma inline_depth(255)    // max inline depth
#endif

namespace
{
    struct poly_add
    {
        template<typename Lhs, typename Rhs>
        struct result
        {
            typedef Lhs type;
        };

        template<typename Lhs, typename Rhs>
        Lhs operator()(const Lhs& lhs, const Rhs& rhs) const
        {
            return lhs + rhs;
        }
    };

    // Our Accumulator function
    template <typename T>
    struct accumulator
    {
        accumulator()
            : sum()
        {}
        
        template <typename Sequence>
        void operator()(Sequence const& seq)
        {
            this->sum += boost::fusion::accumulate(seq, 0, poly_add());
        }
        
        T sum;
    };
}

int main()
{
    using namespace test;
    using namespace boost::fusion;

    vector<
        int, int, int
    > 
    vsmall(BOOST_PP_ENUM_PARAMS(3,));

    list<
        int, int, int
    > 
    lsmall(BOOST_PP_ENUM_PARAMS(3,));

    vector<
        int, int, int, int, int, int, int, int, int, int
    > 
    vmid(BOOST_PP_ENUM_PARAMS(10,));

    list<
        int, int, int, int, int, int, int, int, int, int
    > 
    lmid(BOOST_PP_ENUM_PARAMS(10,));

    vector<
        int, int, int, int, int, int, int, int, int, int
      , int, int, int, int, int, int, int, int, int, int
      , int, int, int, int, int, int, int, int, int, int
    > 
    vbig(BOOST_PP_ENUM_PARAMS(30,));

    list<
        int, int, int, int, int, int, int, int, int, int
      , int, int, int, int, int, int, int, int, int, int
      , int, int, int, int, int, int, int, int, int, int
    > 
    lbig(BOOST_PP_ENUM_PARAMS(30,));

    // first decide how many repetitions to measure
    long repeats = 100;
    double measured = 0;
    while (measured < 1.0 && repeats <= 10000000)
    {
        repeats *= 10;
        
        boost::timer time;

        hammer<accumulator<int> >(vsmall, repeats);
        hammer<accumulator<int> >(lsmall, repeats);
        hammer<accumulator<int> >(vmid, repeats);
        hammer<accumulator<int> >(lmid, repeats);
        hammer<accumulator<int> >(vbig, repeats);
        hammer<accumulator<int> >(lbig, repeats);

        measured = time.elapsed();
    }

    measure<accumulator<int> >(vsmall, 1);
    std::cout 
        << "small vector accumulated result:    " 
        << live_code << std::endl;
    measure<accumulator<int> >(lsmall, 1);
    std::cout 
        << "small list accumulated result:      " 
        << live_code << std::endl;
    measure<accumulator<int> >(vmid, 1);
    std::cout 
        << "medium vector accumulated result:   " 
        << live_code << std::endl;
    measure<accumulator<int> >(lmid, 1);
    std::cout 
        << "medium list accumulated result:     " 
        << live_code << std::endl;
    measure<accumulator<int> >(vbig, 1);
    std::cout 
        << "big vector accumulated result:      " 
        << live_code << std::endl;
    measure<accumulator<int> >(lbig, 1);
    std::cout 
        << "big list accumulated result:        " 
        << live_code << std::endl;

    std::cout.setf(std::ios::scientific);

    std::cout
        << "small vector time:                  "
        << measure<accumulator<int> >(vsmall, repeats)
        << std::endl;
    std::cout
        << "small list time:                    "
        << measure<accumulator<int> >(lsmall, repeats)
        << std::endl;    
    std::cout
        << "medium vector time:                 "
        << measure<accumulator<int> >(vmid, repeats)
        << std::endl;
    std::cout
        << "medium list time:                   "
        << measure<accumulator<int> >(lmid, repeats)
        << std::endl;
    std::cout
        << "big vector time:                    "
        << measure<accumulator<int> >(vbig, repeats)
        << std::endl;
    std::cout
        << "big list time:                      "
        << measure<accumulator<int> >(lbig, repeats)
        << std::endl;

    // This is ultimately responsible for preventing all the test code
    // from being optimized away.  Change this to return 0 and you
    // unplug the whole test's life support system.
    return live_code != 0;
}
