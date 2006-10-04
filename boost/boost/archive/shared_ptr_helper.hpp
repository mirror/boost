#ifndef BOOST_ARCHIVE_SHARED_PTR_HELPER_HPP
#define BOOST_ARCHIVE_SHARED_PTR_HELPER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shared_ptr.hpp: serialization for boost shared pointer

// (C) Copyright 2004 Robert Ramey and Martin Ecker
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <map>

#include <boost/config.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/detail/workaround.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/throw_exception.hpp>

#include <boost/archive/archive_exception.hpp>

namespace boost {
namespace serialization {
    class extended_type_info;
}
namespace archive{
namespace detail {

struct null_deleter {
    void operator()(void const *) const {}
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// a common class for holding various types of shared pointers

class shared_ptr_helper {
    typedef std::map<void*, shared_ptr<void> > collection_type;
    typedef collection_type::const_iterator iterator_type;
    // list of shared_pointers create accessable by raw pointer. This
    // is used to "match up" shared pointers loaded at diferent
    // points in the archive. Note, we delay construction until
    // it is actually used since this is by default included as
    // a "mix-in" even if shared_ptr isn't used.
    collection_type * m_pointers;
    // return a void pointer to the most derived type
    template<class T>
    void * object_identifier(T * t) const {
        const boost::serialization::extended_type_info * true_type 
            = boost::serialization::type_info_implementation<T>::type
                ::get_derived_extended_type_info(*t);
        // note:if this exception is thrown, be sure that derived pointer
        // is either registered or exported.
        if(NULL == true_type)
            boost::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::unregistered_class
                )
            );
        const boost::serialization::extended_type_info * this_type
            = boost::serialization::type_info_implementation<T>::type::get_instance();
        void * vp = void_downcast(*true_type, *this_type, t);
        return vp;
    }
public:
    template<class T>
    void reset(shared_ptr<T> & s, T * r){
        if(NULL == r){
            s.reset();
            return;
        }
        // get pointer to the most derived object.  This is effectively
        // the object identifer
        void * od = object_identifier(r);

        if(NULL == m_pointers)
            m_pointers = new collection_type;

        iterator_type it = m_pointers->find(od);

        if(it == m_pointers->end()){
            s.reset(r);
            m_pointers->insert(collection_type::value_type(od,s));
        }
        else{
            s = static_pointer_cast<T>((*it).second);
        }
    }
    shared_ptr_helper() : 
        m_pointers(NULL)
    {}
    ~shared_ptr_helper(){
        if(NULL != m_pointers)
            delete m_pointers;
    }
};

} // namespace detail
} // namespace serialization
} // namespace boost

#endif // BOOST_ARCHIVE_SHARED_PTR_HELPER_HPP
