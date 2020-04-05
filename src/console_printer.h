#ifndef CONSOLE_PRINTER_H
#define CONSOLE_PRINTER_H

#include "base/base_subscriber.h"

/**
 * @brief Класс производящий вывод полученной команды на стандартный вывод
 */
class console_printer : public base_subscriber
{
public:
    /**
     * @brief Конструктор
     */
    console_printer();
    /**
     * @brief Обработка команда от publisher'а
     * @param str - текст
     */
    void update(uint64_t, const std::string& str) override;
};

#endif // CONSOLE_PRINTER_H
