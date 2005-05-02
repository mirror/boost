// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from an example of James Kanze, with suggestions from Peter Dimov.
// See http://www.gabi-soft.fr/codebase-en.html. 

#ifndef BOOST_IOSTREAMS_SHELL_COMMENTS_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_SHELL_COMMENTS_FILTER_HPP_INCLUDED

#include <cassert>
#include <cstdio>    // EOF.
#include <iostream>  // cin, cout.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/filter/stdio_filter.hpp>
#include <boost/iostreams/operations.hpp>

namespace boost { namespace iostreams { namespace example {

class shell_comments_stdio_filter : public stdio_filter {
public:
    explicit shell_comments_stdio_filter(char comment_char = '#')
        : comment_char_(comment_char) 
        { }
private:
    void do_filter()
    {
        bool  skip = false;
        int   c;
        while ((c = std::cin.get()) != EOF) {
            skip = c == comment_char_ ?
                true :
                c == '\n' ?
                    false :
                    skip;
            if (!skip)
                std::cout.put(c);
        }
    }
    char comment_char_;
};

class shell_comments_input_filter : public input_filter {
public:
    explicit shell_comments_input_filter(char comment_char = '#')
        : comment_char_(comment_char), skip_(false)
        { }

    template<typename Source>
    int get(Source& src)
    {
        int c;
        while (true) {
            if ((c = boost::iostreams::get(src)) == EOF || c == WOULD_BLOCK)
                break;
            skip_ = c == comment_char_ ?
                true :
                c == '\n' ?
                    false :
                    skip_;
            if (!skip_)
                break;
        }
        return c;
    }

    template<typename Source>
    void close(Source&) { skip_ = false; }
private:
    char comment_char_;
    bool skip_;
};

class shell_comments_output_filter : public output_filter {
public:
    explicit shell_comments_output_filter(char comment_char = '#')
        : comment_char_(comment_char), skip_(false)
        { }

    template<typename Sink>
    bool put(Sink& dest, int c)
    {
        skip_ = c == comment_char_ ?
            true :
            c == '\n' ?
                false :
                skip_;

        if (skip_)
            return true;

        return iostreams::put(dest, c);
    }

    template<typename Source>
    void close(Source&) { skip_ = false; }
private:
    char comment_char_;
    bool skip_;
};

} } }       // End namespaces example, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SHELL_COMMENTS_FILTER_HPP_INCLUDED
