#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    if (argc < 2)
        return 1;
    std::string password = "";
    do {
        std::cout << "passwrod: ";
        std::getline(std::cin, password);
    } while (password != argv[1]);
    std::cout << "Ok!" << std::endl;

    return 0;
}
