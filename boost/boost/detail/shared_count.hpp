#ifndef BOOST_DETAIL_SHARED_COUNT_HPP_INCLUDED
#define BOOST_DETAIL_SHARED_COUNT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/shared_count.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#if defined(BOOST_SP_USE_STD_ALLOCATOR) && defined(BOOST_SP_USE_QUICK_ALLOCATOR)
# error BOOST_SP_USE_STD_ALLOCATOR and BOOST_SP_USE_QUICK_ALLOCATOR are incompatible.
#endif

#include <boost/checked_delete.hpp>
#include <boost/throw_exception.hpp>
#include <boost/detail/bad_weak_ptr.hpp>
#include <boost/detail/sp_counted_base.hpp>

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)
#include <boost/detail/quick_allocator.hpp>
#endif

#include <memory>           // std::auto_ptr, std::allocator
#include <functional>       // std::less
#include <new>              // std::bad_alloc
#include <typeinfo>         // std::type_info in get_deleter
#include <cstddef>          // std::size_t

#ifdef __BORLANDC__
# pragma warn -8027     // Functions containing try are not expanded inline
#endif

namespace boost
{

// Debug hooks

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_scalar_constructor_hook(void * px, std::size_t size, void * pn);
void sp_array_constructor_hook(void * px);
void sp_scalar_destructor_hook(void * px, std::size_t size, void * pn);
void sp_array_destructor_hook(void * px);

#endif

namespace detail
{

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

template<class T> void cbi_call_constructor_hook(sp_counted_base * pn, T * px, checked_deleter<T> const &, int)
{
    boost::sp_scalar_constructor_hook(px, sizeof(T), pn);
}

template<class T> void cbi_call_constructor_hook(sp_counted_base *, T * px, checked_array_deleter<T> const &, int)
{
    boost::sp_array_constructor_hook(px);
}

template<class P, class D> void cbi_call_constructor_hook(sp_counted_base *, P const &, D const &, long)
{
}

template<class T> void cbi_call_destructor_hook(sp_counted_base * pn, T * px, checked_deleter<T> const &, int)
{
    boost::sp_scalar_destructor_hook(px, sizeof(T), pn);
}

template<class T> void cbi_call_destructor_hook(sp_counted_base *, T * px, checked_array_deleter<T> const &, int)
{
    boost::sp_array_destructor_hook(px);
}

template<class P, class D> void cbi_call_destructor_hook(sp_counted_base *, P const &, D const &, long)
{
}

#endif

//
// Borland's Codeguard trips up over the -Vx- option here:
//
#ifdef __CODEGUARD__
# pragma option push -Vx-
#endif

template<class P, class D> class sp_counted_base_impl: public sp_counted_base
{
private:

    P ptr; // copy constructor must not throw
    D del; // copy constructor must not throw

    sp_counted_base_impl(sp_counted_base_impl const &);
    sp_counted_base_impl & operator= (sp_counted_base_impl const &);

    typedef sp_counted_base_impl<P, D> this_type;

public:

    // pre: d(p) must not throw

    sp_counted_base_impl(P p, D d): ptr(p), del(d)
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_constructor_hook(this, p, d, 0);
#endif
    }

    virtual void dispose() // nothrow
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_destructor_hook(this, ptr, del, 0);
#endif
        del(ptr);
    }

    virtual void * get_deleter(std::type_info const & ti)
    {
        return ti == typeid(D)? &del: 0;
    }

#if defined(BOOST_SP_USE_STD_ALLOCATOR)

    void * operator new(std::size_t)
    {
        return std::allocator<this_type>().allocate(1, static_cast<this_type *>(0));
    }

    void operator delete(void * p)
    {
        std::allocator<this_type>().deallocate(static_cast<this_type *>(p), 1);
    }

#endif

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)

    void * operator new(std::size_t)
    {
        return quick_allocator<this_type>::alloc();
    }

    void operator delete(void * p)
    {
        quick_allocator<this_type>::dealloc(p);
    }

#endif
};

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

int const shared_count_id = 0x2C35F101;
int const   weak_count_id = 0x298C38A4;

#endif

class weak_count;

class shared_count
{
private:

    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class weak_count;

public:

    shared_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }

    template<class P, class D> shared_count(P p, D d): pi_(0)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_base_impl<P, D>(p, d);
        }
        catch(...)
        {
            d(p); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_base_impl<P, D>(p, d);

        if(pi_ == 0)
        {
            d(p); // delete p
            boost::throw_exception(std::bad_alloc());
        }

#endif
    }

#ifndef BOOST_NO_AUTO_PTR

    // auto_ptr<Y> is special cased to provide the strong guarantee

    template<class Y>
    explicit shared_count(std::auto_ptr<Y> & r): pi_(new sp_counted_base_impl< Y *, checked_deleter<Y> >(r.get(), checked_deleter<Y>()))
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        r.release();
    }

#endif 

    ~shared_count() // nothrow
    {
        if(pi_ != 0) pi_->release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    shared_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->add_ref_copy();
    }

    explicit shared_count(weak_count const & r); // throws bad_weak_ptr when r.use_count() == 0

    shared_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if(tmp != pi_)
        {
            if(tmp != 0) tmp->add_ref_copy();
            if(pi_ != 0) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(shared_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    bool unique() const // nothrow
    {
        return use_count() == 1;
    }

    friend inline bool operator==(shared_count const & a, shared_count const & b)
    {
        return a.pi_ == b.pi_;
    }

    friend inline bool operator<(shared_count const & a, shared_count const & b)
    {
        return std::less<sp_counted_base *>()(a.pi_, b.pi_);
    }

    void * get_deleter(std::type_info const & ti) const
    {
        return pi_? pi_->get_deleter(ti): 0;
    }
};

#ifdef __CODEGUARD__
# pragma option pop
#endif


class weak_count
{
private:

    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class shared_count;

public:

    weak_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
    }

    weak_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

    weak_count(weak_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

    ~weak_count() // nothrow
    {
        if(pi_ != 0) pi_->weak_release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    weak_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

        return *this;
    }

    weak_count & operator= (weak_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

        return *this;
    }

    void swap(weak_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    friend inline bool operator==(weak_count const & a, weak_count const & b)
    {
        return a.pi_ == b.pi_;
    }

    friend inline bool operator<(weak_count const & a, weak_count const & b)
    {
        return std::less<sp_counted_base *>()(a.pi_, b.pi_);
    }
};

inline shared_count::shared_count(weak_count const & r): pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if( pi_ == 0 || !pi_->add_ref_lock() )
    {
        boost::throw_exception( boost::bad_weak_ptr() );
    }
}

} // namespace detail

} // namespace boost

#ifdef __BORLANDC__
# pragma warn .8027     // Functions containing try are not expanded inline
#endif

#endif  // #ifndef BOOST_DETAIL_SHARED_COUNT_HPP_INCLUDED
