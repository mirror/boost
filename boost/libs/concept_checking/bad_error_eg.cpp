#include <list>
#include <algorithm>

struct foo {
  bool operator<(const foo&) const { return false; }
};
int main(int, char*[]) {
  std::list<foo> v;
  std::stable_sort(v.begin(), v.end());
  return 0;
}
