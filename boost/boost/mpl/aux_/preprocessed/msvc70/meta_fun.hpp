// preprocessed version of 'boost/mpl/meta_fun.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

template<
      template< typename P1 > class F
    >
struct meta_fun1
{
    template< typename U1 > struct apply
        : F<U1>
    {
    };
};

template<
      template< typename P1, typename P2 > class F
    >
struct meta_fun2
{
    template< typename U1, typename U2 > struct apply
        : F< U1,U2 >
    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    >
struct meta_fun3
{
    template< typename U1, typename U2, typename U3 > struct apply
        : F< U1,U2,U3 >
    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    >
struct meta_fun4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply
        : F< U1,U2,U3,U4 >
    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    >
struct meta_fun5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply
        : F< U1,U2,U3,U4,U5 >
    {
    };
};

} // namespace mpl
} // namespace boost

