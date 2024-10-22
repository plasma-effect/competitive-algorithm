#include "bits/stdc++.h"
#include <atcoder/all>
#include <boost/multi_array.hpp>
#include <boost/range/irange.hpp>

namespace common {
// common
template <typename T> auto max_v = std::numeric_limits<T>::max();
template <typename T> auto min_v = std::numeric_limits<T>::min();
template <typename Integer>
struct integer_range : boost::integer_range<Integer>, std::ranges::view_base {
  using boost::integer_range<Integer>::integer_range;
};
template <typename Integer> integer_range<Integer> irange(Integer last) {
  return integer_range<Integer>(Integer(0), last);
}
template <typename Integer>
integer_range<Integer> irange(Integer first, Integer last) {
  return integer_range<Integer>(first, last);
}
template <typename T>
std::size_t upper_bound_index(std::vector<T> const& vec, T const& v) {
  return std::ranges::upper_bound(vec, v) - vec.begin();
}
template <typename T>
std::size_t lower_bound_index(std::vector<T> const& vec, T const& v) {
  return std::ranges::lower_bound(vec, v) - vec.begin();
}
template <typename T> using pair = std::pair<T, T>;

// segtree
namespace detail {
constexpr std::plus<> plus;
constexpr std::multiplies<> multiplies;
template <typename T> struct get_val_t {
  T val;
  constexpr get_val_t(T v) : val(v) {}
  constexpr auto operator()() const { return val; }
};
template <typename T> constexpr get_val_t<T> get_zero{0};
template <typename T> constexpr get_val_t<T> get_one{1};
} // namespace detail
template <typename T>
using add_segtree = atcoder::segtree<T, detail::plus, detail::get_zero<T>>;
template <typename T>
using mul_segtree = atcoder::segtree<T, detail::multiplies, detail::get_one<T>>;

// Floyd-Warshall Algorithm
namespace detail {
template <typename T>
void local_update(std::optional<T>& base, std::optional<T> a,
                  std::optional<T> b) {
  if (a && b) {
    if (!base) {
      base = *a + *b;
    } else {
      base = std::min(*base, *a + *b);
    }
  }
}
template <typename T> void local_update(T& base, T a, T b) {
  base = std::min(base, a + b);
}
} // namespace detail
template <typename T>
void warshall_floyd(boost::multi_array<T, 2>& data, std::size_t N) {
  for (auto k : boost::irange(N)) {
    for (auto i : boost::irange(N)) {
      for (auto j : boost::irange(N)) {
        detail::local_update(data[i][j], data[i][k], data[k][j]);
      }
    }
  }
}

// for dijkstra
template <typename T>
using p_queue = std::priority_queue<T, std::vector<T>, std::greater<>>;

} // namespace common
namespace debug {
namespace detail {
template <typename T> void print(std::vector<T> const& vec);
template <typename T0, typename T1> void print(std::pair<T0, T1> const& p);
template <typename T> auto print(T&& val) -> decltype(std::cerr << val) {
  return std::cerr << val;
}
template <typename T> void print(std::vector<T> const& vec) {
  if (vec.size() == 0) {
    std::cerr << "[]";
  } else {
    std::cerr << "[";
    print(vec[0]);
    for (auto i : boost::irange<std::size_t>(1, vec.size())) {
      std::cerr << ", ";
      print(vec[i]);
    }
    std::cerr << "]";
  }
}
template <typename T0, typename T1> void print(std::pair<T0, T1> const& p) {
  std::cerr << "(";
  print(p.first);
  std::cerr << ", ";
  print(p.second);
  std::cerr << ")";
}
} // namespace detail
template <typename T> void println(T const& val) {
  detail::print(val);
  std::cerr << std::endl;
}
template <typename T, typename... Ts>
void println(T const& val, Ts const&... vals) {
  detail::print(val);
  std::cerr << " ";
  println(vals...);
}
} // namespace debug

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
