#ifndef FILE_PRINTER_H
#define FILE_PRINTER_H

#include "base_subscriber.h"

class file_printer : public base_subscriber
{
public:
    file_printer();
    void update(uint64_t,const std::string&) override;

private:
    void write(uint64_t timestamp, const std::string &out);
};

#endif // FILE_PRINTER_H
