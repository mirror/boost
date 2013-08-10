/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "id_manager.hpp"
#include "utils.hpp"
#include <boost/utility/string_ref.hpp>
#include <boost/make_shared.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <deque>
#include <vector>
#include <cctype>

namespace quickbook
{
    // TODO: This should possibly try to always generate valid XML ids:
    // http://www.w3.org/TR/REC-xml/#NT-NameStartChar

    //
    // Forward declarations
    //

    struct id_placeholder;
    struct id_data;
    std::string replace_ids(id_state& state, boost::string_ref xml,
            std::vector<std::string> const* = 0);
    std::vector<std::string> generate_ids(id_state&, boost::string_ref);

    static const std::size_t max_size = 32;

    // id_placeholder
    //
    // When generating the xml, quickbook can't allocate the identifiers until
    // the end, so it stores in the intermedia xml a placeholder string,
    // e.g. id="$1". This represents one of these placeholders.
    //

    struct id_placeholder
    {
        unsigned index;         // The index in id_state::placeholders.
                                // Use for the dollar identifiers in
                                // intermediate xml.
        std::string unresolved_id;
                                // The id that would be generated
                                // without any duplicate handling.
                                // Used for generating old style header anchors.
        std::string id;         // The node id.
        id_placeholder* parent; // Placeholder of the parent id.
        id_category category;
        unsigned num_dots;      // Number of dots in the id.
                                // Normally equal to the section level
                                // but not when an explicit id contains
                                // dots.

        id_placeholder(
                unsigned index,
                boost::string_ref id,
                id_category category,
                id_placeholder* parent_ = 0)
          : index(index),
            unresolved_id(parent_ ?
                parent_->unresolved_id + '.' + detail::to_s(id) :
                detail::to_s(id)),
            id(id.begin(), id.end()),
            parent(parent_),
            category(category),
            num_dots(boost::range::count(id, '.') +
                (parent_ ? parent_->num_dots + 1 : 0))
        {
        }

        std::string to_string()
        {
            return '$' + boost::lexical_cast<std::string>(index);
        }
    };

    //
    // id_state
    //
    // Contains all the data tracked by the id_manager.
    //

    struct file_info;
    struct doc_info;
    struct section_info;

    struct id_state
    {
        boost::shared_ptr<file_info> current_file;
        std::deque<id_placeholder> placeholders;

        // Placeholder methods

        id_placeholder* add_placeholder(boost::string_ref, id_category,
            id_placeholder* parent = 0);

        id_placeholder* get_placeholder(boost::string_ref);

        id_placeholder* get_id_placeholder(
                boost::shared_ptr<section_info> const& section) const;

        // Events

        id_placeholder* start_file(
                unsigned compatibility_version,
                bool document_root,
                boost::string_ref include_doc_id,
                boost::string_ref id,
                value const& title);

        void end_file();

        id_placeholder* add_id(
                boost::string_ref id,
                id_category category);
        id_placeholder* old_style_id(
            boost::string_ref id,
            id_category category);
        id_placeholder* begin_section(
                boost::string_ref id,
                id_category category);
        void end_section();

    private:
        id_placeholder* add_id_to_section(
                boost::string_ref id,
                id_category category,
                boost::shared_ptr<section_info> const& section);
        id_placeholder* create_new_section(
                boost::string_ref id,
                id_category category);
    };

    struct file_info
    {
        boost::shared_ptr<file_info> parent;
        boost::shared_ptr<doc_info> document;

        bool document_root; // !parent || document != parent->document
        unsigned compatibility_version;
        unsigned depth;
        unsigned override_depth;
        id_placeholder* override_id;

        // The 1.1-1.5 document id would actually change per file due to
        // explicit ids in includes and a bug which would sometimes use the
        // document title instead of the id.
        std::string doc_id_1_1;

        file_info(boost::shared_ptr<file_info> const& parent,
                unsigned compatibility_version) :
            parent(parent), document(parent->document), document_root(false),
            compatibility_version(compatibility_version),
            depth(parent->depth + 1),
            override_depth(parent->override_depth),
            override_id(parent->override_id)
        {}

