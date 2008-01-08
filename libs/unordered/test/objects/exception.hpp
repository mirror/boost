
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_OBJECTS_HEADER)
#define BOOST_UNORDERED_TEST_OBJECTS_HEADER

#include <cstddef>
#include <boost/limits.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/exception_safety.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <iostream>
#include "../helpers/fwd.hpp"
#include "../helpers/allocator.hpp"
#include <map>

#define RUN_EXCEPTION_TESTS(test_seq, param_seq) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(RUN_EXCEPTION_TESTS_OP, (test_seq)(param_seq))

#define RUN_EXCEPTION_TESTS_OP(r, product) \
    RUN_EXCEPTION_TESTS_OP2( \
        BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, product), \
            BOOST_PP_CAT(_, BOOST_PP_SEQ_ELEM(1, product)) \
        ), \
        BOOST_PP_SEQ_ELEM(0, product), \
        BOOST_PP_SEQ_ELEM(1, product) \
    )

#define RUN_EXCEPTION_TESTS_OP2(name, test_func, type) \
    BOOST_AUTO_TEST_CASE(name) \
    { \
        test_func< type > fixture; \
        ::test::exception_safety(fixture, BOOST_STRINGIZE(test_func<type>)); \
    }

#define SCOPE(scope_name) \
    for(::test::scope_guard unordered_test_guard( \
            BOOST_STRINGIZE(scope_name)); \
        !unordered_test_guard.dismissed(); \
        unordered_test_guard.dismiss())

#define EPOINT(name) \
    if(::test::exceptions_enabled) { \
        BOOST_ITEST_EPOINT(name); \
    }

#define ENABLE_EXCEPTIONS \
    ::test::exceptions_enable BOOST_PP_CAT(ENABLE_EXCEPTIONS_, __LINE__)(true)
#define DISABLE_EXCEPTIONS \
    ::test::exceptions_enable BOOST_PP_CAT(ENABLE_EXCEPTIONS_, __LINE__)(false)

#define HASH_CHECK(test) if(!(test)) BOOST_ERROR(BOOST_STRINGIZE(test))

namespace test {
    static char const* scope = "";
    bool exceptions_enabled = false;

    class scope_guard {
        scope_guard& operator=(scope_guard const&);
        scope_guard(scope_guard const&);

        char const* old_scope_;
        char const* scope_;
        bool dismissed_;
    public:
        scope_guard(char const* name)
            : old_scope_(scope),
            scope_(name),
            dismissed_(false)
        {
            scope = scope_;
        }

        ~scope_guard() {
            if(dismissed_) scope = old_scope_;
        }

        void dismiss() {
            dismissed_ = true;
        }

        bool dismissed() const {
            return dismissed_;
        }
    };

    class exceptions_enable
    {
        exceptions_enable& operator=(exceptions_enable const&);
        exceptions_enable(exceptions_enable const&);

        bool old_value_;
    public:
        exceptions_enable(bool enable)
            : old_value_(exceptions_enabled)
        {
            exceptions_enabled = enable;
        }

        ~exceptions_enable()
        {
            exceptions_enabled = old_value_;
        }
    };

    struct exception_base {
        struct data_type {};
        struct strong_type {
            template <class T> void store(T const&) {}
            template <class T> void test(T const&) const {}
        };
        data_type init() const { return data_type(); }
        void check() const {}
    };

    template <class T, class P1, class P2, class T2>
    inline void call_ignore_extra_parameters(void (T::*fn)() const, T2 const& obj,
            P1&, P2&)
    {
        (obj.*fn)();
    }

    template <class T, class P1, class P2, class T2>
    inline void call_ignore_extra_parameters(void (T::*fn)(P1&) const, T2 const& obj,
            P1& p1, P2&)
    {
        (obj.*fn)(p1);
    }

    template <class T, class P1, class P2, class T2>
    inline void call_ignore_extra_parameters(void (T::*fn)(P1&, P2&) const, T2 const& obj,
            P1& p1, P2& p2)
    {
        (obj.*fn)(p1, p2);
    }

