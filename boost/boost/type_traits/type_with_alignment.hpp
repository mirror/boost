
// (C) Copyright John Maddock 2000.
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. This 
// software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

#ifndef BOOST_TT_TYPE_WITH_ALIGNMENT_INCLUDED
#define BOOST_TT_TYPE_WITH_ALIGNMENT_INCLUDED

#include "boost/mpl/if.hpp"
#include "boost/preprocessor/list/for_each_i.hpp"
#include "boost/preprocessor/tuple/to_list.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/static_assert.hpp"
#include "boost/config.hpp"

#include <cstddef>

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4121) // alignment is sensitive to packing
#endif

namespace boost {

namespace detail {

class alignment_dummy;
typedef void (*function_ptr)();
typedef int (alignment_dummy::*member_ptr);
typedef int (alignment_dummy::*member_function_ptr)();

#define BOOST_TT_ALIGNMENT_TYPES BOOST_PP_TUPLE_TO_LIST( \
        11, ( \
        char, short, int, long, float, double, long double \
        , void*, function_ptr, member_ptr, member_function_ptr))

#define BOOST_TT_CHOOSE_MIN_ALIGNMENT(R,P,I,T) \
        typename mpl::if_c< \
           alignment_of<T>::value <= target, T, char>::type BOOST_PP_CAT(t,I);

#define BOOST_TT_CHOOSE_T(R,P,I,T) T BOOST_PP_CAT(t,I);
           
template <std::size_t target>
union lower_alignment
{
    BOOST_PP_LIST_FOR_EACH_I(
          BOOST_TT_CHOOSE_MIN_ALIGNMENT
        , ignored
        , BOOST_TT_ALIGNMENT_TYPES
        )
};

union max_align
{
    BOOST_PP_LIST_FOR_EACH_I(
          BOOST_TT_CHOOSE_T
        , ignored
        , BOOST_TT_ALIGNMENT_TYPES
        )
};

#undef BOOST_TT_ALIGNMENT_TYPES
#undef BOOST_TT_CHOOSE_MIN_ALIGNMENT
#undef BOOST_TT_CHOOSE_T

template<int TAlign, int Align>
struct is_aligned
{
    BOOST_STATIC_CONSTANT(bool,
        value = (TAlign >= Align) & (TAlign % Align == 0)
        );
};

} // namespace detail

// This alignment method originally due to Brian Parker, implemented by David
// Abrahams, and then ported here by Doug Gregor. 
template <int Align>
class type_with_alignment
{
    typedef detail::lower_alignment<Align> t1;
    typedef typename mpl::if_c<
          ::boost::detail::is_aligned< ::boost::alignment_of<t1>::value,Align >::value
        , t1
        , detail::max_align
        >::type align_t;

    BOOST_STATIC_CONSTANT(std::size_t, found = alignment_of<align_t>::value);

    BOOST_STATIC_ASSERT(found >= Align);
    BOOST_STATIC_ASSERT(found % Align == 0);

 public:
    typedef align_t type;
};

} // namespace boost

#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif

#endif // BOOST_TT_TYPE_WITH_ALIGNMENT_INCLUDED
