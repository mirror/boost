
#include "test_data.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/progress.hpp>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <vector>

//
// This example uses an idiom that makes it possible to override functions in base classes without
// using virtual functions. Hence the name Non-Virtual Virtual Functions Idiom. The 
// idiom has these tradeoffs:
// Pro:
//      1. fast
//      2. no vtable space overhead
//      3. allows "virtual" functions templates
//
// Con:
//      1. limited to one layer of derivation
//      2. no run-time type-switching possible
//      3. not very flexible
//
// We shall compare it with a traditional way of doing it that uses virtual functions and a container
// of smart-pointers.
//

namespace slow
{
    class xml_node;

    class xml_tree
    { 
    public:
        typedef boost::shared_ptr< xml_node > node_ptr;
        typedef std::vector< node_ptr >       nodes_t;

    private:
        nodes_t nodes;            
         
    public:
        void            add( xml_node* n );
        void            write_tree( ostream& os ) const;
        size_t          size() const;
    };
    
    
    class xml_node 
    {
        virtual size_t  do_size() const = 0;
        virtual string  do_description() const = 0;
              
    public:
        virtual  ~xml_node()                       { }
        size_t   size() const                      { return do_size(); }
        string   description() const               { return do_description(); }
    };
    
} // namespace 'slow'

namespace fast
{

    class xml_node;
    
    class xml_tree
    { 
        typedef boost::ptr_vector<xml_node> nodes_t;
        nodes_t nodes; 
        
    public:

             
    public:
        void            add( xml_node* n );
        void            write_tree( ostream& os ) const;
        size_t          size() const;
    };
    
    
    enum derive_classes 
    {
        simple,
        complex
    };
    
    class xml_node_base
    {
    public:
        
    };
    
    class xml_node 
    {
        void* self_; // store pointer derived class
        
        xml_node();
        xml_node( const xml_node& );
        void operator=( const xml_node& );
        ~xml_node() // forward, substitute for virtual desructor        
        {
            switch( derived_classes )
            {
                case simple: delete (simple_node*)self_; break;
                case complex: delete (complex_node*)self_; break;
                default: BOOST_ASSERT( false );
            }
        }
        friend void ::operator delete( void* );  // only allow heap objects or references
    public:

        xml_node( void* self ) : self_( self )     { }
        size_t   size() const                      { return self_->size(); }        // forward
        string   description() const               { return self_->description(); } // forward
    };

} // namespace 'fast'


/*
template< class T >
class inner_node : public node, public tree
{
    T t_;

    virtual size_t  do_size() const = 0;
    virtual string  do_description() const = 0;
    virtual void    do_write_value( ostream& os ) const = 0;
    
public:
    inner_node() 
    {
    }
};
 


template< class T >
class leaf : public node
{
    T t_;
    
    virtual size_t  do_size() const = 0;
    virtual string  do_description() const = 0;
    virtual void    do_write_value( ostream& os ) const = 0;
public:
    leaf()
    {
    }
};
*/

void test_tree()
{
}



#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Smart Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_tree ) );

    return test;
}


