// (C) 2003, Fernando Luis Cacciola Carballal.
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this software for any purpose is hereby granted
// without fee, provided the above notices are retained on all copies.
// Permission to modify the code and to distribute modified code is granted,
// provided the above notices are retained, and a notice that the code was
// modified is included with the above copyright notice.
//
// See http://www.boost.org/lib/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_OPTIONAL_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_FLC_19NOV2002_HPP

#include<new>
#include<algorithm>

#include "boost/config.hpp"
#include "boost/assert.hpp"
#include "boost/type.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/type_with_alignment.hpp"
#include "boost/type_traits/remove_reference.hpp"
#include "boost/type_traits/is_reference.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/not.hpp"
#include "boost/detail/reference_content.hpp"

#if BOOST_WORKAROUND(BOOST_MSVC, == 1200)
// VC6.0 has the following bug:
//   When a templated assignment operator exist, an implicit conversion
//   constructing an optional<T> is used when assigment of the form:
//     optional<T> opt ; opt = T(...);
//   is compiled.
//   However, optional's ctor is _explicit_ and the assignemt shouldn't compile.
//   Therefore, for VC6.0 templated assignment is disabled.
//
#define BOOST_OPTIONAL_NO_CONVERTING_ASSIGNMENT
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
// VC7.0 has the following bug:
//   When both a non-template and a template copy-ctor exist
//   and the templated version is made 'explicit', the explicit is also
//   given to the non-templated version, making the class non-implicitely-copyable.
//
#define BOOST_OPTIONAL_NO_CONVERTING_COPY_CTOR
#endif

namespace boost {

class InPlaceFactoryBase ;

namespace optional_detail {

template <class T>
class aligned_storage
{
    // Borland ICEs if unnamed unions are used for this!
    union dummy_u
    {
        char data[ sizeof(T) ];
        BOOST_DEDUCED_TYPENAME type_with_alignment<
          ::boost::alignment_of<T>::value >::type aligner_;
    } dummy_ ;

  public:

    void const* address() const { return &dummy_.data[0]; }
    void      * address()       { return &dummy_.data[0]; }
} ;

template<class T>
class types_when_isnt_ref
{
  typedef T const& reference_const_type ;
  typedef T &      reference_type ;
  typedef T const* pointer_const_type ;
  typedef T *      pointer_type ;
  typedef T const& argument_type ;
} ;
template<class T>
class types_when_is_ref
{
  typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type raw_type ;

  typedef raw_type& reference_const_type ;
  typedef raw_type& reference_type ;
  typedef raw_type* pointer_const_type ;
  typedef raw_type* pointer_type ;
  typedef raw_type& argument_type ;
} ;

template<class T>
class optional_base
{
  private :

    typedef BOOST_DEDUCED_TYPENAME detail::make_reference_content<T>::type internal_type ;

    typedef aligned_storage<internal_type> storage_type ;

    typedef types_when_isnt_ref<T> types_when_not_ref ;
    typedef types_when_is_ref<T>   types_when_ref   ;

    typedef optional_base<T> this_type ;

  protected :

    typedef mpl::true_  is_reference_tag ;
    typedef mpl::false_ is_not_reference_tag ;

    typedef BOOST_DEDUCED_TYPENAME is_reference<T>::type is_reference_predicate ;
    
    typedef BOOST_DEDUCED_TYPENAME mpl::if_<is_reference_predicate,types_when_ref,types_when_not_ref>::type types ;
    
    typedef bool (this_type::*unspecified_bool_type)() const;

    typedef BOOST_DEDUCED_TYPENAME types::reference_type       reference_type ;
    typedef BOOST_DEDUCED_TYPENAME types::reference_const_type reference_const_type ;
    typedef BOOST_DEDUCED_TYPENAME types::pointer_type         pointer_type ;
    typedef BOOST_DEDUCED_TYPENAME types::pointer_const_type   pointer_const_type ;
    typedef BOOST_DEDUCED_TYPENAME types::argument_type        argument_type ;

    // Creates an optional<T> uninitialized.
    // No-throw
    optional_base ()
      :
      m_initialized(false) {}

    // Creates an optional<T> initialized with 'val'.
    // Can throw if T::T(T const&) does
    optional_base ( argument_type val )
      :
      m_initialized(false)
    {
      construct(val);
    }

    // Creates a deep copy of another optional<T>
    // Can throw if T::T(T const&) does
    optional_base ( optional_base const& rhs )
      :
      m_initialized(false)
    {
      if ( rhs.is_initialized() )
        construct(rhs.get_impl());
    }

    template<class Expr>
    explicit optional_base ( Expr const& expr, Expr const* tag )
      :
      m_initialized(false)
    {
      construct(expr,tag);
    }
    
    // No-throw (assuming T::~T() doesn't)
    ~optional_base() { destroy(is_reference_predicate()) ; }

    // Assigns from another optional<T> (deep-copies the rhs value)
    // Basic Guarantee: If T::T( T const& ) throws, this is left UNINITIALIZED
    optional_base& operator= ( optional_base const& rhs )
      {
        destroy(is_reference_predicate()); // no-throw

        if ( rhs.is_initialized() )
        {
          // An exception can be thrown here.
          // It it happens, THIS will be left uninitialized.
          assign(rhs.get_impl(), is_reference_predicate() );
        }
        return *this ;
      }

    // Assigns from a T (deep-copies the rhs value)
    // Basic Guarantee: If T::( T const& ) throws, this is left UNINITIALIZED
    optional_base& operator= ( argument_type val )
      {
        destroy(is_reference_predicate()); // no-throw

        // An exception can be thrown here.
        // It it happens, THIS will be left uninitialized.
        assign(val, is_reference_predicate() );

        return *this ;
      }

  public :

    // Destroys the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    void reset()
      {
        destroy(is_reference_predicate());
      }

    // Replaces the current value -if any- with 'val'
    // Basic Guarantee: If T::T( T const& ) throws this is left UNINITIALIZED.
    void reset ( argument_type val )
      {
        destroy(is_reference_predicate());
        assign(val, is_reference_predicate() );
      }

    // Returns a pointer to the value if this is initialized, otherwise,
    // returns NULL.
    // No-throw
    pointer_const_type get_ptr() const { return m_initialized ? get_ptr_impl() : 0 ; }
    pointer_type       get_ptr()       { return m_initialized ? get_ptr_impl() : 0 ; }

    bool is_initialized() const { return m_initialized ; }
    
  protected :

    void construct ( argument_type val )
     {
       new (m_storage.address()) internal_type(val) ;
       m_initialized = true ;
     }

    template<class Expr>
    void construct ( Expr const& expr, void const* )
     {
       new (m_storage.address()) internal_type(expr) ;
       m_initialized = true ;
     }

    template<class Expr>
    void construct ( Expr const& factory, InPlaceFactoryBase const* )
     {
       BOOST_STATIC_ASSERT ( mpl::not_<is_reference_predicate>::value ) ;

       boost::type<T> selector ;
       factory(selector,m_storage.address()) ;
       m_initialized = true ;
     }


    // NOTE: If T is of reference type, assignment must be disallowed, but optional's assignment uses T's copy-ctor
    // so the following overload is needed to filter out the case of T being a reference and issue an error.
    void assign ( argument_type val, is_not_reference_tag )
     {
       new (m_storage.address()) internal_type(val) ;
       m_initialized = true ;
     }

    void destroy( is_not_reference_tag )
     {
       if ( m_initialized )
       {
         get_impl().~T() ;
         m_initialized = false ;
       }
     }

    void destroy( is_reference_tag )
     {
       m_initialized = false ;
     }

    unspecified_bool_type safe_bool() const { return m_initialized ? &this_type::is_initialized : 0 ; }
    
    reference_const_type get_impl() const { return dereference(get_object(), is_reference_predicate() ) ; }
    reference_type       get_impl()       { return dereference(get_object(), is_reference_predicate() ) ; }

    pointer_const_type get_ptr_impl() const { return cast_ptr(get_object(), is_reference_predicate() ) ; }
    pointer_type       get_ptr_impl()       { return cast_ptr(get_object(), is_reference_predicate() ) ; }

  private :

    // internal_type can be either T or reference_content<T>
    internal_type const* get_object() const { return static_cast<internal_type const*>(m_storage.address()); }
    internal_type *      get_object()       { return static_cast<internal_type *>     (m_storage.address()); }

    // reference_content<T> lacks an implicit conversion to T&, so the following is needed to obtain a proper reference.
    reference_const_type dereference( internal_type const* p, is_not_reference_tag ) const { return *p ; }
    reference_type       dereference( internal_type*       p, is_not_reference_tag )       { return *p ; }
    reference_const_type dereference( internal_type const* p, is_reference_tag     ) const { return p->get() ; }
    reference_type       dereference( internal_type*       p, is_reference_tag     )       { return p->get() ; }

    // If T is of reference type, trying to get a pointer to the held value must result in a compile-time error.
    // Decent compilers should disallow conversions from reference_content<T>* to T*, but just in case,
    // the following olverloads are used to filter out the case and guarantee an error in case of T being a reference.
    pointer_const_type cast_ptr( internal_type const* p, is_not_reference_tag ) const { return p ; }
    pointer_type       cast_ptr( internal_type *      p, is_not_reference_tag )       { return p ; }

    bool m_initialized ;
    storage_type m_storage ;
} ;

} // namespace optional_detail

template<class T>
class optional : public optional_detail::optional_base<T>
{
    typedef optional_detail::optional_base<T> base ;

    typedef BOOST_DEDUCED_TYPENAME base::unspecified_bool_type  unspecified_bool_type ;

  public :

    typedef optional<T> this_type ;

    typedef T value_type ;

    typedef BOOST_DEDUCED_TYPENAME base::reference_type       reference_type ;
    typedef BOOST_DEDUCED_TYPENAME base::reference_const_type reference_const_type ;
    typedef BOOST_DEDUCED_TYPENAME base::pointer_type         pointer_type ;
    typedef BOOST_DEDUCED_TYPENAME base::pointer_const_type   pointer_const_type ;
    typedef BOOST_DEDUCED_TYPENAME base::argument_type        argument_type ;
    
    typedef BOOST_DEDUCED_TYPENAME base::is_reference_predicate is_reference_predicate ;

    // Creates an optional<T> uninitialized.
    // No-throw
    optional() : base() {}

    // Creates an optional<T> initialized with 'val'.
    // Can throw if T::T(T const&) does
    optional ( argument_type val ) : base(val) {}

#ifndef BOOST_OPTIONAL_NO_CONVERTING_COPY_CTOR
    // NOTE: MSVC needs templated versions first

    // Creates a deep copy of another convertible optional<U>
    // Requires a valid conversion from U to T.
    // Can throw if T::T(U const&) does
    template<class U>
    explicit optional ( optional<U> const& rhs )
      :
      base()
    {
      BOOST_STATIC_ASSERT ( mpl::not_<is_reference_predicate>::value ) ;

      if ( rhs.is_initialized() )
        construct(rhs.get());
    }
#endif

    // Creates a deep copy of another optional<T>
    // Can throw if T::T(T const&) does
    optional ( optional const& rhs ) : base(rhs) {}

    template<class Expr>
    explicit optional ( Expr const& expr ) : base(expr,&expr) {}

    // No-throw (assuming T::~T() doesn't)
    ~optional() {}

#ifndef BOOST_OPTIONAL_NO_CONVERTING_ASSIGNMENT
    // Assigns from another convertible optional<U> (converts && deep-copies the rhs value)
    // Requires a valid conversion from U to T.
    // Basic Guarantee: If T::T( U const& ) throws, this is left UNINITIALIZED
    template<class U>
    optional& operator= ( optional<U> const& rhs )
      {
        BOOST_STATIC_ASSERT ( mpl::not_<is_reference_predicate>::value ) ;

        destroy(is_reference_predicate()); // no-throw

        if ( rhs.is_initialized() )
        {
          // An exception can be thrown here.
          // It it happens, THIS will be left uninitialized.
          assign(rhs.get(), is_reference_predicate() );
        }
        return *this ;
      }
#endif

    // Assigns from another optional<T> (deep-copies the rhs value)
    // Basic Guarantee: If T::T( T const& ) throws, this is left UNINITIALIZED
    optional& operator= ( optional const& rhs )
      {
        this->base::operator= ( rhs ) ;
        return *this ;
      }

    // Assigns from a T (deep-copies the rhs value)
    // Basic Guarantee: If T::( T const& ) throws, this is left UNINITIALIZED
    optional& operator= ( argument_type val )
      {
        this->base::operator= ( val ) ;
        return *this ;
      }

    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    reference_const_type get() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_impl(); }
    reference_type       get()       { BOOST_ASSERT(this->is_initialized()) ; return this->get_impl(); }
    
