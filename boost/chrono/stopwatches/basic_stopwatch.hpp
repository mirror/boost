//  boost/chrono/stopwatches/basic_stopwatch.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_BASIC_STOPWATCH__HPP
#define BOOST_CHRONO_STOPWATCHES_BASIC_STOPWATCH__HPP

#include <utility>

//#include <boost/chrono/chrono.hpp>
#include <boost/chrono/stopwatches/stopwatch_scoped.hpp>
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

    template<typename Clock, typename Memory>
    class basic_stopwatch
    {
    public:
      typedef Memory storage_type;
      typedef Clock clock;
      typedef typename Clock::duration duration;
      typedef typename Clock::time_point time_point;
      typedef typename Clock::rep rep;
      typedef typename Clock::period period;

      explicit basic_stopwatch(
          system::error_code & ec =  BOOST_CHRONO_THROWS
          ) :
        running_(false), suspended_(false), start_(duration::zero()),
            level_(0), partial_(duration::zero()), suspend_level_(0),
            storage_(), construction_(clock::now(ec))
      {
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec)  return;

        start(ec);
      }
      explicit basic_stopwatch(
          const dont_start_t&,
          system::error_code & ec =  BOOST_CHRONO_THROWS
          ) :
        running_(false), suspended_(false), start_(duration::zero()),
            level_(0), partial_(duration::zero()), suspend_level_(0),
            storage_(), construction_(clock::now(ec))
      {
      }

      explicit basic_stopwatch(
          storage_type const& acc,
          system::error_code & ec = BOOST_CHRONO_THROWS
          ) :
        running_(false), suspended_(false), start_(duration::zero()),
            level_(0), partial_(duration::zero()), suspend_level_(0),
            storage_(acc), construction_(clock::now(ec))
      {
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

        start(ec);
      }

      basic_stopwatch(
          storage_type const& acc,
          const dont_start_t&,
          system::error_code & ec = BOOST_CHRONO_THROWS
          ) :
        running_(false), suspended_(false), start_(duration::zero()),
            level_(0), partial_(duration::zero()), suspend_level_(0),
            storage_(acc), construction_(clock::now(ec))
      {
      }

      ~basic_stopwatch()
      {
        system::error_code ec;
        stop(ec);
      }

      std::pair<duration, time_point> restart(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        time_point tmp = clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return time_point();

        if (running_ && (level_ == 1))
        {
          partial_ += tmp - start_;
          storage_.store(partial_);
          partial_ = duration::zero();
        } else
        {
          running_ = true;
        }
        start_ = tmp;
        return std::make_pair(storage_.elapsed(), start_);
      }

      time_point start(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (!running_)
        {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return time_point();

          start_ = tmp;
          ++level_;
          running_ = true;
          return start_;
        } else
        {
          ++level_;
          ec.clear();
          return time_point();
        }
      }

      duration stop(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (running_ && (--level_ == 0))
        {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return duration::zero();

          partial_ += tmp - start_;
          storage_.store(partial_);
          partial_ = duration::zero();
          running_ = false;
          return storage_.elapsed();
        } else
        {
          ec.clear();
          return duration::zero();
        }
      }

      duration suspend(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (running_)
        {
          if (!suspended_)
          {
            time_point tmp = clock::now(ec);
            if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return duration::zero();

            ++suspend_level_;
            partial_ += tmp - start_;
            suspended_ = true;
            return storage_.elapsed();
          } else
          {
            ++suspend_level_;
            ec.clear();
            return duration::zero();
          }
        } else
        {
          ec.clear();
          return duration::zero();
        }
      }

      time_point resume(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (suspended_ && (--suspend_level_ == 0))
        {
          time_point tmp = clock::now(ec);
          if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return time_point();

          start_ = tmp;
          suspended_ = false;
          return start_;
        } else
        {
          ec.clear();
          return time_point();
        }
      }

      duration elapsed(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        if (running_)
        {
          if (suspended_)
            return storage_.elapsed();
          else
          {
            time_point tmp = clock::now(ec);
            if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return duration::zero();

            return storage_.elapsed() + tmp - start_;
          }
        } else
        {
          return storage_.elapsed();
        }
      }


      void reset(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        construction_ = clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return;

        storage_.reset();
        running_ = false;
        suspended_ = false;
        partial_ = duration::zero();
        start_ = time_point(duration::zero());
        level_ = 0;
        suspend_level_ = 0;
      }

      storage_type const& get_storage()
      {
        return storage_;
      }

      duration lifetime(
          system::error_code & ec = BOOST_CHRONO_THROWS
          )
      {
        typename clock::time_point tmp= clock::now(ec);
        if (!BOOST_CHRONO_IS_THROWS(ec) && ec) return duration::zero();

        return tmp - construction_;
      }

      typedef stopwatch_runner<basic_stopwatch<Clock, Memory> >
          scoped_run;
      typedef stopwatch_stopper<basic_stopwatch<Clock, Memory> >
          scoped_stop;
      typedef stopwatch_suspender<basic_stopwatch<Clock, Memory> >
          scoped_suspend;
      typedef stopwatch_resumer<basic_stopwatch<Clock, Memory> >
          scoped_resume;
    private:
      bool running_;
      bool suspended_;
      time_point start_;
      std::size_t level_;
      duration partial_;
      std::size_t suspend_level_;
      storage_type storage_;
      time_point construction_;
    };

  } // namespace chrono
} // namespace boost

#endif
