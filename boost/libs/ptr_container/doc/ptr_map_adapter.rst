++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

Class ``ptr_map_adapter``
-------------------------

This class is used to build custom pointer containers with
an underlying map-like container. The interface of the class is an extension
of the interface from ``associative_ptr_container``.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_map_
- `new map iterators <reference.html#map-iterator-operations>`_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_map: ptr_map.html

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_

**Synopsis:**

.. parsed-literal::

                     
        namespace boost
        {
            template
            < 
                class T,
                class VoidPtrMap, 
                class CloneAllocator = heap_clone_allocator 
            >
            class ptr_map_adapter 
            {
                
            public: // `modifiers`_         
                std::pair<iterator,bool>  insert( key_type& k, value_type x );                         

            public; // `lookup`_
                T&       operator[]( const key_type& key );
                T&       at( const key_type& key );
                const T& at( const key_type& key ) const;
                
            public: // `pointer container requirements`_
                bool      transfer( iterator object, ptr_map_adapter& from );
                size_type transfer( iterator first, iterator last, ptr_map_adapter& from );
                template< class Range >
                size_type transfer( const Range& r, ptr_map_adapter& from );
                size_type transfer( ptr_map_adapter& from );
                    
            }; //  class 'ptr_map_adapter'
        
        } // namespace 'boost'  

            
Semantics
---------

.. _`modifiers`:

Semantics: modifiers
^^^^^^^^^^^^^^^^^^^^

- ``std::pair<iterator,bool> insert( key_type& k, value_type x );``

    - Requirements: ``x != 0``

    - Effects: Takes ownership of ``x`` and insert it iff there is no equivalent of it already. The bool part of the return value indicates insertion and the iterator points to the element with key ``x``.

    - Throws: bad_pointer if ``x == 0``

    - Exception safety: Strong guarantee


..
        - ``std::pair<iterator,bool> insert( key_type& k, const_reference x );``
    
        - Effects: ``return insert( allocate_clone( x ) );``
    
        - Exception safety: Strong guarantee


.. _`lookup`: 

Semantics: lookup
^^^^^^^^^^^^^^^^^

- ``T& operator[]( const key_type& key );``

    - Effects: returns the object with key ``key`` if it exists; otherwise a new object is allocated and inserted and its reference returned.
    - Exception-safety: Strong guarantee           

- ``T&       at( const key_type& key );``
- ``const T& at( const key_type& jey ) const;``

    - Requirement: the key exists
    - Throws: ``bad_ptr_container_operation`` if the key does not exist                                 

.. _`pointer container requirements`:

Semantics: pointer container requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- ``bool transfer( iterator object, ptr_map_adapter& from );``

   - Requirements: ``not from.empty()``

   - Effects: Inserts the object defined by ``object`` into the container and remove it from ``from`` 
     iff no equivalent object exists.

   - Returns: whether the object was transfered
   
   - Exception safety: Strong guarantee

- ``size_type transfer( iterator first, iterator last, ptr__set_adapter& from );``

   - Requirements: ``not from.empty()``

   - Effects: Inserts the objects defined by the range ``[first,last)`` into the container and remove it from ``from``.
     An object is only transferred if no equivalent object exists. 

   - Returns: the number of transfered objects
              
   - Exception safety: Basic guarantee

- ``template< class Range > void transfer( const Range& r, ptr_map_adapter& from );``

    - Effects: ``return transfer( boost::begin(r), boost::end(r), from );``
                   
- ``size_type transfer( ptr_set_adapter& from );``

   - Effects: ``return transfer( from.begin(), from.end(), from );``.

 
:copyright:     Thorsten Ottosen 2004-2005. 

