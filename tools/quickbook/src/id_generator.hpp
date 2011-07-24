/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_QUICKBOOK_ID_GENERATOR_HPP)
#define BOOST_QUICKBOOK_ID_GENERATOR_HPP

#include "fwd.hpp"
#include <boost/unordered/unordered_map.hpp>
#include <deque>
#include <string>

namespace quickbook
{
    class string_ref;

    class id_generator
    {
    public:

        enum categories
        {
            explicit_id = 0,    // Explicitly given by user
            generated,          // Generated from source, e.g. table title
            numbered,           // Just used to avoid random docbook ids
            default_category
        };

    private:

        struct id;
        struct placeholder;
        typedef boost::unordered_map<std::string, id> placeholder_map;
        
        placeholder_map ids_;
        std::deque<placeholder> placeholders_;

    public:
        id_generator();
        ~id_generator();

        std::string add(std::string const& id, categories priority);

        std::string replace_placeholders(std::string const&);
        string_ref get(string_ref placeholder);
    };
}

#endif