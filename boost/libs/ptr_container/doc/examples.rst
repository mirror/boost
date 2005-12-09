++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

========
Examples
========

Some examples are given here and in the accompanying test files:

.. contents:: :local: 


.. _`Example 1`:

1. Null pointers cannot be stored in the containers 
+++++++++++++++++++++++++++++++++++++++++++++++++++

::

        my_container.push_back( 0 );            // throws bad_ptr 
        my_container.replace( an_iterator, 0 ); // throws bad_ptr
        my_container.insert( an_iterator, 0 );  // throws bad_ptr                                                                 

.. _`Example 2`:

2. Iterators and other operations return indirected values 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:: 

        ptr_vector<X> pvec; 
        std::vector<X*> vec;
        *vec.begin()  = new X;   // fine, memory leak
        *pvec.begin() = new X;   // compile time error
        ( *vec.begin() )->foo(); // call X::foo(), a bit clumsy
        pvec.begin()->foo();     // no indirection needed
        *vec.front()  = X();     // overwrite first element
        pvec.front()  = X();     // no indirection needed


.. _`Example 3`:

3. Copy-semantics of pointer containers
+++++++++++++++++++++++++++++++++++++++

::

        ptr_vector<T> vec1; 
        ...
        ptr_vector<T> vec2( vec1.clone() ); // deep copy objects of 'vec1' and use them to construct 'vec2', could be very expensive
        vec2 = vec1.release();              // give up ownership of pointers in 'vec1' and pass the ownership to 'vec2', rather cheap
        vec2.release();                     // give up ownership; the objects will be deallocated if not assigned to another container
        vec1 = vec2;                        // compile time error: 'operator=()' not defined 
        ptr_vector<T> vec3( vec1 );         // compile time error: copy-constructor not defined 


.. _`Example 4`:

4. Making a non-copyable type Clonable
++++++++++++++++++++++++++++++++++++++

::
        
         // a class that has no normal copy semantics
        class X : boost::noncopyable { public: X* clone() const; ... };
                                                                           
        // this will be found by the library by argument dependent lookup                                                                   
        X* new_clone( const X& x ) 
        { return x.clone(); }
                                                                           
        // we can now use the interface that requires clonability
        ptr_vector<X> vec1, vec2;
        ...
        vec2 = vec1.clone();                                 // 'clone()' requires cloning <g> 
        vec2.insert( vec2.end(), vec1.begin(), vec1.end() ); // inserting always means inserting clones 


.. _`Example 5`:

5. Objects are cloned before insertion, inserted pointers are owned by the container 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::

        class X { ... };                     // assume 'X' is Clonable 
        X x;                                 // and 'X' can be stack-allocated 
        ptr_list<X> list; 
        list.push_back( x );                 // clone 'x' and then insert the resulting pointer 
        list.push_back( new_clone( x );      // do it manually
        list.push_back( new X );             // always give the pointer directly to the container to avoid leaks
        list.push_back( &x );                // don't do this!!! 


.. _`Example 6`:

6. Transferring ownership of a single element 
+++++++++++++++++++++++++++++++++++++++++++++

::

        ptr_deque<T>                    deq; 
        typedef ptr_deque<T>::auto_type auto_type;
        
        // ... fill the container somehow
        
        auto_type ptr  = deq.release_back();             // remove back element from container and give up ownership
        auto_type ptr2 = deq.release( deq.begin() + 2 ); // use an iterator to determine the element to release
        ptr            = deq.release_front();            // supported for 'ptr_list' and 'ptr_deque'
                                        


.. _`Example 7`:

7. Transferring ownership of pointers between different pointer containers 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::


        ptr_list<X> list; ptr_vector<X> vec;
        ...
        //
        // note: no cloning happens in these examples                                
        //
        list.transfer( list.begin(), vec.begin(), vec );           // make the first element of 'vec' the first element of 'list'
        vec.transfer( vec.end(), list.begin(), list.end(), list ); // put all the lists element into the vector                                 
                                

.. _`Example 8`:



8. Selected test files 
++++++++++++++++++++++

:incomplete_type_test.cpp_: Shows how to implement the Composite pattern.
:simple_test.cpp_: Shows how the usage of pointer container compares with a 
  container of pointer pointers
:view_example.cpp_: Shows how to use a pointer container as a view into other container
:tree_test.cpp_: Shows how to make a tree-structure
:array_test.cpp_: Shows how to make an n-ary tree 

.. _incomplete_type_test.cpp : ../test/incomplete_type_test.cpp
.. _simple_test.cpp : ../test/simple_test.cpp
.. _view_example.cpp : ../test/view_example.cpp
.. _tree_test.cpp : ../test/tree_test.cpp
.. _array_test.cpp : ../test/ptr_array.cpp


..
		9. A large example
		++++++++++++++++++

		This examples shows many of the most common
		features at work.

		.. raw:: html
			:file: tut1.html

		10. Changing the Clone Allocator
		++++++++++++++++++++++++++++++++

		This example shows how we can change 
		the Clone Allocator to use the pointer containers
		as view into other containers:

		.. raw:: html
			:file: tut2.html

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_

:copyright:     Thorsten Ottosen 2004-2005. 

