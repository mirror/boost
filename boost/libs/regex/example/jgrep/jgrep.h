/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   FILE     jgrep.h
  *   VERSION  see <boost/version.hpp>
  */

#ifndef _JGREP_H
#define _JGREP_H

#include <boost/regex.hpp>

typedef boost::basic_regex<char> re_type;
extern re_type e;

// flags for output:

extern bool use_case;
extern bool show_lines;
extern bool count_only;
extern bool files_only;
extern bool recurse;
extern bool regularexs;
extern bool words_only;
extern bool verbose;

void process_grep(const char* file);

#endif




