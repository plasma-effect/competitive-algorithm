#include "bits/stdc++.h"

namespace common {
template <typename T> auto max_v = std::numeric_limits<T>::max();
template <typename T> auto min_v = std::numeric_limits<T>::min();

template <typename T> struct binary_indexed_tree {
  std::vector<T> values;
  binary_indexed_tree(std::size_t N) : values(N + 1) {}
  binary_indexed_tree(const std::vector<T>& base) : values(base.size() + 1) {
    for (std::size_t i = 0; i < values.size(); ++i) {
      add(i, base[i]);
    }
  }
  void add(std::size_t i, T v) {
    for (++i; i < values.size(); i += (i & -i)) {
      values.at(i) += v;
    }
  }
  T sum(std::size_t i) {
    T ret{};
    for (; 0 < i; i -= (i & -i)) {
      ret += values.at(i);
    }
    return ret;
  }
};
} // namespace common

void Main() {}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(15);
  Main();
}
