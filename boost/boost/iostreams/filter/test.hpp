// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTER_TEST_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp> // Put size_t in std.
#include <algorithm>        // equal, min.
#include <cstddef>          // size_t.
#include <cstdlib>          // rand.
#include <cstring>          // memcpy, strlen.
#include <iterator>
#include <vector>
#if defined(__CYGWIN__)
# include <boost/random/linear_congruential.hpp>
# include <boost/random/uniform_smallint.hpp>
#endif
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/detail/adapter/basic_adapter.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/operations.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
# undef rand
# undef memcpy
# undef strlen
namespace std { using ::rand; using ::memcpy; using ::strlen; }
#endif

namespace boost { namespace iostreams {

const std::streamsize default_increment = 10;

#if defined(__CYGWIN__)
    std::streamsize rand(int inc)
    {
        static rand48                random_gen;
        static uniform_smallint<int> random_dist(0, inc);
        return random_dist(random_gen);
    }
#else
    std::streamsize rand(int inc) 
    { 
        return (std::rand() * inc + 1) / RAND_MAX; 
    }
#endif

class non_blocking_source : public source {
public:
    explicit non_blocking_source( const char* data, 
                                  std::streamsize inc = default_increment ) 
        : data_(data), inc_(inc), pos_(0), 
          len_(static_cast<std::streamsize>(strlen(data)))
        { }
    explicit non_blocking_source( const char* begin, const char* end,
                                  std::streamsize inc = default_increment )
        : data_(begin), inc_(inc), pos_(0), 
          len_(static_cast<std::streamsize>(end - begin))
        { }
    std::streamsize read(char* s, std::streamsize n)
    {
        if (pos_ == len_)
            return -1;
        std::streamsize avail = 
            (std::min) (n, static_cast<std::streamsize>(len_ - pos_));
        std::streamsize amt = (std::min) (rand(inc_), avail);
        if (amt)
            std::memcpy(s, data_ + pos_, amt);
        pos_ += amt;
        return amt;
    }
private:
    const char*      data_;
    std::streamsize  inc_, pos_, len_;
};

class non_blocking_sink : public sink {
public:
    non_blocking_sink( std::vector<char>& dest,
                       std::streamsize inc = default_increment ) 
        : dest_(dest), inc_(inc) 
        { }
    std::streamsize write(const char* s, std::streamsize n)
    {
        std::streamsize amt = (std::min) (rand(inc_), n);
        dest_.insert(dest_.end(), s, s + amt);
        return amt;
    }
private:
    std::vector<char>&  dest_;
    std::streamsize     inc_;
};

//template<typename Device>
//class would_block_adapter : basic_adapter<Device> {
//private:
//    typedef typename detail::value_type<T>::type value_type;
//    typedef typename detail::param_type<T>::type param_type;
//public:
//    would_block_adapter(param_type dev, std::streamsize inc) 
//        : basic_adapter<Device>(dev), inc_(inc)
//        { }
//    std::streamsize read(char* s, std::streamsize n)
//    {
//        std::streamsize amt = (std::min) (rand(inc_), n);
//        return iostreams::read(this->component(), s, amt);
//    }
//    std::streamsize write(const char* s, std::streamsize n)
//    {
//        std::streamsize amt = (std::min) (rand(inc_), n);
//        return iostreams::write(this->component(), s, amt);
//    }
//private:
//    std::streamsize inc_;
//};

template<typename Filter>
bool test_input_filter( Filter filter, 
                        const char* input, 
                        const char* output )
{
    for ( int inc = default_increment; 
          inc < default_increment * 10; 
          inc += default_increment )
    {
        non_blocking_source  src(input, inc);
        std::vector<char>    dest;
        iostreams::copy(compose(filter, src), iostreams::back_inserter(dest));
        if ( dest.size() != std::strlen(input) ||
            !std::equal(dest.begin(), dest.end(), output) )
        {
            return false;
        }
    }
    return true;
}

template<typename Filter, typename Source1, typename Source2>
bool test_input_filter( Filter filter, 
                        const Source1& input, 
                        const Source2& output )
{
    std::string in;
    std::string out;
    iostreams::copy(input, iostreams::back_inserter(in));
    iostreams::copy(output, iostreams::back_inserter(out));
    return test_input_filter(filter, in.c_str(), out.c_str());
}

template<typename Filter>
bool test_output_filter( Filter filter, 
                         const char* input, 
                         const char* output )
{
    for ( int inc = default_increment; 
          inc < default_increment * 10; 
          inc += default_increment )
    {
        array_source       src(input, input + std::strlen(input));
        std::vector<char>  dest;
        iostreams::copy(src, compose(filter, non_blocking_sink(dest, inc)));
        if ( dest.size() != std::strlen(output) ||
            !std::equal(dest.begin(), dest.end(), output) )
        {
            return false;
        }
    }
    return true;
}

template<typename Filter, typename Source1, typename Source2>
bool test_output_filter( Filter filter, 
                         const Source1& input, 
                         const Source2& output )
{
    std::string in;
    std::string out;
    iostreams::copy(input, iostreams::back_inserter(in));
    iostreams::copy(output, iostreams::back_inserter(out));
    return test_output_filter(filter, in.c_str(), out.c_str());
}

template<typename OutputFilter, typename InputFilter>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const char* data )
{
    for ( int inc = default_increment; 
          inc < default_increment * 10; 
          inc += default_increment )
    {
        array_source       src(data, data + std::strlen(data));
        std::vector<char>  temp;
        std::vector<char>  dest;
        iostreams::copy(src, compose(out, non_blocking_sink(temp, inc)));
        iostreams::copy( 
            compose(in, non_blocking_source(&temp[0], &temp[0] + temp.size(), inc)),
            iostreams::back_inserter(dest)
        );
        if ( dest.size() != std::strlen(data) ||
            !std::equal(dest.begin(), dest.end(), data) )
        {
            return false;
        }
    }
    return true;
}

template<typename OutputFilter, typename InputFilter, typename Source>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const Source& data )
{
    std::string str;
    iostreams::copy(data, iostreams::back_inserter(str));
    return test_filter_pair(out, in, str.c_str());
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FILTER_TEST_HPP_INCLUDED
