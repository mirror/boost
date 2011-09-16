//  boost/chrono/stopwatches/simple_stopwatch.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_SIMPLE_STOPWATCH__HPP
#define BOOST_CHRONO_STOPWATCHES_SIMPLE_STOPWATCH__HPP

#include <utility>

#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * This class provides the simpler stopwath which is just able to give the elapsed time since its creation.
     */
    template<typename Clock=high_resolution_clock>
    class simple_stopwatch
    {
    public:
      typedef Clock clock;
      typedef typename Clock::duration duration;
      typedef typename Clock::time_point time_point;
      typedef typename Clock::rep rep;
      typedef typename Clock::period period;
      BOOST_CHRONO_STATIC_CONSTEXPR bool is_steady =             Clock::is_steady;


      simple_stopwatch() :
        start_(clock::now())
      {
      }
      explicit simple_stopwatch(system::error_code & ec) :
        start_(duration::zero())
      {
        time_point tmp = clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec))
        {
          if (ec)
          {
            return;
          }
        }
        start_ = tmp;
      }

      duration elapsed()
      {
        return clock::now() - start_;
      }
      duration elapsed(system::error_code & ec)
      {
        time_point tmp = clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec))
        {
          if (ec)
            return duration::zero();
        }
        return tmp - start_;
      }

    private:
      time_point start_;
    };

  } // namespace chrono
} // namespace boost

#endif
