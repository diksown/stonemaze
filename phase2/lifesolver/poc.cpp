#include <vector>
int main() {
    // Foo bar(10, 10);
    // Foo baz(10, 10);
    std::vector<std::vector<char>>(10);
    std::vector<std::vector<char>>(10, std::vector<char>(10));
}