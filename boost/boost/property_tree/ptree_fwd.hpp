// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/property_tree/detail/ptree_utils.hpp>
#include <functional>           // for std::less

namespace boost { namespace property_tree
{

    ///////////////////////////////////////////////////////////////////////////
    // Classes

    template<class C, class K, class P, class D, class X> class basic_ptree;
    template<class Key> class basic_path;
    class translator;

    class ptree_error;
    class ptree_bad_data;
    class ptree_bad_path;

    ///////////////////////////////////////////////////////////////////////////
    // Typedefs

    typedef basic_path<std::string> path;
    typedef basic_path<std::wstring> wpath;

    typedef basic_ptree<std::less<std::string>, std::string, path, std::string, translator> ptree;
    typedef basic_ptree<detail::less_nocase<std::string>, std::string, path, std::string, translator> iptree;
#ifndef BOOST_NO_CWCHAR
    typedef basic_ptree<std::less<std::wstring>, std::wstring, wpath, std::wstring, translator> wptree;
    typedef basic_ptree<detail::less_nocase<std::wstring>, std::wstring, wpath, std::wstring, translator> wiptree;
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Free functions

    template<class C, class K, class P, class D, class X> void swap(basic_ptree<C, K, P, D, X> &pt1, basic_ptree<C, K, P, D, X> &pt2);
    template<class Ptree> const Ptree &empty_ptree();
    path operator /(const path &p1, const path &p2);
    wpath operator /(const wpath &p1, const wpath &p2);

} }

#endif
