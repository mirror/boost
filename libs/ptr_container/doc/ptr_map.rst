++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

Class ``ptr_map``
-----------------

A ``ptr_map<Key,T>`` is a pointer container that uses an underlying ``std::map<Key,void*>``
to store the pointers.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_map_adapter_
- `new map iterators <reference.html#map-iterator-operations>`_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_map_adapter: ptr_map_adapter.html
.. class `indirect_fun <indirect_fun.html>`_
 

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_


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
            class ptr_map : public ptr_map_adapter
                                   <
                                       T,
                                       std::map<Key,void*,Compare,Allocator>,
                                       CloneAllocator
                                   >
            {
                // see references
                
            }; //  class 'ptr_map'
        
        } // namespace 'boost'  


:copyright:     Thorsten Ottosen 2004-2005. 

