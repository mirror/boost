// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Inspired by fdstream.hpp, (C) Copyright Nicolai M. Josuttis 2001,
// available at http://www.josuttis.com/cppcode/fdstream.html.

// Define BOOST_IOSTREAMS_SOURCE so that <boost/iostreams/detail/config.hpp>
// knows that we are building the library (possibly exporting code), rather
// than using it (possibly importing code).
#define BOOST_IOSTREAMS_SOURCE 

#include <ios>              // openmodes, failure.
#include <boost/config.hpp> // BOOST_JOIN
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

    // OS-specific headers for low-level i/o.

#include <cassert>
#include <cstdio>        // SEEK_SET, etc.
#include <errno.h>
#include <fcntl.h>       // file opening flags.
#include <sys/stat.h>    // file access permissions.
#ifdef BOOST_IOSTREAMS_WINDOWS
# include <io.h>         // low-level file i/o.
#else
# include <sys/types.h>  // mode_t.
# include <unistd.h>     // low-level file i/o.
#endif

// Names of runtime library routines vary.
#if defined(__BORLANDC__)
# define BOOST_RTL(x) BOOST_JOIN(_rtl_, x)
#else
# if defined(BOOST_IOSTREAMS_WINDOWS) && !defined(__CYGWIN__)
#  define BOOST_RTL(x) BOOST_JOIN(_, x)
# else
#  define BOOST_RTL(x) ::x
# endif
#endif

namespace boost { namespace iostreams {

//------------------Implementation of file_descriptor-------------------------//

void file_descriptor::open
    ( const std::string& path, std::ios::openmode m,
      std::ios::openmode base )
{
    using namespace std;
    m |= base;

        // Calculate oflag argument to open.

    int oflag = 0;
    if ((m & (ios::in | ios::out)) == (ios::in | ios::out)) {
        assert(!(m & ios::app));
        oflag |= O_RDWR;
    } else if (m & ios::in) {
        assert(!(m & (ios::app |ios::trunc)));
        oflag |= O_RDONLY;
    } else if (m & ios::out) {
        oflag |= O_WRONLY;
        m |= ios::trunc;
        if (m & ios::app)
            oflag |= O_APPEND;
    }
    if (m & ios::trunc)
        oflag |= O_CREAT;
    #ifdef BOOST_IOSTREAMS_WINDOWS
        if (m & ios::binary)
            oflag |= O_BINARY;
    #endif

        // Calculate pmode argument to open.

    #if defined(BOOST_IOSTREAMS_POSIX) || defined(__CYGWIN__)
        mode_t pmode = S_IRUSR | S_IWUSR |
                       S_IRGRP | S_IWGRP |
                       S_IROTH | S_IWOTH;
    #else
    # if !defined(__BORLANDC__)
        int pmode = _S_IREAD | _S_IWRITE;
    # endif
    #endif

        // Open file.

    #ifndef __BORLANDC__
        fd_ = BOOST_RTL(open)(path.c_str(), oflag, pmode);
    #else
        fd_ = (m & ios::out) && (!(m & ios::in) || (m & ios::trunc)) ?
            BOOST_RTL(creat)(path.c_str(), 0) :
            BOOST_RTL(open)(path.c_str(), oflag);
    #endif

    if (fd_ == -1)
        throw std::ios::failure("bad open");
    close_ = true;
}

std::streamsize file_descriptor::read(char_type* s, std::streamsize n)
{
    errno = 0;
    std::streamsize result = BOOST_RTL(read)(fd_, s, n);
    if (errno != 0)
        throw std::ios::failure("bad open");
    return result;
}

void file_descriptor::write(const char_type* s, std::streamsize n)
{
    int result = BOOST_RTL(write)(fd_, s, n);
    if (result < n)
        throw detail::bad_write();
}

std::streamoff file_descriptor::seek
    (std::streamoff off, std::ios::seekdir way)
{
    using namespace std;
    std::streamoff result =
        #if !defined(__BORLANDC__)
            BOOST_RTL(lseek)
        #else
            lseek
        #endif
            (fd_, off, way == ios::beg ?
                           SEEK_SET :
                           way == ios::cur ?
                               SEEK_CUR :
                               SEEK_END );
    if (result == -1)
        throw detail::bad_seek();
    return result;
}

void file_descriptor::close()
{
    if (close_ && fd_ != -1 && BOOST_RTL(close)(fd_) == -1)
        throw std::ios::failure("bad close");
}

} } // End namespaces iostreams, boost.
