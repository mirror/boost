#ifndef BOOST_SERIALIZATION_SERIALIZATION_HPP
#define BOOST_SERIALIZATION_SERIALIZATION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#  pragma warning (disable : 4675) // suppress ADL warning
#endif

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/pfto.hpp>
#include <boost/throw_exception.hpp>
#include <boost/serialization/nvp.hpp>

// incremented for each "release"
#define BOOST_SERIALIZATION_LIBRARY_VERSION 19

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

//////////////////////////////////////////////////////////////////////
// public interface to serialization. 

/////////////////////////////////////////////////////////////////////////////
// layer 0 - intrusive verison
// declared and implemented for each user defined class to be serialized
//
//  template<Archive>
//  serialize(Archive &ar, const unsigned int file_version){
//      ar & base_object<base>(*this) & member1 & member2 ... ;
//  }

/////////////////////////////////////////////////////////////////////////////
// layer 1 - layer that routes member access through the access class.
// this is what permits us to grant access to private class member functions
// by specifying friend class boost::serialization::access

#include <boost/serialization/access.hpp>

/////////////////////////////////////////////////////////////////////////////
// layer 2 - default implementation of non-intrusive serialization.
//
// note the usage of function overloading to compensate that C++ does not
// currently support Partial Template Specialization for function templates 
// We have declared the version number as "const unsigned long".  
// Overriding templates for specific data types should declare the version
// number as "const unsigned int". Template matching will first be applied
// to functions with the same version types - that is the overloads.  
// If there is no declared function prototype that matches, the second argument
// will be converted to "const unsigned long" and a match will be made with 
// one of the default template functions below.

namespace boost {
namespace serialization {

// default implemenation - call the member function "serialize"
template<class Archive, class T>
inline void serialize(
    Archive & ar, T & t, const BOOST_PFTO unsigned int file_version
){
    access::serialize(ar, t, static_cast<unsigned int>(file_version));
}

// save data required for construction
template<class Archive, class T>
inline void save_construct_data(
    Archive & /*ar*/, const T * /*t*/, const BOOST_PFTO unsigned int /*file_version */
){
    // default is to save no data because default constructor
    // requires no arguments.
}

// load data required for construction and invoke constructor in place
template<class Archive, class T>
inline void load_construct_data(
    Archive & ar, T * t, const BOOST_PFTO unsigned int /*file_version*/
){
    // default just uses the default constructor.  going
    // through access permits usage of otherwise private default
    // constructor
    access::construct(ar, t);
}

// note trick to be sure that operator new is using class specific
// version if such exists. Due to Peter Dimov.
// note: the following fails if T has no default constructor.
// otherwise it would have been ideal
//struct heap_allocator : public T 
//{
//    T * invoke(){
//        return ::new(sizeof(T));
//    }
//}

// note: this should really be a member of the load_ptr function
// below but some compilers still complain about this.
template<class T>
struct heap_allocator
{
    #if 0
        // note: this fails on msvc 7.0 and gcc 3.2
        template <class U, U x> struct test;
        typedef char* yes;
        typedef int* no;
        template <class U>
        yes has_op_new(U*, test<void* (*)(std::size_t), &U::operator new>* = 0);
        no has_op_new(...);

        template<class U>
        T * new_operator(U);

        T * new_operator(yes){
            return (T::operator new)(sizeof(T));
        }
        T * new_operator(no){
            return static_cast<T *>(operator new(sizeof(T)));
        }
        static T * invoke(){
            return new_operator(has_op_new(static_cast<T *>(NULL)));
        }
    #else
        // while this doesn't handle operator new overload for class T
        static T * invoke(){
            return static_cast<T *>(operator new(sizeof(T)));
        }
    #endif
};

// due to Martin Ecker
template <typename T>
class auto_ptr_with_deleter
{
public:
    explicit auto_ptr_with_deleter(T* p) :
        m_p(p)
    {}
    ~auto_ptr_with_deleter(){
        if (m_p)
            access::destroy(m_p);
    }
    T* get() const {
        return m_p;
    }

    T* release() {
        T* p = m_p;
        m_p = NULL;
        return p;
    }
private:
    T* m_p;
};

// undocmented overridable escape hatches with default implementation
// may be necessary to permit usage of class factories or other
// unforseen circumstances.
template<class Archive, class T>
void load_ptr(Archive & ar, T * & t, const BOOST_PFTO unsigned int file_version)
{
    auto_ptr_with_deleter<T> ap(heap_allocator<T>::invoke());
    if(NULL == ap.get())
        boost::throw_exception(std::bad_alloc()) ;
    t = ap.get();
    load_construct_data(
        ar, 
        t, 
        static_cast<unsigned int>(file_version)
    );
    ar >> make_nvp(NULL, * t);
    ap.release();
}

template<class Archive, class T>
void save_ptr(
    Archive & ar, 
    const T * t,
    const BOOST_PFTO unsigned int file_version
){
    save_construct_data(
        ar, 
        t, 
        static_cast<unsigned int >(file_version)
    );
    // when outputing data through a pointer, the name of the 
    // pointer has already been specified so we don't need a
    // name- value pair here.  We use a nvp with a null name
    // in order to sneak past the archive code that requires
    // names on all variable not primitives
    static_cast<Archive &>(ar) << make_nvp(NULL, *t);
}

/////////////////////////////////////////////////////////////////////////////
// layer 3 - default implementation of non-intrusive serialization.
//
// trick to call serialize from within boost::serialization namspace
// thus permitting serialize override to be in either of 3 namespace
// 1) boost::serialization
// 2) same namepace as Archive
// 3) same namespace as T
// Due to Martin Ecker

template<class Archive, class T>
inline void serialize_adl(
    Archive & ar, T & t, const unsigned int file_version
){
    serialize(ar, t, file_version);
}

template<class Archive, class T>
inline void load_ptr_adl(Archive & ar, T * & t, const unsigned int file_version){
    load_ptr(ar, t, file_version);
}

template<class Archive, class T>
inline void save_ptr_adl(Archive & ar, const T * t, const unsigned int file_version){
    save_ptr(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_SERIALIZATION_HPP
