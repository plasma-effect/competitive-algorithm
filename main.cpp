#include "boost/range/irange.hpp"
#include <atcoder/all>
#include <bits/stdc++.h>
#ifdef LOCAL_DEBUG

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

template <> class dual_array<bool> : public dual_array<std::uint8_t> {
public:
  using dual_array<std::uint8_t>::dual_array;
};

template <typename T, typename F = std::greater<>>
using priority_queue = std::priority_queue<T, std::vector<T>, F>;
} // namespace common

namespace atcoder {
template <int mod>
std::ostream& operator<<(std::ostream& ost, static_modint<mod> const& val) {
  return ost << val.val();
}
} // namespace atcoder
namespace print_detail {
template <typename T>
concept stdstream_able = requires(T a) { std::declval<std::ostream&>() << a; };

class print_base_t {
  std::ios_base::fmtflags base_flags;
  std::ostream& ost;
  struct dec_t {
    const char* prefix = "";
    const char* suffix = "";
    const char* delim = " ";
  };
  dec_t rng_dec, tpl_dec;

public:
  print_base_t(std::ostream& os)
      : base_flags(os.flags()), ost(os), rng_dec{}, tpl_dec{} {}
  ~print_base_t() { ost.setf(base_flags); }

  void print(std::string const& str) { ost << str; }
  void print(std::string_view const& view) { ost << view; }
  void print(const char* str) { ost << str; }
  template <stdstream_able T> void print(T const& v) { ost << v; }
  template <std::input_iterator It> void print(It first, It last) {
    ost << rng_dec.prefix;
    if (first != last) {
      print(*first);
      for (++first; first != last; ++first) {
        ost << rng_dec.delim;
        print(*first);
      }
    }
    ost << rng_dec.suffix;
  }
  template <std::integral Int>
  void print(common::integer_range<Int> const& rng) {
    print(rng.begin(), rng.end());
  }
  template <std::ranges::input_range T> void print(T const& rng) {
    print(rng.begin(), rng.end());
  }
  template <typename T, std::size_t N> void print(T const (&ar)[N]) {
    print(std::ranges::begin(ar), std::ranges::end(ar));
  }
  template <std::size_t S, std::size_t I, typename T>
  void tuple_print(T const& t) {
    if constexpr (I == 0) {
      ost << tpl_dec.prefix;
    } else {
      ost << tpl_dec.delim;
    }
    print(std::get<I>(t));
    if constexpr (I + 1 != S) {
      tuple_print<S, I + 1>(t);
    } else {
      ost << tpl_dec.suffix;
    }
  }
  template <typename T0, typename T1> void print(std::pair<T0, T1> const& p) {
    tuple_print<2, 0>(p);
  }
  template <typename... Ts> void print(std::tuple<Ts...> const& t) {
    tuple_print<sizeof...(Ts), 0>(t);
  }
  void set_range_prefix(const char* new_prefix) { rng_dec.prefix = new_prefix; }
  void set_range_suffix(const char* new_suffix) { rng_dec.suffix = new_suffix; }
  void set_range_delim(const char* new_delim) { rng_dec.delim = new_delim; }
  void set_tuple_prefix(const char* new_prefix) { tpl_dec.prefix = new_prefix; }
  void set_tuple_suffix(const char* new_suffix) { tpl_dec.suffix = new_suffix; }
  void set_tuple_delim(const char* new_delim) { tpl_dec.delim = new_delim; }
};
} // namespace print_detail

namespace debug {
namespace detail {
template <typename T>
constexpr bool is_std_manip_v =
    std::is_same_v<T, decltype(std::setbase(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setfill(std::declval<char>()))> ||
    std::is_same_v<T, decltype(std::setprecision(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setw(std::declval<int>()))> ||
    std::is_convertible_v<T, std::ios_base& (*)(std::ios_base&)>;
template <bool> void print(print_detail::print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_detail::print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb.print(" ");
  }
  pb.print(arg);
  print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace detail
inline void println() { std::cerr << std::endl; }
template <typename... Ts> void println(Ts const&... args) {
  print_detail::print_base_t pb(std::cerr);
  pb.set_range_prefix("{");
  pb.set_range_suffix("}");
  pb.set_range_delim(", ");
  pb.set_tuple_prefix("(");
  pb.set_tuple_suffix(")");
  pb.set_tuple_delim(", ");
  detail::print<false>(pb, args...);
  std::cerr << std::endl;
}
} // namespace debug
#else
namespace debug {
template <typename... Ts> void println(Ts const&...) {}
} // namespace debug
#endif

namespace common {
namespace detail {
template <typename T>
constexpr bool is_std_manip_v =
    std::is_same_v<T, decltype(std::setbase(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setfill(std::declval<char>()))> ||
    std::is_same_v<T, decltype(std::setprecision(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setw(std::declval<int>()))> ||
    std::is_convertible_v<T, std::ios_base& (*)(std::ios_base&)>;
template <bool> void print(print_detail::print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_detail::print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb.print(" ");
  }
  pb.print(arg);
  print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace detail
inline void println() { std::cout << "\n"; }
template <typename... Ts> void println(Ts const&... args) {
  print_detail::print_base_t pb(std::cout);
  detail::print<false>(pb, args...);
  std::cout << "\n";
}
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
  std::cout << std::flush;
}
