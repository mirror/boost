::

  template <
      class Incrementable
    , unsigned Access = use_default_access
    , class Traversal = use_default
    , class Difference = use_default
  >
  class counting_iterator
    : public iterator_adaptor<
          counting_iterator<Incrementable, Access, Traversal, Difference>
        , Incrementable
        , Incrementable
        , Access
        , /* see details for traversal category */
        , Incrementable const&
        , Incrementable const*
        , /* distance = Difference or a signed integral type */>
  {
      friend class iterator_core_access;
   public:
      counting_iterator();
      counting_iterator(counting_iterator const& rhs);
      counting_iterator(Incrementable x);
   private:
      typename counting_iterator::reference dereference() const
      {
          return this->base_reference();
      }
    };


[*Note:* implementers are encouraged to provide an implementation of
  ``distance_to`` and a ``difference_type`` that avoids overflows in
  the cases when the ``Incrementable`` type is a numeric type.]

``counting_iterator`` requirements
----------------------------------

The ``Incrementable`` type must be Default Constructible, Copy
Constructible, and Assignable.  The default distance is
an implementation defined signed integegral type.

The resulting ``counting_iterator`` models Readable Lvalue Iterator.

Furthermore, if you wish to create a counting iterator that is a Forward
Traversal Iterator, then the following expressions must be valid:
::

    Incrementable i, j;
    ++i         // pre-increment
    i == j      // operator equal

If you wish to create a counting iterator that is a 
Bidirectional Traversal Iterator, then pre-decrement is also required:
::

    --i

If you wish to create a counting iterator that is a Random Access
Traversal Iterator, then these additional expressions are also
required:
::

    counting_iterator::difference_type n;
    i += n
    n = i - j
    i < j




``counting_iterator`` operations
--------------------------------

``counting_iterator();``

:Returns: A default constructed instance of ``counting_iterator``.


``counting_iterator(counting_iterator const& rhs);``

:Returns: An instance of ``counting_iterator`` that is a copy of ``rhs``.



``counting_iterator(Incrementable x);``

:Returns: An instance of ``counting_iterator`` with its base
    object copy constructed from ``x``.

