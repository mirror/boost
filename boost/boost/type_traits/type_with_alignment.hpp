
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
#include "boost/preprocessor/list/transform.hpp"
#include "boost/preprocessor/list/append.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/is_pod.hpp"
#include "boost/static_assert.hpp"
#include "boost/config.hpp"

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

#include <cstddef>

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4121) // alignment is sensitive to packing
#endif

namespace boost {

#ifndef __BORLANDC__

namespace detail {

class alignment_dummy;
typedef void (*function_ptr)();
typedef int (alignment_dummy::*member_ptr);
typedef int (alignment_dummy::*member_function_ptr)();

#define BOOST_TT_ALIGNMENT_BASE_TYPES BOOST_PP_TUPLE_TO_LIST( \
        11, ( \
        char, short, int, long, float, double, long double \
        , void*, function_ptr, member_ptr, member_function_ptr))

#define BOOST_TT_HAS_ONE_T(D,Data,T) boost::detail::has_one_T<T>

#define BOOST_TT_ALIGNMENT_STRUCT_TYPES                         \
        BOOST_PP_LIST_TRANSFORM(BOOST_TT_HAS_ONE_T,             \
                                X,                              \
                                BOOST_TT_ALIGNMENT_BASE_TYPES)

#define BOOST_TT_ALIGNMENT_TYPES                                \
        BOOST_PP_LIST_APPEND(BOOST_TT_ALIGNMENT_BASE_TYPES,     \
                             BOOST_TT_ALIGNMENT_STRUCT_TYPES)

#define BOOST_TT_CHOOSE_MIN_ALIGNMENT(R,P,I,T)                                 \
        typename mpl::if_c<                                                    \
           (alignment_of< T >::value == target && !BOOST_PP_CAT(found,I)),     \
           T, char>::type BOOST_PP_CAT(t,I);                                   \
        enum { BOOST_PP_CAT(found,BOOST_PP_INC(I)) =                           \
               alignment_of< T >::value == target || BOOST_PP_CAT(found,I) } ;

#define BOOST_TT_CHOOSE_T(R,P,I,T) T BOOST_PP_CAT(t,I);

template <typename T>
struct has_one_T
{
  T data;
};

template <std::size_t target>
union lower_alignment
{
    enum { found0 = false };

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

#undef BOOST_TT_ALIGNMENT_BASE_TYPES
#undef BOOST_TT_HAS_ONE_T
#undef BOOST_TT_ALIGNMENT_STRUCT_TYPES
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

BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::max_align,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<1> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<2> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<4> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<8> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<10> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<16> ,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::detail::lower_alignment<32> ,true)

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

#if !(defined(__APPLE__) && defined(__MACH__) && defined(__GNUC__))
    BOOST_STATIC_ASSERT(found >= Align);
    BOOST_STATIC_ASSERT(found % Align == 0);
#endif

 public:
    typedef align_t type;
};

#else

//
// Borland specific version, we have this for two reasons:
// 1) The version above doesn't always compile (with the new test cases for example)
// 2) Because of Borlands #pragma option we can create types with alignments that are
//    greater that the largest aligned builtin type.

namespace align{
#pragma option push -a16
struct a2{ short s; };
struct a4{ int s; };
struct a8{ double s; };
struct a16{ long double s; };
#pragma option pop
}

namespace detail {

typedef ::boost::align::a16 max_align;

BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::align::a2,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::align::a4,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::align::a8,true)
BOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(is_pod,::boost::align::a16,true)
}

template <std::size_t N> struct type_with_alignment
{
   // We should never get to here, but if we do use the maximally
   // aligned type:
   // BOOST_STATIC_ASSERT(0);
   typedef align::a16 type;
};
template <> struct type_with_alignment<1>{ typedef char type; };
template <> struct type_with_alignment<2>{ typedef align::a2 type; };
template <> struct type_with_alignment<4>{ typedef align::a4 type; };
template <> struct type_with_alignment<8>{ typedef align::a8 type; };
template <> struct type_with_alignment<16>{ typedef align::a16 type; };

#endif

} // namespace boost

#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_TYPE_WITH_ALIGNMENT_INCLUDED


