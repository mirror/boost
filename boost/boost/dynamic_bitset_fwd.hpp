#ifndef BOOST_DYNAMIC_BITSET_FWD_HPP
#define BOOST_DYNAMIC_BITSET_FWD_HPP

#include <memory>

namespace boost {

template <typename Block = unsigned long,
          typename Allocator = std::allocator<Block> >
class dynamic_bitset;

} // namespace boost

#endif // BOOST_DYNAMIC_BITSET_FWD_HPP
