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
#include <typeinfo> // for std::type_info

#include "boost/variant/variant_fwd.hpp"
#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/aligned_storage.hpp"
#include "boost/compressed_pair.hpp"
#include "boost/empty.hpp"
#include "boost/incomplete_fwd.hpp"
#include "boost/utility/addressof.hpp"
#include "boost/static_assert.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/enum.hpp"
#include "boost/preprocessor/enum_params.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/type_traits/add_const.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/is_const.hpp"
#include "boost/type_traits/is_same.hpp"

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/contains.hpp"
#include "boost/mpl/count_if.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/deref.hpp"
#include "boost/mpl/empty.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/is_sequence.hpp"
#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/logical.hpp"
#include "boost/mpl/max_element.hpp"
#include "boost/mpl/remove_if.hpp"
#include "boost/mpl/sizeof.hpp"
#include "boost/mpl/size_t.hpp"
#include "boost/mpl/transform.hpp"
#include "boost/mpl/void.hpp"

// The following are new/in-progress headers:
#include "boost/variant/detail/move.hpp"
#include "boost/variant/static_visitor.hpp"
#include "boost/variant/detail/has_nothrow_move.hpp"

//////////////////////////////////////////////////////////////////////////
// BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
//
// Defined if variant does not support variant<Types> syntax (see below). 
//
#if defined(BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE)
#   define BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
#endif

namespace boost {

namespace detail { namespace variant {

//////////////////////////////////////////////////////////////////////////
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

    typedef typename mpl::deref<max_it>::type
        type;

};

//////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_storage
//
// Provides an aligned storage type capable of holding any of the types
// specified in the given type-sequence.
//
template <typename Types>
struct make_storage
{
private: // helpers, for metafunction result (below)

    BOOST_STATIC_CONSTANT(
          std::size_t
        , max_size = (max_value< Types, mpl::sizeof_<mpl::_1> >::type::value)
        );
    BOOST_STATIC_CONSTANT(
          std::size_t
        , max_alignment = (max_value< Types, alignment_of<mpl::_1> >::type::value)
        );

public: // metafunction result

    typedef aligned_storage<max_size, max_alignment>
        type;

};

//////////////////////////////////////////////////////////////////////////
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

    const void* address() const
    {
        return 0;
    }

};

//////////////////////////////////////////////////////////////////////////
// (detail) class destroyer
//
// Generic static visitor that destroys the value it visits.
//
struct destroyer
    : public static_visitor<>
{
public: // visitor interfaces

    template <typename T>
    void operator()(T& operand) const
    {
        operand.~T();
    }

};

//////////////////////////////////////////////////////////////////////////
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
    void operator()(const T& operand) const
    {
        new(storage_) T(operand);
    }

};

//////////////////////////////////////////////////////////////////////////
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
    void operator()(T& operand) const
    {
        boost::detail::variant::move_swap(operand, *static_cast<T*>(toswap_));
    }

};

//////////////////////////////////////////////////////////////////////////
// (detail) class reflect
//
// Generic static visitor that performs a typeid on the value it visits.
//
struct reflect
    : public static_visitor<const std::type_info&>
{
public: // visitor interfaces

    template <typename T>
    const std::type_info& operator()(const T&)
    {
        return typeid(T);
    }

};

