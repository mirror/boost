
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
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

        typedef typename ::boost::detail::if_true<Unique>::
            BOOST_NESTED_TEMPLATE then<
                ::boost::unordered::detail::ungrouped_node<A>,
                ::boost::unordered::detail::grouped_node<A>
            >::type node;

        typedef A value_allocator;
        typedef ::boost::unordered::detail::bucket<A> bucket;
        typedef typename allocator_traits<A>::value_type value_type;

        typedef typename bucket::bucket_allocator bucket_allocator;
        typedef typename allocator_traits<bucket_allocator>::pointer bucket_ptr;
        typedef typename bucket::node_ptr node_ptr;

        typedef typename rebind_wrap<value_allocator, node>::type
            node_allocator;
        typedef typename allocator_traits<node_allocator>::pointer real_node_ptr;

        // Members

        bucket_ptr buckets_;
        std::size_t bucket_count_;
        std::size_t size_;
        compressed_pair<bucket_allocator, node_allocator> allocators_;
        
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
            return prev_prime(allocator_traits<bucket_allocator>::max_size(bucket_alloc()) - 1);
        }

        ////////////////////////////////////////////////////////////////////////
        // Constructors and Destructors

        buckets(node_allocator const& a, std::size_t bucket_count)
          : buckets_(),
            bucket_count_(bucket_count),
            size_(),
            allocators_(a,a)
        {
        }

        buckets(buckets& b, move_tag m)
          : buckets_(),
            bucket_count_(b.bucket_count_),
            size_(),
            allocators_(b.allocators_, m)
        {
            swap(b);
        }

        template <typename T>
        buckets(table<T>& x, move_tag m)
          : buckets_(),
            bucket_count_(x.bucket_count_),
            allocators_(x.allocators_, m)
        {
            swap(x);
            x.size_ = 0;
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
        
        void swap(buckets& other, false_type = false_type())
        {
            BOOST_ASSERT(node_alloc() == other.node_alloc());
            std::swap(buckets_, other.buckets_);
            std::swap(bucket_count_, other.bucket_count_);
            std::swap(size_, other.size_);
        }

        void swap(buckets& other, true_type)
        {
            allocators_.swap(other.allocators_);
            std::swap(buckets_, other.buckets_);
            std::swap(bucket_count_, other.bucket_count_);
            std::swap(size_, other.size_);
        }

        void move_buckets_from(buckets& other)
        {
            BOOST_ASSERT(node_alloc() == other.node_alloc());
            BOOST_ASSERT(!this->buckets_);
            this->buckets_ = other.buckets_;
            this->bucket_count_ = other.bucket_count_;
            this->size_ = other.size_;
            other.buckets_ = bucket_ptr();
            other.bucket_count_ = 0;
            other.size_ = 0;
        }

        std::size_t bucket_size(std::size_t index) const
        {
            if (!this->size_) return 0;
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
            if (!this->size_) return node_ptr();
            bucket& b = this->buckets_[bucket_index];
            if (!b.next_) return node_ptr();
            return b.next_->next_;
        }

        // For the remaining functions, buckets_ must not be null.
        
        bucket_ptr get_bucket(std::size_t bucket_index) const
        {
            return buckets_ + static_cast<std::ptrdiff_t>(bucket_index);
        }

        float load_factor() const
        {
            BOOST_ASSERT(this->bucket_count_ != 0);
            return static_cast<float>(this->size_)
                / static_cast<float>(this->bucket_count_);
        }

        ////////////////////////////////////////////////////////////////////////
        // Delete
        
        void delete_node(node_ptr n)
        {
            node* raw_ptr = static_cast<node*>(boost::addressof(*n));
            real_node_ptr real_ptr(node_alloc().address(*raw_ptr));

            ::boost::unordered::detail::destroy(raw_ptr->value_ptr());
            allocator_traits<node_allocator>::destroy(node_alloc(), raw_ptr);
            allocator_traits<node_allocator>::deallocate(node_alloc(), real_ptr, 1);

            --this->size_;
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
                allocator_traits<bucket_allocator>::destroy(bucket_alloc(),
                    boost::addressof(*begin));
            }
    
            allocator_traits<bucket_allocator>::deallocate(bucket_alloc(), this->buckets_, this->bucket_count_ + 1);
    
            this->buckets_ = bucket_ptr();
            BOOST_ASSERT(this->size_ == 0);
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

        void clear()
        {
            if(!this->size_) return;
    
            bucket_ptr end = this->get_bucket(this->bucket_count_);
    
            node_ptr n = (end)->next_;
            while(BOOST_UNORDERED_BORLAND_BOOL(n))
            {
                node_ptr node_to_delete = n;
                n = n->next_;
                this->delete_node(node_to_delete);
            }
    
            ++end;
            for(bucket_ptr begin = this->buckets_; begin != end; ++begin) {
                begin->next_ = bucket_ptr();
            }
    
            this->size_ = 0;
        }

        node_ptr erase(node_ptr r)
        {
            BOOST_ASSERT(r);
            node_ptr next = r->next_;
    
            bucket_ptr bucket = this->get_bucket(
                node::get_hash(r) % this->bucket_count_);
            node_ptr prev = node::unlink_node(*bucket, r);
    
            this->fix_buckets(bucket, prev, next);
    
            this->delete_node(r);
    
            return next;
        }

        node_ptr erase_range(node_ptr r1, node_ptr r2)
        {
            if (r1 == r2) return r2;
    
            std::size_t bucket_index = node::get_hash(r1) % this->bucket_count_;
            node_ptr prev = node::unlink_nodes(
                this->buckets_[bucket_index], r1, r2);
            this->fix_buckets_range(bucket_index, prev, r1, r2);
            this->delete_nodes(r1, r2);
    
            return r2;
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
        void move_buckets_to(buckets&) const;
        void rehash_impl(std::size_t);
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

        typedef compressed_pair<H, P> function_pair;
        typedef typename ::boost::aligned_storage<
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
    //
    // Value Construction

#define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(n, namespace_)                 \
    template<typename T>                                                    \
    void construct_from_tuple(T* ptr, namespace_::tuple<>)                  \
    {                                                                       \
        new ((void*) ptr) T();                                              \
    }                                                                       \
                                                                            \
    BOOST_PP_REPEAT_FROM_TO(1, n,                                           \
        BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL, namespace_)

#define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL(z, n, namespace_)         \
    template<typename T BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename Arg)>\
    void construct_from_tuple(T* ptr,                                       \
            namespace_::tuple<BOOST_PP_ENUM_PARAMS_Z(z, n, Arg)> const& x)  \
    {                                                                       \
        new ((void*) ptr) T(                                                \
            BOOST_PP_ENUM_##z(n, BOOST_UNORDERED_GET_TUPLE_ARG, namespace_) \
        );                                                                  \
    }

#define BOOST_UNORDERED_GET_TUPLE_ARG(z, n, namespace_)                     \
    namespace_::get<n>(x)

BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(10, boost)

#if !defined(BOOST_NO_0X_HDR_TUPLE)
BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(10, std)
#elif defined(BOOST_HAS_TR1_TUPLE)
BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(10, std::tr1)
#endif

#if defined(BOOST_UNORDERED_DEPRECATED_PAIR_CONSTRUCT)
    template <typename A, typename B, typename Arg1>
    struct emulation1 {
        static choice1::type check(choice1, std::pair<A, B> const&);
        static choice2::type check(choice2, A const&);

        enum { value = sizeof(check(choose(), make<Arg1>())) == sizeof(choice2::type) };
    };
#endif

#if defined(BOOST_UNORDERED_DEPRECATED_PAIR_CONSTRUCT)
    template <typename A, typename B, typename Arg1>
    struct check3_base {
        static choice1::type check(choice1, boost::unordered::piecewise_construct_t);
        static choice2::type check(choice2, A const&);
        static choice3::type check(choice3, ...);
    };
#else
    template <typename A, typename B, typename Arg1>
    struct check3_base {
        static choice1::type check(choice1, boost::unordered::piecewise_construct_t);
        static choice3::type check(choice3, ...);
    };
#endif

    template <typename A, typename B, typename Arg1>
    struct piecewise3 {
        enum { value =
            sizeof(check3_base<A,B,Arg1>::check(choose(), make<Arg1>())) ==
            sizeof(choice1::type) };
    };

    template <typename A, typename B, typename Arg1>
    struct emulation3 {
        enum { value =
            sizeof(check3_base<A,B,Arg1>::check(choose(), make<Arg1>())) ==
            sizeof(choice2::type) };
    };

    template <typename A, typename B, typename Arg1>
    struct normal3 {
        enum { value =
            sizeof(check3_base<A,B,Arg1>::check(choose(), make<Arg1>())) ==
            sizeof(choice3::type) };
    };

    template <typename T, typename Arg1>
    struct pair_construct1 {};
    template <typename T, typename Arg1>
    struct normal_construct1 { typedef void type; };

#if defined(BOOST_UNORDERED_DEPRECATED_PAIR_CONSTRUCT)
    template <typename A, typename B, typename Arg1>
    struct pair_construct1<std::pair<A, B>, Arg1>
        : enable_if<emulation1<A, B, Arg1>, void> {};

    template <typename A, typename B, typename Arg1>
    struct normal_construct1<std::pair<A, B>, Arg1>
        : disable_if<emulation1<A, B, Arg1>, void> {};
#endif

    template <typename T, typename Arg1>
    struct piecewise_construct3 {};
    template <typename A, typename B, typename Arg1>
    struct piecewise_construct3<std::pair<A, B>, Arg1>
        : enable_if<piecewise3<A, B, Arg1>, void> {};

    template <typename T, typename Arg1>
    struct pair_construct3 {};
    template <typename A, typename B, typename Arg1>
    struct pair_construct3<std::pair<A, B>, Arg1>
        : enable_if<emulation3<A, B, Arg1>, void> {};

    template <typename T, typename Arg1>
    struct normal_construct3 { typedef void type; };
    template <typename A, typename B, typename Arg1>
    struct normal_construct3<std::pair<A, B>, Arg1>
        : enable_if<normal3<A, B, Arg1>, void> {};

    template <typename T>
    struct pair_construct_n {};
    template <typename T>
    struct normal_construct_n { typedef void type; };

#if defined(BOOST_UNORDERED_DEPRECATED_PAIR_CONSTRUCT)
    template <typename A, typename B>
    struct pair_construct_n<std::pair<A, B> > { typedef void type; };
    template <typename A, typename B>
    struct normal_construct_n<std::pair<A, B> > {};
#endif

    template <class T>
    inline void construct_impl(void* address)
    {
        new(address) T();
    }

    template <class T, class Arg1>
    inline typename normal_construct1<T, Arg1>::type
        construct_impl(void* address, BOOST_FWD_REF(Arg1) arg1)
    {
        new(address) T(
            boost::forward<Arg1>(arg1)
        );
    }

    template <class T, class Arg1>
    inline typename pair_construct1<T, Arg1>::type
        construct_impl(void* address, BOOST_FWD_REF(Arg1) arg1)
    {
        new((void*)(&static_cast<T*>(address)->first))
        typename T::first_type(
            boost::forward<Arg1>(arg1));
        new((void*)(&static_cast<T*>(address)->second))
        typename T::second_type();
   }

    template <class T, class Arg1, class Arg2>
    inline void construct_impl(void* address, BOOST_FWD_REF(Arg1) arg1,
            BOOST_FWD_REF(Arg2) arg2)
    {
        new(address) T(
            boost::forward<Arg1>(arg1),
            boost::forward<Arg2>(arg2));
    }

    template <class T, class Arg1, class Arg2, class Arg3>
    inline typename piecewise_construct3<T, Arg1>::type
        construct_impl(void* address, BOOST_FWD_REF(Arg1),
            BOOST_FWD_REF(Arg2) arg2, BOOST_FWD_REF(Arg3) arg3)
    {
        construct_from_tuple(&static_cast<T*>(address)->first, arg2);
        construct_from_tuple(&static_cast<T*>(address)->second, arg3);
    }

    template <class T, class Arg1, class Arg2, class Arg3>
    inline typename pair_construct3<T, Arg1>::type
        construct_impl(void* address, BOOST_FWD_REF(Arg1) arg1,
            BOOST_FWD_REF(Arg2) arg2, BOOST_FWD_REF(Arg3) arg3)
    {
        new((void*)(&static_cast<T*>(address)->first))
        typename T::first_type(
            boost::forward<Arg1>(arg1));
        new((void*)(&static_cast<T*>(address)->second))
        typename T::second_type(
            boost::forward<Arg2>(arg2),
            boost::forward<Arg3>(arg3));
    }

    template <class T, class Arg1, class Arg2, class Arg3>
    inline typename normal_construct3<T, Arg1>::type
        construct_impl(void* address, BOOST_FWD_REF(Arg1) arg1,
            BOOST_FWD_REF(Arg2) arg2, BOOST_FWD_REF(Arg3) arg3)
    {
        new(address) T(
            boost::forward<Arg1>(arg1),
            boost::forward<Arg2>(arg2),
            boost::forward<Arg3>(arg3));
    }

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)

    template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class... Args>
    inline typename normal_construct_n<T>::type
        construct_impl(void* address, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3,
            Arg4&& arg4, Args&&... args)
    {
        new(address) T(
            std::forward<Arg1>(arg1),
            std::forward<Arg2>(arg2),
            std::forward<Arg3>(arg3),
            std::forward<Arg4>(arg4),
            std::forward<Args>(args)...);
    }

    template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class... Args>
    inline typename pair_construct_n<T>::type
        construct_impl(void* address, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3,
            Arg4&& arg4, Args&&... args)
    {
        new((void*)(&static_cast<T*>(address)->first))
        typename T::first_type(
            std::forward<Arg1>(arg1));
        new((void*)(&static_cast<T*>(address)->second))
        typename T::second_type(
            std::forward<Arg2>(arg2),
            std::forward<Arg3>(arg3),
            std::forward<Arg4>(arg4),
            std::forward<Args>(args)...);
    }

#else

#define BOOST_UNORDERED_CONSTRUCT_IMPL(z, num_params, _)                    \
    template <                                                              \
        class T,                                                            \
        BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)                        \
    >                                                                       \
    inline typename normal_construct_n<T>::type                             \
    construct_impl(void* address,                                           \
        BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params))                     \
    {                                                                       \
        new(address) T(                                                     \
            BOOST_UNORDERED_CALL_PARAMS(z, num_params));                    \
    }

    BOOST_PP_REPEAT_FROM_TO(4, BOOST_UNORDERED_EMPLACE_LIMIT,
        BOOST_UNORDERED_CONSTRUCT_IMPL, _)

#define BOOST_UNORDERED_CONSTRUCT_PAIR_IMPL(z, num_params, _)               \
    template <class T, class Key,                                           \
        BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)                        \
    >                                                                       \
    inline typename pair_construct_n<T>::type                               \
        construct_impl(void* address, BOOST_FWD_REF(Key) key,               \
        BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params))                     \
    {                                                                       \
        new((void*)(&static_cast<T*>(address)->first))                      \
        typename T::first_type(                                             \
            boost::forward<Key>(key));                                      \
        new((void*)(&static_cast<T*>(address)->second))                     \
        typename T::second_type(                                            \
            BOOST_UNORDERED_CALL_PARAMS(z, num_params));                    \
    }

    BOOST_PP_REPEAT_FROM_TO(3, BOOST_UNORDERED_EMPLACE_LIMIT,
        BOOST_UNORDERED_CONSTRUCT_PAIR_IMPL, _)

#undef BOOST_UNORDERED_CONSTRUCT_IMPL
#endif

    ///////////////////////////////////////////////////////////////////
    //
    // Node construction

    template <class Alloc, bool Unique>
    class node_constructor
    {
        typedef ::boost::unordered::detail::buckets<Alloc, Unique> buckets;
        typedef typename buckets::node node;
        typedef typename buckets::real_node_ptr real_node_ptr;
        typedef typename buckets::value_type value_type;
        typedef typename buckets::node_allocator node_allocator;

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

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)
        template <class... Args>
        void construct(Args&&... args)
        {
            construct_preamble();
            construct_impl<value_type>(node_->address(),
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
            construct_impl<value_type>(node_->address(),                       \
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
        typename buckets::node_ptr release()
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
                allocator_traits<node_allocator>::destroy(buckets_.node_alloc(),
                    boost::addressof(*node_));

            allocator_traits<node_allocator>::deallocate(buckets_.node_alloc(), node_, 1);
        }
    }

    template <class Alloc, bool Unique>
    inline void node_constructor<Alloc, Unique>::construct_preamble()
    {
        if(!node_) {
            node_constructed_ = false;
            value_constructed_ = false;

            node_ = allocator_traits<node_allocator>::allocate(buckets_.node_alloc(), 1);
            allocator_traits<node_allocator>::construct(buckets_.node_alloc(),
                boost::addressof(*node_), node());
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
    // basic exception safety. If an exception is thrown this will
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
                ++dst.size_;
    
                for(n = n->next_; n != group_end; n = n->next_) {
                    a.construct(node::get_value(n));
                    end = a.release();
                    node::set_hash(end, hash);
                    node::add_after_node(end, first_node);
                    ++dst.size_;
                }
                
                prev = dst.place_in_bucket(prev, end);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // move_buckets_to
    //
    // Basic exception safety. The source nodes are left in an unusable state
    // if an exception throws.

    template <class A, bool Unique>
    void buckets<A, Unique>::move_buckets_to(buckets& dst) const
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
    
                a.construct(boost::move(node::get_value(n)));
                node_ptr first_node = a.release();
                node::set_hash(first_node, hash);
                node_ptr end = prev->next_ = first_node;
                ++dst.size_;
    
                for(n = n->next_; n != group_end; n = n->next_) {
                    a.construct(boost::move(node::get_value(n)));
                    end = a.release();
                    node::set_hash(end, hash);
                    node::add_after_node(end, first_node);
                    ++dst.size_;
                }
                
                prev = dst.place_in_bucket(prev, end);
            }
        }
    }

    // strong otherwise exception safety
    template <class A, bool Unique>
    void buckets<A, Unique>::rehash_impl(std::size_t num_buckets)
    {
        BOOST_ASSERT(this->size_);

        buckets dst(this->node_alloc(), num_buckets);
        dst.create_buckets();
        
        bucket_ptr src_start = this->get_bucket(this->bucket_count_);
        bucket_ptr dst_start = dst.get_bucket(dst.bucket_count_);

        dst_start->next_ = src_start->next_;
        src_start->next_ = bucket_ptr();
        dst.size_ = this->size_;
        this->size_ = 0;

        node_ptr prev = dst_start;
        while (BOOST_UNORDERED_BORLAND_BOOL(prev->next_))
            prev = dst.place_in_bucket(prev, node::next_group2(prev));

        // Swap the new nodes back into the container and setup the
        // variables.
        dst.swap(*this); // no throw
    }
}}}

#endif
