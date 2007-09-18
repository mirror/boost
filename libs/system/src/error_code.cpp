//  error_code support implementation file  ----------------------------------//

//  Copyright Beman Dawes 2002, 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//----------------------------------------------------------------------------//

//  VC++ 8.0 warns on usage of certain Standard Library and API functions that
//  can be cause buffer overruns or other possible security issues if misused.
//  See http://msdn.microsoft.com/msdnmag/issues/05/05/SafeCandC/default.aspx
//  But the wording of the warning is misleading and unsettling, there are no
//  portable alternative functions, and VC++ 8.0's own libraries use the
//  functions in question. So turn off the warnings.
#define _CRT_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE

// define BOOST_SYSTEM_SOURCE so that <boost/system/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#define BOOST_SYSTEM_SOURCE 

#include <boost/system/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/cerrno.hpp>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace boost::system;
using namespace boost::system::posix;

#include <cstring> // for strerror/strerror_r

# if defined( BOOST_WINDOWS_API )
#   include <windows.h>
#   ifndef ERROR_INCORRECT_SIZE
#    define ERROR_INCORRECT_SIZE ERROR_BAD_ARGUMENTS
#   endif
# endif

//----------------------------------------------------------------------------//

namespace
{

  struct system_to_posix_t
  { 
    int system_value;
    boost::system::posix::posix_errno posix_value;
  };

