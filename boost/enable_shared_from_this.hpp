#ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
#define BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

//
//  enable_shared_from_this.hpp
//
//  Copyright (c) 2002 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/smart_ptr/enable_shared_from_this.html
//

#include <boost/detail/shared_count.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost
{

template<class T> class enable_shared_from_this
{
// dynamic cast to template type doesn't work in constructor, so we have
// to use lazy initialization
    void init_internal_shared_once() const
    {
        if( !owned() && _internal_shared_count.empty() )
        {
            T * p = dynamic_cast<T *>(const_cast<enable_shared_from_this*>(this));
            detail::shared_count( p, detail::sp_deleter_wrapper() ).swap(_internal_shared_count);
            _internal_weak_count = _internal_shared_count;
        }
    }

    bool owned() const
    {
        return _owned;
    }

    mutable detail::shared_count _internal_shared_count;
    mutable detail::weak_count _internal_weak_count;
    mutable bool _owned;

protected:

    enable_shared_from_this():
      _owned(false)
    {
    }

    enable_shared_from_this(enable_shared_from_this const &):
      _owned(false)
    {
    }

    enable_shared_from_this & operator=(enable_shared_from_this const &)
    {
        return *this;
    }

// virtual destructor because we need a vtable for dynamic_cast from base to derived to work
    virtual ~enable_shared_from_this()
    {
// make sure no dangling shared_ptr objects were created by the
// user calling shared_from_this() but never passing ownership of the object
// to a shared_ptr.
        BOOST_ASSERT(owned() || _internal_shared_count.use_count() <= 1);
    }

public:

    shared_ptr<T> shared_from_this()
    {
        init_internal_shared_once();
        T * p = dynamic_cast<T *>(this);
        return shared_ptr<T>( detail::shared_count( _internal_weak_count ), p );
    }

    shared_ptr<T const> shared_from_this() const
    {
        init_internal_shared_once();
        T const * p = dynamic_cast<T const *>(this);
        return shared_ptr<T const>( detail::shared_count( _internal_weak_count ), p );
    }

    template<typename U>
    void _internal_accept_owner(shared_ptr<U> &owner) const
    {
        if( !_owned )
        {
            if( _internal_shared_count.empty() )
            {
                _internal_weak_count = owner.get_shared_count();
            }else
            {
                BOOST_ASSERT(owner.unique()); // no weak_ptrs to owner should exist either, but there's no way to check that
                typedef detail::sp_deleter_wrapper D;
                D * pd = static_cast<D *>(_internal_shared_count.get_deleter(BOOST_SP_TYPEID(D)));
                BOOST_ASSERT( pd != 0 );
                pd->set_deleter(owner);

                shared_ptr<U>( _internal_shared_count, owner.get() ).swap( owner );
                detail::shared_count().swap(_internal_shared_count);
            }
            _owned = true;
        }
    }
};

template< class T, class Y > inline void sp_accept_owner( boost::shared_ptr<Y> * ptr, boost::enable_shared_from_this<T> const * pe )
{
    if( pe != 0 )
    {
        pe->_internal_accept_owner( *ptr );
    }
}

template< class T, class Y > inline void sp_accept_owner( boost::shared_ptr<Y> * ptr, boost::enable_shared_from_this<T> const * pe, void * /*pd*/ )
{
    if( pe != 0 )
    {
        pe->_internal_accept_owner( *ptr );
    }
}

template< class T, class Y > inline void sp_accept_owner( boost::shared_ptr<Y> * /*ptr*/, boost::enable_shared_from_this<T> const * /*pe*/, boost::detail::sp_deleter_wrapper * /*pd*/ )
{
}

} // namespace boost

#endif  // #ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
