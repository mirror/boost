#ifndef RANGE_LIST_RG072501_HPP
#define RANGE_LIST_RG072501_HPP
//
// range_list.hpp - helper to build boost::arrays for *_set types
//

#include "boost/array.hpp"

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// choose range list begins
//

struct choose_range_list_n {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,NumRanges> type;
  };
};

struct choose_range_list_zero {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,1> type;
  };
};


template <std::size_t NumRanges>
struct range_list_gen_helper {
  typedef choose_range_list_n choice;
};

template <>
struct range_list_gen_helper<0> {
  typedef choose_range_list_zero choice;
};

template <typename T, std::size_t NumRanges>
struct range_list_generator {
private:
  typedef typename range_list_gen_helper<NumRanges>::choice Choice;
public:
  typedef typename Choice::template bind<T,NumRanges>::type type;
};

//
// choose range list ends
/////////////////////////////////////////////////////////////////////////

} // namespace multi_array
} // namespace detail
} // namespace boost

#endif // RANGE_LIST_RG072501_HPP
