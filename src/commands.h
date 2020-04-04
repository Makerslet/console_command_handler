#ifndef COMMANDS_H
#define COMMANDS_H

#include "base_command.h"

#include <string>

struct open_scope_command : base_command {
    open_scope_command() :
        base_command(command_type::open_scope) {}
};

struct close_scope_command : base_command {
    close_scope_command() :
        base_command(command_type::close_scope) {}
};

struct text_command : base_command {
    text_command(const std::string& cmd) :
        base_command(command_type::text),
        _info(cmd) {}

    const std::string& info() const {
        return _info;
    }
private:
    std::string _info;
};

struct finish_command : base_command {
    finish_command() :
        base_command(command_type::finish) {}
};

#endif // COMMANDS_H
