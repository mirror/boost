/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    Copyright (c) 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "native_text.hpp"
#include "glob.hpp"
#include "include_paths.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "quickbook.hpp" // For the include_path global (yuck)
#include <boost/foreach.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/filesystem/operations.hpp>
#include <cassert>

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

        bool is_glob = qbk_version_n >= 107u &&
            path_text.find_first_of("[]?*") != std::string::npos;

        if(!is_glob && path_text.find('\\') != std::string::npos)
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

        return path_parameter(path_text,
            is_glob ? path_parameter::glob : path_parameter::path);
    }

    //
    // Search include path
    //

    void include_search_glob(std::set<quickbook_path> & result,
        fs::path dir, std::string path, quickbook::state& state)
    {
        // Search for the first part of the path that contains glob
        // characters. (TODO: Account for escapes?)

        std::size_t glob_pos = path.find_first_of("[]?*");

        if (glob_pos == std::string::npos)
        {
            if (state.dependencies.add_dependency(dir / path))
            {
                result.insert(quickbook_path(
                    dir / path,
                    state.abstract_file_path.parent_path() / path));
            }
            return;
        }

        std::size_t prev = path.rfind('/', glob_pos);
        std::size_t next = path.find('/', glob_pos);

        std::size_t glob_begin = prev == std::string::npos ? 0 : prev + 1;
        std::size_t glob_end = next == std::string::npos ? path.size() : next;

        if (prev != std::string::npos)
            dir /= fs::path(path.substr(0, prev));

        if (next != std::string::npos) ++next;

        boost::string_ref glob(
                path.data() + glob_begin,
                glob_end - glob_begin);

        // Walk through the dir for matches.
        fs::directory_iterator dir_i(dir.empty() ? fs::path(".") : dir);
        fs::directory_iterator dir_e;
        for (; dir_i != dir_e; ++dir_i)
        {
            fs::path f = dir_i->path().filename();

            // Skip if the dir item doesn't match.
            if (!quickbook::glob(glob, detail::path_to_generic(f))) continue;

            // If it's a file we add it to the results.
            if (next == std::string::npos)
            {
                if (fs::is_regular_file(dir_i->status()))
                {
                    result.insert(quickbook_path(
                        dir/f,
                        state.abstract_file_path.parent_path()/dir/f
                        ));
                }
            }
            // If it's a matching dir, we recurse looking for more files.
            else
            {
                if (!fs::is_regular_file(dir_i->status()))
                {
                    include_search_glob(result, dir/f,
                            path.substr(next), state);
                }
            }
        }
    }

    std::set<quickbook_path> include_search(path_parameter const& parameter,
            quickbook::state& state, string_iterator pos)
    {
        std::set<quickbook_path> result;

        // If the path has some glob match characters
        // we do a discovery of all the matches..
        if (parameter.type == path_parameter::glob)
        {
            fs::path current = state.current_file->path.parent_path();

            // Search for the current dir accumulating to the result.
            include_search_glob(result, current, parameter.value, state);

            // Search the include path dirs accumulating to the result.
            BOOST_FOREACH(fs::path dir, include_path)
            {
                include_search_glob(result, dir, parameter.value, state);
            }

            // Done.
            return result;
        }
        else
        {
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

                // Search in each of the include path locations.
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
