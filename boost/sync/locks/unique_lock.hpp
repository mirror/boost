/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007 Anthony Williams
 * (C) Copyright 2011-2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   locks/unique_lock.hpp
 *
 * \brief  This header defines an exclusive lock guard.
 */

#ifndef BOOST_SYNC_LOCKS_UNIQUE_LOCK_HPP_INCLUDED_
#define BOOST_SYNC_LOCKS_UNIQUE_LOCK_HPP_INCLUDED_

#include <cstddef>
#include <boost/utility/enable_if.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/locks/lock_options.hpp>

#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

/*!
 * \brief A unique lock scope guard
 */
template< typename MutexT >
class unique_lock
{
public:
    typedef MutexT mutex_type;

private:
    mutex_type* m_mutex;
    bool m_is_locked;

private:
    explicit unique_lock(upgrade_lock< mutex_type >&);
    unique_lock& operator= (upgrade_lock< mutex_type >& other);

public:
    BOOST_THREAD_MOVABLE_ONLY( unique_lock)

    unique_lock() BOOST_NOEXCEPT :
        m_mutex(NULL), m_is_locked(false)
    {
    }

    explicit unique_lock(mutex_type& m) :
        m_mutex(&m), m_is_locked(false)
    {
        lock();
    }
    unique_lock(mutex_type& m, adopt_lock_t) BOOST_NOEXCEPT :
        m_mutex(&m), m_is_locked(true)
    {
    }
    unique_lock(mutex_type& m, defer_lock_t) BOOST_NOEXCEPT :
        m_mutex(&m), m_is_locked(false)
    {
    }
    unique_lock(mutex_type& m, try_to_lock_t) :
        m_mutex(&m), m_is_locked(false)
    {
        try_lock();
    }

    template< typename TimeT >
    unique_lock(typename enable_if_c< aux::time_traits< TimeT >::is_supported, mutex_type& >::type m, TimeT const& t) :
        m_mutex(&m), m_is_locked(false)
    {
        tined_lock(t);
    }

    unique_lock(BOOST_THREAD_RV_REF(unique_lock) other) BOOST_NOEXCEPT :
        m(BOOST_THREAD_RV(other).m),m_is_locked(BOOST_THREAD_RV(other).m_is_locked)
    {
        BOOST_THREAD_RV(other).m_is_locked = false;
        BOOST_THREAD_RV(other).m_mutex = NULL;
    }

    BOOST_THREAD_EXPLICIT_LOCK_CONVERSION unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other);

#ifndef BOOST_THREAD_PROVIDES_EXPLICIT_LOCK_CONVERSION
    //std-2104 unique_lock move-assignment should not be noexcept
    unique_lock& operator=(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other) //BOOST_NOEXCEPT
    {
        unique_lock temp(::boost::move(other));
        swap(temp);
        return *this;
    }
#endif

    //std-2104 unique_lock move-assignment should not be noexcept
    unique_lock& operator=(BOOST_THREAD_RV_REF(unique_lock) other) //BOOST_NOEXCEPT
    {
        unique_lock temp(::boost::move(other));
        swap(temp);
        return *this;
    }

    // Conversion from upgrade lock
    unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul, try_to_lock_t) :
        m_mutex(NULL), m_is_locked(false)
    {
        if (BOOST_THREAD_RV(ul).owns_lock())
        {
            if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock())
            {
                m_mutex = BOOST_THREAD_RV(ul).release();
                m_is_locked = true;
            }
        }
        else
        {
            m_mutex = BOOST_THREAD_RV(ul).release();
        }
    }

#ifdef BOOST_THREAD_USES_CHRONO
  template <class Clock, class Duration>
  unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul,
      const chrono::time_point<Clock, Duration>& abs_time)
  : m(0),m_is_locked(false)
  {
    if (BOOST_THREAD_RV(ul).owns_lock())
    {
      if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock_until(abs_time))
      {
        m = BOOST_THREAD_RV(ul).release();
        m_is_locked = true;
      }
    }
    else
    {
      m = BOOST_THREAD_RV(ul).release();
    }
  }

  template <class Rep, class Period>
  unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul,
      const chrono::duration<Rep, Period>& rel_time)
  : m(0),m_is_locked(false)
  {
    if (BOOST_THREAD_RV(ul).owns_lock())
    {
      if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock_for(rel_time))
      {
        m = BOOST_THREAD_RV(ul).release();
        m_is_locked = true;
      }
    }
    else
    {
      m = BOOST_THREAD_RV(ul).release();
    }
  }
#endif

#ifdef BOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS
  // Conversion from shared locking
  unique_lock(BOOST_THREAD_RV_REF_BEG shared_lock<mutex_type> BOOST_THREAD_RV_REF_END sl, try_to_lock_t)
  : m(0),m_is_locked(false)
  {
    if (BOOST_THREAD_RV(sl).owns_lock())
    {
      if (BOOST_THREAD_RV(sl).mutex()->try_unlock_shared_and_lock())
      {
        m = BOOST_THREAD_RV(sl).release();
        m_is_locked = true;
      }
    }
    else
    {
      m = BOOST_THREAD_RV(sl).release();
    }
  }

