
Example
-------

The following example prints an array of characters in reverse order
using ``reverse_iterator``.

::
    
    char letters_[] = "hello world!";
    const int N = sizeof(letters_)/sizeof(char) - 1;
    typedef char* base_iterator;
    base_iterator letters(letters_);
    std::cout << "original sequence of letters:\t" << letters_ << std::endl;

    boost::reverse_iterator<base_iterator>
      reverse_letters_first(letters + N),
      reverse_letters_last(letters);

    std::cout << "sequence in reverse order:\t";
    std::copy(reverse_letters_first, reverse_letters_last,
	      std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;



The output is::

    original sequence of letters:   hello world!
    sequence in reverse order:      !dlrow olleh
