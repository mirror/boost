//  french.cpp  ----------------------------------------------------------//

//  Copyright 2010 Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

// Adapted to Boost from the original Hawards's code

#include <iostream>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/floor.hpp>
#include <boost/chrono/round.hpp>
#include <boost/chrono/ceil.hpp>

int main()
{
        using namespace boost::chrono;
        milliseconds ms(2500);
        std::cout << floor<seconds>(ms) << '\n';
        std::cout << round<seconds>(ms) << '\n';
        std::cout << ceil<seconds>(ms) << '\n';
        ms = milliseconds(2516);
        typedef duration<long, boost::ratio<1, 30> > frame_rate;
        std::cout << floor<frame_rate>(ms) << '\n';
        std::cout << round<frame_rate>(ms) << '\n';
        std::cout << ceil<frame_rate>(ms) << '\n';

        return 0;
}
