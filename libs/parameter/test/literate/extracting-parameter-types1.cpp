
#line 1830 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <cassert>

namespace parameter = boost::parameter;
#line 1819 "../../../../libs/parameter/doc/index.rst"
BOOST_PARAMETER_NAME(index)

template <class ArgumentPack>
typename parameter::value_type<ArgumentPack, tag::index, int>::type
twice_index(ArgumentPack const& args)
{
    return 2 * args[_index|42];
}

int six = twice_index(_index = 3);
#line 1838 "../../../../libs/parameter/doc/index.rst"
int main()
{
    assert(six == 6);
}

