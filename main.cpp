#include "boost/range/irange.hpp"
#include <atcoder/all>
#include <bits/stdc++.h>
#ifdef LOCAL_DEBUG
#include "debug/print.hpp"
#else
namespace debug {
template <typename... Ts> void println(Ts const&...) {}
} // namespace debug
#endif

namespace common {
template <typename T> constexpr auto max_v = std::numeric_limits<T>::max();
template <typename T> constexpr auto min_v = std::numeric_limits<T>::min();

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

template <typename T> using pair = std::pair<T, T>;

template <typename T> class dual_array {
  std::vector<T> inside_;
  std::size_t dim0, dim1;

public:
  dual_array(std::size_t d0, std::size_t d1)
      : inside_(d0 * d1), dim0(d0), dim1(d1) {}
  T& operator()(int i0, int i1) {
    assert(0 <= i0 && std::cmp_less(i0, dim0));
    assert(0 <= i1 && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T const& operator()(int i0, int i1) const {
    assert(0 <= i0 && std::cmp_less(i0, dim0));
    assert(0 <= i1 && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T& operator()(std::size_t i0, std::size_t i1) {
    assert(std::cmp_less(i0, dim0));
    assert(std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T const& operator()(std::size_t i0, std::size_t i1) const {
    assert(std::cmp_less(i0, dim0));
    assert(std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  common::pair<std::size_t> dimensions() const { return {dim0, dim1}; }
  std::size_t size() const { return dim0 * dim1; }
};

template <typename T, typename F = std::greater<>>
using priority_queue = std::priority_queue<T, std::vector<T>, F>;
} // namespace common

namespace numeric {
template <typename T, typename F> struct monoid_t {
  using value_t = T;
  T e_;
  F op_;
  constexpr monoid_t(T e, F op) : e_(e), op_(op) {}
  constexpr T operator()() const { return e_; }
  constexpr T operator()(T const& lhs, T const& rhs) const {
    return op_(lhs, rhs);
  }
};
template <typename T> constexpr monoid_t plus{T(0), std::plus<>()};
template <typename T> constexpr monoid_t multiplies{T(1), std::multiplies<>()};
template <typename T>
constexpr monoid_t min{common::max_v<T>,
                       static_cast<T const& (*)(T const&, T const&)>(std::min)};
template <typename T>
constexpr monoid_t max{common::min_v<T>,
                       static_cast<T const& (*)(T const&, T const&)>(std::max)};
} // namespace numeric

namespace common {
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
} // namespace common

namespace graph {
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
template <typename T> void warshall_floyd(common::dual_array<T>& data) {
  auto [N, d1] = data.dimensions();
  assert(N == d1);
  for (auto k : boost::irange(N)) {
    for (auto i : boost::irange(N)) {
      for (auto j : boost::irange(N)) {
        detail::local_update(data(i, j), data(i, k), data(k, j));
      }
    }
  }
}
} // namespace graph

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
