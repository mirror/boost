// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_SERIALIZATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_SERIALIZATION_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace property_tree
{

    ///////////////////////////////////////////////////////////////////////////
    // boost::serialization support

    template<class Archive, class C, class K, class P, class D, class X> 
    inline void save(Archive &ar, 
                     const basic_ptree<C, K, P, D, X> &t,
                     const unsigned int file_version)
    {
        serialization::stl::save_collection<Archive, basic_ptree<C, K, P, D, X> >(ar, t);
        ar << serialization::make_nvp("data", t.data());
    }

    template<class Archive, class C, class K, class P, class D, class X> 
    inline void load(Archive &ar, 
                     basic_ptree<C, K, P, D, X> &t,
                     const unsigned int file_version)
    {
        
        // Load children
        boost::serialization::stl::load_collection
        <
            Archive,
            basic_ptree<C, K, P, D, X>,
            boost::serialization::stl::archive_input_seq<Archive, basic_ptree<C, K, P, D, X> >,
            boost::serialization::stl::no_reserve_imp<basic_ptree<C, K, P, D, X> >
        >(ar, t);
        
        // Load data (must be after load_collection, as it calls clear())
        ar >> serialization::make_nvp("data", t.data());

    }

    template<class Archive, class C, class K, class P, class D, class X>
    inline void serialize(Archive &ar,
                          basic_ptree<C, K, P, D, X> &t,
                          const unsigned int file_version)
    {
        boost::serialization::split_free(ar, t, file_version);
    }

} }

#endif
