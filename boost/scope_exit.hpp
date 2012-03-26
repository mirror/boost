
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#ifndef FILE_boost_scope_exit_hpp_INCLUDED
#define FILE_boost_scope_exit_hpp_INCLUDED

#ifndef DOXYGEN

#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/local_function/detail/preprocessor/void_list.hpp>
#include <boost/local_function/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/paren_if.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/fold_left.hpp>
#include <boost/preprocessor/list/enum.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>

// PRIVATE/PROTECTED //

// NOTE: AUX prefix and aux namespace mark "private" symbols that shall be used
// only within this library; DETAIL prefix and detail namespace mark "protected"
// symbols that can be used by other Boost libraries but not outside Boost.

// WARNING: BOOST_SCOPE_EXIT_AUX_GCC also used in regression tests.
#if defined(__GNUC__) && !defined(BOOST_INTEL)
#   define BOOST_SCOPE_EXIT_AUX_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
#else
#   define BOOST_SCOPE_EXIT_AUX_GCC 0
#endif

#if BOOST_WORKAROUND(BOOST_SCOPE_EXIT_AUX_GCC, BOOST_TESTED_AT(413))
#   define BOOST_SCOPE_EXIT_AUX_TPL_GCC_WORKAROUND_01 1
#else
#   define BOOST_SCOPE_EXIT_AUX_TPL_GCC_WORKAROUND_01 0
#endif

// MSVC 7.1=1300, 8.0=1400, 9.0=1500, 10.0=1600 (this workaround was tested at
// MSVC 8.0 but it might work also for all MVSC >= 7.1).
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
#   define BOOST_SCOPE_EXIT_AUX_TYPEOF_THIS_MSVC_WORKAROUND_01 1
#else
#   define BOOST_SCOPE_EXIT_AUX_TYPEOF_THIS_MSVC_WORKAROUND_01 0
#endif

// Steven Watanabe's trick with a modification suggested by Kim Barrett
namespace boost { namespace scope_exit { namespace detail {

// Type of a local BOOST_SCOPE_EXIT_AUX_ARGS variable.
// First use in a local scope will declare the BOOST_SCOPE_EXIT_AUX_ARGS
// variable, subsequent uses will be resolved as two comparisons
// (cmp1 with 0 and cmp2 with BOOST_SCOPE_EXIT_AUX_ARGS).
template<int Dummy = 0>
struct declared
{
    void* value;
    static int const cmp2 = 0;
    friend void operator>(int, declared const&) {}
};

struct undeclared { declared<> dummy[2]; };

template<int> struct resolve;

template<>
struct resolve<sizeof(declared<>)>
{
    static const int cmp1 = 0;
};

template<>
struct resolve<sizeof(undeclared)>
{
    template<int>
    struct cmp1
    {
        static int const cmp2 = 0;
    };
};

typedef void (*ref_tag)(int&);
typedef void (*val_tag)(int );

template<class T, class Tag> struct member;

template<class T>
struct member<T,ref_tag>
{
    T& value;
#if !BOOST_SCOPE_EXIT_AUX_TPL_GCC_WORKAROUND_01
    member(T& ref) : value(ref) {}
#endif
};

template<class T>
struct member<T,val_tag>
{
    T value;
#if !BOOST_SCOPE_EXIT_AUX_TPL_GCC_WORKAROUND_01
    member(T& val) : value(val) {}
#endif
};

template<class T> inline T& deref(T* p, ref_tag) { return *p; }
template<class T> inline T& deref(T& r, val_tag) { return  r; }

template<class T>
struct wrapper
{
    typedef T type;
};

template<class T> wrapper<T> wrap(T&);

} } } // namespace

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::scope_exit::detail::wrapper, 1)

#define BOOST_SCOPE_EXIT_AUX_ARGS boost_scope_exit_aux_args
extern boost::scope_exit::detail::undeclared BOOST_SCOPE_EXIT_AUX_ARGS;

#define BOOST_SCOPE_EXIT_AUX_GUARD(id)   \
    BOOST_PP_CAT(boost_se_guard_, id)

#define BOOST_SCOPE_EXIT_AUX_GUARD_T(id) \
    BOOST_PP_CAT(boost_se_guard_t_, id)

#define BOOST_SCOPE_EXIT_AUX_PARAMS(id)  \
    BOOST_PP_CAT(boost_se_params_, id)

#define BOOST_SCOPE_EXIT_AUX_THIS_T(id)  \
    BOOST_PP_CAT(boost_se_this_t_,  id)

#define BOOST_SCOPE_EXIT_AUX_THIS_CAPTURE_T(id) \
    BOOST_PP_CAT(boost_se_this_capture_t_,  id)

#define BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id) \
    BOOST_PP_CAT(boost_se_params_t_, id)

#define BOOST_SCOPE_EXIT_DETAIL_TAG(id, i) \
    BOOST_PP_SEQ_CAT( (boost_se_tag_)(i)(_)(id) )

#define BOOST_SCOPE_EXIT_DETAIL_PARAM_THIS(id) \
    BOOST_PP_SEQ_CAT( (boost_se_param_this_)(id) )

#define BOOST_SCOPE_EXIT_DETAIL_PARAM(id, i, var) \
    BOOST_PP_SEQ_CAT( (boost_se_param_)(i)(_)(id) )

#define BOOST_SCOPE_EXIT_DETAIL_PARAM_T(id, i, var) \
    BOOST_PP_SEQ_CAT( (boost_se_param_t_)(i)(_)(id) )

#define BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(id, i, var) \
    BOOST_PP_SEQ_CAT( (boost_se_capture_t_)(i)(_)(id) )

#define BOOST_SCOPE_EXIT_AUX_WRAPPED(id, i) \
    BOOST_PP_SEQ_CAT( (boost_se_wrapped_t_)(i)(_)(id) )

#define BOOST_SCOPE_EXIT_AUX_DEREF(id, i, var) \
    ::boost::scope_exit::detail::deref(var, \
            static_cast<BOOST_SCOPE_EXIT_DETAIL_TAG(id, i)>(0))

#define BOOST_SCOPE_EXIT_AUX_MEMBER(r, id, i, var) \
    ::boost::scope_exit::detail::member< \
        BOOST_SCOPE_EXIT_DETAIL_PARAM_T(id, i, var), \
        BOOST_SCOPE_EXIT_DETAIL_TAG(id, i) \
    > BOOST_SCOPE_EXIT_DETAIL_PARAM(id, i, var);

#define BOOST_SCOPE_EXIT_AUX_ARG_DECL(r, id_ty, i, var) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_TUPLE_ELEM(2, 1, id_ty) \
    BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty)):: \
            BOOST_SCOPE_EXIT_DETAIL_PARAM_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                    i, var) \
    var
 
#define BOOST_SCOPE_EXIT_AUX_ARG(r, id, i, var) \
    BOOST_PP_COMMA_IF(i) \
    boost_se_params_->BOOST_SCOPE_EXIT_DETAIL_PARAM(id, i, var).value

#define BOOST_SCOPE_EXIT_DETAIL_TAG_DECL(r, id, i, var) \
    typedef void (*BOOST_SCOPE_EXIT_DETAIL_TAG(id, i))(int var);

// Adam Butcher's workaround to deduce `this` type on MSVC revision < 10.
// Boost.Typeof for VC71's typeid-based workaround does not work to determine
// `this` type due to error C2355 being incorrectly reported. The typical
// avoidance strategy implemented below is to make an indirect compile-time
// constant by assigning an enum and use that as type-index-- this only works
// with the sizeof() approach and not with the typeid() approach. This does not
// work in typeof emulation mode.
#if BOOST_SCOPE_EXIT_AUX_TYPEOF_THIS_MSVC_WORKAROUND_01 && \
        !defined(BOOST_TYPEOF_EMULATION)

namespace boost { namespace scope_exit { namespace aux {
        namespace msvc_typeof_this {
    
template<int Id>
struct msvc_typeid_wrapper
{
    typedef typename boost::type_of::msvc_extract_type<boost::mpl::int_<Id>
            >::id2type id2type;
    typedef typename id2type::type type;
};

template<>
struct msvc_typeid_wrapper<4>
{
    typedef msvc_typeid_wrapper<4> type;
};

template<typename T>
struct encode_type
{
    BOOST_STATIC_CONSTANT(unsigned,
            value = boost::type_of::encode_counter<T>::count);
    typedef typename boost::type_of::msvc_register_type<T,
            boost::mpl::int_<value> >::id2type type;
    BOOST_STATIC_CONSTANT(unsigned, next = value + 1);
};

template<class T>
struct sizer
{
    typedef char(*type)[encode_type<T>::value];
};

template<typename T>
typename boost::disable_if<
      typename boost::is_function<T>::type
    , typename sizer<T>::type
>::type encode_start(T const&);

template<typename T>
typename boost::enable_if<
      typename boost::is_function<T>::type
    , typename sizer<T>::type
>::type encode_start(T&);

template<typename Organizer, typename T>
boost::type_of::msvc_register_type<T, Organizer> typeof_register_type(const T&,
        Organizer* = 0);

} } } } // namespace

#define BOOST_SCOPE_EXIT_AUX_TYPEDEF_TYPEOF_THIS_INDEX_(id) \
    BOOST_PP_CAT(boost_se_thistype_index_, id)

#define BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS(id, ty, new_type) \
    enum { \
        BOOST_SCOPE_EXIT_AUX_TYPEDEF_TYPEOF_THIS_INDEX_(id) = sizeof( \
            *::boost::scope_exit::aux::msvc_typeof_this::encode_start(this)) \
    }; \
    typedef \
        ty ::boost::scope_exit::aux::msvc_typeof_this::msvc_typeid_wrapper< \
            BOOST_SCOPE_EXIT_AUX_TYPEDEF_TYPEOF_THIS_INDEX_(id) \
        >::type \
        new_type \
    ;

#elif BOOST_SCOPE_EXIT_AUX_TYPEOF_THIS_MSVC_WORKAROUND_01 && \
        defined(BOOST_TYPEOF_EMULATION)

#define BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS(id, ty, new_type) \
    /* unfortunately, MSVC typeof(this) workaround does not work in type-of */ \
    /* emulation mode so trying to give meaningful compiler errors */ \
    BOOST_MPL_ASSERT_MSG(false, \
            ERROR_msvc_compilers_require_native_typeof_to_capture_object_this, \
            ()); \
    typedef int new_type; /* some `int` type to limit cryptic errors */

#else // TYPEOF_THIS_WORKAROUND

#define BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS(id, ty, new_type) \
    typedef /* trailing `EMPTY()` handles empty `ty` */ \
        BOOST_PP_IIF(BOOST_PP_IS_EMPTY(ty BOOST_PP_EMPTY()), \
            BOOST_TYPEOF \
        , \
            BOOST_TYPEOF_TPL \
        )(this) \
        new_type \
    ;

#endif // TYPEOF_THIS_WORKAROUND

#if BOOST_SCOPE_EXIT_AUX_TPL_GCC_WORKAROUND_01

#define BOOST_SCOPE_EXIT_AUX_PARAMS_T_CTOR(id, ty, captures, has_this) \
    /* expand to nothing */

#define BOOST_SCOPE_EXIT_DETAIL_PARAM_INIT(r, id, i, var) \
    BOOST_PP_COMMA_IF(i) { BOOST_SCOPE_EXIT_AUX_DEREF(id, i, var) }

#define BOOST_SCOPE_EXIT_AUX_PARAMS_INIT(id, captures, has_this) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_this, \
            BOOST_PP_LIST_IS_CONS(captures)), \
        = { \
    ) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_DETAIL_PARAM_INIT, id, captures) \
    BOOST_PP_COMMA_IF(BOOST_PP_BITAND(BOOST_PP_LIST_IS_CONS(captures), \
            has_this)) \
    BOOST_PP_EXPR_IIF(has_this, this) /* no extra {...} needed here */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_this, \
            BOOST_PP_LIST_IS_CONS(captures)), \
        } /* trailing `;` will be added by the caller */ \
    )

#else // TPL_WORKAROUND

#define BOOST_SCOPE_EXIT_AUX_CTOR_ARG(r, id, i, var) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM_T(id, i, var) & BOOST_PP_CAT(a, i)

#define BOOST_SCOPE_EXIT_AUX_MEMBER_INIT(r, id, i, var) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM(id, i, var) ( BOOST_PP_CAT(a, i) )

#define BOOST_SCOPE_EXIT_AUX_CTOR_ARG_THIS_NAME(id) \
    BOOST_PP_CAT(boost_se_this_arg_, id)

#define BOOST_SCOPE_EXIT_AUX_CTOR_ARG_THIS(id, ty, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    ty BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id)::BOOST_SCOPE_EXIT_AUX_THIS_T(id) \
            BOOST_SCOPE_EXIT_AUX_CTOR_ARG_THIS_NAME(id) /* ptr so no & */

#define BOOST_SCOPE_EXIT_AUX_MEMBER_THIS_INIT(id, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM_THIS(id)( \
            BOOST_SCOPE_EXIT_AUX_CTOR_ARG_THIS_NAME(id))

#define BOOST_SCOPE_EXIT_AUX_PARAMS_T_CTOR(id, ty, captures, has_this) \
    BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id)( \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_AUX_CTOR_ARG, id, captures) \
        BOOST_PP_IIF(has_this, \
            BOOST_SCOPE_EXIT_AUX_CTOR_ARG_THIS \
        , \
            BOOST_PP_TUPLE_EAT(3) \
        )(id, ty, BOOST_PP_LIST_IS_CONS(captures)) \
    ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(BOOST_PP_LIST_IS_CONS(captures), \
                has_this), \
            : \
        ) \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_AUX_MEMBER_INIT, id, \
                captures) \
        BOOST_PP_IIF(has_this, \
            BOOST_SCOPE_EXIT_AUX_MEMBER_THIS_INIT \
        , \
            BOOST_PP_TUPLE_EAT(2) \
        )(id, BOOST_PP_LIST_IS_CONS(captures)) \
    {}

#define BOOST_SCOPE_EXIT_DETAIL_PARAM_INIT(r, id, i, var) \
    BOOST_PP_COMMA_IF(i) BOOST_SCOPE_EXIT_AUX_DEREF(id,i,var)

#define BOOST_SCOPE_EXIT_AUX_PARAMS_INIT(id, captures, has_this) \
    BOOST_PP_LPAREN_IF(BOOST_PP_BITOR(has_this, \
            BOOST_PP_LIST_IS_CONS(captures))) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_DETAIL_PARAM_INIT, id, captures) \
    BOOST_PP_COMMA_IF(BOOST_PP_BITAND(BOOST_PP_LIST_IS_CONS(captures), \
            has_this)) \
    BOOST_PP_EXPR_IIF(has_this, this) \
    BOOST_PP_RPAREN_IF(BOOST_PP_BITOR(has_this, \
            BOOST_PP_LIST_IS_CONS(captures)))

#endif // TPL_WORKAROUND

#if defined(BOOST_TYPEOF_EMULATION)

#define BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(r, id_ty, i, var) \
    struct BOOST_SCOPE_EXIT_AUX_WRAPPED(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), i) \
        : BOOST_TYPEOF(::boost::scope_exit::detail::wrap( \
                BOOST_SCOPE_EXIT_AUX_DEREF(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                        i, var))) \
    {}; \
    typedef BOOST_PP_TUPLE_ELEM(2, 1,id_ty) \
        BOOST_SCOPE_EXIT_AUX_WRAPPED(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), i)::type\
        BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                i, var) \
    ;

#elif defined(BOOST_INTEL)

#define BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(r, id_ty, i, var) \
    typedef \
        BOOST_TYPEOF_KEYWORD(BOOST_SCOPE_EXIT_AUX_DEREF( \
                BOOST_PP_TUPLE_ELEM(2, 0, id_ty), i, var)) \
        BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                i, var) \
    ;

#else

#define BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(r, id_ty, i, var) \
    typedef \
        BOOST_TYPEOF(::boost::scope_exit::detail::wrap( \
                BOOST_SCOPE_EXIT_AUX_DEREF(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                        i, var))) \
        BOOST_SCOPE_EXIT_AUX_WRAPPED(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), i) \
    ; \
    typedef BOOST_PP_TUPLE_ELEM(2, 1, id_ty) \
        BOOST_SCOPE_EXIT_AUX_WRAPPED(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), i)::type\
        BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                i, var) \
    ;

#endif

#define BOOST_SCOPE_EXIT_DETAIL_PARAM_DECL(r, id_ty, i, var) \
    typedef \
        BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                i, var) \
        BOOST_SCOPE_EXIT_DETAIL_PARAM_T(BOOST_PP_TUPLE_ELEM(2, 0, id_ty), \
                i, var) \
    ;

