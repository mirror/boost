//  synchronizaion.hpp  --------------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_DETAIL_WINAPI_SYNCHRONIZATION_HPP
#define BOOST_DETAIL_WINAPI_SYNCHRONIZATION_HPP

#include <boost/detail/winapi/basic_types.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost
{
namespace detail
{
namespace winapi
{
#if defined( BOOST_USE_WINDOWS_H )
    typedef ::CRITICAL_SECTION CRITICAL_SECTION_;
    typedef ::PAPCFUNC PAPCFUNC_;

    using ::InitializeCriticalSection;
    using ::EnterCriticalSection;
    using ::TryEnterCriticalSection;
    using ::LeaveCriticalSection;
    using ::DeleteCriticalSection;

# ifdef BOOST_NO_ANSI_APIS
    using ::CreateMutexW;
    using ::CreateEventW;
    using ::OpenEventW;
    using ::CreateSemaphoreW;
# else
    using ::CreateMutexA;
    using ::CreateEventA;
    using ::OpenEventA;
    using ::CreateSemaphoreA;
# endif
    using ::ReleaseMutex;
    using ::ReleaseSemaphore;
    using ::SetEvent;
    using ::ResetEvent;
    using ::WaitForMultipleObjects;
    using ::WaitForSingleObject;
    using ::QueueUserAPC;

    const DWORD_ infinite       = INFINITE;
    const DWORD_ wait_abandoned = WAIT_ABANDONED;
    const DWORD_ wait_object_0  = WAIT_OBJECT_0;
    const DWORD_ wait_timeout   = WAIT_TIMEOUT;
    const DWORD_ wait_failed    = WAIT_FAILED;

#else // defined( BOOST_USE_WINDOWS_H )

extern "C" {

    struct CRITICAL_SECTION_
    {
        struct critical_section_debug * DebugInfo;
        long LockCount;
        long RecursionCount;
        void * OwningThread;
        void * LockSemaphore;
    #if defined(_WIN64)
        unsigned __int64 SpinCount;
    #else
        unsigned long SpinCount;
    #endif
    };

     __declspec(dllimport) void WINAPI
        InitializeCriticalSection(CRITICAL_SECTION_ *);
    __declspec(dllimport) void WINAPI
        EnterCriticalSection(CRITICAL_SECTION_ *);
    __declspec(dllimport) bool WINAPI
        TryEnterCriticalSection(CRITICAL_SECTION_ *);
    __declspec(dllimport) void WINAPI
        LeaveCriticalSection(CRITICAL_SECTION_ *);
    __declspec(dllimport) void WINAPI
        DeleteCriticalSection(CRITICAL_SECTION_ *);

    struct _SECURITY_ATTRIBUTES;
# ifdef BOOST_NO_ANSI_APIS
    __declspec(dllimport) HANDLE_ WINAPI
        CreateMutexW(_SECURITY_ATTRIBUTES*, BOOL_, LPCWSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenMutexW(DWORD_ dwDesiredAccess, BOOL_ bInheritHandle, LPCWSTR_ lpName);
    __declspec(dllimport) HANDLE_ WINAPI
        CreateSemaphoreW(_SECURITY_ATTRIBUTES*, LONG_, LONG_, LPCWSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenSemaphoreW(DWORD_ dwDesiredAccess, BOOL_ bInheritHandle, LPCWSTR_ lpName);
    __declspec(dllimport) HANDLE_ WINAPI
        CreateEventW(_SECURITY_ATTRIBUTES*, BOOL_, BOOL_, LPCWSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenEventW(DWORD_, BOOL_, LPCWSTR_);
# else
    __declspec(dllimport) HANDLE_ WINAPI
        CreateMutexA(_SECURITY_ATTRIBUTES*, BOOL_, LPCSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenMutexA(DWORD_ dwDesiredAccess, BOOL_ bInheritHandle, LPCSTR_ lpName);
    __declspec(dllimport) HANDLE_ WINAPI
        CreateSemaphoreA(_SECURITY_ATTRIBUTES*, LONG_, LONG_, LPCSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenSemaphoreA(DWORD_ dwDesiredAccess, BOOL_ bInheritHandle, LPCSTR_ lpName);
    __declspec(dllimport) HANDLE_ WINAPI
        CreateEventA(_SECURITY_ATTRIBUTES*, BOOL_, BOOL_, LPCSTR_);
    __declspec(dllimport) HANDLE_ WINAPI
        OpenEventA(DWORD_, BOOL_, LPCSTR_);
# endif
    __declspec(dllimport) BOOL_ WINAPI
        ReleaseMutex(HANDLE_);
    __declspec(dllimport) DWORD_ WINAPI
        WaitForSingleObject(HANDLE_, DWORD_);
    __declspec(dllimport) DWORD_ WINAPI
        WaitForMultipleObjects(DWORD_ nCount,
                HANDLE_ const * lpHandles,
                BOOL_ bWaitAll,
                DWORD_ dwMilliseconds);
    __declspec(dllimport) BOOL_ WINAPI
        ReleaseSemaphore(HANDLE_, LONG_, LONG_*);
    typedef void (__stdcall *PAPCFUNC8)(ULONG_PTR_);
    __declspec(dllimport) DWORD_ WINAPI
        QueueUserAPC(PAPCFUNC8, HANDLE_, ULONG_PTR_);
# ifndef UNDER_CE
    __declspec(dllimport) BOOL_ WINAPI
        SetEvent(HANDLE_);
    __declspec(dllimport) BOOL_ WINAPI
        ResetEvent(HANDLE_);
# else
    using ::SetEvent;
    using ::ResetEvent;
# endif

} // extern "C"

const DWORD_ infinite       = (DWORD_)0xFFFFFFFF;
const DWORD_ wait_abandoned = 0x00000080L;
const DWORD_ wait_object_0  = 0x00000000L;
const DWORD_ wait_timeout   = 0x00000102L;
const DWORD_ wait_failed    = (DWORD_)0xFFFFFFFF;

#endif // defined( BOOST_USE_WINDOWS_H )

BOOST_FORCEINLINE HANDLE_ create_anonymous_mutex(_SECURITY_ATTRIBUTES* lpAttributes, BOOL_ bInitialOwner)
{
#ifdef BOOST_NO_ANSI_APIS
    return CreateMutexW(lpAttributes, bInitialOwner, 0);
#else
    return CreateMutexA(lpAttributes, bInitialOwner, 0);
#endif
}

BOOST_FORCEINLINE HANDLE_ create_anonymous_semaphore(_SECURITY_ATTRIBUTES* lpAttributes, LONG_ lInitialCount, LONG_ lMaximumCount)
{
#ifdef BOOST_NO_ANSI_APIS
    return CreateSemaphoreW(lpAttributes, lInitialCount, lMaximumCount, 0);
#else
    return CreateSemaphoreA(lpAttributes, lInitialCount, lMaximumCount, 0);
#endif
}

BOOST_FORCEINLINE HANDLE_ create_anonymous_event(_SECURITY_ATTRIBUTES* lpAttributes, BOOL_ bManualReset, BOOL_ bInitialState)
{
#ifdef BOOST_NO_ANSI_APIS
    return CreateEventW(lpAttributes, bManualReset, bInitialState, 0);
#else
    return CreateEventA(lpAttributes, bManualReset, bInitialState, 0);
#endif
}

}
}
}

#endif // BOOST_DETAIL_WINAPI_SYNCHRONIZATION_HPP