    template <class T>
    T const& constant(T const& x) {
        return x;
    }

    template <class Test>
    class test_runner
    {
        Test const& test_;
    public:
        test_runner(Test const& t) : test_(t) {}
        void operator()() const {
            DISABLE_EXCEPTIONS;
            typename Test::data_type x(test_.init());
            typename Test::strong_type strong;
            strong.store(x);
            try {
                ENABLE_EXCEPTIONS;
                call_ignore_extra_parameters(&Test::run, test_, x, strong);
            }
            catch(...) {
                call_ignore_extra_parameters(&Test::check, test_,
                        constant(x), constant(strong));
                throw;
            }
        }
    };

    template <class Test>
    void exception_safety(Test const& f, char const* name) {
        test_runner<Test> runner(f);
        ::boost::itest::exception_safety(runner, name);
    }
}

namespace test
{
namespace exception
{
    namespace detail
    {
        // This annoymous namespace won't cause ODR violations as I won't
        // be linking multiple translation units together. I'll probably
        // move this into a cpp file before a full release, but for now it's
        // the most convenient way.
        namespace
        {
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
                    tag_(tag) {}

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

            typedef std::map<memory_area, memory_track, memory_area_compare,
                test::malloc_allocator<std::pair<memory_area const, memory_track> > >
                allocated_memory_type;
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
            HASH_CHECK(count_allocators > 0);
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

                    HASH_CHECK(no_allocations_left);
                    HASH_CHECK(no_constructions_left);
                    HASH_CHECK(allocated_memory_empty);
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
                HASH_CHECK(pos->first.start == ptr);
                HASH_CHECK(pos->first.end == (char*) ptr + n * size);
                HASH_CHECK(pos->second.tag_ == tag);
                allocated_memory.erase(pos);
            }
            HASH_CHECK(count_allocations > 0);
            if(count_allocations > 0) --count_allocations;
        }

        void track_construct(void* ptr, std::size_t /*size*/, int tag)
        {
            ++count_constructions;
        }

        void track_destroy(void* ptr, std::size_t /*size*/, int tag)
        {
            HASH_CHECK(count_constructions > 0);
            if(count_constructions > 0) --count_constructions;
        }
    }

    class object;
    class hash;
    class equal_to;
    template <class T> class allocator;

    class object
    {
    public:
        int tag1_, tag2_;

        explicit object() : tag1_(0), tag2_(0)
        {
            SCOPE(object::object()) {
                EPOINT("Mock object default constructor.");
            }
        }

        explicit object(int t1, int t2 = 0) : tag1_(t1), tag2_(t2)
        {
            SCOPE(object::object(int)) {
                EPOINT("Mock object constructor by value.");
            }
        }

        object(object const& x)
             : tag1_(x.tag1_), tag2_(x.tag2_)
        {
            SCOPE(object::object(object)) {
                EPOINT("Mock object copy constructor.");
            }
        }

        ~object() {
            tag1_ = -1;
            tag2_ = -1;
        }

        object& operator=(object const& x)
        {
            SCOPE(object::operator=(object)) {
                tag1_ = x.tag1_;
                EPOINT("Mock object assign operator 1.");
                tag2_ = x.tag2_;
                //EPOINT("Mock object assign operator 2.");
            }
            return *this;
        }

        friend bool operator==(object const& x1, object const& x2) {
            SCOPE(operator==(object, object)) {
                EPOINT("Mock object equality operator.");
            }

            return x1.tag1_ == x2.tag1_ && x1.tag2_ == x2.tag2_;
        }

        friend bool operator!=(object const& x1, object const& x2) {
            SCOPE(operator!=(object, object)) {
                EPOINT("Mock object inequality operator.");
            }

            return !(x1.tag1_ == x2.tag1_ && x1.tag2_ == x2.tag2_);
        }

