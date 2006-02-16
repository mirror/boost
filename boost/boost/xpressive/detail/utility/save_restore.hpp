///////////////////////////////////////////////////////////////////////////////
// save_restore.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_UTILITY_SAVE_RESTORE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_UTILITY_SAVE_RESTORE_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // save-and-restore implementation
    //   a simple variant of ScopeGuard for saving an restoring a variable's value
    struct restore_base
    {
    };

    typedef restore_base const &restore;

    template<typename T>
    struct restore_impl
      : restore_base
    {
        mutable T *ref;
        T const val;

        explicit restore_impl(T &t)
          : ref(&t)
          , val(t)
        {
        }

        restore_impl(T &t, T const &n)
          : ref(&t)
          , val(t)
        {
            *this->ref = n;
        }

        restore_impl(restore_impl<T> const &that)
          : ref(that.ref)
          , val(that.val)
        {
            that.ref = 0;
        }

        ~restore_impl()
        {
            if(0 != this->ref)
            {
                *this->ref = this->val;
            }
        }

    private:
        restore_impl &operator =(restore_impl<T> const &);
    };

    template<typename T>
    inline restore_impl<T> save(T &t)
    {
        return restore_impl<T>(t);
    }

    template<typename T>
    inline restore_impl<T> save(T &t, T const &n)
    {
        return restore_impl<T>(t, n);
    }

}}}

#endif
