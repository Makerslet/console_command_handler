#ifndef SUBSCRIBER_MOCK_H
#define SUBSCRIBER_MOCK_H

#include "base/base_subscriber.h"

struct subscriber_mock : base_subscriber {
    subscriber_mock() : _timestamp(0) {}

    void update(uint64_t timestamp, const std::string& str) override {
        _timestamp = timestamp;
        _output = str;
    }

    const std::string& output() const {
        return  _output;
    }

    uint64_t timestamp() const {
        return _timestamp;
    }

private:
    std::string _output;
    uint64_t _timestamp;
};

#endif // SUBSCRIBER_MOCK_H
