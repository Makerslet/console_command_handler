#ifndef FILE_PRINTER_H
#define FILE_PRINTER_H

#include "base/base_subscriber.h"

/**
 * @brief Класс производящий вывод полученной команды в файл
 */
class file_printer : public base_subscriber
{
public:
    /**
     * @brief Конструктор
     */
    file_printer();
    /**
     * @brief Обработка команды от publisher'а
     * @param timestamp - временная метка
     * @param out - текст
     */
    void update(uint64_t timestamp,const std::string& out) override;

private:
    /**
     * @brief Метод записи в файл
     * @param timestamp - временная метка
     * @param out - текст
     */
    void write(uint64_t timestamp, const std::string &out);
};

#endif // FILE_PRINTER_H
