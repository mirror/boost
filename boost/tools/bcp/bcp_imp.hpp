/*
 *
 * Copyright (c) 2003
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */

#include "bcp.hpp"
#include <string>
#include <cstring>
#include <list>
#include <set>
#include <map>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

//
//path operations:
//
int compare_paths(const fs::path& a, const fs::path& b);
inline bool equal_paths(const fs::path& a, const fs::path& b)
{ return compare_paths(a, b) == 0; }

struct path_less
{
   bool operator()(const fs::path& a, const fs::path& b)const
   { return compare_paths(a, b) < 0; }
};

class bcp_implementation
   : public bcp_application
{
public:
   bcp_implementation();
   ~bcp_implementation();
private:
   //
   // the following are the overridden virtuals from the base class:
   //
   void enable_list_mode();
   void enable_cvs_mode();
   void enable_unix_lines();
   void enable_scan_mode();
   void set_boost_path(const char* p);
   void set_destination(const char* p);
   void add_module(const char* p);

   virtual int run();
private:
   // internal helper functions:
   void scan_cvs_path(const fs::path& p);
   void add_path(const fs::path& p);
   void add_directory(const fs::path& p);
   void add_file(const fs::path& p);
   void copy_path(const fs::path& p);
   void add_file_dependencies(const fs::path& p, bool scanfile);
   bool is_source_file(const fs::path& p);
   bool is_html_file(const fs::path& p);
   bool is_binary_file(const fs::path& p);
   void add_dependent_lib(const std::string& libname);
   void create_path(const fs::path& p);

   std::list<std::string> m_module_list; // the modules to process
   bool m_list_mode;                     // list files only
   bool m_cvs_mode;                      // check cvs for files
   bool m_unix_lines;                    // fix line endings
   bool m_scan_mode;                     // scan non-boost files.
   fs::path m_boost_path;                // the path to the boost root
   fs::path m_dest_path;                 // the path to copy to
   std::map<fs::path, bool, path_less> m_cvs_paths;    // valid files under cvs control
   std::set<fs::path, path_less> m_copy_paths;         // list of files to copy
};
