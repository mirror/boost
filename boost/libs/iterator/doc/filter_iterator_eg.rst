
Example
-------

This example uses ``filter_iterator`` to output only the positive
integers from an array of integers.

::

    struct is_positive_number {
      bool operator()(int x) { return 0 < x; }
    };

    int main()
    {
      int numbers_[] = { 0, -1, 4, -3, 5, 8, -2 };
      const int N = sizeof(numbers_)/sizeof(int);

      typedef int* base_iterator;
      base_iterator numbers(numbers_);

      typedef boost::filter_iterator<is_positive_number, base_iterator>
	FilterIter;

      is_positive_number predicate;
      FilterIter filter_iter_first(predicate, numbers, numbers + N);
      FilterIter filter_iter_last(predicate, numbers + N, numbers + N);

      std::copy(filter_iter_first, filter_iter_last, std::ostream_iterator<int>(std::cout, " "));
      std::cout << std::endl;

      return 0;
    }


The output is::

  4 5 8
