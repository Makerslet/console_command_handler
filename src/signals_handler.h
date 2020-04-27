#ifndef SIGNALS_HANDLER_H
#define SIGNALS_HANDLER_H

#include "command_handler.h"

#include <memory>

class signals_handler
{
public:
    static void set_state(std::shared_ptr<command_handler>);
    static void handle_sigint(int);

private:
    inline static std::weak_ptr<command_handler> _handler;
};

#endif // SIGNALS_HANDLER_H
