#include <algorithm>
#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    if (argc < 2)
        return 1;

    bool endOfParams   = false;
    bool reverse       = false;
    bool noNewLine     = false;
    bool eachInNewLine = false;

    int i = 1;

    while (!endOfParams) {
        std::string argStr(argv[i]);
        if (argStr == "-n") {
            noNewLine = true;
            ++i;
            continue;
        }
        if (argStr == "-r") {
            reverse = true;
            ++i;
            continue;
        }
        if (argStr == "-l") {
            eachInNewLine = true;
            ++i;
            continue;
        }
        endOfParams = true;
    }
    if (reverse)
        std::reverse(argv + i, argv + argc);

    for (; i < argc; ++i) {
        std::cout << argv[i];
        eachInNewLine ? std::cout << std::endl : std::cout << " ";
    }

    if (!noNewLine)
        std::cout << std::endl;

    return 0;
}
