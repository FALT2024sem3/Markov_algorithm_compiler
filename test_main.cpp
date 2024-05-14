#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include <sstream>
#include "tree_creation.h"
#include <gtest/gtest.h>

// Функция для захвата стандартного вывода из std::wcout
std::wstring captureOutput(const wchar_t* filename) {
    std::wostringstream output;
    std::wstreambuf *oldCoutBuffer = std::wcout.rdbuf(output.rdbuf());
    try {
        tree_creation(const_cast<wchar_t*>(filename));
    } catch (const std::runtime_error &e) {
        std::wcerr << L"Error: " << e.what() << std::endl;
    }
    std::wcout.rdbuf(oldCoutBuffer);
    return output.str();
}

// Утилита для удаления пробелов и символов конца строки
std::wstring simplifyString(const std::wstring& str) {
    std::wstring result;
    for (wchar_t ch : str) {
        if (!iswspace(ch)) {
            result += ch;
        }
    }
    return result;
}

// Утилита для проверки ошибок
void checkErrorOutput(const wchar_t* filename, const std::wstring& expectedError) {
    std::wostringstream output;
    std::wstreambuf *oldCerrBuffer = std::wcerr.rdbuf(output.rdbuf());
    captureOutput(filename);
    std::wcerr.rdbuf(oldCerrBuffer);

    EXPECT_EQ(output.str(), expectedError);
}

// Тест для проверки вывода программы с файлом Markov.IN
TEST(OutputTest, MatchesExpectedOutput) {
    std::wstring expectedOutput = LR"({
link:
"d" "o"
{
"c" "t"
IF
"a" OR "s" AND ! "w" {
"o" "p"
}
{
GOTO: link
"Vostok" "Gagarin"
}
ENDIF
"who" "?"
GOTO: error
}
"" "r"
error:
})";

    std::wstring actualOutput = captureOutput(L"tests/Markov.IN");

    // Упрощение строк для сравнения
    EXPECT_EQ(simplifyString(actualOutput), simplifyString(expectedOutput));
}

// Тесты для проверки ошибок
TEST(OutputTest, ErrorOutputMarkov1) { checkErrorOutput(L"tests/Markov1.IN", L"Error: \"}\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov2) { checkErrorOutput(L"tests/Markov2.IN", L"Error: \"->\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov3) { checkErrorOutput(L"tests/Markov3.IN", L"Error: \"dafe\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov4) { checkErrorOutput(L"tests/Markov4.IN", L"Error: \"{\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov5) { checkErrorOutput(L"tests/Markov5.IN", L"Error: EOF expected\n"); }
TEST(OutputTest, ErrorOutputMarkov6) { checkErrorOutput(L"tests/Markov6.IN", L"Error: EOF expected\n"); }
TEST(OutputTest, ErrorOutputMarkov7) { checkErrorOutput(L"tests/Markov7.IN", L"Error: string expected\n"); }
TEST(OutputTest, ErrorOutputMarkov8) { checkErrorOutput(L"tests/Markov8.IN", L"Error: \"->\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov9) { checkErrorOutput(L"tests/Markov9.IN", L"Error: \"->\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov10) { checkErrorOutput(L"tests/Markov10.IN", L"Error: \"dafe\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov11) { checkErrorOutput(L"tests/Markov11.IN", L"Error: \"dafe\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov12) { checkErrorOutput(L"tests/Markov12.IN", L"Error: \":\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov13) { checkErrorOutput(L"tests/Markov13.IN", L"Error: \"}\" expected\n"); }
TEST(OutputTest, ErrorOutputMarkov14) { checkErrorOutput(L"tests/Markov14.IN", L"Error: \"(\" expected\n"); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
