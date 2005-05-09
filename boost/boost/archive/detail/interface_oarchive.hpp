#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <string>
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>
//#include <boost/static_warning.hpp>

//#include <boost/serialization/level.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {
namespace detail {

class BOOST_DECL_ARCHIVE basic_oserializer;
class BOOST_DECL_ARCHIVE basic_pointer_oserializer;

template<class Archive>
class interface_oarchive 
{
protected:
    interface_oarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface

    struct is_loading {
        typedef mpl::bool_<false> type;
        BOOST_STATIC_CONSTANT(bool, value=false);
    };
    struct is_saving {
        typedef mpl::bool_<true> type;
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_oserializer * register_type(const T * t = NULL){
        const basic_pointer_oserializer & bpos =
            instantiate_pointer_oserializer(
                static_cast<Archive *>(NULL),
                static_cast<T *>(NULL)
            );
        this->This()->register_basic_serializer(bpos.get_basic_serializer());
        return & bpos;
    }

    template<class T>
    T & get_helper(T & h){
        typedef BOOST_DEDUCED_TYPENAME boost::serialization::type_info_implementation<T>::type eti_type;
        boost::serialization::extended_type_info * eti = eti_type::get_instance();
        boost::serialization::basic_helper *hptr = 
            this->This()->basic_iarchive::lookup_helper(eti);
        if(NULL == hptr){
            hptr = new T;
            this->This()->basic_iarchive::insert_helper(hptr, eti);
        }
        return static_cast<T &>(* hptr);
    }

    // default processing - invoke serialization library
    template<class T>
    void save_override(T & t, /*BOOST_PFTO*/ int){
        archive::save(* this->This(), t);
    }

    template<class T>
    Archive & operator<<(T & t){
        this->This()->save_override(t, 0);
        return * this->This();
    }

    // the & operator 
    template<class T>
    Archive & operator&(T & t){
		#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
			return * this->This() << const_cast<const T &>(t);
		#else
			return * this->This() << t;
		#endif
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP
