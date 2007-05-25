// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_multimap_view.hpp
/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_multimap.

#ifndef BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_multimap_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_multimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a tr1::unordered_multimap.

See also const_unordered_multimap_view.
                                                                             **/

template< class Tag, class BimapType >
class unordered_multimap_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_multimap_adaptor,
        Tag,BimapType,
        local_iterator_type_by,const_local_iterator_type_by
    ),

    public ::boost::bimaps::detail::map_view_base<
                unordered_multimap_view<Tag,BimapType>,Tag,BimapType >

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_multimap_adaptor,
        Tag,BimapType,
        local_iterator_type_by,const_local_iterator_type_by

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(unordered_multimap_view,Tag,BimapType);

    public:

    unordered_multimap_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS

    unordered_multimap_view & operator=(const unordered_multimap_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP


