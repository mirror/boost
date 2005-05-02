// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// NOTE: I hope to replace the current implementation with a much simpler 
// one.

#ifndef BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cassert>     
#include <cstdio>                            
#include <stdexcept>                       // logic_error.               
#include <boost/config.hpp>                // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/categories.hpp> 
#include <boost/iostreams/detail/char_traits.hpp> 
#include <boost/iostreams/pipeline.hpp>      

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

#define BOOST_IOSTREAMS_ASSERT_UNREACHABLE(val)   \
    (assert("unreachable code" == 0), val) \
    /**/

namespace boost { namespace iostreams {

namespace newline {

const char CR                   = 0x0D;
const char LF                   = 0x0A;

    // Flags for configuring newline_filter.

// Exactly one of the following three flags must be present.

const int print_CR          = 0;    // Use CR as line separator.
const int print_LF          = 1;    // Use LF as line separator.
const int print_CRLF        = 2;    // Use CRLF as line separator.

const int accept_CR         = 4;    // Recognize CR as line separator.
const int accept_LF         = 8;    // Recognize LF as line separator.
const int accept_CRLF       = 16;   // Recognize CRLF as line separator.
const int ignore_CR         = 32;   // Ignore stray CR's.
const int ignore_LF         = 64;   // Ignore stray LF's.
const int greedy            = 128;  // Check for CRLF before matching CR.
const int final_newline     = 256;  // Adding terminating newline.

    // Useful combinations of flags.

const int accept_default = 
    accept_CR | accept_LF | accept_CRLF | greedy;
const int posix = accept_default | print_LF;
const int mac = accept_default | print_CR;
const int windows = accept_default | print_CRLF;

    // Masks used by newline_filter.

const int print_mask = print_CR | print_LF | print_CRLF;

} // End namespace newline.

template<typename Ch>
class basic_newline_filter {
public:
    typedef Ch                                      char_type;
    typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
    typedef typename traits_type::int_type          int_type;
    struct io_category 
        : dual_use, 
          filter_tag, 
          closable_tag 
        { };

    basic_newline_filter(int flags) : flags_(flags) 
    { 
        using namespace newline;
        int print = (flags & print_mask);
        if (print != print_CR && print != print_LF && print != print_CRLF)
            throw std::logic_error("bad flags");
    }

    template<typename Source>
    int_type get(Source& src)
    {
        using namespace newline;
        while (true) {

            // Handle unfinished business.
            if (flags_ & (has_LF | has_EOF)) {
                if (flags_ & has_LF)
                    return newline();
                else 
                    return EOF;
            }

            // Handle the most common case.
            int_type c;
            if (!is_newline(c = boost::iostreams::get(src))) {
                if (!ignore(c))
                    return non_newline(c);
                else
                    continue;
            }

            // Handle newlines.
            if ( c == CR && 
                (flags_ & accept_CRLF) != 0 && 
                ((flags_ & greedy) != 0 || (flags_ & accept_CR) == 0) )
            {
                int_type d;
                if ((d = boost::iostreams::get(src)) == LF)  
                    return newline();
                else if (flags_ & accept_CR) {
                    this->putback(src, d);
                    return newline();
                } else if (flags_ & ignore_CR) {
                    return non_newline(d);
                } else {
                    this->putback(src, d);
                    return non_newline(CR);
                }
            } else {
                return newline();
            }
        }
    }

    template<typename Sink>
    void put(Sink& snk, char_type c)
    {
        using namespace newline;

        // Handle unfinished business.
        if (flags_ & has_CR) {
            flags_ &= ~has_CR;
            if (c == LF) {
                newline(snk);
                return;
            } else if (flags_ & accept_CR) {
                newline(snk); // Continue below.
            } else if ((flags_ & ignore_CR) == 0) {
                non_newline(CR, snk); // Continue below.
            }
        }

        // Handle the most common case.
        if (!is_newline(c)) {
            if (!ignore(c)) 
                non_newline(c, snk);
            return;
        }
            
        // Handle newlines.
        if ( c == CR && 
            (flags_ & accept_CRLF) != 0 && 
            ((flags_ & greedy) != 0 || (flags_ & accept_CR) == 0) )
        {
            flags_ |= has_CR;
        } else {
             newline(snk);
        }
    }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        using namespace newline;
        if ( which & BOOST_IOS::out && 
             (flags_ & final_newline) != 0 && 
             (flags_ & line_complete) == 0 )
        {
            newline(snk);
        }
    }
private:
    static bool is_eof(int_type c) 
    { return traits_type::eq_int_type(c, traits_type::eof()); }
    bool is_newline(int_type c) 
    { 
        using namespace newline;
        return c == CR && (flags_ & accept_CR) != 0 ||
               c == LF && (flags_ & accept_LF) != 0 ||
               (c == CR || c == LF) && (flags_ & accept_CRLF) != 0;
    }
    bool ignore(int_type c) 
    { 
        using namespace newline;
        return c == CR && (flags_ & ignore_CR) != 0 ||
               c == LF && (flags_ & ignore_LF) != 0;
    }

    template<typename Source>
    void putback(Source& src, int_type c)
    {
        if (!is_eof(c))
            boost::iostreams::putback(src, c);
        else
            flags_ |= has_EOF;
    }

    // Returns the given character, recording the fact that it is
    // not a newline (unless c is EOF and a final newline sequence
    // must be returned before EOF.)
    int_type non_newline(int_type c)
    {
        using namespace newline;
        if ( c == EOF && 
            (flags_ & final_newline) != 0 && 
            (flags_ & line_complete) == 0 ) 
        {
            flags_ |= has_EOF;
            return newline();
        } else {
            flags_ &= ~line_complete;
            return c;
        }
    }

    // Returns the appropriate element of a newline sequence.
    int_type newline() 
    { 
        using namespace newline;
        flags_ |= line_complete;
        switch (flags_ & print_mask) {
        case print_CR: return CR;
        case print_LF: return LF;
        case print_CRLF:
            if (flags_ & has_LF) {
                flags_ &= ~has_LF;
                return LF;
            } else {
                flags_ |= has_LF;
                return CR;
            }
        }
        return BOOST_IOSTREAMS_ASSERT_UNREACHABLE(0);
    }
    
    // Writes the given character, recording the fact that it is
    // not a newline.
    template<typename Sink>
    void non_newline(int_type c, Sink& snk)
    {
        flags_ &= ~line_complete;
        boost::iostreams::put(snk, c);
    }

    // Writes a newline sequence.
    template<typename Sink>
    void newline(Sink& snk) 
    { 
        using namespace newline;
        switch (flags_ & print_mask) {
        case print_CR: 
            boost::iostreams::put(snk, CR);
            break;
        case print_LF: 
            boost::iostreams::put(snk, LF);
            break;
        case print_CRLF:
            boost::iostreams::put(snk, CR);
            boost::iostreams::put(snk, LF);
            break;
        }
        flags_ |= line_complete;
    }
    enum {
        has_LF = 32768,
        has_CR = has_LF << 1,
        has_EOF = has_CR << 1,
        line_complete = has_EOF << 1,
        internal_mask = has_LF | has_CR | has_EOF | line_complete
    };
    int       flags_;
    int_type  next_;
};
BOOST_IOSTREAMS_PIPABLE(basic_newline_filter, 1)

typedef basic_newline_filter<char>     newline_filter;
typedef basic_newline_filter<wchar_t>  newline_wfilter;

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED
