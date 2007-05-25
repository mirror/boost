// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_map_view.hpp
/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_map.

#ifndef BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_map_adaptor.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Map View of a bimap, signature compatible with tr1::unordered_map.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a tr1::unordered_map.

See also const_unordered_map_view.
                                                                             **/


template< class Tag, class BimapType >
class unordered_map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_iterator_type_by,const_local_iterator_type_by
    ),

    public ::boost::bimaps::detail::map_view_base<
                unordered_map_view<Tag,BimapType>,Tag,BimapType >,
    public ::boost::bimaps::detail::
                unique_map_view_access<
                    unordered_map_view<Tag,BimapType>, Tag,  BimapType>::type

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_iterator_type_by,const_local_iterator_type_by

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(unordered_map_view,Tag,BimapType);

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        unique_map_view_access<
            unordered_map_view<Tag,BimapType>, Tag,  BimapType

        >::type unique_map_view_access_;

    public:

    unordered_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    using unique_map_view_access_::at;
    using unique_map_view_access_::operator[];

    unordered_map_view & operator=(const unordered_map_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP


