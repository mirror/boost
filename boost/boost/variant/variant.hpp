//-----------------------------------------------------------------------------
// boost variant/variant.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman, Itay Maman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_VARIANT_HPP
#define BOOST_VARIANT_VARIANT_HPP

#include <cstddef> // for std::size_t
#include <new> // for placement new
#include <typeinfo> // for typeid, std::type_info

#include "boost/variant/variant_fwd.hpp"
#include "boost/variant/detail/enable_recursive_fwd.hpp"
#include "boost/variant/detail/initializer.hpp"
#include "boost/variant/detail/make_variant_list.hpp"
#include "boost/variant/detail/visitation_impl.hpp"

#include "boost/variant/detail/generic_result_type.hpp"
#include "boost/variant/detail/has_nothrow_move.hpp"
#include "boost/variant/detail/move.hpp"

#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/mpl/aux_/config/eti.hpp"
#include "boost/mpl/aux_/value_wknd.hpp"

#include "boost/detail/reference_content.hpp"
#include "boost/aligned_storage.hpp"
#include "boost/compressed_pair.hpp"
#include "boost/empty.hpp"
#include "boost/utility/addressof.hpp"
#include "boost/static_assert.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/enum.hpp"
#include "boost/preprocessor/enum_params.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/add_const.hpp"
#include "boost/type_traits/has_nothrow_copy.hpp"
#include "boost/type_traits/is_const.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/variant/recursive_wrapper_fwd.hpp"
#include "boost/variant/static_visitor.hpp"

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/contains.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/empty.hpp"
#include "boost/mpl/find.hpp"
#include "boost/mpl/find_if.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/is_sequence.hpp"
#include "boost/mpl/logical.hpp"
#include "boost/mpl/max_element.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/remove_if.hpp"
#include "boost/mpl/sizeof.hpp"
#include "boost/mpl/size_t.hpp"
#include "boost/mpl/transform.hpp"
#include "boost/mpl/void.hpp"

///////////////////////////////////////////////////////////////////////////////
// Temporary home-grown enable_if (until boost::enable_if is adopted)
//
#if BOOST_WORKAROUND(BOOST_MSVC,  <= 1300)                      \
 || BOOST_WORKAROUND(__GNUC__, <= 2 && __GNUC_MINOR__ <= 95)    \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3000)                     \
 || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
#   define BOOST_VARIANT_AUX_NO_SFINAE
#endif

#if !defined(BOOST_VARIANT_AUX_NO_SFINAE)

namespace boost { namespace detail { namespace variant {

template <bool Cond, typename T = void>
struct enable_if_c
{
};

template <typename T>
struct enable_if_c< true,T >
{
    typedef T type;
};

template <typename C, typename T = void>
struct enable_if
    : enable_if_c< C::value, T >
{
};

}}} // namespace boost::detail::variant

#endif // !defined(BOOST_VARIANT_AUX_NO_SFINAE)

///////////////////////////////////////////////////////////////////////////////
// Implementation Macros:
//
// BOOST_VARIANT_VISITATION_UNROLLING_LIMIT
//   Defined in boost/variant/detail/visitation_impl.hpp.
//
// BOOST_VARIANT_MINIMIZE_SIZE
//   When #defined, implementation employs all known means to minimize the
//   size of variant objects. However, often unsuccessful due to alignment
//   issues, and potentially harmful to runtime speed, so not enabled by
//   default. (TODO: Investigate further.)

#if defined(BOOST_VARIANT_MINIMIZE_SIZE)
#   include <climits> // for SCHAR_MAX
#   include "boost/mpl/apply_if.hpp"
#   include "boost/mpl/equal_to.hpp"
#   include "boost/mpl/identity.hpp"
#   include "boost/mpl/int.hpp"
#   include "boost/mpl/if.hpp"
#   include "boost/mpl/less.hpp"
#   include "boost/mpl/long.hpp"
#   include "boost/mpl/O1_size.hpp"
#endif


namespace boost {

namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction max_value
//
// Finds the maximum value of the unary metafunction F over Sequence.
//
template <typename Sequence, typename F>
struct max_value
{
private: // helpers, for metafunction result (below)

    typedef typename mpl::max_element<
          typename mpl::transform<Sequence, F>::type
        >::type max_it;

public: // metafunction result

    typedef typename BOOST_MPL_AUX_DEREF_WNKD(max_it)
        type;

};

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_storage
//
// Provides an aligned storage type capable of holding any of the types
// specified in the given type-sequence.
//
template <typename Types>
struct make_storage
{
private: // helpers, for metafunction result (below)

