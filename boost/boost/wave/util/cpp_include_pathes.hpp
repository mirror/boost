/*=============================================================================
    Wave: A Standard compliant C++ preprocessor library

    http://spirit.sourceforge.net/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(CPP_INCLUDE_PATHES_HPP_AF620DA4_B3D2_4221_AD91_8A1ABFFB6944_INCLUDED)
#define CPP_INCLUDE_PATHES_HPP_AF620DA4_B3D2_4221_AD91_8A1ABFFB6944_INCLUDED

#include <string>
#include <list>
#include <set>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/wave/wave_config.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace util {

///////////////////////////////////////////////////////////////////////////////
//
//  include_pathes - controlling the include path search order
//
//  General notes:
//
//      Any directories specified with the 'add_include_path()' function before 
//      the function 'set_sys_include_delimiter()' is called are searched only 
//      for the case of '#include "file"' directives, they are not searched for 
//      '#include <file>' directives. If additional directories are specified 
//      with the 'add_include_path()' function after a call to the function 
//      'set_sys_include_delimiter()', these directories are searched for all 
//      '#include' directives. 
//
//      In addition, a call to the function 'set_sys_include_delimiter()' 
//      inhibits the use of the current directory as the first search directory 
//      for '#include "file"' directives. Therefore, the current directory is 
//      searched only if it is requested explicitly with a call to the function
//      'add_include_path(".")'. 
//
//      Calling both functions, the 'set_sys_include_delimiter()' and 
//      'add_include_path(".")' allows you to control precisely which 
//      directories are searched before the current one and which are searched 
//      after.
//
///////////////////////////////////////////////////////////////////////////////
class include_pathes
{
    typedef std::list<boost::filesystem::path> include_list_t;
    typedef std::set<std::string> pragma_once_set_t;
    
public:
    include_pathes()
    :   was_sys_include_path(false),
        current_dir(boost::filesystem::initial_path())
    {}
    
    bool add_include_path(char const *path_, bool is_system = false)
    {
        return add_include_path(path_, (is_system || was_sys_include_path) ? 
            system_include_pathes : user_include_pathes);
    }
    void set_sys_include_delimiter() { was_sys_include_path = true; }
    bool find_include_file (std::string &s, bool is_system, 
        char const *current_file) const;
    void set_current_directory(char const *path_);

    void init_initial_path() { boost::filesystem::initial_path(); }
    
protected:
    bool find_include_file (std::string &s, include_list_t const &pathes,
        char const *) const;
    bool add_include_path(char const *path_, include_list_t &pathes_);

private:
    include_list_t user_include_pathes;
    include_list_t system_include_pathes;
    bool was_sys_include_path;          // saw a set_sys_include_delimiter()
    boost::filesystem::path current_dir;

#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
public:
    bool has_pragma_once(std::string const &filename)
    {
        return pragma_once_files.find(filename) != pragma_once_files.end();
    }
    bool add_pragma_once_header(std::string const &filename)
    {
        return pragma_once_files.insert(filename).second;
    }

private:
    pragma_once_set_t pragma_once_files;
#endif
};

///////////////////////////////////////////////////////////////////////////////
//  Add an include path to one of the search lists (user include path or system 
//  include path).
inline
bool include_pathes::add_include_path (
    char const *path_, include_list_t &pathes_)
{
    namespace fs = boost::filesystem;
    if (path_) {
    fs::path newpath = fs::complete(fs::path(path_, fs::native), current_dir);

        if (!fs::exists(newpath) || !fs::is_directory(newpath)) {
        // the given path does not form a name of a valid file system directory
        // item
            return false;
        }

        pathes_.push_back (newpath);
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//  Find an include file by traversing the list of include directories
inline
bool include_pathes::find_include_file (std::string &s, 
    include_list_t const &pathes, char const *current_file) const
{
    namespace fs = boost::filesystem;
    typedef include_list_t::const_iterator const_include_list_iter_t;

    const_include_list_iter_t it = pathes.begin();
    const_include_list_iter_t include_pathes_end = pathes.end();

#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0    
    if (0 != current_file) {
    // re-locate the directory of the current file (#include_next handling)

    // #include_next does not distinguish between <file> and "file"
    // inclusion, nor does it check that the file you specify has the same
    // name as the current file.  It simply looks for the file named, starting
    // with the directory in the search path after the one where the current
    // file was found.

        for (/**/; it != include_pathes_end; ++it) {
            fs::path currpath ((*it).string(), fs::native);
            fs::path file_path (current_file, fs::native);
	          if (std::equal(currpath.begin(), currpath.end(), file_path.begin())) 
	          {
                ++it;     // start searching with the next directory
                break;
            }
        }
    }
#endif

    for (/**/; it != include_pathes_end; ++it) {
        fs::path currpath ((*it).string(), fs::native);
        currpath /= fs::path(s, fs::native);      // append filename

        if (fs::exists(currpath)) {
            s = currpath.string();                // found the required file
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//  Find an include file by searching the user and system includes in the 
//  correct sequence (as it was configured by the user of the driver program)
inline bool 
include_pathes::find_include_file (std::string &s, bool is_system, 
    char const *current_file) const
{
    namespace fs = boost::filesystem;
    
// if not system include (<...>), then search current directory first
    if (!is_system) {
        if (!was_sys_include_path) {  // set_sys_include_delimiter() not called
        // first look in the current directory
            fs::path currpath (current_dir.string(), fs::native);
            currpath /= fs::path(s, fs::native);
            
            if (fs::exists(currpath) && 0 == current_file) {
            // if 0 != current_path (#include_next handling) it can't be
            // the file in the current directory
                s = currpath.string();    // found in local directory
                return true;
            }   

        // iterate all user include file directories to find the file
            if (0 == current_file)
                return find_include_file(s, user_include_pathes, 0);

        // #include_next doesn't distinguish between <file> and "file"
        // ... fall through
        }

    // iterate all user include file directories to find the file
        if (find_include_file(s, user_include_pathes, current_file))
            return true;

    // if nothing found, fall through
    // ...
    }

// iterate all system include file directories to find the file
    return find_include_file (s, system_include_pathes, current_file);
}

///////////////////////////////////////////////////////////////////////////////
//  Set current directory from a given file name

inline
void include_pathes::set_current_directory(char const *path_)
{
    namespace fs = boost::filesystem;
    
    fs::path filename = fs::complete(fs::path(path_, fs::native), current_dir);
    if (fs::exists(filename) && fs::is_directory(filename)) 
        current_dir = filename;
    else
        current_dir = filename.branch_path();
}

///////////////////////////////////////////////////////////////////////////////
}   // namespace util
}   // namespace wave
}   // namespace boost

#endif // !defined(CPP_INCLUDE_PATHES_HPP_AF620DA4_B3D2_4221_AD91_8A1ABFFB6944_INCLUDED)
