// (C) Copyright Jonathan Turkanis 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Based on the ScopeGuard, by Andrei Alexandrescu and Petru Marginean. 
// See "Generic<Programming>: Change the Way You Write Exception-Safe 
// Code - Forever", C/C++ Users Jornal, Dec 2000, 
// http://www.cuj.com/documents/s=8000/cujcexp1812alexandr.

//
// Changes from original:
//
// - There are only two scope_guard implementation classes: one
//   which invokes a function or function object upon detsruction,
//   and one which does the same within a try-catch block. Other 
//   variants can be constructed using Boost.Bind or Boost.Lambda 
//   (see <libs/utility/scope_guard_example.cpp>).
//
// - The following names changes have been applied:
//
//     ScopeGuard          --> scope_guard
//     ScopeGuardImplBase  --> scope_guard_base
//     MakeGuard           --> make_guard
//     ON_BLOCK_EXIT       --> BOOST_SCOPE_GUARD
//   
// - The following were added:
//
//   - The object generator safe_guard, returning a scope_guard which
//     catches all exceptions.
//   - The macro BOOST_SAFE_GUARD, declaring an anonymous scope guard
//     which catches all exceptions.
//
// Open issues:
// 
// - Macros don't work on VC6 with edit-and-continue enabled (/ZI).
//
// Acknowledgments: Thanks to Pavel Vozenilik and Joaquín Mª López Muñoz.
//

#ifndef BOOST_IOSTREAMS_SCOPE_GUARD_HPP_INCLUDED
#define BOOST_IOSTREAMS_SCOPE_GUARD_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <exception>
#include <boost/config.hpp> // BOOST_MSVC, BOOST_JOIN.

namespace boost { namespace iostreams { namespace detail {

class scope_guard_base {
public:
    scope_guard_base() : dismissed_(false) { }
    scope_guard_base(const scope_guard_base& i)
        : dismissed_(i.dismissed_)
        { i.dismiss(); }
    void dismiss() const { dismissed_ = true; }
    void touch() const { }
protected:
    bool dismissed() const { return dismissed_; }
private:
    scope_guard_base& operator=(const scope_guard_base&);
    mutable bool dismissed_;
};
    
template<typename F>
struct scope_guard_impl : scope_guard_base {
    scope_guard_impl(F f) : f_(f) { }
    ~scope_guard_impl() { if (!dismissed()) f_(); }
    F f_;
};
    
template<typename F>
struct safe_scope_guard_impl : scope_guard_base {
    safe_scope_guard_impl(F f) : f_(f) { }
    ~safe_scope_guard_impl() 
        { 
            try { if (!dismissed()) f_(); }
            catch (std::exception&) { }
        }
    F f_;
};

} // End namespace detail.

typedef const detail::scope_guard_base& scope_guard;

template<typename F>
inline detail::scope_guard_impl<F> make_guard(F f)
{ return detail::scope_guard_impl<F>(f); }

template<typename F>
inline detail::safe_scope_guard_impl<F> safe_guard(F f)
{ return detail::safe_scope_guard_impl<F>(f); }

} } // End namespaces iostreams, boost.

#define BOOST_SCOPE_GUARD(f) ::boost::iostreams::scope_guard               \
    BOOST_JOIN(scope_guard, __LINE__) = ::boost::iostreams::make_guard(f); \
    BOOST_JOIN(scope_guard, __LINE__).touch();                      \
    /**/
#define BOOST_SAFE_GUARD(f) ::boost::iostreams::scope_guard                \
    BOOST_JOIN(scope_guard, __LINE__) = ::boost::iostreams::safe_guard(f); \
    BOOST_JOIN(scope_guard, __LINE__).touch();                      \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_SCOPE_GUARD_HPP_INCLUDED
