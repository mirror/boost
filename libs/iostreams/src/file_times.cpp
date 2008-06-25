/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        libs/iostreams/src/file_times.cpp
 * Date:        Sun Jun 22 14:23:12 MDT 2008
 * Copyright:   Jorge Lodos and 2008 CodeRage, LLC
 * Author:      Jorge Lodos and Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Implements the functions declared in the header 
 * <boost/iostreams/detail/file_times.hpp>.
 */

// Define BOOST_IOSTREAMS_SOURCE so that <boost/iostreams/detail/config.hpp>
// knows that we are building the library (possibly exporting code), rather
// than using it (possibly importing code).
#define BOOST_IOSTREAMS_SOURCE

#include <ctime>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/file_times.hpp>
#include <boost/iostreams/detail/system_failure.hpp>

#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>      // futimes
# include <sys/types.h>     // struct stat.
#endif

namespace boost { namespace iostreams { namespace detail {

time_t last_read_time(file_handle h)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    FILETIME ft_access;
    if (!::GetFileTime(h, NULL, &ft_access, NULL))
        throw_system_failure("failed querying last access time");
    SYSTEMTIME st_access;
    if (!FileTimeToSystemTime(&ft_access, &st_access))
        throw_system_failure("failed querying last access time");
    std::tm tm;
    tm.tm_sec = st_access.wSecond;
    tm.tm_min = st_access.wMinute;
    tm.tm_hour = st_access.wHour;
    tm.tm_mday = st_access.wDay;
    tm.tm_mon = st_access.wMonth - 1;
    tm.tm_year = st_access.wYear - 1900;
    return std::mktime(&tm);
#else    
    struct stat info;
    if (::fstat(handle_, &info) == -1)
        throw_system_failure("failed querying last access time");
    return info.st_atime;
#endif
}

void set_last_read_time(file_handle h, time_t tm)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    struct std::tm* t = std::gmtime(&tm);
	if (t == NULL)
        throw_system_failure("failed settting last access time");
    SYSTEMTIME st_access;
    st_access.wSecond = t->tm_sec;
    st_access.wMinute = t->tm_min;
    st_access.wHour = t->tm_hour;
    st_access.wDay = t->tm_mday;
    st_access.wMonth = t->tm_mon + 1;
    st_access.wYear = t->tm_year + 1900;
    FILETIME ft_access;
    if (!SystemTimeToFileTime(&st_access, &ft_access))
        throw_system_failure("failed settting last access time");
    if (!::SetFileTime(h, NULL, &ft_access, NULL))
        throw_system_failure("failed settting last access time");
#else
    struct stat info;
    if (::fstat(handle_, &info) == -1)
        throw_system_failure("failed settting last access time");
    struct timeval tv[2];
    tv[0].tv_sec = tm;
    tv[0].tv_usec = 0;
    tv[1].tv_sec = info.st_mtime;
    tv[1].tv_usec = 0;
    if (futimes(handle_, tv) != 0)
        throw_system_failure("failed settting last access time");
#endif
}

time_t last_write_time(file_handle h)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    FILETIME ft_modification;
    if (!::GetFileTime(h, NULL, NULL, &ft_modification))
        throw_system_failure("failed querying last modification time");
    SYSTEMTIME st_modification;
    if (!FileTimeToSystemTime(&ft_modification, &st_modification))
        throw_system_failure("failed querying last modification time");
    std::tm tm;
    tm.tm_sec = st_modification.wSecond;
    tm.tm_min = st_modification.wMinute;
    tm.tm_hour = st_modification.wHour;
    tm.tm_mday = st_modification.wDay;
    tm.tm_mon = st_modification.wMonth - 1;
    tm.tm_year = st_modification.wYear - 1900;
    return std::mktime(&tm);
#else
    struct stat info;
    if (::fstat(handle_, &info) == -1)
        throw_system_failure("failed querying last modification time");
    return info.st_mtime;
#endif
}

void set_last_write_time(file_handle h, time_t tm)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    struct std::tm* t = std::gmtime(&tm);
	if (t == NULL)
        throw_system_failure("failed settting last modification time");
    SYSTEMTIME st_modification;
    st_modification.wSecond = t->tm_sec;
    st_modification.wMinute = t->tm_min;
    st_modification.wHour = t->tm_hour;
    st_modification.wDay = t->tm_mday;
    st_modification.wMonth = t->tm_mon + 1;
    st_modification.wYear = t->tm_year + 1900;
    FILETIME ft_modification;
    if (!SystemTimeToFileTime(&st_modification, &ft_modification))
        throw_system_failure("failed settting last modification time");
    if(!::SetFileTime(h, NULL, &ft_modification, NULL))
        throw_system_failure("failed settting last modification time");
#else
    struct stat info;
    if (::fstat(handle_, &info) == -1)
        throw_system_failure("failed settting last modification time");
    struct timeval tv[2];
    tv[0].tv_sec = info.st_atime;
    tv[0].tv_usec = 0;
    tv[1].tv_sec = tm;
    tv[1].tv_usec = 0;
    if (futimes(handle_, tv) != 0)
        throw_system_failure("failed settting last modification time");
#endif
}

} } } // End namespaces detail, iostreams, boost.
