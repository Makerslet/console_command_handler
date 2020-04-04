#include "commands_factory.h"
#include "commands.h"

std::unique_ptr<base_command> commands_factory::create_command(const std::string& str)
{
    if(str == "{")
        return std::make_unique<open_scope_command>();
    else if(str == "}")
        return  std::make_unique<close_scope_command>();
    else if(str == "exit")
        return  std::make_unique<finish_command>();
    else
        return std::make_unique<text_command>(str);
}
