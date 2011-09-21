//  boost/chrono/stopwatches/stopwatch_scoped.hpp  ------------------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_STOPWATCH_SCOPED_HPP
#define BOOST_CHRONO_STOPWATCHES_STOPWATCH_SCOPED_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>

namespace boost
{
  namespace chrono
  {

    //--------------------------------------------------------------------------------------//
    template<class Stopwatch> class stopwatch_runner
    {
    public:
      typedef Stopwatch stopwatch;
      stopwatch_runner(stopwatch & a, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        stopwatch_(a)
      {
        stopwatch_.start(ec);
      }
      ~stopwatch_runner()
      {
        system::error_code ec;
        stopwatch_.stop(ec);
      }
#if 0
      typename Stopwatch::duration elapsed(system::error_code & ec = BOOST_CHRONO_THROWS)
      {
        return stopwatch_.elapsed(ec)-stopwatch_.get_storage();
      }
#endif
    private:
      stopwatch& stopwatch_;
      stopwatch_runner();//= delete;
      stopwatch_runner(const stopwatch_runner&); // = delete;
      stopwatch_runner& operator=(const stopwatch_runner&); // = delete;

    };

    //--------------------------------------------------------------------------------------//
    template<class Stopwatch> class stopwatch_stopper
    {
    public:
      typedef Stopwatch stopwatch;
      stopwatch_stopper(stopwatch & a, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        stopwatch_(a)
      {
        stopwatch_.stop(ec);
      }
      ~stopwatch_stopper()
      {
        system::error_code ec;
        stopwatch_.start(ec);
      }
#if 0
      typename Stopwatch::duration elapsed(system::error_code & ec = BOOST_CHRONO_THROWS)
      {
        return stopwatch_.elapsed(ec)-stopwatch_.get_storage();
      }
#endif
    private:
      stopwatch& stopwatch_;
      stopwatch_stopper();//= delete;
      stopwatch_stopper(const stopwatch_stopper&); // = delete;
      stopwatch_stopper& operator=(const stopwatch_stopper&); // = delete;

    };

    //--------------------------------------------------------------------------------------//
    template<class Stopwatch> class stopwatch_suspender
    {
    public:
      typedef Stopwatch stopwatch;
      stopwatch_suspender(stopwatch & a, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        stopwatch_(a)
      {
        stopwatch_.suspend(ec);
      }
      ~stopwatch_suspender()
      {
        system::error_code ec;
        stopwatch_.resume(ec);
      }
    private:
      stopwatch& stopwatch_;
      stopwatch_suspender(); // = delete;
      stopwatch_suspender(const stopwatch_suspender&); // = delete;
      stopwatch_suspender& operator=(const stopwatch_suspender&); // = delete;
    };

    //--------------------------------------------------------------------------------------//
    template<class Stopwatch> class stopwatch_resumer
    {
    public:
      typedef Stopwatch stopwatch;
      stopwatch_resumer(stopwatch & a, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        stopwatch_(a)
      {
        stopwatch_.resume(ec);
      }
      ~stopwatch_resumer()
      {
        system::error_code ec;
        stopwatch_.suspend(ec);
      }
    private:
      stopwatch& stopwatch_;
      stopwatch_resumer(); // = delete;
      stopwatch_resumer(const stopwatch_resumer&); // = delete;
      stopwatch_resumer& operator=(const stopwatch_resumer&); // = delete;
    };

  } // namespace chrono
} // namespace boost

#endif
