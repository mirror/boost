 
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/config.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

using namespace std;
using namespace boost;

//////////////////////////////////////////////////////////////////////////////
// Test class 1: a class hierarchy
//////////////////////////////////////////////////////////////////////////////

class Base
{
    Base( const Base& r ) : data1(r.data1), data2(r.data2), 
        data3(r.data3), data(r.data) 
    { }
    
    Base& operator=( const Base& );
    int data1, data2, data3;
    string data;
    
public:
    
    Base() : data1(1), data2(2), data3(rand()%256), 
             data(lexical_cast<string>(rand())) {}
    virtual ~Base()                       { /** write debug code here */ }
    void     print( ostream& out ) const  { do_print( out); }
    Base*    clone() const                { return do_clone(); }
    void     foo()                        { do_foo(); }
    
    virtual bool less_than( const Base& b ) const
    {
        return true;
    }
    
    virtual bool equal( const Base& b ) const
    {
        return this == &b ;
    }

    bool data_less_than( const Base& b ) const
    {
        return data1 == b.data1 && data2 == b.data2 && data3 < b.data3;
    }

    bool data_less_than2( const Base& b ) const
    {
        return data_less_than(b) && data < b.data;
    }
    
private:
    virtual void  do_print( ostream& out ) const   { };
    virtual Base* do_clone() const                 { return new Base( *this ); }; 
    virtual void  do_foo()                         { };
};



ostream& operator<<( ostream& out, Base& b )
{
    b.print( out );
    return out;
}


//
//  We rely on argument dependent lookup
//  for this to be found
//
Base* new_clone( const Base& b )
{
    return b.clone();
}



bool operator<( const Base& l, const Base& r )
{
    return l.less_than( r );
}



bool operator>( const Base& l, const Base& r )
{
    return !l.less_than( r ) && r.less_than( l );
}



bool operator==( const Base& l, const Base& r )
{
    return l.equal( r );
}



bool operator!=( const Base& l, const Base& r )
{
    return !l.equal( r );
}



class Derived : public Base
{   
    int i_;
        
    virtual void  do_print( ostream& out ) const
    {
        out << i_;
    }
    
    
    virtual Base* do_clone() const
    {
        return new Derived;
    }
    
    virtual void do_foo() 
    {
        ++i_;
    }
    
public:
    Derived() : i_( rand() )
    { }

    virtual bool less_than( const Base& b ) const
    {
        const Derived& d = dynamic_cast<const Derived&>( b );
        return i_ < d.i_;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Test class 2: a value class 
//////////////////////////////////////////////////////////////////////////////

class Value 
{   
    string s_;
    
public:
    
    Value() : s_( boost::lexical_cast<string>( rand() ) ) 
    {}
    
    ~Value()      { /** debug code here */ }
    
    string name() const
    {
        return s_;
    }
};



bool operator<( const Value& l, const Value& r )
{
    return l.name() < r.name();
}



bool operator>( const Value& l, const Value& r )
{
    return l.name() > r.name();
}



bool operator==( const Value& l, const Value& r )
{
    return l.name() == r.name();
}



bool operator!=( const Value& l, const Value& r )
{
    return l.name() != r.name();
}



ostream& operator<<( ostream& out, const Value& v )
{
    return out << v.name() << " ";
}



