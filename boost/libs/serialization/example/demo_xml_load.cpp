/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// demo_xml_load.cpp : demonstrates usage of serialization system
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org for updates, documentation, and revision history.

#include <iostream>
#include <string>
#include <boost/archive/tmpdir.hpp>

#include <boost/archive/xml_iarchive.hpp>

#include "demo_xml.hpp"

void
restore_schedule(bus_schedule &s, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}

int main(int argc, char *argv[])
{   
	std::string filename(boost::archive::tmpdir());
	filename += "/demo_save.xml";

	// make  a new schedule
    bus_schedule new_schedule;

    restore_schedule(new_schedule, filename.c_str());

    // and display
    std::cout << "\nrestored schedule";
    std::cout << new_schedule;

    return 0;
}
