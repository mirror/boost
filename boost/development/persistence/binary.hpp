/* boost binary.hpp header file
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
 *  See http://www.boost.org for most recent version including documentation.
 *
 * Revision history
 *  04 Dec 00 Initial version split off persistence.hpp
 */

#ifndef BOOST_PERSISTENCE_BINARY_HPP
#define BOOST_PERSISTENCE_BINARY_HPP

#include <boost/cstdint.hpp>

/* 
 * Non-portable binary format.
 */

namespace boost {

template<class Writable>
// Writable concept requires only expressions w.good() and w.write(ptr, size)
class binary_writer
{
public:
  explicit binary_writer(Writable & strm) : os(strm) { }

  bool good() { return os.good(); }

  template<class T>
  void write(const T& x)  {
    os.write(reinterpret_cast<const char *>(&x), sizeof(x));
  }
  void write(const std::string& x) {
    write(x.length());
    os.write(x.c_str(), x.length());
  }
  void write(const char *s) { write(std::string(s)); }  // optimize later
    
  void start_sequence(std::size_t n) { write(n); }
  void start_sequence_element() { }
  void separate_sequence_elements() { }
  void end_sequence_element() { }
  void end_sequence() { }
  void start_struct() { }
  void separate_struct_members() { }
  void end_struct() { }
  void start_value() { }
  void end_value() { }
protected:
  Writable & os;
};

typedef binary_writer<std::ostream> binary_ostream_writer;

template<class Readable>
// Readable concept requires only expressions r.good() and r.read(ptr, size)
class binary_reader
{
public:
  explicit binary_reader(Readable & strm) : is(strm) { }

  bool good() { return is.good(); }

  template<class T>
  void read(T& x) 
  {
    is.read(reinterpret_cast<char *>(&x), sizeof(x));
  }
  void read(std::string & x)
  {
    std::size_t sz;
    read(sz);
    x.erase();
    x.reserve(sz);
    while(sz--) {
      char c;
      is.read(&c, 1);
      x += c;
    }
  }
  void read(char *&x) {
    std::string s;
    read(s);
    delete[] x;
    x = new char[s.size()+1];
    std::copy(s.begin(), s.end(), x);
    *(x+s.size()) = 0;
  }

  void start_sequence(std::size_t& n) { read(n); }
  bool end_sequence() { return false; }
  void start_struct() { }
  void end_struct() { }
protected:
  Readable & is;
};

typedef binary_reader<std::istream> binary_istream_reader;


} // namespace boost

#endif // BOOST_PERSISTENCE_BINARY_HPP
