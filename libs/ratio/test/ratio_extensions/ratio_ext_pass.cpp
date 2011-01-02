//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

// test ratio:  equivalent ratios convert with BOOST_RATIO_EXTENSIONS

#define BOOST_RATIO_EXTENSIONS
#include <boost/ratio.hpp>
#include <boost/detail/lightweight_test.hpp>

boost::intmax_t func(boost::ratio<5,6>  s) {
    return s.num;    
}

void test() {
    BOOST_TEST((
        func(boost::ratio<10,12>() )==5
    ));
}

int main()
{
    test();
}
