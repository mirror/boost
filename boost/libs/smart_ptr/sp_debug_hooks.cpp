//
//  sp_debug_hooks.cpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  http://www.boost.org/libs/smart_ptr/debug_hooks.html
//

#if defined(BOOST_ENABLE_SP_DEBUG_HOOKS)

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_mutex.hpp>
#include <new>
#include <cstdlib>
#include <map>
#include <deque>
#include <iostream>

int const m = 2; // m * sizeof(int) must be aligned appropriately

// magic values to mark heap blocks with

int const allocated_scalar  = 0x1234560C;
int const allocated_array   = 0x1234560A;
int const adopted_scalar    = 0x0567890C;
int const adopted_array     = 0x0567890A;
int const deleted           = 0x498769DE;

using namespace std; // for compilers where things aren't in std

// operator new

static new_handler get_new_handler()
{
    new_handler p = set_new_handler(0);
    set_new_handler(p);
    return p;
}

static void * allocate(size_t n, int mark)
{
    int * pm;

    for(;;)
    {
        pm = static_cast<int*>(malloc(n + m * sizeof(int)));

        if(pm != 0) break;

        if(new_handler pnh = get_new_handler())
        {
            pnh();
        }
        else
        {
            return 0;
        }
    }

    *pm = mark;

    return pm + m;
}

void * operator new(size_t n) throw(bad_alloc)
{
    void * p = allocate(n, allocated_scalar);

#if !defined(BOOST_NO_EXCEPTIONS)

    if(p == 0) throw bad_alloc();

#endif

    return p;
}

#if !defined(__BORLANDC__) || (__BORLANDC__ > 0x551)

void * operator new(size_t n, nothrow_t const &) throw()
{
    return allocate(n, allocated_scalar);
}

#endif

void * operator new[](size_t n) throw(bad_alloc)
{
    void * p = allocate(n, allocated_array);

#if !defined(BOOST_NO_EXCEPTIONS)

    if(p == 0) throw bad_alloc();

#endif

    return p;
}

#if !defined(__BORLANDC__) || (__BORLANDC__ > 0x551)

void * operator new[](size_t n, nothrow_t const &) throw()
{
    return allocate(n, allocated_array);
}

#endif

// cycle detection

typedef std::map< void const *, std::pair<void *, size_t> > map_type;

static map_type & get_map()
{
    static map_type m;
    return m;
}

typedef boost::detail::lightweight_mutex mutex_type;

static mutex_type & get_mutex()
{
    static mutex_type m;
    return m;
}

static void * init_mutex_before_main = &get_mutex();

namespace
{
    class X;

    struct count_layout
    {
        boost::detail::counted_base * pi;
        int id;
    };

    struct shared_ptr_layout
    {
        X * px;
        count_layout pn;
    };
}

// assume 4 byte alignment for pointers when scanning
size_t const pointer_align = 4;

typedef std::map<void const *, long> map2_type;

static void scan_and_count(void const * area, size_t size, map_type const & m, map2_type & m2)
{
    unsigned char const * p = static_cast<unsigned char const *>(area);

    for(size_t n = 0; n + sizeof(shared_ptr_layout) <= size; p += pointer_align, n += pointer_align)
    {
        shared_ptr_layout const * q = reinterpret_cast<shared_ptr_layout const *>(p);

        if(q->pn.id == boost::detail::shared_count_id && q->pn.pi != 0 && m.count(q->pn.pi) != 0)
        {
            ++m2[q->pn.pi];
        }
    }
}

typedef std::deque<void const *> open_type;

static void scan_and_mark(void const * area, size_t size, map2_type & m2, open_type & open)
{
    unsigned char const * p = static_cast<unsigned char const *>(area);

    for(size_t n = 0; n + sizeof(shared_ptr_layout) <= size; p += pointer_align, n += pointer_align)
    {
        shared_ptr_layout const * q = reinterpret_cast<shared_ptr_layout const *>(p);

        if(q->pn.id == boost::detail::shared_count_id && q->pn.pi != 0 && m2.count(q->pn.pi) != 0)
        {
            open.push_back(q->pn.pi);
            m2.erase(q->pn.pi);
        }
    }
}

static void find_unreachable_objects(map_type const & m, map2_type & m2)
{
    // scan objects for shared_ptr members, compute internal counts

    {
        for(map_type::const_iterator i = m.begin(); i != m.end(); ++i)
        {
            boost::detail::counted_base const * p = static_cast<boost::detail::counted_base const *>(i->first);

            BOOST_ASSERT(p->use_count() != 0); // there should be no inactive counts in the map

            scan_and_count(i->second.first, i->second.second, m, m2);
        }
    }

    // mark reachable objects

    {
        open_type open;

        for(map2_type::iterator i = m2.begin(); i != m2.end(); ++i)
        {
            boost::detail::counted_base const * p = static_cast<boost::detail::counted_base const *>(i->first);
            if(p->use_count() != i->second) open.push_back(p);
        }

        for(open_type::iterator j = open.begin(); j != open.end(); ++j)
        {
            m2.erase(*j);
        }

        while(!open.empty())
        {
            void const * p = open.front();
            open.pop_front();

            map_type::const_iterator i = m.find(p);
            BOOST_ASSERT(i != m.end());

            scan_and_mark(i->second.first, i->second.second, m2, open);
        }
    }

    // m2 now contains the unreachable objects
}

