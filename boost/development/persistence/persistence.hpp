/* boost persistence.hpp header file
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without free provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 *
 * Revision history
 *  26 Nov 00 Templatize binary_writer/reader (Beman)
 *  18 Nov 00 Add descriptors (Jens)
 *  13 Mar 00 Initial version
 */

#ifndef BOOST_PERSISTENCE_HPP
#define BOOST_PERSISTENCE_HPP

#include <cstddef>
#include <fstream>
#include <utility>     // std::pair
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>         // std::map and std::multimap
#include <set>         // std::set and std::multiset
#include <limits>
#include <typeinfo>

#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>


namespace boost {

/*
 * Descriptions suitable for saving and loading
 */

template<class Desc, class T1, class T2>
inline void describe(Desc & descriptor, std::pair<T1, T2>& pair)
{
  descriptor & pair.first & pair.second;
}

// if the global description is not there, try the member function
template<class Desc, class T>
inline void describe(Desc & descriptor, T& x)
{
  x.describe(descriptor);
}


/*
 * Saving.
 */

// overloads for a sequence
template<class Writer, class ForwardIterator>
inline void save_sequence(Writer & writer,
			  ForwardIterator first, ForwardIterator last,
			  std::size_t n)
{
  writer.start_sequence(n);
  while (first != last) {
    writer.start_sequence_element();
    save(writer, *first);
    writer.end_sequence_element();
    if (++first != last)
      writer.separate_sequence_elements();
  }
  writer.end_sequence();
}

template<class Writer, class ForwardIterator>
inline void save_sequence(Writer & writer,
			  ForwardIterator first, ForwardIterator last)
{
  // We could avoid computing the distance for a shift_writer
  save_sequence(writer, first, last, std::distance(first, last));
}

// overloads with all relevant container types
template<class Writer, class T, class Allocator>
inline void save(Writer & writer, const std::deque<T, Allocator>& container)
{
  save_sequence(writer, container.begin(), container.end(), container.size());
}

template<class Writer, class T, class Allocator>
inline void save(Writer & writer, const std::list<T, Allocator>& container)
{
  save_sequence(writer, container.begin(), container.end(), container.size());
}

template<class Writer, class T, class Allocator>
inline void save(Writer & writer, const std::vector<T, Allocator>& container)
{
  save_sequence(writer, container.begin(), container.end(), container.size());
}

template<class Writer, class Key, class T, class Compare, class Allocator>
inline void save(Writer & writer, const std::map<Key, T, Compare, Allocator>& m)
{
  save_sequence(writer, m.begin(), m.end(), m.size());
}

template<class Writer, class Key, class T, class Compare, class Allocator>
inline void save(Writer & writer, 
		 const std::multimap<Key, T, Compare, Allocator>& m)
{
  save_sequence(writer, m.begin(), m.end(), m.size());  
}

template<class Writer, class Key, class Compare, class Allocator>
inline void save(Writer & writer, const std::set<Key, Compare, Allocator>& s)
{
  save_sequence(writer, s.begin(), s.end(), m.size());
}

template<class Writer, class Key, class Compare, class Allocator>
inline void save(Writer & writer, 
		 const std::multiset<Key, Compare, Allocator>& s)
{
  save_sequence(writer, s.begin(), s.end(), m.size());  
}

template<class Writer>
class save_descriptor
{
public:
  save_descriptor(Writer & w)
    : writer(w), first(true)
  {
    writer.start_struct();
  }

  ~save_descriptor() { writer.end_struct(); }

  template<class T>
  save_descriptor& operator & (const T& x)
  {
    if(first)
      first = false;
    else
      writer.separate_struct_members();
    save(writer, x);
    return *this;
  }

  save_descriptor& cstring(const char * x) {
    save_cstring(writer, x);
    return *this;
  }

private:
  Writer & writer;
  bool first;
};

// if your Reader handles some additional type as elementary, you can
// overload similarly
template<class Writer>
inline void save(Writer & writer, const std::string & s)
{
  writer.start_value();
  writer.write(s);
  writer.end_value();
}

// C-style strings are handled separately
template<class Writer>
inline void save_cstring(Writer & writer, const char *s)
{
  writer.start_value();
  writer.write_cstring(s);
  writer.end_value();
}


template<bool b>
struct save_forward { };

template<>
struct save_forward<true>
{
  // forward to Writer
  template<class Writer, class T>
  static inline void save(Writer & writer, const T& x)
  {
    writer.start_value();
    writer.write(x);
    writer.end_value();
  }
};

template<>
struct save_forward<false>
{
  // forward to describe()
  template<class Writer, class T>
  static inline void save(Writer & writer, const T& x) {
    save_descriptor<Writer> desc(writer);
    describe(desc, const_cast<T&>(x));
  }
};

template<class Writer, class T>
inline void save(Writer & writer, const T& x)
{
  // forward all (built-in) arithmetic types to the Writer
  // assume everything else is describe()ed
  save_forward<is_arithmetic<T>::value>::save(writer, x);
}


/*
 * Reading.
 */

// overloads for a sequence
template<class T, class Reader, class OutputIterator>
inline void load_sequence(Reader & reader, OutputIterator out)
{
  std::size_t n;
  reader.start_sequence(n);
  T tmp;
  while(reader.good() && n-- > 0 && !reader.end_sequence()) {
    load(reader, tmp);
    *out = tmp;
    ++out;
  }
}

template<class Reader, class InsertIterator>
inline void load_container(Reader & reader, const InsertIterator& ins)
{
  typedef typename InsertIterator::container_type container_type;
  load_sequence<typename container_type::value_type>(reader, ins);
}

template<class Reader, class Container>
inline void load_assoc_container(Reader & reader, Container & cont)
{
  typedef typename Container::key_type key_type;
  typedef typename Container::mapped_type mapped_type;
  // we cannot use Container::value_type here because it contains "const Key"
  typedef std::pair<key_type, mapped_type> stored_type;
  load_sequence<stored_type>(reader, std::inserter(cont, cont.begin()));
}

// overloads with all relevant container types
template<class Reader, class T, class Allocator>
inline void load(Reader & reader, std::deque<T, Allocator>& container)
{
  load_container(reader, std::back_inserter(container));
}

template<class Reader, class T, class Allocator>
inline void load(Reader & reader, std::list<T, Allocator>& container)
{
  load_container(reader, std::back_inserter(container));
}

template<class Reader, class T, class Allocator>
inline void load(Reader & reader, std::vector<T, Allocator>& container)
{
  load_container(reader, std::back_inserter(container));
}

template<class Reader, class Key, class T, class Compare, class Allocator>
inline void load(Reader & reader, std::map<Key, T, Compare, Allocator>& m)
{
  load_assoc_container(reader, m);
}

template<class Reader, class Key, class T, class Compare, class Allocator>
inline void load(Reader & reader, std::multimap<Key, T, Compare, Allocator>& m)
{
  load_assoc_container(reader, m);
}

template<class Reader, class Key, class Compare, class Allocator>
inline void load(Reader & reader, std::set<Key, Compare, Allocator>& s)
{
  load_container<Key>(reader, std::inserter(s, s.begin()));
}

template<class Reader, class Key, class Compare, class Allocator>
inline void load(Reader & reader, std::multiset<Key, Compare, Allocator>& s)
{
  load_container<Key>(reader, std::inserter(s, s.begin()));
}

template<class Reader>
class load_descriptor
{
public:
  load_descriptor(Reader & r) : reader(r) { reader.start_struct(); }
  ~load_descriptor() { reader.end_struct(); }

  template<class T>
  load_descriptor& operator & (T& x) {
    load(reader, x);
    return *this;
  }

  load_descriptor& cstring(char *& x) {
    load_cstring(reader, x);
    return *this;
  }

private:
  Reader & reader;
};

// if your Reader handles some additional type as elementary, you can
// overload similarly
template<class Reader>
inline void load(Reader & reader, std::string & s) { reader.read(s); }

// C-style strings are handled separately
template<class Reader>
inline void load_cstring(Reader & reader, char *&s) { reader.read_cstring(s); }


template<bool b>
struct load_forward { };

template<>
struct load_forward<true>
{
  // forward to Reader
  template<class Reader, class T>
  static inline void load(Reader & reader, T& x) { reader.read(x); }
};

template<>
struct load_forward<false>
{
  // forward to describe()
  template<class Reader, class T>
  static inline void load(Reader & reader, T& x) {
    load_descriptor<Reader> desc(reader);
    describe(desc, x);
  }
};

template<class Reader, class T>
inline void load(Reader & reader, T& x)
{
  // forward all (built-in) arithmetic types to the Reader
  // assume everything else is describe()ed
  load_forward<is_arithmetic<T>::value>::load(reader, x);
}

// to extend this for your own data structure(s),
// write more overloaded load and save functions.
// always think about overloading structural stuff (above) first
// before specializing format-specific stuff (separate headers)


/*
 * Convenience wrapper functions
 */
template<class Writer, class Container>
void save_file(const Container & cont, const std::string & filename)
{
  std::ofstream file(filename.c_str());
  file.exceptions(std::ios::failbit|std::ios::badbit);
  Writer w(file);
  save(w, cont);
}

template<class Reader, class Container>
void load_file(Container & cont, const std::string & filename)
{
  std::ifstream file(filename.c_str());
  file.exceptions(std::ios::failbit|std::ios::badbit);
  Reader r(file);
  load(r, cont);
}

} // namespace boost

#endif BOOST_PERSISTENCE_HPP
