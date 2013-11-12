/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    Copyright (c) 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "input_path.hpp"
#include "include_paths.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "quickbook.hpp" // For the include_path global (yuck)
#include <boost/foreach.hpp>
#include <boost/range/algorithm/replace.hpp>

namespace quickbook
{
    //
    // check_path
    //

    path_details check_path(value const& path, quickbook::state& state)
    {
        // Paths are encoded for quickbook 1.6+ and also xmlbase
        // values (technically xmlbase is a 1.6 feature, but that
        // isn't enforced as it's backwards compatible).
        //
        // Counter-intuitively: encoded == plain text here.

        std::string path_text = qbk_version_n >= 106u || path.is_encoded() ?
                path.get_encoded() : detail::to_s(path.get_quickbook());

        if(path_text.find('\\') != std::string::npos)
        {
            quickbook::detail::ostream* err;

            if (qbk_version_n >= 106u) {
                err = &detail::outerr(path.get_file(), path.get_position());
                ++state.error_count;
            }
            else {
                err = &detail::outwarn(path.get_file(), path.get_position());
            }

            *err << "Path isn't portable: '"
                << path_text
                << "'"
                << std::endl;

            boost::replace(path_text, '\\', '/');
        }

        return path_details(path_text, path_details::path);
    }

    //
    // Search include path
    //

    std::set<include_search_return> include_search(path_details const& details,
            quickbook::state& state, string_iterator pos)
    {
        std::set<include_search_return> result;

        fs::path path = detail::generic_to_path(details.value);

        // If the path is relative, try and resolve it.
        if (!path.has_root_directory() && !path.has_root_name())
        {
            fs::path local_path =
                state.current_file->path.parent_path() / path;

            // See if it can be found locally first.
            if (state.dependencies.add_dependency(local_path))
            {
                result.insert(include_search_return(
                    local_path,
                    state.filename_relative.parent_path() / path));
                return result;
            }

            BOOST_FOREACH(fs::path full, include_path)
            {
                full /= path;

                if (state.dependencies.add_dependency(full))
                {
                    result.insert(include_search_return(full, path));
                    return result;
                }
            }
        }
        else
        {
            if (state.dependencies.add_dependency(path)) {
                result.insert(include_search_return(path, path));
                return result;
            }
        }

        detail::outerr(state.current_file, pos)
            << "Unable to find file: "
            << details.value
            << std::endl;
        ++state.error_count;

        return result;
    }

    //
    // include_search_return
    //

    bool include_search_return::operator<(include_search_return const& other) const
    {
        if (filename_relative < other.filename_relative) return true;
        else if (other.filename_relative < filename_relative) return false;
        else return filename < other.filename;
    }
}
