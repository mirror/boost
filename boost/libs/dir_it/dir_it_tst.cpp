// -*-C++-*- dir_it_tst.cpp
// <!!----------------------------------------------------------------------> 
// <!! Copyright (C) 1998 Dietmar Kuehl, Claas Solutions GmbH > 
// <!!> 
// <!! Permission to use, copy, modify, distribute and sell this > 
// <!! software for any purpose is hereby granted without fee, provided > 
// <!! that the above copyright notice appears in all copies and that > 
// <!! both that copyright notice and this permission notice appear in > 
// <!! supporting documentation. Dietmar Kuehl and Claas Solutions make no > 
// <!! representations about the suitability of this software for any > 
// <!! purpose. It is provided "as is" without express or implied warranty. > 
// <!!----------------------------------------------------------------------> 

// Author: Dietmar Kuehl dietmar.kuehl@claas-solutions.de 
// Title:  A simple test for the class 'dir_it'

// -------------------------------------------------------------------------- 

#include "boost/directory.h"
#include <iostream>
#include <algorithm>

// -------------------------------------------------------------------------- 

int main()
{
	using namespace boost::filesystem;

  for (dir_it it("./"); it != dir_it(); ++it)
		if (!get<is_hidden>(it))
			{
				std::cout << (get<is_directory>(it)? 'd': '-');
				std::cout << (get<user_read>(it)? 'r': '-');
				std::cout << (get<user_write>(it)? 'w': '-');
				std::cout << (get<user_execute>(it)? 'x': '-');
				
				std::cout.width(8);
				std::cout << get<size>(it) << ' ';
				
				char buf[128];
				buf[strftime(buf, sizeof(buf) - 1, "%b %d %H:%M", localtime(get<mtime>(it)))] = 0;
				std::cout << buf << ' ';
				
				std::cout << *it << "\n";
			}
}
