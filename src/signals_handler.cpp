#include "signals_handler.h"

void signals_handler::set_state(std::shared_ptr<command_handler> handler)
{
    _handler = handler;
}
void signals_handler::handle_sigint(int)
{
    auto handler_sptr = _handler.lock();
    if(handler_sptr)
        handler_sptr->stop_handling();

    std::exit(0);
}
