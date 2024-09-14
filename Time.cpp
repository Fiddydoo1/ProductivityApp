#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <iomanip>

int main() {

    // Get the current time from the system clock

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

    std::tm bedtime = local_time;

    bedtime.tm_hour = bed_hour;
    bedtime.tm_min = bed_minute;
    bedtime.tm_sec = 0;

    //Checks if the date entered or something like that is past midnight

    if (bedtime.tm_hour < local_time.tm_hour || (bedtime.tm_hour == local_time.tm_hour && bedtime.tm_min < local_time.tm_min)) {
        bedtime.tm_mday += 1;
    }

    std::time_t bedtime_time = std::mktime(&bedtime);

    double seconds_until_bedtime = std::difftime(bedtime_time, current_time);

    double total_time_in_seconds = seconds_until_bedtime;
    double school = (2.0 / 3.0) * total_time_in_seconds;
    double project = (1.0 / 3.0) * total_time_in_seconds;

    int school_hours = static_cast<int>(school) / 3600;
    int school_minutes = (static_cast<int>(school) % 3600) / 60;
    int school_seconds = static_cast<int>(school) % 60;

    int project_hours = static_cast<int>(project) / 3600;
    int project_minutes = (static_cast<int>(project) % 3600) / 60;
    int project_seconds = static_cast<int>(project) % 60;

    std::cout << "Time until bedtime: "
        << floor(total_time_in_seconds / 3600) << " hours, "
        << (static_cast<int>(total_time_in_seconds) % 3600) / 60 << " minutes, "
        << static_cast<int>(total_time_in_seconds) % 60 << " seconds.\n";

    auto projectDuration = std::chrono::seconds(static_cast<int>(project));
    auto project_end_time = now + projectDuration;

    std::time_t project_end_time_t = std::chrono::system_clock::to_time_t(project_end_time);

    std::tm future_time;
    localtime_s(&future_time, &project_end_time_t);

    char future_buffer[9];
    std::strftime(future_buffer, sizeof(future_buffer), "%H:%M:%S", &future_time);

    //School part

    std::cout << "Time for school: ";

    std::cout << school_hours << ":";

    if (school_minutes < 10) {
        std::cout << "0" << school_minutes << ":" << school_seconds << std::endl;
    }
    else {
        std::cout << school_minutes << ":" << school_seconds << "s" << std::endl;
    }

    //Project part

    std::cout << "Time for project: ";

    std::cout << project_hours << ":";

    if (project_minutes < 10) {
        std::cout << "0" << project_minutes << ":" << project_seconds << "s" << std::endl;
    }
    else {
        std::cout << project_minutes << ":" << project_seconds << "s" << std::endl;
    }

    std::cout << "Set timer to: " << future_buffer << std::endl;

    _getch();

    return 0;
}
