#include <iostream>
#include <iomanip>
#include <string>

void Main() {
  int a, b, c;
  std::string s;
  std::cin >> a >> b >> c >> s;
  std::cout << a + b + c << " " << s << std::endl;
}

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);
  Main();
}
