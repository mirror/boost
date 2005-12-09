++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: boost.png

Class ``ptr_set``
-----------------

A ``ptr_set<T>`` is a pointer container that uses an underlying ``std::set<void*>``
to store the pointers.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_set_adapter_
- `void_ptr_indirect_fun <indirect_fun.html>`_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_set_adapter: ptr_set_adapter.html

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
                class Compare        = std::less<Key>, 
                class CloneAllocator = heap_clone_allocator, 
                class Allocator      = std::allocator<void*>
            >
            class ptr_set : public  ptr_set_adapter
                                    <
                                        Key,
                                        std::set<void*,
                                        void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                        CloneAllocator
                                    >
            {
                // see references
                
            }; //  class 'ptr_set'
        
        } // namespace 'boost'  

**Remarks:**

- Using ``nullable<T>`` as ``Key`` is meaningless and not allowed


:copyright:     Thorsten Ottosen 2004-2005. 

