/*=============================================================================
    Copyright (c) 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "glob.hpp"
#include <cassert>

namespace quickbook
{
    typedef boost::string_ref::const_iterator glob_iterator;

    bool match_section(glob_iterator& pattern_begin, glob_iterator pattern_end,
            glob_iterator& filename_begin, glob_iterator& filename_end);
    bool match_range(glob_iterator& pattern_begin, glob_iterator pattern_end,
            unsigned char x);

    bool glob(boost::string_ref const& pattern,
            boost::string_ref const& filename)
    {
        // If there wasn't this special case then '*' would match an
        // empty string.
        if (filename.empty()) return pattern.empty();

        glob_iterator pattern_it = pattern.begin();
        glob_iterator pattern_end = pattern.end();

        glob_iterator filename_it = filename.begin();
        glob_iterator filename_end = filename.end();

        if (!match_section(pattern_it, pattern_end, filename_it, filename_end))
            return false;

        while (pattern_it != pattern_end) {
            assert(*pattern_it == '*');
            ++pattern_it;
            if (pattern_it == pattern_end) return true;

            // TODO: Error?
            if (*pattern_it == '*') return false;

            while (true) {
                if (filename_it == filename_end) return false;
                if (match_section(pattern_it, pattern_end, filename_it, filename_end))
                    break;
                ++filename_it;
            }
        }

        return filename_it == filename_end;
    }

    bool match_section(glob_iterator& pattern_begin, glob_iterator pattern_end,
            glob_iterator& filename_begin, glob_iterator& filename_end)
    {
        glob_iterator pattern_it = pattern_begin;
        glob_iterator filename_it = filename_begin;

        while (pattern_it != pattern_end && *pattern_it != '*') {
            if (filename_it == filename_end) return false;

            switch(*pattern_it) {
                case '*':
                    assert(false);
                    return false;
                case '[':
                    if (!match_range(pattern_it, pattern_end, *filename_it))
                        return false;
                    ++filename_it;
                    break;
                case '?':
                    ++pattern_it;
                    ++filename_it;
                    break;
                case '\\':
                    ++pattern_it;
                    if (pattern_it == pattern_end) return false;
                    BOOST_FALLTHROUGH;
                default:
                    if (*pattern_it != *filename_it) return false;
                    ++pattern_it;
                    ++filename_it;
            }
        }

        if (pattern_it == pattern_end && filename_it != filename_end)
            return false;

        pattern_begin = pattern_it;
        filename_begin = filename_it;
        return true;
    }

    bool match_range(glob_iterator& pattern_begin, glob_iterator pattern_end,
            unsigned char x)
    {
        assert(pattern_begin != pattern_end && *pattern_begin == '[');
        ++pattern_begin;
        if (pattern_begin == pattern_end) return false;

        bool invert_match = false;
        bool matched = false;

        if (*pattern_begin == '^') {
            invert_match = true;
            ++pattern_begin;
            if (pattern_begin == pattern_end) return false;
        }

        // Search for a match
        while (true) {
            unsigned char first = *pattern_begin;
            ++pattern_begin;
            if (first == ']') break;
            if (pattern_begin == pattern_end) return false;

            if (first == '\\') {
                first = *pattern_begin;
                ++pattern_begin;
                if (pattern_begin == pattern_end) return false;
            }

            if (*pattern_begin != '-') {
                matched = matched || (first == x);
            }
            else {
                ++pattern_begin;
                if (pattern_begin == pattern_end) return false;

                unsigned char second = *pattern_begin;
                ++pattern_begin;
                if (second == ']') {
                    matched = matched || (first == x) || (x == '-');
                    break;
                }
                if (pattern_begin == pattern_end) return false;

                if (second == '\\') {
                    second = *pattern_begin;
                    ++pattern_begin;
                    if (pattern_begin == pattern_end) return false;
                }

                // TODO: What if second < first?
                matched = matched || (first <= x && x <= second);
            }
        }

        return invert_match != matched;
    }
}
