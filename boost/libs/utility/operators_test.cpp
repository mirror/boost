//  Demonstrate and test boost/operators.hpp  -------------------------------//

//  (C) Copyright Beman Dawes 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  04 Jun 00 Added regression test for a bug I found (David Abrahams)
//  17 Jun 00 Fix for broken compilers (Aleksey Gurtovoy)
//  ?? ??? 00 Major update to randomly test all one- and two- argument forms by
//            wrapping integral types and comparing the results of operations to
//            the results for the raw types (David Abrahams)
//  12 Dec 99 Minor update, output confirmation message.
//  15 Nov 99 Initial version

#include <boost/operators.hpp>
#include <cassert>
#include <iostream>
#include <boost/min_rand.hpp>


namespace
{
    // avoiding a template version of true_value so as to not confuse VC++
    int true_value(int x) { return x; }
    long true_value(long x) { return x; }
    signed char true_value(signed char x) { return x; }
    unsigned int true_value(unsigned int x) { return x; }
    unsigned long true_value(unsigned long x) { return x; }
    unsigned char true_value(unsigned char x) { return x; }

    // The use of operators<> here tended to obscure interactions with certain
    // compiler bugs
    template <class T>
    class Wrapped1 : boost::operators<Wrapped1<T> >
    {
    public:
        explicit Wrapped1( T v = T() ) : _value(v) {}
        T value() const { return _value; }

        bool operator<(const Wrapped1& x) const { return _value < x._value; }
        bool operator==(const Wrapped1& x) const { return _value == x._value; }
        
        Wrapped1& operator+=(const Wrapped1& x)
          { _value += x._value; return *this; }
        Wrapped1& operator-=(const Wrapped1& x)
          { _value -= x._value; return *this; }
        Wrapped1& operator*=(const Wrapped1& x)
          { _value *= x._value; return *this; }
        Wrapped1& operator/=(const Wrapped1& x)
          { _value /= x._value; return *this; }
        Wrapped1& operator%=(const Wrapped1& x)
          { _value %= x._value; return *this; }
        Wrapped1& operator|=(const Wrapped1& x)
          { _value |= x._value; return *this; }
        Wrapped1& operator&=(const Wrapped1& x)
          { _value &= x._value; return *this; }
        Wrapped1& operator^=(const Wrapped1& x)
          { _value ^= x._value; return *this; }
        Wrapped1& operator++()               { ++_value; return *this; }
        Wrapped1& operator--()               { --_value; return *this; }
        
    private:
        T _value;
    };
    template <class T>
    T true_value(Wrapped1<T> x) { return x.value(); }    

    template <class T, class U>
    class Wrapped2 :
        boost::operators<Wrapped2<T, U> >,
        boost::operators2<Wrapped2<T, U>, U>
    {
    public:
        explicit Wrapped2( T v = T() ) : _value(v) {}
        T value() const { return _value; }

        bool operator<(const Wrapped2& x) const { return _value < x._value; }
        bool operator==(const Wrapped2& x) const { return _value == x._value; }
        
        Wrapped2& operator+=(const Wrapped2& x)
          { _value += x._value; return *this; }
        Wrapped2& operator-=(const Wrapped2& x)
          { _value -= x._value; return *this; }
        Wrapped2& operator*=(const Wrapped2& x)
          { _value *= x._value; return *this; }
        Wrapped2& operator/=(const Wrapped2& x)
          { _value /= x._value; return *this; }
        Wrapped2& operator%=(const Wrapped2& x)
          { _value %= x._value; return *this; }
        Wrapped2& operator|=(const Wrapped2& x)
          { _value |= x._value; return *this; }
        Wrapped2& operator&=(const Wrapped2& x)
          { _value &= x._value; return *this; }
        Wrapped2& operator^=(const Wrapped2& x)
          { _value ^= x._value; return *this; }
        Wrapped2& operator++()                { ++_value; return *this; }
        Wrapped2& operator--()                { --_value; return *this; }
         
        bool operator<(U u) const { return _value < u; }
        bool operator>(U u) const { return _value > u; }
        bool operator==(U u) const { return _value == u; }
        Wrapped2& operator+=(U u) { _value += u; return *this; }
        Wrapped2& operator-=(U u) { _value -= u; return *this; }
        Wrapped2& operator*=(U u) { _value *= u; return *this; }
        Wrapped2& operator/=(U u) { _value /= u; return *this; }
        Wrapped2& operator%=(U u) { _value %= u; return *this; }
        Wrapped2& operator|=(U u) { _value |= u; return *this; }
        Wrapped2& operator&=(U u) { _value &= u; return *this; }
        Wrapped2& operator^=(U u) { _value ^= u; return *this; }

    private:
        T _value;
    };
    template <class T, class U>
    T true_value(Wrapped2<T,U> x) { return x.value(); }
    
    //  MyInt uses only the single template-argument form of all_operators<>
    typedef Wrapped1<int> MyInt;