        file_info(boost::shared_ptr<file_info> const& parent,
                boost::shared_ptr<doc_info> const& document,
                unsigned compatibility_version) :
            parent(parent), document(document), document_root(true),
            compatibility_version(compatibility_version),
            depth(0), override_depth(0), override_id(0)
        {}
    };

    struct doc_info
    {
        boost::shared_ptr<section_info> current_section;
        std::string last_title_1_1;
        std::string section_id_1_1;

        doc_info() :
            current_section(), last_title_1_1(), section_id_1_1()
        {}
    };

    struct section_info
    {
        boost::shared_ptr<section_info> parent;
        unsigned compatibility_version;
        unsigned file_depth;
        unsigned level;
        std::string id_1_1;
        id_placeholder* placeholder_1_6;

        section_info(boost::shared_ptr<section_info> const& parent,
                file_info const* current_file, boost::string_ref id) :
            parent(parent),
            compatibility_version(current_file->compatibility_version),
            file_depth(current_file->depth),
            level(parent ? parent->level + 1 : 1),
            id_1_1(), placeholder_1_6(0)
        {
            if (parent && compatibility_version < 106u) {
                id_1_1 = parent->id_1_1;
                if (!id_1_1.empty() && !id.empty())
                    id_1_1 += ".";
                id_1_1.append(id.begin(), id.end());
            }
        }
    };

    //
    // id_manager
    //

    id_manager::id_manager()
      : state(new id_state)
    {
    }

    id_manager::~id_manager() {}

    void id_manager::start_file(
            unsigned compatibility_version,
            boost::string_ref include_doc_id,
            boost::string_ref id,
            value const& title)
    {
        state->start_file(compatibility_version, false, include_doc_id, id, title);
    }

    std::string id_manager::start_file_with_docinfo(
            unsigned compatibility_version,
            boost::string_ref include_doc_id,
            boost::string_ref id,
            value const& title)
    {
        return state->start_file(compatibility_version, true, include_doc_id,
            id, title)->to_string();
    }

    void id_manager::end_file()
    {
        state->end_file();
    }

    std::string id_manager::begin_section(boost::string_ref id,
            id_category category)
    {
        return state->begin_section(id, category)->to_string();
    }

    void id_manager::end_section()
    {
        return state->end_section();
    }

    int id_manager::section_level() const
    {
        return state->current_file->document->current_section->level;
    }

    std::string id_manager::old_style_id(boost::string_ref id, id_category category)
    {
        return state->old_style_id(id, category)->to_string();
    }

    std::string id_manager::add_id(boost::string_ref id, id_category category)
    {
        return state->add_id(id, category)->to_string();
    }

    std::string id_manager::add_anchor(boost::string_ref id, id_category category)
    {
        return state->add_placeholder(id, category)->to_string();
    }

    std::string id_manager::replace_placeholders_with_unresolved_ids(
            boost::string_ref xml) const
    {
        return replace_ids(*state, xml);
    }

    std::string id_manager::replace_placeholders(boost::string_ref xml) const
    {
        assert(!state->current_file);
        std::vector<std::string> ids = generate_ids(*state, xml);
        return replace_ids(*state, xml, &ids);
    }

    unsigned id_manager::compatibility_version() const
    {
        return state->current_file->compatibility_version;
    }

    //
    // normalize_id
    //
    // Normalizes generated ids.
    //

    namespace
    {
        std::string normalize_id(
                boost::string_ref src_id,
                std::size_t prefix = 0,
                std::size_t size = max_size)
        {
            std::string id(src_id.begin(), src_id.end());

            std::size_t src = prefix;
            std::size_t dst = prefix;
            size += prefix;

            if (src >= id.length()) {
                return id;
            }

            while (src < id.length() && id[src] == '_') {
                ++src;
            }

            if (src >= id.length()) {
                id += '_';
                return id;
            }

            while (src < id.length() && dst < size) {
                if (id[src] == '_') {
                    do {
                        ++src;
                    } while(src < id.length() && id[src] == '_');

                    if (src < id.length()) id[dst++] = '_';
                }
                else {
                    id[dst++] = id[src++];
                }
            }

            id.erase(dst);

            return id;
        }
    }

