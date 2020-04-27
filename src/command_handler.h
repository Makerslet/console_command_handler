#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "base/base_command.h"
#include "base/base_publisher.h"

#include <memory>
#include <map>

/**
 * @brief Класс обработки команд
 */
class command_handler : public base_publisher
{
    /**
     * @brief Команды принадлежащие определенному scope
     */
    using scope_commands = std::vector<std::string>;
    /**
     * @brief Временная метка первой команды с scope и список команд
     */
    using commands_description = std::pair<uint64_t, scope_commands>;

public:
    /**
     * @brief Конструктор обработчика команд
     * @param bulk_length - размер пакета команд
     */
    command_handler(std::size_t bulk_length);
    /**
     * @brief Метод запуска команды в обработку
     * @param command - команда
     */
    void add_command(std::unique_ptr<base_command>&& command);

    void stop_handling();
private:
    /**
     * @brief Метод обработки оповещения подписчиков
     * @param timestamp - временная метка первой команды
     * @param string - информационная строка
     */
    void notify(uint64_t timestamp, const std::string& string);
    /**
     * @brief Метод обработки команды открытия scope
     */
    void handle_open_scope();
    /**
     * @brief Метод обработки команды закрытия scope
     */
    void handle_close_scope();
    /**
     * @brief Метод обработки команды завершения ввода
     */
    /**
     * @brief Метод обработки текстовой команды
     * @param timestamp - временная метка
     * @param str - текст команды
     */
    void handle_text_command(uint64_t timestamp, const std::string& str);
    /**
     * @brief Метод объединение текста команд
     * @param commands - объъединяемые команды
     */
    std::string prepare_str(const scope_commands& commands);

private:
    std::size_t _bulk_length;
    std::size_t _current_scope_level;

    std::vector<commands_description> _commands;
};

#endif // COMMAND_HANDLER_H
