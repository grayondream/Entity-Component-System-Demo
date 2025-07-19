#pragma once
#include <any>

enum class EventType {
    KeyBoard
};

class Event{
public:
    Event(EventType type) : _type(type) {}

    template<typename T>
    void setParam(const std::string& key, const T& value) {
        _param = value;
    }

    template<typename T>
    T getParam(const std::string& key) const {
        return std::any_cast<T>(_param);
    }
private:
    EventType _type;
    std::any _param;
};