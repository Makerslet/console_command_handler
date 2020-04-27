#include "commands_factory.h"
#include "command_handler.h"
#include "console_printer.h"
#include "file_printer.h"
#include "args_parser.h"
#include "signals_handler.h"

#include <csignal>
#include <iostream>

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

namespace bpo = boost::program_options;

int main (int argc, char** argv)
{
    args_parser parser;
    std::optional<size_t> result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;

    commands_factory cmd_factory;
    auto cmd_handler = std::make_shared<command_handler>(result.value());

    signals_handler::set_state(cmd_handler);
    std::signal(SIGINT, signals_handler::handle_sigint);

    auto console_out = std::make_shared<console_printer>();
    cmd_handler->subscribe(console_out);

    auto file_out = std::make_shared<file_printer>();
    cmd_handler->subscribe(file_out);

    std::string argument;
    while(std::getline(std::cin, argument))
    {
        try {
            auto command = cmd_factory.create_command(argument);
            cmd_handler->add_command(std::move(command));
        }
        catch(const std::logic_error& ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    cmd_handler->stop_handling();

    return 0;
}


