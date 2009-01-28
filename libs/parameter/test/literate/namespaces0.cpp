
#line 2051 "../../../../libs/parameter/doc/index.rst"
#line 2054 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>
#include <iostream>
#line 2040 "../../../../libs/parameter/doc/index.rst"
namespace lib
{
  BOOST_PARAMETER_NAME(name)
  BOOST_PARAMETER_NAME(index)

  BOOST_PARAMETER_FUNCTION(
    (int), f, tag,
    (optional (name,*,"bob")(index,(int),1))
  )
  {
      std::cout << name << ":" << index << std::endl;
      return index;
  }
}
#line 2067 "../../../../libs/parameter/doc/index.rst"
int x = lib::f(lib::_name = "jill", lib::_index = 1);
#line 2071 "../../../../libs/parameter/doc/index.rst"
int main() {}

