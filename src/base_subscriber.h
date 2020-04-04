#ifndef BASE_SUBSCRIBER_H
#define BASE_SUBSCRIBER_H

#include <vector>
#include <string>

struct base_subscriber {
    virtual ~base_subscriber() = default;
    virtual void update(const std::string&) = 0;
};

#endif // BASE_SUBSCRIBER_H
