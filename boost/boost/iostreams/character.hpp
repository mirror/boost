// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              
                       
#include <iostream>
#include <memory>    // allocator.
#include <vector> 
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/one_step_filter.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/streambuf_facade.hpp>

namespace boost { namespace iostreams {

namespace detail {

struct eof_t { };
struct would_block_t { };

} // End namespace detail.

template<typename Ch>
class basic_character {
private:
    struct safe_bool_helper { int x; };
    typedef int safe_bool_helper::*  safe_bool;
    typedef basic_character<Ch>      my_type;
public:
    basic_character(Ch c) : val_(c) { }
    Ch value() const { return val_; }
#if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    operator bool() const 
#else
    operator safe_bool() const 
#endif
    { 
        return flags_ == good_f ? &safe_bool_helper::x : 0;
    }
    friend bool good(my_type) const
    { 
        return flags_ == good_f ? &safe_bool_helper::x : 0;
    }
    friend bool eof(my_type) const
    { 
        return flags_ == eof_f ? &safe_bool_helper::x : 0;
    }
    friend bool would_block(my_type) const
    { 
        return flags_ == would_block_f ? &safe_bool_helper::x : 0;
    }
    friend bool operator==(my_type lhs, Ch rhs) const
    { 
        return lhs.flags_ == good_f ? lhs.val_ == rhs : false;
    }
    friend bool operator==(Ch lhs, my_type rhs) const
    { 
        return rhs.flags_ == good_f ? rhs.val_ == lhs : false;
    }
    friend bool operator==(my_type lhs, my_type rhs) const
    { 
        return rhs.flags_ == good_f ? 
            lhs.flags_ == good_f && lhs.val_ == rhs.val_ :
            lhs.flags_ == rhs.flags_;
    }
    friend bool operator!=(my_type lhs, Ch rhs) const
    { 
        return lhs.flags_ == good_f ? lhs.val_ != rhs : true;
    }
    friend bool operator!=(Ch lhs, my_type rhs) const
    { 
        return rhs.flags_ == good_f ? rhs.val_ != lhs : true;
    }
    friend bool operator!=(my_type lhs, my_type rhs) const
    { 
        return lhs.flags_ == good_f ? 
            lhs.flags_ != good_f || lhs.val_ != rhs.val_ :
            lhs.flags_ != rhs.flags_;
    }
// undef'd below. 
#define BOOST_CHARACTER_OP(op) \
    friend bool operator op (my_type lhs, Ch rhs) const \
    { return lhs.val_ op rhs; } \
    friend bool operator op (Ch lhs, my_type rhs) const \
    { return lhs op rhs.val_; } \
    friend bool operator op (my_type lhs, my_type rhs) const \
    { return lhs.val_ op rhs.val_; } \
    /**/
    BOOST_CHARACTER_OP(<)
    BOOST_CHARACTER_OP(<=)
    BOOST_CHARACTER_OP(>)
    BOOST_CHARACTER_OP(>=)
#undef BOOST_CHARACTER_OP
private:
    enum flag { good_f, eof_f, would_block_f };
    Ch    val_;
    flag  flags_;
};

typedef basic_character<char>     character;
typedef basic_character<wchar_t>  wcharacter;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED
