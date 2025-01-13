#include "bits/stdc++.h"
#include <atcoder/all>
#include <boost/multi_array.hpp>
#include <boost/range/irange.hpp>
#ifdef LOCAL_DEBUG
#include "debug/print.hpp"
#else
namespace debug {
template <typename... Ts> void println(Ts const&...) {}
} // namespace debug
#endif

namespace numeric {
template <typename T> constexpr auto max_v = std::numeric_limits<T>::max();
template <typename T> constexpr auto min_v = std::numeric_limits<T>::min();
namespace detail {
template <typename T> struct get_val_t {
  T val;
  constexpr get_val_t(T v) : val(v) {}
  constexpr auto operator()() const { return val; }
};
} // namespace detail
namespace detail {
template <auto id, typename F> struct monoid_t {
  using value_t = decltype(id);
  F op_;
  constexpr monoid_t(F op) : op_(op) {}
  constexpr auto operator()() const { return id; }
  constexpr auto operator()(const value_t& lhs, const value_t& rhs) const {
    return op_(lhs, rhs);
  }
};
constexpr auto min_f = [](const auto& lhs, const auto& rhs) {
  return std::min(lhs, rhs);
};
constexpr auto max_f = [](const auto& lhs, const auto& rhs) {
  return std::max(lhs, rhs);
};
} // namespace detail
template <typename T> constexpr detail::monoid_t<T(0), std::plus<>> plus{{}};
template <typename T>
constexpr detail::monoid_t<T(1), std::multiplies<>> multiplies{{}};
template <typename T>
constexpr detail::monoid_t<max_v<T>, decltype(detail::min_f)> min{{}};
template <typename T>
constexpr detail::monoid_t<min_v<T>, decltype(detail::max_f)> max{{}};
} // namespace numeric

namespace common {
// common
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
template <typename T> T const& chmax(T& lhs, T const& v) {
  return lhs = std::max(lhs, v);
}
template <typename T> T const& chmin(T& lhs, T const& v) {
  return lhs = std::min(lhs, v);
}
template <std::ranges::input_range T>
std::ostream& print_range(const T& ar, const char* delim = " ") {
  using type = std::remove_cvref_t<decltype(*std::ranges::begin(ar))>;
  std::ranges::copy(ar, std::ostream_iterator<type>(std::cout, delim));
  return std::cout;
}

// segtree
namespace detail {
template <auto monoid> using value_t = typename decltype(monoid)::value_t;
} // namespace detail
template <auto monoid>
using segtree = atcoder::segtree<detail::value_t<monoid>, monoid, monoid>;
template <typename T> using add_segtree = segtree<numeric::plus<T>>;
template <typename T> using mul_segtree = segtree<numeric::multiplies<T>>;
template <typename T> using max_segtree = segtree<numeric::max<T>>;

template <auto m0, auto m1>
using lazy_segtree = atcoder::lazy_segtree<detail::value_t<m0>, m0, m0,
                                           detail::value_t<m1>, m1, m1, m1>;

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
template <typename T, typename F = std::greater<>>
using p_queue = std::priority_queue<T, std::vector<T>, F>;

} // namespace common

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
