/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    Copyright (c) 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_QUICKBOOK_INCLUDE_PATHS_HPP)
#define BOOST_QUICKBOOK_INCLUDE_PATHS_HPP

// Classes and functions for dealing with the values from include, import and
// xinclude elements.

#include "fwd.hpp"
#include "values.hpp"
#include <set>
#include <string>
#include <boost/filesystem/path.hpp>

namespace quickbook
{
    struct path_parameter {
        // Will possibly add 'url' and 'glob' to this list later:
        enum path_type { path };

        std::string value;
        path_type type;

        path_parameter(std::string const& value, path_type type) :
            value(value), type(type) {}
    };

    path_parameter check_path(value const& path, quickbook::state& state);

    struct include_search_return
    {
        include_search_return(fs::path const& x, fs::path const& y)
            : filename(x), filename_relative(y) {}

        fs::path filename;
        fs::path filename_relative;

        bool operator<(include_search_return const& other) const;
    };

    std::set<include_search_return> include_search(path_parameter const&,
            quickbook::state& state, string_iterator pos);
}

#endif
