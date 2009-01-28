
#line 2069 "../../../../libs/parameter/doc/index.rst"
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
#line 2080 "../../../../libs/parameter/doc/index.rst"
using lib::_name;
using lib::_index;

int x = lib::f(_name = "jill", _index = 1);
#line 2089 "../../../../libs/parameter/doc/index.rst"
int main() {}

