#include "file_printer.h"

#include <fstream>

file_printer::file_printer()
{}

void file_printer::update(uint64_t timestamp,const std::string& out)
{
    write(timestamp, out);
}

void file_printer::write(uint64_t timestamp, const std::string& out)
{
    std::string file_name = std::to_string(timestamp) + ".log";
    std::ofstream fstream(file_name);
    if(!fstream.is_open()) {
        std::string error = "can't open file " + file_name;
        throw std::runtime_error(error);
    }

    fstream << out << std::endl;
    fstream.close();
}
