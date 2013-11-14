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
        if (qbk_version_n >= 107u) {
            std::string path_text = path.get_encoded();

            if (path_text.find("\\\\") != std::string::npos ||
                    path_text.find("\\/") != std::string::npos)
            {
                detail::outerr(path.get_file(), path.get_position())
                    << "Invalid path (contains escaped slash): "
                    << path_text
                   << std::endl;
                ++state.error_count;
                return path_parameter(path_text, path_parameter::invalid);
            }

            bool is_glob = path_text.find_first_of("[]?*") != std::string::npos;

            return path_parameter(path_text,
                is_glob ? path_parameter::glob : path_parameter::path);
        }
        else {
            // Paths are encoded for quickbook 1.6+ and also xmlbase
            // values (technically xmlbase is a 1.6 feature, but that
            // isn't enforced as it's backwards compatible).
            //
            // Counter-intuitively: encoded == plain text here.

            std::string path_text = qbk_version_n >= 106u || path.is_encoded() ?
                    path.get_encoded() : detail::to_s(path.get_quickbook());

            if (path_text.find('\\') != std::string::npos)
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
    }

    //
    // Search include path
    //

    void include_search_glob(std::set<quickbook_path> & result,
        quickbook_path const& location,
        std::string path, quickbook::state& state)
    {
        // Search for the first part of the path that contains glob
        // characters. (TODO: Account for escapes?)

        std::size_t glob_pos = path.find_first_of("[]?*");

        if (glob_pos == std::string::npos)
        {
            quickbook_path complete_path = location / path;

            if (fs::exists(complete_path.file_path))
            {
                state.dependencies.add_glob_match(complete_path.file_path);
                result.insert(complete_path);
            }
            return;
        }

        std::size_t prev = path.rfind('/', glob_pos);
        std::size_t next = path.find('/', glob_pos);

        std::size_t glob_begin = prev == std::string::npos ? 0 : prev + 1;
        std::size_t glob_end = next == std::string::npos ? path.size() : next;

        quickbook_path new_location = location;

        if (prev != std::string::npos) {
            new_location /= path.substr(0, prev);
        }

        if (next != std::string::npos) ++next;

        boost::string_ref glob(
                path.data() + glob_begin,
                glob_end - glob_begin);

        fs::path base_dir = new_location.file_path.empty() ?
            fs::path(".") : new_location.file_path;
        if (!fs::is_directory(base_dir)) return;

        // Walk through the dir for matches.
        for (fs::directory_iterator dir_i(base_dir), dir_e;
                dir_i != dir_e; ++dir_i)
        {
            fs::path f = dir_i->path().filename();
            std::string generic_path = detail::path_to_generic(f);

            // Skip if the dir item doesn't match.
            if (!quickbook::glob(glob, generic_path)) continue;

            // If it's a file we add it to the results.
            if (next == std::string::npos)
            {
                if (fs::is_regular_file(dir_i->status()))
                {
                    quickbook_path r = new_location / generic_path;
                    state.dependencies.add_glob_match(r.file_path);
                    result.insert(r);
                }
            }
            // If it's a matching dir, we recurse looking for more files.
            else
            {
                if (!fs::is_regular_file(dir_i->status()))
                {
                    include_search_glob(result, new_location / generic_path,
                            path.substr(next), state);
                }
            }
        }
    }

    std::set<quickbook_path> include_search(path_parameter const& parameter,
            quickbook::state& state, string_iterator pos)
    {
        std::set<quickbook_path> result;

        switch (parameter.type) {
            case path_parameter::glob:
            // If the path has some glob match characters
            // we do a discovery of all the matches..
            {
                fs::path current = state.current_file->path.parent_path();

                // Search for the current dir accumulating to the result.
                state.dependencies.add_glob(current / parameter.value);
                include_search_glob(result,
                        quickbook_path(current,
                            state.abstract_file_path.parent_path()),
                        parameter.value, state);

                // Search the include path dirs accumulating to the result.
                BOOST_FOREACH(fs::path dir, include_path)
                {
                    state.dependencies.add_glob(dir / parameter.value);
                    include_search_glob(result, quickbook_path(dir, fs::path()),
                            parameter.value, state);
                }

                // Done.
                return result;
            }

            case path_parameter::path:
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

            case path_parameter::invalid:
                return result;

            default:
                assert(0);
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

    quickbook_path quickbook_path::operator/(boost::string_ref x) const
    {
        return quickbook_path(*this) /= x;
    }

    quickbook_path& quickbook_path::operator/=(boost::string_ref x)
    {
        file_path.append(x.begin(), x.end());
        abstract_file_path.append(x.begin(), x.end());
        return *this;
    }
}