  const system_to_posix_t system_to_posix[] = 
  {

#ifdef BOOST_POSIX_API
  //  POSIX-like O/S -> posix_errno decode table  ----------------------------//

    // most common errors first to speed sequential search
    { ENOENT, no_such_file_or_directory },
    { EACCES, permission_denied },
    { EINVAL, invalid_argument },

    // rest are alphabetical for easy maintenance
    { 0, success }, 
    { E2BIG, argument_list_too_long },
    { EADDRINUSE, address_in_use },
    { EADDRNOTAVAIL, address_not_available },
    { EAFNOSUPPORT, address_family_not_supported },
    { EAGAIN, resource_unavailable_try_again },
    { EALREADY, connection_already_in_progress },
    { EBADF, bad_file_descriptor },
    { EBADMSG, bad_message },
    { EBUSY, device_or_resource_busy },
    { ECANCELED, operation_canceled },
    { ECHILD, no_child_process },
    { ECONNABORTED, connection_aborted },
    { ECONNREFUSED, connection_refused },
    { ECONNRESET, connection_reset },
    { EDEADLK, resource_deadlock_would_occur },
    { EDESTADDRREQ, destination_address_required },
    { EDOM, argument_out_of_domain },
    { EEXIST, file_exists },
    { EFAULT, bad_address },
    { EFBIG, file_too_large },
    { EHOSTUNREACH, host_unreachable },
    { EIDRM, identifier_removed },
    { EILSEQ, illegal_byte_sequence },
    { EINPROGRESS, operation_in_progress },
    { EINTR, interrupted },
    { EIO, io_error },
    { EISCONN, already_connected },
    { EISDIR, is_a_directory },
    { ELOOP, too_many_synbolic_link_levels },
    { EMFILE, too_many_files_open },
    { EMLINK, too_many_links },
    { EMSGSIZE, message_size },
    { ENAMETOOLONG, filename_too_long },
    { ENETDOWN, network_down },
    { ENETRESET, network_reset },
    { ENETUNREACH, network_unreachable },
    { ENFILE, too_many_files_open_in_system },
    { ENOBUFS, no_buffer_space },
    { ENODATA, no_message_available },
    { ENODEV, no_such_device },
    { ENOEXEC, executable_format_error },
    { ENOLCK, no_lock_available },
    { ENOLINK, no_link },
    { ENOMEM, not_enough_memory },
    { ENOMSG, no_message },
    { ENOPROTOOPT, no_protocol_option },
    { ENOSPC, no_space_on_device },
    { ENOSR, no_stream_resources },
    { ENOSTR, not_a_stream },
    { ENOSYS, function_not_supported },
    { ENOTCONN, not_connected },
    { ENOTDIR, not_a_directory },
    { ENOTEMPTY, directory_not_empty },
    { ENOTRECOVERABLE, state_not_recoverable },
    { ENOTSOCK, not_a_socket },
    { ENOTSUP, not_supported },
    { ENOTTY, inappropriate_io_control_operation },
    { ENXIO, no_such_device_or_address },
    { EOPNOTSUPP, operation_not_supported },
    { EOVERFLOW, value_too_large },
    { EOWNERDEAD, owner_dead },
    { EPERM, operation_not_permitted },
    { EPIPE, broken_pipe },
    { EPROTO, protocol_error },
    { EPROTONOSUPPORT, protocol_not_supported },
    { EPROTOTYPE, wrong_protocol_type },
    { ERANGE, result_out_of_range },
    { EROFS, read_only_file_system },
    { ESPIPE, invalid_seek },
    { ESRCH, no_such_process },
    { ETIME, stream_timeout },
    { ETIMEDOUT, timed_out },
    { ETXTBSY, text_file_busy },
    { EWOULDBLOCK, operation_would_block },
    { EXDEV, cross_device_link }

#else

  //  Windows system -> posix_errno decode table  ----------------------------//  

    // see WinError.h comments for descriptions of errors
    
    // most common errors first to speed sequential search
    { ERROR_FILE_NOT_FOUND, no_such_file_or_directory },
    { ERROR_PATH_NOT_FOUND, no_such_file_or_directory },

    // rest are alphabetical for easy maintenance
    { 0, success }, 
    { ERROR_ACCESS_DENIED, permission_denied },
    { ERROR_ALREADY_EXISTS, file_exists },
    { ERROR_BAD_UNIT, no_such_device },
    { ERROR_BUFFER_OVERFLOW, filename_too_long },
    { ERROR_BUSY, device_or_resource_busy },
    { ERROR_BUSY_DRIVE, device_or_resource_busy },
    { ERROR_CANNOT_MAKE, permission_denied },
    { ERROR_CANTOPEN, io_error },
    { ERROR_CANTREAD, io_error },
    { ERROR_CANTWRITE, io_error },
    { ERROR_CURRENT_DIRECTORY, permission_denied },
    { ERROR_DEV_NOT_EXIST, no_such_device },
    { ERROR_DEVICE_IN_USE, device_or_resource_busy },
    { ERROR_DIR_NOT_EMPTY, directory_not_empty },
    { ERROR_DIRECTORY, invalid_argument }, // WinError.h: "The directory name is invalid"
    { ERROR_DISK_FULL, no_space_on_device },
    { ERROR_FILE_EXISTS, file_exists },
    { ERROR_HANDLE_DISK_FULL, no_space_on_device },
    { ERROR_INVALID_ACCESS, permission_denied },
    { ERROR_INVALID_DRIVE, no_such_device },
    { ERROR_INVALID_FUNCTION, function_not_supported },
    { ERROR_INVALID_HANDLE, invalid_argument },
    { ERROR_INVALID_NAME, invalid_argument },
    { ERROR_LOCK_VIOLATION, no_lock_available },
    { ERROR_LOCKED, no_lock_available },
    { ERROR_NEGATIVE_SEEK, invalid_argument },
    { ERROR_NOACCESS, permission_denied },
    { ERROR_NOT_ENOUGH_MEMORY, not_enough_memory },
    { ERROR_NOT_READY, resource_unavailable_try_again },
    { ERROR_NOT_SAME_DEVICE, cross_device_link },
    { ERROR_OPEN_FAILED, io_error },
    { ERROR_OPEN_FILES, device_or_resource_busy },
    { ERROR_OUTOFMEMORY, not_enough_memory },
    { ERROR_READ_FAULT, io_error },
    { ERROR_SEEK, io_error },
    { ERROR_SHARING_VIOLATION, permission_denied },
    { ERROR_TOO_MANY_OPEN_FILES, too_many_files_open },
    { ERROR_WRITE_FAULT, io_error },
    { ERROR_WRITE_PROTECT, permission_denied }

#endif
  };

  //  standard error categories  -------------------------------------------//

  class posix_error_category : public error_category
  {
  public:
    const char *   name() const;
    std::string    message( int ev ) const;
  };

  class system_error_category : public error_category
  {
  public:
    const char *        name() const;
    posix::posix_errno  posix( int ev ) const;
    std::string         message( int ev ) const;
    error_condition     default_error_condition( int ev ) const;
  };

  const posix_error_category posix_category_const;
  const system_error_category system_category_const;

  //  posix_error_category implementation  ---------------------------------//

  const char * posix_error_category::name() const
  {
    return "POSIX";
  }