//////////////////////////////////////////////////////////////////////////
// (detail) class template invoke_visitor
//
// Generic static visitor that invokes the given visitor using:
//  * for raw visits where the given value is a
//    boost::incomplete, the given value's held value.
//  * for all other visits, the given value itself.
//
template <typename Visitor>
class invoke_visitor
    : public static_visitor< typename Visitor::result_type >
{
private: // representation

    Visitor& visitor_;

public: // typedefs

    typedef typename Visitor::result_type
        result_type;

public: // structors

    explicit invoke_visitor(Visitor& visitor)
        : visitor_(visitor)
    {
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

public: // visitor interfaces

    template <typename T>
    result_type operator()(incomplete<T>& operand)
    {
        return visitor_(operand.get());
    }

    template <typename T>
    result_type operator()(const incomplete<T>& operand)
    {
        return visitor_(operand.get());
    }

    template <typename T>
    result_type operator()(T& operand)
    {
        return visitor_(operand);
    }

#else// defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

private: // helpers, for visitor interfaces (below)

    template <typename T>
    result_type execute_impl(incomplete<T>& operand, long)
    {
        return visitor_(operand.get());
    }

    template <typename T>
    result_type execute_impl(const incomplete<T>& operand, long)
    {
        return visitor_(operand.get());
    }

    template <typename T>
    result_type execute_impl(T& operand, int)
    {
        return visitor_(operand);
    }

public: // visitor interfaces

    template <typename T>
    result_type operator()(T& operand)
    {
        return execute_impl(operand, 1L);
    }

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING workaround

};

//////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_variant_list
//
// Provides a MPL-compatible sequence with the specified non-void types
// as arguments. However, if resultant sequence is empty, then resultant
// sequence contains boost::empty.
//
// Rationale #1: see class template convert_void (above) and using-
// declaration workaround (below).
//
// Rationale #2: boost::empty behavior enables variant<> syntax.
//
template < BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename T) >
struct make_variant_list
{
private: // helpers, for metafunction result (below)

    // [Define a macro to convert any void(NN) tags to mpl::void...]
#   define BOOST_VARIANT_DETAIL_CONVERT_VOID(z, N,_)   \
        typename convert_void<BOOST_PP_CAT(T,N)>::type

    // [...so that the specified types can be passed to mpl::list...]
    typedef typename mpl::list< 
          BOOST_PP_ENUM(
              BOOST_VARIANT_LIMIT_TYPES
            , BOOST_VARIANT_DETAIL_CONVERT_VOID
            , _
            )
        >::type initial_result;

    // [...and, finally, the conversion macro can be undefined:]
#   undef BOOST_VARIANT_DETAIL_CONVERT_VOID

public: // metafunction result

    typedef typename mpl::if_<
          mpl::empty<initial_result>
        , mpl::list1<boost::empty>
        , initial_result
        >::type type;

};

}} // namespace detail::variant

//////////////////////////////////////////////////////////////////////////
// class template variant (concept inspired by Andrei Alexandrescu)
//
// See docs and boost/variant/variant_fwd.hpp for more information.
//
template <
    BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename T)
  >
class variant
{
private: // static precondition assertions

#if defined(BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT)

    // Sequences are not supported for compilers that do not support
    // using declarations in templates (see below).
    BOOST_STATIC_ASSERT((
          mpl::not_< // !is_sequence<T0>
              mpl::is_sequence<T0>
            >::type::value
        ));

#endif // BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT

public: // typedefs

    typedef typename mpl::apply_if<
          mpl::is_sequence<T0>
        , mpl::identity<T0>
        , detail::variant::make_variant_list<
              BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, T)
            >
        >::type types;

private: // static precondition assertions, cont.

    // [Assert unique types: ommitted due to compile-time complexity.]
    /*
    BOOST_STATIC_ASSERT((
          mpl::equal<
              types
            , typename mpl::unique<types>::type
            >::type::value
        ));
    */

#if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1300))

    // [Assert no top-level const-qualified types:]
    BOOST_STATIC_ASSERT((
          mpl::equal_to<
              typename mpl::count_if<
                  types
                , is_const<mpl::_>
                >::type
            , mpl::size_t<0>
            >::type::value
        ));

#endif // avoid on BOOST_MSVC

