#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

enum class command_type {
    open_scope,
    close_scope,
    finish,
    text
};

struct base_command {
    base_command(command_type type) :
        _type(type) {}

    virtual ~base_command() = default;

    command_type type() const {
        return _type;
    };

private:
    command_type _type;
};

#endif // BASE_COMMAND_H
