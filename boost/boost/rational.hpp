//  Boost rational.hpp header file  ------------------------------------------//

//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Credits:
//  Thanks to the boost mailing list in general for useful comments.
//  Particular contributions included:
//    Andrew D Jewell, for reminding me to take care to avoid overflow
//    Ed Brey, for many comments, including picking up on some dreadful typos

//  Revision History
//  19 Nov 00  Throw on divide by zero in operator /= (John (EBo) David)
//  23 Jun 00  Incorporate changes from Mark Rodgers for Borland C++
//  22 Jun 00  Change _MSC_VER to BOOST_MSVC so other compilers are not
//             affected (Beman Dawes)
//   6 Mar 00  Fix operator-= normalization, #include <string> (Jens Maurer) 
//  14 Dec 99  Modifications based on comments from the boost list
//  09 Dec 99  Initial Version (Paul Moore)

#ifndef BOOST_RATIONAL_HPP
#define BOOST_RATIONAL_HPP

#include <iostream>             // for std::istream and std::ostream
#include <stdexcept>            // for std::domain_error
#include <string>               // for std::string implicit constructor
#include <boost/operators.hpp>  // for boost::addable etc
#include <cstdlib>              // for std::abs
#include <boost/config.hpp>     // for BOOST_NO_STDC_NAMESPACE, BOOST_MSVC

namespace boost {

template <typename IntType>
IntType gcd(IntType n, IntType m)
{
    while (m) {
        IntType r = n % m;
        if (r < 0)
            r += m;

        n = m;
        m = r;
    }

    return n;
}

template <typename IntType>
IntType lcm(IntType n, IntType m)
{
    n /= gcd(n, m);
    n *= m;
    return n;
}

class bad_rational : public std::domain_error
{
public:
    explicit bad_rational() : std::domain_error("bad rational: zero denominator") {}
};

// The following is an awful lot of code to implement a 1-line abs() function.

#ifdef BOOST_MSVC
// This is a gross hack. MS Visual C++ has utterly broken namespace reslution
// rules. Basically, the call to abs(int) in abs(rational) below will not find
// ::abs(). So the only way we have of fixing this is to reimplement std::abs
// in the boost:: namespace! In practice, this is a relatively minor bit of
// pollution, so we should be OK.

inline int abs(int n) { return ::abs(n); }
inline long abs(long n) { return ::labs(n); }

#endif

template <typename IntType>
class rational;

template <typename IntType>
rational<IntType> abs(const rational<IntType>& r);

template <typename IntType>
class rational :
    less_than_comparable < rational<IntType> >,
    equality_comparable < rational<IntType> >,
    addable < rational<IntType> >,
    subtractable < rational<IntType> >,
    multipliable < rational<IntType> >,
    dividable < rational<IntType> >,
    incrementable < rational<IntType> >,
    decrementable < rational<IntType> >
{
    typedef IntType int_type;

public:
    rational(IntType n = 0) : num(n), den(1) {}
    rational(IntType n, IntType d) : num(n), den(d) { normalize(); }

    // Default copy constructor and assignment are fine

    // Assign in place
    rational& assign(IntType n, IntType d);

    // Access to representation
    IntType numerator() const { return num; }
    IntType denominator() const { return den; }

    // Arithmetic assignment operators
    rational& operator+= (const rational& r);
    rational& operator-= (const rational& r);
    rational& operator*= (const rational& r);
    rational& operator/= (const rational& r);

    // Increment and decrement
    const rational& operator++();
    const rational& operator--();

    // Comparison operators
    bool operator< (const rational& r) const;
    bool operator== (const rational& r) const;

private:
    // Implementation - numerator and denominator (normalized).
    // Other possibilities - separate whole-part, or sign, fields?
    IntType num;
    IntType den;

    // Representation note: Fractions are kept in normalized form at all
    // times. normalized form is defined as gcd(num,den) == 1 and den > 0.
    // In particular, note that the implementation of abs() below relies
    // on den always being positive.
    void normalize();
};

// Assign in place
template <typename IntType>
inline rational<IntType>& rational<IntType>::assign(IntType n, IntType d)
{
    num = n;
    den = d;
    normalize();
    return *this;
}

// Unary plus and minus
template <typename IntType>
inline rational<IntType> operator+ (const rational<IntType>& r)
{
    return r;
}

template <typename IntType>
inline rational<IntType> operator- (const rational<IntType>& r)
{
    return rational<IntType>(-r.numerator(), r.denominator());
}

// Arithmetic assignment operators
template <typename IntType>
rational<IntType>& rational<IntType>::operator+= (const rational<IntType>& r)
{
    // This calculation avoids overflow
    IntType new_den = lcm(den, r.den);
    num = num * (new_den / den) + r.num * (new_den / r.den);
    den = new_den;
    normalize(); // Example where this is needed: 1/2 + 1/2
    return *this;
}

template <typename IntType>
rational<IntType>& rational<IntType>::operator-= (const rational<IntType>& r)
{
    // This calculation avoids overflow
    IntType new_den = lcm(den, r.den);
    num = num * (new_den / den) - r.num * (new_den / r.den);
    den = new_den;
    normalize(); // Example where this is needed: 1/2 + 1/2
    return *this;
}

template <typename IntType>
rational<IntType>& rational<IntType>::operator*= (const rational<IntType>& r)
{
    // Avoid overflow and preserve normalization
    IntType gcd1 = gcd<IntType>(num, r.den);
    IntType gcd2 = gcd<IntType>(r.num, den);
    num = (num/gcd1) * (r.num/gcd2);
    den = (den/gcd2) * (r.den/gcd1);
    return *this;
}

template <typename IntType>
rational<IntType>& rational<IntType>::operator/= (const rational<IntType>& r)
{
    // Trap division by zero
    if (r.num == 0) throw bad_rational();
    // Avoid overflow and preserve normalization
    IntType gcd1 = gcd<IntType>(num, r.num);
    IntType gcd2 = gcd<IntType>(r.den, den);
    num = (num/gcd1) * (r.den/gcd2);
    den = (den/gcd2) * (r.num/gcd1);
    return *this;
}

// Increment and decrement
template <typename IntType>
inline const rational<IntType>& rational<IntType>::operator++()
{
    // This can never denormalise the fraction
    num += den;
    return *this;
}

template <typename IntType>
inline const rational<IntType>& rational<IntType>::operator--()
{
    // This can never denormalise the fraction
    num -= den;
    return *this;
}

// Comparison operators
template <typename IntType>
bool rational<IntType>::operator< (const rational<IntType>& r) const
{
    // Avoid overflow
    IntType gcd1 = gcd<IntType>(num, r.num);
    IntType gcd2 = gcd<IntType>(r.den, den);
    return (num/gcd1) * (r.den/gcd2) < (den/gcd2) * (r.num/gcd1);
}

template <typename IntType>
inline bool rational<IntType>::operator== (const rational<IntType>& r) const
{
    return ((num == r.num) && (den == r.den));
}

// Normalisation
template <typename IntType>
void rational<IntType>::normalize()
{
    if (den == 0)
        throw bad_rational();

    IntType g = gcd<IntType>(num, den);

    num /= g;
    den /= g;

    if (den < 0) {
        num = -num;
        den = -den;
    }
}

// Input and output
template <typename IntType>
std::istream& operator>> (std::istream& is, rational<IntType>& r)
{
    IntType n = 0, d = 1;
    char c = 0;

    is >> n;
    c = is.get();

    if (c == '/')
        is >> d;
    else
        is.putback(c);

    if (is)
        r.assign(n, d);

    return is;
}

// Add manipulators for output format?
template <typename IntType>
std::ostream& operator<< (std::ostream& os, const rational<IntType>& r)
{
    os << r.numerator() << '/' << r.denominator();
    return os;
}

// Type conversion
template <typename T, typename IntType>
inline T rational_cast(const rational<IntType>& src)
{
    return static_cast<T>(src.numerator())/src.denominator();
}

#ifdef __GNUC__
// Workaround for a bug in gcc 2.95.2 - using statements at function scope are
// silently ignored - to get around this, we need to include std::abs at
// namespace scope.

using std::abs;
#endif

template <typename IntType>
inline rational<IntType> abs(const rational<IntType>& r)
{
#if !defined(BOOST_NO_STDC_NAMESPACE) && !defined(BOOST_MSVC)
    // We want to use abs() unadorned below, so that if IntType is a
    // user-defined type, the name lookup rules will work to find an
    // appropriate abs() defined for IntType.
    //
    // We protect this with BOOST_NO_STDC_NAMESPACE, as some compilers
    // don't put abs into std:: (notably MS Visual C++) and so we can't
    // "use" it from there.
    using std::abs;
#endif
    // Note that with normalized fractions, the denominator is always positive.
    return rational<IntType>(abs(r.numerator()), r.denominator());
}

} // namespace boost

#endif  // BOOST_RATIONAL_HPP

