//-----------------------------------------------------------------------------
// boost mpl/iterator_tag.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

namespace boost {
namespace mpl {

struct input_iter_tag_;
struct fwd_iter_tag_;
struct bi_iter_tag_;
struct ra_iter_tag_;

typedef input_iter_tag_ input_iterator_tag;
typedef fwd_iter_tag_   forward_iterator_tag;
typedef bi_iter_tag_    bidirectional_iterator_tag;
typedef ra_iter_tag_    random_access_iterator_tag;

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
