#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <cassert>
#include <functional>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

static int alloc_count = 0;
static int dealloc_count = 0;

template<typename T>
struct counting_allocator : public std::allocator<T>
{
  template<typename U>
  struct rebind
  {
    typedef counting_allocator<U> other;
  };

  
  T* allocate(std::size_t n)
  {
    alloc_count++;
    return std::allocator<T>::allocate(n);
  }

  void deallocate(T* p, std::size_t n)
  {
    dealloc_count++;
    std::allocator<T>::deallocate(p, n);
  }
};

static int do_minus(int x, int y) { return x-y; }

struct DoNothing
{
  void operator()() const {}
};

static void do_nothing() {}

int
test_main(int, char*[])
{
  function<int, int, int>::allocator< counting_allocator<int> >::type f; 
  f = plus<int>();
  f.clear();
  BOOST_TEST(alloc_count == 1);
  BOOST_TEST(dealloc_count == 1);

  alloc_count = 0;
  dealloc_count = 0;
  f = &do_minus;
  f.clear();

  function<void>::allocator< counting_allocator<int> >::type fv;
  alloc_count = 0;
  dealloc_count = 0;
  fv = DoNothing();
  fv.clear();
  BOOST_TEST(alloc_count == 1);
  BOOST_TEST(dealloc_count == 1);
  
  alloc_count = 0;
  dealloc_count = 0;
  fv = &do_nothing;
  fv.clear();

  return 0;
}
