/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/path.hpp
 * Date:        Sat Jun 21 21:24:05 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class boost::iostreams::detail::path, for storing a 
 * a std::string or std::wstring.
 *
 * This class allows interoperability with Boost.Filesystem without
 * creating a dependence on Boost.Filesystem headers or implementation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED

#include <string>
#include <boost/static_assert.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace iostreams { namespace detail {

class path {
public:

    // Default constructor
    path() : narrow_(), wide_(), is_wide_(false) { }

    // Constructor taking a std::string
    path(const std::string& p) : narrow_(p), wide_(), is_wide_(false) { }

    // Constructor taking a C-style string
    path(const char* p) : narrow_(p), wide_(), is_wide_(false) { }

    // Constructor taking a boost::filesystem::path or boost::filesystem::wpath
    template<typename Path>
    explicit path(const Path& p)
    {
        typedef typename Path::external_string_type string_type;
        init(p, boost::type<string_type>());
    }

    // Copy constructor
    path(const path& p) 
        : narrow_(p.narrow_), wide_(p.wide_), is_wide_(p.is_wide_) 
        { }

    // Assignment operator taking another path
    path& operator=(const path& p)
    {
        narrow_ = p.narrow_;
        wide_ = p.wide_;
        is_wide_ = p.is_wide_;
    }

    // Assignment operator taking a std::string
    path& operator=(const std::string& p)
    {
        narrow_ = p;
        wide_.clear();
        is_wide_ = false;
    }

    // Assignment operator taking a C-style string
    path& operator=(const char* p)
    {
        narrow_.assign(p);
        wide_.clear();
        is_wide_ = false;
    }

    // Assignment operator taking a Boost.Filesystem path
    template<typename Path>
    path& operator=(const Path& p)
    {
        typedef typename Path::external_string_type string_type;
        init(p, boost::type<string_type>());
    }

    bool is_wide() const { return is_wide_; }

    // Returns a representation of the underlying path as a std::string
    // Requires: is_wide() returns false
    std::string to_string() const { return narrow_; }

    // Returns a representation of the underlying path as a std::wstring
    // Requires: is_wide() returns true
    std::wstring to_wstring() const { return wide_; }
private:
    
    // For wide-character paths, use a boost::filesystem::wpath instead of a
    // std::wstring
    path(const std::wstring&);
    path& operator=(const std::wstring&);

    template<typename Path>
    void init(const Path& p, boost::type<std::string>)
    {
        narrow_ = p.external_file_string();
        wide_.clear();
        is_wide_ = false;
    }

    template<typename Path>
    void init(const Path& p, boost::type<std::wstring>)
    {
        wide_ = p.external_file_string();
        narrow_.clear();
        is_wide_ = true;
    }

    std::string   narrow_;
    std::wstring  wide_;
    bool          is_wide_;
};

inline bool operator==(const path& lhs, const path& rhs)
{
    return lhs.is_wide() ?
        rhs.is_wide() && lhs.to_wstring() == rhs.to_wstring() :
        !rhs.is_wide() && lhs.to_string() == rhs.to_string();
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED
