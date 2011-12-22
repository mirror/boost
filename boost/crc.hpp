//  Boost CRC library crc.hpp header file  -----------------------------------//

//  Copyright 2001, 2004, 2011 Daryle Walker.
//  Distributed under the Boost Software License, Version 1.0.  (See the
//  accompanying file LICENSE_1_0.txt or a copy at
//  <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/crc/> for the library's home page.

/** \file
    \brief  A collection of function templates and class templates that compute
      various forms of Cyclic Redundancy Codes (CRCs).

    \author  Daryle Walker

    \version  1.5

    \copyright  Boost Software License, version 1.0

    Contains the declarations (and definitions) of various kinds of CRC
    computation functions, function object types, and encapsulated policy types.

    \warning  The sample CRC-computer types were just checked against the
      <a href="http://regregex.bbcmicro.net/crc-catalogue.htm">Catalogue of
      parametrised CRC algorithms</a>.  New type aliases were added where I got
      a standard wrong.  However, the mistaken <code>typedef</code>s are still
      there for backwards compatibility.
    \note  There are references to the <i>Rocksoft&trade; Model CRC
      Algorithm</i>, as described within \"<cite>A Painless Guide to CRC Error
      Detection Algorithms</cite>,\" linked from \"<a
      href="http://www.ross.net/crc/crcpaper.html">CRC: A Paper On CRCs</a>\" by
      Ross Williams.  It will be abbreviated \"RMCA\" in other documentation
      blocks.
 */

#ifndef BOOST_CRC_HPP
#define BOOST_CRC_HPP

#include <boost/array.hpp>           // for boost::array
#include <boost/config.hpp>          // for BOOST_STATIC_CONSTANT, etc.
#include <boost/cstdint.hpp>         // for UINTMAX_C
#include <boost/integer.hpp>         // for boost::uint_t
#include <boost/mpl/integral_c.hpp>  // for boost::mpl::integral_c

#include <climits>  // for CHAR_BIT, etc.
#include <cstddef>  // for std::size_t

#include <boost/limits.hpp>  // for std::numeric_limits


// The type of CRC parameters that can go in a template should be related
// on the CRC's bit count.  This macro expresses that type in a compact
// form, but also allows an alternate type for compilers that don't support
// dependent types (in template value-parameters).
#if !(defined(BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS) || (defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)))
#define BOOST_CRC_PARM_TYPE  typename ::boost::uint_t<Bits>::fast
#else
#define BOOST_CRC_PARM_TYPE  unsigned long
#endif

// Some compilers [MS VC++ 6] cannot correctly set up several versions of a
// function template unless every template argument can be unambiguously
// deduced from the function arguments.  (The bug is hidden if only one version
// is needed.)  Since all of the CRC function templates have this problem, the
// workaround is to make up a dummy function argument that encodes the template
// arguments.  Calls to such template functions need all their template
// arguments explicitly specified.  At least one compiler that needs this
// workaround also needs the default value for the dummy argument to be
// specified in the definition.
#if defined(__GNUC__) || !defined(BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#define BOOST_CRC_DUMMY_PARM_TYPE
#define BOOST_CRC_DUMMY_INIT
#define BOOST_ACRC_DUMMY_PARM_TYPE
#define BOOST_ACRC_DUMMY_INIT
#else
namespace boost { namespace detail {
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
     BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
     bool ReflectIn, bool ReflectRem >
    struct dummy_crc_argument  { };
} }
#define BOOST_CRC_DUMMY_PARM_TYPE   , detail::dummy_crc_argument<Bits, \
 TruncPoly, InitRem, FinalXor, ReflectIn, ReflectRem> *p_
#define BOOST_CRC_DUMMY_INIT        BOOST_CRC_DUMMY_PARM_TYPE = 0
#define BOOST_ACRC_DUMMY_PARM_TYPE  , detail::dummy_crc_argument<Bits, \
 TruncPoly, 0, 0, false, false> *p_
#define BOOST_ACRC_DUMMY_INIT       BOOST_ACRC_DUMMY_PARM_TYPE = 0
#endif


namespace boost
{


//  Forward declarations  ----------------------------------------------------//

//! Bit-wise CRC computer
template < std::size_t Bits >
    class crc_basic;

//! Table-driven CRC computer, usable as a function object
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly = 0u,
           BOOST_CRC_PARM_TYPE InitRem = 0u,
           BOOST_CRC_PARM_TYPE FinalXor = 0u, bool ReflectIn = false,
           bool ReflectRem = false >
    class crc_optimal;

//! Compute the (unaugmented) CRC of a memory block
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
    typename uint_t<Bits>::fast  crc( void const *buffer,
     std::size_t byte_count
     BOOST_CRC_DUMMY_PARM_TYPE );

//! Compute the CRC of a memory block, with any augmentation provided by user
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
    typename uint_t<Bits>::fast  augmented_crc( void const *buffer,
     std::size_t byte_count, typename uint_t<Bits>::fast initial_remainder = 0u
     BOOST_ACRC_DUMMY_PARM_TYPE );

//! Computation type for ARC|CRC-16|CRC-IBM|CRC-16/ARC|CRC-16/LHA standard
typedef crc_optimal<16, 0x8005, 0, 0, true, true>         crc_16_type;
//! Computation type for CRC-16/CCITT-FALSE standard
typedef crc_optimal<16, 0x1021, 0xFFFF, 0, false, false>  crc_ccitt_false_t;
//! Computation type for the CRC mistakenly called the CCITT standard
typedef crc_ccitt_false_t                                 crc_ccitt_type;
//! Computation type for the actual
//! KERMIT|CRC-16/CCITT|CRC-16/CCITT-TRUE|CRC-CCITT standard
typedef crc_optimal<16, 0x1021, 0, 0, true, true>         crc_ccitt_true_t;
//! Computation type that I mistakenly called the XMODEM standard; it inverts
//! both reflection parameters and reflects the truncated divisor (Don't use?!)
typedef crc_optimal<16, 0x8408, 0, 0, true, true>         crc_xmodem_type;
//! Computation type for the actual XMODEM|ZMODEM|CRC-16/ACORN standard
typedef crc_optimal<16, 0x1021, 0, 0, false, false>       crc_xmodem_t;

//! Computation type for CRC-32|CRC-32/ADCCP|PKZIP standard
typedef crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>
  crc_32_type;


//  Forward declarations for implementation detail stuff  --------------------//
//  (Just for the stuff that will be needed for the next two sections)

//! \cond
namespace detail
{
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
        struct crc_table_t;

    template < std::size_t Bits, bool DoReflect >
        class crc_helper;

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template < std::size_t Bits >
        class crc_helper< Bits, false >;
    #endif

}  // namespace detail
//! \endcond


//  Simple cyclic redundancy code (CRC) class declaration  -------------------//

/** Objects of this type compute the CRC checksum of submitted data, where said
    data can be entered piecemeal through several different kinds of groupings.
    Modulo-2 polynomial division steps are always performed bit-wise, without
    the use of pre-computation tables.  Said division uses the altered
    algorithm, so any data has to be unaugmented.

    \pre  0 \< \a Bits \<= \c std::numeric_limits&lt;uintmax_t&gt;::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
 */
template < std::size_t Bits >
class crc_basic
{
public:
    // Type
    /** \brief  The register type used for computations

        This type is used for CRC calculations and is the type for any returned
        checksums and returned or submitted remainders, (truncated) divisors, or
        XOR masks.  It is a built-in unsigned integer type.
     */
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constant for the template parameter
    //! A copy of \a Bits provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );

    // Constructor (use the automatic copy-ctr, move-ctr, and dtr)
    //! Create a computer, separately listing each needed parameter
    explicit  crc_basic( value_type truncated_polynominal,
               value_type initial_remainder = 0, value_type final_xor_value = 0,
               bool reflect_input = false, bool reflect_remainder = false );

    // Internal Operations
    //! Return the (truncated) polynomial divisor
    value_type  get_truncated_polynominal() const;
    //! Return what the polynomial remainder was set to during construction
    value_type  get_initial_remainder() const;
    //! Return the XOR-mask used during output processing
    value_type  get_final_xor_value() const;
    //! Check if input-bytes will be reflected before processing
    bool        get_reflect_input() const;
    //! Check if the remainder will be reflected during output processing
    bool        get_reflect_remainder() const;

    //! Return the remainder based from already-processed bits
    value_type  get_interim_remainder() const;
    //! Change the interim remainder to a new value
    void        reset( value_type new_rem );
    //! Change the interim remainder back to the initial value
    void        reset();

    // External Operations
    //! Submit a single bit for input processing
    void  process_bit( bool bit );
    //! Submit the lowest \a bit_count bits of a byte for input processing
    void  process_bits( unsigned char bits, std::size_t bit_count );
    //! Submit a single byte for input processing
    void  process_byte( unsigned char byte );
    //! Submit a memory block for input processing, iterator-pair style
    void  process_block( void const *bytes_begin, void const *bytes_end );
    //! Submit a memory block for input processing, pointer-and-size style
    void  process_bytes( void const *buffer, std::size_t byte_count );

    //! Return the checksum of the already-processed bits
    value_type  checksum() const;

private:
    // Member data
    value_type  rem_;
    value_type  poly_, init_, final_;  // non-const to allow assignability
    bool        rft_in_, rft_out_;     // non-const to allow assignability

};  // boost::crc_basic


//  Optimized cyclic redundancy code (CRC) class declaration  ----------------//

/** Objects of this type compute the CRC checksum of submitted data, where said
    data can be entered piecemeal through several different kinds of groupings.
    Modulo-2 polynomial division steps are performed byte-wise, aided by the use
    of pre-computation tables.  Said division uses the altered algorithm, so any
    data has to be unaugmented.

    \pre  0 \< \a Bits \<= \c std::numeric_limits&lt;uintmax_t&gt;::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.  Defaults
      to \c 0, i.e. the only non-zero term is the implicit one for
      x<sup><var>Bits</var></sup>.  (\e Poly from the RMCA)
    \tparam InitRem  The (unaugmented) initial state of the polynomial
      remainder.  Defaults to \c 0 if omitted.  (\e Init from the RMCA)
    \tparam FinalXor  The (XOR) bit-mask to be applied to the output remainder,
      after possible reflection but before returning.  Defaults to \c 0 (i.e. no
      bit changes) if omitted.  (\e XorOut from the RMCA)
    \tparam ReflectIn  If \c true, input bytes are read lowest-order bit first,
      otherwise highest-order bit first.  Defaults to \c false if omitted.
      (\e RefIn from the RMCA)
    \tparam ReflectRem  If \c true, the output remainder is reflected before the
      XOR-mask.  Defaults to \c false if omitted.  (\e RefOut from the RMCA)

    \todo  Get rid of the default value for \a TruncPoly.  Choosing a divisor is
      an important decision with many factors, so a default is never useful,
      especially a bad one.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
class crc_optimal
{
public:
    // Type
    //! \copydoc  boost::crc_basic::value_type
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constants for the template parameters
    //! \copydoc  boost::crc_basic::bit_count
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );
    //! A copy of \a TruncPoly provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, truncated_polynominal = TruncPoly );
    //! A copy of \a InitRem provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, initial_remainder = InitRem );
    //! A copy of \a FinalXor provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, final_xor_value = FinalXor );
    //! A copy of \a ReflectIn provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( bool, reflect_input = ReflectIn );
    //! A copy of \a ReflectRem provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( bool, reflect_remainder = ReflectRem );

    // Constructor (use the automatic copy-ctr, move-ctr, and dtr)
    //! Create a computer, giving an initial remainder if desired
    explicit  crc_optimal( value_type init_rem = InitRem );

    // Internal Operations
    //! \copybrief  boost::crc_basic::get_truncated_polynominal
    value_type  get_truncated_polynominal() const;
    //! \copybrief  boost::crc_basic::get_initial_remainder
    value_type  get_initial_remainder() const;
    //! \copybrief  boost::crc_basic::get_final_xor_value
    value_type  get_final_xor_value() const;
    //! \copybrief  boost::crc_basic::get_reflect_input
    bool        get_reflect_input() const;
    //! \copybrief  boost::crc_basic::get_reflect_remainder
    bool        get_reflect_remainder() const;

    //! \copybrief  boost::crc_basic::get_interim_remainder
    value_type  get_interim_remainder() const;
    //! Change the interim remainder to either a given value or the initial one
    void        reset( value_type new_rem = InitRem );

    // External Operations
    //! \copybrief  boost::crc_basic::process_byte
    void  process_byte( unsigned char byte );
    //! \copybrief  boost::crc_basic::process_block
    void  process_block( void const *bytes_begin, void const *bytes_end );
    //! \copybrief  boost::crc_basic::process_bytes
    void  process_bytes( void const *buffer, std::size_t byte_count );

    //! \copybrief  boost::crc_basic::checksum
    value_type  checksum() const;

    // Operators
    //! Submit a single byte for input processing, suitable for the STL
    void        operator ()( unsigned char byte );
    //! Return the checksum of the already-processed bits, suitable for the STL
    value_type  operator ()() const;

private:
    // The implementation of output reflection depends on both reflect states.
    BOOST_STATIC_CONSTANT( bool, reflect_output = (ReflectRem != ReflectIn) );

    #ifndef __BORLANDC__
    #define BOOST_CRC_REF_OUT_VAL  reflect_output
    #else
    typedef crc_optimal  self_type;
    #define BOOST_CRC_REF_OUT_VAL  (self_type::reflect_output)
    #endif

    // More implementation types
    typedef detail::crc_table_t<Bits, TruncPoly, ReflectIn>  crc_table_type;
    typedef detail::crc_helper<Bits, ReflectIn>              helper_type;
    typedef detail::crc_helper<Bits, BOOST_CRC_REF_OUT_VAL>  reflect_out_type;

    #undef BOOST_CRC_REF_OUT_VAL

    // Member data
    value_type  rem_;

};  // boost::crc_optimal


//  Implementation detail stuff  ---------------------------------------------//

//! \cond
namespace detail
{
    // Single-bit mask constant, MPL-style
    // (Template parameter is the 0-based index of the bit, i.e. 2**index.)
    template < int BitIndex >
    struct high_bit_mask_c
        : boost::mpl::integral_c<typename boost::uint_t< BitIndex + 1 >::fast,
           ( UINTMAX_C(1) << BitIndex )>
    {};

    // Lowest-bits mask constant, MPL-style
    // (Template parameter is the number of low bits set, i.e. 2**count - 1.)
    template < int BitCount >
    struct low_bits_mask_c
        : boost::mpl::integral_c<typename boost::uint_t< BitCount >::fast, (
           BitCount ? (( (( UINTMAX_C(1) << (BitCount - 1) ) - 1u) << 1 ) |
           UINTMAX_C( 1 )) : 0u )>
    {};

    // Bit-reflection functions
    template < typename Unsigned >
    Unsigned  reflect_unsigned( Unsigned x, int word_length
     = std::numeric_limits<Unsigned>::digits )
    {
        for ( Unsigned  l = 1u, h = l << (word_length - 1) ; h > l ; h >>= 1, l
         <<= 1 )
        {
            Unsigned const  m = h | l, t = x & m;

            if ( (t == h) || (t == l) )
                x ^= m;
        }

        return x;
    }

    unsigned char  reflect_byte_slowly( unsigned char x )
    { return reflect_unsigned(x); }

    boost::array< unsigned char, (UINTMAX_C( 1 ) << CHAR_BIT) >
    make_byte_reflection_table()
    {
        boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )>  result;

        for ( boost::uint_t<CHAR_BIT + 1>::fast  i = 0u ; i <= UCHAR_MAX ; ++i )
            result[ i ] = reflect_byte_slowly( i );

        return result;
    }

    unsigned char  reflect_byte( unsigned char x )
    {
        static  boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )> const
          table = make_byte_reflection_table();

        return table[ x ];
    }

    template < typename Unsigned >
    Unsigned  reflect_optionally( Unsigned x, bool reflect, int word_length
     = std::numeric_limits<Unsigned>::digits )
    { return reflect ? reflect_unsigned(x, word_length) : x; }

    unsigned char  reflect_byte_optionally( unsigned char x, bool reflect )
    { return reflect ? reflect_byte(x) : x; }

    // Encapsulate the core CRC computation routines
    template < int Bits, typename Register >
    bool  crc_modulo_update( Register &remainder, bool new_dividend_bit,
     Register truncated_divisor )
    {
        // compare the new bit with the remainder's highest
        remainder ^= new_dividend_bit ? high_bit_mask_c<Bits - 1>::value : 0u;

        // perform modulo-2 division
        bool const  quotient = remainder & high_bit_mask_c<Bits - 1>::value;

        remainder <<= 1;
        remainder ^= quotient ? truncated_divisor : 0u;
        return quotient;
    }

    template < int Bits, typename Register, typename Word >
    void  crc_modulo_word_update( Register &remainder, Word new_dividend_bits,
     Register truncated_divisor, int word_length, bool reflect )
    {
        // The natural reading order for division is highest digit/bit first.
        // The "reflect" parameter switches this.  However, building a bit mask
        // for the lowest bit is the easiest....
        new_dividend_bits = reflect_optionally( new_dividend_bits, not reflect,
         word_length );

        // Perform modulo-2 division
        for ( int  i = word_length ; i ; --i, new_dividend_bits >>= 1 )
            crc_modulo_update<Bits>( remainder, new_dividend_bits & 1u,
             truncated_divisor );

        // Note that the quotient isn't stored, since you usually won't need it,
        // and calculating it slows you down.  If you want it, just do this loop
        // manually.  Start with Word: Quotient := 0, then for each step do:
        //   Quotient <- (Quotient << 1) | crc_modulo_update(...)
    }


    // CRC table generator
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    struct crc_table_t
    {
        BOOST_STATIC_CONSTANT( std::size_t, byte_combos = (1ul << CHAR_BIT) );

        typedef typename boost::uint_t<Bits>::fast  value_type;
#if defined(__BORLANDC__) && defined(_M_IX86) && (__BORLANDC__ == 0x560)
        // for some reason Borland's command line compiler (version 0x560)
        // chokes over this unless we do the calculation for it:
        typedef value_type                   table_type[ 0x100 ];
#elif defined(__GNUC__)
        // old versions of GCC (before 4.0.2) choke on using byte_combos
        // as a constant expression when compiling with -pedantic.
        typedef value_type                   table_type[1ul << CHAR_BIT];
#else
        typedef value_type                   table_type[ byte_combos ];
#endif

        static  void  init_table();

        static  table_type  table_;

    };  // boost::detail::crc_table_t

    // CRC table generator static data member definition
    // (Some compilers [Borland C++] require the initializer to be present.)
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    typename crc_table_t<Bits, TruncPoly, Reflect>::table_type
    crc_table_t<Bits, TruncPoly, Reflect>::table_
     = { 0 };

    // Populate CRC lookup table
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    void
    crc_table_t<Bits, TruncPoly, Reflect>::init_table
    (
    )
    {
        // compute table only on the first run
        static  bool  did_init = false;
        if ( did_init )  return;

        // Loop over every possible dividend value
        for ( boost::uint_t<CHAR_BIT + 1>::fast  dividend = 0u ; dividend <=
         UCHAR_MAX ; ++dividend )
        {
            value_type  remainder = 0u;

            crc_modulo_word_update<Bits>( remainder, dividend, TruncPoly,
             CHAR_BIT, false );

            table_[ reflect_byte_optionally(dividend, Reflect) ]
             = reflect_optionally( remainder, Reflect, Bits );
        }

        did_init = true;
    }

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    // Align the msb of the remainder to a byte
    template < std::size_t Bits, bool RightShift >
    class remainder
    {
    public:
        typedef typename uint_t<Bits>::fast  value_type;

        static unsigned char align_msb( value_type rem )
            { return rem >> (Bits - CHAR_BIT); }
    };

    // Specialization for the case that the remainder has less
    // bits than a byte: align the remainder msb to the byte msb
    template < std::size_t Bits >
    class remainder< Bits, false >
    {
    public:
        typedef typename uint_t<Bits>::fast  value_type;

        static unsigned char align_msb( value_type rem )
            { return rem << (CHAR_BIT - Bits); }
    };
    #endif

    // CRC helper routines
    template < std::size_t Bits, bool DoReflect >
    class crc_helper
    {
    public:
        // Type
        typedef typename uint_t<Bits>::fast  value_type;

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return reflect_unsigned(x, Bits); }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ rem; }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return rem >> CHAR_BIT; }
    #else
        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return DoReflect ? reflect_unsigned(x, Bits) : x; }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ ( DoReflect ? rem :
                                ((Bits>CHAR_BIT)?( rem >> (Bits - CHAR_BIT) ) :
                                    ( rem << (CHAR_BIT - Bits) ))); }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return DoReflect ? rem >> CHAR_BIT : rem << CHAR_BIT; }
    #endif

    };  // boost::detail::crc_helper

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template < std::size_t Bits >
    class crc_helper<Bits, false>
    {
    public:
        // Type
        typedef typename uint_t<Bits>::fast  value_type;

        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return x; }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ remainder<Bits,(Bits>CHAR_BIT)>::align_msb( rem ); }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return rem << CHAR_BIT; }

    };  // boost::detail::crc_helper
    #endif


}  // namespace detail
//! \endcond


//  Simple CRC class function definitions  -----------------------------------//

/** Constructs a \c crc_basic object with at least the required parameters to a
    particular CRC formula to be processed upon receiving input.

    \param[in] truncated_polynominal  The lowest coefficients of the divisor
      polynomial.  The highest-order coefficient is omitted and always assumed
      to be 1.  (\e Poly from the RMCA)
    \param[in] initial_remainder  The (unaugmented) initial state of the
      polynomial remainder.  Defaults to \c 0 if omitted.  (\e Init from the
      RMCA)
    \param[in] final_xor_value  The (XOR) bit-mask to be applied to the output
      remainder, after possible reflection but before returning.  Defaults to
      \c 0 (i.e. no bit changes) if omitted.  (\e XorOut from the RMCA)
    \param[in] reflect_input  If \c true, input bytes are read lowest-order bit
      first, otherwise highest-order bit first.  Defaults to \c false if
      omitted.  (\e RefIn from the RMCA)
    \param[in] reflect_remainder  If \c true, the output remainder is reflected
      before the XOR-mask.  Defaults to \c false if omitted.  (\e RefOut from
      the RMCA)

    \post  <code><var>truncated_polynominal</var> ==
      this-&gt;get_truncated_polynominal()</code>
    \post  <code><var>initial_remainder</var> ==
      this-&gt;get_initial_remainder()</code>
    \post  <code><var>final_xor_value</var> ==
      this-&gt;get_final_xor_value()</code>
    \post  <code><var>reflect_input</var> ==
      this-&gt;get_reflect_input()</code>
    \post  <code><var>reflect_remainder</var> ==
      this-&gt;get_reflect_remainder()</code>
    \post  <code><var>initial_remainder</var> ==
      this-&gt;get_interim_remainder()</code>
    \post  <code>(<var>reflect_remainder</var> ?
      REFLECT(<var>initial_remainder</var>) : <var>initial_remainder</var>) ^
      <var>final_xor_value</var> == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
crc_basic<Bits>::crc_basic
(
    typename crc_basic<Bits>::value_type  truncated_polynominal,
    typename crc_basic<Bits>::value_type  initial_remainder,      // = 0
    typename crc_basic<Bits>::value_type  final_xor_value,        // = 0
    bool                                  reflect_input,          // = false
    bool                                  reflect_remainder       // = false
)
    : rem_( initial_remainder ), poly_( truncated_polynominal )
    , init_( initial_remainder ), final_( final_xor_value )
    , rft_in_( reflect_input ), rft_out_( reflect_remainder )
{
}

/** Returns a representation of the polynomial divisor.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.  The omitted bit for x<sup>#bit_count</sup> is always 1.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored (even any for x<sup>#bit_count</sup>) since they're unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_truncated_polynominal
(
) const
{
    return poly_;
}

/** Returns a representation of the polynomial remainder before any input has
    been submitted.  The value of the 2<sup>i</sup> bit is the value of the
    coefficient of the polynomial's x<sup>i</sup> term.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored since they're unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_initial_remainder
(
) const
{
    return init_;
}

/** Returns the mask to be used during creation of a checksum.  The mask is used
    for an exclusive-or (XOR) operation applied bit-wise to the interim
    remainder representation (after any reflection, if #get_reflect_remainder()
    returns \c true).

    \return  The bit-mask.  If the bit-length of #value_type exceeds #bit_count,
      the values of higher-placed bits should be ignored since they're
      unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_final_xor_value
(
) const
{
    return final_;
}

/** Returns a whether or not a submitted byte will be \"reflected\" before it is
    used to update the interim remainder.  Only the byte-wise operations
    #process_byte, #process_block, and #process_bytes are affected.

    \retval true  Input bytes will be read starting from the lowest-order bit.
    \retval false  Input bytes will be read starting from the highest-order bit.
 */
template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_input
(
) const
{
    return rft_in_;
}

/** Indicates if the interim remainder will be \"reflected\" before it is passed
    to the XOR-mask stage when returning a checksum.

    \retval true  The interim remainder is reflected before further work.
    \retval false  The interim remainder is applied to the XOR-mask as-is.
 */
template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_remainder
(
) const
{
    return rft_out_;
}

/** Returns a representation of the polynomial remainder after all the input
    submissions since construction or the last #reset call.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.  If CRC processing gets interrupted here, retain the
    value returned, and use it to start up the next CRC computer where you left
    off (with #reset(value_type) or construction).  The next computer has to
    have its other parameters compatible with this computer.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored since they're unregulated.  No output processing (reflection or
      XOR mask) has been applied to the value.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_interim_remainder
(
) const
{
    return rem_ & detail::low_bits_mask_c<Bits>::value;
}

/** Changes the interim polynomial remainder to \a new_rem, purging any
    influence previously submitted input has had.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.

    \param[in] new_rem  The (unaugmented) state of the polynomial remainder
      starting from this point, with no output processing applied.

    \post  <code><var>new_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(<var>new_rem</var>) : <var>new_rem</var>) ^
      this-&gt;get_final_xor_value()) == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
    typename crc_basic<Bits>::value_type  new_rem
)
{
    rem_ = new_rem;
}

/** Changes the interim polynomial remainder to the initial remainder given
    during construction, purging any influence previously submitted input has
    had.  The value of the 2<sup>i</sup> bit is the value of the coefficient of
    the polynomial's x<sup>i</sup> term.

    \post  <code>this-&gt;get_initial_remainder() ==
      this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_initial_remainder()) :
      this-&gt;get_initial_remainder()) ^ this-&gt;get_final_xor_value())
      == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
)
{
    this->reset( this->get_initial_remainder() );
}

/** Updates the interim remainder with a single altered-CRC-division step.

    \param[in] bit  The new input bit.

    \post  The interim remainder is updated though a modulo-2 polynomial
      division, where the division steps are altered for unaugmented CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bit
(
    bool  bit
)
{
    detail::crc_modulo_update<Bits>( rem_, bit, poly_ );
}

/** Updates the interim remainder with several altered-CRC-division steps.  Each
    bit is processed separately, starting from the one at the
    2<sup><var>bit_count</var> - 1</sup> place, then proceeding down to the
    lowest-placed bit.  Any order imposed by
    <code>this-&gt;get_reflect_input()</code> is ignored.

    \pre  0 \< \a bit_count \<= \c CHAR_BIT

    \param[in] bits  The byte containing the new input bits.
    \param[in] bit_count  The number of bits in the byte to be read.

    \post  The interim remainder is updated though \a bit_count modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.
 */
template < std::size_t Bits >
void
crc_basic<Bits>::process_bits
(
    unsigned char  bits,
    std::size_t    bit_count
)
{
    // ignore the bits above the ones we want
    bits <<= CHAR_BIT - bit_count;

    // compute the CRC for each bit, starting with the upper ones
    unsigned char const  high_bit_mask = 1u << ( CHAR_BIT - 1u );
    for ( std::size_t i = bit_count ; i > 0u ; --i, bits <<= 1u )
    {
        process_bit( static_cast<bool>(bits & high_bit_mask) );
    }
}

/** Updates the interim remainder with a byte's worth of altered-CRC-division
    steps.  The bits within the byte are processed from the highest place down
    if <code>this-&gt;get_reflect_input()</code> is \c false, and lowest place
    up otherwise.

    \param[in] byte  The new input byte.

    \post  The interim remainder is updated though \c CHAR_BIT modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_byte
(
    unsigned char  byte
)
{
    process_bits( (rft_in_ ? detail::reflect_byte( byte ) : byte), CHAR_BIT );
}

/** Updates the interim remainder with several bytes' worth of
    altered-CRC-division steps.  The bits within each byte are processed from
    the highest place down if <code>this-&gt;get_reflect_input()</code> is
    \c false, and lowest place up otherwise.  The bytes themselves are processed
    starting from the one pointed by \a bytes_begin until \a bytes_end is
    reached through forward iteration, treating the two pointers as if they
    point to <code>unsigned char</code> objects.

    \pre  \a bytes_end has to equal \a bytes_begin if the latter is \c NULL or
      otherwise doesn't point to a valid buffer.
    \pre  \a bytes_end, if not equal to \a bytes_begin, has to point within or
      one-byte-past the same buffer \a bytes_begin points into.
    \pre  \a bytes_end has to be reachable from \a bytes_begin through a finite
      number of forward byte-pointer increments.

    \param[in] bytes_begin  The address where the memory block begins.
    \param[in] bytes_end  Points to one-byte past the address of the memory
      block's last byte, or \a bytes_begin if no bytes are to be read.

    \post  The interim remainder is updated though <code>CHAR_BIT * (((unsigned
      char const *) bytes_end) - ((unsigned char const *) bytes_begin))</code>
      modulo-2 polynomial divisions, where the division steps are altered for
      unaugmented CRCs.
 */
template < std::size_t Bits >
void
crc_basic<Bits>::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    for ( unsigned char const * p
     = static_cast<unsigned char const *>(bytes_begin) ; p < bytes_end ; ++p )
    {
        process_byte( *p );
    }
}

/** Updates the interim remainder with several bytes' worth of
    altered-CRC-division steps.  The bits within each byte are processed from
    the highest place down if <code>this-&gt;get_reflect_input()</code> is
    \c false, and lowest place up otherwise.  The bytes themselves are processed
    starting from the one pointed by \a buffer, forward-iterated (as if the
    pointed-to objects were of <code>unsigned char<code>) until \a byte_count
    bytes are read.

    \pre  \a byte_count has to equal 0 if \a buffer is \c NULL or otherwise
      doesn't point to valid memory.
    \pre  If \a buffer points within valid memory, then that block has to have
      at least \a byte_count more valid bytes allocated from that point.

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.

    \post  The interim remainder is updated though <code>CHAR_BIT *
      <var>byte_count</var></code> modulo-2 polynomial divisions, where the
      division steps are altered for unaugmented CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bytes
(
    void const *  buffer,
    std::size_t   byte_count
)
{
    unsigned char const * const  b = static_cast<unsigned char const *>(
     buffer );

    process_block( b, b + byte_count );
}

/** Computes the checksum of all the submitted bits since construction or the
    last call to #reset.  The checksum will be the raw checksum, i.e. the
    (interim) remainder after all the modulo-2 polynomial division, plus any
    output processing.

    \return  <code>(this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_interim_remainder()) :
      this-&gt;get_interim_remainder()) ^ this-&gt;get_final_xor_value()</code>

    \note  Since checksums are meant to be compared, any higher-placed bits
      (when the bit-length of #value_type exceeds #bit_count) will be set to 0.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::checksum
(
) const
{
    return ( (rft_out_ ? detail::reflect_unsigned( rem_, Bits ) :
     rem_) ^ final_ ) & detail::low_bits_mask_c<Bits>::value;
}


//  Optimized CRC class function definitions  --------------------------------//

// Macro to compact code
#define BOOST_CRC_OPTIMAL_NAME  crc_optimal<Bits, TruncPoly, InitRem, \
 FinalXor, ReflectIn, ReflectRem>

/** Constructs a \c crc_optimal object with a particular CRC formula to be
    processed upon receiving input.  The initial remainder may be overridden.

    \param[in] init_rem  The (unaugmented) initial state of the polynomial
      remainder.  Defaults to #initial_remainder if omitted.

    \post  <code>#truncated_polynominal ==
      this-&gt;get_truncated_polynominal()</code>
    \post  <code>#initial_remainder == this-&gt;get_initial_remainder()</code>
    \post  <code>#final_xor_value == this-&gt;get_final_xor_value()</code>
    \post  <code>#reflect_input == this-&gt;get_reflect_input()</code>
    \post  <code>#reflect_remainder == this-&gt;get_reflect_remainder()</code>
    \post  <code><var>init_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>(#reflect_remainder ? REFLECT(<var>init_rem</var>) :
      <var>init_rem</var>) ^ #final_xor_value == this-&gt;checksum()</code>
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
BOOST_CRC_OPTIMAL_NAME::crc_optimal
(
    typename BOOST_CRC_OPTIMAL_NAME::value_type  init_rem  // = InitRem
)
    : rem_( helper_type::reflect(init_rem) )
{
    crc_table_type::init_table();
}

//! \copydetails  boost::crc_basic::get_truncated_polynominal
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_truncated_polynominal
(
) const
{
    return TruncPoly;
}

//! \copydetails  boost::crc_basic::get_initial_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_initial_remainder
(
) const
{
    return InitRem;
}

//! \copydetails  boost::crc_basic::get_final_xor_value
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_final_xor_value
(
) const
{
    return FinalXor;
}

//! \copydetails  boost::crc_basic::get_reflect_input
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_input
(
) const
{
    return ReflectIn;
}

//! \copydetails  boost::crc_basic::get_reflect_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_remainder
(
) const
{
    return ReflectRem;
}

//! \copydetails  boost::crc_basic::get_interim_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_interim_remainder
(
) const
{
    // Interim remainder should be _un_-reflected, so we have to undo it.
    return helper_type::reflect( rem_ ) & detail::low_bits_mask_c<Bits>::value;
}

/** Changes the interim polynomial remainder to \a new_rem, purging any
    influence previously submitted input has had.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.

    \param[in] new_rem  The (unaugmented) state of the polynomial remainder
      starting from this point, with no output processing applied.  Defaults to
      <code>this-&gt;get_initial_remainder()</code> if omitted.

    \post  <code><var>new_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(<var>new_rem</var>) : <var>new_rem</var>) ^
      this-&gt;get_final_xor_value()) == this-&gt;checksum()</code>
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::reset
(
    typename BOOST_CRC_OPTIMAL_NAME::value_type  new_rem  // = InitRem
)
{
    rem_ = helper_type::reflect( new_rem );
}

/** \copydetails  boost::crc_basic::process_byte

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_byte
(
    unsigned char  byte
)
{
    process_bytes( &byte, sizeof(byte) );
}

/** \copydetails  boost::crc_basic::process_block

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
void
BOOST_CRC_OPTIMAL_NAME::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    // Recompute the CRC for each byte passed
    for ( unsigned char const * p
     = static_cast<unsigned char const *>(bytes_begin) ; p < bytes_end ; ++p )
    {
        // Compare the new byte with the remainder's higher bits to
        // get the new bits, shift out the remainder's current higher
        // bits, and update the remainder with the polynominal division
        // of the new bits.
        unsigned char const  byte_index = helper_type::index( rem_, *p );
        rem_ = helper_type::shift( rem_ );
        rem_ ^= crc_table_type::table_[ byte_index ];
    }
}

/** \copydetails  boost::crc_basic::process_bytes

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_bytes
(
    void const *   buffer,
    std::size_t  byte_count
)
{
    unsigned char const * const  b = static_cast<unsigned char const *>(
     buffer );
    process_block( b, b + byte_count );
}

//! \copydetails  boost::crc_basic::checksum
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::checksum
(
) const
{
    return ( reflect_out_type::reflect(rem_) ^ get_final_xor_value() )
     & detail::low_bits_mask_c<Bits>::value;
}

/** Updates the interim remainder with a byte's worth of altered-CRC-division
    steps.  The bits within the byte are processed from the highest place down
    if <code>this-&gt;get_reflect_input()</code> is \c false, and lowest place
    up otherwise.  This function is meant to present a function-object interface
    to code that wants to process a stream of bytes with
    <code>std::for_each</code> or similar range-processing algorithms.  Since
    some of these algorithms takes their function object by value, make sure to
    copy back the result to this object so the updates can be remembered.

    \param[in] byte  The new input byte.

    \post  The interim remainder is updated though \c CHAR_BIT modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::operator ()
(
    unsigned char  byte
)
{
    process_byte( byte );
}

/** Computes the checksum of all the submitted bits since construction or the
    last call to #reset.  The checksum will be the raw checksum, i.e. the
    (interim) remainder after all the modulo-2 polynomial division, plus any
    output processing.  This function is meant to present a function-object
    interface to code that wants to receive data like
    <code>std::generate_n</code> or similar data-processing algorithms.  Note
    that if this object is used as a generator multiple times without an
    intervening mutating operation, the same value will always be returned.

    \return  <code>(this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_interim_remainder()) :
      this-&gt;get_interim_remainder()) ^ this-&gt;get_final_xor_value()</code>

    \note  Since checksums are meant to be compared, any higher-placed bits
      (when the bit-length of #value_type exceeds #bit_count) will be set to 0.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::operator ()
(
) const
{
    return checksum();
}


//  CRC computation function definition  -------------------------------------//

/** Computes the polynomial remainder of a CRC run, assuming that \a buffer and
    \a byte_count describe a memory block representing the polynomial dividend.
    The division steps are altered so the result directly gives a checksum,
    without need to augment the memory block with scratch-space bytes.  The
    first byte is considered the highest order, going down for subsequent bytes.

    \pre  0 \< \a Bits \<= \c std::numeric_limits&lt;uintmax_t&gt;::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.
      (\e Poly from the RMCA)
    \tparam InitRem  The (unaugmented) initial state of the polynomial
      remainder.  (\e Init from the RMCA)
    \tparam FinalXor  The (XOR) bit-mask to be applied to the output remainder,
      after possible reflection but before returning.  (\e XorOut from the RMCA)
    \tparam ReflectIn  If \c True, input bytes are read lowest-order bit first,
      otherwise highest-order bit first.  (\e RefIn from the RMCA)
    \tparam ReflectRem  If \c True, the output remainder is reflected before the
      XOR-mask.  (\e RefOut from the RMCA)

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.

    \return  The checksum, which is the last (interim) remainder plus any output
      processing.

    \note  Unaugmented-style CRC runs perform modulo-2 polynomial division in
      an altered order.  The trailing \a Bits number of zero-valued bits needed
      to extracted an (unprocessed) checksum is virtually moved to near the
      beginning of the message.  This is OK since the XOR operation is
      commutative and associative.  It also means that you can get a checksum
      anytime.  Since data is being read byte-wise, a table of pre-computed
      remainder changes (as XOR masks) can be used to speed computation.

 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename uint_t<Bits>::fast
crc
(
    void const *  buffer,
    std::size_t   byte_count
    BOOST_CRC_DUMMY_INIT
)
{
    BOOST_CRC_OPTIMAL_NAME  computer;
    computer.process_bytes( buffer, byte_count );
    return computer.checksum();
}


//  Augmented-message CRC computation function definition  -------------------//

/** Computes the polynomial remainder of a CRC run, assuming that \a buffer and
    \a byte_count describe a memory block representing the polynomial dividend.
    The first byte is considered the highest order, going down for subsequent
    bytes.  Within a byte, the highest-order bit is read first (corresponding to
    \e RefIn = \c False in the RMCA).  Check the other parts of this function's
    documentation to see how a checksum can be gained and/or used.

    \pre  0 \< \a Bits \<= \c std::numeric_limits&lt;uintmax_t&gt;::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.
      (\e Poly from the RMCA)

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.
    \param[in] initial_remainder  The initial state of the polynomial
      remainder, defaulting to zero if omitted.  If you are reading a memory
      block in multiple runs, put the return value of the previous run here.
      (Note that initial-remainders given by RMCA parameter lists, as
      \e Init, assume that the initial remainder is in its \b unaugmented state,
      so you would need to convert the value to make it suitable for this
      function.  I currently don't provide a conversion routine.)

    \return  The interim remainder, if no augmentation is used.  A special value
      if augmentation is used (see the notes).  No output processing is done on
      the value.  (In RMCA terms, \e RefOut is \c False and \e XorOut is \c 0.)

    \note  Augmented-style CRC runs use straight-up modulo-2 polynomial
      division.  Since data is being read byte-wise, a table of pre-computed
      remainder changes (as XOR masks) can be used to speed computation.
    \note  Reading just a memory block will yield an interim remainder, and not
      the final checksum.  To get that checksum, allocate \a Bits / \c CHAR_BIT
      bytes directly after the block and fill them with zero values, then extend
      \a byte_count to include those extra bytes.  A data block is corrupt if
      the return value doesn't equal your separately given checksum.
    \note  Another way to perform a check is use the zero-byte extension method,
      but replace the zero values with your separately-given checksum.  The
      checksum must be loaded in big-endian order.  Here corruption, in either
      the data block or the given checksum, is confirmed if the return value is
      not zero.
    \note  The two checksum techniques assume the CRC-run is performed bit-wise,
      while this function works byte-wise.  That means that the techniques can
      be used only if \c CHAR_BIT divides \a Bits evenly!
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
typename uint_t<Bits>::fast
augmented_crc
(
    void const *                 buffer,
    std::size_t                  byte_count,
    typename uint_t<Bits>::fast  initial_remainder  // = 0u
    BOOST_ACRC_DUMMY_INIT
)
{
    typedef unsigned char                                byte_type;
    typedef detail::crc_table_t<Bits, TruncPoly, false>  crc_table_type;

    typename uint_t<Bits>::fast  rem = initial_remainder;
    byte_type const * const      b = static_cast<byte_type const *>( buffer );
    byte_type const * const      e = b + byte_count;

    crc_table_type::init_table();
    for ( byte_type const * p = b ; p < e ; ++p )
    {
        // Use the current top byte as the table index to the next
        // "partial product."  Shift out that top byte, shifting in
        // the next augmented-message byte.  Complete the division.
        byte_type const  byte_index = rem >> ( Bits - CHAR_BIT );
        rem <<= CHAR_BIT;
        rem |= *p;
        rem ^= crc_table_type::table_[ byte_index ];
    }

    return rem & detail::low_bits_mask_c<Bits>::value;
}


}  // namespace boost


// Undo header-private macros
#undef BOOST_CRC_OPTIMAL_NAME
#undef BOOST_ACRC_DUMMY_INIT
#undef BOOST_ACRC_DUMMY_PARM_TYPE
#undef BOOST_CRC_DUMMY_INIT
#undef BOOST_CRC_DUMMY_PARM_TYPE
#undef BOOST_CRC_PARM_TYPE


#endif  // BOOST_CRC_HPP

