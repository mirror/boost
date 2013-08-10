/*=============================================================================
    Copyright (c) 2011, 2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "id_manager_impl.hpp"
#include <boost/make_shared.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm.hpp>

// TODO: This should possibly try to always generate valid XML ids:
// http://www.w3.org/TR/REC-xml/#NT-NameStartChar

namespace quickbook {
    //
    // The maximum size of a generated part of an id.
    //
    // Not a strict maximum, sometimes broken because the user
    // explicitly uses a longer id, or for backwards compatibility.

    static const std::size_t max_size = 32;

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
    typedef std::vector<id_placeholder const*> placeholder_index;

    placeholder_index index_placeholders(id_state const&, boost::string_ref xml);
    void resolve_id(id_placeholder const&, std::vector<std::string> const&,
        allocated_ids&, placeholder_data& data);
    std::string generate_id(id_placeholder const&, allocated_ids&, placeholder_data& data);

    std::vector<std::string> generate_ids(id_state const& state, boost::string_ref xml)
    {
        std::vector<std::string> generated_ids(state.placeholders.size());

        // Get a list of the placeholders in the order that we wish to
        // process them.
        placeholder_index placeholders = index_placeholders(state, xml);

        typedef std::vector<id_placeholder const*>::iterator iterator;

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

        bool operator()(id_placeholder const* x, id_placeholder const* y) const
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
        id_state const& state;
        std::vector<unsigned>& order;
        unsigned count;

        get_placeholder_order_callback(id_state const& state,
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
            id_state const& state,
            boost::string_ref xml)
    {
        // The order that the placeholder appear in the xml source.
        std::vector<unsigned> order(state.placeholders.size());

        xml_processor processor;
        get_placeholder_order_callback callback(state, order);
        processor.parse(xml, callback);

        placeholder_index sorted_placeholders;
        sorted_placeholders.reserve(state.placeholders.size());
        BOOST_FOREACH(id_placeholder const& p, state.placeholders)
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

    void resolve_id(id_placeholder const& p, std::vector<std::string> const& generated_ids,
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

    void register_generation_data(id_placeholder const&, allocated_ids&,
            placeholder_data& data);

    std::string generate_id(id_placeholder const& p, allocated_ids& ids,
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
    void register_generation_data(id_placeholder const& p, allocated_ids& ids,
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
        id_state const& state;
        std::vector<std::string> const* ids;
        boost::string_ref::const_iterator source_pos;
        std::string result;

        replace_ids_callback(id_state const& state,
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
            if (id_placeholder const* p = state.get_placeholder(value))
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

    std::string replace_ids(id_state const& state, boost::string_ref xml,
            std::vector<std::string> const* ids)
    {
        xml_processor processor;
        replace_ids_callback callback(state, ids);
        processor.parse(xml, callback);
        return callback.result;
    }

    //
    // normalize_id
    //
    // Normalizes generated ids.
    //

    std::string normalize_id(boost::string_ref src_id)
    {
        return normalize_id(src_id, 0, max_size);
    }

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
