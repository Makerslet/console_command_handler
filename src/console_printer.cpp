#include "console_printer.h"
#include <iostream>

console_printer::console_printer()
{}

void console_printer::update(const std::string &out)
{
    std::cout << out << std::endl;
}
