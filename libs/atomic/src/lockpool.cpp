#include <boost/atomic.hpp>

//  Copyright (c) 2011 Helge Bahmann
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

namespace boost {
namespace atomics {
namespace detail {

lockpool::lock_type lockpool::pool_[41];

}
}
}
