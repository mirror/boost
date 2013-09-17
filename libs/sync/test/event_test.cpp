// Copyright (C) 2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>

#include <boost/thread.hpp>
#include <boost/sync/event.hpp>

#include <boost/typeof/typeof.hpp>

static void test_event_post_wait()
{
    boost::sync::event ev;

    ev.post();
    ev.wait();

    BOOST_REQUIRE( ev.try_wait() == true );

    ev.reset();

    BOOST_REQUIRE( ev.try_wait() == false );
}


static void test_event_post_try_wait()
{
    boost::sync::event ev;

    BOOST_REQUIRE( ev.try_wait() == false );

    ev.post();

    BOOST_REQUIRE( ev.try_wait() == true );
}

static void test_event_post_wait_autoreset()
{
    boost::sync::event ev(true);

    ev.post();
    ev.wait();
    BOOST_REQUIRE( ev.try_wait() == false );
}


static void test_event_reset()
{
    boost::sync::event ev(false);

    BOOST_REQUIRE( ev.try_wait() == false );
    ev.post();
    BOOST_REQUIRE( ev.try_wait() == true );
    ev.reset();
    BOOST_REQUIRE( ev.try_wait() == false );
}

struct event_wait_and_post_test
{
    void run()
    {
        boost::thread post_thread(boost::bind(&event_wait_and_post_test::wait_and_post, this));
        ev_.wait();
    }

    void wait_and_post()
    {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        ev_.post();
    }

    static void run_test()
    {
        event_wait_and_post_test test;
        test.run();
    }

    boost::sync::event ev_;
    boost::thread thread_;
};

static void test_event_wait_for()
{
    using namespace boost;

    sync::event ev;

    BOOST_AUTO(start, chrono::system_clock::now());

    BOOST_REQUIRE( ev.try_wait() == false );

    BOOST_REQUIRE(!ev.try_wait_for(chrono::milliseconds(500)));

    BOOST_REQUIRE( ev.try_wait() == false );


    BOOST_AUTO(end, chrono::system_clock::now());
    BOOST_AUTO(wait_time, end - start);

    // guessing!
    BOOST_REQUIRE( wait_time > chrono::milliseconds(450) );
    BOOST_REQUIRE( wait_time < chrono::milliseconds(1000) );

    ev.post();

    BOOST_REQUIRE(ev.try_wait_for(chrono::milliseconds(500)));
}

static void test_event_wait_until()
{
    using namespace boost;

    sync::event ev(0);
    {
        BOOST_AUTO(now, chrono::system_clock::now());
        BOOST_AUTO(timeout, now + chrono::milliseconds(500));

        BOOST_REQUIRE(!ev.try_wait_until(timeout));

        BOOST_AUTO(end, chrono::system_clock::now());
        BOOST_AUTO(timeout_delta, end - timeout);

        // guessing!
        BOOST_REQUIRE( timeout_delta > chrono::milliseconds(-400) );
        BOOST_REQUIRE( timeout_delta < chrono::milliseconds(400) );
    }

    ev.post();

    {
        BOOST_AUTO(start,   chrono::system_clock::now());
        BOOST_AUTO(timeout, start + chrono::milliseconds(500));

        BOOST_REQUIRE(ev.try_wait_until(timeout));

        BOOST_AUTO(end, chrono::system_clock::now());

        // guessing!
        BOOST_REQUIRE( (end - start) < chrono::milliseconds(100) );
    }
}

boost::unit_test::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE("boost::sync::event test suite");

    test->add(BOOST_TEST_CASE(test_event_post_wait));
    test->add(BOOST_TEST_CASE(test_event_post_wait_autoreset));
    test->add(BOOST_TEST_CASE(test_event_post_try_wait));
    test->add(BOOST_TEST_CASE(test_event_reset));

    test->add(BOOST_TEST_CASE(event_wait_and_post_test::run_test));

    test->add(BOOST_TEST_CASE(test_event_wait_for));
    test->add(BOOST_TEST_CASE(test_event_wait_until));

    return test;
}

