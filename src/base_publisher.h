#ifndef BASE_PUBLISHER_H
#define BASE_PUBLISHER_H

#include "base_subscriber.h"

#include <memory>

struct base_publisher {
    virtual ~base_publisher() = default;
    virtual void subscribe(std::shared_ptr<base_subscriber>) = 0;
};

#endif // BASE_PUBLISHER_H
