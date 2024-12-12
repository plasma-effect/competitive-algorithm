#include "debug/print.hpp"
#include <atcoder/all>
#include <bits/stdc++.h>
#include <boost/range/irange.hpp>

namespace common {
namespace detail {
template <local_print::output_able T> void print(T a) { std::cout << a; }
void print(std::string const& str) { std::cout << str; }
void print(const char* str) { std::cout << str; }
template <std::size_t N> void print(const char (&str)[N]) { std::cout << str; }
template <std::input_iterator T> void print(T ite, T last) {
  if (ite != last) {
    print(*ite);
    for (++ite; ite != last; ++ite) {
      std::cout << " ";
      print(*ite);
    }
  }
}
template <typename T> void print(std::vector<T> const& vec) {
  print(std::ranges::begin(vec), std::ranges::end(vec));
}
template <std::integral Int> void print(boost::integer_range<Int> const& rng) {
  print(std::ranges::begin(rng), std::ranges::end(rng));
}
template <typename T, std::size_t N> void print(T const (&ar)[N]) {
  print(std::ranges::begin(ar), std::ranges::end(ar));
}
template <typename T, std::size_t N> void print(std::array<T, N> const& ar) {
  print(std::ranges::begin(ar), std::ranges::end(ar));
}
template <typename T0, typename T1> void print(std::pair<T0, T1> const& p) {
  print(p.first);
  std::cout << " ";
  print(p.second);
}
} // namespace detail
void println() { std::cout << std::endl; }
template <typename T> void println(T const& val) {
  detail::print(val);
  std::cout << std::endl;
}
template <typename T, typename... Ts>
void println(T const& val, Ts const&... vals) {
  detail::print(val);
  std::cout << " ";
  println(vals...);
}
} // namespace common

void Main() {
  common::println(1, 2);
  common::println("test");
}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
