::

  template <class UnaryFunction>
  class function_output_iterator {
  public:
    typedef iterator_tag<
          writable_iterator
        , incrementable_traversal_tag
    > iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());

    struct output_proxy {
      output_proxy(UnaryFunction& f);
      template <class T> output_proxy& operator=(const T& value);
    };
    output_proxy operator*();
    function_output_iterator& operator++();
    function_output_iterator& operator++(int);
  };


``function_output_iterator`` requirements
-----------------------------------------

The ``UnaryFunction`` must be Assignable, Copy Constructible, and the
expression ``f(x)`` must be valid, where ``f`` is an object of type
``UnaryFunction`` and ``x`` is an object of a type accepted by ``f``.
The resulting ``function_output_iterator`` is a model of the Writable
and Incrementable Iterator concepts.


``function_output_iterator`` operations
---------------------------------------

``explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());``

:Returns: An instance of ``function_output_iterator`` with
  ``f`` stored as a data member.


``output_proxy operator*();``

:Returns: An instance of ``output_proxy`` constructed with
  a copy of the unary function ``f``.
  

``function_output_iterator& operator++();``

:Returns: ``*this``


``function_output_iterator& operator++(int);``

:Returns: ``*this``


``function_output_iterator::output_proxy`` operations
-----------------------------------------------------

``output_proxy(UnaryFunction& f);``

:Returns: An instance of ``output_proxy`` with ``f`` stored as
    a data member.


``template <class T> output_proxy& operator=(const T& value);``

:Effects: 
  ::

      m_f(value); 
      return *this; 
