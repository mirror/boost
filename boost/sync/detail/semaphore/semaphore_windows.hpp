// semaphore.hpp, win32 semaphores
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_WINDOWS_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_WINDOWS_HPP_INCLUDED_

#include <cstddef>
#include <limits>
#include <boost/detail/win/GetLastError.hpp>
#include <boost/detail/win/synchronization.hpp>
#include <boost/detail/win/handles.hpp>
#include <boost/throw_exception.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class semaphore
{
    BOOST_DELETED_FUNCTION(semaphore(semaphore const&))
    BOOST_DELETED_FUNCTION(semaphore& operator=(semaphore const&))

    typedef boost::detail::win32::HANDLE_ HANDLE_;
    typedef boost::detail::win32::DWORD_  DWORD_;
    typedef boost::detail::win32::LONG_   LONG_;
    typedef boost::detail::win32::BOOL_   BOOL_;

public:
    explicit semaphore(unsigned int i = 0)
    {
        m_sem = boost::detail::win32::CreateSemaphoreA(NULL, i, (std::numeric_limits<LONG_>::max)(), NULL);
        if (!m_sem)
        {
            const DWORD_ err = boost::detail::win32::GetLastError();
            BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore constructor failed in CreateSemaphore"));
        }
    }

    ~semaphore() BOOST_NOEXCEPT
    {
        int status = boost::detail::win32::CloseHandle(m_sem);
        BOOST_VERIFY (status != 0);
    }

    void post()
    {
        const BOOL_ status = boost::detail::win32::ReleaseSemaphore(m_sem, 1, NULL);
        if (status == 0)
        {
            const DWORD_ err = boost::detail::win32::GetLastError();
            BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore::post failed in ReleaseSemaphore"));
        }
    }


    bool wait()
    {
        switch (boost::detail::win32::WaitForSingleObject(m_sem, boost::detail::win32::infinite))
        {
        case boost::detail::win32::wait_object_0:
            return true;

        case boost::detail::win32::wait_failed:
            {
                const DWORD_ err = boost::detail::win32::GetLastError();
                BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore::wait failed in WaitForSingleObject"));
            }

        default:
            BOOST_ASSERT(false);
            return false;
        }
    }


    bool try_wait()
    {
        return do_try_wait_for( 0L );
    }

#ifdef BOOST_SYNC_USES_CHRONO
    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & rel_time)
    {
        return do_try_wait_for(static_cast< DWORD_ >(chrono::duration_cast<chrono::milliseconds>( rel_time ).count()));
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout )
    {
        typename Clock::time_point  c_now = Clock::now();
        return try_wait_for( timeout - c_now );
    }
#endif

private:
#ifdef BOOST_SYNC_USES_CHRONO
    bool do_try_wait_for( long milliseconds )
    {
        switch (boost::detail::win32::WaitForSingleObject(m_sem, milliseconds))
        {
        case boost::detail::win32::wait_object_0:
            return true;

        case boost::detail::win32::wait_timeout:
            return false;

        case boost::detail::win32::wait_failed:
            {
                const DWORD_ err = boost::detail::win32::GetLastError();
                BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore::do_try_wait_for failed in WaitForSingleObject"));
            }

        default:
            BOOST_ASSERT(false);
            return false;
        }
    }
#endif

    HANDLE_ m_sem;
};

} // namespace winnt

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_WINDOWS_HPP_INCLUDED_
