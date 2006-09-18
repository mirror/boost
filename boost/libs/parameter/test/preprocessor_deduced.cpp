// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/preprocessor.hpp>
#include <boost/parameter/name.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>
#include "basics.hpp"

namespace test {

namespace mpl = boost::mpl;

using mpl::_;
using boost::is_convertible;

BOOST_PARAMETER_NAME(expected)
BOOST_PARAMETER_NAME(x)
BOOST_PARAMETER_NAME(y)
BOOST_PARAMETER_NAME(z)

BOOST_PARAMETER_FUNCTION((int), f, tag,
    (required
       (expected, *)
    )
    (deduced
       (required
          (x, *(is_convertible<_, int>))
          (y, *(is_convertible<_, std::string>))
       )
    )
)
{
    assert(equal(x, boost::tuples::get<0>(expected)));
    assert(equal(y, boost::tuples::get<1>(expected)));
    return 1;
}

struct X 
{
    X(int x = -1)
      : x(x)
    {}
    
    bool operator==(X const& other) const
    {
        return x == other.x;
    }
    
    int x;
};

BOOST_PARAMETER_FUNCTION((int), g, tag,
    (required
      (expected, *)
    )
    (deduced
       (required
          (x, *(is_convertible<_, int>))
          (y, *(is_convertible<_, std::string>))
       )
       (optional
          (z, *(is_convertible<_, X>), X())
       )
    )
)
{
    assert(equal(x, boost::tuples::get<0>(expected)));
    assert(equal(y, boost::tuples::get<1>(expected)));
    assert(equal(z, boost::tuples::get<2>(expected)));
    return 1;
}

} // namespace test

using boost::make_tuple;

// make_tuple doesn't work with char arrays.
char const* str(char const* s)
{
    return s;
}

int main()
{
    using namespace test;

    f(make_tuple(0, str("foo")), _x = 0, _y = "foo");
    f(make_tuple(0, str("foo")), _x = 0, _y = "foo");
    f(make_tuple(0, str("foo")), 0, "foo");
    f(make_tuple(0, str("foo")), "foo", 0);
    f(make_tuple(0, str("foo")), _y = "foo", 0);
    f(make_tuple(0, str("foo")), _x = 0, "foo");
    f(make_tuple(0, str("foo")), 0, _y = "foo");

    g(make_tuple(0, str("foo"), X()), _x = 0, _y = "foo");
    g(make_tuple(0, str("foo"), X()), 0, "foo");
    g(make_tuple(0, str("foo"), X()), "foo", 0);
    g(make_tuple(0, str("foo"), X()), _y = "foo", 0);   
    g(make_tuple(0, str("foo"), X()), _x = 0, "foo");
    g(make_tuple(0, str("foo"), X()), 0, _y = "foo");

    g(make_tuple(0, str("foo"), X(1)), 0, _y = "foo", X(1));
    g(make_tuple(0, str("foo"), X(1)), X(1), 0, _y = "foo");

    return 0;
}