    //
    // id_state
    //

    id_placeholder* id_state::add_placeholder(
            boost::string_ref id, id_category category,
            id_placeholder* parent)
    {
        placeholders.push_back(id_placeholder(
            placeholders.size(), id, category, parent));
        return &placeholders.back();
    }

    id_placeholder* id_state::get_placeholder(boost::string_ref value)
    {
        // If this isn't a placeholder id.
        if (value.size() <= 1 || *value.begin() != '$')
            return 0;

        unsigned index = boost::lexical_cast<int>(std::string(
                value.begin() + 1, value.end()));

        return &placeholders.at(index);
    }

    id_placeholder* id_state::get_id_placeholder(
            boost::shared_ptr<section_info> const& section) const
    {
        return !section ? 0 :
            section->file_depth < current_file->override_depth ?
                current_file->override_id : section->placeholder_1_6;
    }

    id_placeholder* id_state::start_file(
            unsigned compatibility_version,
            bool document_root,
            boost::string_ref include_doc_id,
            boost::string_ref id,
            value const& title)
    {
        // Create new file

        boost::shared_ptr<file_info> parent = current_file;

        if (document_root) {
            current_file = boost::make_shared<file_info>(parent,
                    boost::make_shared<doc_info>(),
                    compatibility_version);
        }
        else {
            current_file =
                boost::make_shared<file_info>(parent, compatibility_version);
        }

        // Choose specified id to use. Prefer 'include_doc_id' (the id
        // specified in an 'include' element) unless backwards compatibility
        // is required.

        boost::string_ref initial_doc_id;

        if (document_root ||
            compatibility_version >= 106u ||
            (parent && parent->compatibility_version >= 106u))
        {
            initial_doc_id = !include_doc_id.empty() ? include_doc_id : id;
        }
        else {
            initial_doc_id = !id.empty() ? id : include_doc_id;
        }

        // Set variables used for backwards compatible id generation.
        // They're a bit odd because of old bugs.

        if (document_root || compatibility_version < 106u) {
            // Note: this is done for older versions even if docinfo is
            // otherwise ignored.

            if (title.check())
                current_file->document->last_title_1_1 =
                    detail::to_s(title.get_quickbook());

            current_file->doc_id_1_1 = !initial_doc_id.empty() ? detail::to_s(initial_doc_id) :
                detail::make_identifier(current_file->document->last_title_1_1);
        }
        else if (parent) {
            current_file->doc_id_1_1 = parent->doc_id_1_1;
        }

        if (document_root) {
            if (!initial_doc_id.empty()) {
                return create_new_section(id, id_category::explicit_section_id);
            }
            else if (!title.empty()) {
                return create_new_section(
                    detail::make_identifier(title.get_quickbook()),
                    id_category::generated_doc);
            }
            else if (compatibility_version >= 106u) {
                return create_new_section("doc", id_category::numbered);
            }
            else {
                return create_new_section("", id_category::generated_doc);
            }
        }
        else {
            // If an id was set for the file, then the file overrides the
            // current section's id with this id.

            if (compatibility_version >= 106u && !initial_doc_id.empty()) {
                boost::shared_ptr<section_info> null_section;

                current_file->override_depth = current_file->depth;
                current_file->override_id = add_id_to_section(initial_doc_id,
                    id_category::explicit_section_id, null_section);
            }

            return 0;
        }
    }

    void id_state::end_file()
    {
        current_file = current_file->parent;
    }

    id_placeholder* id_state::add_id(
            boost::string_ref id,
            id_category category)
    {
        return add_id_to_section(id, category,
            current_file->document->current_section);
    }

