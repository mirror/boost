//  boost/chrono/stopwatches/suspendable_stopwatch.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_SUSPENDABLE_STOPWATCH__HPP
#define BOOST_CHRONO_STOPWATCHES_SUSPENDABLE_STOPWATCH__HPP

#include <utility>

//#include <boost/chrono/chrono.hpp>
#include <boost/chrono/stopwatches/stopwatch_scoped.hpp>
#include <boost/chrono/stopwatches/memories/no_memory.hpp>
#include <boost/system/error_code.hpp>

namespace boost
{
  namespace chrono
  {

    struct dont_start_t
    {
    };
    static const dont_start_t dont_start =
    { };

    template<typename Clock, typename LapsMemory=no_memory<typename Clock::duration> >
    class suspendable_stopwatch
    {
    public:
      typedef LapsMemory laps_memory;
      typedef Clock clock;
      typedef typename Clock::duration duration;
      typedef typename Clock::time_point time_point;
      typedef typename Clock::rep rep;
      typedef typename Clock::period period;
      BOOST_CHRONO_STATIC_CONSTEXPR bool is_steady =             Clock::is_steady;

      explicit suspendable_stopwatch(
          system::error_code & ec =  BOOST_CHRONO_THROWS
          ) :
        start_(duration::zero()),
        running_(false),
        storage_(),
        suspended_(false),
        partial_(duration::zero())
      {
        start(ec);
      }
      explicit suspendable_stopwatch(
          const dont_start_t&
          ) :
          start_(duration::zero()),
          running_(false),
          storage_(),
          suspended_(false),
          partial_(duration::zero())
      {
      }

      explicit suspendable_stopwatch(
          laps_memory const& acc,
          system::error_code & ec = BOOST_CHRONO_THROWS
          ) :
          start_(duration::zero()),
          running_(false),
          storage_(acc),
          suspended_(false),
          partial_(duration::zero())
      {
        start(ec);
      }

      suspendable_stopwatch(
          laps_memory const& acc,
          const dont_start_t&
          ) :
            start_(duration::zero()),
            running_(false),
            storage_(acc),
            suspended_(false),
            partial_(duration::zero())
      {
      }

      ~suspendable_stopwatch()
      {
        system::error_code ec;
        stop(ec);
      }

      void restart(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        time_point tmp = clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

        if (running_)
        {
          partial_ += tmp - start_;
          storage_.store(partial_);
          partial_ = duration::zero();
        }
        else
        {
          running_ = true;
        }
        start_ = tmp;
      }

      void start(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

          partial_ = duration::zero();
          start_ = tmp;
          running_ = true;
      }

      void stop(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

          partial_ += tmp - start_;
          storage_.store(partial_);
          start_ = time_point(duration::zero());
          running_ = false;
          suspended_ = false;
      }

      void suspend(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (is_running())
        {
          if (!suspended_)
          {
            time_point tmp = clock::now(ec);
            if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

            partial_ += tmp - start_;
            suspended_ = true;
          }
          else
          {
            ec.clear();
          }
        } else
        {
          ec.clear();
        }
      }

      void resume(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (suspended_)
        {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

          start_ = tmp;
          suspended_ = false;
        } else
        {
          ec.clear();
        }
      }

      bool is_running() const {
        return running_;
      }
      bool is_suspended() const {
        return suspended_;
      }

      duration elapsed(
          system::error_code & ec = BOOST_CHRONO_THROWS
          ) const
      {
        if (is_running())
        {
          if (suspended_) {
            return partial_;
          }
          else
          {
            time_point tmp = clock::now(ec);
            if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return duration::zero();

            return partial_ + tmp - start_;
          }
        } else
        {
          return duration::zero();
        }
      }


      void reset(
          )
      {
        storage_.reset();
        running_ = false;
        suspended_ = false;
        partial_ = duration::zero();
        start_ = time_point(duration::zero());
      }

      laps_memory const& get_laps_memory()
      {
        return storage_;
      }


      typedef stopwatch_runner<suspendable_stopwatch<Clock, LapsMemory> >
          scoped_run;
      typedef stopwatch_stopper<suspendable_stopwatch<Clock, LapsMemory> >
          scoped_stop;
      typedef stopwatch_suspender<suspendable_stopwatch<Clock, LapsMemory> >
          scoped_suspend;
      typedef stopwatch_resumer<suspendable_stopwatch<Clock, LapsMemory> >
          scoped_resume;
    private:
      time_point start_;
      bool running_;
      laps_memory storage_;
      bool suspended_;
      duration partial_;
    };

  } // namespace chrono
} // namespace boost

#endif
