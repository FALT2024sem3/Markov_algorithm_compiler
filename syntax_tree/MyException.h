#if !defined(EXCEPTION)
#define EXCEPTION

#include <exception>
#include <string>
class MyException : public std::exception
{
public:
    // Конструктор, принимающий строку с описанием ошибки и строки с ошибкой
    MyException(const std::string &message_, int line_) : message(message_), line(line_) {}

    // Переопределение виртуального метода what(), возвращающего описание ошибки
    const char *what() const noexcept override
    {
        return message.c_str();
    }
    // Возвращаем номер строки с ошибкой
    int GetLineNumber()
    {
        return line;
    }

private:
    std::string message; // Строка, содержащая описание ошибки
    int line{};          // Номер строки с ошибкой
};

#endif // MACRO