    id_placeholder* id_state::add_id_to_section(
            boost::string_ref id,
            id_category category,
            boost::shared_ptr<section_info> const& section)
    {
        std::string id_part(id.begin(), id.end());

        // Note: Normalizing id according to file compatibility version, but
        // adding to section according to section compatibility version.

        if (current_file->compatibility_version >= 106u &&
                category.c < id_category::explicit_id) {
            id_part = normalize_id(id);
        }

        id_placeholder* placeholder_1_6 = get_id_placeholder(section);

        if(!section || section->compatibility_version >= 106u) {
            return add_placeholder(id_part, category, placeholder_1_6);
        }
        else {
            std::string const& qualified_id = section->id_1_1;

            std::string new_id;
            if (!placeholder_1_6)
                new_id = current_file->doc_id_1_1;
            if (!new_id.empty() && !qualified_id.empty()) new_id += '.';
            new_id += qualified_id;
            if (!new_id.empty() && !id_part.empty()) new_id += '.';
            new_id += id_part;

            return add_placeholder(new_id, category, placeholder_1_6);
        }
    }

    id_placeholder* id_state::old_style_id(
        boost::string_ref id,
        id_category category)
    {
        return current_file->compatibility_version < 103u ?
            add_placeholder(
                current_file->document->section_id_1_1 + "." + detail::to_s(id), category) :
                add_id(id, category);
    }

    id_placeholder* id_state::begin_section(
            boost::string_ref id,
            id_category category)
    {
        current_file->document->section_id_1_1 = detail::to_s(id);
        return create_new_section(id, category);
    }

    id_placeholder* id_state::create_new_section(
            boost::string_ref id,
            id_category category)
    {
        boost::shared_ptr<section_info> parent =
            current_file->document->current_section;

        boost::shared_ptr<section_info> new_section =
            boost::make_shared<section_info>(parent,
                current_file.get(), id);

        id_placeholder* p;

        if (new_section->compatibility_version >= 106u) {
            p = add_id_to_section(id, category, parent);
            new_section->placeholder_1_6 = p;
        }
        else if (new_section->compatibility_version >= 103u) {
            new_section->placeholder_1_6 = get_id_placeholder(parent);

            std::string new_id;
            if (!new_section->placeholder_1_6) {
                new_id = current_file->doc_id_1_1;
                if (!new_section->id_1_1.empty()) new_id += '.';
            }
            new_id += new_section->id_1_1;

            p = add_placeholder(new_id, category,
                new_section->placeholder_1_6);
        }
        else {
            new_section->placeholder_1_6 = get_id_placeholder(parent);

            std::string new_id;
            if (parent && !new_section->placeholder_1_6)
                new_id = current_file->doc_id_1_1 + '.';

            new_id += detail::to_s(id);

            p = add_placeholder(new_id, category,
                new_section->placeholder_1_6);
        }

        current_file->document->current_section = new_section;
        
        return p;
    }

    void id_state::end_section()
    {
        boost::shared_ptr<section_info> popped_section =
            current_file->document->current_section;
        current_file->document->current_section = popped_section->parent;
    }

    //
    // Xml subset parser used for finding id values.
    //
    // I originally tried to integrate this into the post processor
    // but that proved tricky. Alternatively it could use a proper
    // xml parser, but I want this to be able to survive badly
    // marked up escapes.
    //

    struct xml_processor
    {
        xml_processor();

        std::vector<std::string> id_attributes;

        struct callback {
            virtual void start(boost::string_ref) {}
            virtual void id_value(boost::string_ref) {}
            virtual void finish(boost::string_ref) {}
            virtual ~callback() {}
        };

        void parse(boost::string_ref, callback&);
    };

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
    {
        static int const n_id_attributes = sizeof(id_attributes_)/sizeof(char const*);
        for (int i = 0; i != n_id_attributes; ++i)
        {
            id_attributes.push_back(id_attributes_[i]);
        }

        boost::sort(id_attributes);
    }

    template <typename Iterator>
    bool read(Iterator& it, Iterator end, char const* text)
    {
        for(Iterator it2 = it;; ++it2, ++text) {
            if (!*text) {
                it = it2;
                return true;
            }

            if (it2 == end || *it2 != *text)
                return false;
        }
    }

