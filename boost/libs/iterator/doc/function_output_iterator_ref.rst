::

  template <class UnaryFunction>
  class function_output_iterator {
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef void                     value_type;
    typedef void                     difference_type;
    typedef void                     pointer;
    typedef void                     reference;

    explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());

    /* implementation defined */ operator*();
    function_output_iterator& operator++();
    function_output_iterator& operator++(int);
  private:
    UnaryFunction m_f;     // exposition only
  };



``function_output_iterator`` requirements
.........................................

The ``UnaryFunction`` must be Assignable, Copy Constructible.  



``function_output_iterator`` models
...................................

``function_output_iterator`` is a model of the Writable and
Incrementable Iterator concepts.



``function_output_iterator`` operations
.......................................

``explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());``

:Returns: An instance of ``function_output_iterator`` with
  ``m_f`` constructed from ``f``.


``/* implementation defined */ operator*();``

:Returns: An object ``r`` of implementation defined type
  such that if ``f(t)`` is a valid expression for
  some object ``t`` then ``r = t`` is a valid expression.
  ``r = t`` will have the same effect as ``f(t)``.
  

``function_output_iterator& operator++();``

:Returns: ``*this``


``function_output_iterator& operator++(int);``

:Returns: ``*this``
