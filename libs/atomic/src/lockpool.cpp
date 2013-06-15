#include <boost/config.hpp>
#include <boost/atomic.hpp>

//  Copyright (c) 2011 Helge Bahmann
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

namespace boost {
namespace atomics {
namespace detail {

namespace {

// This seems to be the maximum across all modern CPUs
enum { cache_line_size = 64 };

template< unsigned int N >
struct padding
{
    char data[N];
};
template< >
struct padding< 0 >
{
};

struct BOOST_ALIGNMENT(cache_line_size) padded_lock
{
    lockpool::lock_type lock;
    // The additional padding is needed to avoid false sharing between locks
    enum { padding_size = (sizeof(lockpool::lock_type) <= cache_line_size ? (cache_line_size - sizeof(lockpool::lock_type)) : (cache_line_size - sizeof(lockpool::lock_type) % cache_line_size)) };
    padding< padding_size > pad;
};

static padded_lock lock_pool_[41];

} // namespace


// NOTE: This function must NOT be inline. Otherwise MSVC 9 will sometimes generate broken code for modulus operation which result in crashes.
BOOST_ATOMIC_DECL lockpool::lock_type& lockpool::get_lock_for(const volatile void* addr)
{
    std::size_t index = reinterpret_cast<std::size_t>(addr) % (sizeof(lock_pool_) / sizeof(*lock_pool_));
    return lock_pool_[index].lock;
}

}
}
}
