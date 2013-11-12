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

    path_parameter check_path(value const& path, quickbook::state& state)
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

        return path_parameter(path_text, path_parameter::path);
    }

    //
    // Search include path
    //

    std::set<quickbook_path> include_search(
            path_parameter const& parameter,
            quickbook::state& state, string_iterator pos)
    {
        std::set<quickbook_path> result;

        fs::path path = detail::generic_to_path(parameter.value);

        // If the path is relative, try and resolve it.
        if (!path.has_root_directory() && !path.has_root_name())
        {
            fs::path local_path =
                state.current_file->path.parent_path() / path;

            // See if it can be found locally first.
            if (state.dependencies.add_dependency(local_path))
            {
                result.insert(quickbook_path(
                    local_path,
                    state.abstract_file_path.parent_path() / path));
                return result;
            }

            BOOST_FOREACH(fs::path full, include_path)
            {
                full /= path;

                if (state.dependencies.add_dependency(full))
                {
                    result.insert(quickbook_path(full, path));
                    return result;
                }
            }
        }
        else
        {
            if (state.dependencies.add_dependency(path)) {
                result.insert(quickbook_path(path, path));
                return result;
            }
        }

        detail::outerr(state.current_file, pos)
            << "Unable to find file: "
            << parameter.value
            << std::endl;
        ++state.error_count;

        return result;
    }

    //
    // quickbook_path
    //

    bool quickbook_path::operator<(quickbook_path const& other) const
    {
        if (abstract_file_path < other.abstract_file_path) return true;
        else if (other.abstract_file_path < abstract_file_path) return false;
        else return file_path < other.file_path;
    }
}
