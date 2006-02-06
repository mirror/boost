// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/preprocessor.hpp>
#include <boost/parameter/keyword.hpp>
#include "basics.hpp"

namespace test {

BOOST_PARAMETER_FUNCTION((int), f, tag,
    (required
      (tester, *)
      (name, *)
    )
    (optional
      (value, *)
      (index, *)
    )
)
{
    args[tester](
        args[name]
      , args[value | 1.f]
      , args[index | 2]
    );

    return 1;
}

struct base
{
    template <class Args>
    base(Args const& args)
    {
        args[tester](
            args[name]
          , args[value | 1.f]
          , args[index | 2]
        );
    }
};

struct class_ : base
{
    BOOST_PARAMETER_CONSTRUCTOR(class_, (base), tag,
        (required
          (tester, *)
          (name, *)
        )
        (optional
          (value, *)
          (index, *)
        )
    )

    BOOST_PARAMETER_MEMBER_FUNCTION((int), f, tag,
        (required
          (tester, *)
          (name, *)
        )
        (optional
          (value, *)
          (index, *)
        )
    )
    {
        args[tester](
            args[name]
          , args[value | 1.f]
          , args[index | 2]
        );

        return 1;
    }

    BOOST_PARAMETER_CONST_MEMBER_FUNCTION((int), f, tag,
        (required
          (tester, *)
          (name, *)
        )
        (optional
          (value, *)
          (index, *)
        )
    )
    {
        args[tester](
            args[name]
          , args[value | 1.f]
          , args[index | 2]
        );

        return 1;
    }
};

}

int main()
{
    using namespace test;

    f(
        tester = values(S("foo"), 1.f, 2)
      , S("foo")
    );

    f(
        tester = values(S("foo"), 1.f, 2)
      , name = S("foo")
    );

    class_ x(
        tester = values(S("foo"), 1.f, 2)
      , S("foo"), test::index = 2
    );

    x.f(
        tester = values(S("foo"), 1.f, 2)
      , S("foo")
    );

    x.f(
        tester = values(S("foo"), 1.f, 2)
      , name = S("foo")
    );

    class_ const& x_const = x;

    x_const.f(
        tester = values(S("foo"), 1.f, 2)
      , S("foo")
    );

    x_const.f(
        tester = values(S("foo"), 1.f, 2)
      , name = S("foo")
    );
}

