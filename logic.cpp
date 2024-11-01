#include "logic.h"

bool logic::in_port::get_value() const
{
    auto ptr = this->out.lock();
    if (ptr) {
        return ptr->get_value();
    }
    throw "get value error";
    return false;
}