// Traits.

#define BOOST_SCOPE_EXIT_AUX_TRAITS_OP_CAPTURE(d, captures, this01, capture) \
    (BOOST_PP_LIST_APPEND(captures, (capture, BOOST_PP_NIL)), this01)

#define BOOST_SCOPE_EXIT_AUX_TRAITS_OP_THIS(d, captures, this01, this_) \
    (captures, 1 /* has this (note, no error if multiple this_) */)

#define BOOST_SCOPE_EXIT_AUX_TRAITS_OP(d, captures_this, capture) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK(\
            capture), \
        BOOST_SCOPE_EXIT_AUX_TRAITS_OP_THIS \
    , \
        BOOST_SCOPE_EXIT_AUX_TRAITS_OP_CAPTURE \
    )(d, BOOST_PP_TUPLE_ELEM(2, 0, captures_this), \
            BOOST_PP_TUPLE_ELEM(2, 1, captures_this), capture)

// ref_val: & | =
#define BOOST_SCOPE_EXIT_AUX_TRAITS_ALL_OP(ref_val, traits) \
    ( \
        BOOST_PP_LIST_APPEND((ref_val, BOOST_PP_NIL), \
                BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
    , \
        BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits) \
    )

#define BOOST_SCOPE_EXIT_AUX_TRAITS(captures) \
    BOOST_PP_LIST_FOLD_LEFT(BOOST_SCOPE_EXIT_AUX_TRAITS_OP, \
            (BOOST_PP_NIL, 0), captures)

#define BOOST_SCOPE_EXIT_AUX_TRAITS_ALL(captures) \
    BOOST_SCOPE_EXIT_AUX_TRAITS_ALL_OP(BOOST_PP_LIST_FIRST(captures), \
            BOOST_SCOPE_EXIT_AUX_TRAITS(BOOST_PP_LIST_REST(captures)))

#define BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, traits)

#define BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, traits)

#ifndef BOOST_NO_LAMBDAS

namespace boost { namespace scope_exit { namespace aux {

template<typename This = void>
struct guard { // With object `this_` (for backward compatibility).
    explicit guard(This _this) : this_(_this) {}
    ~guard() { if(f_) f_(this_); }
    template<typename Lambda>
    void operator=(Lambda f) { f_ = f; }
private:
    This this_;
    boost::function<void (This)> f_;
};

template<>
struct guard<void> { // Without object `this_` (could capture `this` directly).
    ~guard() { if(f_) f_(); }
    template<typename Lambda>
    void operator=(Lambda f) { f_ = f; }
private:
    boost::function<void (void)> f_;
};

} } } // namespace
    
#define BOOST_SCOPE_EXIT_AUX_LAMBDA_PARAMS(id) \
    BOOST_PP_CAT(boost_se_lambda_params_, id)

#define BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_CAPTURE_TYPE(id) \
    BOOST_PP_CAT(boost_se_lambda_this_t_, id)

#define BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_PARAM_TYPE(id) \
    BOOST_PP_CAT(boost_se_lambda_this_capture_t_, id)

#define BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_TYPE(id) \
    /* can always use `typename` on C++11 (so no _TPL) */ \
    typename BOOST_SCOPE_EXIT_AUX_LAMBDA_PARAMS(id):: \
            BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_PARAM_TYPE(id)

// Precondition: HAS_THIS(traits).
#define BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_TYPEDEFS(id, traits) \
    BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS(id, \
            typename, /* can always use `typename` on C++11 (so no _TPL) */ \
            BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_CAPTURE_TYPE(id)) \
    /* capture type for workaround GCC internal error (even on later C++11) */ \
    struct BOOST_SCOPE_EXIT_AUX_LAMBDA_PARAMS(id) { \
        typedef BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_CAPTURE_TYPE(id) \
                BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_PARAM_TYPE(id); \
    };

#define BOOST_SCOPE_EXIT_AUX_IMPL_LAMBDA(id, traits) \
    BOOST_PP_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
        /* no need for TYPEDEF THIS MSVC workaround on C++11 */ \
        BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_TYPEDEFS \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(id, traits) \
    ::boost::scope_exit::aux::guard< \
        BOOST_PP_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_TYPE \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(id) \
    > BOOST_SCOPE_EXIT_AUX_GUARD(id) \
        BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            (this) \
        ) \
    ; \
    BOOST_SCOPE_EXIT_AUX_GUARD(id) = [ \
        BOOST_PP_LIST_ENUM(BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
    ]( \
        BOOST_PP_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            BOOST_SCOPE_EXIT_AUX_LAMBDA_THIS_TYPE \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(id) \
        BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), this_) \
    ) mutable /* can change value captures (as with SCOPE_EXIT) */ -> void

#endif // Lambdas.

#if defined(BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDA_IMPL) && \
        !defined(BOOST_NO_LAMBDAS) // Use lambda for SCOPE_EXIT (not just _ALL).

#define BOOST_SCOPE_EXIT_AUX_IMPL(id, ty, traits) \
    BOOST_SCOPE_EXIT_AUX_IMPL_LAMBDA(id, traits)

#else // Not using lambdas.

