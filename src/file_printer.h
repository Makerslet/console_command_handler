#ifndef FILE_PRINTER_H
#define FILE_PRINTER_H

#include "base_subscriber.h"

class file_printer : public base_subscriber
{
public:
    file_printer();
    void update(const std::string&) override;

private:
    void init_file_name();
    void write(const std::string &out);

private:
    std::string _file_name;
};

#endif // FILE_PRINTER_H
