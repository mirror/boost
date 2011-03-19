/*=============================================================================
    Copyright (c) 2010-2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "values.hpp"
#include <boost/intrusive_ptr.hpp>
#include <boost/current_function.hpp>

#define UNDEFINED_ERROR() \
    throw value_error( \
        std::string(BOOST_CURRENT_FUNCTION) +\
        " not defined for " + \
        this->type_name() + \
        " values." \
        );

namespace quickbook
{
    ////////////////////////////////////////////////////////////////////////////
    // Value Error
    
    value_error::value_error(std::string const& x)
        : std::logic_error(x) {}
    
    ////////////////////////////////////////////////////////////////////////////
    // Node

    namespace detail
    {
        value_node::value_node(tag_type t)
            : ref_count_(0), tag_(t), next_() {
        }        
    
        value_node::~value_node() {
        }
        
        value_node* value_node::store() { return this; }

        file_position value_node::get_position() const { UNDEFINED_ERROR(); }
        std::string value_node::get_quickbook() const { UNDEFINED_ERROR(); }
        std::string value_node::get_boostbook() const {  UNDEFINED_ERROR(); }
        value_node* value_node::get_list() const {  UNDEFINED_ERROR(); }

        bool value_node::empty() const { return false; }
        bool value_node::is_list() const { return false; }
        bool value_node::is_string() const { return false; }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Empty/nil values
    //
    // (nil is just a special case of empty, don't be mislead by the name
    //  the type is not important).

    namespace detail
    {
        struct value_empty_impl : public value_node
        {
            static value_node* new_(value::tag_type t);

        protected:
            explicit value_empty_impl(value::tag_type t)
                : value_node(t) {}

        private:
            char const* type_name() const { return "empty"; }
        
            virtual value_node* clone() const
                { return new value_empty_impl(tag_); }

            virtual bool empty() const
                { return true; }
            
            friend value quickbook::empty_value(value::tag_type);
        };
    
        struct value_nil_impl : public value_empty_impl
        {
            static value_nil_impl instance;
        private:
            value_nil_impl()
                : value_empty_impl(value::default_tag)
            {
                intrusive_ptr_add_ref(&instance);
            }
        };
        
        value_nil_impl value_nil_impl::instance;

        value_node* value_empty_impl::new_(value::tag_type t) {
            // The return value from this function is always placed in an
            // intrusive_ptr which will manage the memory correctly.
            // Note that value_nil_impl increments its reference count
            // in its constructor, so that it will never be deleted by the
            // intrusive pointer.

            if (t == value::default_tag)
                return &value_nil_impl::instance;
            else
                return new value_empty_impl(t);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // value_counted

    namespace detail
    {
        value_counted::value_counted()
            : value_base(&value_nil_impl::instance)
        {
            // Even though empty is not on the heap, its reference
            // counter needs to be incremented so that the destructor
            // doesn't try to delete it.

            intrusive_ptr_add_ref(value_);
        }
    
        value_counted::value_counted(value_counted const& x)
            : value_base(x)
        {
            intrusive_ptr_add_ref(value_);
        }
    
        value_counted::value_counted(value_base const& x)
            : value_base(x)
        {
            intrusive_ptr_add_ref(value_);
        }
    
        value_counted::value_counted(value_node* x)
            : value_base(x)
        {
            intrusive_ptr_add_ref(value_);
        }
    
        value_counted& value_counted::operator=(value_counted x)
        {
            swap(x);
            return *this;
        }
    
        value_counted::~value_counted()
        {
            intrusive_ptr_release(value_);
        }

        void value_counted::store()
        {
            value_node* new_value = value_->store();
            intrusive_ptr_add_ref(new_value);
            intrusive_ptr_release(value_);
            value_ = new_value;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // value

    value::value()
        : detail::value_counted()
    {
    }

    value::value(value const& x)
        : detail::value_counted(x)
    {
    }

    value::value(detail::value_ref x)
        : detail::value_counted(x)
    {
    }

    value::value(detail::value_node* x)
        : detail::value_counted(x)
    {
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Iterator

    namespace detail
    {
        value::iterator::iterator()
            : ptr_(&value_nil_impl::instance) {}
    }

    value empty_value(value::tag_type t)
    {
        return value(detail::value_empty_impl::new_(t));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Strings

    namespace detail
    {
        struct value_string_impl : public value_node
        {
        public:
            explicit value_string_impl(std::string const&, value::tag_type);
        private:
            char const* type_name() const { return "boostbook"; }

            virtual ~value_string_impl();
            virtual value_node* clone() const;
            virtual std::string get_boostbook() const;
            virtual bool is_string() const;
            virtual bool empty() const;
    
            std::string value_;
        };
    
        struct value_qbk_string_impl : public value_node
        {
        public:
            explicit value_qbk_string_impl(
                    std::string const&, file_position, value::tag_type);
            explicit value_qbk_string_impl(
                    quickbook::iterator begin, quickbook::iterator end,
                    value::tag_type);
        private:
            char const* type_name() const { return "quickbook"; }

            virtual ~value_qbk_string_impl();
            virtual value_node* clone() const;
            virtual file_position get_position() const;
            virtual std::string get_quickbook() const;
            virtual bool is_string() const;
            virtual bool empty() const;
    
            std::string value_;
            file_position position_;
        };

        struct value_qbk_ref_impl : public value_node
        {
        public:
            explicit value_qbk_ref_impl(quickbook::iterator begin, quickbook::iterator end, value::tag_type);
        private:
            char const* type_name() const { return "quickbook"; }

            virtual ~value_qbk_ref_impl();
            virtual value_node* clone() const;
            virtual value_node* store();
            virtual file_position get_position() const;
            virtual std::string get_quickbook() const;
            virtual bool is_string() const;
            virtual bool empty() const;
    
            quickbook::iterator begin_;
            quickbook::iterator end_;
        };
    
        struct value_qbk_bbk_impl : public value_node
        {
        private:
            char const* type_name() const { return "quickbook/boostbook"; }

            value_qbk_bbk_impl(
                std::string const& qbk, std::string const& bbk,
                file_position const&, value::tag_type);
            value_qbk_bbk_impl(std::string const&, value::tag_type);
            value_qbk_bbk_impl(
                    quickbook::iterator, quickbook::iterator,
                    std::string const&, value::tag_type);
    
            virtual ~value_qbk_bbk_impl();
            virtual value_node* clone() const;
            virtual file_position get_position() const;
            virtual std::string get_quickbook() const;
            virtual std::string get_boostbook() const;
            virtual bool is_string() const;
            virtual bool empty() const;

            std::string qbk_value_;
            std::string bbk_value_;
            file_position position_;
            
            friend quickbook::value quickbook::qbk_bbk_value(
                    std::string const&, quickbook::value::tag_type);
            friend quickbook::value quickbook::qbk_bbk_value(
                    quickbook::iterator, quickbook::iterator,
                    std::string const&, quickbook::value::tag_type);
        };

        // value_string_impl
    
        value_string_impl::value_string_impl(
                std::string const& val,
                value::tag_type tag
            )
            : value_node(tag), value_(val)
        {
        }
    
        value_string_impl::~value_string_impl()
        {
        }

        value_node* value_string_impl::clone() const
        {
            return new value_string_impl(value_, tag_);
        }
    
        std::string value_string_impl::get_boostbook() const
            { return value_; }

        bool value_string_impl::is_string() const
            { return true; }

        bool value_string_impl::empty() const
            { return value_.empty(); }

        // value_qbk_string_impl
    
        value_qbk_string_impl::value_qbk_string_impl(
                std::string const& v,
                file_position p,
                value::tag_type tag)
            : value_node(tag)
            , value_(v)
            , position_(p)
        {}

        value_qbk_string_impl::value_qbk_string_impl(
                quickbook::iterator begin, quickbook::iterator end,
                value::tag_type tag)
            : value_node(tag)
            , value_(begin, end)
            , position_(begin.get_position())
        {}
    
        value_qbk_string_impl::~value_qbk_string_impl()
        {}
    
        value_node* value_qbk_string_impl::clone() const
        {
            return new value_qbk_string_impl(value_, position_, tag_);
        }

        file_position value_qbk_string_impl::get_position() const
            { return position_; }

        std::string value_qbk_string_impl::get_quickbook() const
            { return value_; }

        bool value_qbk_string_impl::is_string() const
            { return true; }

        bool value_qbk_string_impl::empty() const
            { return value_.empty(); }
    
        // value_qbk_ref_impl
    
        value_qbk_ref_impl::value_qbk_ref_impl(
                quickbook::iterator begin, quickbook::iterator end,
                value::tag_type tag
            ) : value_node(tag), begin_(begin), end_(end)
        {
        }
    
        value_qbk_ref_impl::~value_qbk_ref_impl()
        {
        }
    
        value_node* value_qbk_ref_impl::clone() const
        {
            return new value_qbk_ref_impl(begin_, end_, tag_);
        }

        value_node* value_qbk_ref_impl::store()
        {
            return new value_qbk_string_impl(begin_, end_, tag_);
        }

        file_position value_qbk_ref_impl::get_position() const
            { return begin_.get_position(); }

        std::string value_qbk_ref_impl::get_quickbook() const
            { return std::string(begin_.base(), end_.base()); }

        bool value_qbk_ref_impl::is_string() const
            { return true; }

        bool value_qbk_ref_impl::empty() const
            { return begin_ == end_; }
    
        // value_qbk_bbk_impl
    
        value_qbk_bbk_impl::value_qbk_bbk_impl(
                std::string const& qbk,
                std::string const& bbk,
                file_position const& pos,
                value::tag_type tag)
            : value_node(tag)
            , qbk_value_(qbk)
            , bbk_value_(bbk)
            , position_(pos)
            
        {
        }
    
        value_qbk_bbk_impl::value_qbk_bbk_impl(
                quickbook::iterator begin,
                quickbook::iterator end,
                std::string const& bbk,
                value::tag_type tag)
            : value_node(tag)
            , qbk_value_(begin.base(), end.base())
            , bbk_value_(bbk)
            , position_(begin.get_position())
            
        {
        }
    
        value_qbk_bbk_impl::value_qbk_bbk_impl(
                std::string const& val,
                value::tag_type tag)
            : value_node(tag)
            , qbk_value_(val)
            , bbk_value_(val)
            , position_()
        {
        }
    
        value_qbk_bbk_impl::~value_qbk_bbk_impl()
        {
        }

        value_node* value_qbk_bbk_impl::clone() const
        {
            return new value_qbk_bbk_impl(
                    qbk_value_, bbk_value_, position_, tag_);
        }

        file_position value_qbk_bbk_impl::get_position() const
            { return position_; }

        std::string value_qbk_bbk_impl::get_quickbook() const
            { return qbk_value_; }

        std::string value_qbk_bbk_impl::get_boostbook() const
            { return bbk_value_; }

        bool value_qbk_bbk_impl::is_string() const
            { return true; }

        // Should this test the quickbook, the boostbook or both?
        bool value_qbk_bbk_impl::empty() const
            { return bbk_value_.empty(); }
    }

    value qbk_value(iterator x, iterator y, value::tag_type t)
    {
        return value(new detail::value_qbk_ref_impl(x, y, t));
    }

    value qbk_value(std::string const& x, file_position pos, value::tag_type t)
    {
        return value(new detail::value_qbk_string_impl(x, pos, t));
    }

    value bbk_value(std::string const& x, value::tag_type t)
    {
        return value(new detail::value_string_impl(x, t));
    }

    value qbk_bbk_value(std::string const& x, value::tag_type t)
    {
        return value(new detail::value_qbk_bbk_impl(x,t));
    }

    value qbk_bbk_value(
            iterator x, iterator y,
            std::string const& z, value::tag_type t)
    {
        return value(new detail::value_qbk_bbk_impl(x,y,z,t));
    }

    //////////////////////////////////////////////////////////////////////////
    // List methods
    
    namespace detail
    {
    namespace {
        value_node** list_ref_back(value_node**);
        void list_ref(value_node*);
        void list_unref(value_node*);
        value_node** merge_sort(value_node**);
        value_node** merge_sort(value_node**, int);
        value_node** merge(value_node**, value_node**, value_node**);
        void rotate(value_node**, value_node**, value_node**);

        value_node** list_ref_back(value_node** back)
        {
            while(*back != &value_nil_impl::instance) {
                intrusive_ptr_add_ref(*back);
                back = &(*back)->next_;
            }
            
            return back;
        }

        void list_ref(value_node* ptr)
        {
            while(ptr != &value_nil_impl::instance) {
                intrusive_ptr_add_ref(ptr);
                ptr = ptr->next_;
            }
        }

        void list_unref(value_node* ptr)
        {
            while(ptr != &value_nil_impl::instance) {
                value_node* next = ptr->next_;
                intrusive_ptr_release(ptr);
                ptr = next;
            }
        }

        value_node** merge_sort(value_node** l)
        {
            if(*l == &value_nil_impl::instance)
                return l;
            else
                return merge_sort(l, 9999);
        }

        value_node** merge_sort(value_node** l, int recurse_limit)
        {
            value_node** p = &(*l)->next_;
            for(int count = 0;
                count < recurse_limit && *p != &value_nil_impl::instance;
                ++count)
            {
                p = merge(l, p, merge_sort(p, count));
            }
            return p;
        }
        
        value_node** merge(
                value_node** first, value_node** second, value_node** third)
        {
            for(;;) {
                for(;;) {
                    if(first == second) return third;
                    if((*second)->tag_ < (*first)->tag_) break;
                    first = &(*first)->next_;
                }
    
                rotate(first, second, third);
                first = &(*first)->next_;
                
                // Since the two ranges were just swapped, the order is now:
                // first...third...second
                //
                // Also, that since the second section of the list was
                // originally before the first, if the heads are equal
                // we need to swap to maintain the order.
                
                for(;;) {
                    if(first == third) return second;
                    if((*third)->tag_ <= (*first)->tag_) break;
                    first = &(*first)->next_;
                }
    
                rotate(first, third, second);
                first = &(*first)->next_;
            }
        }

        void rotate(value_node** first, value_node** second, value_node** third)
        {
            value_node* tmp = *first;
            *first = *second;
            *second = *third;
            *third = tmp;
            //if(*second != &value_nil_impl::instance) back = second;
        }
    }
    }

    //////////////////////////////////////////////////////////////////////////
    // Lists
    
    namespace detail
    {
        struct value_list_impl : public value_node
        {
            value_list_impl(value::tag_type);
            value_list_impl(value_node*, value::tag_type);
        private:
            char const* type_name() const { return "list"; }

            virtual ~value_list_impl();
            virtual value_node* clone() const;
            virtual value_node* store();
            virtual bool empty() const;
            virtual bool is_list() const;
    
            virtual value_node* get_list() const;
    
            value_node* head_;
        };

        value_list_impl::value_list_impl(value::tag_type tag)
            : value_node(tag), head_(&value_nil_impl::instance)
        {}
    
        value_list_impl::value_list_impl(value_node* ptr, value::tag_type tag)
            : value_node(tag), head_(ptr)
        {
            list_ref(head_);
        }
    
        value_list_impl::~value_list_impl()
        {
            list_unref(head_);
        }

        value_node* value_list_impl::clone() const
        {
            return new value_list_impl(head_, tag_);
        }

        // TODO: Could reuse nodes is any node has a reference count of 1.
        value_node* value_list_impl::store()
        {
            value_node* pos = head_;
            boost::intrusive_ptr<value_node> new_node;

            while(true) {
                if(pos == &value_nil_impl::instance)
                    return this;
                new_node = pos->store();
                if(new_node.get() != pos) break;
                pos = pos->next_;
            }

            value_list_builder build;

            for(value_node* pos2 = head_;
                pos2 != &value_nil_impl::instance;
                pos2 = pos2->next_)
            {
                if(pos2 == pos)
                    build.append(new_node.get());
                else
                    build.append(pos2);
            }

            return new value_list_impl(build.get(), tag_);
        }


        bool value_list_impl::empty() const
        {
            return head_ == &value_nil_impl::instance;
        }
    
        bool value_list_impl::is_list() const
        {
            return true;
        }
    
        value_node* value_list_impl::get_list() const
        {
            return head_;
        }
    }

    value list_value(value::tag_type t)
    {
        return value(new detail::value_list_impl(t));
    }

    //////////////////////////////////////////////////////////////////////////
    // List builder
    
    namespace detail
    {
        // value_list_builder
    
        value_list_builder::value_list_builder()
            : head_(&value_nil_impl::instance)
            , back_(&head_)
        {}

        value_list_builder::value_list_builder(value_node* ptr)
            : head_(ptr)
            , back_(list_ref_back(&head_))
        {}

        value_list_builder::~value_list_builder()
        {
            list_unref(head_);
        }

        void value_list_builder::swap(value_list_builder& other) {
            std::swap(head_, other.head_);
            std::swap(back_, other.back_);
            if(back_ == &other.head_) back_ = &head_;
            if(other.back_ == &head_) other.back_ = &other.head_;
        }

        // TODO: Multiple list refs are incompatible with 'store'
        value_node* value_list_builder::get() const {
            return head_;
        }
    
        void value_list_builder::append(value_node* item)
        {
            if(item->next_) item = item->clone();
            intrusive_ptr_add_ref(item);
            item->next_ = *back_;
            *back_ = item;
            back_ = &item->next_;
        }
        
        void value_list_builder::sort()
        {
            back_ = merge_sort(&head_);
            assert(*back_ == &value_nil_impl::instance);
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Value builder
    
    value_builder::value_builder()
        : current()
        , list_tag(value::default_tag)
        , saved()
    {
    }
    
    void value_builder::swap(value_builder& other) {
        current.swap(other.current);
        std::swap(list_tag, other.list_tag);
        saved.swap(other.saved);
    }
    
    void value_builder::save() {
        boost::scoped_ptr<value_builder> store(new value_builder);
        swap(*store);
        saved.swap(store);
    }

    void value_builder::restore() {
        boost::scoped_ptr<value_builder> store;
        store.swap(saved);
        swap(*store);
    }

    value value_builder::get() {
        return value(new detail::value_list_impl(current.get(), list_tag));
    }

    void value_builder::reset() {
        detail::value_list_builder new_builder;
        current.swap(new_builder);
        list_tag = value::default_tag;
    }

    void value_builder::insert(value const& item) {
        current.append(item.value_);
    }

    void value_builder::start_list(value::tag_type tag) {
        value::tag_type saved_tag = tag;
        save();
        list_tag = saved_tag;
    }

    void value_builder::finish_list() {
        value list = get();
        restore();
        insert(list);
    }

    void value_builder::clear_list() {
        restore();
    }

    void value_builder::sort_list()
    {
        current.sort();
    }
}