#ifdef BOOST_THREAD_USES_CHRONO
  template <class Clock, class Duration>
  unique_lock(BOOST_THREAD_RV_REF_BEG shared_lock<mutex_type> BOOST_THREAD_RV_REF_END sl,
      const chrono::time_point<Clock, Duration>& abs_time)
  : m(0),m_is_locked(false)
  {
    if (BOOST_THREAD_RV(sl).owns_lock())
    {
      if (BOOST_THREAD_RV(sl).mutex()->try_unlock_shared_and_lock_until(abs_time))
      {
        m = BOOST_THREAD_RV(sl).release();
        m_is_locked = true;
      }
    }
    else
    {
      m = BOOST_THREAD_RV(sl).release();
    }
  }

  template <class Rep, class Period>
  unique_lock(BOOST_THREAD_RV_REF_BEG shared_lock<mutex_type> BOOST_THREAD_RV_REF_END sl,
      const chrono::duration<Rep, Period>& rel_time)
  : m(0),m_is_locked(false)
  {
    if (BOOST_THREAD_RV(sl).owns_lock())
    {
      if (BOOST_THREAD_RV(sl).mutex()->try_unlock_shared_and_lock_for(rel_time))
      {
        m = BOOST_THREAD_RV(sl).release();
        m_is_locked = true;
      }
    }
    else
    {
      m = BOOST_THREAD_RV(sl).release();
    }
  }
#endif // BOOST_THREAD_USES_CHRONO
#endif // BOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS

  void swap(unique_lock& other)BOOST_NOEXCEPT
  {
    std::swap(m,other.m);
    std::swap(m_is_locked,other.m_is_locked);
  }

  ~unique_lock()
  {
    if (owns_lock())
    {
      m->unlock();
    }
  }

  void lock()
  {
    if (m == 0)
    {
      boost::throw_exception(
          boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if (owns_lock())
    {
      boost::throw_exception(
          boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m->lock();
    m_is_locked = true;
  }

  bool try_lock()
  {
    if (m == 0)
    {
      boost::throw_exception(
          boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if (owns_lock())
    {
      boost::throw_exception(
          boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked = m->try_lock();
    return m_is_locked;
  }
#if defined BOOST_THREAD_USES_DATETIME
  template<typename TimeDuration>
  bool timed_lock(TimeDuration const& relative_time)
  {
    if(m==0)
    {
      boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if(owns_lock())
    {
      boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked=m->timed_lock(relative_time);
    return m_is_locked;
  }

  bool timed_lock(::boost::system_time const& absolute_time)
  {
    if(m==0)
    {
      boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if(owns_lock())
    {
      boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked=m->timed_lock(absolute_time);
    return m_is_locked;
  }
  bool timed_lock(::boost::xtime const& absolute_time)
  {
    if(m==0)
    {
      boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if(owns_lock())
    {
      boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked=m->timed_lock(absolute_time);
    return m_is_locked;
  }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

  template <class Rep, class Period>
  bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
  {
    if(m==0)
    {
      boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if(owns_lock())
    {
      boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked=m->try_lock_for(rel_time);
    return m_is_locked;
  }
  template <class Clock, class Duration>
  bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
  {
    if(m==0)
    {
      boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if(owns_lock())
    {
      boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
    }
    m_is_locked=m->try_lock_until(abs_time);
    return m_is_locked;
  }
#endif

  void unlock()
  {
    if (m == 0)
    {
      boost::throw_exception(
          boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
    }
    if (!owns_lock())
    {
      boost::throw_exception(
          boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock doesn't own the mutex"));
    }
    m->unlock();
    m_is_locked = false;
  }

#if defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
  typedef void (unique_lock::*bool_type)();
  operator bool_type() const BOOST_NOEXCEPT
  {
    return m_is_locked?&unique_lock::lock:0;
  }
  bool operator!() const BOOST_NOEXCEPT
  {
    return !owns_lock();
  }
#else
  explicit operator bool() const BOOST_NOEXCEPT
  {
    return owns_lock();
  }
#endif
  bool owns_lock() const BOOST_NOEXCEPT
  {
    return m_is_locked;
  }

  Mutex* mutex() const BOOST_NOEXCEPT
  {
    return m;
  }

  Mutex* release() BOOST_NOEXCEPT
  {
    Mutex* const res=m;
    m=0;
    m_is_locked=false;
    return res;
  }
};

template< typename MutexT >
inline void swap(unique_lock< MutexT >& lhs, unique_lock< MutexT >& rhs) BOOST_NOEXCEPT
{
    lhs.swap(rhs);
}


} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_LOCKS_UNIQUE_LOCK_HPP_INCLUDED_