        // None of the last few functions are used by the unordered associative
        // containers - so there aren't any exception points.
        friend bool operator<(object const& x1, object const& x2) {
            return x1.tag1_ < x2.tag1_ ||
                (x1.tag1_ == x2.tag1_ && x1.tag2_ < x2.tag2_);
        }

        friend object generate(object const*) {
            int* x = 0;
            return object(::test::generate(x), ::test::generate(x));
        }

        friend std::ostream& operator<<(std::ostream& out, object const& o)
        {
            return out<<"("<<o.tag1_<<","<<o.tag2_<<")";
        }
    };

    class hash
    {
        int tag_;
    public:
        hash(int t = 0) : tag_(t)
        {
            SCOPE(hash::object()) {
                EPOINT("Mock hash default constructor.");
            }
        }

        hash(hash const& x)
            : tag_(x.tag_)
        {
            SCOPE(hash::hash(hash)) {
                EPOINT("Mock hash copy constructor.");
            }
        }

        hash& operator=(hash const& x)
        {
            SCOPE(hash::operator=(hash)) {
                EPOINT("Mock hash assign operator 1.");
                tag_ = x.tag_;
                EPOINT("Mock hash assign operator 2.");
            }
            return *this;
        }

        std::size_t operator()(object const& x) const {
            SCOPE(hash::operator()(object)) {
                EPOINT("Mock hash function.");
            }

            switch(tag_) {
            case 1:
                return x.tag1_;
            case 2:
                return x.tag2_;
            default:
                return x.tag1_ + x.tag2_; 
            }
        }

        friend bool operator==(hash const& x1, hash const& x2) {
            SCOPE(operator==(hash, hash)) {
                EPOINT("Mock hash equality function.");
            }
            return x1.tag_ == x2.tag_;
        }

        friend bool operator!=(hash const& x1, hash const& x2) {
            SCOPE(hash::operator!=(hash, hash)) {
                EPOINT("Mock hash inequality function.");
            }
            return x1.tag_ != x2.tag_;
        }
    };

    class equal_to
    {
        int tag_;
    public:
        equal_to(int t = 0) : tag_(t)
        {
            SCOPE(equal_to::equal_to()) {
                EPOINT("Mock equal_to default constructor.");
            }
        }

        equal_to(equal_to const& x)
            : tag_(x.tag_)
        {
            SCOPE(equal_to::equal_to(equal_to)) {
                EPOINT("Mock equal_to copy constructor.");
            }
        }

        equal_to& operator=(equal_to const& x)
        {
            SCOPE(equal_to::operator=(equal_to)) {
                EPOINT("Mock equal_to assign operator 1.");
                tag_ = x.tag_;
                EPOINT("Mock equal_to assign operator 2.");
            }
            return *this;
        }

        bool operator()(object const& x1, object const& x2) const {
            SCOPE(equal_to::operator()(object, object)) {
                EPOINT("Mock equal_to function.");
            }

            switch(tag_) {
            case 1:
                return x1.tag1_ == x2.tag1_;
            case 2:
                return x1.tag2_ == x2.tag2_;
            default:
                return x1 == x2; 
            }
        }

        friend bool operator==(equal_to const& x1, equal_to const& x2) {
            SCOPE(operator==(equal_to, equal_to)) {
                EPOINT("Mock equal_to equality function.");
            }
            return x1.tag_ == x2.tag_;
        }

        friend bool operator!=(equal_to const& x1, equal_to const& x2) {
            SCOPE(operator!=(equal_to, equal_to)) {
                EPOINT("Mock equal_to inequality function.");
            }
            return x1.tag_ != x2.tag_;
        }
    };

    template <class T>
    class allocator
    {
    public:
        int tag_;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T const* const_pointer;
        typedef T& reference;
        typedef T const& const_reference;
        typedef T value_type;

        template <class U> struct rebind { typedef allocator<U> other; };

        explicit allocator(int t = 0) : tag_(t)
        {
            SCOPE(allocator::allocator()) {
                EPOINT("Mock allocator default constructor.");
            }
            detail::allocator_ref();
        }