// ty: EMPTY() | typename
#define BOOST_SCOPE_EXIT_AUX_IMPL(id, ty, traits) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_DETAIL_TAG_DECL, id, \
            BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL, (id, ty), \
            BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
    BOOST_PP_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
        BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(id, ty, BOOST_SCOPE_EXIT_AUX_THIS_CAPTURE_T(id)) \
    struct BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id) { \
        /* interim capture types to workaround internal errors on old GCC */ \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_DETAIL_PARAM_DECL, (id, ty), \
                BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
        BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            typedef BOOST_SCOPE_EXIT_AUX_THIS_CAPTURE_T(id) \
                    BOOST_SCOPE_EXIT_AUX_THIS_T(id) ; \
        ) \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_AUX_MEMBER, id, \
                BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
        BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            BOOST_SCOPE_EXIT_AUX_THIS_T(id) \
                    BOOST_SCOPE_EXIT_DETAIL_PARAM_THIS(id) ; \
        ) \
        BOOST_SCOPE_EXIT_AUX_PARAMS_T_CTOR(id, ty, \
                BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits), \
                BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits)) \
    } BOOST_SCOPE_EXIT_AUX_PARAMS(id) \
        BOOST_SCOPE_EXIT_AUX_PARAMS_INIT(id, \
                BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits), \
                BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits)) \
    ; \
    ::boost::scope_exit::detail::declared< \
        ::boost::scope_exit::detail::resolve< \
            sizeof(BOOST_SCOPE_EXIT_AUX_ARGS) \
        >::cmp1<0>::cmp2 \
    > BOOST_SCOPE_EXIT_AUX_ARGS; \
    BOOST_SCOPE_EXIT_AUX_ARGS.value = &BOOST_SCOPE_EXIT_AUX_PARAMS(id); \
    struct BOOST_SCOPE_EXIT_AUX_GUARD_T(id) { \
        BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id)* boost_se_params_; \
        BOOST_SCOPE_EXIT_AUX_GUARD_T(id) (void* boost_se_params) \
            : boost_se_params_( \
                    (BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id)*)boost_se_params) \
        {} \
        ~BOOST_SCOPE_EXIT_AUX_GUARD_T(id)() { \
            boost_se_body( \
                BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_AUX_ARG, id, \
                        BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
                BOOST_PP_COMMA_IF(BOOST_PP_BITAND(BOOST_PP_LIST_IS_CONS( \
                        BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)), \
                        BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits))) \
                BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS( \
                        traits), \
                    boost_se_params_->BOOST_SCOPE_EXIT_DETAIL_PARAM_THIS(id) \
                ) \
            ); \
        } \
        static void boost_se_body( \
            BOOST_PP_LIST_FOR_EACH_I(BOOST_SCOPE_EXIT_AUX_ARG_DECL, (id, ty), \
                    BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)) \
            BOOST_PP_COMMA_IF(BOOST_PP_BITAND(BOOST_PP_LIST_IS_CONS( \
                    BOOST_SCOPE_EXIT_AUX_TRAITS_CAPTURES(traits)), \
                    BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits))) \
            BOOST_PP_EXPR_IIF(BOOST_SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
                ty BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id):: \
                        BOOST_SCOPE_EXIT_AUX_THIS_T(id) this_ \
            ) \
        )

#endif // Using lambdas.

// PUBLIC //

#if defined(BOOST_NO_VARIADIC_MACROS) // No variadic macros (sequences only).
#   define BOOST_SCOPE_EXIT_ID(id, within_template, void_or_seq) \
        BOOST_SCOPE_EXIT_AUX_IMPL(id, \
                BOOST_PP_EXPR_IIF(within_template, typename), \
                BOOST_SCOPE_EXIT_AUX_TRAITS( \
                        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(void_or_seq)))
#   define BOOST_SCOPE_EXIT(void_or_seq) \
        BOOST_SCOPE_EXIT_ID(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, 0, \
                void_or_seq)
#   define BOOST_SCOPE_EXIT_TPL(void_or_seq) \
        BOOST_SCOPE_EXIT_ID(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, 1, \
                void_or_seq)
#   if !defined(BOOST_NO_LAMBDAS)
#       define BOOST_SCOPE_EXIT_ALL_ID(id, seq) \
            BOOST_SCOPE_EXIT_AUX_IMPL_LAMBDA(id, \
                    BOOST_SCOPE_EXIT_AUX_TRAITS_ALL( \
                            BOOST_LOCAL_FUNCTION_DETAIL_PP_NON_VOID_LIST(seq)))
#       define BOOST_SCOPE_EXIT_ALL(seq) \
            BOOST_SCOPE_EXIT_ALL_ID( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, seq)
#   endif
#else // Variadic macros (both sequences and variadic tuples).
#   define BOOST_SCOPE_EXIT_ID(id, within_template, ...) \
        BOOST_SCOPE_EXIT_AUX_IMPL(id, \
                BOOST_PP_EXPR_IIF(within_template, typename), \
                BOOST_SCOPE_EXIT_AUX_TRAITS( \
                        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(__VA_ARGS__)))
#   define BOOST_SCOPE_EXIT(...) \
        BOOST_SCOPE_EXIT_ID(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, 0, \
                __VA_ARGS__)
#   define BOOST_SCOPE_EXIT_TPL(...) \
        BOOST_SCOPE_EXIT_ID(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, 1, \
                __VA_ARGS__)
#   if !defined(BOOST_NO_LAMBDAS)
#       define BOOST_SCOPE_EXIT_ALL_ID(id, ...) \
            BOOST_SCOPE_EXIT_AUX_IMPL_LAMBDA(id, \
                    BOOST_SCOPE_EXIT_AUX_TRAITS_ALL( \
                            BOOST_LOCAL_FUNCTION_DETAIL_PP_NON_VOID_LIST( \
                                    __VA_ARGS__)))
#       define BOOST_SCOPE_EXIT_ALL(...) \
            BOOST_SCOPE_EXIT_ALL_ID( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, __VA_ARGS__)
#   endif
#endif // Variadics.

#if defined(BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDA_IMPL) && \
        !defined(BOOST_NO_LAMBDAS) // Use lambdas for SCOPE_EXIT (not just ALL).
#   define BOOST_SCOPE_EXIT_END_ID(id) \
        ; /* lambdas ended with just `;` */
#else // Not using lambdas.
#   define BOOST_SCOPE_EXIT_END_ID(id) \
        } BOOST_SCOPE_EXIT_AUX_GUARD(id)(BOOST_SCOPE_EXIT_AUX_ARGS.value);
#endif // Using lambdas.
#define BOOST_SCOPE_EXIT_END \
    BOOST_SCOPE_EXIT_END_ID(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER)

// DOCUMENTATION //

#else // DOXYGEN

/** @file
@brief Scope exits allow to execute arbitrary code when the enclosing scope exits.
*/

/**
@brief This macro declares a scope exit.

The scope exit declaration schedules the execution of the scope exit body at the exit of the enclosing scope:

@code
    { // Some local scope.
        ...
        BOOST_SCOPE_EXIT(capture_list) {
            ... // Body code.
        } BOOST_SCOPE_EXIT_END
        ...
    }
@endcode

The enclosing scope must be local.
If multiple scope exits are declared within the same enclosing scope, the scope exit bodies are executed in the reversed order of their declarations.
Note how the end of the scope exit body must be marked by @RefMacro{BOOST_SCOPE_EXIT_END} (or by a <c>;</c> but only on C++11).

@Params
@Param{capture_list,
On compilers that support variadic macros\, the capture list syntax is defined by the following grammar:
@code
    capture_list:
            void | capture_tuple | capture_sequence
    capture_tuple:
            capture\, capture\, ...
    capture_sequence:
            (capture) (capture) ...
    capture:
            [&]variable | this_
@endcode
On compilers that do not support variadic macros\, <c>capture_tuple</c> cannot be used:
@code
    capture_list:
            void | capture_sequence
@endcode
Finally\, on C++11 compilers <c>this</c> can be used instead of <c>this_</c>:
@code
    capture:
            [&]variable | this_ | this
@endcode

Lexical conventions: <c>token1 | token2</c> means either <c>token1</c> or
<c>token2</c>; <c>[token]</c> means either <c>token</c> or nothing;
<c>{expression}</c> means the token resulting from the expression.
}
@EndParams

Note that on compilers with variadic macro support (most of moder compliers and all C++11 compilers), the capture list can be specified as a comma-separated list of tokens.
On all compilers, the same macro @RefMacro{BOOST_SCOPE_EXIT} also allows to specify the capture list as a Boost.Preprocessor sequence of tokens (for supporting compilers without variadic macros and for backward compatibility with older versions of this library).

The name <c>variable</c> of each captured variable must be a valid name in the enclosing scope and it must appear exactly once in the capture list.
If a capture starts with the ampersand sign <c>&</c>, the corresponding variable will be available by reference within the scope exit body; otherwise, a copy of the variable will be made at the point of the scope exit declaration and that copy will be available inside the scope exit body (in this case, the variable's type must be <c>CopyConstructible</c>).

From within a member function, the object <c>this</c> can be captured using the special symbol <c>this_</c> in both the capture list and the scope exit body (using <c>this</c> instead of <c>this_</c> in the scope exit body leads to undefined behaviour).
On C++11 it is possible (but not required) to use <c>this</c> instead of <c>this_</c>.

It is possible to capture no variable by specifying the capture list as <c>void</c> (regardless of variadic macro support).

Only variables listed in the capture list, static variables, <c>extern</c> variables, global variables, functions, and enumerations from the enclosing scope can be used inside the scope exit body.

On various GCC versions the special macro @RefMacro{BOOST_SCOPE_EXIT_TPL} must be used instead of @RefMacro{BOOST_SCOPE_EXIT} within templates (this is not necessary on C++11).

On C++11, it is possible capture all variables in scope without listing their names using the macro @RefMacro{BOOST_SCOPE_EXIT_ALL}.

@Warning The implementation executes the scope exit body within a destructor thus the scope exit body must never throw in order to comply with STL exception safety requirements.

@Note The implementation uses Boost.Typeof to automatically deduce the types of the captured variables.
In order to compile code in type-of emulation mode, Boost.Typeof must be properly configured (see the @RefSectId{Getting_Started, Getting Started} section).

@See @RefSect{Tutorial} section, @RefSectId{Getting_Started, Getting Started} section, @RefSectId{No_Variadic_Macros, No Variadic Macros} section, @RefMacro{BOOST_SCOPE_EXIT_TPL}, @RefMacro{BOOST_SCOPE_EXIT_ALL}, @RefMacro{BOOST_SCOPE_EXIT_END}.
*/
#define BOOST_SCOPE_EXIT(capture_list)

