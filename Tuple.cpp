//
// Created by corbi on 11/1/2021.
//
#include "Tuple.h"

std::string Tuple::toString() {
    std::string str;
    for (size_t i = 0; i < values.size(); ++i)
    {
        str += values.at(i);
    }
    return str;
}
