#ifdef LOCAL_DEBUG
#include "local_headers.hpp"
#else
#include "atcoder/all"
#include "bits/stdc++.h"
#include "boost/multiprecision/cpp_int.hpp"
#include "boost/range/irange.hpp"
#endif
#include "graph/topological_sort.hpp"
#include "graph/warshall_floyd.hpp"
#include "normal_print.hpp"
#include "numeric.hpp"
#include "segtree.hpp"
#ifdef LOCAL_DEBUG
#include "debug_print.hpp"
#else
namespace debug {
template <typename... Ts> void println(Ts const&...) {}
} // namespace debug
#endif
#define IGNORE [[maybe_unused]] auto _

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
  std::cout << std::flush;
}