/**
@brief This macro is a workaround to declare a scope exit for various versions of GCC.

Various versions of the GCC compiler do not compile @RefMacro{BOOST_SCOPE_EXIT} inside function templates.
As a workaround, @RefMacro{BOOST_SCOPE_EXIT_TPL} should be used instead of @RefMacro{BOOST_SCOPE_EXIT} in these cases:

@code
    { // Some local scope.
        ...
        BOOST_SCOPE_EXIT_TPL(capture_list) {
            ... // Body code.
        } BOOST_SCOPE_EXIT_END
        ...
    }
@endcode

The syntax of @RefMacro{BOOST_SCOPE_EXIT_TPL} is the exact same as the one of @RefMacro{BOOST_SCOPE_EXIT} (see @RefMacro{BOOST_SCOPE_EXIT} for more information).

On C++11, @RefMacro{BOOST_SCOPE_EXIT_TPL} is not needed because @RefMacro{BOOST_SCOPE_EXIT} always compiles on GCC versions that support C++11 (that is also why there is no need for a <c>BOOST_SCOPE_EXIT_ALL_TPL</c> macro given that @RefMacro{BOOST_SCOPE_EXIT_ALL} is only available for C++11 compilers on which it always compiles correctly).
However, @RefMacro{BOOST_SCOPE_EXIT_TPL} is still provided on C++11 so to write code that is portable between C++03 and C++11 compilers.

@Note The problem boils down to the following code (see also <a href="http://gcc.gnu.org/bugzilla/show_bug.cgi?id=37920">GCC bug 37920</a>):
@code
    template<class T>
    void f(T const& x) {
        int i = 0;
        struct local {
            typedef __typeof__(i) typeof_i;
            typedef __typeof__(x) typeof_x;
        };
        typedef local::typeof_i i_type;
        typedef local::typeof_x x_type;
    }

    int main(void) { f(0); }
@endcode
This can be fixed by adding <c>typename</c> in front of <c>local::typeof_i</c> and <c>local::typeof_x</c> (which is the approach followed by the implementation of @RefMacro{BOOST_SCOPE_EXIT_TPL}).

@Note Although @RefMacro{BOOST_SCOPE_EXIT_TPL} has the same suffix as <c>BOOST_TYPEOF_TPL</c>, it does not follow the Boost.Typeof convention.

@See @RefSect{Tutorial} section, @RefMacro{BOOST_SCOPE_EXIT}, @RefMacro{BOOST_SCOPE_EXIT_END}.
*/
#define BOOST_SCOPE_EXIT_TPL(capture_list)

/**
@brief This macro allows to expand multiple scope exit macros on the same line.

This macro is equivalent to @RefMacro{BOOST_SCOPE_EXIT} but it can be expanded
multiple times on the same line if different identifiers <c>id</c> are provided
for each expansion (see @RefMacro{BOOST_SCOPE_EXIT} for more detail).

@Params
@Param{id,
    A unique identifier token which can be catted by the preprocessor (for
    example <c>__LINE__</c> or <c>scope_exit_number_1_on_line_123</c>).
}
@Param{within_template,
    Specify <c>1</c> when this macro is used in a type-dependant context
    on GCC\, <c>1</c> otherwise (this is equivalent to using
    @RefMacro{BOOST_SCOPE_EXIT_TPL} on separate lines).
}
@Param{capture_list,
    Same as the <c>capture_list</c> parameter of the
    @RefMacro{BOOST_SCOPE_EXIT} macro.
}
@EndParams

@Note This macro can be useful when the scope exit macros are expanded
within user-defined macros (because macros all expand on the same line).
On some compilers (e.g., MSVC which supports the non standard
<c>__COUNTER__</c> macro) it might not be necessary to use this macro but
the use of this macro is always necessary to ensure portability when expanding
multiple scope exit macros on the same line (because this library can only
portably use <c>__LINE__</c> to internally generate unique identifiers).

@See @RefMacro{BOOST_SCOPE_EXIT_END_ID}, @RefMacro{BOOST_SCOPE_EXIT_ALL_ID},
    @RefMacro{BOOST_SCOPE_EXIT}, @RefMacro{BOOST_SCOPE_EXIT_TPL}.
*/
#define BOOST_SCOPE_EXIT_ID(id, within_template, capture_list)

/**
@brief This macro declares a scope exit that captures all variables in scope (C++11 only).

This macro accepts a capture list starting with either <c>&</c> or <c>=</c> to capture all variables in scope by reference or value respectively (following the same syntax of C++11 lambdas).
A part from that, this macro works like @RefMacro{BOOST_SCOPE_EXIT} (see @RefMacro{BOOST_SCOPE_EXIT} for more information).

@code
    { // Some local scope.
        ...
        BOOST_SCOPE_EXIT_ALL(capture_list) { // C++11 only.
            ... // Body code.
        }; // Use `;` instead of `BOOST_SCOPE_EXIT_END` (C++11 only).
        ...
    }
@endcode

@Warning This macro is only available on C++11 compilers.
It is not defined on non-C++11 compilers so its use on non-C++11 compilers will generate a compiler error.

@Params
@Param{capture_list,
@code
capture_list:
        capture_tuple | capture_sequence
capture_tuple:
        {& | =} [\, capture\, capture\, ...]
capture_sequence:
        {(&) | (=)} [(capture) (capture) ...]
capture:
        [&]variable | this_ | this
@endcode

Lexical conventions: <c>token1 | token2</c> means either <c>token1</c> or
<c>token2</c>; <c>[token]</c> means either <c>token</c> or nothing;
<c>{expression}</c> means the token resulting from the expression.
}
@EndParams

For this macro, the capture list must always contain at least the leading <c>&</c> or <c>=</c> so it can never be <c>void</c>.

Note that on compilers with variadic macro support (which should be all C++11 compilers), the capture list can be specified as a comma-separated list.
On all compilers, the same macro @RefMacro{BOOST_SCOPE_EXIT_ALL} also allows to specify the capture list as a Boost.Preprocessor sequence (to allow to use a syntax consistent with the one of <c>BOOST_SCOPE_EXIT</c> when used on compilers without variadic macro support).
The scope exit body declared by this macro can be terminated equivalently by either a semi-column <c>;</c> or by the macro @RefMacro{BOOST_SCOPE_EXIT_END}.
The @RefMacro{BOOST_SCOPE_EXIT_ALL} macro is only available on C++11 where the terminating semi-column <c>;</c> can always be used without worrying about portability with C++03 (see @RefMacro{BOOST_SCOPE_EXIT_END} for more information).
Similarly, this macro can always use <c>this</c> instead of <c>this_</c> to capture the enclosing object without worrying about portability with C++03 because this macro is only available on C++11 compilers.

@Note In summary, this macro can take advantage of all syntax improvements allowed by C++11 but it optionally supports the same syntax required by C++03 so programmers can always program both @RefMacro{BOOST_SCOPE_EXIT_ALL} and @RefMacro{BOOST_SCOPE_EXIT} using the same syntax and for all compilers if they wish to do so.

@Warning The implementation executes the scope exit body within a destructor thus the scope exit body must never throw in order to comply with STL exception safety requirements.

@See @RefSect{Tutorial} section, @RefSectId{No_Variadic_Macros, No Variadic Macros} section, @RefMacro{BOOST_SCOPE_EXIT}, @RefMacro{BOOST_SCOPE_EXIT_END}.
*/
#define BOOST_SCOPE_EXIT_ALL(capture_list)