        template <class Y> allocator(allocator<Y> const& x) : tag_(x.tag_)
        {
            SCOPE(allocator::allocator()) {
                EPOINT("Mock allocator template copy constructor.");
            }
            detail::allocator_ref();
        }

        allocator(allocator const& x) : tag_(x.tag_)
        {
            SCOPE(allocator::allocator()) {
                EPOINT("Mock allocator copy constructor.");
            }
            detail::allocator_ref();
        }

        ~allocator() {
            detail::allocator_unref();
        }

        allocator& operator=(allocator const& x) {
            SCOPE(allocator::allocator()) {
                EPOINT("Mock allocator assignment operator.");
                tag_ = x.tag_;
            }
            return *this;
        }

        // If address throws, then it can't be used in erase or the
        // destructor, which is very limiting. I need to check up on
        // this.

        pointer address(reference r) {
            //SCOPE(allocator::address(reference)) {
            //    EPOINT("Mock allocator address function.");
            //}
            return pointer(&r);
        }

        const_pointer address(const_reference r)  {
            //SCOPE(allocator::address(const_reference)) {
            //    EPOINT("Mock allocator const address function.");
            //}
            return const_pointer(&r);
        }

        pointer allocate(size_type n) {
            T* ptr = 0;
            SCOPE(allocator::allocate(size_type)) {
                EPOINT("Mock allocator allocate function.");

                using namespace std;
                ptr = (T*) malloc(n * sizeof(T));
                if(!ptr) throw std::bad_alloc();
            }
            detail::track_allocate((void*) ptr, n, sizeof(T), tag_);
            return pointer(ptr);

            //return pointer(static_cast<T*>(::operator new(n * sizeof(T))));
        }

        pointer allocate(size_type n, const_pointer u)
        {
            T* ptr = 0;
            SCOPE(allocator::allocate(size_type, const_pointer)) {
                EPOINT("Mock allocator allocate function.");

                using namespace std;
                ptr = (T*) malloc(n * sizeof(T));
                if(!ptr) throw std::bad_alloc();
            }
            detail::track_allocate((void*) ptr, n, sizeof(T), tag_);
            return pointer(ptr);

            //return pointer(static_cast<T*>(::operator new(n * sizeof(T))));
        }

        void deallocate(pointer p, size_type n)
        {
            //::operator delete((void*) p);
            if(p) {
                detail::track_deallocate((void*) p, n, sizeof(T), tag_);
                using namespace std;
                free(p);
            }
        }

        void construct(pointer p, T const& t) {
            SCOPE(allocator::construct(pointer, T)) {
                EPOINT("Mock allocator construct function.");
                new(p) T(t);
            }
            detail::track_construct((void*) p, sizeof(T), tag_);
        }

        void destroy(pointer p) {
            detail::track_destroy((void*) p, sizeof(T), tag_);
            p->~T();
        }

        size_type max_size() const {
            SCOPE(allocator::construct(pointer, T)) {
                EPOINT("Mock allocator max_size function.");
            }
            return (std::numeric_limits<std::size_t>::max)();
        }
    };

    template <class T>
    void swap(allocator<T>& x, allocator<T>& y)
    {
        std::swap(x.tag_, y.tag_);
    }

    // It's pretty much impossible to write a compliant swap when these
    // two can throw. So they don't.

    template <class T>
    inline bool operator==(allocator<T> const& x, allocator<T> const& y)
    {
        //SCOPE(operator==(allocator, allocator)) {
        //    EPOINT("Mock allocator equality operator.");
        //}
        return x.tag_ == y.tag_;
    }

    template <class T>
    inline bool operator!=(allocator<T> const& x, allocator<T> const& y)
    {
        //SCOPE(operator!=(allocator, allocator)) {
        //    EPOINT("Mock allocator inequality operator.");
        //}
        return x.tag_ != y.tag_;
    }
}
}

#endif

