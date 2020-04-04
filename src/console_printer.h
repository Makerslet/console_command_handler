#ifndef CONSOLE_PRINTER_H
#define CONSOLE_PRINTER_H

#include "base_subscriber.h"

class console_printer : public base_subscriber
{
public:
    console_printer();
    void update(const std::string&) override;
};

#endif // CONSOLE_PRINTER_H
