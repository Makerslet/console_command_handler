#include "command_handler.h"
#include "commands.h"

#include <chrono>

command_handler::command_handler(std::size_t bulk_length) :
    _bulk_length(bulk_length), _current_scope_level(0)
{}

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
            handle_text_command((dynamic_cast<text_command*>(command.get()))->info());
            break;
        }
    }
}


void command_handler::handle_open_scope()
{
    if(_current_scope_level == 0)
    {
        auto commands_iter = _commands.find(_current_scope_level);
        if(commands_iter != _commands.end())
        {
            auto& description = commands_iter->second;
            if(!description.second.empty())
            {
                notify(description.first, prepare_str(description.second));
                description.second.clear();
            }
        }
        else
            _commands[_current_scope_level] = commands_description();
    }

    ++_current_scope_level;
    if(_commands.find(_current_scope_level) == _commands.end())
        _commands[_current_scope_level] = commands_description();
    auto commands_iter = _commands.find(_current_scope_level);
    auto& description = commands_iter->second;
    description.first = 0;
    description.second.clear();
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
        scope_commands commands;
        uint64_t timestamp = 0;
        for(auto& scope : _commands)
        {
            if(scope.first == 0)
                continue;

            auto& description = scope.second;
            if(timestamp == 0)
                timestamp = description.first;

            for(const auto& command : description.second)
                commands.push_back(command);

            description.first = 0;
            description.second.clear();
        }

        if(!commands.empty())
            notify(timestamp, prepare_str(commands));
    }

    --_current_scope_level;
}

void command_handler::handle_finish()
{}

void command_handler::handle_text_command(const std::string& str)
{
    if(_commands.find(_current_scope_level) == _commands.end())
        _commands[_current_scope_level] = commands_description();

    auto commands_iter = _commands.find(_current_scope_level);
    auto& description = commands_iter->second;
    if(description.second.empty())
        description.first = time_stamp();
    description.second.push_back(str);

    if(_current_scope_level == 0)
    {
        if(description.second.size() == _bulk_length)
        {
            notify(description.first, prepare_str(description.second));
            description.second.clear();
        }
    }
}

std::string command_handler::prepare_str(const scope_commands& commands)
{
    std::string result("bulk: ");
    for(const auto& command : commands)
        result += command + ", ";

    result.erase(result.length() - 2, 1);
    return result;
}

uint64_t command_handler::time_stamp()
{
    auto now = std::chrono::system_clock::now();
    return  std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
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
