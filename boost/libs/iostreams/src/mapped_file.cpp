// (C) Copyright Craig Henderson 2002 'boost/memmap.hpp' from sandbox
// (C) Copyright Jonathan Turkanis 2004.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Define BOOST_IOSTREAMS_SOURCE so that <boost/iostreams/detail/config.hpp>
// knows that we are building the library (possibly exporting code), rather
// than using it (possibly importing code).
#define BOOST_IOSTREAMS_SOURCE 

#include <cassert>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
// BEGIN DEBUG
//#include <iostream>
// END DEBUG

#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <errno.h>
# include <fcntl.h>
# include <sys/mman.h>      // mmap, munmap.
# include <sys/stat.h>
# include <sys/types.h>     // struct stat.
# include <unistd.h>        // sysconf.
#endif

namespace boost { namespace iostreams {

namespace detail {

struct mapped_file_impl {
    mapped_file_impl() : error_(false) { clear(false); }
    ~mapped_file_impl() { close(); }
    void clear(bool error)
    {
        data_ = 0;
        size_ = 0;
        mode_ = std::ios::openmode();
        error_ = error;
        handle_ = 0;
        #ifdef BOOST_IOSTREAMS_WINDOWS
            mapped_handle_ = 0;
        #endif
    }
    void close()
    {
        if (!handle_)
            return;
        #ifdef BOOST_IOSTREAMS_WINDOWS
            ::SetLastError(0);
            ::UnmapViewOfFile(data_);
            ::CloseHandle(mapped_handle_);
            ::CloseHandle(handle_);
            error_ = ::GetLastError() != 0;
            // BEGIN DEBUG
            //std::cout << "closing file: error = " << ::GetLastError() << "\n";
            // END DEBUG
        #else
            errno = 0;
            ::munmap(reinterpret_cast<char *>(data_), size_);
            ::close(handle_);
            error_ = errno != 0;
        #endif
    }
    char*                data_;
    std::size_t          size_;
    std::ios::openmode   mode_;
    bool                 error_;
#ifdef BOOST_IOSTREAMS_WINDOWS
    HANDLE               handle_;
    HANDLE               mapped_handle_;
#else
    int                  handle_;
#endif
};

} // End namespace detail.

mapped_file_source::mapped_file_source( const std::string& path,
                                        mapped_file_source::size_type length,
                                        boost::intmax_t offset )
{ open(path, std::ios::in, length, offset); }

void mapped_file_source::open( const std::string& path, size_type length,
                               boost::intmax_t offset )
{ open(path, std::ios::in, length, offset); }

mapped_file_source::size_type mapped_file_source::size() const
{ return pimpl_->size_; }

bool mapped_file_source::is_open() const
{ return !!pimpl_ && pimpl_->handle_ != 0; }

void mapped_file_source::close() { pimpl_->close(); }

mapped_file_source::operator mapped_file_source::safe_bool() const
{
    return !!pimpl_ && pimpl_->error_ == false ?
        &safe_bool_helper::x : 0;
}

bool mapped_file_source::operator!() const
{ return !!pimpl_ || pimpl_->error_; }

std::ios::openmode mapped_file_source::mode() const { return pimpl_->mode_; }

const char* mapped_file_source::data() const { return pimpl_->data_; }

const char* mapped_file_source::begin() const { return data(); }

const char* mapped_file_source::end() const { return data() + size(); }

#ifdef BOOST_IOSTREAMS_WINDOWS //----------------------------------------------------//

void close_handles(detail::mapped_file_impl& impl)
{
    ::CloseHandle(impl.mapped_handle_);
    ::CloseHandle(impl.handle_);
    impl.clear(true);
}

void mapped_file_source::open( const std::string& path, std::ios::openmode mode,
                               size_type length, boost::intmax_t offset )
{
    using namespace std;

    if (is_open())
        throw ios::failure("file already open");
    if (!pimpl_)
        pimpl_.reset(new impl_type);
    else
        pimpl_->clear(false);
    bool readonly = (mode & ios::out) == 0;
    pimpl_->mode_ = readonly ? ios::in : (ios::in | ios::out);

    //--------------Open underlying file--------------------------------------//


    // BEGIN DEBUG
    //SetLastError(0);
    //std::cout << "about to open file " << path.c_str() << "\n";
    // END DEBUG

    pimpl_->handle_ =
        ::CreateFileA( path.c_str(),
                       readonly ? GENERIC_READ : GENERIC_ALL,
                       FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if (pimpl_->handle_ == INVALID_HANDLE_VALUE) {
        pimpl_->clear(true);
        // BEGIN DEBUG
        //std::cout << "failed opening file " << path.c_str() << std::endl;
        //std::cout << "GetLastError() ==  " << GetLastError() << std::endl;
        // END DEBUG
        return;
    }

    //--------------Create mapping--------------------------------------------//

    pimpl_->mapped_handle_ =
        ::CreateFileMappingA( pimpl_->handle_, NULL,
                              readonly ? PAGE_READONLY : PAGE_READWRITE,
                              0, 0, path.c_str() );
    if (pimpl_->mapped_handle_ == NULL) {
        ::CloseHandle(pimpl_->handle_);
        pimpl_->clear(true);
        // BEGIN DEBUG
        //std::cout << "failed creating mapping for file " << path.c_str() << std::endl;
        // END DEBUG
        return;
    }

    //--------------Access data-----------------------------------------------//

    void* data =
        ::MapViewOfFileEx( pimpl_->mapped_handle_,
                           readonly ? FILE_MAP_READ : FILE_MAP_WRITE,
                           (DWORD) (offset >> (sizeof(DWORD) * 8)),
                           (DWORD) (offset & 0xffffffff),
                           length != max_length ? length : 0, 0 );
    if (!data) {
        close_handles(*pimpl_);
        // BEGIN DEBUG
        //std::cout << "failed mapping view for for file " << path.c_str() <<std::endl;
        // END DEBUG
        return;
    }

    //--------------Determing file size---------------------------------------//

    // Dynamically locate GetFileSizeEx (thanks to Pavel Vozenilik).
    typedef BOOL (WINAPI *func)(HANDLE, PLARGE_INTEGER);
    HMODULE hmod = ::GetModuleHandleA("kernel32.dll");
    func get_size =
        reinterpret_cast<func>(::GetProcAddress(hmod, "GetFileSizeEx"));

    if (get_size) {
        LARGE_INTEGER info;
        if (get_size(pimpl_->handle_, &info)) {
            boost::intmax_t size =
                ( (static_cast<boost::intmax_t>(info.HighPart) << 32) |
                  info.LowPart );
            pimpl_->size_ =
                static_cast<std::size_t>(
                    length != max_length ?
                        std::min<boost::intmax_t>(length, size) :
                        size
                );
        } else {
            close_handles(*pimpl_);
            // BEGIN DEBUG
            //std::cout << "failed getting size_ex of file " << path.c_str() << "\n";
            // END DEBUG
            return;
        }
    } else {
        DWORD hi;
        DWORD low;
        if ( (low = ::GetFileSize(pimpl_->handle_, &hi))
                 !=
             INVALID_FILE_SIZE )
        {
            boost::intmax_t size =
                (static_cast<boost::intmax_t>(hi) << 32) | low;
            pimpl_->size_ =
                static_cast<std::size_t>(
                    length != max_length ?
                        std::min<boost::intmax_t>(length, size) :
                        size
                );
        } else {
            close_handles(*pimpl_);
            // BEGIN DEBUG
            //std::cout << "failed getting size of file " << path.c_str() << "\n";
            // END DEBUG
            return;
        }
    }

    pimpl_->data_ = reinterpret_cast<char*>(data);
}

int mapped_file_source::alignment()
{
    SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    return static_cast<int>(info.dwAllocationGranularity);
}

#else // #ifdef BOOST_IOSTREAMS_WINDOWS //-------------------------------------------//

void mapped_file_source::open( const std::string& path, std::ios::openmode mode,
                               size_type length, boost::intmax_t offset )
{
    using namespace std;

    if (is_open())
        throw ios::failure("file already open");
    if (!pimpl_)
        pimpl_.reset(new impl_type);
    else
        pimpl_->clear(false);
    bool readonly = (mode & ios::out) == 0;
    pimpl_->mode_ = readonly ? ios::in : (ios::in | ios::out);

    //--------------Open underlying file--------------------------------------//

    errno = 0;
    pimpl_->handle_ = ::open(path.c_str(), readonly? O_RDONLY : O_RDWR);
    if (errno != 0)
        return;

    //--------------Determine file size---------------------------------------//

    bool success = true;
    struct stat info;
    if (length != max_length)
        pimpl_->size_ = length;
    else {
        success = ::fstat(pimpl_->handle_, &info) != -1;
        pimpl_->size_ = info.st_size;
    }
    if (!success) {
        ::close(pimpl_->handle_);
        pimpl_->clear(true);
        return;
    }

    //--------------Create mapping--------------------------------------------//

    void* data = ::mmap( 0, pimpl_->size_,
                         readonly ? PROT_READ : PROT_WRITE,
                         MAP_SHARED | MAP_FILE,
                         // readonly ? MAP_PRIVATE : MAP_SHARED,
                         pimpl_->handle_, offset );
    if (data == MAP_FAILED) {
        ::close(pimpl_->handle_);
        pimpl_->clear(true);
        return;
    }
    pimpl_->data_ = reinterpret_cast<char*>(data);

    return;
}

int mapped_file_source::alignment()
{ return static_cast<int>(sysconf(_SC_PAGESIZE)); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //------------------------------------------//

} } // End namespaces iostreams, boost.
