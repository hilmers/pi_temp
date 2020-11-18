#include <fstream>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <chrono>

constexpr auto pi_temperature_path = "/sys/class/thermal/thermal_zone0/temp";

const float GetCurrentTemp() {
    std::ifstream temp_file(pi_temperature_path);
    std::string temperature_string((std::istreambuf_iterator<char>(temp_file)), std::istreambuf_iterator<char>());
    float temperature = std::stof(temperature_string);
    temperature = temperature / 1000;
    return temperature;
}

int main() {
    sqlite3* db;
    int db_opened = sqlite3_open("data.db", &db);
    if (db_opened != SQLITE_OK) {
        std::cout << "Failed to open database\n";
	return 1;
    } else {
        std::cout << "Successfully opened database\n";
    }
    const auto now = std::chrono::system_clock::now();
    const auto epoch = now.time_since_epoch();
    const auto temp = GetCurrentTemp();
    std::string sql_statement = "INSERT INTO temperature (epoch_time, temperature) VALUES (" + std::to_string(epoch.count()) + ", " + std::to_string(temp) + ")";
    std::cout << sql_statement << "\n";
    std::cout << temp << "\n";
    int db_closed = sqlite3_close(db);
    if (db_closed != 0)
	std::cout << "Failed to close database\n";
    return 0;
}
