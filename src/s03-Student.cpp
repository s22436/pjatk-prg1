#include <s22436/Student.h>

#include <iostream>
#include <sstream>

s22436::Student::Student(std::string n,
                         std::string s,
                         std::string in,
                         unsigned sn,
                         float ga)
        : name{n}
        , surname{s}
        , index_number{in}
        , semester_number{sn}
        , grade_average{ga}
{}

auto s22436::Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Name: " << name << " Surname: " << surname
        << " Index number: " << index_number
        << " Semester Number: " << semester_number
        << " Grade Average: " << grade_average;
    return out.str();
}

auto main() -> int
{
    auto me = s22436::Student("Dominik", "Hinc", "22436", 1, 4);
    std::cout << me.to_string() << '\n';

    return 0;
}
