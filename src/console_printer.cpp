#include "console_printer.h"
#include <iostream>

console_printer::console_printer()
{}

void console_printer::update(uint64_t, const std::string &out)
{
    std::cout << out << std::endl;
}
