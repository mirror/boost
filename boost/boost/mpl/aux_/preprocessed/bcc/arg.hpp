// preprocessed version of 'boost/mpl/arg.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

template<> struct arg<-1>
{
    BOOST_STATIC_CONSTANT(int, value = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U2 type;
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U3 type;
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U4 type;
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U5 type;
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1, int, arg)

} // namespace mpl
} // namespace boost