    template <typename Iterator>
    void read_past(Iterator& it, Iterator end, char const* text)
    {
        while (it != end && !read(it, end, text)) ++it;
    }

    bool find_char(char const* text, char c)
    {
        for(;*text; ++text)
            if (c == *text) return true;
        return false;
    }

    template <typename Iterator>
    void read_some_of(Iterator& it, Iterator end, char const* text)
    {
        while(it != end && find_char(text, *it)) ++it;
    }

    template <typename Iterator>
    void read_to_one_of(Iterator& it, Iterator end, char const* text)
    {
        while(it != end && !find_char(text, *it)) ++it;
    }

    void xml_processor::parse(boost::string_ref source, callback& c)
    {
        typedef boost::string_ref::const_iterator iterator;

        c.start(source);

        iterator it = source.begin(), end = source.end();

        for(;;)
        {
            read_past(it, end, "<");
            if (it == end) break;

            if (read(it, end, "!--quickbook-escape-prefix-->"))
            {
                read_past(it, end, "<!--quickbook-escape-postfix-->");
                continue;
            }

            switch(*it)
            {
            case '?':
                ++it;
                read_past(it, end, "?>");
                break;

            case '!':
                if (read(it, end, "!--"))
                    read_past(it, end, "-->");
                else
                    read_past(it, end, ">");
                break;

            default:
                if ((*it >= 'a' && *it <= 'z') ||
                        (*it >= 'A' && *it <= 'Z') ||
                        *it == '_' || *it == ':')
                {
                    read_to_one_of(it, end, " \t\n\r>");

                    for (;;) {
                        read_some_of(it, end, " \t\n\r");
                        iterator name_start = it;
                        read_to_one_of(it, end, "= \t\n\r>");
                        if (it == end || *it == '>') break;
                        boost::string_ref name(name_start, it - name_start);
                        ++it;

                        read_some_of(it, end, "= \t\n\r");
                        if (it == end || (*it != '"' && *it != '\'')) break;

                        char delim = *it;
                        ++it;

                        iterator value_start = it;

                        it = std::find(it, end, delim);
                        if (it == end) break;
                        boost::string_ref value(value_start, it - value_start);
                        ++it;

                        if (boost::find(id_attributes, detail::to_s(name))
                                != id_attributes.end())
                        {
                            c.id_value(value);
                        }
                    }
                }
                else
                {
                    read_past(it, end, ">");
                }
            }
        }

        c.finish(source);
    }

    //
    // generate_ids
    //

    //
    // Data used for generating placeholders that have duplicates.
    //

    struct id_generation_data
    {
        id_generation_data(boost::string_ref src_id)
          : child_start(src_id.rfind('.') + 1),
            id(normalize_id(src_id, child_start, max_size - 1)),
                // 'max_size - 1' leaves a character to append
                // a number.
            count(0)
        {
            if (std::isdigit(id[id.length() - 1]))
            {
                if (child_length() < max_size - 1)
                    id += '_';
                else
                    reduce_id();
            }
        }

        void reduce_id()
        {
            assert(id.length() > child_start);
            std::size_t length = id.length() - 1;
            while(length > child_start && std::isdigit(id[length - 1])) --length;
            id.erase(length);
            count = 0;
        }

        std::size_t child_length() const
        {
            return id.length() - child_start;
        }

        std::size_t child_start;
        std::string id;
        int count;
    };

    // Created for all desired ids, either when resolving an id or due to
    // generating a new id to avoid duplicates.
    struct id_data
    {
        id_data()
          : category(id_category::numbered),
            used(false),
            generation_data()
        {}

        void update_category(id_category c)
        {
            if (c.c > category.c) category = c;
        }

        id_category category;   // The highest priority category of the
                                // placeholders that want to use this id.
        bool used;              // Whether this id has been used.
        boost::shared_ptr<id_generation_data> generation_data;
                                // If a duplicates are found, this is
                                // created to generate new ids.
                                //
                                // Many to one relationship, because truncation
                                // can lead to different ids contending for the
                                // same id prefix.
    };

