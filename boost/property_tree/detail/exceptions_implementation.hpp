// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED

namespace boost { namespace property_tree
{

    namespace detail
    {

        // Default path-to-string converter; this is overridden for default path
        template<class P>
        std::string path_to_string(const P &path)
        {
            return std::string("<cannot convert path to string>");
        }

        // Helper for preparing what string in ptree_bad_path exception
        template<class P> 
        std::string prepare_bad_path_what(const std::string &what, const P &path)
        {
            using namespace detail;     // To allow correct resolution of path_to_string()
            return what + " (" + path_to_string(path) + ")";
        }

        // Default data-to-string converter; this is overridden for default data (string)
        template<class D>
        std::string data_to_string(const D &data)
        {
            return std::string("<cannot convert data to string>");
        }

        // Helper for preparing what string in ptree_bad_data exception
        template<class D> 
        std::string prepare_bad_data_what(const std::string &what, const D &data)
        {
            using namespace detail;     // To allow correct resolution of data_to_string()
            return what + " (" + data_to_string(data) + ")";
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_error

    inline ptree_error::ptree_error(const std::string &what): 
        std::runtime_error(what) 
    { 
    }
    
    inline ptree_error::~ptree_error() throw()
    { 
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_data

    template<class D> 
    ptree_bad_data::ptree_bad_data(const std::string &what, const D &data):
        ptree_error(detail::prepare_bad_data_what(what, data)), 
        m_data(data)
    {
    }

    inline ptree_bad_data::~ptree_bad_data() throw()
    {
    }

    template<class D> 
    D ptree_bad_data::data()
    {
        return boost::any_cast<D>(m_data);
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_path

    template<class P> 
    ptree_bad_path::ptree_bad_path(const std::string &what, const P &path):
        ptree_error(detail::prepare_bad_path_what(what, path)), 
        m_path(path)
    {

    }

    inline ptree_bad_path::~ptree_bad_path() throw()
    {
    }

    template<class P> 
    P ptree_bad_path::path()
    {
        return boost::any_cast<P>(m_path);
    }

} }

#endif
