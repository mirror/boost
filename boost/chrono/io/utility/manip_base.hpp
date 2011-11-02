//  boost/chrono/utility/locale_facet_ptr.hpp  ------------------------------------------------------------//

//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_UTILITY_MANIP_BASE_PTR_HPP
#define BOOST_CHRONO_UTILITY_MANIP_BASE_PTR_HPP

#include <locale>
#include <boost/assert.hpp>

/**
 *
 * @Example
 * @code

    class mendl: public manip<mendl>
    {
    public:
      explicit mendl(size_t how_many) :
        count(how_many) {}
      template <typename out_stream>
      void operator()(out_stream &out) const
      {
        for (size_t line = 0; line < count; ++line)
        {
          out.put(out.widen('\n'));
        }
  ÊÊÊÊÊ out.flush();
      }
    private:
      size_t count;
    };

 * @codeend
 */

namespace boost
{
  namespace chrono
  {


    /**
     *
     * @param os
     * @param m
     * @return
     */

    template <typename Final>
    class manip
    {
    public:
      template <typename out_stream>
      void operator()(out_stream &out) const
      {
        (*static_cast<const Final *> (this))(out);
      }
    };

    template <typename out_stream, typename manip_type>
    out_stream &operator<<(out_stream &out, const manip<manip_type> &op)
    {
      if (out.good())
        op(out);
      return out;
    }

    template <typename in_stream, typename manip_type>
    in_stream &operator>>(in_stream &in, const manip<manip_type> &op)
    {
      if (in.good())
        op(in);
      return in;
    }

  } // namespace chrono
} // namespace boost

#endif // header
