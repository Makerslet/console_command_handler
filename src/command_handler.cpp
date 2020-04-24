#include "command_handler.h"
#include "commands.h"

command_handler::command_handler(std::size_t bulk_length) :
    _bulk_length(bulk_length),
    _current_scope_level(0)
{
    _commands.emplace_back(commands_description()); // 0 scope
    _commands.emplace_back(commands_description()); // nested scopes
}

void command_handler::add_command(std::unique_ptr<base_command>&& command)
{
    switch (command->type()) {
        case command_type::open_scope: {
            handle_open_scope();
            break;
        }
        case command_type::close_scope: {
            handle_close_scope();
            break;
        }
        case command_type::finish : {
            handle_finish();
            break;
        }
        case command_type::text: {
            handle_text_command(command->timestamp(),
                                (dynamic_cast<text_command*>(command.get()))->info());
            break;
        }
    }
}


void command_handler::handle_open_scope()
{
    if(_current_scope_level > 0)
    {
        ++_current_scope_level;
        return;
    }

    // отправить на выполнение команды нулевого scope
    // если он не пустой
    commands_description& commands_scope = _commands[_current_scope_level];

    if(!commands_scope.second.empty())
    {
        notify(commands_scope.first, prepare_str(commands_scope.second));
        commands_scope.second.clear();
    }

    //проинициализировать вложенный scope
    _current_scope_level = 1;

    commands_scope = _commands[_current_scope_level];
    commands_scope.first = 0;
    commands_scope.second.clear();
}

void command_handler::handle_close_scope()
{
    if(_current_scope_level == 0)
    {
        std::string error = "error close scope";
        throw std::logic_error(error);
    }
    else if(_current_scope_level == 1)
    {
        commands_description& commands = _commands[_current_scope_level];
        if(!commands.second.empty())
        {
            notify(commands.first, prepare_str(commands.second));
            commands.first = 0;
            commands.second.clear();
        }
    }

    --_current_scope_level;
}

void command_handler::handle_finish()
{
    if(_current_scope_level == 0)
    {
        commands_description& commands = _commands[_current_scope_level];
        if(!commands.second.empty())
            notify(commands.first, prepare_str(commands.second));
    }
}

void command_handler::handle_text_command(uint64_t timestamp, const std::string& str)
{
    size_t index = _current_scope_level > 0 ? 1 : 0;
    commands_description& commands = _commands[index];

    if(commands.second.empty())
        commands.first = timestamp;
    commands.second.push_back(str);

    if(_current_scope_level == 0)
    {
        if(commands.second.size() == _bulk_length)
        {
            notify(commands.first, prepare_str(commands.second));
            commands.second.clear();
        }
    }
}

std::string command_handler::prepare_str(const scope_commands& commands)
{
    std::string result("bulk: ");
    for(const auto& command : commands)
        result += command + ", ";

    result.erase(result.length() - 2, 2);
    return result;
}


void command_handler::subscribe(std::shared_ptr<base_subscriber> subscriber)
{
    _subscribers.push_back(subscriber);
}

void command_handler::notify(uint64_t timestamp,const std::string& string)
{
    for(auto subscriber : _subscribers)
    {
        auto shared_subscriber = subscriber.lock();
        if(shared_subscriber)
            shared_subscriber->update(timestamp, string);
    }
}
