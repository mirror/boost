/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_archive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp> // msvc 6.0 needs this to suppress warnings

#include <cassert>
#include <set>
#include <list>
#include <vector>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#define BOOST_ARCHIVE
#include <boost/archive/detail/auto_link_archive.hpp>

#include <boost/limits.hpp>
#include <boost/state_saver.hpp>
#include <boost/throw_exception.hpp>

#include <boost/archive/detail/basic_iserializer.hpp>
#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <boost/serialization/tracking.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/basic_helper.hpp>

using namespace boost::serialization;

namespace boost {
namespace serialization {
    class extended_type_info;
}
namespace archive {
namespace detail {

class basic_iserializer;
class basic_pointer_iserializer;

class basic_iarchive_impl 
{
    friend class basic_iarchive;

    version_type m_archive_library_version;
    unsigned int m_flags;

    //////////////////////////////////////////////////////////////////////
    // information about each serialized object loaded
    // indexed on object_id
    struct aobject
    {
        void * address;
        class_id_type class_id;
        aobject(
            void *a,
            class_id_type class_id_
        ) :
            address(a),
            class_id(class_id_)
        {}
        aobject() : address(NULL), class_id(-2) {}
    };
    typedef std::vector<aobject> object_id_vector_type;
    object_id_vector_type object_id_vector;

    //////////////////////////////////////////////////////////////////////
    // used to implement the reset_object_address operation.
    // list of objects which might be moved. We use a vector for implemenation
    // in the hope the the truncation operation will be faster than either
    // with a list or stack adaptor
    std::vector<std::size_t> moveable_object_stack;
    std::size_t moveable_object_position;

    void reset_object_address(
        const void * new_address, 
        const void *old_address
    );

    //////////////////////////////////////////////////////////////////////
    // used by load object to look up class id given basic_serializer
    struct cobject_type
    {
        const basic_iserializer * bis;
        const class_id_type class_id;
        cobject_type(
            std::size_t class_id_,
            const basic_iserializer & bis_
        ) : 
            bis(& bis_),
            class_id(class_id_)
        {}
        cobject_type(const cobject_type & rhs) : 
            bis(rhs.bis),
            class_id(rhs.class_id)
        {}
        // the following cannot be defined because of the const
        // member.  This will generate a link error if an attempt
        // is made to assign.  This should never be necessary
        cobject_type & operator=(const cobject_type & rhs);
        bool operator<(const cobject_type &rhs) const
        {
            return *bis < *(rhs.bis);
        }
    };
    typedef std::set<cobject_type> cobject_info_set_type;
    cobject_info_set_type cobject_info_set;

    //////////////////////////////////////////////////////////////////////
    // information about each serialized class indexed on class_id
    class cobject_id 
    {
    public:
        cobject_id & operator=(const cobject_id & rhs){
            bis_ptr = rhs.bis_ptr;
            bpis_ptr = rhs.bpis_ptr;
            file_version = rhs.file_version;
            tracking_level = rhs.tracking_level;
            initialized = rhs.initialized;
            return *this;
        }
        const basic_iserializer * bis_ptr;
        const basic_pointer_iserializer * bpis_ptr;
        version_type file_version;
        tracking_type tracking_level;
        bool initialized;

        cobject_id(const basic_iserializer & bis_) :
            bis_ptr(& bis_),
            bpis_ptr(NULL),
            file_version(0),
            tracking_level(track_never),
            initialized(false)
        {}
        cobject_id(const cobject_id &rhs): 
            bis_ptr(rhs.bis_ptr),
            bpis_ptr(rhs.bpis_ptr),
            file_version(rhs.file_version),
            tracking_level(rhs.tracking_level),
            initialized(rhs.initialized)
        {}
    };
    typedef std::vector<cobject_id> cobject_id_vector_type;
    cobject_id_vector_type cobject_id_vector;

    //////////////////////////////////////////////////////////////////////
    // list of objects created by de-serialization.  Used to implement
    // clean up after exceptions.
    class created_pointer_type
    {
    public:
        created_pointer_type(
            class_id_type class_id_,
            void * address_
        ) :
            class_id(class_id_),
            address(address_)
        {}
        created_pointer_type(const created_pointer_type &rhs) :
            class_id(rhs.class_id),
            address(rhs.address)
        {}
        created_pointer_type & operator=(const created_pointer_type &){
            assert(false);
            return *this;
        }
        void * get_address() const {
            return address;
        }
        // object to which this item refers
        const class_id_type class_id;
    private:
        void * address;
    };

    std::list<created_pointer_type> created_pointers;

    //////////////////////////////////////////////////////////////////////
    // address of the most recent object serialized as a poiner
    // whose data itself is now pending serialization
    void * pending_object;
    const basic_iserializer * pending_bis;
    version_type pending_version;

    //////////////////////////////////////////////////////////////////////
    // list of serialization helpers
    struct helper_compare;

    struct helper_type {
        // at least one compiler sunpro 5.3 erroneously doesn't give access to embedded structs
        friend struct helper_compare;
        boost::serialization::basic_helper * m_helper;
        const boost::serialization::extended_type_info * m_eti;
        helper_type(
            boost::serialization::basic_helper * h, 
            const boost::serialization::extended_type_info * const eti
        ) :
            m_helper(h),
            m_eti(eti)
        {}
    };

    struct helper_compare {
        bool operator()(const helper_type & lhs, const helper_type & rhs) const {
            return * lhs.m_eti < * rhs.m_eti;
        }
    };

    typedef std::set<helper_type, helper_compare>::iterator helper_iterator;
    typedef std::set<helper_type, helper_compare>::const_iterator 
        helper_const_iterator;

    std::set<helper_type, helper_compare> m_helpers;

    basic_iarchive_impl(unsigned int flags) :
        m_archive_library_version(ARCHIVE_VERSION()),
        m_flags(flags),
        moveable_object_position(0),
        pending_object(NULL),
        pending_bis(NULL),
        pending_version(0)
    {}
    ~basic_iarchive_impl(){
        // delete helpers
        for(
            helper_iterator it = m_helpers.begin();
            it !=  m_helpers.end();
            ++it
        ){
            delete it->m_helper;
        }
    }
    void set_library_version(unsigned int archive_library_version){
        m_archive_library_version = archive_library_version;
    }
    bool
    track(
        basic_iarchive & ar,
        void * & t
    );
    void
    load_preamble(
        basic_iarchive & ar,
        cobject_id & co
    );
    class_id_type register_type(
        const basic_iserializer & bis
    );

    // redirect through virtual functions to load functions for this archive
    template<class T>
    void load(basic_iarchive & ar, T & t){
        ar.vload(t);
    }

//public:
    void
    next_object_pointer(void * t){
        pending_object = t;
    }
    void delete_created_pointers();
    class_id_type register_type(
        const basic_pointer_iserializer & bpis
    );
    void load_object(
        basic_iarchive & ar,
        void * t,
        const basic_iserializer & bis
    );
    const basic_pointer_iserializer * load_pointer(
        basic_iarchive & ar,
        void * & t, 
        const basic_pointer_iserializer * bpis,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    );
    boost::serialization::basic_helper * lookup_helper(
        const boost::serialization::extended_type_info * const eti
    ){
        helper_iterator it;
        const helper_type ht(NULL, eti);
        it = m_helpers.find(ht);
        return (it == m_helpers.end()) ? NULL : it->m_helper;
    }
    boost::serialization::basic_helper* insert_helper(
        boost::serialization::basic_helper * h, 
        const boost::serialization::extended_type_info * const eti
    ){
        std::pair<helper_iterator, bool> result = m_helpers.insert(
            helper_type(h, eti)
        );
        return (*result.first).m_helper;
    }
};

inline void 
basic_iarchive_impl::reset_object_address(
    const void * new_address, 
    const void *old_address
){
    // if the this object wasn't tracked
    std::size_t i = moveable_object_position;
    if(i >= moveable_object_stack.size())
        return;
    if(old_address != object_id_vector[i].address)
        // skip to any lower level ones
        ++i;
    while(i < moveable_object_stack.size()){
        // calculate displacement from this level
        assert(object_id_vector[i].address >= old_address);
        // warning - pointer arithmetic on void * is in herently non-portable
        // but expected to work on all platforms in current usage
        std::size_t member_displacement
            = reinterpret_cast<std::size_t>(object_id_vector[i].address) 
            - reinterpret_cast<std::size_t>(old_address);
        object_id_vector[i].address = reinterpret_cast<void *>(
            reinterpret_cast<std::size_t>(new_address) + member_displacement
        );
        ++i;
    }
}

inline void 
basic_iarchive_impl::delete_created_pointers()
{
    while(created_pointers.size() > 0){
        const created_pointer_type & cp = created_pointers.front();

        // figure out the class of the object to be deleted
        // note: extra line used to evade borland issue
        const int id = cp.class_id;
        const cobject_id & co = cobject_id_vector[id];
        // with the appropriate input serializer, 
        // delete the indicated object
        co.bis_ptr->destroy(cp.get_address());
        created_pointers.pop_front();
    }
}

inline class_id_type
basic_iarchive_impl::register_type(
    const basic_iserializer & bis
){
    cobject_type co(cobject_info_set.size(), bis);
    std::pair<cobject_info_set_type::const_iterator, bool>
        result = cobject_info_set.insert(co);

    if(result.second){
        cobject_id_vector.push_back(cobject_id(bis));
        assert(cobject_info_set.size() == cobject_id_vector.size());
    }
    const int id = result.first->class_id;
    cobject_id & coid = cobject_id_vector[id];
    coid.bpis_ptr = bis.get_bpis_ptr();
    return result.first->class_id;
}

void
basic_iarchive_impl::load_preamble(
    basic_iarchive & ar,
    cobject_id & co
){
    if(! co.initialized){
        if(co.bis_ptr->class_info()){
            class_id_optional_type cid;
            load(ar, cid);    // to be thrown away
            load(ar, co.tracking_level);
            load(ar, co.file_version);
        }
        else{
            // override tracking with indicator from class information
            co.tracking_level = co.bis_ptr->tracking(m_flags);
            co.file_version = version_type(
                co.bis_ptr->version()
            );
        }
        co.initialized = true;
    }
}

bool
basic_iarchive_impl::track(
    basic_iarchive & ar,
    void * & t
){
    object_id_type oid;
    load(ar, oid);

    // if its a reference to a old object
    if(object_id_type(object_id_vector.size()) > oid){
        // we're done
        t = object_id_vector[oid].address;
        return false;
    }
    return true;
}

inline void
basic_iarchive_impl::load_object(
    basic_iarchive & ar,
    void * t,
    const basic_iserializer & bis
){
    // if its been serialized through a pointer and the preamble's been done
    if(t == pending_object && & bis == pending_bis){
        // read data
        (bis.load_object_data)(ar, t, pending_version);
        return;
    }

    const class_id_type cid = register_type(bis);
    // note: extra line used to evade borland issue
    const int id = cid;
    cobject_id & co = cobject_id_vector[id];

    load_preamble(ar, co);
    // note: extra line used to evade borland issue
    const bool tracking = co.tracking_level;
    // if we didn't track this object when the archive was saved
    if(! tracking){ 
        // all we need to do is read the data
        (bis.load_object_data)(ar, t, co.file_version);
        return;
    }

    // we're tracking the object
    // if it was already read
    if(! track(ar, t))
        // we're done
        return;

    std::size_t tracking_list_position = object_id_vector.size();
    // add a new enty into the tracking list
    object_id_vector.push_back(aobject(t, cid));
    // save the current move stack position in case we want to truncate it
    std::size_t next_moveable_object_position = moveable_object_stack.size();
    // and add an entry for this object
    moveable_object_stack.push_back(tracking_list_position);

    // read data
    (bis.load_object_data)(ar, t, co.file_version);

    // last object created
    moveable_object_position = next_moveable_object_position;
}

inline const basic_pointer_iserializer *
basic_iarchive_impl::load_pointer(
    basic_iarchive &ar,
    void * & t,
    const basic_pointer_iserializer * bpis_ptr,
    const basic_pointer_iserializer * (*finder)(
        const boost::serialization::extended_type_info & type_
    )
){
    class_id_type cid;
    load(ar, cid);

    if(NULL_POINTER_TAG == cid){
        t = NULL;
        return bpis_ptr;
    }

    // if its a new class type - i.e. never been registered
    if(class_id_type(cobject_info_set.size()) <= cid){
        // if its either abstract
        if(NULL == bpis_ptr
        // or polymorphic
        || bpis_ptr->get_basic_serializer().is_polymorphic()){
            // is must have been exported
            char key[BOOST_SERIALIZATION_MAX_KEY_SIZE];
            class_name_type class_name(key);
            load(ar, class_name);
            // if it has a class name
            const serialization::extended_type_info *eti = NULL;
            if(0 != key[0])
                eti = serialization::extended_type_info::find(key);
            if(NULL == eti)
                boost::throw_exception(
                    archive_exception(archive_exception::unregistered_class)
                );
            bpis_ptr = (*finder)(*eti);
        }
        assert(NULL != bpis_ptr);
        class_id_type new_cid = register_type(bpis_ptr->get_basic_serializer());
        int i = cid;
        cobject_id_vector[i].bpis_ptr = bpis_ptr;
        assert(new_cid == cid);
    }
    int i = cid;
    cobject_id & co = cobject_id_vector[i];
    bpis_ptr = co.bpis_ptr;

    load_preamble(ar, co);

    // extra line to evade borland issue
    const bool tracking = co.tracking_level;
    // if we're tracking and the pointer has already been read
    if(tracking && ! track(ar, t))
        // we're done
        return bpis_ptr;

    // save state
    std::size_t original_moveable_stack_size(moveable_object_stack.size());
    state_saver<std::size_t> w(moveable_object_position);

    if(! tracking){
        bpis_ptr->load_object_ptr(ar, t, co.file_version);
    }
    else{
        state_saver<void *> x(pending_object);
        state_saver<const basic_iserializer *> y(pending_bis);
        state_saver<version_type> z(pending_version);

        pending_bis = & bpis_ptr->get_basic_serializer();
        pending_version = co.file_version;

        // predict next object id to be created
        const unsigned int ui = object_id_vector.size();

        // because the following operation could move the items
        // don't use co after this
        // add to list of serialized objects so that we can properly handle
        // cyclic strucures
        object_id_vector.push_back(aobject(t, cid));
        bpis_ptr->load_object_ptr(
            ar, 
            object_id_vector[ui].address, 
            co.file_version
        );
        t = object_id_vector[ui].address;
        assert(NULL != t);

        // and add to list of created pointers
        created_pointers.push_back(created_pointer_type(cid, t));
    }
    // anything pointed to is never moved 
    // so truncate the stack of moveable objects
    moveable_object_stack.resize(original_moveable_stack_size);

    return bpis_ptr;
}

//////////////////////////////////////////////////////////////////////
// implementation of basic_iarchive functions

void 
BOOST_DECL_ARCHIVE 
basic_iarchive::next_object_pointer(void *t){
    pimpl->next_object_pointer(t);
}

BOOST_DECL_ARCHIVE
basic_iarchive::basic_iarchive(unsigned int flags) : 
    pimpl(new basic_iarchive_impl(flags))
{}

BOOST_DECL_ARCHIVE
basic_iarchive::~basic_iarchive()
{
    delete pimpl;
}

void
BOOST_DECL_ARCHIVE
basic_iarchive::set_library_version(unsigned int archive_library_version){
    pimpl->set_library_version(archive_library_version);
}

void
BOOST_DECL_ARCHIVE
basic_iarchive::reset_object_address(
    const void * new_address, 
    const void * old_address
){
    pimpl->reset_object_address(new_address, old_address);
}

void
BOOST_DECL_ARCHIVE 
basic_iarchive::load_object(
    void *t, 
    const basic_iserializer & bis
){
    pimpl->load_object(*this, t, bis);
}

// load a pointer object
BOOST_DECL_ARCHIVE 
const basic_pointer_iserializer * 
basic_iarchive::load_pointer(
    void * &t, 
    const basic_pointer_iserializer * bpis_ptr,
    const basic_pointer_iserializer * (*finder)(
        const boost::serialization::extended_type_info & type_
    )
){
    return pimpl->load_pointer(*this, t, bpis_ptr, finder);
}

void
BOOST_DECL_ARCHIVE 
basic_iarchive::register_basic_serializer(const basic_iserializer & bis){
    pimpl->register_type(bis);
}

void
BOOST_DECL_ARCHIVE 
basic_iarchive::delete_created_pointers()
{
    pimpl->delete_created_pointers();
}

unsigned int 
BOOST_DECL_ARCHIVE 
basic_iarchive::get_library_version() const{
    return pimpl->m_archive_library_version;
}

unsigned int 
BOOST_DECL_ARCHIVE 
basic_iarchive::get_flags() const{
    return pimpl->m_flags;
}

BOOST_DECL_ARCHIVE 
boost::serialization::basic_helper * 
basic_iarchive::lookup_helper(
    const boost::serialization::extended_type_info * const eti
){
    return pimpl->lookup_helper(eti);
}

BOOST_DECL_ARCHIVE 
boost::serialization::basic_helper * 
basic_iarchive::insert_helper(
    boost::serialization::basic_helper * h,
    const boost::serialization::extended_type_info * const eti
){
    return pimpl->insert_helper(h, eti);
}

} // namespace detail
} // namespace archive
} // namespace boost
