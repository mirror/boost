/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_UTILS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

#include <string>
#include <iostream>
#include <boost/ref.hpp>
#include <boost/assert.hpp>

namespace quickbook { namespace detail
{
    template <typename Char>
    inline void
    print_char(Char ch, std::ostream& out)
    {
        switch (ch)
        {
            case '<': out << "&lt;";    break;
            case '>': out << "&gt;";    break;
            case '&': out << "&amp;";   break;
            case '"': out << "&quot;";  break;
            default:  out << ch;        break;
        }
    }

    template <typename Char>
    inline void
    print_space(Char ch, std::ostream& out)
    {
        switch (ch)
        {
            case ' ': out << "&nbsp;";  break;
            default:  out << ch;        break;
        }
    }

    template <typename Char>
    inline Char
    filter_identifier_char(Char ch)
    {
        if (!std::isalnum(ch))
            ch = '_';
        return std::tolower(ch);
    }

    template <typename Iterator>
    inline std::string
    make_identifier(Iterator const& first, Iterator const& last)
    {
        std::string out_name;
        for (Iterator i = first; i != last; ++i)
            out_name += filter_identifier_char(*i);
        return out_name;
    }

    template <typename T>
    struct var_wrapper
        : public ::boost::reference_wrapper<T>
    {
        typedef ::boost::reference_wrapper<T> parent;

        explicit inline var_wrapper(T& t) : parent(t) {}

        inline T& operator()() const { return parent::get(); }
    };

    template <typename T>
    inline var_wrapper<T>
    var(T& t)
    {
        return var_wrapper<T>(t);
    }

    // un-indent a code segment
    void unindent( std::string& program )
    {
        std::string::size_type const n = program.find_first_not_of(" \t");
        BOOST_ASSERT( std::string::npos != n );
        program.erase( 0, n );

        std::string::size_type pos = 0;
        while( std::string::npos != ( pos = program.find( '\n', pos ) ) )
        {
            if( std::string::npos == ( pos = program.find_first_not_of('\n', pos) ) )
            {
                break;
            }

            program.erase( pos, n );
        }
    }

    // remove the extension from a filename
    std::string
    remove_extension(std::string const& filename)
    {
        std::string::size_type const n = filename.find_last_of('.');
        return std::string(filename.begin(), filename.begin()+n);
    }
}}

#endif // BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

