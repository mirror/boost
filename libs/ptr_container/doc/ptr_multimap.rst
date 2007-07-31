++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

Class ``ptr_multimap``
----------------------

A ``ptr_multimap<Key,T>`` is a pointer container that uses an underlying ``std::multimap<Key,void*>``
to store the pointers.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_multimap_adapter_
- `new map iterators <reference.html#map-iterator-operations>`_

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_multimap_adapter: ptr_multimap_adapter.html



**Synopsis:**

.. parsed-literal::

                     
        namespace boost
        {
            template
            < 
                class Key, 
                class T, 
                class Compare        = std::less<Key>,
                class CloneAllocator = heap_clone_allocator,
                class Allocator      = std::allocator< std::pair<const Key,void*> >
            >
            class ptr_multimap : public ptr_multimap_adapter
                                        <
                                            T,
                                            std::multimap<Key,void*,Compare,Allocator>,
                                            CloneAllocator
                                        >
            {
                // see references
                
            }; //  class 'ptr_multimap'
        
        } // namespace 'boost'  


:copyright:     Thorsten Ottosen 2004-2005. 