    struct placeholder_generation_data
    {
        placeholder_generation_data() : resolved_id(), data(0) {}

        std::string resolved_id;
        id_data* data;
    };

    typedef boost::unordered_map<std::string, id_data> allocated_ids;
    typedef std::vector<placeholder_generation_data> placeholder_data;
    typedef std::vector<id_placeholder*> placeholder_index;

    placeholder_index index_placeholders(id_state&, boost::string_ref xml);
    void resolve_id(id_placeholder&, std::vector<std::string> const&,
        allocated_ids&, placeholder_data& data);
    std::string generate_id(id_placeholder&, allocated_ids&, placeholder_data& data);

    std::vector<std::string> generate_ids(id_state& state, boost::string_ref xml)
    {
        std::vector<std::string> generated_ids(state.placeholders.size());

        // Get a list of the placeholders in the order that we wish to
        // process them.
        placeholder_index placeholders = index_placeholders(state, xml);

        typedef std::vector<id_placeholder*>::iterator iterator;

        iterator it = placeholders.begin(),
            end = placeholders.end();

        while (it != end) {
            // We process all the ids that have the same number of dots
            // together. Note that ids with different parents can clash, e.g.
            // because of old fashioned id generation or anchors containing
            // multiple dots.
            //
            // So find the group of placeholders with the same number of dots.
            iterator group_begin = it, group_end = it;
            while (group_end != end && (*group_end)->num_dots == (*it)->num_dots)
                ++group_end;

            // Used to find duplicate ids, and store required data about them.
            allocated_ids ids;
            placeholder_data data(state.placeholders.size());

            // First resolve ids by adding them to their parent's ids
            // (which have been fully processed in a previous iteration).
            for (it = group_begin; it != group_end; ++it) {
                resolve_id(**it, generated_ids, ids, data);
            }

            // Generate the final ids, taking into account any duplicates
            // found when resolving.
            for (it = group_begin; it != group_end; ++it) {
                generated_ids[(*it)->index] = generate_id(**it, ids, data);
            }
        }

        return generated_ids;
    }

    //
    // index_placeholders
    //
    // Create a sorted index of the placeholders, in order
    // to make numbering duplicates easy. A total order.
    //

    struct placeholder_compare
    {
        std::vector<unsigned>& order;

        placeholder_compare(std::vector<unsigned>& order) : order(order) {}

        bool operator()(id_placeholder* x, id_placeholder* y) const
        {
            bool x_explicit = x->category.c >= id_category::explicit_id;
            bool y_explicit = y->category.c >= id_category::explicit_id;

            return
                x->num_dots < y->num_dots ? true :
                x->num_dots > y->num_dots ? false :
                x_explicit > y_explicit ? true :
                x_explicit < y_explicit ? false :
                order[x->index] < order[y->index];
        }
    };

    struct get_placeholder_order_callback : xml_processor::callback
    {
        id_state& state;
        std::vector<unsigned>& order;
        unsigned count;

        get_placeholder_order_callback(id_state& state,
                std::vector<unsigned>& order)
          : state(state),
            order(order),
            count(0)
        {}

        void id_value(boost::string_ref value)
        {
            set_placeholder_order(state.get_placeholder(value));
        }

        void set_placeholder_order(id_placeholder const* p)
        {
            if (p && !order[p->index]) {
                set_placeholder_order(p->parent);
                order[p->index] = ++count;
            }
        }
    };

    placeholder_index index_placeholders(
            id_state& state,
            boost::string_ref xml)
    {
        // The order that the placeholder appear in the xml source.
        std::vector<unsigned> order(state.placeholders.size());

        xml_processor processor;
        get_placeholder_order_callback callback(state, order);
        processor.parse(xml, callback);

        placeholder_index sorted_placeholders;
        sorted_placeholders.reserve(state.placeholders.size());
        BOOST_FOREACH(id_placeholder& p, state.placeholders)
            if (order[p.index]) sorted_placeholders.push_back(&p);
        boost::sort(sorted_placeholders, placeholder_compare(order));

        return sorted_placeholders;
    }

