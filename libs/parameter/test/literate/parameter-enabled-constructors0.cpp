
#line 1215 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>
#include <iostream>
#line 1201 "../../../../libs/parameter/doc/index.rst"
BOOST_PARAMETER_NAME(name)
BOOST_PARAMETER_NAME(index)

struct myclass_impl
{
    template <class ArgumentPack>
    myclass_impl(ArgumentPack const& args)
    {
        std::cout << "name = " << args[_name]
                  << "; index = " << args[_index | 42]
                  << std::endl;
    }
};

#line 1228 "../../../../libs/parameter/doc/index.rst"
struct myclass : myclass_impl
{
    BOOST_PARAMETER_CONSTRUCTOR(
        myclass, (myclass_impl), tag
      , (required (name,*)) (optional (index,*))) // no semicolon
};


#line 1242 "../../../../libs/parameter/doc/index.rst"
int main() {
#line 1239 "../../../../libs/parameter/doc/index.rst"
myclass x("bob", 3);                     // positional
myclass y(_index = 12, _name = "sally"); // named
myclass z("june");                       // positional/defaulted
#line 1242 "../../../../libs/parameter/doc/index.rst"
}

