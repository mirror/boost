/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oarchive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression

#include <cassert>
#include <set>

#include <boost/limits.hpp>
#include <boost/state_saver.hpp>
#include <boost/throw_exception.hpp>

// including this here to work around an ICC in intel 7.0
// normally this would be part of basic_oarchive.hpp below.
#include <boost/archive/basic_archive.hpp>

#include <boost/archive/detail/basic_oserializer.hpp>
#include <boost/archive/detail/basic_pointer_oserializer.hpp>
#include <boost/archive/detail/basic_oarchive.hpp>

#include <boost/serialization/extended_type_info.hpp>
#include <boost/archive/archive_exception.hpp>

using namespace boost::serialization;

namespace boost {
namespace archive {
namespace detail {

class basic_oserializer;
class basic_pointer_oserializer;

class basic_oarchive_impl
{
    friend class basic_oarchive;
    //////////////////////////////////////////////////////////////////////
    // information about each serialized object saved
    // keyed on address, class_id
    struct aobject
    {
        const void * address;
        class_id_type class_id;
        object_id_type object_id;

        bool operator<(const aobject &rhs) const
        {
            assert(NULL != address);
            assert(NULL != rhs.address);
            if( address < rhs.address )
                return true;
            if( address > rhs.address )
                return false;
            return class_id < rhs.class_id;
        }
        aobject & operator=(const aobject & rhs)
        {
            address = rhs.address;
            class_id = rhs.class_id;
            object_id = rhs.object_id;
            return *this;
        }
        aobject(
            const void *a,
            class_id_type class_id_,
            object_id_type object_id_
        ) :
            address(a),
            class_id(class_id_),
            object_id(object_id_)
        {}
        aobject() : address(NULL){}
    };
    // keyed on class_id, address
    typedef std::set<aobject> object_set_type;
    object_set_type object_set;

    //////////////////////////////////////////////////////////////////////
    // information about each serialized class saved
    // keyed on type_info
    struct cobject_type
    {
        const basic_oserializer * bos_ptr;
        const class_id_type class_id;
        bool initialized;
        cobject_type(
            std::size_t class_id_,
            const basic_oserializer & bos_
        ) :
            bos_ptr(& bos_),
            class_id(class_id_),
            initialized(false)
        {}
        cobject_type(const basic_oserializer & bos_)
            : bos_ptr(& bos_)
        {}
        cobject_type(
            const cobject_type & rhs
        ) :
            bos_ptr(rhs.bos_ptr),
            class_id(rhs.class_id),
            initialized(rhs.initialized)
        {}
        // the following cannot be defined because of the const
        // member.  This will generate a link error if an attempt
        // is made to assign.  This should never be necessary
        // use this only for lookup argument 
        cobject_type & operator=(const cobject_type &rhs);
        bool operator<(const cobject_type &rhs) const {
            return *bos_ptr < *(rhs.bos_ptr);
        }
    };
    // keyed on type_info
    typedef std::set<cobject_type> cobject_info_set_type;
    cobject_info_set_type cobject_info_set;

    // list of objects initially stored as pointers - used to detect errors
    // keyed on object id
    std::set<object_id_type> stored_pointers;

    bool is_object; // pass forward indicater that we're saving an object
                    // directly rather than result of a pointer
    basic_oarchive_impl()
        : is_object(true)
    {}

