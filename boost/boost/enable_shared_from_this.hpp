#ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
#define BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

//
//  enable_shared_from_this.hpp
//
//  Copyright (c) 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  http://www.boost.org/libs/smart_ptr/enable_shared_from_this.html
//

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace boost
{

template<class T> class enable_shared_from_this
{
public:

    shared_ptr<T> shared_from_this()
    {
        return shared_ptr<T>(weak_this);
    }

    shared_ptr<T const> shared_from_this() const
    {
        return shared_ptr<T const>(weak_this);
    }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<class Y> friend class shared_ptr;

#endif

    weak_ptr<T> weak_this;
};

} // namespace boost

#endif  // #ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
