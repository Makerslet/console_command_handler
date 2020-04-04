#include "file_printer.h"

#include <fstream>
#include <chrono>
#include <experimental/filesystem>

file_printer::file_printer()
{}

void file_printer::update(const std::string& out)
{
    write(out);
}

void file_printer::write(const std::string& out)
{
    if(_file_name.empty())
        init_file_name();

    std::ofstream fstream(_file_name);
    if(fstream.is_open()) {
        std::string error = "can't open file " + _file_name;
        throw std::runtime_error(error);
    }
    fstream << out << std::endl;
    fstream.close();
}

void file_printer::init_file_name()
{
    auto now = std::chrono::system_clock::now();
    _file_name = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}
