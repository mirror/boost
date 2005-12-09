++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

Class ``ptr_multimap_adapter``
------------------------------

This class is used to build custom pointer containers with
an underlying multimap-like container. The interface of the class is an extension
of the interface from ``associative_ptr_container``.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_multimap_
- `new map iterators`__

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_multimap: ptr_multimap.html
__ ptr_container.html#map-iterator-operations

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_

**Synopsis:**

.. parsed-literal::

                     
        namespace boost
        {
            template
            < 
                T,
                class VoidPtrMultiMap,
                class CloneAllocator = heap_clone_allocator 
            >
            class ptr_multimap_adapter 
            {
                
            public: // `modifiers`_         
                iterator  insert( key_type& k, T* x );                         

            public: // `pointer container requirements`_
                void      transfer( iterator object, ptr_multimap_adapter& from );
                size_type transfer( iterator first, iterator last, ptr_multimap_adapter& from );
                template< class Range >
                size_type transfer( const Range& r, ptr_multimap_adapter& from );
                void      transfer( ptr_multimap_adapter& from );

            }; //  class 'ptr_multimap_adapter'
        
        } // namespace 'boost'  

            
Semantics
---------

.. _`modifiers`:

Semantics: modifiers
^^^^^^^^^^^^^^^^^^^^

- ``iterator insert( key_type& k, T* x );``

    - Requirements: ``x != 0``

    - Effects: Takes ownership of ``x`` and returns an iterator pointing to it.

    - Throws: bad_pointer if ``x == 0``

    - Exception safety: Strong guarantee


.. 
        - ``iterator insert( key_type& k, const_reference x );``
    
        - Effects: ``return insert( allocate_clone( x ) );``
    
        - Exception safety: Strong guarantee


.. _`lookup`: 

..
        Semantics: lookup
        ^^^^^^^^^^^^^^^^^
        
        - ``reference        operator[]( const Key& key );``
        - ``const_reference  operator[]( const Key& key ) const;``
        
            - Requirements: the key exists
        
            - Effects: returns the object with key ``key``
        
            - Throws: ``bad_ptr_container_operation`` if the key does not exist                                 

.. _`pointer container requirements`:
        
Semantics: pointer container requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- ``void transfer( iterator object, ptr_multimap_adapter& from );``

   - Requirements: ``not from.empty()``

   - Effects: Inserts the object defined by ``object`` into the container and remove it from ``from``. 

   - Postconditions: ``size()`` is one more, ``from.size()`` is one less.

   - Exception safety: Strong guarantee

- ``void transfer( iterator first, iterator last, ptr_multimap_adapter& from );``

   - Requirements: ``not from.empty()``

   - Effects: Inserts the objects defined by the range ``[first,last)`` into the container and remove it from ``from``.

   - Postconditions: Let ``N == std::distance(first,last);`` then ``size()`` is ``N`` more, ``from.size()`` is ``N`` less.
              
   - Exception safety: Basic guarantee

- ``template< class Range > void transfer( const Range& r, ptr_multimap_adapter& from );``

    - Effects: ``transfer( boost::begin(r), boost::end(r), from );``

- ``void transfer( ptr_multimap_adapter& from );``

   - Effects: ``transfer( from.begin(), from.end(), from );``.

   - Postconditions: ``from.empty();``

   - Exception safety: Basic guarantee
 

:copyright:     Thorsten Ottosen 2004-2005. 

