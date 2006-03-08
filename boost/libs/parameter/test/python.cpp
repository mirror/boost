// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/preprocessor.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/python.hpp>
#include <boost/python.hpp>

namespace test {

BOOST_PARAMETER_KEYWORD(tag, x)
BOOST_PARAMETER_KEYWORD(tag, y)
BOOST_PARAMETER_KEYWORD(tag, z)

struct X
{
    BOOST_PARAMETER_MEMBER_FUNCTION((int), f, tag,
        (required
         (x, *)
         (y, *)
        )
        (optional
         (z, *)
        )
    )
    {
        return args[x] + args[y] + args[z | 0];
    }

    BOOST_PARAMETER_MEMBER_FUNCTION((std::string), g, tag,
        (optional
         (x, *)
         (y, *)
        )
    )
    {
        return std::string(args[x | "foo"]) + args[y | "bar"];
    }
};

} // namespace test

struct f_fwd
{
    template <class R, class T, class A0, class A1, class A2>
    R operator()(boost::type<R>, T& self, A0 const& a0, A1 const& a1, A2 const& a2)
    {
        return self.f(a0,a1,a2);
    }
};

struct g_fwd
{
    template <class R, class T, class A0, class A1>
    R operator()(boost::type<R>, T& self, A0 const& a0, A1 const& a1)
    {
        return self.g(a0,a1);
    }
};

BOOST_PYTHON_MODULE(python_parameter)
{
    namespace mpl = boost::mpl;
    using namespace test;
    using namespace boost::python;

    class_<X>("X")
        .def(
            "f"
          , boost::parameter::python::function<
                f_fwd
              , mpl::vector3<tag::x, tag::y, tag::z*>
              , mpl::vector4<int, int, int, int>
            >()
        )
        .def(
            "g"
          , boost::parameter::python::function<
                g_fwd
              , mpl::vector2<tag::x*, tag::y*>
              , mpl::vector3<std::string, std::string, std::string>
            >()
        );
}

