/* boost random_device.cpp implementation
 *
 * Copyright Jens Maurer 2000
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#define BOOST_RANDOM_SOURCE

#include <boost/nondet_random.hpp>
#include <string>
#include <cassert>


#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
const bool boost::random_device::has_fixed_range;
const boost::random_device::result_type boost::random_device::min_value;
const boost::random_device::result_type boost::random_device::max_value;
#endif


#if defined(BOOST_WINDOWS)

#include <windows.h>
#include <wincrypt.h>
#include <stdexcept>  // std::invalid_argument

const char * const boost::random_device::default_token = "";

class boost::random_device::impl
{
public:
  impl(const std::string & token) : path(token) {
    std::basic_string<TCHAR> prov_name(token.begin(), token.end());
    if(prov_name.empty()) prov_name = MS_DEF_PROV;

    TCHAR buffer[80];
    DWORD type;
    DWORD len;

    // Find the type of the provider
    for(DWORD i = 0; ; ++i) {
      len = sizeof(buffer);
      if(!CryptEnumProviders(i, NULL, 0, &type, buffer, &len)) {
        error("Could not find provider");
      }
      if(buffer == prov_name) {
        break;
      }
    }

    if(!CryptAcquireContext(&hProv, NULL, prov_name.c_str(), type,
        CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
      error("Failed to aqcuire CSP context");
    }
  }

  ~impl() {
    if(!CryptReleaseContext(hProv, 0)) error("could not release CSP");
  }

  unsigned int next() {
    unsigned int result;

    if(!CryptGenRandom(hProv, sizeof(result),
        static_cast<BYTE*>(static_cast<void*>(&result)))) {
      error("error while reading");
    }

    return result;
  }

private:
  void error(const std::string & msg) {
    DWORD error_code = GetLastError();
    TCHAR buf[80];
    DWORD num = FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      GetLastError(),
      0,
      buf,
      sizeof(buf),
      NULL);

    throw std::invalid_argument("boost::random_device: " + msg + 
                                " random-number pseudo-device " + path + 
                                ": " + std::string(&buf[0], &buf[0] + num));
  }
  const std::string path;
  HCRYPTPROV hProv;
};

#else

// the default is the unlimited capacity device, using some secure hash
// try "/dev/random" for blocking when the entropy pool has drained
const char * const boost::random_device::default_token = "/dev/urandom";

/*
 * This uses the POSIX interface for unbuffered reading.
 * Using buffered std::istream would consume entropy which may
 * not actually be used.  Entropy is a precious good we avoid
 * wasting.
 */

#if defined(__GNUC__) && defined(_CXXRT_STD_NAME)
// I have severe difficulty to get the POSIX includes to work with
// -fhonor-std and Dietmar Kühl's standard C++ library.  Hack around that
// problem for now.
extern "C" {
static const int O_RDONLY = 0;
extern int open(const char *__file, int __oflag, ...);
extern int read(int __fd, __ptr_t __buf, size_t __nbytes);
extern int close(int __fd);
}
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // open
#include <unistd.h>   // read, close
#endif

#include <errno.h>    // errno
#include <string.h>   // strerror
#include <stdexcept>  // std::invalid_argument


class boost::random_device::impl
{
public:
  impl(const std::string & token) : path(token) {
    fd = open(token.c_str(), O_RDONLY);
    if(fd < 0)
      error("cannot open");
  }

  ~impl() { if(close(fd) < 0) error("could not close"); }

  unsigned int next() {
    unsigned int result;
    long sz = read(fd, reinterpret_cast<char *>(&result), sizeof(result));
    if(sz == -1)
      error("error while reading");
    else if(sz != sizeof(result)) {
      errno = 0;
      error("EOF while reading");
    }
    return result;
  }

private:
  void error(const std::string & msg) {
    throw std::invalid_argument("boost::random_device: " + msg + 
                                " random-number pseudo-device " + path + 
                                ": " + strerror(errno));
  }
  const std::string path;
  int fd;
};

#endif // BOOST_WINDOWS

boost::random_device::random_device(const std::string& token)
  : pimpl(new impl(token))
{
  assert((std::numeric_limits<result_type>::max)() == max_value);
}

boost::random_device::~random_device()
{
  // the complete class impl is now visible, so we're safe
  // (see comment in random.hpp)
  delete pimpl;
}

double boost::random_device::entropy() const
{
  return 10;
}

unsigned int boost::random_device::operator()()
{
  return pimpl->next();
}
