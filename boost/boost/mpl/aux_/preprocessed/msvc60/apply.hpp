// preprocessed version of 'boost/mpl/apply.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

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

// workaround for the ETI bug
template<>
struct apply0<int>
{
    typedef apply0 type;
};

namespace aux {

template< typename F>
struct msvc_apply1
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1 > struct apply
        {
        };
    };

    template< typename T1 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<T1>
    {
    };
};

} // namespace aux

template<
      typename F, typename T1
    >
struct apply1
    : aux::msvc_apply1<F>::template result_<
          T1
        >
{
};

// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef apply1 type;
};

template<>
struct apply1< arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1
        >
    struct apply
        : aux::msvc_apply1<F>::template result_<
              T1
            >
    {
    };
};

namespace aux {

template< typename F>
struct msvc_apply2
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2 > struct apply
        {
        };
    };

    template< typename T1, typename T2 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2 >
    {
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2
    >
struct apply2
    : aux::msvc_apply2<F>::template result_<
          T1, T2
        >
{
};

// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef apply2 type;
};

template<>
struct apply2< arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2
        >
    struct apply
        : aux::msvc_apply2<F>::template result_<
              T1, T2
            >
    {
    };
};

namespace aux {

template< typename F>
struct msvc_apply3
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2, typename P3 > struct apply
        {
        };
    };

    template< typename T1, typename T2, typename T3 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3 >
    {
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3
    : aux::msvc_apply3<F>::template result_<
          T1, T2, T3
        >
{
};

// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef apply3 type;
};

template<>
struct apply3< arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3
        >
    struct apply
        : aux::msvc_apply3<F>::template result_<
              T1, T2, T3
            >
    {
    };
};

namespace aux {

template< typename F>
struct msvc_apply4
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            >
        struct apply
        {
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4 >
    {
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4
    : aux::msvc_apply4<F>::template result_<
          T1, T2, T3, T4
        >
{
};

// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef apply4 type;
};

template<>
struct apply4< arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        >
    struct apply
        : aux::msvc_apply4<F>::template result_<
              T1, T2, T3, T4
            >
    {
    };
};

namespace aux {

template< typename F>
struct msvc_apply5
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            , typename P5
            >
        struct apply
        {
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4,T5 >
    {
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5
    : aux::msvc_apply5<F>::template result_<
          T1, T2, T3, T4, T5
        >
{
};

// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef apply5 type;
};

template<>
struct apply5< arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1>,arg<-1> >
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct apply
        : aux::msvc_apply5<F>::template result_<
              T1, T2, T3, T4, T5
            >
    {
    };
};

} // namespace mpl
} // namespace boost

