::

  template <
      class Iterator
    , class Value = use_default
    , class CategoryOrTraversal = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
  {
   public:
      typedef /* see below */ value_type;
      typedef /* see below */ reference;
      typedef /* see below */ pointer;
      typedef /* see below */ difference_type;
      typedef /* see below */ iterator_category;

      indirect_iterator();
      indirect_iterator(Iterator x);

      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
      );
  };

  template <class Dereferenceable>
  struct referent {
    /* see below */
  };


The member types of ``indirect_iterator`` are defined according to the
following pseudo-code.  We use the abbreviation
``V=iterator_traits<Iterator>::value_type`` and ``v`` is an object of
type ``V``.::

  if (Value is use_default) then
      if (referent<V> has member type) then
          typedef remove_const<referent<V>::type> value_type;
      else
          typedef iterator_traits<V>::value_type value_type;
  else
      typedef remove_const<Value>::type value_type;

  if (Reference is use_default) then
      if (Value is use_default) then
         if (referent<V> has member type) then
            typedef referent<V>::type& reference;
         else
            typedef iterator_traits<V>::value_type& reference;
      else
          typedef Value& reference;
  else
      typedef Reference reference;

  if (Value is use_default) then
     if (referent<V> has member type) then
	typedef referent<V>::type* pointer;
     else
	typedef iterator_traits<V>::value_type* pointer;
  else
      typedef Value* pointer;

  if (Difference is use_default)
      typedef iterator_traits<Iterator>::difference_type difference_type;
  else
      typedef Difference difference_type;


The member ``indirect_iterator::iterator_category`` is a type that
satisfies the requirements of the concepts modeled by the indirect
iterator as specified in the following requirements section.
(Should replace this with detailed description. -JGS)

If the ``Dereferenceable`` template argument to ``referent`` is a
class and has member ``element_type`` then ``referent`` 
contains the following typedef::

    typedef Dereferenceable::element_type type;


``indirect_iterator`` requirements
..................................

The ``CategoryOrTraversal`` argument shall be one of the standard
iterator tags or ``use_default``. If ``CategoryOrTraversal`` is an
iterator tag, the template parameter ``Iterator`` argument shall meet
the traversal requirements corresponding to the iterator tag and the
requirements of Readable Iterator and ``indirect_iterator`` satisfies
the requirements corresponding to the iterator tag.  If
``CategoryOrTraversal`` is ``use_default`` then the ``Iterator``
argument shall meet the requirements of Readable Iterator and
``indirect_iterator`` satisfies the requirements of the most refined
standard traversal concept that is satisfied by the ``Iterator``
argument. In this case

The expression ``*v``, where ``v`` is an object of type
``iterator_traits<Iterator>::value_type``, must be a valid expression
and must be convertible to ``iterator_adaptor::reference``. Also,
there are further requirements on the
``iterator_traits<Iterator>::value_type`` if the ``Value`` parameter
is not ``use_default``, as implied by the algorithm for deducing the
default for the ``value_type`` member.



``indirect_iterator`` operations
................................

``indirect_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``indirect_iterator`` with 
   a default-constructed ``iterator_adaptor`` subobject.


``indirect_iterator(Iterator x);``

:Returns: An instance of ``indirect_iterator`` with
    the ``iterator_adaptor`` subobject copy constructed from ``x``.

::

  template <
      class Iterator2, class Value2, unsigned Access, class Traversal
    , class Reference2, class Difference2
  >
  indirect_iterator(
      indirect_iterator<
           Iterator2, Value2, Access, Traversal, Reference2, Difference2
      > const& y
    , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
  );

:Requires: ``Iterator2`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``indirect_iterator`` whose 
    ``iterator_adaptor`` subobject is constructed from ``y.base()``.


