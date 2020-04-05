#ifndef COMMANDS_H
#define COMMANDS_H

#include "base_command.h"

#include <string>

struct open_scope_command : base_command {
    open_scope_command(uint64_t ts) :
        base_command(command_type::open_scope, ts) {}
};

struct close_scope_command : base_command {
    close_scope_command(uint64_t ts) :
        base_command(command_type::close_scope, ts) {}
};

struct text_command : base_command {
    text_command(const std::string& cmd, uint64_t ts) :
        base_command(command_type::text, ts),
        _info(cmd) {}

    const std::string& info() const {
        return _info;
    }
private:
    std::string _info;
};

struct finish_command : base_command {
    finish_command(uint64_t ts) :
        base_command(command_type::finish, ts) {}
};

#endif // COMMANDS_H
