#include <iostream>
#include <random>
#include <string>


auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    int correctAnswer      = d100(rd);
    std::string userAnswer = "0";

    while (std::stoi(userAnswer) != correctAnswer) {
        std::cout << "guess: ";
        std::getline(std::cin, userAnswer);
        if (std::stoi(userAnswer) == correctAnswer)
            break;
        if (std::stoi(userAnswer) > correctAnswer)
            std::cout << "number too big!" << std::endl;
        if (std::stoi(userAnswer) < correctAnswer)
            std::cout << "number too small!" << std::endl;
    }

    std::cout << "number just right" << std::endl;

    return 0;
}
