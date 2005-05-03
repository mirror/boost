++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: cboost.gif

Class ``ptr_multiset``
----------------------

A ``ptr_multiset<T>`` is a pointer container that uses an underlying ``std::multiset<void*>``
to store the pointers.

**See also:**

- reversible_ptr_container_
- associative_ptr_container_
- ptr_multiset_adapter_
- `void_ptr_indirect_fun <indirect_fun.html>`_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _associative_ptr_container: associative_ptr_container.html
.. _ptr_multiset_adapter: ptr_multiset_adapter.html
.. _`indirect predicates`: indirect_fun.html 

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
            class ptr_multiset : public ptr_multiset_adapter
                                        <
                                            Key,
                                            std::multiset<void*,void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                            CloneAllocator
                                        >
            {
                // see references
                
            }; //  class 'ptr_multiset'
        
        } // namespace 'boost'  

**Remarks:**

- Using ``nullable<T>`` as ``Key`` is meaningless and not allowed


:copyright:     Thorsten Ottosen 2004-2005. 

