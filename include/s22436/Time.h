#include <string>

#ifndef S22436_TIME_H
#define S22436_TIME_H

namespace s22436 {
enum Time_of_day { MORNING, AFTERNOON, EVENING, NIGHT };


struct Time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

    auto to_string() const -> std::string;
    auto to_string(Time_of_day) const -> std::string;

    auto time_of_day() const -> Time_of_day;

    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;

    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Time;
    auto to_time(uint64_t) const -> Time;

    auto operator+(Time const&) const -> Time;
    auto operator-(Time const&) const -> Time;
    auto operator<(Time const&) const -> bool;
    auto operator>(Time const&) const -> bool;
    auto operator==(Time const&) const -> bool;
    auto operator!=(Time const&) const -> bool;

    Time(unsigned, unsigned, unsigned);
};


}  // namespace s22436


#endif
