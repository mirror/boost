// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_CONTAINER_DEVICE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_CONTAINER_DEVICE_HPP_INCLUDED

#define USE_BLOCK_STREAMBUF

#include <fstream>
#include <deque>
#include <list>
#include <vector>
#include <string>
#include <boost/iostreams/device/container_device.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/ref.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

#include <boost/progress.hpp>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <boost/iostreams/file.hpp>
#include <boost/iostreams/file_descriptor.hpp>

template<typename Container>
void read_container_device()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    typedef container_device<Container, input>  device;
    typedef stream_facade<device>               container_stream;

    test_file test;
    Container cnt;
    for (int z = 0; z < data_reps; ++z)
        cnt.insert( cnt.end(), data<char>(),
                    data<char>() + data_length() );

        // Test container_device with container held by value

    {
        device            dev(cnt);
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from container_stream "
            "in chars with no buffer"
        );
    }

    {
        device            dev(cnt);
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from sequence adapter"
            "in chars with no buffer"
        );
    }

    {
        container_stream  first(cnt);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from container_stream "
            "in chars with buffer"
        );
    }

    {
        container_stream  first(cnt);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from sequence adapter"
            "in chars with buffer"
        );
    }


        // Test container_device with container held by reference

    {
        device            dev(ref(cnt));
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from container_stream "
            "based on reference in chars with no buffer"
        );
    }

    {
        device            dev(ref(cnt));
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from sequence adapter"
            "based on reference in chars with no buffer"
        );
    }

    {
        container_stream  first(ref(cnt));
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from container_stream "
            "based on reference in chars with buffer"
        );
    }

    {
        container_stream  first(ref(cnt));
        ifstream          second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from sequence adapter"
            "based on reference in chars with buffer"
        );
    }
}

template<typename Container>
void write_container_device()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    typedef container_device<Container, output>  device;
    typedef stream_facade<device>                container_stream;
    test_file                                    test;

        // Test container_device with container held by value

    {
        device            dev;
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        write_data_in_chars(first);
        Container cnt = first->container();
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "in chars with no buffer"
        );
    }

    {
        device            dev;
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        write_data_in_chunks(first);
        Container cnt = first->container();
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to sequence adapter"
            "in chars with no buffer"
        );
    }

    {
        device            dev;
        container_stream  first(dev);
        ifstream          second(test.name().c_str());
        write_data_in_chars(first);
        Container cnt = first->container();
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "in chars with buffer"
        );
    }

    {
        device            dev;
        container_stream  first(dev);
        ifstream          second(test.name().c_str());
        write_data_in_chunks(first);
        Container cnt = first->container();
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to sequence adapter"
            "in chars with buffer"
        );
    }


        // Test container_device with container held by reference

    {
        Container         cnt;
        device            dev(ref(cnt));
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        write_data_in_chars(first);
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "based on reference in chars with no buffer"
        );
    }

    {
        Container         cnt;
        device            dev(ref(cnt));
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        write_data_in_chunks(first);
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "based on reference in chars with no buffer"
        );
    }

   {
        Container         cnt;
        device            dev(ref(cnt));
        container_stream  first(dev, 0);
        ifstream          second(test.name().c_str());
        write_data_in_chars(first);
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "based on reference in chars with buffer"
        );
    }

    {
        Container         cnt;
        container_stream  first(ref(cnt));
        ifstream          second(test.name().c_str());
        write_data_in_chunks(first);
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(cnt, second),
            "failed writing to container_stream "
            "based on reference in chars with buffer"
        );
    }
}

template<typename Container>
void seek_container_device()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    typedef container_device<Container, seekable>  device;
    typedef stream_facade<device>                  container_stream;

        // Test container_device with container held by value

    {
        device            dev;
        container_stream  io(dev, 0);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within container_stream "
            "in chars with no buffer"
        );
    }

    {
        device            dev;
        container_stream  io(dev, 0);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within container_stream "
            "in chunks with no buffer"
        );
    }

    {
        device            dev;
        container_stream  io(dev);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within container_stream "
            "in chars with buffer"
        );
    }

    {
        device            dev;
        container_stream  io(dev);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within container_stream "
            "in chunks with buffer"
        );
    }
}

void container_device_test()
{
    using namespace boost::iostreams;
    read_container_device< std::deque<char> >();
    read_container_device< std::list<char> >();
    read_container_device< std::string >();
    read_container_device< std::vector<char> >();
    write_container_device< std::deque<char> >();
    write_container_device< std::list<char> >();
    write_container_device< std::string >();
    write_container_device< std::vector<char> >();
    seek_container_device< std::deque<char> >();
    seek_container_device< std::string >();
    seek_container_device< std::vector<char> >();
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_CONTAINER_DEVICE_HPP_INCLUDED