    typedef Wrapped2<long, long> MyLong;

    template <class X1, class Y1, class X2, class Y2>
    void sanity_check(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert(true_value(y1) == true_value(y2));
        assert(true_value(x1) == true_value(x2));
    }

    template <class X1, class Y1, class X2, class Y2>
    void test_less_than_comparable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 < y1) == (x2 < y2));
        assert((x1 <= y1) == (x2 <= y2));
        assert((x1 >= y1) == (x2 >= y2));
        assert((x1 > y1) == (x2 > y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_less_than_comparable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_less_than_comparable_aux(x1, y1, x2, y2);
        test_less_than_comparable_aux(y1, x1, y2, x2);
    }

    template <class X1, class Y1, class X2, class Y2>
    void test_equality_comparable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 == y1) == (x2 == y2));
        assert((x1 != y1) == (x2 != y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_equality_comparable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_equality_comparable_aux(x1, y1, x2, y2);
        test_equality_comparable_aux(y1, x1, y2, x2);
    }

    template <class X1, class Y1, class X2, class Y2>
    void test_multipliable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 * y1).value() == (x2 * y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_multipliable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_multipliable_aux(x1, y1, x2, y2);
        test_multipliable_aux(y1, x1, y2, x2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_addable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 + y1).value() == (x2 + y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_addable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_addable_aux(x1, y1, x2, y2);
        test_addable_aux(y1, x1, y2, x2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_subtractable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        assert((x1 - y1).value() == x2 - y2);
    }

    template <class X1, class Y1, class X2, class Y2>
    void test_dividable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        if (y2 != 0)
            assert((x1 / y1).value() == x2 / y2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_modable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        if (y2 != 0)
            assert((x1 / y1).value() == x2 / y2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_xorable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 ^ y1).value() == (x2 ^ y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_xorable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_xorable_aux(x1, y1, x2, y2);
        test_xorable_aux(y1, x1, y2, x2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_andable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 & y1).value() == (x2 & y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_andable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_andable_aux(x1, y1, x2, y2);
        test_andable_aux(y1, x1, y2, x2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_orable_aux(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        assert((x1 | y1).value() == (x2 | y2));
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_orable(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        sanity_check(x1, y1, x2, y2);
        test_orable_aux(x1, y1, x2, y2);
        test_orable_aux(y1, x1, y2, x2);
    }
    
    template <class X1, class X2>
    void test_incrementable(X1 x1, X2 x2)
    {
        sanity_check(x1, x1, x2, x2);
        assert(x1++.value() == x2++);
        assert(x1.value() == x2);
    }
    
    template <class X1, class X2>
    void test_decrementable(X1 x1, X2 x2)
    {
        sanity_check(x1, x1, x2, x2);
        assert(x1--.value() == x2--);
        assert(x1.value() == x2);
    }
    
    template <class X1, class Y1, class X2, class Y2>
    void test_all(X1 x1, Y1 y1, X2 x2, Y2 y2)
    {
        test_less_than_comparable(x1, y1, x2, y2);
        test_equality_comparable(x1, y1, x2, y2);
        test_multipliable(x1, y1, x2, y2);
        test_addable(x1, y1, x2, y2);
        test_subtractable(x1, y1, x2, y2);
        test_dividable(x1, y1, x2, y2);
        test_modable(x1, y1, x2, y2);
        test_xorable(x1, y1, x2, y2);
        test_andable(x1, y1, x2, y2);
        test_orable(x1, y1, x2, y2);
        test_incrementable(x1, x2);
        test_decrementable(x1, x2);
    }
    
    template <class Big, class Small>
    struct tester
    {
        void operator()(boost::min_rand& randomizer) const
        {
            Big b1 = Big(randomizer());
            Big b2 = Big(randomizer());
            Small s = Small(randomizer());
            
            test_all(Wrapped1<Big>(b1), Wrapped1<Big>(b2), b1, b2);
            test_all(Wrapped2<Big, Small>(b1), s, b1, s);
        }
    };

    // added as a regression test. We had a bug which this uncovered.
    struct Point
        : boost::addable<Point,
        boost::subtractable<Point> >
    {
        Point( int h, int v ) : h(h), v(v) {}
        Point() :h(0), v(0) {}
        const Point& operator+=( const Point& rhs ) { h += rhs.h; v += rhs.v; return *this; }
        const Point& operator-=( const Point& rhs ) { h -= rhs.h; v -= rhs.v; return *this; }

        int h;
        int v;
    };
} // unnamed namespace


// workaround for MSVC bug; for some reasons the compiler doesn't instantiate
// inherited operator templates at the moment it must, so the following
// explicit instantiations force it to do that.

#if defined(BOOST_MSVC) && (_MSC_VER <= 1200)
template Wrapped1<int>;
template Wrapped1<long>;
template Wrapped1<unsigned int>;
template Wrapped1<unsigned long>;

template Wrapped2<int, int>;
template Wrapped2<int, signed char>;
template Wrapped2<long, signed char>;
template Wrapped2<long, int>;
template Wrapped2<long, long>;
template Wrapped2<unsigned int, unsigned int>;
template Wrapped2<unsigned int, unsigned char>;
template Wrapped2<unsigned long, unsigned int>;
template Wrapped2<unsigned long, unsigned char>;
template Wrapped2<unsigned long, unsigned long>;
#endif

#ifdef NDEBUG
#error This program is pointless when NDEBUG disables assert()!
#endif

int main()
{
    // Regression test.
    Point x;
    x = x + Point(3, 4);
    x = x - Point(3, 4);
    
    for (int n = 0; n < 10000; ++n)
    {
        boost::min_rand r;
        tester<long, int>()(r);
        tester<long, signed char>()(r);
        tester<long, long>()(r);
        tester<int, int>()(r);
        tester<int, signed char>()(r);
        
        tester<unsigned long, unsigned int>()(r);
        tester<unsigned long, unsigned char>()(r);
        tester<unsigned long, unsigned long>()(r);
        tester<unsigned int, unsigned int>()(r);
        tester<unsigned int, unsigned char>()(r);
    }
    
    MyInt i1(1);
    MyInt i2(2);
    MyInt i;

    assert( i1.value() == 1 );
    assert( i2.value() == 2 );
    assert( i.value() == 0 );

    i = i2;
    assert( i.value() == 2 );
    assert( i2 == i );
    assert( i1 != i2 );
    assert( i1 <  i2 );
    assert( i1 <= i2 );
    assert( i <= i2 );
    assert( i2 >  i1 );
    assert( i2 >= i1 );
    assert( i2 >= i );

    i = i1 + i2; assert( i.value() == 3 );
    i = i + i2; assert( i.value() == 5 );
    i = i - i1; assert( i.value() == 4 );
    i = i * i2; assert( i.value() == 8 );
    i = i / i2; assert( i.value() == 4 );
    i = i % (i - i1); assert( i.value() == 1 );
    i = i2 + i2; assert( i.value() == 4 );
    i = i1 | i2 | i; assert( i.value() == 7 );
    i = i & i2; assert( i.value() == 2 );
    i = i + i1; assert( i.value() == 3 );
    i = i ^ i1; assert( i.value() == 2 );
    i = (i+i1)*(i2|i1); assert( i.value() == 9 );
    
    MyLong j1(1);
    MyLong j2(2);
    MyLong j;

    assert( j1.value() == 1 );
    assert( j2.value() == 2 );
    assert( j.value() == 0 );

    j = j2;
    assert( j.value() == 2 );
    
    assert( j2 == j );
    assert( 2 == j );
    assert( j2 == 2 );    
    assert( j == j2 );
    assert( j1 != j2 );
    assert( j1 != 2 );
    assert( 1 != j2 );
    assert( j1 <  j2 );
    assert( 1 <  j2 );
    assert( j1 <  2 );
    assert( j1 <= j2 );
    assert( 1 <= j2 );
    assert( j1 <= j );
    assert( j <= j2 );
    assert( 2 <= j2 );
    assert( j <= 2 );
    assert( j2 >  j1 );
    assert( 2 >  j1 );
    assert( j2 >  1 );
    assert( j2 >= j1 );
    assert( 2 >= j1 );
    assert( j2 >= 1 );
    assert( j2 >= j );
    assert( 2 >= j );
    assert( j2 >= 2 );

    assert( (j1 + 2) == 3 );
    assert( (1 + j2) == 3 );
    j = j1 + j2; assert( j.value() == 3 );
    
    assert( (j + 2) == 5 );
    assert( (3 + j2) == 5 );
    j = j + j2; assert( j.value() == 5 );
    
    assert( (j - 1) == 4 );
    j = j - j1; assert( j.value() == 4 );
    
    assert( (j * 2) == 8 );
    assert( (4 * j2) == 8 );
    j = j * j2; assert( j.value() == 8 );
    
    assert( (j / 2) == 4 );
    j = j / j2; assert( j.value() == 4 );
    
    assert( (j % 3) == 1 );
    j = j % (j - j1); assert( j.value() == 1 );
    
    j = j2 + j2; assert( j.value() == 4 );
    
    assert( (1 | j2 | j) == 7 );
    assert( (j1 | 2 | j) == 7 );
    assert( (j1 | j2 | 4) == 7 );
    j = j1 | j2 | j; assert( j.value() == 7 );
    
    assert( (7 & j2) == 2 );
    assert( (j & 2) == 2 );
    j = j & j2; assert( j.value() == 2 );
    
    j = j | j1; assert( j.value() == 3 );
    
    assert( (3 ^ j1) == 2 );
    assert( (j ^ 1) == 2 );
    j = j ^ j1; assert( j.value() == 2 );
    
    j = (j+j1)*(j2|j1); assert( j.value() == 9 );
    
    std::cout << "0 errors detected\n";
    return 0;
}