    typedef typename max_value<
          Types, mpl::sizeof_<mpl::_1>
        >::type max_size;
    typedef typename max_value<
          Types, alignment_of<mpl::_1>
        >::type max_alignment;

public: // metafunction result

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

    typedef ::boost::aligned_storage<
          BOOST_MPL_AUX_VALUE_WKND(max_size)::value
        , BOOST_MPL_AUX_VALUE_WKND(max_alignment)::value
        > type;

#else // MSVC7 and below

    BOOST_STATIC_CONSTANT(std::size_t, msvc_max_size_c = max_size::value);
    BOOST_STATIC_CONSTANT(std::size_t, msvc_max_alignment_c = max_alignment::value);

    typedef ::boost::aligned_storage<
          msvc_max_size_c
        , msvc_max_alignment_c
        > type;

#endif // MSVC workaround

};

#if defined(BOOST_MPL_MSVC_60_ETI_BUG)

template<>
struct make_storage<int>
{
    typedef int type;
};

#endif

///////////////////////////////////////////////////////////////////////////////
// (detail) class null_storage
//
// Simulates aligned_storage's interface, but with nothing underneath.
//
struct null_storage
{
public: // queries

    void* address()
    {
        return 0;
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

    const void* address() const
    {
        return 0;
    }

#else // MSVC6

    const void* address() const;

#endif // MSVC6 workaround

};

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

// MSVC6 seems not to like inline functions with const void* returns, so we
// declare the following here:

const void* null_storage::address() const
{
    return 0;
}

#endif // MSVC6 workaround

///////////////////////////////////////////////////////////////////////////////
// (detail) class destroyer
//
// Generic static visitor that destroys the value it visits.
//
struct destroyer
    : public static_visitor<>
{
public: // visitor interfaces

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    operator()(T& operand) const
    {
        operand.~T();

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x0551))
        operand; // suppresses warnings
#endif

