/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "syntax_highlight.hpp"

namespace quickbook
{    
    std::string syntax_highlight(
        iterator first, iterator last,
        actions& escape_actions,
        std::string const& source_mode)
    {
        quickbook::collector temp;

        // print the code with syntax coloring
        if (source_mode == "c++")
        {
            cpp_highlight cpp_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, cpp_p);
        }
        else if (source_mode == "python")
        {
            python_highlight python_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, python_p);
        }
        else if (source_mode == "teletype")
        {
            teletype_highlight teletype_p(temp, escape_actions);
            boost::spirit::classic::parse(first, last, teletype_p);
        }
        else
        {
            BOOST_ASSERT(0);
        }

        std::string str;
        temp.swap(str);
        
        return str;
    }
}
