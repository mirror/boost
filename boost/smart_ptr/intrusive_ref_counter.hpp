/*
 *          Copyright Andrey Semashev 2007 - 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   intrusive_ref_counter.hpp
 * \author Andrey Semashev
 * \date   12.03.2009
 *
 * This header contains a reference counter class for \c intrusive_ptr.
 */

#ifndef BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_
#define BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_

#include <boost/config.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sp_adl_block {

/*!
 * \brief Thread unsafe reference counter policy for \c basic_intrusive_ref_counter
 *
 * The policy instructs the \c basic_intrusive_ref_counter base class to implement
 * a reference counter suitable for single threaded use only. Pointers to the same
 * object with this kind of reference counter must not be used by different threads.
 */
struct thread_unsafe_counter
{
    typedef unsigned int type;

    static unsigned int load(unsigned int const& counter) BOOST_NOEXCEPT
    {
        return counter;
    }

    static void increment(unsigned int& counter) BOOST_NOEXCEPT
    {
        ++counter;
    }

    static unsigned int decrement(unsigned int& counter) BOOST_NOEXCEPT
    {
        return --counter;
    }
};

/*!
 * \brief Thread safe reference counter policy for \c basic_intrusive_ref_counter
 *
 * The policy instructs the \c basic_intrusive_ref_counter base class to implement
 * a thread-safe reference counter, if the target platform supports multithreading.
 */
struct thread_safe_counter
{
    typedef boost::detail::atomic_count type;

    static unsigned int load(boost::detail::atomic_count const& counter) BOOST_NOEXCEPT
    {
        return static_cast< unsigned int >(static_cast< long >(counter));
    }

    static void increment(boost::detail::atomic_count& counter) BOOST_NOEXCEPT
    {
        ++counter;
    }

    static unsigned int decrement(boost::detail::atomic_count& counter) BOOST_NOEXCEPT
    {
        return --counter;
    }
};

template< typename CounterPolicyT >
class basic_intrusive_ref_counter;

template< typename CounterPolicyT >
void intrusive_ptr_add_ref(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT;
template< typename CounterPolicyT >
void intrusive_ptr_release(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT;

/*!
 * \brief A reference counter base class
 *
 * This base class can be used with user-defined classes to add support
 * for \c intrusive_ptr. The class contains a reference counter defined by the \c CounterPolicyT
 * and a virtual destructor, which makes the derived class polymorphic.
 * Upon releasing the last \c intrusive_ptr referencing the object
 * derived from the \c basic_intrusive_ref_counter class, operator \c delete
 * is automatically called on the pointer to the object.
 */
template< typename CounterPolicyT >
class basic_intrusive_ref_counter
{
private:
    //! Reference counter type
    typedef typename CounterPolicyT::type counter_type;
    //! Reference counter
    mutable counter_type m_ref_counter;

public:
    /*!
     * Default constructor
     *
     * \post <tt>use_count() == 0</tt>
     */
    basic_intrusive_ref_counter() : m_ref_counter(0)
    {
    }

    /*!
     * Copy constructor
     *
     * \post <tt>use_count() == 0</tt>
     */
    basic_intrusive_ref_counter(basic_intrusive_ref_counter const&) : m_ref_counter(0)
    {
    }

    /*!
     * Virtual destructor
     */
    virtual ~basic_intrusive_ref_counter() {}

    /*!
     * Assignment
     *
     * \post The reference counter is not modified after assignment
     */
    basic_intrusive_ref_counter& operator= (basic_intrusive_ref_counter const&) BOOST_NOEXCEPT { return *this; }

    /*!
     * \return The reference counter
     */
    unsigned int use_count() const BOOST_NOEXCEPT
    {
        return CounterPolicyT::load(m_ref_counter);
    }

    friend void intrusive_ptr_add_ref< CounterPolicyT >(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT;
    friend void intrusive_ptr_release< CounterPolicyT >(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT;
};

template< typename CounterPolicyT >
inline void intrusive_ptr_add_ref(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT
{
    CounterPolicyT::increment(p->m_ref_counter);
}

template< typename CounterPolicyT >
inline void intrusive_ptr_release(const basic_intrusive_ref_counter< CounterPolicyT >* p) BOOST_NOEXCEPT
{
    if (CounterPolicyT::decrement(p->m_ref_counter) == 0)
        delete p;
}

} // namespace sp_adl_block

using sp_adl_block::basic_intrusive_ref_counter;
using sp_adl_block::thread_unsafe_counter;
using sp_adl_block::thread_safe_counter;

//! Convenience typedef for the default reference counter type
typedef basic_intrusive_ref_counter< thread_safe_counter > intrusive_ref_counter;

} // namespace boost

#endif // BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_
