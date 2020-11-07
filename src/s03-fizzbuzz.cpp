#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    if (argc < 2)
        return 1;

    int maxNumber = std::stoi(argv[1]);
    for (int i = 1; i <= maxNumber; ++i) {
        std::cout << i << " ";
        if (i % 3 == 0)
            std::cout << "Fizz";
        if (i % 5 == 0)
            std::cout << "Buzz";

        std::cout << std::endl;
    }

    return 0;
}
