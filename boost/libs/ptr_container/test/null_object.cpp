
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/null_object.hpp>
#include <boost/assert.hpp>
#include <boost/progress.hpp>
#include <string>
#include <exception>
#include <iostream>


class animal
{
    virtual std::string do_speak() const = 0;
    std::string name_;

protected:
    //
    // Animals cannot be copied...
    //
    animal( const animal& r ) : name_( r.name_ )           { }
    void operator=( const animal& );

private:
    //
    // ...but due to advances in genetics, we can clone them!
    //

    virtual animal* do_clone() const = 0;
        
public:
    animal() : name_("")                                   { }
    animal( const std::string& name ) : name_(name)        { }
    virtual ~animal()                                      { }
    
    std::string speak() const
    {
        return do_speak();
    }

    std::string name() const
    {
        return name_;
    }

    animal* clone() const
    {
        return do_clone();
    }

    bool is_null() const;
};

animal* allocate_clone( const animal& a )
{
    return a.clone();
}

//
// Define a null object with just about zero overhead.
// No matter how many null objects you have, you will always
// share the same static instance.
//
// This class must always be a leaf class, hence you should never derive
// from it.
//

class null_animal : public boost::null_object<animal,null_animal>
{
    virtual std::string do_speak() const { return ""; }
    virtual animal*     do_clone() const { return new null_animal; }
};

inline bool animal::is_null() const
{
    return this == &null_animal::null_instance;
}


template< class T >
inline bool is_null( T& r )
{
    // &r == is_null<T>::instance()?
}



const std::string muuuh = "Muuuh!";
const std::string oiink = "Oiiink";

class cow : public animal
{
    virtual std::string do_speak() const
    {
        return muuuh;
    }

    virtual animal* do_clone() const
    {
        return new cow( *this );
    }

public:
    cow( const std::string& name ) : animal(name)          { }
};

class pig : public animal
{
    virtual std::string do_speak() const
    {
        return oiink;
    }

    virtual animal* do_clone() const
    {
        return new pig( *this );
    }
    
public:
    pig( const std::string& name ) : animal(name)          { }
};


int main()
{
    typedef boost::ptr_deque<animal> farm_t;
    farm_t farm;
    farm.push_back( new null_animal );
    farm.push_back( new pig("foo") );
    farm.push_back( new null_animal );
    farm.push_back( new cow("bar") );
    farm.push_back( new null_animal );

    for( farm_t::iterator i = farm.begin(), e = farm.end();
         i != e; ++i )
    {
        std::cout << i->name() << " says " << i->speak();
    }

    farm_t farm2( farm.begin(), farm.end() );
   
    for( farm_t::iterator i = farm2.begin(), e = farm2.end();
         i != e; ++i )
    {
        std::cout << i->name() << " says " << i->speak();
    }

    const int count = 1000000;
    typedef std::deque<animal*> ptr_deque;
    
    {
        ptr_deque d;
        d.push_back( 0 );
        d.push_back( new pig("foo") );
        d.push_back( 0 );
        d.push_back( new cow("bar") );
        d.push_back( 0 );

        boost::progress_timer timer;
        for( int i = 0; i != count; ++i )
            for( ptr_deque::iterator i = d.begin(), e = d.end();
                 i != e;
                 ++i )
            {
                if( *i )
                {
                    ( *i )->name();
                    ( *i )->speak();
                }
            }
    }

    {
        boost::progress_timer timer;

        for( int i = 0; i != count; ++i )    
            for( farm_t::iterator i = farm2.begin(), e = farm2.end();
                 i != e; ++i )
            {
                i->name();
                i->speak();
            }
    }

    {
        ptr_deque d;
        d.push_back( 0 );
        d.push_back( new pig("foo") );
        d.push_back( new cow("foo bar") );
        d.push_back( new cow("bar") );
        d.push_back( 0 );

        boost::progress_timer timer;
        for( int i = 0; i != count; ++i )
            for( ptr_deque::iterator i = d.begin(), e = d.end();
                 i != e;
                 ++i )
            {
                if( *i )
                {
                    ( *i )->name();
                    ( *i )->speak();
                }
            }
    }

    {
        ptr_deque d;
        d.push_back( 0 );
        d.push_back( new pig("foo") );
        d.push_back( new cow("foo bar") );
        d.push_back( new pig("bar") );
        d.push_back( new cow("barbar") );

        boost::progress_timer timer;
        for( int i = 0; i != count; ++i )
            for( ptr_deque::iterator i = d.begin(), e = d.end();
                 i != e;
                 ++i )
            {
                if( *i )
                {
                    ( *i )->name();
                    ( *i )->speak();
                }
            }
    }

    {
        boost::progress_timer timer;

        for( int i = 0; i != count; ++i )    
            for( farm_t::iterator i = farm2.begin(), e = farm2.end();
                 i != e; ++i )
            {
                if( !i->is_null() )
                {
                    i->name();
                    i->speak();
                }
            }
    }

}
