
#line 2083 "../../../../libs/parameter/doc/index.rst"
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
#line 2097 "../../../../libs/parameter/doc/index.rst"
using namespace lib;
int x = f(_name = "jill", _index = 3);
#line 2103 "../../../../libs/parameter/doc/index.rst"
int main() {}

