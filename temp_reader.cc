#include <fstream>
#include <string>
#include <iostream>

constexpr auto pi_temperature_path = "/sys/class/thermal/thermal_zone0/temp";

std::string GetCurrentTemp() {
    std::ifstream temp_file(pi_temperature_path);
    std::string temperature((std::istreambuf_iterator<char>(temp_file)), std::istreambuf_iterator<char>());
    return temperature;
}

int main() {
    auto temp = GetCurrentTemp();
    std::cout << temp << "\n";
    return 0;
}