        BOOST_VARIANT_AUX_RETURN_VOID;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class copy_into
//
// Generic static visitor that copies the value it visits into the given buffer.
//
class copy_into
    : public static_visitor<>
{
private: // representation

    void* storage_;

public: // structors

    explicit copy_into(void* storage)
        : storage_(storage)
    {
    }

public: // visitor interfaces

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    operator()(const T& operand) const
    {
        new(storage_) T(operand);
        BOOST_VARIANT_AUX_RETURN_VOID;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class assigner
//
// Generic static visitor that assigns the given storage (which must be a
// constructed value of the same type) to the value it visits.
//
struct assigner
    : public static_visitor<>
{
private: // representation

    const void* rhs_storage_;

public: // structors

    explicit assigner(const void* rhs_storage)
        : rhs_storage_(rhs_storage)
    {
    }

public: // visitor interfaces

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    operator()(T& lhs_value) const
    {
        // NOTE TO USER :
        // Compile error here indicates one of variant's bounded types does
        // not meet the requirements of the Assignable concept. Thus,
        // variant is not Assignable.
        //
        // Hint: Are any of the bounded types const-qualified or references?
        //
        lhs_value = *static_cast<const T*>(rhs_storage_);
        BOOST_VARIANT_AUX_RETURN_VOID;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class swap_with
//
// Generic static visitor that swaps the value it visits with the given value.
//
struct swap_with
    : public static_visitor<>
{
private: // representation

    void* toswap_;

public: // structors

    explicit swap_with(void* toswap)
        : toswap_(toswap)
    {
    }

public: // visitor interfaces

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    operator()(T& operand) const
    {
        ::boost::detail::variant::move_swap(operand, *static_cast<T*>(toswap_));
        BOOST_VARIANT_AUX_RETURN_VOID;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class reflect
//
// Generic static visitor that performs a typeid on the value it visits.
//
struct reflect
    : public static_visitor<const std::type_info&>
{
public: // visitor interfaces

    template <typename T>
    const std::type_info& operator()(const T&) const
    {
        return typeid(T);
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class compare_equal
//
// Generic static visitor that compares the given lhs storage with the visited
// rhs content using operator==.
//
struct compare_equal
    : public static_visitor<bool>
{
private: // representation

    const void* lhs_;

public: // structors

    explicit compare_equal(const void* lhs)
        : lhs_(lhs)
    {
    }

public: // visitor interfaces

    template <typename T>
    bool operator()(const T& rhs) const
    {
        return *static_cast<const T*>(lhs_) == rhs;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class compare_less
//
// Generic static visitor that compares the given lhs storage with the visited
// rhs content using operator<.
//
struct compare_less
    : public static_visitor<bool>
{
private: // representation

    const void* lhs_;

public: // structors

    explicit compare_less(const void* lhs)
        : lhs_(lhs)
    {
    }

public: // visitor interfaces

    template <typename T>
    bool operator()(const T& rhs) const
    {
        return *static_cast<const T*>(lhs_) < rhs;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) class template invoke_visitor
//
// Generic static visitor that invokes the given visitor using:
//  * for 'internal' visits of a recursive_wrapper, the wrapper's held value.
//  * for all other visits, the given value itself.
//
template <typename Visitor>
class invoke_visitor
{
private: // representation

    Visitor& visitor_;

public: // visitor typedefs

    typedef typename Visitor::result_type
        result_type;

public: // structors

    explicit invoke_visitor(Visitor& visitor)
        : visitor_(visitor)
    {
    }

private: // helpers, for visitor interfaces (below)

#if !defined(BOOST_NO_VOID_RETURNS)

    template <typename T>
    result_type visit(T& operand)
    {
        return visitor_(operand);
    }

#   if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x0564))
    template <typename T>
    result_type visit(const T& operand)
    {
        return visitor_(operand);
    }
#   endif

#else // defined(BOOST_NO_VOID_RETURNS)

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    visit_impl(T& operand, mpl::false_)
    {
        return visitor_(operand);
    }

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    visit_impl(T& operand, mpl::true_)
    {
        visitor_(operand);
        BOOST_VARIANT_AUX_RETURN_VOID;
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    visit(T& operand)
    {
        typedef typename is_same<result_type, void>::type
            has_void_result_type;

        return visit_impl(operand, has_void_result_type());
    }

#endif // BOOST_NO_VOID_RETURNS) workaround

public: // visitor interfaces

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(boost::recursive_wrapper<T>& operand)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(const boost::recursive_wrapper<T>& operand)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(boost::detail::reference_content<T>& operand)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(const boost::detail::reference_content<T>& operand)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(T& operand)
    {
        return visit(operand);
    }

#else// defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

private: // helpers, for visitor interfaces (below)

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    execute_impl(boost::recursive_wrapper<T>& operand, long)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    execute_impl(const boost::recursive_wrapper<T>& operand, long)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    execute_impl(boost::detail::reference_content<T>& operand, long)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    execute_impl(const boost::detail::reference_content<T>& operand, long)
    {
        return visit(operand.get());
    }

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    execute_impl(T& operand, int)
    {
        return visit(operand);
    }

public: // visitor interfaces

    template <typename T>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(T& operand)
    {
        return execute_impl(operand, 1L);
    }

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING workaround

};

}} // namespace detail::variant

///////////////////////////////////////////////////////////////////////////////
// class template variant (concept inspired by Andrei Alexandrescu)
//
// See docs and boost/variant/variant_fwd.hpp for more information.
//
template <
      typename T0_
    , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(typename T)
    >
class variant
{
private: // helpers, for typedefs (below)

    typedef variant wknd_self_t;

    struct is_recursive_
        : detail::variant::is_recursive_flag<T0_>
    {
    };

    typedef typename mpl::apply_if<
          is_recursive_
        , T0_
        , mpl::identity< T0_ >
        >::type unwrapped_T0_;

    struct is_sequence_based_
        : mpl::is_sequence<unwrapped_T0_>
    {
    };

#if !defined(BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT)

private: // helpers, for typedefs (below)

    typedef typename mpl::apply_if<
          is_sequence_based_
        , mpl::identity<unwrapped_T0_>
        , detail::variant::make_variant_list<
              unwrapped_T0_
            , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
            >
        >::type specified_types;

    typedef typename mpl::apply_if<
          is_recursive_
        , mpl::transform<
              specified_types
            , mpl::protect<
                  detail::variant::quoted_enable_recursive<wknd_self_t>
                >
            >
        , mpl::identity< specified_types >
        >::type recursive_enabled_types;

public: // public typedefs

    typedef typename mpl::transform<
          recursive_enabled_types
        , unwrap_recursive<mpl::_1>
        >::type types;

private: // internal typedefs

    typedef typename mpl::transform<
          recursive_enabled_types
        , mpl::protect< detail::make_reference_content<> >
        >::type internal_types;

    typedef typename mpl::front<
          internal_types
        >::type internal_T0;

#else // defined(BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT)

private: // helpers, for typedefs (below)

    typedef unwrapped_T0_ T0;

    #define BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEFS(z,N,_) \
        typedef typename mpl::apply_if< \
              is_recursive_ \
            , detail::variant::enable_recursive< \
                  BOOST_PP_CAT(T,N) \
                , wknd_self_t \
                > \
            , mpl::identity< BOOST_PP_CAT(T,N) > \
            >::type BOOST_PP_CAT(recursive_enabled_T,N); \
        /**/

    BOOST_PP_REPEAT(
          BOOST_VARIANT_LIMIT_TYPES
        , BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEFS
        , _
        )

    #undef BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEFS

    #define BOOST_VARIANT_AUX_UNWRAP_RECURSIVE_TYPEDEFS(z,N,_) \
        typedef typename unwrap_recursive< \
              BOOST_PP_CAT(recursive_enabled_T,N) \
            >::type BOOST_PP_CAT(public_T,N); \
        /**/

    BOOST_PP_REPEAT(
          BOOST_VARIANT_LIMIT_TYPES
        , BOOST_VARIANT_AUX_UNWRAP_RECURSIVE_TYPEDEFS
        , _
        )

    #undef BOOST_VARIANT_AUX_UNWRAP_RECURSIVE_TYPEDEFS

public: // public typedefs

    typedef typename detail::variant::make_variant_list<
          BOOST_VARIANT_ENUM_PARAMS(public_T)
        >::type types;

private: // helpers, for internal typedefs (below)

    #define BOOST_VARIANT_AUX_MAKE_REFERENCE_CONTENT_TYPEDEFS(z,N,_) \
        typedef detail::make_reference_content< \
              BOOST_PP_CAT(recursive_enabled_T,N) \
            >::type BOOST_PP_CAT(internal_T,N); \
        /**/

    BOOST_PP_REPEAT(
          BOOST_VARIANT_LIMIT_TYPES
        , BOOST_VARIANT_AUX_MAKE_REFERENCE_CONTENT_TYPEDEFS
        , _
        )

    #undef BOOST_VARIANT_AUX_MAKE_REFERENCE_CONTENT_TYPEDEFS

private: // internal typedefs

    typedef typename detail::variant::make_variant_list<
          BOOST_VARIANT_ENUM_PARAMS(internal_T)
        >::type internal_types;

private: // static precondition assertions

    // NOTE TO USER :
    // variant< type-sequence > syntax is not supported on this compiler!
    //
#   if !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)
    BOOST_STATIC_ASSERT( ::boost::mpl::not_<is_sequence_based_>::value );
#   else
    BOOST_STATIC_ASSERT( !is_sequence_based_::value );
#   endif

#endif // BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT workaround

private: // helpers, for representation (below)

    typedef typename detail::variant::make_storage<internal_types>::type
        storage1_t;

    typedef typename mpl::remove_if<
          internal_types
        , detail::variant::has_nothrow_move_constructor<mpl::_1>
        >::type throwing_internal_types;

    // [storage2_t = empty(throwing_types) ? null_storage : make_storage<throwing_types>]
    typedef typename mpl::apply_if<
          mpl::empty<throwing_internal_types>
        , mpl::identity<detail::variant::null_storage>
        , detail::variant::make_storage<throwing_internal_types>
        >::type storage2_t;

private: // representation (int which_)

    // which_ on:
    // * [0,  size<internal_types>) indicates storage1
    // * [-size<internal_types>, 0) indicates storage2
    // if which_ >= 0:
    // * then which() -> which_
    // * else which() -> -(which_ + 1)

#if !defined(BOOST_VARIANT_MINIMIZE_SIZE)

    typedef int which_t;

#else // defined(BOOST_VARIANT_MINIMIZE_SIZE)

    // [if O1_size available, then attempt which_t size optimization...]
    // [select signed char if fewer than SCHAR_MAX types, else signed int:]
    typedef typename mpl::apply_if<
          mpl::equal_to< mpl::O1_size<internal_types>, mpl::long_<-1> >
        , mpl::identity< int >
        , mpl::if_<
              mpl::less< mpl::O1_size<internal_types>, mpl::int_<SCHAR_MAX> >
            , signed char
            , int
            >
        >::type which_t;

#endif // BOOST_VARIANT_MINIMIZE_SIZE switch

    which_t which_;

    static bool using_storage1_impl(mpl::true_)
    {
        // Since there is no storage2, we know storage1 is in use:
        return true;
    }

    bool using_storage1_impl(mpl::false_) const
    {
        // Since a true second storage is in use (i.e. NOT null_storage), we must check:
        return which_ >= 0;
    }

    bool using_storage1() const
    {
        typedef typename is_same<storage2_t, detail::variant::null_storage>::type
            has_single_storage;

        return using_storage1_impl(has_single_storage());
    }

    void activate_storage1(int which)
    {
        which_ = static_cast<which_t>( which );
    }

    void activate_storage2(int which)
    {
        which_ = static_cast<which_t>( -(which + 1) );
    }

private: // representation (aligned double-storage)

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

    compressed_pair< storage1_t,storage2_t > storage_;

    void* storage1() { return storage_.first().address(); }
    void* storage2() { return storage_.second().address(); }

    const void* storage1() const { return storage_.first().address(); }
    const void* storage2() const { return storage_.second().address(); }

#else // MSVC6

    storage1_t msvc_storage1_;
    storage2_t msvc_storage2_;

    void* storage1() { return msvc_storage1_.address(); }
    void* storage2() { return msvc_storage2_.address(); }

    const void* storage1() const;
    const void* storage2() const;

#endif // MSVC6 workaround

    void* active_storage()
    {
        return using_storage1() ? storage1() : storage2();
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

    const void* active_storage() const
    {
        return using_storage1() ? storage1() : storage2();
    }

#else // MSVC6

    const void* active_storage() const;

#endif // MSVC6 workaround

    void* inactive_storage()
    {
        return using_storage1() ? storage2() : storage1();
    }

public: // queries

    int which() const
    {
        // If NOT using storage1...
        if (using_storage1() == false)
            // ...then return adjusted which_:
            return -(which_ + 1);
        
        // Otherwise, return which_ directly:
        return which_;
    }

private: // helpers, for structors (below)

    typedef BOOST_VARIANT_AUX_INITIALIZER_T(
          recursive_enabled_types, recursive_enabled_T
        ) initializer;

    void destroy_content()
    {
        detail::variant::destroyer visitor;
        this->internal_apply_visitor(visitor);
    }

public: // structors

    ~variant()
    {
        destroy_content();
    }

    variant()
    {
        // NOTE TO USER :
        // Compile error from here indicates that the first bound
        // type is not default-constructible, and so variant cannot
        // support its own default-construction.
        //
        new( storage1() ) internal_T0();
        activate_storage1(0); // zero is the index of the first bounded type
    }

private: // helpers, for structors, cont. (below)

    class convert_copy_into
        : public static_visitor<int>
    {
    private: // representation

        void* storage_;

    public: // structors

        explicit convert_copy_into(void* storage)
            : storage_(storage)
        {
        }

    public: // helpers, for visitor interfaces (below)

        template <typename T>
        int execute(T& operand, int = 0) const
        {
            // NOTE TO USER :
            // Compile error here indicates one of the source variant's types 
            // cannot be unambiguously converted to the destination variant's
            // types (or that no conversion exists).
            //
            return initializer::initialize(storage_, operand);
        }

        template <typename T>
        int execute(
              boost::detail::reference_content<T>& operand
            , long
            ) const
        {
            return execute( operand.get() );
        }

        template <typename T>
        int execute(
              const boost::detail::reference_content<T>& operand
            , long
            ) const
        {
            return execute( operand.get() );
        }

    public: // visitor interfaces

        template <typename T>
        int operator()(T& operand) const
        {
            return execute(operand, 1L);
        }

    };

    friend class convert_copy_into;

private: // helpers, for structors, below 

    template <typename T>
    void convert_construct(
          T& operand
        , int
        , mpl::false_ = mpl::false_() // is_foreign_variant
        )
    {
        // NOTE TO USER :
        // Compile error here indicates that the given type is not 
        // unambiguously convertible to one of the variant's types
        // (or that no conversion exists).
        //
        activate_storage1(
              initializer::initialize(
                  storage1()
                , operand
                )
            );
    }

    template <typename Variant>
    void convert_construct(
          Variant& operand
        , long
        , mpl::true_// is_foreign_variant
        )
    {
        convert_copy_into visitor(storage1());
        activate_storage1(
              operand.internal_apply_visitor(visitor)
            );
    }

    template <typename Variant>
    void convert_construct_variant(Variant& operand)
    {
        // [Determine if the given variant is itself a bounded type, or if its
        //  content needs to be converted (i.e., it is a 'foreign' variant):]
        //

        typedef typename mpl::find_if<
              types
            , is_same<
                  add_const<mpl::_1>
                , const Variant
                >
            >::type found_it;

        typedef typename mpl::end<types>::type not_found;
        typedef typename is_same<
              found_it, not_found
            >::type is_foreign_variant;

        // Convert construct from operand:
        convert_construct(
              operand, 1L
            , is_foreign_variant()
            );
    }

    template <BOOST_VARIANT_ENUM_PARAMS(typename U)>
    void convert_construct(
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(U)>& operand
        , long
        )
    {
        convert_construct_variant(operand);
    }

    template <BOOST_VARIANT_ENUM_PARAMS(typename U)>
    void convert_construct(
          const boost::variant<BOOST_VARIANT_ENUM_PARAMS(U)>& operand
        , long
        )
    {
        convert_construct_variant(operand);    
    }

public: // structors, cont.

#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) \
 && !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

    template <typename T>
    variant(const T& operand)
    {
        convert_construct(operand, 1L);
    }

    template <typename T>
    variant(T& operand)
    {
        convert_construct(operand, 1L);
    }

#elif !defined(BOOST_VARIANT_AUX_NO_SFINAE)

    // For compilers that cannot distinguish between T& and const T& in
    // template constructors, but do support SFINAE, we can workaround:

    template <typename T>
    variant(const T& operand)
    {
        convert_construct(operand, 1L);
    }

    template <typename T>
    variant(
          T& operand
        , typename detail::variant::enable_if<
              mpl::not_< is_const<T> >
            , void
            >::type* = 0
        )
    {
        convert_construct(operand, 1L);
    }

#else // defined(BOOST_NO_SFINAE)

    // For compilers that cannot distinguish between T& and const T& in
    // template constructors, and do NOT support SFINAE, we can't workaround:

    template <typename T>
    variant(const T& operand)
    {
        convert_construct(operand, 1L);
    }

#endif // CW8 and MSVC6 workarounds

public: // structors, cont.

    // [MSVC6 requires copy constructor appear after template constructors]
    variant(const variant& operand)
    {
        // Copy the value of operand into *this...
        detail::variant::copy_into visitor( storage1() );
        operand.internal_apply_visitor(visitor);

        // ...and activate the *this's primary storage on success:
        activate_storage1(operand.which());
    }

private: // helpers, for modifiers (below)

    // class assign_into
    //
    // Generic visitor that assigns the value it visits to the variant it is
    // given, maintaining the strong guarantee of exception safety.
    //

    class assign_into
        : public static_visitor<>
    {
    private: // representation

        variant& target_;
        int source_which_;

    public: // structors

        assign_into(variant& target, int source_which)
            : target_(target)
            , source_which_(source_which)
        {
        }

    private: // helpers, for visitor interfaces (below)

        template <typename T, typename B>
        void assign_impl(
              const T& operand
            , mpl::true_// has_nothrow_copy
            , B// has_nothrow_move_constructor
            )
        {
            // Destroy the target's active storage...
            target_.destroy_content(); // nothrow

            // ...copy the source content into the target's storage1...
            new(target_.storage1())
                T( operand ); // nothrow

            // ...and activate the target's storage1:
            target_.activate_storage1(source_which_); // nothrow
        }

        template <typename T>
        void assign_impl(
              const T& operand
            , mpl::false_// has_nothrow_copy
            , mpl::true_// has_nothrow_move_constructor
            )
        {
            // Attempt to make a temporary copy (so as to move it below)...
            T temp(operand);

            // ...and upon success destroy the target's active storage...
            target_.destroy_content(); // nothrow

            // ...move the temporary copy into the target's storage1...
            new(target_.storage1())
                T( detail::variant::move(temp) ); // nothrow

            // ...and activate the target's storage1:
            target_.activate_storage1(source_which_); // nothrow
        }

        template <typename T>
        void assign_impl(
              const T& operand
            , mpl::false_// has_nothrow_copy
            , mpl::false_// has_nothrow_move_constructor
            )
        {
            // Attempt a copy into target's inactive storage...
            new(target_.inactive_storage()) T(operand);

            // ...and upon success destroy the target's active storage...
            target_.destroy_content(); // nothrow

            // ...and if the target _was_ using storage1...
            if (target_.using_storage1())
                // ...then activate storage2:
                target_.activate_storage2(source_which_); // nothrow
            else
                // ...otherwise, activate storage1:
                target_.activate_storage1(source_which_); // nothrow
        }

    public: // visitor interfaces

        template <typename T>
            BOOST_VARIANT_AUX_RETURN_VOID_TYPE
        operator()(const T& operand)
        {
            typedef typename has_nothrow_copy<T>::type
                nothrow_copy;
            typedef typename detail::variant::has_nothrow_move_constructor<T>::type
                nothrow_move_constructor;

            assign_impl(
                  operand
                , nothrow_copy()
                , nothrow_move_constructor()
                );

            BOOST_VARIANT_AUX_RETURN_VOID;
        }

    };

    friend class assign_into;

    void assign(const variant& rhs)
    {
        // If the types are the same...
        if (which() == rhs.which())
        {
            // ...then assign the value directly:
            detail::variant::assigner visitor(rhs.active_storage());
            this->internal_apply_visitor(visitor);
        }
        else
        {
            // Otherwise, perform general variant assignment:
            assign_into visitor(*this, rhs.which());
            rhs.internal_apply_visitor(visitor); 
        }
    }

public: // modifiers

    template <typename T>
    variant& operator=(const T& rhs)
    {
        // While potentially inefficient, the following construction of a
        // variant allows T as any type convertible to a bounded type (i.e.,
        // opposed to an exact match) without excessive code redundancy.
        //
        variant temp(rhs);
        assign( detail::variant::move(temp) );
        return *this;
    }

    variant& operator=(const variant& rhs)
    {
        assign(rhs);
        return *this;
    }

private: // helpers, for modifiers, cont. (below)

    // class swap_variants
    //
    // Generic static visitor that swaps given lhs and rhs variants.
    //
    // NOTE: Must be applied to the rhs variant.
    //
    class swap_variants
        : public static_visitor<>
    {
    private: // representation

        variant& lhs_;
        variant& rhs_;

    public: // structors

        swap_variants(variant& lhs, variant& rhs)
            : lhs_(lhs)
            , rhs_(rhs)
        {
        }

    private: // helpers, for visitor interfaces (below)

        template <typename T>
        void swap_impl(
              T& rhs_content
            , mpl::true_// has_nothrow_move_constructor
            )
        {
            // Cache rhs's which-index (because it will be overwritten)...
            int rhs_old_which = rhs_.which();

            // ...move rhs_content to the side...
            T rhs_old_content( detail::variant::move(rhs_content) ); // nothrow

            try
            {
                // ...attempt to move-assign lhs to (now-moved) rhs:
                rhs_ = detail::variant::move(lhs_);
            }
            catch(...)
            {
                // In case of failure, restore rhs's old contents...
                new(boost::addressof(rhs_content))
                    T( detail::variant::move(rhs_old_content) ); // nothrow

                // ...and rethrow:
                throw;
            }

            // In case of success, destroy lhs's active storage...
            lhs_.destroy_content(); // nothrow

            // ...move rhs's old contents to lhs's storage1...
            new(lhs_.storage1())
                T( detail::variant::move(rhs_old_content) ); // nothrow

            // ...and activate lhs's storage1:
            lhs_.activate_storage1(rhs_old_which); // nothrow
        }

        template <typename T>
        void swap_impl(
              T& rhs_content
            , mpl::false_// has_nothrow_move_constructor
            )
        {
            // Cache rhs's which-index (because it will be overwritten)...
            int rhs_old_which = rhs_.which();

            // ...move rhs's content into lhs's inactive storage...
            new(lhs_.inactive_storage()) T(detail::variant::move(rhs_content));

            try
            {
                // ...attempt to move-assign lhs to (now-copied) rhs:
                rhs_ = detail::variant::move(lhs_);
            }
            catch(...)
            {
                // In case of failure, destroy the copied value...
                static_cast<T*>(lhs_.inactive_storage())->~T(); // nothrow

                // ...and rethrow:
                throw;
            }

            // In case of success, destroy lhs's active storage...
            lhs_.destroy_content(); // nothrow

            // ...and if lhs _was_ using storage1...
            if (lhs_.using_storage1()) // nothrow
            {
                // ...then activate storage2:
                lhs_.activate_storage2(rhs_old_which); // nothrow
            }
            else
            {
                // ...otherwise, activate storage1:
                lhs_.activate_storage1(rhs_old_which); // nothrow
            }
        }

    public: // visitor interfaces

        template <typename T>
            BOOST_VARIANT_AUX_RETURN_VOID_TYPE
        operator()(T& rhs_content)
        {
            typedef typename detail::variant::has_nothrow_move_constructor<T>::type
                has_nothrow_move_constructor;

            swap_impl(
                  rhs_content
                , has_nothrow_move_constructor()
                );

            BOOST_VARIANT_AUX_RETURN_VOID;
        }

    };

    friend class swap_variants;

public: // modifiers, cont.

    void swap(variant& rhs)
    {
        // If the types are the same...
        if (which() == rhs.which())
        {
            // ...then swap the values directly:
            detail::variant::swap_with visitor(active_storage());
            rhs.internal_apply_visitor(visitor);
        }
        else
        {
            // Otherwise, perform general variant swap:
            swap_variants visitor(*this, rhs);
            rhs.internal_apply_visitor(visitor);
        }
    }

public: // queries

    //
    // NOTE: member which() defined above.
    //

    bool empty() const
    {
        typedef typename mpl::begin<internal_types>::type
            begin_it;

        typedef typename mpl::find<
              internal_types, boost::empty
            >::type empty_it;

        typedef typename mpl::distance<
              begin_it, empty_it
            >::type empty_index;

        return which() == empty_index::value;
    }

    const std::type_info& type() const
    {
        detail::variant::reflect visitor;
        return this->apply_visitor(visitor);
    }

public: // comparison operators

    bool operator==(const variant& rhs) const
    {
        if (this->which() != rhs.which())
            return false;

        detail::variant::compare_equal visitor( active_storage() );
        return rhs.apply_visitor(visitor);
    }

    bool operator<(const variant& rhs) const
    {
        //
        // Dirk Schreib suggested this collating order.
        //

        if (this->which() != rhs.which())
            return this->which() < rhs.which();

        detail::variant::compare_less visitor( active_storage() );
        return rhs.apply_visitor(visitor);
    }

    template <typename U>
    void operator==(const U&) const
    {
        // force static assertion failure:
        BOOST_STATIC_ASSERT( false && sizeof(U) );
    }

    template <typename U>
    void operator<(const U&) const
    {
        // force static assertion failure:
        BOOST_STATIC_ASSERT( false && sizeof(U) );
    }

// helpers, for visitation support (below) -- private when possible
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

    template < BOOST_VARIANT_ENUM_PARAMS(typename U) >
    friend class variant;

private:

#else// defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

public:

#endif// !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

    template <typename Visitor>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(
              typename Visitor::result_type
            )
    internal_apply_visitor(Visitor& visitor)
    {
        typedef mpl::int_<0> first_which;
        typedef typename mpl::begin<internal_types>::type first_it;
        typedef typename mpl::end<internal_types>::type last_it;
        typedef detail::variant::visitation_impl_step<
              first_it, last_it
            > first_step;

        return detail::variant::visitation_impl(
              which(), visitor, active_storage(), mpl::false_()
            , static_cast<first_which*>(0), static_cast<first_step*>(0)
            );
    }

    template <typename Visitor>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(
              typename Visitor::result_type
            )
    internal_apply_visitor(Visitor& visitor) const
    {
        typedef mpl::int_<0> first_which;
        typedef typename mpl::begin<internal_types>::type first_it;
        typedef typename mpl::end<internal_types>::type last_it;
        typedef detail::variant::visitation_impl_step<
              first_it, last_it
            > first_step;

        return detail::variant::visitation_impl(
              which(), visitor, active_storage(), mpl::false_()
            , static_cast<first_which*>(0), static_cast<first_step*>(0)
            );
    }

public: // visitation support

    template <typename Visitor>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(
              typename Visitor::result_type
            )
    apply_visitor(Visitor& visitor)
    {
        detail::variant::invoke_visitor<Visitor> invoker(visitor);
        return this->internal_apply_visitor(invoker);
    }

    template <typename Visitor>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(
              typename Visitor::result_type
            )
    apply_visitor(Visitor& visitor) const
    {
        detail::variant::invoke_visitor<Visitor> invoker(visitor);
        return this->internal_apply_visitor(invoker);
    }

}; // class variant

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

// MSVC6 seems not to like inline functions with const void* returns, so we
// declare the following here:

template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
const void*
variant<
      BOOST_VARIANT_ENUM_PARAMS(T)
    >::storage1() const
{
    return msvc_storage1_.address();
}

template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
const void*
variant<
      BOOST_VARIANT_ENUM_PARAMS(T)
    >::storage2() const
{
    return msvc_storage2_.address();
}

template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
const void*
variant<
      BOOST_VARIANT_ENUM_PARAMS(T)
    >::active_storage() const
{
    return const_cast<variant*>(this)->active_storage();
}

#endif // MSVC6 workaround

///////////////////////////////////////////////////////////////////////////////
// function template swap
//
// Swaps two variants of the same type (i.e., identical specification).
//
template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
inline void swap(
      variant< BOOST_VARIANT_ENUM_PARAMS(T) >& lhs
    , variant< BOOST_VARIANT_ENUM_PARAMS(T) >& rhs
    )
{
    lhs.swap(rhs);
}

} // namespace boost

// implementation additions
#include "boost/variant/detail/variant_io.hpp"

#endif // BOOST_VARIANT_VARIANT_HPP
