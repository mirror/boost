// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python.hpp>
#include <iostream>
#include "simple.hpp"

int add(int x, int y, int z, int u)
{   
    return x + y + z + u;
}

void print(int value, char const* name, float scale)
{
    std::cout << "value = " << value << "\n";
    std::cout << "name = " << name << "\n";
    std::cout << "scale = " << scale << "\n";
}

BOOST_PYTHON_MODULE(parameter)
{
    def("add", boost::parameter::python::make_function<add_meta>());
    def("echo", boost::parameter::python::make_function<print_meta>());
}

