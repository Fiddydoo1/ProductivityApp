#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <vector>

void add_new(std::vector<double> vector_of_fractions) {
    auto now = std::chrono::system_clock::now();

    // Convert it to a time_t which represents calendar time

    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    char buffer[26];

    ctime_s(buffer, sizeof(buffer), &current_time);

    std::cout << "Current time is: " << buffer << std::endl;

    std::tm local_time;
    localtime_s(&local_time, &current_time);

    int bed_hour, bed_minute;
    std::cout << "When would you like to sleep today? Hour: ";
    std::cin >> bed_hour;
    std::cout << "Minute?: ";
    std::cin >> bed_minute;
    std::cout << std::endl;

    std::tm bedtime = local_time;

    bedtime.tm_hour = bed_hour;
    bedtime.tm_min = bed_minute;
    bedtime.tm_sec = 0;
    // Checks if the date entered or something like that is past midnight

    if (bedtime.tm_hour < local_time.tm_hour || (bedtime.tm_hour == local_time.tm_hour && bedtime.tm_min < local_time.tm_min)) {
        bedtime.tm_mday += 1;
    }

    std::time_t bedtime_time = std::mktime(&bedtime);

    double seconds_until_bedtime = std::difftime(bedtime_time, current_time);

    double total_time_in_seconds = seconds_until_bedtime;

    double previous = total_time_in_seconds;

    
    for (int i = 0; i < vector_of_fractions.size(); i++) {

        if (i == 0) {
            total_time_in_seconds = seconds_until_bedtime * vector_of_fractions[i];
        }
        else {
            total_time_in_seconds = total_time_in_seconds + seconds_until_bedtime * vector_of_fractions[i];
        }

        int name_hours = static_cast<int>(total_time_in_seconds) / 3600;
        int name_minutes = (static_cast<int>(total_time_in_seconds) % 3600) / 60;
        int name_seconds = static_cast<int>(total_time_in_seconds) % 60;

        auto name_duration = std::chrono::seconds(static_cast<int>(total_time_in_seconds));

        auto name_end_time = now + name_duration;


        std::time_t name_end_time_t = std::chrono::system_clock::to_time_t(name_end_time);

        std::tm future_time;
        localtime_s(&future_time, &name_end_time_t);

        char future_buffer[9];
        std::strftime(future_buffer, sizeof(future_buffer), "%H:%M:%S", &future_time);
        std::cout << "Set timer to: " << std::endl;
        std::cout << future_buffer << std::endl << std::endl;
        
    }

}

int main() {

    //Add your fractions here

    std::vector<double> fractions = {
        2.0 / 4.0,
        1.0 / 4.0,
        1.0 / 4.0
    };

    add_new(fractions);

    _getch();

    return 0;
}
