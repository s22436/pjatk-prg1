#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    if (argc < 2)
        return 1;
    int startingNumber = std::stoi(argv[1]);
    for (int i = startingNumber; i >= 0; --i) {
        std::cout << i << std::endl;
    }

    return 0;
}
