#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "tree_creation.h"
#include "syntax_tree/MyException.h"

main()
{
        try
        {
                wchar_t string[20] = L"MARKOV.IN";
                tree_creation(string);
        }
        catch (MyException &e)
        {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cerr << "In line: " << e.GetLineNumber() << std::endl;
        }
}