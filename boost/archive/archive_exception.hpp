#ifndef BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive/archive_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <exception>
#include <cassert>
#include <string>

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by archives
//
class archive_exception : 
    public virtual std::exception
{
public:
    typedef enum {
        no_exception,       // initialized without code
        other_exception,    // any excepton not listed below
        unregistered_class, // attempt to serialize a pointer of an
                            // an unregistered class
        invalid_signature,  // first line of archive does not contain
                            // expected string
        unsupported_version,// archive created with library version
                            // subsequent to this one
        pointer_conflict,   // an attempt has been made to directly
                            // serialize an object which has
                            // already been serialzed through a pointer.  
                            // Were this permited, the archive load would result 
                            // in the creation of an extra copy of the obect.
        incompatible_native_format, // attempt to read native binary format
                            // on incompatible platform
        array_size_too_short,// array being loaded doesn't fit in array allocated
        stream_error,       // i/o error on stream
        invalid_class_name, // class name greater than the maximum permitted.
                            // most likely a corrupted archive or an attempt
                            // to insert virus via buffer overrun method.
        unregistered_cast,   // base - derived relationship not registered with 
                            // void_cast_register
        unsupported_class_version, // type saved with a version # greater than the 
                            // one used by the program.  This indicates that the proggram
                            // needs to be rebuilt.
        inconsistent_pointer_serialization, // an object as been serialized
                            // more than once through pointers of different types.
        multiple_code_instantiation // code for implementing serialization for some
                            // type has been instantiated in more than one module.
    } exception_code;
private:
    std::string m_msg;
public:
    exception_code code;
    archive_exception(
        exception_code c, 
        const char * e1 = NULL,
        const char * e2 = NULL
    ) : 
        code(c)
    {
        m_msg = "programming error";
        switch(code){
        case no_exception:
            m_msg = "uninitialized exception";
            break;
        case unregistered_class:
            m_msg = "unregistered class";
            if(NULL != e1){
                m_msg += " - ";
                m_msg += e1;
            }    
            break;
        case invalid_signature:
            m_msg = "invalid signature";
            break;
        case unsupported_version:
            m_msg = "unsupported version";
            break;
        case pointer_conflict:
            m_msg = "pointer conflict";
            break;
        case incompatible_native_format:
            m_msg = "incompatible native format";
            if(NULL != e1){
                m_msg += " - ";
                m_msg += e1;
            }    
            break;
        case array_size_too_short:
            m_msg = "array size too short";
            break;
        case stream_error:
            m_msg = "stream error";
            break;
        case invalid_class_name:
            m_msg = "class name too long";
            break;
        case unregistered_cast:
            m_msg = "unregistered void cast ";
            m_msg += (NULL != e1) ? e1 : "?";
            m_msg += "<-";
            m_msg += (NULL != e2) ? e2 : "?";
           break;
        case unsupported_class_version:
            m_msg = "class version";
            break;
        case other_exception:
            // if get here - it indicates a derived exception 
            // was sliced by passing by value in catch
            m_msg = "unknown derived exception";
            break;
        case inconsistent_pointer_serialization:
            // same object saved through different kinds of pointers
            m_msg = "inconsistent_pointer_serialization";
            break;
        case multiple_code_instantiation:
            m_msg = "code instantiated in more than one module";
            if(NULL != e1){
                m_msg += " - ";
                m_msg += e1;
            }    
            break;
        default:
            assert(false);
            break;
        }
    }
    ~archive_exception() throw () {}
    virtual const char *what( ) const throw()
    {
        return m_msg.c_str();
    }
protected:
    archive_exception() : 
         code(no_exception)
    {}
};

}// namespace archive
}// namespace boost

#endif //BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP
