/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "./utils.hpp"
#include <cctype>
#include <boost/spirit/core.hpp>

namespace quickbook {
    extern bool ms_errors;
}

namespace quickbook { namespace detail
{
    void
    print_char(char ch, std::ostream& out)
    {
        switch (ch)
        {
            case '<': out << "&lt;";    break;
            case '>': out << "&gt;";    break;
            case '&': out << "&amp;";   break;
            case '"': out << "&quot;";  break;
            default:  out << ch;        break;
            // note &apos; is not included. see the curse of apos: 
            // http://fishbowl.pastiche.org/2003/07/01/the_curse_of_apos
        }
    }

    void
    print_string(std::basic_string<char> const& str, std::ostream& out)
    {
        for (std::string::const_iterator cur = str.begin();
            cur != str.end(); ++cur)
        {
            print_char(*cur, out);
        }
    }

    void
    print_space(char ch, std::ostream& out)
    {
        out << ch;
    }
    
    namespace
    {
        bool 
        find_empty_content_pattern(
            std::basic_string<char> const& str
          , std::string::size_type& pos
          , std::string::size_type& len)
        {
            using namespace boost::spirit;
            typedef std::basic_string<char>::const_iterator iter;
            for (iter i = str.begin(); i!=str.end(); ++i)
            {
                parse_info<iter> r = parse(i, str.end(), '>' >> +blank_p >> '<');
                if (r.hit)
                {
                    pos = i-str.begin();
                    len = r.length;
                    return true;
                }
            }

            return false;
        }
    }

    void
    convert_nbsp(std::basic_string<char>& str)
    {
        std::string::size_type pos;
        std::string::size_type len;
        while (find_empty_content_pattern(str, pos, len))
            str.replace(pos, len, ">&nbsp;<");
    }

    char
    filter_identifier_char(char ch)
    {
        if (!std::isalnum(static_cast<unsigned char>(ch)))
            ch = '_';
        return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    // un-indent a code segment
    void unindent(std::string& program)
    {
        std::string::size_type const start = program.find_first_not_of("\r\n");
        program.erase(0, start); // erase leading newlines

        std::string::size_type const n = program.find_first_not_of(" \t");
        BOOST_ASSERT(std::string::npos != n);
        program.erase(0, n);

        std::string::size_type pos = 0;
        while (std::string::npos != (pos = program.find_first_of("\r\n", pos)))
        {
            if (std::string::npos == (pos = program.find_first_not_of("\r\n", pos)))
            {
                break;
            }

            program.erase(pos, n);
        }
    }

    // remove the extension from a filename
    std::string
    remove_extension(std::string const& filename)
    {
        std::string::size_type const n = filename.find_last_of('.');
        if(std::string::npos == n)
        {
            return filename;
        }
        else
        {
            return std::string(filename.begin(), filename.begin()+n);
        }
    }

    std::string escape_uri(std::string uri)
    {
        for (std::string::size_type n = 0; n < uri.size(); ++n)
        {
            static char const mark[] = "-_.!~*'()?\\/";
            if((!std::isalnum(static_cast<unsigned char>(uri[n])) || 127 < static_cast<unsigned char>(uri[n]))
              && 0 == std::strchr(mark, uri[n]))
            {
                static char const hex[] = "0123456789abcdef";
                char escape[] = { hex[uri[n] / 16], hex[uri[n] % 16] };
                uri.insert(n + 1, escape, 2);
                uri[n] = '%';
                n += 2;
            }
        }
        return uri;
    }
    
    std::ostream & outerr(const std::string & file, int line)
    {
        if (ms_errors)
            return std::clog << file << "(" << line << "): error: ";
        else
            return std::clog << file << ":" << line << ": error: ";
    }
    
    std::ostream & outwarn(const std::string & file, int line)
    {
        if (ms_errors)
            return std::clog << file << "(" << line << "): warning: ";
        else
            return std::clog << file << ":" << line << ": warning: ";
    }
}}


