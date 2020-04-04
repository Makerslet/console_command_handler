#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "base_command.h"
#include "base_publisher.h"

#include <memory>
#include <map>

class command_handler : public base_publisher
{
    using scope_commands = std::vector<std::string>;
    using commands_description = std::pair<uint64_t, scope_commands>;

public:
    command_handler(std::size_t);
    void add_command(std::unique_ptr<base_command>&&);

    void subscribe(std::shared_ptr<base_subscriber>) override;

private:
    void notify(uint64_t, const std::string&);
    void handle_open_scope();
    void handle_close_scope();
    void handle_finish();
    void handle_text_command(const std::string& str);

    std::string prepare_str(const scope_commands&);
    uint64_t time_stamp();

private:
    std::size_t _bulk_length;
    std::size_t _current_scope_level;

    std::vector<std::weak_ptr<base_subscriber>> _subscribers;
    std::map<std::size_t, commands_description> _commands;
};

#endif // COMMAND_HANDLER_H
