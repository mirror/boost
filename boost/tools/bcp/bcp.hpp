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

#include <boost/shared_ptr.hpp>

class bcp_application;
typedef boost::shared_ptr<bcp_application> pbcp_application;

class bcp_application
{
public:
   virtual ~bcp_application();

   virtual void enable_list_mode() = 0;
   virtual void enable_cvs_mode() = 0;
   virtual void enable_unix_lines() = 0;
   virtual void enable_scan_mode() = 0;
   virtual void enable_licence_mode() = 0;
   virtual void set_boost_path(const char* p) = 0;
   virtual void set_destination(const char* p) = 0;
   virtual void add_module(const char* p) = 0;

   virtual int run() = 0;

   static pbcp_application create();
};


