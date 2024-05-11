#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "tree_creation.h"

main()
{
        try
        {
                wchar_t string[20] = L"MARKOV.IN";
                tree_creation(string);
        }
        catch (const std::runtime_error &e)
        {
                std::cerr << "Error: " << e.what() << std::endl;
        }
}
