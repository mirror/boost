// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PERF_FILE_STREAM_TEST_HPP_INCLUDED
#define BOOST_IOSTREAMS_PERF_FILE_STREAM_TEST_HPP_INCLUDED

#define USE_BLOCK_STREAMBUF

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <boost/iostreams/file.hpp>
#include <boost/iostreams/file_descriptor.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/progress.hpp>
#include "../test/detail/verification.hpp"

void remove_all(int trials)
{
    char temp_name[30];
    for (int z = 0; z < trials; ++z) {
        sprintf(temp_name, "C:/temp/tmp%d", z);
        remove(temp_name);
    }
}

void file_stream_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    int trials_per_run = 100;
    int runs = 400;
    double elapsed1 = 0, elapsed2 = 0;
    char temp_name[30];

    remove_all(trials_per_run);

    for (int w = 0; w < runs; ++w) {

        {
            timer t;
            stream_facade<file_descriptor_sink> out;
            ios_base::openmode mode = 
                ios_base::out | ios_base::trunc;
            for (int z = 0; z < trials_per_run; ++z) {
                sprintf(temp_name, "C:/temp/tmp%d", z);
                out.open(file_descriptor_sink(temp_name, mode));
                write_data_in_chunks(out);
                out.close();
            }
            elapsed1 += t.elapsed();
        }
    
        remove_all(trials_per_run);

        {
            timer t;
            std::ofstream out;
            std::ios_base::openmode mode = 
                std::ios_base::out | std::ios_base::trunc;
            for (int z = 0; z < trials_per_run; ++z) {
                sprintf(temp_name, "C:/temp/tmp%d", z);
                out.open(temp_name, mode);
                test::write_data_in_chunks(out);
                out.close();
            }
            elapsed2 += t.elapsed();
        }

        remove_all(trials_per_run);
    }

    cout << "total time stream_facade<file_descriptor_sink>: " << elapsed1 << "s\n";
    cout << "total time std::ofstream: " << elapsed2 << "s\n";
    
}

#endif // #ifndef BOOST_IOSTREAMS_PERF_FILE_STREAM_TEST_HPP_INCLUDED
