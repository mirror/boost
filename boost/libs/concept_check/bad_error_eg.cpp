#include <list>
#include <algorithm>

int main() {
  std::list<int> v;
  std::stable_sort(v.begin(), v.end());
  return 0;
}