/**
@brief This macro allows to expand multiple scope exit macros on the same line.

This macro is equivalent to @RefMacro{BOOST_SCOPE_EXIT_ALL} but it can be
expanded multiple times on the same line if different identifiers <c>id</c> are
provided for each expansion (see @RefMacro{BOOST_SCOPE_EXIT_ALL} for more
detail).

@Params
@Param{id,
    A unique identifier token which can be catted by the preprocessor (for
    example <c>__LINE__</c> or <c>scope_exit_number_1_on_line_123</c>).
}
@Param{capture_list,
    Same as the <c>capture_list</c> parameter of the
    @RefMacro{BOOST_SCOPE_EXIT} macro.
}
@EndParams

@Note This macro can be useful when the scope exit macros are expanded
within user-defined macros (because macros all expand on the same line).
On some compilers (e.g., MSVC which supports the non standard
<c>__COUNTER__</c> macro) it might not be necessary to use this macro but
the use of this macro is always necessary to ensure portability when expanding
multiple scope exit macros on the same line (because this library can only
portably use <c>__LINE__</c> to internally generate unique identifiers).

@See @RefMacro{BOOST_SCOPE_EXIT_ID}, @RefMacro{BOOST_SCOPE_EXIT_ALL}.
*/
#define BOOST_SCOPE_EXIT_ALL_ID(id, capture_list)

/**
@brief This macro marks the end of a scope exit body.

This macro must follow the closing curly bracket <c>}</c> that ends the scope exit body:

@code
    { // Some local scope.
        ...
        BOOST_SCOPE_EXIT(capture_list) {
            ... // Body code.
        } BOOST_SCOPE_EXIT_END
        ...
    }
@endcode

On C++11, this macro is not necessary and it can be replaced by a semi-column <c>;</c> :
@code
    { // Some local scope.
        ...
        BOOST_SCOPE_EXIT(capture_list) {
            ... // Body code.
        }; // C++11 only.
        ...
    }
@endcode
However, @RefMacro{BOOST_SCOPE_EXIT_END} is still provided on C++11 so to write code that is portable between C++03 and C++11 compilers.

@See @RefSect{Tutorial} section, @RefMacro{BOOST_SCOPE_EXIT}, @RefMacro{BOOST_SCOPE_EXIT_TPL}, @RefMacro{BOOST_SCOPE_EXIT_ALL}.
*/
#define BOOST_SCOPE_EXIT_END

/**
@brief This macro allows to expand multiple scope exit macros on the same line.

This macro is equivalent to @RefMacro{BOOST_SCOPE_EXIT_END} but it can be
expanded multiple times on the same line if different identifiers <c>id</c> are
provided for each expansion (see @RefMacro{BOOST_SCOPE_EXIT_END} for more
detail).

@Params
@Param{id,
    A unique identifier token which can be catted by the preprocessor (for
    example <c>__LINE__</c> or <c>scope_exit_number_1_on_line_123</c>).
}
@EndParams

@Note This macro can be useful when the scope exit macros are expanded
within user-defined macros (because macros all expand on the same line).
On some compilers (e.g., MSVC which supports the non standard
<c>__COUNTER__</c> macro) it might not be necessary to use this macro but
the use of this macro is always necessary to ensure portability when expanding
multiple scope exit macros on the same line (because this library can only
portably use <c>__LINE__</c> to internally generate unique identifiers).

@See @RefMacro{BOOST_SCOPE_EXIT_ID}, @RefMacro{BOOST_SCOPE_EXIT_END}.
*/
#define BOOST_SCOPE_EXIT_END_ID(id)

/**
@brief Force to use C++11 lambda implementation for scope-exit macro.

If programmers define this configuration macro on a C++11 compiler, lambda functions will be used to implement the @RefMacro{BOOST_SCOPE_EXIT} macro.
By default this macro is not defined.

@Note When @RefMacro{BOOST_SCOPE_EXIT} is implemented using lambda, the semantics of its variable captures follow the semantics of C++11 lambda captures which are in general different from the legacy capture semantics of this library (e.g., C++11 lambdas require to capture data members via capturing the object <c>this</c> while this library always allowed to capture data members directly).
Therefore, when this configuration macro is defined, @RefMacro{BOOST_SCOPE_EXIT} is no longer backward compatible.

A semicolon <c>;</c> can simply be used instead of @RefMacro{BOOST_SCOPE_EXIT_END} when this configuration macro is defined.

This configuration macro does not control the definition of @RefMacro{BOOST_SCOPE_EXIT_ALL} which is always and automatically defined on compilers that support C++11 lambdas.

@See @RefMacro{BOOST_SCOPE_EXIT}, @RefMacro{BOOST_SCOPE_EXIT_ALL}, @RefMacro{BOOST_SCOPE_EXIT_END}.
*/
#define BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDA_IMPL

#endif // DOXYGEN

#endif // #ifndef FILE_boost_scope_exit_hpp_INCLUDED

