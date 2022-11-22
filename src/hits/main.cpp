#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using json = nlohmann::json;

int main() {
    std::string s = "Hello, world!";
    json js = s;
    std::cout << js << std::endl;
    return 0;
}