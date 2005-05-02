// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from an example of James Kanze, with suggestions from Peter Dimov.
// See http://www.gabi-soft.fr/codebase-en.html. 

#ifndef BOOST_IOSTREAMS_CPP_COMMENTS_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CPP_COMMENTS_FILTER_HPP_INCLUDED

#include <cassert>
#include <cstdio>    // EOF.
#include <iostream>  // cin, cout.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/filter/stdio_filter.hpp>
#include <boost/iostreams/operations.hpp>

namespace boost { namespace iostreams { namespace example {

struct cpp_comments_base {
    enum {
        st_line_beginning,
        st_normal,
        st_open_slash,
        st_close_slash,
        st_open_star,
        st_close_star,
        st_quote,
        st_escape_odd,
        st_escape_even
    };
    cpp_comments_base() : state_(st_normal) { }
    int state_;
};

class cpp_comments_stdio_filter : public stdio_filter {
public:
    explicit cpp_comments_stdio_filter() { }
private:
    void do_filter()
    {
        int c;
        while ((c = std::cin.get()) != EOF) {
            switch (state_) {
            case st_normal:
                if (c == '/') {
                    state_ = st_open_slash;
                } else if (c == '"' || c == '<') {

                }
                break;
            case st_open_slash:
            case st_close_slash:
            case st_open_star:
            case st_close_star:
            case st_quote:
            case st_escape_odd:
            case st_escape_even:
            }
        }
    }
    void do_close() { state_ = st_normal; }
};

//class cpp_comments_input_filter : public input_filter {
//public:
//    explicit cpp_comments_input_filter(char comment_char = '#')
//        : comment_char_(comment_char), skip_(false)
//        { }
//
//    template<typename Source>
//    int get(Source& src)
//    {
//        int c;
//        while (true) {
//            if ((c = boost::iostreams::get(src)) == EOF || c == WOULD_BLOCK)
//                break;
//            skip_ = c == comment_char_ ?
//                true :
//                c == '\n' ?
//                    false :
//                    skip_;
//            if (!skip_)
//                break;
//        }
//        return c;
//    }
//
//    template<typename Source>
//    void close(Source&) { skip_ = false; }
//private:
//    char comment_char_;
//    bool skip_;
//};
//
//class cpp_comments_output_filter : public output_filter {
//public:
//    explicit cpp_comments_output_filter(char comment_char = '#')
//        : comment_char_(comment_char), skip_(false)
//        { }
//
//    template<typename Sink>
//    bool put(Sink& dest, int c)
//    {
//        skip_ = c == comment_char_ ?
//            true :
//            c == '\n' ?
//                false :
//                skip_;
//
//        if (skip_)
//            return true;
//
//        return iostreams::put(dest, c);
//    }
//
//    template<typename Source>
//    void close(Source&) { skip_ = false; }
//private:
//    char comment_char_;
//    bool skip_;
//};

} } }       // End namespaces example, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CPP_COMMENTS_FILTER_HPP_INCLUDED
