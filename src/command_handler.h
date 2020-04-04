#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "base_command.h"
#include "base_publisher.h"

#include <memory>

class command_handler : public base_publisher
{
public:
    command_handler(std::size_t);
    void add_command(std::unique_ptr<base_command>&&);

    void subscribe(std::shared_ptr<base_subscriber>) override;

private:
    void notify();

private:
    std::size_t _bulk_length;
    std::size_t _scope_level;

    std::vector<std::weak_ptr<base_subscriber>> _subscribers;
};

#endif // COMMAND_HANDLER_H
