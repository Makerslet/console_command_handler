#include "command_handler.h"

command_handler::command_handler(std::size_t bulk_length) :
    _bulk_length(bulk_length), _scope_level(0)
{}

void command_handler::add_command(std::unique_ptr<base_command>&&)
{

}

void command_handler::subscribe(std::shared_ptr<base_subscriber> subscriber)
{
    _subscribers.push_back(subscriber);
}

void command_handler::notify()
{
    std::string string;
    for(auto subscriber : _subscribers)
    {
        auto shared_subscriber = subscriber.lock();
        if(shared_subscriber)
            shared_subscriber->update(string);
    }
}
