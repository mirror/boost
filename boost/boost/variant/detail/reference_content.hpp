//-----------------------------------------------------------------------------
// boost variant/detail/reference_content.hpp header file
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

#ifndef BOOST_VARIANT_DETAIL_REFERENCE_CONTENT_HPP
#define BOOST_VARIANT_DETAIL_REFERENCE_CONTENT_HPP

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   include "boost/utility/addressof.hpp"
#   include "boost/type.hpp"
#endif

namespace boost {
namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) class template reference_content
//
// Non-Assignable wrapper for references.
//

template <typename RefT>
class reference_content;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T>
class reference_content< T& >
{
private: // representation

    T& content_;

public: // structors

    ~reference_content()
    {
    }

    reference_content(T& r)
        : content_( r )
    {
    }

    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }

public: // non-Assignable

    reference_content& operator=(const reference_content&);

public: // queries

    T& get() const
    {
        return content_;
    }

};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename RefT>
class reference_content
{
private: // representation

    void* content_;

public: // structors

    ~reference_content()
    {
    }

    reference_content(RefT r)
        : content_( boost::addressof(r) )
    {
    }

    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }

private: // non-Assignable

    reference_content& operator=(const reference_content&);

private: // helpers, for queries (below)

    template <typename T>
    RefT get_impl( boost::type<T&> ) const
    {
        return *static_cast<T*>( content_ );
    }

public: // queries

    RefT get() const
    {
        boost::type<RefT> wknd_type;
        return get_impl( wknd_type );
    }

};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

}} // namespace detail::variant
} // namespace boost

#endif // BOOST_VARIANT_DETAIL_REFERENCE_CONTENT_HPP
