// preprocessed version of 'boost/mpl/aux_/advance_backward.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {
namespace aux {

#if !defined(PRIOR)
#   define PRIOR(x) x::prior
#endif

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename PRIOR(iter0) iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename PRIOR(iter0) iter1;
        typedef typename PRIOR(iter1) iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename PRIOR(iter0) iter1;
        typedef typename PRIOR(iter1) iter2;
        typedef typename PRIOR(iter2) iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename PRIOR(iter0) iter1;
        typedef typename PRIOR(iter1) iter2;
        typedef typename PRIOR(iter2) iter3;
        typedef typename PRIOR(iter3) iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename advance_backward<4>::template apply<Iterator>::type chunk_result_;
        typedef typename advance_backward<( (N - 4) < 0 ? 0 : N - 4 )>::template apply<chunk_result_>::type type;
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

