// preprocessed version of 'boost/mpl/apply.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template< int > struct apply_impl_chooser;
}

template< typename F >
struct apply0 : F
{
};

template<>
struct apply0< arg<-1> >
{
    template< typename F > struct apply
        : F
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<0>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply0<
              F  
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1
    >
struct apply1
    : F::template apply<
          T1
        >
{
};

template<>
struct apply1< arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1
        >
    struct apply
        : F::template apply<
              T1
            >
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<1>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply1<
              F, T1
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2
    >
struct apply2
    : F::template apply<
          T1, T2
        >
{
};

template<>
struct apply2< arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2
        >
    struct apply
        : F::template apply<
              T1, T2
            >
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<2>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply2<
              F, T1, T2
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3
    : F::template apply<
          T1, T2, T3
        >
{
};

template<>
struct apply3< arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3
        >
    struct apply
        : F::template apply<
              T1, T2, T3
            >
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<3>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply3<
              F, T1, T2, T3
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4
    : F::template apply<
          T1, T2, T3, T4
        >
{
};

template<>
struct apply4< arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        >
    struct apply
        : F::template apply<
              T1, T2, T3, T4
            >
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<4>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply4<
              F, T1, T2, T3, T4
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5
    : F::template apply<
          T1, T2, T3, T4, T5
        >
{
};

template<>
struct apply5< arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct apply
        : F::template apply<
              T1, T2, T3, T4, T5
            >
    {
    };
};

namespace aux {

template<>
struct apply_impl_chooser<5>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply5<
              F, T1, T2, T3, T4, T5
            > type;
    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_apply_arg
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<>
struct is_apply_arg<void_>
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct apply_count_args
{
    BOOST_STATIC_CONSTANT(int, value = is_apply_arg<T1>::value + is_apply_arg<T2>::value + is_apply_arg<T3>::value + is_apply_arg<T4>::value + is_apply_arg<T5>::value);
};

} // namespace aux

template<
      typename F, typename T1 = void_, typename T2 = void_
    , typename T3 = void_, typename T4 = void_, typename T5 = void_
    >
struct apply
    : aux::apply_impl_chooser< 
          aux::apply_count_args< T1,T2,T3,T4,T5 >::value
        >::template result_< F,T1,T2,T3,T4,T5 >::type
{
};

} // namespace mpl
} // namespace boost

