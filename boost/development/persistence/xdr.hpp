/* boost xdr.hpp header file
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
 *  04 Dec 00 Initial, incomplete, buggy version split off persistence.hpp
 */

#ifndef BOOST_XDR_HPP
#define BOOST_XDR_HPP

#include <boost/cstdint.hpp>

/*
 * RFC 1832: External Data Representation Standard
 */

namespace boost {

class xdr_writer
{
public:
  explicit xdr_writer(std::ostream & strm) : os(strm) { }

  bool good() { return os.good(); }

  void write(int_least32_t x)
  {
    // assume two's complement notation for int_least32_t for the moment
    write(static_cast<uint_least32_t>(x));
  }

  void write(uint_least32_t x)
  {
    os.put((x>>24) & 0xff);
    os.put((x>>16) & 0xff);
    os.put((x>>8) & 0xff);
    os.put((x) & 0xff);
  }

  void write(double x)
  {
    // Hm... Is there some endianess-independent idea how to do it?
    // assume little-endian (x86) for the moment
    for(int i = 7; i >= 0; --i)
      os.put(*(reinterpret_cast<char *>(&x)+i));
  }

  void write(const std::string& x)
  {
    write(static_cast<uint_least32_t>(x.length()));
    os.write(x.c_str(), x.length());
    // padding
    for(int i = 0; i < 4-(x.length()%4); ++i)
      os.put(0);
  }

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
  std::ostream & os;
};


class xdr_reader
{
public:
  explicit xdr_reader(std::istream & strm) : is(strm) { }

  bool good() { return is.good(); }

  void read(int_least32_t& x)
  {
    // assume two's complement notation for int_least32_t for the moment
    read(*reinterpret_cast<uint_least32_t*>(&x));
  }

  void read(uint_least32_t& x)
  {
    x = (getuchar()<<24) | (getuchar()<<16) | (getuchar()<<8) | getuchar();
  }

  void read(double& x)
  {
    // Hm... Is there some endianess-independent idea how to do it?
    // assume little-endian (x86) for the moment
    for(int i = 7; i >= 0; --i)
      is.get(*(reinterpret_cast<char *>(&x)+i));
  }

  void read(std::string& x)
  {
    uint_least32_t length;
    read(length);
    x.erase();
    x.reserve(length);
    for(int i = 0; i < length; ++i) {
      x += getchar();
    }
    // padding to 4 bytes
    for(int i = 0; i < 4 - (length % 4); ++i)
      getchar();
   }

  void start_sequence(std::size_t& n) { read(n); }
  bool end_sequence() { return false; }
  void start_struct() { }
  void end_struct() { }

protected:
  char getchar() { char c; is.get(c); return c; }
  signed char getschar() { return static_cast<signed char>(getchar()); }
  unsigned char getuchar() { return static_cast<unsigned char>(getchar()); }

  std::istream & is;  
};

} // namespace boost

#endif // BOOST_XDR_HPP
