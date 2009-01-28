
#line 1670 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>
#line 1660 "../../../../libs/parameter/doc/index.rst"
BOOST_PARAMETER_NAME((pass_foo, keywords) foo)

BOOST_PARAMETER_FUNCTION(
  (int), f,
  keywords, (required (foo, *)))
{
    return foo + 1;
}

int x = f(pass_foo = 41);
#line 1671 "../../../../libs/parameter/doc/index.rst"
int main()
{}