private: // representation

    typedef typename detail::variant::make_storage<types>::type
        storage1_t;

    typedef typename mpl::remove_if<
          types
        , detail::variant::has_nothrow_move_constructor<mpl::_1>
        >::type throwing_types;

    // [storage2_t = empty(throwing_types) ? null_storage : make_storage<throwing_types>]
    typedef typename mpl::apply_if<
          mpl::empty<throwing_types>
        , mpl::identity<detail::variant::null_storage>
        , detail::variant::make_storage<throwing_types>
        >::type storage2_t;

    // which_ on:
    // * [0,  size<types>) indicates storage1
    // * [-size<types>, 0) indicates storage2
    // if which_ >= 0:
    // * then which() -> which_
    // * else which() -> -(which_ + 1)
    int which_;
    compressed_pair< storage1_t,storage2_t > storage_;

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
        which_ = which;
    }

    void activate_storage2(int which)
    {
        which_ = -(which + 1);
    }

    void* active_storage()
    {
        if (using_storage1() == false)
            return storage_.second().address();
        
        return storage_.first().address();
    }

    const void* active_storage() const
    {
        return const_cast<variant * const>(this)->active_storage();
    }

    void* inactive_storage()
    {
        if (using_storage1() == false)
            return storage_.first().address();
 
        return storage_.second().address();
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

// [On compilers where using declarations in class templates can correctly avoid name hiding...]
#if !defined(BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE)

    // [...use an optimal converting initializer based on the variant typelist:]

    struct initializer_root
    {
    public: // static functions

        // Root type must expose name "initialize," so
        // the following dummy function is provided:

        static void initialize();

    };

    struct make_initializer_node
    {
        template <typename Base, typename Iterator>
        struct apply
        {
        private: // helpers, for metafunction result (below)

            struct initializer_node
                : Base
            {
            private: // helpers, for static functions (below)

                typedef typename Iterator::type
                    T;

            public: // static functions

                using Base::initialize;

                static int initialize(void* dest, const T& operand)
                {
                    new(dest) T(operand);

                    BOOST_STATIC_CONSTANT(
                          std::size_t
                        , idx = (
                              mpl::distance<
                                  typename mpl::begin<types>::type
                                , Iterator
                                >::type::value
                            )
                        );

                    return idx;
                }

            };

        public: // metafunction result

            typedef initializer_node
                type;

        };
    };

    typedef typename mpl::iter_fold<
          types
        , initializer_root
        , mpl::protect< make_initializer_node >
        >::type initializer;

#else // defined(BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE)

    // [...otherwise, use a hackish workaround based on variant's template parameters:]

    struct preprocessor_list_initializer
    {
    public: // static functions

        #define BOOST_VARIANT_INITIALIZE_FUNCTION(z,N,_)   \
            static int initialize(                         \
                  void* dest                               \
                , const BOOST_PP_CAT(T,N)& operand         \
                )                                          \
            {                                              \
                typedef BOOST_PP_CAT(T,N) T;               \
                BOOST_STATIC_CONSTANT(int, which = (N));   \
                                                           \
                new(dest) T(operand);                      \
                return which;                              \
            }                                              \
            /**/

        BOOST_PP_REPEAT(
              BOOST_VARIANT_LIMIT_TYPES
            , BOOST_VARIANT_INITIALIZE_FUNCTION
            , _
            )
        #undef BOOST_VARIANT_INITIALIZE_FUNCTION

    };

    typedef preprocessor_list_initializer
        initializer;

#endif // BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE workaround

    void destroy_content()
    {
        detail::variant::destroyer visitor;
        raw_apply_visitor(visitor);
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
        // type is default-constructible, and so variant cannot
        // support its own default-construction

        new(storage_.first().address()) T0();
        activate_storage1(0); // zero is the index of the first bounded type
    }

    variant(const variant& operand)
    {
        // Copy the value of operand into *this...
        detail::variant::copy_into visitor(storage_.first().address());
        operand.raw_apply_visitor(visitor);

        // ...and activate the *this's primary storage on success:
        activate_storage1(operand.which());
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

    public: // visitor interfaces

        template <typename T>
        int operator()(const T& operand) const
        {
            // NOTE TO USER :
            // Compile error here indicates one of the source variant's types 
            // cannot be unambiguously converted to the destination variant's
            // types (or that no conversion exists).
            //
            return initializer::initialize(storage_, operand);
        }

    };

private: // helpers for structors, cont. (below)

    template <typename T>
    void copy_construct(
          const T& operand
        , mpl::false_ = mpl::false_() // from_foreign_variant
        )
    {
        // NOTE TO USER :
        // Compile error here indicates that the given type is not 
        // unambiguously convertible to one of the variant's types
        // (or that no conversion exists).
        //
        activate_storage1(
              initializer::initialize(
                  storage_.first().address()
                , operand
                )
            );
    }

    template <typename Variant>
    void copy_construct(
          const Variant& operand
        , mpl::true_// from_foreign_variant
        )
    {
        convert_copy_into visitor(storage_.first().address());
        activate_storage1(
              operand.raw_apply_visitor(visitor)
            );
    }

private: // workaround, for structors, cont. (below)

    // [While unnecessary for conforming compilers, this workaround doesn't break anything:]

    template <BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename U)>
    void constructor_simulated_partial_ordering(
          const boost::variant<BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, U)>& operand
        , long)
    {
        // [Determine if operand is a bounded type, or if it needs to be converted (foreign):]
        typedef mpl::bool_<
              !mpl::contains<
                  types
                , boost::variant<BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES,U)>
                >::type::value
            > from_foreign_variant;

        copy_construct(
              operand
            , from_foreign_variant()
            );
    }

    template <typename T>
    void constructor_simulated_partial_ordering(const T& operand, int)
    {
        copy_construct(operand);
    }