  std::string posix_error_category::message( int ev ) const
  {
  // strerror_r is preferred because it is always thread safe,
  // however, we fallback to strerror in certain cases because:
  //   -- Windows doesn't provide strerror_r.
  //   -- HP and Sundo provide strerror_r on newer systems, but there is
  //      no way to tell if is available at runtime and in any case their
  //      versions of strerror are thread safe anyhow.
  //   -- Linux only sometimes provides strerror_r.
  //   -- Tru64 provides strerror_r only when compiled -pthread.
  //   -- VMS doesn't provide strerror_r, but on this platform, strerror is
  //      thread safe.
  # if defined(BOOST_WINDOWS_API) || defined(__hpux) || defined(__sun)\
     || (defined(__linux) && (!defined(__USE_XOPEN2K) || defined(BOOST_SYSTEM_USE_STRERROR)))\
     || (defined(__osf__) && !defined(_REENTRANT))\
     || (defined(__vms))
      const char * c_str = std::strerror( ev );
      return std::string( c_str ? c_str : "invalid_argument" );
  # else
      char buf[64];
      char * bp = buf;
      std::size_t sz = sizeof(buf);
  #  if defined(__CYGWIN__) || defined(__USE_GNU)
      // Oddball version of strerror_r
      const char * c_str = strerror_r( ev, bp, sz );
      return std::string( c_str ? c_str : "invalid_argument" );
  #  else
      // POSIX version of strerror_r
      int result;
      for (;;)
      {
        // strerror_r returns 0 on success, otherwise ERANGE if buffer too small,
        // invalid_argument if ev not a valid error number
  #  if defined (__sgi)
        const char * c_str = strerror( ev );
        result = 0;
        return std::string( c_str ? c_str : "invalid_argument" );
  #  else
        result = strerror_r( ev, bp, sz );
  #  endif
        if (result == 0 )
          break;
        else
        {
  #  if defined(__linux)
          // Linux strerror_r returns -1 on error, with error number in errno
          result = errno;
  #  endif
          if ( result !=  ERANGE ) break;
        if ( sz > sizeof(buf) ) std::free( bp );
        sz *= 2;
        if ( (bp = static_cast<char*>(std::malloc( sz ))) == 0 )
          return std::string( "ENOMEM" );
        }
      }
      try
      {
      std::string msg( ( result == invalid_argument ) ? "invalid_argument" : bp );
      if ( sz > sizeof(buf) ) std::free( bp );
        sz = 0;
      return msg;
      }
      catch(...)
      {
        if ( sz > sizeof(buf) ) std::free( bp );
        throw;
      }
  #  endif
  # endif
  }
  //  system_error_category implementation  --------------------------------// 

  const char * system_error_category::name() const
  {
    return "system";
  }

  posix_errno system_error_category::posix( int ev ) const
  {
    const system_to_posix_t * cur = system_to_posix;
    do
    {
      if ( ev == cur->system_value )
        return cur->posix_value;
      ++cur;
    } while ( cur != system_to_posix
      + sizeof(system_to_posix)/sizeof(system_to_posix_t) );
    return static_cast<posix::posix_errno>(-1);
  }

  error_condition system_error_category::default_error_condition( int ev ) const
  {
    int tmp = posix(ev);
    return tmp >= 0
      ? error_condition( tmp, posix_category )
      : error_condition( ev, system_category );
  }

# if !defined( BOOST_WINDOWS_API )

  std::string system_error_category::message( int ev ) const
  {
    return posix_category.message( ev );
  }
# else
// TODO:
  
//Some quick notes on the implementation (sorry for the noise if
//someone has already mentioned them):
//
//- The ::LocalFree() usage isn't exception safe.
//
//See:
//
//<http://boost.cvs.sourceforge.net/boost/boost/boost/asio/system_exception.hpp?revision=1.1&view=markup>
//
//in the implementation of what() for an example.
//
//Cheers,
//Chris
  std::string system_error_category::message( int ev ) const
  {
    LPVOID lpMsgBuf;
    ::FormatMessageA( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        ev,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPSTR) &lpMsgBuf,
        0,
        NULL 
    );
    std::string str( static_cast<LPCSTR>(lpMsgBuf) );
    ::LocalFree( lpMsgBuf ); // free the buffer
    while ( str.size()
      && (str[str.size()-1] == '\n' || str[str.size()-1] == '\r') )
        str.erase( str.size()-1 );
    if ( str.size() && str[str.size()-1] == '.' ) 
      { str.erase( str.size()-1 ); }
    return str;
  }
# endif

} // unnamed namespace

namespace boost
{
  namespace system
  {

    BOOST_SYSTEM_DECL const error_category & posix_category
      = posix_category_const;

    BOOST_SYSTEM_DECL const error_category & system_category
      = system_category_const;

    // deprecated synonyms
    BOOST_SYSTEM_DECL const error_category & errno_ecat
      = posix_category_const;

    BOOST_SYSTEM_DECL const error_category & native_ecat
      = system_category_const;

  } // namespace system
} // namespace boost