    //
    // resolve_id
    //
    // Convert child ids to full ids, and add to the
    // allocated ids (although not yet set in stone because
    // there might be duplicates).
    //
    // Note that the parent ids has to be generated before resolving
    // the child id.
    //

    void resolve_id(id_placeholder& p, std::vector<std::string> const& generated_ids,
            allocated_ids& ids, placeholder_data& data)
    {
        assert(!data[p.index].data);

        std::string id = p.parent ?
            generated_ids[p.parent->index] + "." + p.id : p.id;

        id_data& data_ = ids.emplace(id, id_data()).first->second;
        data_.update_category(p.category);

        data[p.index].data = &data_;
        data[p.index].resolved_id = id;
    }

    //
    // generate_id
    //
    // Finally generate the final id.
    //

    void register_generation_data(id_placeholder&, allocated_ids&,
            placeholder_data& data);

    std::string generate_id(id_placeholder& p, allocated_ids& ids,
            placeholder_data& data)
    {
        assert(data[p.index].data);

        // If the placeholder id is available, then update data
        // and return.
        if (p.category == data[p.index].data->category &&
                !data[p.index].data->used &&
                p.category.c != id_category::numbered)
        {
            data[p.index].data->used = true;
            return data[p.index].resolved_id;
        }

        if (!data[p.index].data->generation_data)
        {
            data[p.index].data->generation_data =
                boost::make_shared<id_generation_data>(data[p.index].resolved_id);
            register_generation_data(p, ids, data);
        }

        // Loop until an available id is found.
        for(;;)
        {
            id_generation_data& generation_data = *data[p.index].data->generation_data;

            std::string postfix =
                boost::lexical_cast<std::string>(generation_data.count++);

            if (generation_data.child_length() + postfix.length() > max_size) {
                // The resulting id is too long, so move to a shorter id.
                generation_data.reduce_id();
                register_generation_data(p, ids, data);
            }
            else {
                std::string id = generation_data.id + postfix;

                if (ids.find(id) == ids.end()) return id;
            }
        }
    }

    // Every time the generation id is changed, this is called to
    // check if that id is already in use.
    void register_generation_data(id_placeholder& p, allocated_ids& ids,
            placeholder_data& data)
    {
        std::string const& id = data[p.index].data->generation_data->id;

        id_data& new_data = ids.emplace(id, id_data()).first->second;

        // If there is already generation_data for the new id then use that.
        // Otherwise use the placeholder's existing generation_data.
        if (new_data.generation_data)
            data[p.index].data->generation_data = new_data.generation_data;
        else
            new_data.generation_data = data[p.index].data->generation_data;
    }

    //
    // replace_ids
    //
    // Return a copy of the xml with all the placeholders replaced by
    // generated_ids.
    //

    struct replace_ids_callback : xml_processor::callback
    {
        id_state& state;
        std::vector<std::string> const* ids;
        boost::string_ref::const_iterator source_pos;
        std::string result;

        replace_ids_callback(id_state& state,
                std::vector<std::string> const* ids)
          : state(state),
            ids(ids),
            source_pos(),
            result()
        {}

        void start(boost::string_ref xml)
        {
            source_pos = xml.begin();
        }

        void id_value(boost::string_ref value)
        {
            if (id_placeholder* p = state.get_placeholder(value))
            {
                boost::string_ref id = ids ?
                    (*ids)[p->index] : p->unresolved_id;

                result.append(source_pos, value.begin());
                result.append(id.begin(), id.end());
                source_pos = value.end();
            }
        }

        void finish(boost::string_ref xml)
        {
            result.append(source_pos, xml.end());
            source_pos = xml.end();
        }
    };

    std::string replace_ids(id_state& state, boost::string_ref xml,
            std::vector<std::string> const* ids)
    {
        xml_processor processor;
        replace_ids_callback callback(state, ids);
        processor.parse(xml, callback);
        return callback.result;
    }
}
