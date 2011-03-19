/*=============================================================================
    Copyright (c) 2010-2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// An easy way to store data parsed for quickbook.

#if !defined(BOOST_SPIRIT_QUICKBOOK_VALUES_HPP)
#define BOOST_SPIRIT_QUICKBOOK_VALUES_HPP

#include <utility>
#include <string>
#include <cassert>
#include <boost/scoped_ptr.hpp>
#include "fwd.hpp"

namespace quickbook
{
    class value;
    class value_builder;

    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        // Node
    
        class value_node
        {
        private:
            value_node(value_node const&);
            value_node& operator=(value_node const&);

        public:
            typedef int tag_type;

        protected:
            explicit value_node(tag_type);
            virtual ~value_node();

        public:
            virtual value_node* clone() const = 0;
            virtual value_node* store();

            virtual file_position get_position() const;
            virtual std::string get_quickbook() const;
            virtual std::string get_boostbook() const;

            virtual bool is_empty() const;
            virtual bool is_list() const;
            virtual bool is_string() const;

            virtual value_node* get_list() const;

            int ref_count_;
            const tag_type tag_;
            value_node* next_;

            friend void intrusive_ptr_add_ref(value_node* ptr)
                { ++ptr->ref_count_; }
            friend void intrusive_ptr_release(value_node* ptr)
                { if(--ptr->ref_count_ == 0) delete ptr; }
        };

        ////////////////////////////////////////////////////////////////////////
        // Value base
        //
        // This defines most of the public methods for value.
        // 'begin' and 'end' are defined with the iterators later.
    
        class value_base
        {
        public:
            class iterator;

            typedef iterator const_iterator;
            typedef value_node::tag_type tag_type;
            enum { no_tag = -1, default_tag = 0 };

        protected:
            explicit value_base(value_node* base)
                : value_(base)
            {
                assert(value_);
            }

            ~value_base() {}

        public:
            void swap(value_base& x) { std::swap(value_, x.value_); }

            bool is_empty() const { return value_->is_empty(); }
            bool is_list() const { return value_->is_list(); }
            bool is_string() const { return value_->is_string(); }

            iterator begin() const;
            iterator end() const;

            // Item accessors
            int get_tag() const { return value_->tag_; }
            file_position get_position() const
            { return value_->get_position(); }
            std::string get_quickbook() const
            { return value_->get_quickbook(); }
            std::string get_boostbook() const
            { return value_->get_boostbook(); }

        protected:
            value_node* value_;

            // value_builder needs to access 'value_' to get the node
            // from a value.
            friend class quickbook::value_builder;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // Reference and proxy values for use in iterators

        class value_ref : public value_base
        {
        public:
            explicit value_ref(value_node* base) : value_base(base) {}
        };
        
        class value_proxy : public value_base
        {
        public:
            explicit value_proxy(value_node* base) : value_base(base) {}
            value_proxy* operator->() { return this; }
        };
    
        ////////////////////////////////////////////////////////////////////////
        // Iterators

        class value_base::iterator
            : public boost::forward_iterator_helper<
                iterator, value, int, value_proxy, value_ref>
        {
        public:
            iterator();
            explicit iterator(value_node* p) : ptr_(p) {}
            friend bool operator==(iterator x, iterator y)
                { return x.ptr_ == y.ptr_; }
            iterator& operator++() { ptr_ = ptr_->next_; return *this; }
            value_ref operator*() const { return value_ref(ptr_); }
            value_proxy operator->() const { return value_proxy(ptr_); }
        private:
            value_node* ptr_;
        };

        inline value_base::iterator value_base::begin() const
        {
            return iterator(value_->get_list());
        }

        inline value_base::iterator value_base::end() const
        {
            return iterator();
        }

        ////////////////////////////////////////////////////////////////////////
        // Reference counting for values

        class value_counted : public value_base
        {
        public:
            value_counted();
            value_counted(value_counted const&);
            value_counted(value_base const&);
            value_counted(value_node*);
            value_counted& operator=(value_counted);
            ~value_counted();

            void store();
        };

        ////////////////////////////////////////////////////////////////////////
        // List builder
        //
        // Values are immutable, so this class is used to build a list of
        // value nodes before constructing the value.

        class value_list_builder {
            value_list_builder(value_list_builder const&);
            value_list_builder& operator=(value_list_builder const&);
        public:
            value_list_builder();
            value_list_builder(value_node*);
            ~value_list_builder();
            void swap(value_list_builder& b);
            value_node* get() const;

            void append(value_node*);
            void sort();
        private:
            value_node* head_;
            value_node** back_;
        };
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Value
    //
    // Most of the methods are in value_base.

    class value : public detail::value_counted
    {
    public:
        value();
        value(value const&);
        value(detail::value_ref);
        explicit value(detail::value_node*);
    };

    value empty_value(value::tag_type = value::default_tag);
    value list_value(value::tag_type = value::default_tag);
    value qbk_value(iterator, iterator, value::tag_type = value::default_tag);
    value qbk_value(std::string const&,
            file_position = file_position(),
            value::tag_type = value::default_tag);
    value bbk_value(std::string const&, value::tag_type = value::default_tag);
    value qbk_bbk_value(std::string const&,
            value::tag_type = value::default_tag);
    value qbk_bbk_value(iterator, iterator, std::string const&,
            value::tag_type = value::default_tag);

    ////////////////////////////////////////////////////////////////////////////
    // Value Builder
    //
    // Used to incrementally build a valueeter tree.

    class value_builder {
    public:
        value_builder();
        void swap(value_builder& b);
        
        void save();
        void restore();

        value get();

        void reset();
        void set_tag(value::tag_type);
        value::tag_type release_tag(value::tag_type = value::no_tag);
        void insert(value const&);

        void start_list(value::tag_type);
        void finish_list();
        void clear_list();
        void sort_list();

    private:
        detail::value_list_builder current;
        value::tag_type list_tag, next_tag;
        boost::scoped_ptr<value_builder> saved;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Value Consumer
    //
    // Convenience class for unpacking value values.

    class value_consumer {
    public:
        typedef value::iterator iterator;
        typedef value::iterator const_iterator;
        typedef iterator::reference reference;
    
        value_consumer(value const& x)
            : list_(x)
            , pos_(x.begin())
            , end_(x.end())
        {}

        value_consumer(reference x)
            : list_(x)
            , pos_(x.begin())
            , end_(x.end())
        {}

        reference consume(value::tag_type t = value::no_tag)
        {
            assert(is(t));
            return *pos_++;
        }

        value optional_consume(value::tag_type t = value::no_tag)
        {
            if(is(t)) {
                return *pos_++;
            }
            else {
                return value();
            }
        }

        bool is(value::tag_type t = value::no_tag)
        {
            return (pos_ != end_ &&
                (t == value::no_tag || t == pos_->get_tag()));
        }

        iterator begin() const { return pos_; }
        iterator end() const { return end_; }
    private:
        value list_;
        iterator pos_, end_;
    };
}

#endif
