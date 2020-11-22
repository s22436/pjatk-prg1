#ifndef S22436_STUDENT_H
#define S22436_STUDENT_H

namespace s22436 {
struct Student {
    std::string name{""};
    std::string surname{""};
    std::string index_number{0};
    unsigned semester_number{0};
    float grade_average{0};

    auto to_string() const -> std::string;

    Student(std::string, std::string, std::string, unsigned, float);
};

}  // namespace s22436


#endif
