#ifndef BOOST_SERIALIZATION_SHARED_PTR_HPP
#define BOOST_SERIALIZATION_SHARED_PTR_HPP

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

#include <set>

#include <boost/detail/workaround.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/basic_helper.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace serialization{
namespace detail {

class shared_ptr_holder_base {
public:
    virtual const void * get_raw_pointer() const = 0;
    virtual const void * get_shared_pointer() const = 0;
    bool operator<(const shared_ptr_holder_base & rhs) const {
        return get_raw_pointer() < rhs.get_raw_pointer();
    }
};

class shared_ptr_holder_arg : public shared_ptr_holder_base {
    const void * const m_p;
    const void * get_raw_pointer() const {
        return m_p;
    }
    const void * get_shared_pointer() const {
        return NULL;
    }
public:
    shared_ptr_holder_arg(const void * const p) :
        m_p(p)
    {}
};

template<class T>
class shared_ptr_holder : public shared_ptr_holder_base {
    boost::shared_ptr<T> m_sp;
    const void * get_raw_pointer() const {
        return static_cast<const void *>(m_sp.get());
    }
    const void * get_shared_pointer() const {
        return & m_sp;
    }
public:
    shared_ptr_holder(const boost::shared_ptr<T> & sp) :
    m_sp(sp)
    {}
};

class shared_ptr_helper : public basic_helper {
    typedef const shared_ptr_holder_base * value_type;
    typedef std::set<value_type> collection_type;
    typedef collection_type::const_iterator iterator_type;
    collection_type m_pointers;
    const shared_ptr_holder_base * find(const void * const raw_ptr) const {
        const shared_ptr_holder_arg spha(raw_ptr);
        iterator_type it = m_pointers.find(& spha);
        if(it == m_pointers.end())
            return NULL;
        return *it;
    }
public:
    template<class T>
    void reset(shared_ptr<T> & s, T * r){
        if(NULL == r){
            s.reset();
            return;
        }
        // sp_arg can only used as a search argument
        const shared_ptr_holder_base * psphb = find(r);
        if(NULL == psphb){
            // uh - oh doesn't look good to me. but I see no alternative
            s.reset(r);
            psphb = new shared_ptr_holder<T>(s);
            m_pointers.insert(psphb);
        }
        else
            s = * static_cast<const shared_ptr<T> *>(psphb->get_shared_pointer());
    }
    virtual ~shared_ptr_helper(){
        if(! m_pointers.empty()){
            // delete shared pointer holders
            for(
                iterator_type it = m_pointers.begin();
                it !=  m_pointers.end();
                ++it
            ){
                #if BOOST_WORKAROUND(BOOST_MSVC, <= 1200)
                    delete const_cast<shared_ptr_holder_base *>(*it);
                #else
                    delete *it;
                #endif
            }
        }
    }
};

} // namespace detail

// set serialization traits
// version 1 to distinguis from boost 1.32 version
template<class T>
struct version< ::boost::shared_ptr<T> > {                                                                      \
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<1> type;
    BOOST_STATIC_CONSTANT(unsigned int, value = type::value);
};

// don't track shared pointers
template<class T>
struct tracking_level< ::boost::shared_ptr<T> > { 
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_< ::boost::serialization::track_never> type;
    BOOST_STATIC_CONSTANT(int, value = type::value);                                       \
};

template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost::shared_ptr<T> &t,
    const unsigned int /* file_version */
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level<T>::value != track_never));
    const T * t_ptr = t.get();
	ar << boost::serialization::make_nvp("px", t_ptr);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::shared_ptr<T> &t,
    const unsigned int /* file_version */
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level<T>::value != track_never));
	T* r;
	ar >> boost::serialization::make_nvp("px", r);
    detail::shared_ptr_helper & sph = ar.get_helper(
        static_cast<detail::shared_ptr_helper *>(NULL)
    );
    sph.reset(t,r);
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost::shared_ptr<T> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_SHARED_PTR_HPP
