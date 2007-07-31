#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  weak_ptr_mt_test.cpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright 2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/bind.hpp>

#include <vector>
#include <memory>
#include <stdexcept>

#include <cstdio>
#include <ctime>
#include <cstdlib>

// 'portable' thread framework

class abstract_thread
{
public:

    virtual ~abstract_thread() {}
    virtual void run() = 0;
};

#if !defined(BOOST_HAS_PTHREADS) && defined(BOOST_HAS_WINTHREADS)

char const * title = "Using Windows threads";

#include <windows.h>
#include <process.h>

typedef HANDLE pthread_t;

unsigned __stdcall common_thread_routine(void * pv)
{
    abstract_thread * pt = static_cast<abstract_thread *>(pv);
    pt->run();
    delete pt;
    return 0;
}

int pthread_create(pthread_t * thread, void const *, unsigned (__stdcall * start_routine) (void*), void* arg)
{
    HANDLE h = (HANDLE)_beginthreadex(0, 0, start_routine, arg, 0, 0);

    if(h != 0)
    {
        *thread = h;
        return 0;
    }
    else
    {
        return 1; // return errno;
    }
}

int pthread_join(pthread_t thread, void ** /*value_ptr*/)
{
    ::WaitForSingleObject(thread, INFINITE);
    ::CloseHandle(thread);
    return 0;
}

#else

char const * title = "Using POSIX threads";

#include <pthread.h>

extern "C" void * common_thread_routine(void * pv)
{
    abstract_thread * pt = static_cast<abstract_thread *>(pv);
    pt->run();
    delete pt;
    return 0;
}

#endif

//

template<class F> class thread: public abstract_thread
{
public:

    explicit thread(F f): f_(f)
    {
    }

    void run()
    {
        f_();
    }

private:

    F f_;
};

template<class F> pthread_t createThread(F f)
{
    std::auto_ptr<abstract_thread> p(new thread<F>(f));

    pthread_t r;

    if(pthread_create(&r, 0, common_thread_routine, p.get()) == 0)
    {
        p.release();
        return r;
    }

    throw std::runtime_error("createThread failed.");
}

//

int const n = 16384;
int const k = 512; // vector size
int const m = 16; // threads

void test( std::vector< boost::shared_ptr<int> > & v )
{
    using namespace std; // printf, rand

    std::vector< boost::weak_ptr<int> > w( v.begin(), v.end() );

    int s = 0, f = 0, r = 0;

    for( int i = 0; i < n; ++i )
    {
        // randomly kill a pointer

        v[ rand() % k ].reset();
        ++s;

        for( int j = 0; j < k; ++j )
        {
            if( boost::shared_ptr<int> px = w[ j ].lock() )
            {
                ++s;

                if( rand() & 4 )
                {
                    continue;
                }

                // rebind anyway with prob. 50% for add_ref_lock() against weak_release() contention
                ++f;
            }
            else
            {
                ++r;
            }

            w[ j ] = v[ rand() % k ];
        }
    }

    printf( "\n%d locks, %d forced rebinds, %d normal rebinds.", s, f, r );
}

int main()
{
    using namespace std; // printf, clock_t, clock

    printf("%s: %d threads, %d * %d iterations: ", title, m, n, k );

    std::vector< boost::shared_ptr<int> > v( k );

    for( int i = 0; i < k; ++i )
    {
        v[ i ].reset( new int( 0 ) );
    }

    clock_t t = clock();

    pthread_t a[m];

    for(int i = 0; i < m; ++i)
    {
        a[i] = createThread( boost::bind( test, v ) );
    }

    v.resize( 0 ); // kill original copies

    for(int j = 0; j < m; ++j)
    {
        pthread_join( a[j], 0 );
    }

    t = clock() - t;

    printf("\n\n%.3f seconds.\n", static_cast<double>(t) / CLOCKS_PER_SEC);

    return 0;
}