    // Returns a pointer to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    pointer_const_type operator->() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_ptr_impl() ; }
    pointer_type       operator->()       { BOOST_ASSERT(this->is_initialized()) ; return this->get_ptr_impl() ; }

    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    reference_const_type operator *() const { return this->get() ; }
    reference_type       operator *()       { return this->get() ; }

    // implicit conversion to "bool"
    // No-throw
    operator unspecified_bool_type() const { return this->safe_bool() ; }

       // This is provided for those compilers which don't like the conversion to bool
       // on some contexts.
       bool operator!() const { return !this->is_initialized() ; }
} ;

// Returns a reference to the value if this is initialized, otherwise, the behaviour is UNDEFINED.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_const_type
get ( optional<T> const& opt )
{
  return opt.get() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_type
get ( optional<T>& opt )
{
  return opt.get() ;
}

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_const_type
get ( optional<T> const* opt )
{
  return opt->get_ptr() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_type
get ( optional<T>* opt )
{
  return opt->get_ptr() ;
}

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_const_type
get_pointer ( optional<T> const& opt )
{
  return opt.get_ptr() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_type
get_pointer ( optional<T>& opt )
{
  return opt.get_ptr() ;
}


// template<class OP> bool equal_pointees(OP const& x, OP const& y);
//
// Being OP a model of OptionalPointee (either a pointer or an optional):
//
// If both x and y have valid pointees, returns the result of (*x == *y)
// If only one has a valid pointee, returns false.
// If none have valid pointees, returns true.
// No-throw
template<class OptionalPointee>
inline
bool equal_pointees ( OptionalPointee const& x, OptionalPointee const& y )
{
  return (!x) != (!y) ? false : ( !x ? true : (*x) == (*y) ) ;
}

// template<class OP> bool less_pointees(OP const& x, OP const& y);
//
// Being OP a model of OptionalPointee (either a pointer or an optional):
//
// If y has not a valid pointee, returns false.
// ElseIf x has not a valid pointee, returns true.
// ElseIf both x and y have valid pointees, returns the result of (*x < *y)
// No-throw
template<class OptionalPointee>
inline
bool less_pointees ( OptionalPointee const& x, OptionalPointee const& y )
{
  return !y ? false : ( !x ? true : (*x) < (*y) ) ;
}

// optional's relational operators ( ==, !=, <, >, <=, >= ) have deep-semantics (compare values).
// WARNING: This is UNLIKE pointers. Use equal_pointees()/less_pointess() in generic code instead.

template<class T>
inline
bool operator == ( optional<T> const& x, optional<T> const& y )
{ return equal_pointees(x,y); }

template<class T>
inline
bool operator < ( optional<T> const& x, optional<T> const& y )
{ return less_pointees(x,y); }

template<class T>
inline
bool operator != ( optional<T> const& x, optional<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional<T> const& x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, optional<T> const& y )
{ return !( x < y ) ; }

//
// The following swap implementation follows the GCC workaround as found in
//  "boost/detail/compressed_pair.hpp"
//
namespace optional_detail {

// GCC <= 3.2 gets the using declaration at namespace scope (FLC)
#if BOOST_WORKAROUND(__GNUC__, <= 3) && __GNUC_MINOR__ <= 2
   // workaround for GCC (JM):
   using std::swap;
#define BOOST_OPTIONAL_STD_SWAP_INTRODUCED_AT_NS_SCOPE
#endif

// optional's swap:
// If both are initialized, calls swap(T&, T&), with whatever exception guarantess are given there.
// If only one is initialized, calls I.reset() and U.reset(*I), with the Basic Guarantee
// If both are uninitialized, do nothing (no-throw)
template<class T>
inline
void optional_swap ( optional<T>& x, optional<T>& y )
{
  if ( !x && !!y )
  {
    x.reset(*y); // Basic guarantee.
    y.reset();
  }
  else if ( !!x && !y )
  {
    y.reset(*x); // Basic guarantee.
    x.reset();
  }
  else if ( !!x && !!y )
  {
// GCC > 3.2 and all other compilers have the using declaration at function scope (FLC)
#ifndef BOOST_OPTIONAL_STD_SWAP_INTRODUCED_AT_NS_SCOPE
    // allow for Koenig lookup
    using std::swap ;
#endif
    swap(*x,*y);
  }
}

} // namespace optional_detail

template<class T> inline void swap ( optional<T>& x, optional<T>& y )
{
  optional_detail::optional_swap(x,y);
}


} // namespace boost

#endif

