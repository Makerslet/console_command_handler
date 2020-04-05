#ifndef BASE_SUBSCRIBER_H
#define BASE_SUBSCRIBER_H

#include <vector>
#include <string>

/**
 * @brief Интерфейс подписчика
 */
struct base_subscriber {
    /**
     * @brief Деструктор подписчика
     */
    virtual ~base_subscriber() = default;
    /**
     * @brief Интерфейс получения уведомлений
     * @timestamp - временная метка
     * @str - информационная строка
     */
    virtual void update(uint64_t timestamp, const std::string& str) = 0;
};

#endif // BASE_SUBSCRIBER_H
