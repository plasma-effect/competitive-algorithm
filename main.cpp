#include "bits/stdc++.h"
#include <atcoder/all>
#include <boost/range/irange.hpp>

namespace common {
template <typename T> auto max_v = std::numeric_limits<T>::max();
template <typename T> auto min_v = std::numeric_limits<T>::min();

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

} // namespace common
namespace debug {
namespace detail {
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
} // namespace detail
template <typename T> void println(T&& val) {
  detail::print(std::forward<T>(val));
  std::cerr << std::endl;
}
template <typename T, typename... Ts> void println(T&& val, Ts&&... vals) {
  detail::print(std::forward<T>(val));
  std::cerr << " ";
  println(std::forward<Ts>(vals)...);
}
} // namespace debug

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
