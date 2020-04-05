#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <cstdint>

enum class command_type {
    open_scope,
    close_scope,
    finish,
    text
};

struct base_command {
    base_command(command_type type, uint64_t timestamp) :
        _type(type), _timestamp(timestamp) {}

    virtual ~base_command() = default;

    command_type type() const {
        return _type;
    };

    uint64_t timestamp() const {
        return _timestamp;
    }

private:
    command_type _type;
    uint64_t _timestamp;
};

#endif // BASE_COMMAND_H
