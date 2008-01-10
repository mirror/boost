
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_MEMORY_HEADER)
#define BOOST_UNORDERED_TEST_MEMORY_HEADER

#define HASH_CHECK(test) if(!(test)) BOOST_ERROR(BOOST_STRINGIZE(test))

namespace test
{
    namespace detail
    {
        // This annoymous namespace won't cause ODR violations as I won't
        // be linking multiple translation units together. I'll probably
        // move this into a cpp file before a full release, but for now it's
        // the most convenient way.

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

        struct default_allocator_holder { template <class T> struct apply {
            typedef std::allocator<T> type; }; };

        template <class AllocatorHolder = default_allocator_holder>
        struct memory_tracker {
            typedef std::map<memory_area, memory_track, memory_area_compare,
                BOOST_DEDUCED_TYPENAME AllocatorHolder::
                template apply<std::pair<memory_area const, memory_track> >::type
            > allocated_memory_type;

            allocated_memory_type allocated_memory;
            unsigned int count_allocators;
            unsigned int count_allocations;
            unsigned int count_constructions;

            memory_tracker() :
                count_allocators(0), count_allocations(0),
                count_constructions(0)
            {}

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
                BOOST_DEDUCED_TYPENAME allocated_memory_type::iterator pos
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
        };
    }
}

#endif
