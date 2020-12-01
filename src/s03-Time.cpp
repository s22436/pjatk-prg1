#include <s22436/Time.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr const auto SECONDS_IN_DAY = 86400;

s22436::Time::Time(unsigned h, unsigned m, unsigned s)
        : hours{h}, minutes{m}, seconds{s}
{
    if (h > 23 || m > 59 || s > 59) {
        throw std::out_of_range("Incorrect time values");
    }
}

auto formatTime(unsigned i) -> std::string
{
    return i < 10 ? "0" + std::to_string(i) : std::to_string(i);
}

auto s22436::Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << std::setw(2) << formatTime(hours) << ":" << formatTime(minutes)
        << ":" << formatTime(seconds);
    return out.str();
}

auto s22436::Time::time_of_day() const -> Time_of_day
{
    if (hours < 5) {
        return s22436::NIGHT;
    } else if (hours < 12) {
        return s22436::MORNING;
    } else if (hours < 20) {
        return s22436::AFTERNOON;
    } else {
        return s22436::EVENING;
    }
}

auto s22436::Time::to_string(s22436::Time_of_day tod) const -> std::string
{
    switch (tod) {
    case s22436::MORNING:
        return "Rano!";
    case s22436::AFTERNOON:
        return "Popoludnie!";
    case s22436::EVENING:
        return "Wieczor!";
    case s22436::NIGHT:
        return "Noc!";
    default:
        return "Brak takiej pory dnia!";
    }
}

auto s22436::Time::next_hour() -> void
{
    if (hours == 23) {
        hours = 0;
    } else {
        ++hours;
    }
}
auto s22436::Time::next_minute() -> void
{
    if (minutes == 59) {
        next_hour();
        minutes = 0;
    } else {
        ++minutes;
    }
}
auto s22436::Time::next_second() -> void
{
    if (seconds == 59) {
        next_minute();
        seconds = 0;
    } else {
        ++seconds;
    }
}

auto s22436::Time::count_seconds() const -> uint64_t
{
    return hours * 3600 + minutes * 60 + seconds;
}
auto s22436::Time::count_minutes() const -> uint64_t
{
    return hours * 60 + minutes;
}
auto s22436::Time::time_to_midnight() const -> Time
{
    return to_time(SECONDS_IN_DAY - count_seconds());
}

auto s22436::Time::to_time(uint64_t sec) const -> Time
{
    auto tempTime = static_cast<unsigned>(sec);
    if (tempTime > SECONDS_IN_DAY) {
        tempTime %= SECONDS_IN_DAY;
    }

    auto h = tempTime / 3600;
    tempTime %= 3600;
    auto m = tempTime / 60;
    tempTime %= 60;
    return s22436::Time(h, m, tempTime);
}

auto s22436::Time::operator+(Time const& t) const -> Time
{
    return to_time(count_seconds() + t.count_seconds());
}
auto s22436::Time::operator-(Time const& t) const -> Time
{
    int result = static_cast<int>(count_seconds() - t.count_seconds());
    if (result < 0) {
        result = SECONDS_IN_DAY - std::abs((result % SECONDS_IN_DAY));
    }

    return to_time(static_cast<uint64_t>(result));
}
auto s22436::Time::operator<(Time const& t) const -> bool
{
    return count_seconds() < t.count_seconds();
}
auto s22436::Time::operator>(Time const& t) const -> bool
{
    return count_seconds() > t.count_seconds();
}
auto s22436::Time::operator==(Time const& t) const -> bool
{
    return count_seconds() == t.count_seconds();
}
auto s22436::Time::operator!=(Time const& t) const -> bool
{
    return count_seconds() != t.count_seconds();
}

auto main() -> int
{
    auto time = s22436::Time(23, 59, 59);
    std::cout << "INITIAL: " << time.to_string() << '\n';
    time.next_second();
    std::cout << "AFTER SECOND INCREASED: " << time.to_string() << '\n';


    std::cout << "Godzina: " << time.to_string() << " to "
              << time.to_string(time.time_of_day()) << '\n';

    auto timeOne = s22436::Time(21, 13, 11);
    auto timeTwo = s22436::Time(3, 3, 3);

    std::cout << timeOne.to_string() << " + " << timeTwo.to_string() << " = "
              << (timeOne + timeTwo).to_string() << '\n';
    std::cout << timeTwo.to_string() << " - " << timeOne.to_string() << " = "
              << (timeTwo - timeOne).to_string() << '\n';
    std::cout << timeOne.to_string() << " > " << timeTwo.to_string() << " = "
              << (timeOne > timeTwo ? "PRAWDA" : "FALSZ") << '\n';
    std::cout << timeOne.to_string() << " < " << timeTwo.to_string() << " = "
              << (timeOne < timeTwo ? "PRAWDA" : "FALSZ") << '\n';
    std::cout << timeOne.to_string() << " == " << timeTwo.to_string() << " = "
              << (timeOne == timeTwo ? "PRAWDA" : "FALSZ") << '\n';
    std::cout << timeOne.to_string() << " != " << timeTwo.to_string() << " = "
              << (timeOne != timeTwo ? "PRAWDA" : "FALSZ") << '\n';

    std::cout << "Godzina: " << timeOne.to_string()
              << " w sekundach od polnocy to: " << timeOne.count_seconds()
              << " sec" << '\n';
    std::cout << "Godzina: " << timeOne.to_string()
              << " w munitach od polnocy to: " << timeOne.count_minutes()
              << " min" << '\n';
    std::cout << "O Godzinie: " << timeOne.to_string()
              << " do polnocy zostalo: "
              << timeOne.time_to_midnight().to_string() << '\n';

    return 0;
}
