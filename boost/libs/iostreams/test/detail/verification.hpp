// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.


#ifndef BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED

#include <exception>
#include <string>
#include <string.h>
#include <fstream>
#include <istream>
#include <ostream>

#include <boost/config.hpp>
#include "./constants.hpp"

namespace boost { namespace iostreams { namespace test {

template<typename Ch, typename Tr>
bool compare_streams_in_chars(std::basic_istream<Ch, Tr>&, std::basic_istream<Ch, Tr>&);
template<typename Ch, typename Tr>
bool compare_streams_in_chunks(std::basic_istream<Ch, Tr>&, std::basic_istream<Ch, Tr>&);
bool compare_files(const std::string&, const std::string&);
template<typename Container, typename Ch, typename Tr>
bool compare_container_and_stream(Container&, std::basic_istream<Ch, Tr>&);
template<typename Ch, typename Tr>
void write_data_in_chars(std::basic_ostream<Ch, Tr>&);
template<typename Ch, typename Tr>
void write_data_in_chunks(std::basic_ostream<Ch, Tr>& os);
bool test_seekable_in_chars(std::iostream& io);
bool test_seekable_in_chunks(std::iostream& io);
bool unbuffered_putback_test(std::istream&);
bool buffered_putback_test(std::istream&);

template<typename Ch, typename Tr>
bool compare_streams_in_chars
    (std::basic_istream<Ch, Tr>& first, std::basic_istream<Ch, Tr>& second)
{
    for (int z = 0; z < 10; ++z)
        for (int w = 0; w < data_length(); ++w)
            if (first.eof() != second.eof() || first.get() != second.get())
                return false;
    return true;
}

template<typename Ch, typename Tr>
bool compare_streams_in_chunks
    (std::basic_istream<Ch, Tr>& first, std::basic_istream<Ch, Tr>& second)
{
    int i = 0;
    do {
        Ch buf_one[chunk_size];
        Ch buf_two[chunk_size];
        first.read(buf_one, chunk_size);
        second.read(buf_two, chunk_size);
        std::streamsize amt = first.gcount();
        if ( amt != second.gcount() ||
             std::char_traits<Ch>::compare(buf_one, buf_two, amt) != 0 )
            return false;
        ++i;
    } while (!first.eof());
    return true;
}

bool compare_files(const std::string& first, const std::string& second)
{
    std::fstream one(first.c_str());
    std::fstream two(second.c_str());
    return compare_streams_in_chunks(one, two);
}

template<typename Container, typename Ch, typename Tr>
bool compare_container_and_stream(Container& cnt, std::basic_istream<Ch, Tr>& is)
{
    typename Container::iterator first = cnt.begin();
    typename Container::iterator last = cnt.end();
    do  {
        if ((first == last) != is.eof()) return false;
        if (first != last && *first++ != is.get()) return false;
    } while (first != last);
    return true;
}

template<typename Ch, typename Tr>
void write_data_in_chars(std::basic_ostream<Ch, Tr>& os)
{
    for (int z = 0; z < data_reps; ++z) 
        for (int w = 0; w < data_length(); ++w) 
            os.put(detail::data((Ch*)0)[w]);
    os.flush();
}

template<typename Ch, typename Tr>
void write_data_in_chunks(std::basic_ostream<Ch, Tr>& os)
{
    const Ch* buf = detail::data((Ch*)0);
    for (int z = 0; z < data_reps; ++z)
        os.write(buf, data_length());
    os.flush();
}

bool test_seekable_in_chars(std::iostream& io)
{
    for (int i = 0; i < data_reps; ++i) {
        int j;
        for (j = 0; j < chunk_size; ++j)
            io.put(narrow_data()[j]);
        io.seekp(-chunk_size, std::ios::cur);
        for (j = 0; j < chunk_size; ++j)
            if (io.get() != narrow_data()[j])
               return false;
        io.seekp(-chunk_size, std::ios::cur);
        for (j = 0; j < chunk_size; ++j)
            io.put(narrow_data()[j]);
    }
    return true;
}

bool test_seekable_in_chunks(std::iostream& io)
{
    for (int i = 0; i < data_reps; ++i) {
        io.write(narrow_data(), chunk_size);
        io.seekp(-chunk_size, std::ios::cur);
        char buf[chunk_size];
        io.read(buf, chunk_size);
        if (strncmp(buf, narrow_data(), chunk_size) != 0)
            return false;
        io.seekp(-chunk_size, std::ios::cur);
        io.write(narrow_data(), chunk_size);
    }
    return true;
}

bool unbuffered_putback_test(std::istream& is)
{
    try {
        do {
            char buf[chunk_size];
            is.read(buf, chunk_size);
            if (is.gcount() < chunk_size)
                break;
            is.putback('a');
            if (is.get() != 'a')
                return false;
        } while (!is.eof());
        return true;
    } catch (std::exception&) { return false; }
}

bool buffered_putback_test(std::istream& is)
{
    try {
        do {
            char buf[chunk_size];
            is.read(buf, chunk_size);
            if (is.gcount() < chunk_size)
                break;
            is.putback('a');
            is.putback('b');
            is.putback('c');
            is.putback('d');
            if ( is.get() != 'd' || is.get() != 'c' ||
                 is.get() != 'b' || is.get() != 'a' )
            {
                return false;
            }
        } while (!is.eof());
        return true;
    } catch (std::exception&) { return false; }
}

} } } // End namespaces test, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED
