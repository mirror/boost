
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_OBJECTS_HEADER)
#define BOOST_UNORDERED_TEST_OBJECTS_HEADER

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <cstddef>
#include "../helpers/fwd.hpp"
#include <iostream>
#include <map>

namespace test
{
    // Note that the default hash function will work for any equal_to (but not
    // very well).
    class object;
    class hash;
    class less;
    class equal_to;
    template <class T> class allocator;

    class object
    {
        friend class hash;
        friend class equal_to;
        friend class less;
        int tag1_, tag2_;
    public:
        explicit object(int t1 = 0, int t2 = 0) : tag1_(t1), tag2_(t2) {}

        ~object() {
            tag1_ = -1;
            tag2_ = -1;
        }

        friend bool operator==(object const& x1, object const& x2) {
            return x1.tag1_ == x2.tag1_ && x1.tag2_ == x2.tag2_;
        }

        friend bool operator!=(object const& x1, object const& x2) {
            return x1.tag1_ != x2.tag1_ || x1.tag2_ != x2.tag2_;
        }

        friend bool operator<(object const& x1, object const& x2) {
            return x1.tag1_ < x2.tag1_ ||
                (x1.tag1_ == x2.tag1_ && x1.tag2_ < x2.tag2_);
        }

        friend object generate(object const*) {
            int* x = 0;
            return object(generate(x), generate(x));
        }

        friend std::ostream& operator<<(std::ostream& out, object const& o)
        {
            return out<<"("<<o.tag1_<<","<<o.tag2_<<")";
        }
    };

    // This object is usd to test how well the containers cope with equivalent keys.
    class equivalent_object
    {
        friend class hash;
        friend class equal_to;
        friend class less;
        int tag1_, tag2_;
    public:
        explicit equivalent_object(int t1 = 0, int t2 = 0) : tag1_(t1), tag2_(t2) {}

        ~equivalent_object() {
            tag1_ = -1;
            tag2_ = -1;
        }

        friend bool operator==(equivalent_object const& x1, equivalent_object const& x2) {
            return x1.tag1_ == x2.tag1_;
        }

        friend bool operator!=(equivalent_object const& x1, equivalent_object const& x2) {
            return x1.tag1_ != x2.tag1_;
        }

        friend bool operator<(equivalent_object const& x1, equivalent_object const& x2) {
            return x1.tag1_ < x2.tag1_;
        }

        friend equivalent_object generate(equivalent_object const*) {
            signed char* x = 0;
            return equivalent_object(generate(x), generate(x));
        }

        friend std::ostream& operator<<(std::ostream& out, equivalent_object const& o)
        {
            return out<<"("<<o.tag1_<<","<<o.tag2_<<")";
        }
    };

    class hash
    {
        int type_;
    public:
        explicit hash(int t = 0) : type_(t) {}

        std::size_t operator()(object const& x) const {
            switch(type_) {
            case 1:
                return x.tag1_;
            case 2:
                return x.tag2_;
            default:
                return x.tag1_ + x.tag2_; 
            }
        }

        std::size_t operator()(equivalent_object const& x) const {
            return x.tag1_;
        }

        std::size_t operator()(int x) const {
            return x;
        }

        friend bool operator==(hash const& x1, hash const& x2) {
            return x1.type_ == x2.type_;
        }

        friend bool operator!=(hash const& x1, hash const& x2) {
            return x1.type_ != x2.type_;
        }
    };

    class less
    {
        int type_;
    public:
        explicit less(int t = 0) : type_(t) {}

        bool operator()(object const& x1, object const& x2) const {
            switch(type_) {
            case 1:
                return x1.tag1_ < x2.tag1_;
            case 2:
                return x1.tag2_ < x2.tag2_;
            default:
                return x1 < x2;
            }
        }

        bool operator()(equivalent_object const& x1, equivalent_object const& x2) const {
            return x1 < x2;
        }

        std::size_t operator()(int x1, int x2) const {
            return x1 < x2;
        }

        friend bool operator==(less const& x1, less const& x2) {
            return x1.type_ == x2.type_;
        }
    };

    class equal_to
    {
        int type_;
    public:
        explicit equal_to(int t = 0) : type_(t) {}

        bool operator()(object const& x1, object const& x2) const {
            switch(type_) {
            case 1:
                return x1.tag1_ == x2.tag1_;
            case 2:
                return x1.tag2_ == x2.tag2_;
            default:
                return x1 == x2;
            }
        }

        bool operator()(equivalent_object const& x1, equivalent_object const& x2) const {
            return x1 == x2;
        }

        std::size_t operator()(int x1, int x2) const {
            return x1 == x2;
        }

        friend bool operator==(equal_to const& x1, equal_to const& x2) {
            return x1.type_ == x2.type_;
        }

        friend bool operator!=(equal_to const& x1, equal_to const& x2) {
            return x1.type_ != x2.type_;
        }

        friend less create_compare(equal_to x) {
            return less(x.type_);
        }
    };

    namespace detail
    {
        // This annoymous namespace won't cause ODR violations as I won't
        // be linking multiple translation units together. I'll probably
        // move this into a cpp file before a full release, but for now it's
        // the most convenient way.
        namespace {
            struct memory_area {
                void const* start;
                void const* end;

                memory_area(void const* s, void const* e)
                    : start(s), end(e)
                {
                    BOOST_ASSERT(start != end);
                }
            };

            struct memory_track {
                explicit memory_track(int tag = -1) :
                    constructed_(0),
                    tag_(tag) {}

                int constructed_;
                int tag_;
            };

            // This is a bit dodgy as it defines overlapping
            // areas as 'equal', so this isn't a total ordering.
            // But it is for non-overlapping memory regions - which
            // is what'll be stored.
            //
            // All searches will be for areas entirely contained by
            // a member of the set - so it should find the area that contains
            // the region that is searched for.

            struct memory_area_compare {
                bool operator()(memory_area const& x, memory_area const& y) const {
                    return x.end <= y.start;
                }
            };

            typedef std::map<memory_area, memory_track, memory_area_compare> allocated_memory_type;
            allocated_memory_type allocated_memory;
            unsigned int count_allocators = 0;
            unsigned int count_allocations = 0;
            unsigned int count_constructions = 0;
        }

        void allocator_ref()
        {
            if(count_allocators == 0) {
                count_allocations = 0;
                count_constructions = 0;
                allocated_memory.clear();
            }
            ++count_allocators;
        }

        void allocator_unref()
        {
            BOOST_TEST(count_allocators > 0);
            if(count_allocators > 0) {
                --count_allocators;
                if(count_allocators == 0) {
                    bool no_allocations_left = (count_allocations == 0);
                    bool no_constructions_left = (count_constructions == 0);
                    bool allocated_memory_empty = allocated_memory.empty();

                    // Clearing the data before the checks terminate the tests.
                    count_allocations = 0;
                    count_constructions = 0;
                    allocated_memory.clear();

                    BOOST_TEST(no_allocations_left);
                    BOOST_TEST(no_constructions_left);
                    BOOST_TEST(allocated_memory_empty);
                }
            }
        }

        void track_allocate(void *ptr, std::size_t n, std::size_t size, int tag)
        {
            if(n == 0) {
                BOOST_ERROR("Allocating 0 length array.");
            }
            else {
                ++count_allocations;
                allocated_memory[memory_area(ptr, (char*) ptr + n * size)] =
                    memory_track(tag);
            }
        }

        void track_deallocate(void* ptr, std::size_t n, std::size_t size, int tag)
        {
            allocated_memory_type::iterator pos
                = allocated_memory.find(memory_area(ptr, (char*) ptr + n * size));
            if(pos == allocated_memory.end()) {
                BOOST_ERROR("Deallocating unknown pointer.");
            } else {
                BOOST_TEST(pos->first.start == ptr);
                BOOST_TEST(pos->first.end == (char*) ptr + n * size);
                BOOST_TEST(pos->second.tag_ == tag);
                BOOST_TEST(pos->second.constructed_ == 0);
                allocated_memory.erase(pos);
            }
            BOOST_TEST(count_allocations > 0);
            if(count_allocations > 0) --count_allocations;
        }

        void track_construct(void* ptr, std::size_t size, int tag)
        {
            allocated_memory_type::iterator pos
                = allocated_memory.find(memory_area(ptr, (char*) ptr + size));
            if(pos == allocated_memory.end()) {
                BOOST_ERROR("Constructing unknown pointer.");
            }
            else {
                BOOST_TEST(pos->second.tag_ == tag);
                ++pos->second.constructed_;
            }
            ++count_constructions;
        }

        void track_destroy(void* ptr, std::size_t size, int tag)
        {
            allocated_memory_type::iterator pos
                = allocated_memory.find(memory_area(ptr, (char*) ptr + size));
            if(pos == allocated_memory.end())
                BOOST_ERROR("Destroying unknown pointer.");
            else {
                BOOST_TEST(pos->second.tag_ == tag);
                BOOST_TEST(pos->second.constructed_ > 0);
                if(pos->second.constructed_ > 0) --pos->second.constructed_;
            }
            BOOST_TEST(count_constructions > 0);
            if(count_constructions > 0) --count_constructions;
        }
    }

    template <class T>
    class allocator
    {
# ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    public:
# else
        template <class> friend class allocator;
# endif
        int tag_;
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T const* const_pointer;
        typedef T& reference;
        typedef T const& const_reference;
        typedef T value_type;

        template <class U> struct rebind { typedef allocator<U> other; };

        explicit allocator(int t = 0) : tag_(t) { detail::allocator_ref(); }
        template <class Y> allocator(allocator<Y> const& x) : tag_(x.tag_) { detail::allocator_ref(); }
        allocator(allocator const& x) : tag_(x.tag_) { detail::allocator_ref(); }
        ~allocator() { detail::allocator_unref(); }

        pointer address(reference r) { return pointer(&r); }
        const_pointer address(const_reference r) { return const_pointer(&r); }

        pointer allocate(size_type n) {
            pointer ptr(static_cast<T*>(::operator new(n * sizeof(T))));
            detail::track_allocate((void*) ptr, n, sizeof(T), tag_);
            return ptr;
        }

        pointer allocate(size_type n, const_pointer u)
        {
            pointer ptr(static_cast<T*>(::operator new(n * sizeof(T))));
            detail::track_allocate((void*) ptr, n, sizeof(T), tag_);
            return ptr;
        }

        void deallocate(pointer p, size_type n)
        {
            detail::track_deallocate((void*) p, n, sizeof(T), tag_);
            ::operator delete((void*) p);
        }

        void construct(pointer p, T const& t) {
            detail::track_construct((void*) p, sizeof(T), tag_);
            new(p) T(t);
        }

        void destroy(pointer p) {
            detail::track_destroy((void*) p, sizeof(T), tag_);
            p->~T();
        }

        size_type max_size() const {
            return (std::numeric_limits<size_type>::max)();
        }

        bool operator==(allocator const& x) const
        {
            return tag_ == x.tag_;
        }

        bool operator!=(allocator const& x) const
        {
            return tag_ != x.tag_;
        }
    };

    template <class T>
    bool equivalent_impl(allocator<T> const& x, allocator<T> const& y, test::derived_type) {
        return x == y;
    }

#if BOOST_WORKAROUND(__GNUC__, < 3)
    void swap(test::object& x, test::object& y) {
        test::object tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    void swap(test::equivalent_object& x, test::equivalent_object& y) {
        test::equivalent_object tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    void swap(test::hash& x, test::hash& y) {
        test::hash tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    void swap(test::less& x, test::less& y) {
        test::less tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    void swap(test::equal_to& x, test::equal_to& y) {
        test::equal_to tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    template <class T>
    void swap(test::allocator<T>& x, test::allocator<T>& y) {
        test::allocator<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }
#endif
}

#endif