public: // structors, cont.

    template <typename T>
    variant(const T& operand)
    {
        constructor_simulated_partial_ordering(operand, 1L);
    }

private: // helpers, for modifiers (below)

    // class assign_into
    //
    // Generic visitor that assigns the value it visits to the variant it is
    // given, maintaining the strong guarantee of exception safety.
    //

    friend class assign_into;

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

        template <typename T>
        void assign_impl(
              const T& operand
            , mpl::true_// has_nothrow_move_constructor
            )
        {
            // Attempt to make a temporary copy...
            T temp(operand);

            // ...and upon success destroy the target's active storage...
            target_.destroy_content(); // nothrow

            // ...move the temporary copy into the target's storage1...
            new(target_.storage_.first().address())  // nothrow
                T( detail::variant::move(temp) );

            // ...and activate the target's storage1:
            target_.activate_storage1(source_which_); // nothrow
        }

        template <typename T>
        void assign_impl(
              const T& operand
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
        void operator()(const T& operand)
        {
            assign_impl(
                  operand
                , mpl::bool_< detail::variant::has_nothrow_move_constructor<T>::value >()
                );
        }

    };

    void assign(const variant& operand)
    {
        assign_into visitor(*this, operand.which());
        operand.raw_apply_visitor(visitor);        
    }

public: // modifiers

    variant& operator=(const variant& rhs)
    {
        assign(rhs);
        return *this;
    }

    template <typename T>
    variant& operator=(const T& rhs)
    {
        // While potentially inefficient, the following (implicit)
        // construction of a variant allows T as any type convertible
        // to a bounded type (i.e., opposed to an exact match).

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

    friend class swap_variants;

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
                new(boost::addressof(rhs_content))     // nothrow
                    T( detail::variant::move(rhs_old_content) );

                // ...and rethrow:
                throw;
            }

            // In case of success, destroy lhs's active storage...
            lhs_.destroy_content(); // nothrow

            // ...move rhs's old contents to lhs's storage1...
            new(lhs_.storage_.first().address())   // nothrow
                T( detail::variant::move(rhs_old_content) );

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
        void operator()(T& rhs_content)
        {
            swap_impl(
                  rhs_content
                , mpl::bool_< detail::variant::has_nothrow_move_constructor<T>::value >()
                );
        }

    };

