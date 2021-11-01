//
// Created by corbi on 9/28/2021.
//

#include <iostream>
#include "Predicate.h"

std::string Predicate::toString() {
    std::string stringToAdd;
    stringToAdd += id + "(";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        stringToAdd += parameters.at(i).toString();
        if (i != parameters.size() - 1) {
            stringToAdd += ",";
        }
    }
    stringToAdd += ")";
    return stringToAdd;
}

void Predicate::addParameter(Parameter parameterToAdd) {
    parameters.push_back(parameterToAdd);
}

