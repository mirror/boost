//-----------------------------------------------------------------------------
// boost variant/variant_before.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_VARIANT_BEFORE_HPP
#define BOOST_VARIANT_VARIANT_BEFORE_HPP

#include <functional> // for std::binary_function

#include "boost/assert.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include "boost/mpl/bool.hpp"
#   include "boost/type_traits/is_same.hpp"
#endif

namespace boost {

///////////////////////////////////////////////////////////////////////////////
// class template variant_before
//
// Binary function object, provides collating order for variants.
//
// Rationale: Any ordering that might be constructed for operator< is destined
//   to be rather arbitrary and potentially confusing to the user. To avoid
//   his confusion, we force the user to explicitly spell variant_before.
//   (See also http://lists.boost.org/MailArchives/boost/msg51738.php.)
//

namespace detail { namespace variant {

class variant_before_impl
    : public boost::static_visitor<bool>
{

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

public: // binary visitor interface

    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }

    template <typename T, typename U>
    bool operator()(const T&, const U&) const
    {
        // should never be here (see variant_before below)
        BOOST_ASSERT(false);
        return false;
    }

#else // MSVC7 and below

private: // helpers, for binary visitor interface (below)

    template <typename T>
    bool execute_impl(const T& lhs, const T& rhs, mpl::true_) const
    {
        return lhs < rhs;
    }

    template <typename T, typename U>
    bool execute_impl(const T&, const U&, mpl::false_) const
    {
        // should never be here (see variant_before below)
        BOOST_ASSERT(false);
        return false;
    }

public: // binary visitor interface

    template <typename T, typename U>
    bool operator()(const T& lhs, const U& rhs) const
    {
        // MSVC7 finds normal implementation (above) ambiguous,
        // so we must explicitly disambiguate

        typedef typename is_same<U, T>::type U_is_T;
        return execute_impl(lhs, rhs, U_is_T());
    }

#endif // MSVC7 and below workaround

};

}} // namespace detail::variant

template <typename Variant>
class variant_before
    : public std::binary_function<Variant,Variant,bool>
{
public: // function interface

    bool operator()(const Variant& lhs, const Variant& rhs) const
    {
        //
        // Dirk Schreib suggested the below collating order.
        //

        if (lhs.which() == rhs.which())
        {
            detail::variant::variant_before_impl visitor;
            return boost::apply_visitor(visitor, lhs, rhs);
        }
        else
        {
            return lhs.which() < rhs.which();
        }
    }

};

} // namespace boost

#endif // BOOST_VARIANT_VARIANT_BEFORE_HPP
