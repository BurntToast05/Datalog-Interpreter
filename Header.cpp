//
// Created by corbi on 11/1/2021.
//
#include <iostream>
#include <vector>
#include "Header.h"

std::string Header::toString() {
    std::string str;
    for (size_t i = 0; i < attributes.size(); ++i)
    {
        str += attributes.at(i);
    }
    return str;
}
