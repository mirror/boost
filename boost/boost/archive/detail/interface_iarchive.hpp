#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <string>
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
template<class T>
class shared_ptr;
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail {

class BOOST_DECL_ARCHIVE basic_pointer_iserializer;

template<class Archive>
class interface_iarchive 
{
protected:
    interface_iarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    struct is_loading {
        typedef mpl::bool_<true> type;
        BOOST_STATIC_CONSTANT(bool, value=true);
    };
    struct is_saving {
        typedef mpl::bool_<false> type;
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_iserializer * register_type(T * t = NULL){
        #if BOOST_SERIALIZATION_STATIC_DATA_REGISTRATION_WORKAROUND
        boost::serialization::access::static_data_registration_workaround<T>();
        #endif
        const basic_pointer_iserializer & bpis =
            archive::detail::instantiate_pointer_iserializer(
                static_cast<Archive *>(NULL),
                static_cast<T *>(NULL)
            );
        this->This()->register_basic_serializer(bpis.get_basic_serializer());
        return & bpis;
    }

    void lookup_helper(
        const boost::serialization::extended_type_info * const eti,
        shared_ptr<void> & sph
    ){
        this->This()->basic_iarchive::lookup_basic_helper(eti, sph);
    }

    void insert_helper(
        const boost::serialization::extended_type_info * const eti,
        shared_ptr<void> & sph
    ){
        this->This()->basic_iarchive::insert_basic_helper(eti, sph);
    }

    // default processing - invoke serialization library
    template<class T>
    void load_override(T & t, /*BOOST_PFTO*/ int){
        archive::load(* this->This(), t);
    }

    template<class T>
    Archive & operator>>(T & t){
        this->This()->load_override(t, 0);
        return * this->This();
    }

    // the & operator 
    template<class T>
    Archive & operator&(T & t){
        return *(this->This()) >> t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP
