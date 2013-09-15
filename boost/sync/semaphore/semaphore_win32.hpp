// semaphore.hpp, win32 semaphores
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_SEMAPHORE_SEMAPHORE_WIN32_HPP
#define BOOST_SYNC_SEMAPHORE_SEMAPHORE_WIN32_HPP

#include <boost/detail/win/GetLastError.hpp>
#include <boost/detail/win/synchronization.hpp>
#include <boost/detail/win/handles.hpp>

#include <boost/typeof/typeof.hpp>

namespace boost {
namespace sync {

class semaphore
{
    BOOST_DELETED_FUNCTION(semaphore(semaphore const&))
    BOOST_DELETED_FUNCTION(semaphore& operator=(semaphore const&))

    typedef boost::detail::win32::HANDLE_ HANDLE_;
    typedef boost::detail::win32::DWORD_  DWORD_;
    typedef boost::detail::win32::LONG_   LONG_;
    typedef boost::detail::win32::BOOL_   BOOL_;

public:
    semaphore(int i=0)
    {
        BOOST_ASSERT_MSG(i >= 0, "boost::sync::semaphore constructor called with negative count");

        sem_ = boost::detail::win32::CreateSemaphoreA(NULL, i, (std::numeric_limits<LONG_>::max)(), NULL);
        if (!sem_)
            boost::throw_exception(thread_resource_error(boost::detail::win32::GetLastError(), "boost::sync::semaphore constructor failed in CreateSemaphore"));
    }

    ~semaphore()
    {
        boost::detail::win32::CloseHandle(sem_);
    }

    void post()
    {
        const BOOL_ status = boost::detail::win32::ReleaseSemaphore(sem_, 1, NULL);
        if (status == 0)
            boost::throw_exception(thread_resource_error(boost::detail::win32::GetLastError(), "boost::sync::semaphore::post failed in ReleaseSemaphore"));
    }


    bool wait()
    {
        using namespace boost::detail::win32;

        switch ( WaitForSingleObject(sem_, INFINITE) )
        {
        case wait_object_0:
            return true;

        case wait_failed:
            boost::throw_exception(thread_resource_error(boost::detail::win32::GetLastError(), "boost::sync::semaphore::wait failed in WaitForSingleObject"));

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
        BOOST_AUTO ( milliseconds, (DWORD_)chrono::duration_cast<chrono::milliseconds>( rel_time ) );
        return do_try_wait_for( milliseconds.count() );
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
        using namespace boost::detail::win32;

        switch ( WaitForSingleObject(sem_, milliseconds) )
        {
        case wait_object_0:
            return true;

        case wait_timeout:
            return false;

        case wait_failed:
            boost::throw_exception(thread_resource_error(boost::detail::win32::GetLastError(), "boost::sync::semaphore::do_try_wait_for failed in WaitForSingleObject"));

        default:
            BOOST_ASSERT(false);
            return false;
        }
    }
#endif

    HANDLE_ sem_;
};

}
}

#endif // BOOST_SYNC_SEMAPHORE_SEMAPHORE_WIN32_HPP
