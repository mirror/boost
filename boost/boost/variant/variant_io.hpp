//-----------------------------------------------------------------------------
// boost variant/variant_comparison.hpp header file
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

#ifndef BOOST_VARIANT_VARIANT_IO_HPP
#define BOOST_VARIANT_VARIANT_IO_HPP

#include <iosfwd> // for std::basic_ostream forward declare

#include "boost/variant/variant_fwd.hpp"
#include "boost/variant/static_visitor.hpp"

namespace boost {

///////////////////////////////////////////////////////////////////////////////
// function template operator<<
//
// Outputs the content of the given variant to the given ostream.
//

// forward declare (allows output of embedded variant< variant< ... >, ... >)
template <
      typename E, typename T
    , BOOST_VARIANT_ENUM_PARAMS(typename U)
    >
inline std::basic_ostream<E,T>& operator<<(
      std::basic_ostream<E,T>& out
    , const variant< BOOST_VARIANT_ENUM_PARAMS(U) >& rhs
    );

namespace detail { namespace variant {

template <typename OStream>
class printer
    : public boost::static_visitor<>
{
private: // representation

    OStream& out_;

public: // structors

    explicit printer(OStream& out)
        : out_( out )
    {
    }

public: // visitor interface

    template <typename T>
    void operator()(const T& operand) const
    {
        out_ << operand;
    }

};

}} // namespace detail::variant

template <typename E, typename T, BOOST_VARIANT_ENUM_PARAMS(typename U)>
inline std::basic_ostream<E,T>& operator<<(
      std::basic_ostream<E,T>& out
    , const variant< BOOST_VARIANT_ENUM_PARAMS(U) >& rhs
    )
{
    detail::variant::printer< std::basic_ostream<E,T> > visitor(out);
    rhs.apply_visitor(visitor);
    return out;
}

} // namespace boost

#endif // BOOST_VARIANT_VARIANT_IO_HPP
