// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/char_traits.hpp>

namespace boost { namespace iostreams {

template<typename Ch>
class basic_character {
private:
    typedef basic_character<Ch> my_type;
    struct eof_t { };
    struct would_block_t { };
    basic_character(eof_t) : val_(), flags_(f_eof) { }
    basic_character(would_block_t)
        : val_(), flags_(f_would_block)
        { }
public:
    basic_character() : val_() { }
    basic_character(Ch c) : val_(c), flags_(f_good) { }
    Ch value() const { return val_; }
    operator Ch() const { return val_; }
    static my_type eof() { return eof_t(); }
    static my_type would_block() { return would_block_t(); }
    friend bool good(my_type c) { return c.flags_ == f_good; }
    friend bool eof(my_type c) { return c.flags_ == f_eof; }
    friend bool would_block(my_type c) { return c.flags_ == f_would_block; }
private:
    enum flag { f_good, f_eof, f_would_block };
    Ch    val_;
    flag  flags_;
};

typedef basic_character<char>     character;
typedef basic_character<wchar_t>  wcharacter;

inline character eof() { return character::eof(); }
inline wcharacter weof() { return wcharacter::eof(); }
inline character would_block() { return character::eof(); }
inline wcharacter wwould_block() { return wcharacter::would_block(); }

template<typename Ch>
basic_character<Ch>
int_type_to_character(typename BOOST_IOSTREAMS_CHAR_TRAITS(Ch)::int_type i)
{
    typedef basic_character<char_type>              return_type;
    typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
    return !traits_type::eq_int_type(i, traits_type::eof()) ?
                traits_type::to_char_type(c) :
                return_type::eof();
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CHARACTER_HPP_INCLUDED
