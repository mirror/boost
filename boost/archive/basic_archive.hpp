#ifndef BOOST_ARCHIVE_BASIC_ARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_archive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cassert>
#include <boost/config.hpp>
#include <boost/cstdint.hpp> // size_t
#include <boost/noncopyable.hpp>
#include <boost/integer_traits.hpp>
#include <boost/serialization/strong_typedef.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#define BOOST_ARCHIVE_STRONG_TYPEDEF(T, D)        \
namespace boost {                                 \
namespace archive {                               \
BOOST_STRONG_TYPEDEF(T, D)                        \
} /* archive */                                   \
template<>                                        \
class integer_traits<boost::archive::D>  :        \
    public integer_traits<boost::T>               \
{};                                               \
} /* boost */                                     \
/**/

/* NOTE : Warning  : Warning : Warning : Warning : Warning
 * Don't ever changes this.  If you do, they previously created
 * binary archives won't be readable !!!
 */
BOOST_ARCHIVE_STRONG_TYPEDEF(uint_least16_t, library_version_type)

/* NOTE : Warning  : Warning : Warning : Warning : Warning
 * If any of these are changed to different sized types, 
 * binary_iarchive won't be able to read older archives
 * unless you rev the library version and include conditional
 * code based on the library version.  There is nothing
 * inherently wrong in doing this - but you have to be super
 * careful because it's easy to get wrong and start breaking
 * old archives !!!
 */
//BOOST_ARCHIVE_STRONG_TYPEDEF(uint_least8_t, version_type)
//BOOST_ARCHIVE_STRONG_TYPEDEF(int_least16_t, class_id_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(int_least16_t, class_id_optional_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(int_least16_t, class_id_reference_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(uint_least32_t, object_id_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(uint_least32_t, object_reference_type)

namespace boost {
namespace archive {

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

struct version_type
    : boost::totally_ordered1< version_type
    , boost::totally_ordered2< version_type, uint_least8_t                             
    > >                                                         
{                                                               
    typedef uint_least8_t base_type;
    base_type t;
    version_type(){};
    explicit version_type(const version_type & t_) : t(t_.t){}
    version_type(const unsigned int & t_) : t(t_){
        assert(t_ <= boost::integer_traits<base_type>::const_max);
    }
    version_type & operator=(const version_type & rhs){
        t = rhs.t; 
        return *this;
    }
    operator const base_type () const {
        return t;
    }                
    operator base_type & (){
        return t;
    }
    bool operator==(const version_type & rhs) const {
        return t == rhs.t;
    } 
    bool operator<(const version_type & rhs) const {
        return t < rhs.t;
    }   
};

struct class_id_type
    : boost::totally_ordered1< class_id_type
    , boost::totally_ordered2< class_id_type, int_least16_t                             
    > >                                                         
{
    typedef int_least16_t base_type;
    base_type t;
    class_id_type(){};
    class_id_type(const class_id_type & t_) : t(t_.t){}
    explicit class_id_type(const std::size_t & t_) : t(t_){
        //assert(t_ <= boost::integer_traits<base_type>::const_max);
    }
    explicit class_id_type(const int & t_) : t(t_){}
    class_id_type & operator=(const class_id_type & rhs){
        t = rhs.t; 
        return *this;
    }

    // used for standard i/o
    operator const base_type () const {
        return t;
    }                
    operator base_type & (){
        return t;
    }
    bool operator==(const class_id_type & rhs) const {
        return t == rhs.t;
    } 
    bool operator<(const class_id_type & rhs) const {
        return t < rhs.t;
    }   
};

#define NULL_POINTER_TAG boost::archive::class_id_type(-1)

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

struct tracking_type {
    bool t;
    explicit tracking_type(const bool t_ = false)
        : t(t_)
    {};
    tracking_type(const tracking_type & t_)
        : t(t_.t)
    {}
    operator bool () const {
        return t;
    };
    operator bool & () {
        return t;
    };
    tracking_type & operator=(const bool t_){
        t = t_;
        return *this;
    }
    bool operator==(const tracking_type & rhs) const {
        return t == rhs.t;
    }
    bool operator==(const bool & rhs) const {
        return t == rhs;
    }
    tracking_type & operator=(const tracking_type & rhs){
        t = rhs.t;
        return *this;
    }
};

struct class_name_type : 
    private boost::noncopyable 
{
    char *t;
    operator const char * & () const {
        return const_cast<const char * &>(t);
    }
    operator char * () {
        return t;
    }
    explicit class_name_type(const char *key_) 
    : t(const_cast<char *>(key_)){}
    explicit class_name_type(char *key_) 
    : t(key_){}
    class_name_type & operator=(const class_name_type & rhs){
        t = rhs.t;
        return *this;
    }
};

enum archive_flags {
    no_header = 1,  // suppress archive header info
    no_codecvt = 2,  // suppress alteration of codecvt facet
    no_xml_tag_checking = 4,   // suppress checking of xml tags
    no_tracking = 8,           // suppress ALL tracking
    flags_last = 8
};

BOOST_ARCHIVE_DECL(const char *)
BOOST_ARCHIVE_SIGNATURE();

BOOST_ARCHIVE_DECL(library_version_type)
BOOST_ARCHIVE_VERSION();

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

namespace boost {
template<>
class integer_traits<boost::archive::class_id_type> : 
    public integer_traits<boost::archive::class_id_type::base_type>
{};
} // namespace boost

#include <boost/serialization/level.hpp>

// set implementation level to primitive for all types
// used internally by the serialization library

BOOST_CLASS_IMPLEMENTATION(boost::archive::library_version_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::version_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_reference_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_optional_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_name_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::object_id_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::object_reference_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::tracking_type, primitive_type)

#endif //BOOST_ARCHIVE_BASIC_ARCHIVE_HPP
