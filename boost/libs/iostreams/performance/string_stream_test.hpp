// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PERF_STRING_STREAM_TEST_HPP_INCLUDED
#define BOOST_IOSTREAMS_PERF_STRING_STREAM_TEST_HPP_INCLUDED

#define USE_BLOCK_STREAMBUF

#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <boost/iostreams/container_device.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/progress.hpp>
#include "../test/detail/verification.hpp"

struct string_sink {
    typedef char                             char_type;
    typedef boost::iostreams::sink_tag              category;
    typedef boost::iostreams::detail::buffer<char>  buffer_type;
    string_sink() : buf_(new buffer_type(0)) { }
    void write(const char* s, std::streamsize n)
        {
            int size = (int) (buf().ptr() - buf().begin());
            if (buf().ptr() - buf().begin() + n > buf().size()) 
                grow(n);
            size = (int) (buf().ptr() - buf().begin());
            memcpy(buf().ptr(), s, n);
            buf().ptr() += n;
        }
    void grow(std::streamsize length)
        {
            length += buf().size();
            length *= 1.5;
            boost::iostreams::detail::buffer<char> tmp(length);
            std::streamsize valid = 
                static_cast<std::streamsize>(buf().ptr() - buf().data());
            tmp.ptr() += valid;
            memcpy(tmp.data(), buf().data(), valid);
            buf().swap(tmp);
        }
    std::string str() const 
    { 
        return std::string(buf().data(), buf().ptr());
    }
    buffer_type& buf() const { return *buf_; }
    boost::shared_ptr<buffer_type> buf_;
};

void string_stream_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;
    typedef container_device<string, seekable> seekable_string;
    typedef container_device<vector<char>, seekable> seekable_vector;

    int trials_per_run = 100;
    int runs = 400;
    double elapsed1 = 0, elapsed2 = 0;

    for (int w = 0; w < runs; ++w) {

        {
            timer t;
            stream_facade<string_sink> out;
            for (int z = 0; z < trials_per_run; ++z) {
                out.open(string_sink(), 0, 0);
                write_data_in_chunks(out);
                out.close();
            }
            elapsed1 += t.elapsed();
        }

        {
            timer t;
            std::stringstream out;
            for (int z = 0; z < trials_per_run; ++z) {
                out.str("");
                write_data_in_chunks(out);
            }
            elapsed2 += t.elapsed();
        }
    }

    cout << "total time stream_facade<seekable_string>: " << elapsed1 << "s\n";
    cout << "total time std::stringstream: " << elapsed2 << "s\n";
}

#endif // #ifndef BOOST_IOSTREAMS_PERF_STRING_STREAM_TEST_HPP_INCLUDED