void report_unreachable_objects(bool verbose)
{
    map2_type m2;

    mutex_type::scoped_lock lock(get_mutex());

    map_type const & m = get_map();

    find_unreachable_objects(m, m2);

    if(verbose)
    {
        for(map2_type::iterator j = m2.begin(); j != m2.end(); ++j)
        {
            map_type::const_iterator i = m.find(j->first);
            BOOST_ASSERT(i != m.end());
//            std::cerr << "Unreachable object at " << i->second.first << ", " << i->second.second << " bytes long.\n";
        }
    }

    if(verbose || !m2.empty())
    {
        std::cerr << m2.size() << " unreachable objects.\n";
    }
}

typedef std::deque< boost::shared_ptr<X> > free_list_type;

static void scan_and_free(void * area, size_t size, map2_type const & m2, free_list_type & free)
{
    unsigned char * p = static_cast<unsigned char *>(area);

    for(size_t n = 0; n + sizeof(shared_ptr_layout) <= size; p += pointer_align, n += pointer_align)
    {
        shared_ptr_layout * q = reinterpret_cast<shared_ptr_layout *>(p);

        if(q->pn.id == boost::detail::shared_count_id && q->pn.pi != 0 && m2.count(q->pn.pi) != 0 && q->px != 0)
        {
            boost::shared_ptr<X> * ppx = reinterpret_cast< boost::shared_ptr<X> * >(p);
            free.push_back(*ppx);
            ppx->reset();
        }
    }
}

void free_unreachable_objects()
{
    map2_type m2;

    mutex_type::scoped_lock lock(get_mutex());

    map_type const & m = get_map();

    find_unreachable_objects(m, m2);

    free_list_type free;

    for(map2_type::iterator j = m2.begin(); j != m2.end(); ++j)
    {
        map_type::const_iterator i = m.find(j->first);
        BOOST_ASSERT(i != m.end());
        scan_and_free(i->second.first, i->second.second, m2, free);
    }
}

// debug hooks

namespace boost
{

void sp_scalar_constructor_hook(void * p)
{
    if(p == 0) return;

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm != adopted_scalar);    // second smart pointer to the same address
    BOOST_ASSERT(*pm != allocated_array);   // allocated with new[]
    BOOST_ASSERT(*pm == allocated_scalar);  // not allocated with new

    *pm = adopted_scalar;
}

void sp_scalar_constructor_hook(void * px, std::size_t size, void * pn)
{
    sp_scalar_constructor_hook(px);
    mutex_type::scoped_lock lock(get_mutex());
    get_map()[pn] = std::make_pair(px, size);
}

void sp_scalar_destructor_hook(void * p)
{
    if(p == 0) return;

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm == adopted_scalar);    // attempt to destroy nonmanaged block

    *pm = allocated_scalar;
}

void sp_scalar_destructor_hook(void * px, std::size_t /*size*/, void * pn)
{
    sp_scalar_destructor_hook(px);
    mutex_type::scoped_lock lock(get_mutex());
    get_map().erase(pn);
}

// It is not possible to handle the array hooks in a portable manner.
// The implementation typically reserves a bit of storage for the number
// of objects in the array, and the argument of the array hook isn't
// equal to the return value of operator new[].

void sp_array_constructor_hook(void * /* p */)
{
/*
    if(p == 0) return;

    // adjust p depending on the implementation

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm != adopted_array);     // second smart array pointer to the same address
    BOOST_ASSERT(*pm != allocated_scalar);  // allocated with new
    BOOST_ASSERT(*pm == allocated_array);   // not allocated with new[]

    *pm = adopted_array;
*/
}

void sp_array_destructor_hook(void * /* p */)
{
/*
    if(p == 0) return;

    // adjust p depending on the implementation

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm == adopted_array); // attempt to destroy nonmanaged block

    *pm = allocated_array;
*/
}

} // namespace boost

// operator delete

void operator delete(void * p) throw()
{
    if(p == 0) return;

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm != deleted);           // double delete
    BOOST_ASSERT(*pm != adopted_scalar);    // delete p.get();
    BOOST_ASSERT(*pm != allocated_array);   // allocated with new[]
    BOOST_ASSERT(*pm == allocated_scalar);  // not allocated with new

    *pm = deleted;

    free(pm);
}

#if !defined(__BORLANDC__) || (__BORLANDC__ > 0x551)

void operator delete(void * p, nothrow_t const &) throw()
{
    ::operator delete(p);
}

#endif

void operator delete[](void * p) throw()
{
    if(p == 0) return;

    int * pm = static_cast<int*>(p);
    pm -= m;

    BOOST_ASSERT(*pm != deleted);           // double delete
    BOOST_ASSERT(*pm != adopted_scalar);    // delete p.get();
    BOOST_ASSERT(*pm != allocated_scalar);  // allocated with new
    BOOST_ASSERT(*pm == allocated_array);   // not allocated with new[]

    *pm = deleted;

    free(pm);
}

#if !defined(__BORLANDC__) || (__BORLANDC__ > 0x551)

void operator delete[](void * p, nothrow_t const &) throw()
{
    ::operator delete[](p);
}

#endif

#endif // defined(BOOST_ENABLE_SP_DEBUG_HOOKS)