    const cobject_type &
    find(const basic_oserializer & bos);
    const basic_oserializer *  
    find(const serialization::extended_type_info &ti) const;
    void
    save_preamble(
        basic_oarchive & ar,
        const unsigned int file_version,
        bool tracking
    );
    bool
    track(
        basic_oarchive & ar,
        const void *t,
        const basic_oserializer & bos,
        const class_id_type cid,
        bool is_object
    );
public:
    const cobject_type &
    register_type(const basic_oserializer & bos);
    void save_object(
        basic_oarchive & ar,
        const void *t,
        const basic_oserializer & bos
    );
    void save_pointer(
        basic_oarchive & ar,
        const void * t, 
        const basic_pointer_oserializer * bpos
    );

};

//////////////////////////////////////////////////////////////////////
// implementation of basic_oarchive implementation functions

// given a type_info - find its bos
// return NULL if not found
inline const basic_oserializer *
basic_oarchive_impl::find(const serialization::extended_type_info & ti) const {
    class bosarg : public basic_oserializer
    {
       bool class_info() const {
            assert(false); 
            return false;
        }
        // returns true if objects should be tracked
        bool tracking() const {
            assert(false);
            return false;
        }
        // returns class version
        unsigned int version() const {
            assert(false);
            return 0;
        }
        // returns true if this class is polymorphic
        bool is_polymorphic() const{
            assert(false);
            return false;
        }
        void save_object_data(      
            basic_oarchive & ar, const void * x
        ) const {
            assert(false);
        }
    public:
        bosarg(const serialization::extended_type_info & type_) :
          boost::archive::detail::basic_oserializer(type_)
        {}
    };
    bosarg bos(ti);
    cobject_info_set_type::const_iterator cit 
        = cobject_info_set.find(cobject_type(bos));
    // it should already have been "registered" - see below
    if(cit == cobject_info_set.end()){
        // if an entry is not found in the table it is because a pointer
        // of a derived class has been serialized through its base class
        // but the derived class hasn't been "registered" 
        return NULL;
    }
    // return pointer to the real class
    return cit->bos_ptr;
}

inline const basic_oarchive_impl::cobject_type &
basic_oarchive_impl::find(const basic_oserializer & bos)
{
    std::pair<cobject_info_set_type::iterator, bool> cresult = 
        cobject_info_set.insert(cobject_type(cobject_info_set.size(), bos));
    return *(cresult.first);
}

inline const basic_oarchive_impl::cobject_type &
basic_oarchive_impl::register_type(
    const basic_oserializer & bos
){
    cobject_type co(cobject_info_set.size(), bos);
    std::pair<cobject_info_set_type::const_iterator, bool>
        result = cobject_info_set.insert(co);
    return *(result.first);
}

void
basic_oarchive_impl::save_preamble(
    basic_oarchive & ar,
    const unsigned int file_version,
    bool tracking
){
    ar.vsave(tracking_type(tracking));
    ar.vsave(version_type(file_version));
}

// return true if this is a new object and should be serialized
// false if it can be skipped.
bool
basic_oarchive_impl::track(
    basic_oarchive & ar,
    const void *t,
    const basic_oserializer & bos,
    const class_id_type cid,
    bool is_object
){
    object_id_type oid(object_set.size());
    // lookup to see if this object has already been written to the archive
    basic_oarchive_impl::aobject ao(t, cid, oid);
    std::pair<basic_oarchive_impl::object_set_type::const_iterator, bool>
        aresult = object_set.insert(ao);
    oid = aresult.first->object_id;
    // if its aready there
    if(! aresult.second){
        ar.vsave(object_reference_type(oid));
        // and its an object
        if(is_object
        // but it was originally stored through a pointer
        && stored_pointers.end() != stored_pointers.find(oid)){
            // this has to be a user error.  loading such an archive
            // would create duplicate objects
            boost::throw_exception(
                archive_exception(archive_exception::pointer_conflict)
            );
        }
        return false;
    }
    ar.vsave(oid);
    if(! is_object)
        // add to the set of object initially stored through pointers
        stored_pointers.insert(oid);
    return true;
}

inline void
basic_oarchive_impl::save_object(
    basic_oarchive & ar,
    const void *t,
    const basic_oserializer & bos
){
    bool new_object = true;
    if(is_object){
        const cobject_type & co = register_type(bos);
        if(bos.class_info()){
            if( ! co.initialized){
                ar.vsave(class_id_optional_type(co.class_id));
                save_preamble(ar, bos.version(), bos.tracking());
                (const_cast<cobject_type &>(co)).initialized = true;
            }
        }
        if(bos.tracking())
            new_object = track(ar, t, bos, co.class_id, true);
        ar.end_preamble();
    }
    if(new_object){
        state_saver<bool> x(is_object);
        is_object = true;
        (bos.save_object_data)(ar, t);
    }
}

// save a pointer to an object instance
inline void
basic_oarchive_impl::save_pointer(
    basic_oarchive & ar,
    const void * t, 
    const basic_pointer_oserializer * bpos_ptr
){
    const basic_oserializer & bos = bpos_ptr->get_basic_serializer();
    unsigned int original_count = cobject_info_set.size();
    const cobject_type & co = register_type(bos);
    if(! co.initialized){
        ar.vsave(co.class_id);
        // if its a previously unregistered class 
        if((cobject_info_set.size() > original_count)){
            if(bos.is_polymorphic()){
                const serialization::extended_type_info *eti = & bos.type;
                const char * key = NULL;
                if(NULL != eti)
                    key = eti->key;
                if(NULL != key){
                    // the following is required by IBM C++ compiler which
                    // makes a copy when passing a non-const to a const.  This
                    // is permitted by the standard but rarely seen in practice
                    const class_name_type cn(key);
                    // write out the external class identifier
                    ar.vsave(cn);
                }
                else
                    // without an external class name
                    // we won't be able to de-serialize it so bail now
                    boost::throw_exception(
                        archive_exception(archive_exception::unregistered_class)
                    );
            }
        }
        if(bos.class_info())
            save_preamble(ar, bos.version(), bos.tracking());
        (const_cast<cobject_type &>(co)).initialized = true;
    }
    else{
        ar.vsave(class_id_reference_type(co.class_id));
    }

    bool result = true;
    if(bos.tracking())
        result = track(ar, t, bos, co.class_id, false);

    ar.end_preamble();

    if(result){
        state_saver<bool> x(is_object);
        is_object = false;
        bpos_ptr->save_object_ptr(ar, t);
    }
}

//////////////////////////////////////////////////////////////////////
// implementation of basic_oarchive functions

basic_oarchive::basic_oarchive()
    : pimpl(new basic_oarchive_impl)
{}

basic_oarchive::~basic_oarchive()
{
    delete pimpl;
}

void basic_oarchive::save_object(
    const void *x, 
    const basic_oserializer & bos
){
    pimpl->save_object(*this, x, bos);
}

void basic_oarchive::save_pointer(
    const void * t, 
    const basic_pointer_oserializer * bpos_ptr
){
    pimpl->save_pointer(*this, t, bpos_ptr);
}

void basic_oarchive::register_basic_serializer(const basic_oserializer & bos){
    pimpl->register_type(bos);
}

} // namespace detail
} // namespace archive
} // namespace boost
