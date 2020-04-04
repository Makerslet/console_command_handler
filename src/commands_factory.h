#ifndef COMMANDS_FACTORY_H
#define COMMANDS_FACTORY_H

#include "base_command.h"

#include <memory>

class commands_factory
{
public:
    std::unique_ptr<base_command> create_command(const std::string&);
};

#endif // COMMANDS_FACTORY_H
