#ifndef BOOST_WEAK_PTR_HPP_INCLUDED
#define BOOST_WEAK_PTR_HPP_INCLUDED

//
//  weak_ptr.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/smart_ptr/weak_ptr.htm for documentation.
//

#include <boost/shared_ptr.hpp>

#include <boost/config.hpp>   // for broken compiler workarounds
#include <boost/assert.hpp>

#include <boost/detail/shared_count.hpp>

#include <algorithm>          // for std::swap
#include <functional>         // for std::less

#ifdef BOOST_MSVC  // moved here to work around VC++ compiler crash
# pragma warning(push)
# pragma warning(disable:4284) // odd return type for operator->
#endif    

namespace boost
{

template<typename T> class weak_ptr
{
private:

    // Borland 5.5.1 specific workarounds
    typedef weak_ptr<T> this_type;

public:

    typedef T element_type;

    weak_ptr(): px(0), pn()
    {
    }

//  generated copy constructor, assignment, destructor are fine

    template<typename Y>
    weak_ptr(weak_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }

    template<typename Y>
    weak_ptr(shared_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }

    template<typename Y>
    weak_ptr(weak_ptr<Y> const & r, detail::static_cast_tag): px(static_cast<element_type *>(r.px)), pn(r.pn)
    {
    }

    template<typename Y>
    weak_ptr(weak_ptr<Y> const & r, detail::dynamic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if (px == 0) // need to allocate new counter -- the cast failed
        {
            pn = detail::weak_count();
        }
    }

    template<typename Y>
    weak_ptr & operator=(weak_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn;
        return *this;
    }

    template<typename Y>
    weak_ptr & operator=(shared_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn;
        return *this;
    }

    void reset()
    {
        this_type().swap(*this);
    }

    T * get() const // never throws
    {
        return use_count() == 0? 0: px;
    }

    typename detail::shared_ptr_traits<T>::reference operator* () const // never throws
    {
        T * p = get();
        BOOST_ASSERT(p != 0);
        return *p;
    }

    T * operator-> () const // never throws
    {
        T * p = get();
        BOOST_ASSERT(p != 0);
        return p;
    }
    
    long use_count() const // never throws
    {
        return pn.use_count();
    }

    void swap(weak_ptr<T> & other) // never throws
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<typename Y> friend class weak_ptr;

#endif

    T * px;                     // contained pointer
    detail::weak_count pn;      // reference counter

};  // weak_ptr

template<class T, class U> inline bool operator==(weak_ptr<T> const & a, weak_ptr<U> const & b)
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(weak_ptr<T> const & a, weak_ptr<U> const & b)
{
    return a.get() != b.get();
}

template<class T> inline bool operator<(weak_ptr<T> const & a, weak_ptr<T> const & b)
{
    return std::less<T*>()(a.get(), b.get());
}

template<class T> void swap(weak_ptr<T> & a, weak_ptr<T> & b)
{
    a.swap(b);
}

template<class T, class U> weak_ptr<T> shared_static_cast(weak_ptr<U> const & r)
{
    return weak_ptr<T>(r, detail::static_cast_tag());
}

template<class T, class U> weak_ptr<T> shared_dynamic_cast(weak_ptr<U> const & r)
{
    return weak_ptr<T>(r, detail::dynamic_cast_tag());
}

// get_pointer() enables boost::mem_fn to recognize weak_ptr

template<class T> inline T * get_pointer(weak_ptr<T> const & p)
{
    return p.get();
}

} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif    

#endif  // #ifndef BOOST_WEAK_PTR_HPP_INCLUDED
