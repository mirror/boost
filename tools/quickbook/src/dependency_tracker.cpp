/*=============================================================================
    Copyright (c) 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "dependency_tracker.hpp"
#include "input_path.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>

namespace quickbook
{
    // Convert the path to its canonical representation if it exists.
    // Or something close if it doesn't.
    static fs::path normalize_path(fs::path const& path)
    {
        fs::path p = fs::absolute(path); // The base of the path.
        fs::path extra; // The non-existant part of the path.
        int parent_count = 0; // Number of active '..' sections

        // Invariant: path is equivalent to: p / ('..' * parent_count) / extra
        // i.e. if parent_count == 0: p/extra
        // if parent_count == 2: p/../../extra

        // Pop path sections from path until we find an existing
        // path, adjusting for any dot path sections.
        while (!fs::exists(fs::status(p))) {
            fs::path name = p.filename();
            p = p.parent_path();
            if (name == "..") {
                ++parent_count;
            }
            else if (name == ".") {
            }
            else if (parent_count) {
                --parent_count;
            }
            else {
                extra = name / extra;
            }
        }

        // If there are any left over ".." sections, then add them
        // on to the end of the real path, and trust Boost.Filesystem
        // to sort them out.
        while (parent_count) {
            p = p / "..";
            --parent_count;
        }

        // Cannoicalize the existing part of the path, and add 'extra' back to
        // the end.
        return fs::canonical(p) / extra;
    }

    bool dependency_tracker::add_dependency(fs::path const& f) {
        bool found = fs::exists(fs::status(f));
        dependencies[normalize_path(f)] |= found;
        return found;
    }

    void dependency_tracker::write_dependencies(std::ostream& out)
    {
        BOOST_FOREACH(dependency_list::value_type const& d, dependencies)
        {
            if (d.second) {
                out << detail::path_to_generic(d.first) << std::endl;
            }
        }
    }

    void dependency_tracker::write_checked_locations(std::ostream& out)
    {
        BOOST_FOREACH(dependency_list::value_type const& d, dependencies)
        {
            out << (d.second ? "+ " : "- ")
                << detail::path_to_generic(d.first) << std::endl;
        }
    }
}
