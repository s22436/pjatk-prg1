#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    int startingNumber = argc > 1 ? std::stoi(argv[1]) : 99;
    for (int i = startingNumber; i > 0; --i) {
        std::cout << i << " bottles of beer on the wall, " << i
                  << " bottles of beer" << std::endl;
        std::cout << "Take one down, pass it around," << std::endl;
    }
    std::cout << "No more bottles of beer on the wall, no more bottles of beer."
              << std::endl;
    std::cout << "Go to the store and buy some more, " << startingNumber
              << " bottles of beer on the wall..";
    std::cout << std::endl;


    return 0;
}
