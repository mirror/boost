#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/config.hpp>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>

namespace boost { 
namespace archive {

template<class Archive>
class binary_iarchive_impl : 
    public basic_binary_iprimitive<Archive, std::istream>,
    public basic_binary_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_iarchive<Archive>;
    friend class basic_binary_iarchive<Archive>;
    friend class load_access;
#endif
protected:
    void init(){
        basic_binary_iarchive<Archive>::init();
        basic_binary_iprimitive<Archive, std::istream>::init();
    }
    binary_iarchive_impl(std::istream & is, unsigned int flags = 0) :
        basic_binary_iprimitive<Archive, std::istream>(
            is, 
            0 != (flags & no_codecvt)
        )
    {
        if(0 == (flags & no_header)){
            #if ! defined(__MWERKS__)
                this->basic_binary_iarchive<Archive>::init();
                this->basic_binary_iprimitive<Archive, std::istream>::init();
            #else
                basic_binary_iarchive<Archive>::init();
                basic_binary_iprimitive<Archive, std::istream>::init();
            #endif
        }
    }
};

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class binary_iarchive : 
    public binary_iarchive_impl<binary_iarchive>
{
public:
    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<binary_iarchive>(is, flags)
    {
    }
};

} // namespace archive
} // namespace boost

// required by smart_cast for compilers not implementing 
// partial template specialization
BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(boost::archive::binary_iarchive)

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_HPP
