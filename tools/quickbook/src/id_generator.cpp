/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "id_generator.hpp"
#include "markups.hpp"
#include "phrase_tags.hpp"
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <vector>

namespace quickbook
{
    // string_ref

    struct string_ref
    {
    public:
        typedef std::string::const_iterator iterator;

    private:
        iterator begin_, end_;

    public:
        string_ref() : begin_(), end_() {}

        explicit string_ref(iterator b, iterator e)
            : begin_(b), end_(e) {}

        explicit string_ref(std::string const& x)
            : begin_(x.begin()), end_(x.end()) {}

        iterator begin() const { return begin_; }
        iterator end() const { return end_; }
        
        std::size_t size() const
        {
            return static_cast<std::size_t>(end_ - begin_);
        }    
    };

    bool operator==(string_ref const& x, string_ref const& y);
    bool operator<(string_ref const& x, string_ref const& y);

    inline bool operator==(string_ref const& x, std::string const& y)
    {
        return x == string_ref(y);
    }

    inline bool operator==(std::string const& x, string_ref const& y)
    {
        return string_ref(x) == y;
    }

    inline bool operator<(string_ref const& x, std::string const& y)
    {
        return x < string_ref(y);
    }

    inline bool operator<(std::string const& x, string_ref const& y)
    {
        return string_ref(x) < y;
    }

    bool operator==(string_ref const& x, string_ref const& y)
    {
        return x.size() == y.size() &&
            std::equal(x.begin(), x.end(), y.begin());
    }

    bool operator<(string_ref const& x, string_ref const& y)
    {
        return std::lexicographical_compare(
            x.begin(), x.end(), y.begin(), y.end());
    }

    // id_generator

    struct id_generator::id
    {
        id()
          : category(id_generator::default_category),
            used(false),
            count(0) {}
    
        id_generator::categories category;

        // These are updated when generating ids
        bool used;
        int count;
    };

    id_generator::id_generator()
    {
    }

    id_generator::~id_generator()
    {
    }

    std::string id_generator::add(
            std::string const& value,
            id_generator::categories category)
    {
        std::string result;
        id_generator::id& id = ids_[value];

        // Doesn't check if explicit ids collide, could probably be a warning.
        if (category == explicit_id)
        {
            id.category = category;
            id.used = true;
            result = value;
        }
        else
        {
            if (category < id.category) id.category = category;

            // '$' can't appear in quickbook ids, so use it indicate a
            // placeholder id.
            result = "$" +
                boost::lexical_cast<std::string>(placeholders_.size());
            placeholders_.push_back(
                id_generator::placeholder(category, *ids_.find(value)));
        }

        return result;
    }

    string_ref id_generator::get(string_ref value)
    {
        // If this isn't a placeholder id. 
        if (value.size() <= 1 || *value.begin() != '$')
            return value;

        id_generator::placeholder& placeholder = placeholders_.at(
            boost::lexical_cast<int>(std::string(
                value.begin() + 1, value.end())));

        if (placeholder.final_id.empty())
        {
            if (placeholder.category < id_generator::numbered &&
                    !placeholder.id.second.used &&
                    placeholder.id.second.category == placeholder.category)
            {
                placeholder.id.second.used = true;
                placeholder.final_id = placeholder.id.first;
            }
            else while(true)
            {
                int count = placeholder.id.second.count++;
                placeholder.final_id = placeholder.id.first +
                    boost::lexical_cast<std::string>(count);
                // TODO: Should add final_id to ids_, there are some
                // edges cases where it could collide.
                if (ids_.find(placeholder.final_id) == ids_.end())
                    break;
            }
        }

        return string_ref(placeholder.final_id);
    }

    // Very simple xml subset parser which replaces id values.
    //
    // I originally tried to integrate this into the post processor
    // but that proved tricky. Alternatively it could use a proper
    // xml parser, but I want this to be able to survive badly
    // marked up escapes.

    struct xml_processor
    {
        xml_processor();
    
        std::string escape_prefix;
        std::string escape_postfix;
        std::string processing_instruction_postfix;
        std::string comment_postfix;
        std::string whitespace;
        std::string tag_end;
        std::string name_end;
        std::string attribute_assign;
        std::vector<std::string> id_attributes;
        
        std::string replace(std::string const&, id_generator&);
    };

    std::string id_generator::replace_placeholders(std::string const& source)
    {
        xml_processor processor;
        return processor.replace(source, *this);
    }

    namespace
    {
        char const* id_attributes_[] =
        {
            "id",
            "linkend",
            "linkends",
            "arearefs"
        };
    }

    xml_processor::xml_processor()
        : escape_prefix("<!--quickbook-escape-prefix-->")
        , escape_postfix("<!--quickbook-escape-postfix-->")
        , processing_instruction_postfix("?>")
        , comment_postfix("-->")
        , whitespace(" \t\n\r")
        , tag_end(" \t\n\r>")
        , name_end("= \t\n\r>")
        , attribute_assign("= \t\n\r")
    {
        static int const n_id_attributes = sizeof(id_attributes_)/sizeof(char const*);
        for (int i = 0; i != n_id_attributes; ++i)
        {
            id_attributes.push_back(id_attributes_[i]);
        }

        std::sort(id_attributes.begin(), id_attributes.end());
    }

    std::string xml_processor::replace(std::string const& source, id_generator& ids)
    {
        std::string result;

        typedef std::string::const_iterator iterator;

        // copied is the point up to which the source has been copied, or
        // replaced, to result.
        iterator copied = source.begin();

        iterator end = source.end();

        for(iterator it = copied; it != end; it = std::find(it, end, '<'))
        {
            assert(copied <= it && it <= end);        

            if (static_cast<std::size_t>(end - it) > escape_prefix.size() &&
                    std::equal(escape_prefix.begin(), escape_prefix.end(), it))
            {
                it = std::search(it + escape_prefix.size(), end,
                    escape_postfix.begin(), escape_postfix.end());

                if (it == end) break;

                it += escape_postfix.size();
                continue;
            }

            ++it;
            if (it == end) break;

            switch(*it)
            {
            case '?':
                it = std::search(it, end,
                    processing_instruction_postfix.begin(),
                    processing_instruction_postfix.end());
                break;

            case '!':
                if (end - it > 3 && it[1] == '-' && it[2] == '-')
                {
                    it = std::search(it + 3, end,
                        comment_postfix. begin(), comment_postfix.end());
                    if (it != end) it += comment_postfix.size();
                }
                else
                {
                    it = std::find(it, end, '>');
                }
                break;

            default:
                if ((*it >= 'a' && *it <= 'z') ||
                        (*it >= 'A' && *it <= 'Z') ||
                        *it == '_' || *it == ':')
                {
                    it = std::find_first_of(
                        it + 1, end, tag_end.begin(), tag_end.end());

                    while (true) {
                        while(it != end &&
                                std::find(whitespace.begin(),
                                    whitespace.end(), *it)
                                != whitespace.end())
                            ++it;
                            
                        iterator name_start = it;

                        it = std::find_first_of(
                            it, end, name_end.begin(), name_end.end());
                        
                        if (it == end || *it == '>') break;

                        string_ref name(name_start, it);
                        ++it;

                        while (it != end &&
                                std::find(attribute_assign.begin(),
                                    attribute_assign.end(), *it)
                                != attribute_assign.end())
                            ++it;

                        if (it == end || (*it != '"' && *it != '\'')) break;

                        char delim = *it;
                        ++it;

                        iterator value_start = it;

                        it = std::find(it, end, delim);
                        string_ref value(value_start, it);
                        if (it == end) break;
                        ++it;

                        if (std::find(id_attributes.begin(), id_attributes.end(),
                                    name)
                                != id_attributes.end())
                        {
                            result.append(copied, value.begin());
                            string_ref x = ids.get(value);
                            result.append(x.begin(), x.end());
                            copied = value.end();
                        }
                    }
                }
                else
                {
                    it = std::find(it, end, '>');
                }
            }
        }
        
        result.append(copied, source.end());
        return result;
    }
}
