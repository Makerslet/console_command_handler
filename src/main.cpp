#include "commands_factory.h"
#include "command_handler.h"
#include "console_printer.h"
#include "file_printer.h"
#include "args_parser.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

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


    std::string argument;
    commands_factory cmd_factory;
    command_type cmd_type;
    command_handler cmd_handler(result.value());

    auto console_out = std::make_shared<console_printer>();
    auto file_out = std::make_shared<file_printer>();

    cmd_handler.subscribe(console_out);
    cmd_handler.subscribe(file_out);

    do {
        std::getline(std::cin, argument);
        auto command = cmd_factory.create_command(argument);
        cmd_type = command->type();
        cmd_handler.add_command(std::move(command));

    } while(cmd_type != command_type::finish);

    return 0;
}