public: // modifiers, cont.

    void swap(variant& rhs)
    {
        // If the types are the same...
        if (which() == rhs.which())
        {
            // ...then swap the values directly:
            detail::variant::swap_with visitor(active_storage());
            rhs.raw_apply_visitor(visitor);
        }
        else
        {
            // Otherwise, perform general variant swap:
            swap_variants visitor(*this, rhs);
            rhs.raw_apply_visitor(visitor);
        }
    }

public: // queries

    //
    // NOTE: member which() defined above.
    //

    bool empty() const
    {
        typedef typename mpl::find<
              types
            , boost::empty
            >::type empty_it;

        typedef typename mpl::distance<
              typename mpl::begin<types>::type
            , empty_it
            >::type empty_index;

        return which() == empty_index::value;
    }

    const std::type_info& type() const
    {
        detail::variant::reflect visitor;
        return this->apply_visitor(visitor);
    }

private: // helpers, for visitation support (below)

    template <typename Which, typename Iterator, typename LastIterator, typename Variant, typename Visitor>
    static
        typename Visitor::result_type
    apply_visitor_impl(
          const int var_which // [const-ness may aid in optimization by compiler]
        , Variant& var
        , Visitor& visitor
        , mpl::false_// is_last
        )
    {
        typedef typename mpl::next<Which>::type next_which;
        typedef typename mpl::next<Iterator>::type next_iter;
        typedef mpl::bool_<is_same<next_iter, LastIterator>::value> next_is_last;
        typedef typename mpl::apply_if<
              is_const<Variant>
            , add_const<typename Iterator::type>
            , mpl::identity<typename Iterator::type>
            >::type T;

        if (var_which == Which::value)
        {
            return visitor(
                  *static_cast<T*>( var.active_storage() )
                );
        }

        return apply_visitor_impl<next_which, next_iter, LastIterator>(
              var_which
            , var
            , visitor
            , next_is_last()
            );
    }

    template <typename W, typename I, typename LI, typename Variant, typename Visitor>
    static
        typename Visitor::result_type
    apply_visitor_impl(
          const int
        , Variant&
        , Visitor&
        , mpl::true_// is_last
        )
    {
        // | This is never called at runtime: a visitor must handle at |
        // | least one of the variant's types. Throw to circumvent the |
        // | compile-time requirement that a value is returned:        |
        throw;
    }

// helpers, for visitation support (below) -- private when possible
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

    template < BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename U) >
    friend class variant;

private:

#else// defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

public:

#endif// !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

    template <typename Visitor>
        typename Visitor::result_type
    raw_apply_visitor(Visitor& visitor)
    {
        return apply_visitor_impl<
              mpl::int_<0>
            , typename mpl::begin<types>::type
            , typename mpl::end<types>::type
            >(which(), *this, visitor, mpl::false_());
    }

    template <typename Visitor>
        typename Visitor::result_type
    raw_apply_visitor(Visitor& visitor) const
    {
        return apply_visitor_impl<
              mpl::int_<0>
            , typename mpl::begin<types>::type
            , typename mpl::end<types>::type
            >(which(), *this, visitor, mpl::false_());
    }

public: // visitation support

    template <typename Visitor>
        typename Visitor::result_type
    apply_visitor(Visitor& visitor)
    {
        detail::variant::invoke_visitor<Visitor> invoker(visitor);
        return raw_apply_visitor(invoker);
    }

    template <typename Visitor>
        typename Visitor::result_type
    apply_visitor(Visitor& visitor) const
    {
        detail::variant::invoke_visitor<Visitor> invoker(visitor);
        return raw_apply_visitor(invoker);
    }

};

//////////////////////////////////////////////////////////////////////////
// function template swap
//
// Swaps two variants of the same type (i.e., identical specification).
//
template < BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename T) >
inline void swap(
      boost::variant< BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, T) >& lhs
    , boost::variant< BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, T) >& rhs
    )
{
    lhs.swap(rhs);
}

} // namespace boost

#endif // BOOST_VARIANT_VARIANT_HPP
