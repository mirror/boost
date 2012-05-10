//  scoped_enum_emulation.hpp  ---------------------------------------------------------//

//  Copyright Beman Dawes, 2009
//  Copyright (C) 2012 Vicente J. Botet Escriba
//  Copyright (C) 2012 Anthony Williams

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Generates C++0x scoped enums if the feature is present, otherwise emulates C++0x
//  scoped enums with C++03 namespaces and enums. The Boost.Config BOOST_NO_SCOPED_ENUMS
//  macro is used to detect feature support.
//
//  See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2347.pdf for a
//  description of the scoped enum feature. Note that the committee changed the name
//  from strongly typed enum to scoped enum.  
//
//  Caution: only the syntax is emulated; the semantics are not emulated and
//  the syntax emulation doesn't include being able to specify the underlying
//  representation type.
//
//  The emulation is via struct rather than namespace to allow use within classes.
//  Thanks to Andrey Semashev for pointing that out.
//
//  Helpful comments and suggestions were also made by Kjell Elster, Phil Endecott,
//  Joel Falcou, Mathias Gaunard, Felipe Magno de Almeida, Matt Calabrese, Vincente
//  Botet, and Daniel James. 
//
//  Sample usage:
//
//     BOOST_SCOPED_ENUM_START(algae) { green, red, cyan }; BOOST_SCOPED_ENUM_END
//     ...
//     BOOST_SCOPED_ENUM(algae) sample( algae::red );
//     void foo( BOOST_SCOPED_ENUM(algae) color );
//     ...
//     sample = algae::green;
//     foo( algae::cyan );

#ifndef BOOST_SCOPED_ENUM_EMULATION_HPP
#define BOOST_SCOPED_ENUM_EMULATION_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{

#ifdef BOOST_NO_SCOPED_ENUMS
  template <typename EnumType>
  struct underlying_type
  {
    typedef typename EnumType::underlying_type type;
  };

  template <typename UnderlyingType, typename EnumType>
  UnderlyingType underlying_cast(EnumType v)
  {
    return v.underlying();
  }

  template <typename EC>
  inline
  typename EC::enum_type native_value(EC e)
  {
    return e.native();
  }

#else  // BOOST_NO_SCOPED_ENUMS

  template <typename EnumType>
  struct underlying_type
  {
    //typedef typename std::underlying_type<EnumType>::type type;
  };

  template <typename UnderlyingType, typename EnumType>
  UnderlyingType underlying_cast(EnumType v)
  {
    return static_cast<UnderlyingType>(v);
  }

  template <typename EC>
  inline
  EC native_value(EC e)
  {
    return e;
 }

#endif
}


#ifdef BOOST_NO_SCOPED_ENUMS

#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS

#define BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR \
     explicit operator underlying_type() const { return underlying(); }

#else

#define BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR

#endif

#define BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType, UnderlyingType)    \
    struct EnumType {                                                   \
        typedef UnderlyingType underlying_type;                             \
        EnumType()  {}                                                  \
        explicit EnumType(underlying_type v) : v_(v) {}                 \
        underlying_type underlying() const { return v_; }               \
        BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR                \
    private:                                                                \
        underlying_type v_;                                                 \
        typedef EnumType self_type;                                     \
    public:                                                                 \
        enum enum_type

#define BOOST_SCOPED_ENUM_DECLARE_END2() \
        enum_type native() const { return enum_type(v_); }              \
        friend bool operator ==(self_type lhs, enum_type rhs)  { return enum_type(lhs.v_)==rhs; } \
        friend bool operator ==(enum_type lhs, self_type rhs)  { return lhs==enum_type(rhs.v_); } \
        friend bool operator !=(self_type lhs, enum_type rhs)  { return enum_type(lhs.v_)!=rhs; } \
        friend bool operator !=(enum_type lhs, self_type rhs)  { return lhs!=enum_type(rhs.v_); } \
    };

#define BOOST_SCOPED_ENUM_DECLARE_END(EnumType) \
    ; \
    EnumType(enum_type v) : v_(v) {}  \
    BOOST_SCOPED_ENUM_DECLARE_END2()

#define BOOST_SCOPED_ENUM_DECLARE_BEGIN(EnumType) \
  BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType,int)

#define BOOST_SCOPED_ENUM_NATIVE(EnumType) EnumType::enum_type
#define BOOST_SCOPED_ENUM_FORWARD_DECLARE(EnumType) struct EnumType

#else  // BOOST_NO_SCOPED_ENUMS

#define BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType,UnderlyingType) enum class EnumType:UnderlyingType
#define BOOST_SCOPED_ENUM_DECLARE_BEGIN(EnumType) enum class EnumType
#define BOOST_SCOPED_ENUM_DECLARE_END2() 
#define BOOST_SCOPED_ENUM_DECLARE_END(EnumType) ;

#define BOOST_SCOPED_ENUM_NATIVE(EnumType) EnumType
#define BOOST_SCOPED_ENUM_FORWARD_DECLARE(EnumType) enum class EnumType

#endif  // BOOST_NO_SCOPED_ENUMS

#define BOOST_SCOPED_ENUM_START(name) BOOST_SCOPED_ENUM_DECLARE_BEGIN(name)
#define BOOST_SCOPED_ENUM_END BOOST_SCOPED_ENUM_DECLARE_END2()
#define BOOST_SCOPED_ENUM(name) BOOST_SCOPED_ENUM_NATIVE(name)

#endif  // BOOST_SCOPED_ENUM_EMULATION_HPP
