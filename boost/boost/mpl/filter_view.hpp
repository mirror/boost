//-----------------------------------------------------------------------------
// boost mpl/filter_view.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_FILTER_VIEW_HPP_INCLUDED
#define BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/aux_/filter_iter.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct filter_view
{
 private:    
    typedef typename lambda<Predicate>::type pred_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

 public:
    struct tag;
    typedef filter_view type;
    typedef typename aux::next_filter_iter< first_,last_,pred_ >::type begin;
    typedef aux::filter_iter< last_,last_,pred_ > end;
};

BOOST_MPL_AUX_VOID_SPEC(2, filter_view)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_FILTER_VIEW_HPP_INCLUDED
