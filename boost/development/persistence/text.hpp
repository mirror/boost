/* boost text.hpp header file
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

#ifndef BOOST_PERSISTENCE_TEXT_HPP
#define BOOST_PERSISTENCE_TEXT_HPP

#include <iostream>

/*
 * Default operation: use operator<< and operator>>
 *
 *  text_writer/reader were not templatized like binary_writer/reader
 *  because the concept supplied by the template parameter would would be so
 *  complex that the only sensible way to implement it would be to derive from
 *  ostream/istream - and that is what shift_writer/reader already assumes.(BGD)
 */

namespace boost {

class text_writer
{
public:
  explicit text_writer(std::ostream & strm, char delim_chr = '"',
	       char escape_chr = '\\')
    : os(strm), delimiter_character(delim_chr), escape_character(escape_chr)
  { }

  bool good() { return os.good(); }

  template<class T>
  void write(const T& x)
  {
    os << x;
  }

  void write(double d)
  {
    // probably needs further overriding of user's settings
    std::streamsize prec = 
      os.precision(std::numeric_limits<double>::digits10);
    os << d;
    os.precision(prec);
  }

  void write(const std::string & s)
  {
    os << delimiter_character;
    for(std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
      if(*it == escape_character || *it == delimiter_character)
	os << escape_character << *it;
      else
	os << *it;
    }
    os << delimiter_character;   // end of string
  }

  void write_cstring(const char *s) {
    // optimize later
    write(std::string(s));
  }

  // delimiters of sequence of with unknown size
  void start_sequence(std::size_t) { os << "["; }
  void start_sequence_element() { }
  void separate_sequence_elements() { }
  void end_sequence_element() { }
  void end_sequence() { os << "] "; }
  void start_struct() { os << "{"; }
  void separate_struct_members() { }
  void end_struct() { os << "} "; }
  void start_value() { }
  void end_value() { os << " "; }

protected:
  std::ostream & os;
  const char delimiter_character, escape_character;
};


class text_reader
{
public:
  explicit text_reader(std::istream & strm, char delim_chr = '"',
			char escape_chr = '\\')
    : is(strm), delimiter_character(delim_chr), escape_character(escape_chr)
  { }

  bool good() { return is.good(); }

  template<class T>
  void read(T & x) { is >> x >> std::ws; }
  void read(std::string & x)
  {
    x.resize(0);
    char delim = delimiter_character;
    if(is.peek() == delim)
      is.get();
    else
      delim = '\n';              // read to end-of-line
    if(!is)
      return;
    for(;;) {
      char c = is.get();
      if(!is)
	break;
      if(c == delim) {           // end of string
	is >> std::ws;
	return; 
      }
      if(c == escape_character) {
	if(is.peek() == escape_character || is.peek() == delim) {
	  c = is.get();
	  if(!is)
	    break;
	}
      }
      x += c;
    }
    is.setstate(is.failbit);
  }

  void read_cstring(char *& x)
  {
    // optimize later
    std::string s;
    read(s);
    delete[] x;
    x = new char[s.size()+1];
    std::copy(s.begin(), s.end(), x);
    *(x+s.size()) = 0;
  }

  void start_sequence(std::size_t& n) {
    expect('[');
    n = std::numeric_limits<std::size_t>::max();
  }
  bool end_sequence() { return check_for(']'); }

  void start_struct() { expect('{'); }
  void end_struct() { expect('}'); }

protected:
  std::istream & is;
  const char delimiter_character, escape_character;

  bool check_for(char c) {
    if(is.peek() == c) {
      is.get();
      is >> std::ws;
      return true;
    } else {
      return false;
    }
  }
  void expect(char c) {
    if(!check_for(c))
      is.setstate(is.failbit);
  }
};

} // namespace boost

#endif // BOOST_PERSISTENCE_TEXT_HPP
