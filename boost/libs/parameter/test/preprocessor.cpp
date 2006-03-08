// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/preprocessor.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/type_traits/is_const.hpp>
#include <string>
#include "basics.hpp"

#ifndef BOOST_NO_SFINAE
# include <boost/utility/enable_if.hpp>
#endif

namespace test {

BOOST_PARAMETER_FUNCTION((int), f, tag,
    (required
      (tester, *)
      (name, *)
    )
    (optional
      (value, *)
      (out(index), (int))
    )
)
{
    typedef typename boost::parameter::binding<
        Args, tag::index, int&
    >::type index_type;

    BOOST_MPL_ASSERT((boost::is_same<index_type, int&>));

    args[tester](
        args[name]
      , args[value | 1.f]
      , args[index | 2]
    );

    return 1;
}

BOOST_PARAMETER_FUNCTION((int), g, tag,
    (required
      (tester, *)
      (name, *)
    )
    (optional
      (value, *)
      (out(index), (int))
    )
)
{
    typedef typename boost::parameter::binding<
        Args, tag::index, int const&
    >::type index_type;

    BOOST_MPL_ASSERT((boost::is_same<index_type, int const&>));

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

BOOST_PARAMETER_FUNCTION(
    (int), sfinae, tag,
    (required
       (name, (std::string))
    )
)
{
    return 1;
}

#ifndef BOOST_NO_SFINAE
// On compilers that actually support SFINAE, add another overload
// that is an equally good match and can only be in the overload set
// when the others are not.  This tests that the SFINAE is actually
// working.  On all other compilers we're just checking that
// everything about SFINAE-enabled code will work, except of course
// the SFINAE.
template<class A0>
typename boost::enable_if<boost::is_same<int,A0>, int>::type
sfinae(A0 const& a0)
{
    return 0;
}
#endif

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

    int index_lvalue = 2;
    
    f(
        tester = values(S("foo"), 1.f, 2)
      , name = S("foo")
      , 1.f
      , index_lvalue
    );

    g(
        tester = values(S("foo"), 1.f, 2)
      , name = S("foo")
      , 1.f
      , 2
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
   
#ifndef BOOST_NO_SFINAE
    assert(sfinae("foo") == 1);
    assert(sfinae(1) == 0);
#endif
}

