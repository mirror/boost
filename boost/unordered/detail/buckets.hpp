
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED

#include <boost/unordered/detail/node.hpp>

namespace boost { namespace unordered { namespace detail {
    
    ////////////////////////////////////////////////////////////////////////////
    //
    // Now the main data structure:
    //
    // buckets<A, Unique>           functions<H, P>
    //       |                              |
    //       +---------------+--------------+
    //                       |
    //                   table<T>
    //
    // T is a class which contains typedefs for all the types we need.
    
    // buckets
    //
    // This is responsible for allocating and deallocating buckets and nodes.
    //
    // Notes:
    // 1. For the sake exception safety the consturctors don't allocate
    //    anything.
    // 2. It's the callers responsibility to allocate the buckets before calling
    //    any of the methods (other than getters and setters).

    template <class A, bool Unique>
    class buckets
    {
        buckets(buckets const&);
        buckets& operator=(buckets const&);
    public:
        // Types

        typedef BOOST_DEDUCED_TYPENAME ::boost::detail::if_true<Unique>::
            BOOST_NESTED_TEMPLATE then<
                ::boost::unordered::detail::ungrouped_node<A>,
                ::boost::unordered::detail::grouped_node<A>
            >::type node;

        typedef A value_allocator;
        typedef ::boost::unordered::detail::bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_allocator
            bucket_allocator;
        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME bucket::node_ptr node_ptr;

        typedef BOOST_DEDUCED_TYPENAME rebind_wrap<value_allocator, node>::type
            node_allocator;
        typedef BOOST_DEDUCED_TYPENAME node_allocator::pointer real_node_ptr;

        // Members

        bucket_ptr buckets_;
        std::size_t bucket_count_;
        ::boost::compressed_pair<bucket_allocator, node_allocator> allocators_;
        
        // Data access

        bucket_allocator const& bucket_alloc() const
        {
            return allocators_.first();
        }

        node_allocator const& node_alloc() const
        {
            return allocators_.second();
        }

        bucket_allocator& bucket_alloc()
        {
            return allocators_.first();
        }

        node_allocator& node_alloc()
        {
            return allocators_.second();
        }

        std::size_t max_bucket_count() const
        {
            // -1 to account for the start bucket.
            return prev_prime(this->bucket_alloc().max_size() - 1);
        }

        ////////////////////////////////////////////////////////////////////////
        // Constructors and Destructors

        buckets(node_allocator const& a, std::size_t bucket_count)
          : buckets_(),
            bucket_count_(bucket_count),
            allocators_(a,a)
        {
        }
    
        inline ~buckets()
        {
            if(this->buckets_) { this->delete_buckets(); }
        }

        void create_buckets()
        {
            // The array constructor will clean up in the event of an
            // exception.
            allocator_array_constructor<bucket_allocator>
                constructor(bucket_alloc());
    
            // Creates an extra bucket to act as the start node.
            constructor.construct(bucket(), this->bucket_count_ + 1);
    
            // Only release the buckets once everything is successfully
            // done.
            this->buckets_ = constructor.release();
        }
        
        // no throw
        void swap(buckets& other)
        {
            BOOST_ASSERT(node_alloc() == other.node_alloc());
            std::swap(buckets_, other.buckets_);
            std::swap(bucket_count_, other.bucket_count_);
        }

        void move(buckets& other)
        {
            BOOST_ASSERT(node_alloc() == other.node_alloc());
            if(this->buckets_) { this->delete_buckets(); }
            this->buckets_ = other.buckets_;
            this->bucket_count_ = other.bucket_count_;
            other.buckets_ = bucket_ptr();
            other.bucket_count_ = 0;
        }

        std::size_t bucket_size(std::size_t index) const
        {
            if (!this->buckets_) return 0;
            node_ptr ptr = this->buckets_[index].next_;
            if (!ptr) return 0;
            ptr = ptr->next_;
    
            std::size_t count = 0;
            while(BOOST_UNORDERED_BORLAND_BOOL(ptr) &&
                node::get_hash(ptr) % this->bucket_count_ == index)
            {
                ++count;
                ptr = ptr->next_;
            }
    
            return count;
        }

        node_ptr bucket_begin(std::size_t bucket_index) const
        {
            if (!this->buckets_) return node_ptr();
            bucket& b = this->buckets_[bucket_index];
            if (!b.next_) return node_ptr();
            return b.next_->next_;
        }

        // For the remaining functions, buckets_ must not be null.
        
        bucket_ptr get_bucket(std::size_t bucket_index) const
        {
            return buckets_ + static_cast<std::ptrdiff_t>(bucket_index);
        }

        ////////////////////////////////////////////////////////////////////////
        // Delete
        
        void delete_node(node_ptr n)
        {
            node* raw_ptr = static_cast<node*>(&*n);
            real_node_ptr real_ptr(node_alloc().address(*raw_ptr));

            ::boost::unordered::detail::destroy(raw_ptr->value_ptr());
            node_alloc().destroy(real_ptr);
            node_alloc().deallocate(real_ptr, 1);
        }

        void delete_buckets()
        {
            bucket_ptr end = this->get_bucket(this->bucket_count_);
    
            node_ptr n = (end)->next_;
            while(BOOST_UNORDERED_BORLAND_BOOL(n))
            {
                node_ptr node_to_delete = n;
                n = n->next_;
                delete_node(node_to_delete);
            }
    
            ++end;
            for(bucket_ptr begin = this->buckets_; begin != end; ++begin) {
                bucket_alloc().destroy(begin);
            }
    
            bucket_alloc().deallocate(this->buckets_, this->bucket_count_ + 1);
    
            this->buckets_ = bucket_ptr();
        }

        std::size_t delete_nodes(node_ptr begin, node_ptr end)
        {
            std::size_t count = 0;
            while(begin != end) {
                node_ptr n = begin;
                begin = begin->next_;
                delete_node(n);
                ++count;
            }
            return count;
        }

        // This is called after erasing a node or group of nodes to fix up
        // the bucket pointers.
        void fix_buckets(bucket_ptr bucket, node_ptr prev, node_ptr next)
        {
            if (!next)
            {
                if (bucket->next_ == prev) bucket->next_ = node_ptr();
            }
            else
            {
                bucket_ptr next_bucket = this->get_bucket(
                    node::get_hash(next) % this->bucket_count_);
                if (next_bucket != bucket)
                {
                    next_bucket->next_ = prev;
                    if (bucket->next_ == prev) bucket->next_ = node_ptr();
                }
            }
        }

        // This is called after erasing a range of nodes to fix any bucket
        // pointers into that range.
        void fix_buckets_range(
            std::size_t bucket_index, node_ptr prev, node_ptr begin, node_ptr end)
        {
            node_ptr n = begin;
    
            // If we're not at the start of the current bucket, then
            // go to the start of the next bucket.
            if (this->get_bucket(bucket_index)->next_ != prev)
            {
                for(;;) {
                    n = n->next_;
                    if (n == end) return;
    
                    std::size_t new_bucket_index =
                        node::get_hash(n) % this->bucket_count_;
                    if (bucket_index != new_bucket_index) {
                        bucket_index = new_bucket_index;
                        break;
                    }
                }
            }
    
            // Iterate through the remaining nodes, clearing out the bucket
            // pointers.
            this->buckets_[bucket_index].next_ = bucket_ptr();
            for(;;) {
                n = n->next_;
                if (n == end) break;
    
                std::size_t new_bucket_index =
                    node::get_hash(n) % this->bucket_count_;
                if (bucket_index != new_bucket_index) {
                    bucket_index = new_bucket_index;
                    this->buckets_[bucket_index].next_ = bucket_ptr();
                }
            };
    
            // Finally fix the bucket containing the trailing node.
            if (BOOST_UNORDERED_BORLAND_BOOL(n)) {
                this->buckets_[node::get_hash(n) % this->bucket_count_].next_
                    = prev;
            }
        }

        // Iterate through the nodes placing them in the correct buckets.
        // pre: prev->next_ is not null.
        node_ptr place_in_bucket(node_ptr prev, node_ptr end) {
            bucket_ptr b = this->get_bucket(node::get_hash(prev->next_) % this->bucket_count_);

            if (!b->next_) {
                b->next_ = prev;
                return end;
            }
            else {
                node_ptr next = end->next_;
                end->next_ = b->next_->next_;
                b->next_->next_ = prev->next_;
                prev->next_ = next;
                return prev;
            }
        }
        
        void copy_buckets_to(buckets&) const;
    };

    // Assigning and swapping the equality and hash function objects
    // needs strong exception safety. To implement that normally we'd
    // require one of them to be known to not throw and the other to
    // guarantee strong exception safety. Unfortunately they both only
    // have basic exception safety. So to acheive strong exception
    // safety we have storage space for two copies, and assign the new
    // copies to the unused space. Then switch to using that to use
    // them. This is implemented in 'set_hash_functions' which
    // atomically assigns the new function objects in a strongly
    // exception safe manner.

    template <class H, class P> class set_hash_functions;

    template <class H, class P>
    class functions
    {
        friend class set_hash_functions<H, P>;
        functions& operator=(functions const&);

        typedef ::boost::compressed_pair<H, P> function_pair;
        typedef BOOST_DEDUCED_TYPENAME ::boost::aligned_storage<
            sizeof(function_pair),
            ::boost::alignment_of<function_pair>::value>::type aligned_function;

        bool current_; // The currently active functions.
        aligned_function funcs_[2];

        function_pair const& current() const {
            return *static_cast<function_pair const*>(
                static_cast<void const*>(&funcs_[current_]));
        }

        void construct(bool which, H const& hf, P const& eq)
        {
            new((void*) &funcs_[which]) function_pair(hf, eq);
        }

        void construct(bool which, function_pair const& f)
        {
            new((void*) &funcs_[which]) function_pair(f);
        }
        
        void destroy(bool which)
        {
            ::boost::unordered::detail::destroy((function_pair*)(&funcs_[which]));
        }
        
    public:

        functions(H const& hf, P const& eq)
            : current_(false)
        {
            construct(current_, hf, eq);
        }

        functions(functions const& bf)
            : current_(false)
        {
            construct(current_, bf.current());
        }

        ~functions() {
            destroy(current_);
        }

        H const& hash_function() const {
            return current().first();
        }

        P const& key_eq() const {
            return current().second();
        }
    };
    
    template <class H, class P>
    class set_hash_functions
    {
        set_hash_functions(set_hash_functions const&);
        set_hash_functions& operator=(set_hash_functions const&);
    
        functions<H,P>& functions_;
        bool tmp_functions_;

    public:

        set_hash_functions(functions<H,P>& f, H const& h, P const& p)
          : functions_(f),
            tmp_functions_(!f.current_)
        {
            f.construct(tmp_functions_, h, p);
        }

        set_hash_functions(functions<H,P>& f, functions<H,P> const& other)
          : functions_(f),
            tmp_functions_(!f.current_)
        {
            f.construct(tmp_functions_, other.current());
        }

        ~set_hash_functions()
        {
            functions_.destroy(tmp_functions_);
        }

        void commit()
        {
            functions_.current_ = tmp_functions_;
            tmp_functions_ = !tmp_functions_;
        }
    };

    ////////////////////////////////////////////////////////////////////////////
    // Node Constructors

#if defined(BOOST_UNORDERED_STD_FORWARD)

    template <class T, class... Args>
    inline void construct_impl(T*, void* address, Args&&... args)
    {
        new(address) T(std::forward<Args>(args)...);
    }

#if defined(BOOST_UNORDERED_CPP0X_PAIR)
    template <class First, class Second, class Key, class Arg0, class... Args>
    inline void construct_impl(std::pair<First, Second>*, void* address,
        Key&& k, Arg0&& arg0, Args&&... args)
    )
    {
        new(address) std::pair<First, Second>(k,
            Second(arg0, std::forward<Args>(args)...);
    }
#endif

#else

#define BOOST_UNORDERED_CONSTRUCT_IMPL(z, num_params, _)                       \
    template <                                                                 \
        class T,                                                               \
        BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)                           \
    >                                                                          \
    inline void construct_impl(                                                \
        T*, void* address,                                                     \
        BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params)                         \
    )                                                                          \
    {                                                                          \
        new(address) T(                                                        \
            BOOST_UNORDERED_CALL_PARAMS(z, num_params));                       \
    }                                                                          \
                                                                               \
    template <class First, class Second, class Key,                            \
        BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)                           \
    >                                                                          \
    inline void construct_impl(                                                \
        std::pair<First, Second>*, void* address,                              \
        Key const& k, BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params))          \
    {                                                                          \
        new(address) std::pair<First, Second>(k,                               \
            Second(BOOST_UNORDERED_CALL_PARAMS(z, num_params)));               \
    }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
        BOOST_UNORDERED_CONSTRUCT_IMPL, _)

#undef BOOST_UNORDERED_CONSTRUCT_IMPL
#endif

    ///////////////////////////////////////////////////////////////////
    //
    // Node construction

    template <class Alloc, bool Unique>
    class node_constructor
    {
        typedef ::boost::unordered::detail::buckets<Alloc, Unique> buckets;
        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef BOOST_DEDUCED_TYPENAME buckets::real_node_ptr real_node_ptr;
        typedef BOOST_DEDUCED_TYPENAME buckets::value_type value_type;

        buckets& buckets_;
        real_node_ptr node_;
        bool node_constructed_;
        bool value_constructed_;

    public:

        node_constructor(buckets& m) :
            buckets_(m),
            node_(),
            node_constructed_(false),
            value_constructed_(false)
        {
        }

        ~node_constructor();
        void construct_preamble();

#if defined(BOOST_UNORDERED_STD_FORWARD)
        template <class... Args>
        void construct(Args&&... args)
        {
            construct_preamble();
            construct_impl((value_type*) 0, node_->address(),
                std::forward<Args>(args)...);
            value_constructed_ = true;
        }
#else

#define BOOST_UNORDERED_CONSTRUCT(z, num_params, _)                            \
        template <                                                             \
            BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)                       \
        >                                                                      \
        void construct(                                                        \
            BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params)                     \
        )                                                                      \
        {                                                                      \
            construct_preamble();                                              \
            construct_impl(                                                    \
                (value_type*) 0, node_->address(),                             \
                BOOST_UNORDERED_CALL_PARAMS(z, num_params)                     \
            );                                                                 \
            value_constructed_ = true;                                         \
        }

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_CONSTRUCT, _)

#undef BOOST_UNORDERED_CONSTRUCT

#endif
        template <class K, class M>
        void construct_pair(K const& k, M*)
        {
            construct_preamble();
            new(node_->address()) value_type(k, M());                    
            value_constructed_ = true;
        }

        value_type& value() const
        {
            BOOST_ASSERT(node_);
            return node_->value();
        }

        // no throw
        BOOST_DEDUCED_TYPENAME buckets::node_ptr release()
        {
            real_node_ptr p = node_;
            node_ = real_node_ptr();
            // node_ptr cast
            return buckets_.bucket_alloc().address(*p);
        }

    private:
        node_constructor(node_constructor const&);
        node_constructor& operator=(node_constructor const&);
    };
    
    // node_constructor

    template <class Alloc, bool Unique>
    inline node_constructor<Alloc, Unique>::~node_constructor()
    {
        if (node_) {
            if (value_constructed_) {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
                struct dummy { node<Alloc, Grouped> x; };
#endif
                ::boost::unordered::detail::destroy(node_->value_ptr());
            }

            if (node_constructed_)
                buckets_.node_alloc().destroy(node_);

            buckets_.node_alloc().deallocate(node_, 1);
        }
    }

    template <class Alloc, bool Unique>
    inline void node_constructor<Alloc, Unique>::construct_preamble()
    {
        if(!node_) {
            node_constructed_ = false;
            value_constructed_ = false;

            node_ = buckets_.node_alloc().allocate(1);
            buckets_.node_alloc().construct(node_, node());
            node_->init(buckets_.bucket_alloc().address(*node_));

            node_constructed_ = true;
        }
        else {
            BOOST_ASSERT(node_constructed_ && value_constructed_);
            ::boost::unordered::detail::destroy(node_->value_ptr());
            value_constructed_ = false;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // copy_buckets_to
    //
    // basic excpetion safety. If an exception is thrown this will
    // leave dst partially filled and the buckets unset.

    template <class A, bool Unique>
    void buckets<A, Unique>::copy_buckets_to(buckets& dst) const
    {
        BOOST_ASSERT(!dst.buckets_);

        dst.create_buckets();
        bucket_ptr dst_start = dst.get_bucket(dst.bucket_count_);

        {        
            node_constructor<A, Unique> a(dst);
    
            node_ptr n = this->buckets_[this->bucket_count_].next_;
            node_ptr prev = dst_start;
            
            while(n) {
                std::size_t hash = node::get_hash(n);
                node_ptr group_end = node::next_group(n);
    
                a.construct(node::get_value(n));
                node_ptr first_node = a.release();
                node::set_hash(first_node, hash);
                node_ptr end = prev->next_ = first_node;
    
                for(n = n->next_; n != group_end; n = n->next_) {
                    a.construct(node::get_value(n));
                    end = a.release();
                    node::set_hash(end, hash);
                    node::add_after_node(end, first_node);
                }
                
                prev = dst.place_in_bucket(prev, end);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////
    //
    // Iterators

    // iterator_access is used to access the internal iterator without
    // making it publicly available.

    class iterator_access
    {
    public:
        template <class Iterator>
        static BOOST_DEDUCED_TYPENAME Iterator::node_ptr const&
            get(Iterator const& it)
        {
            return it.node_;
        }
    };
}}}

#endif
