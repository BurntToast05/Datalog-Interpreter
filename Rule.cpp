//
// Created by corbi on 9/28/2021.
//

#include "Rule.h"

std::string Rule::toString() {
    std::string str;
    str += headPredicate.toString() + " :- ";
    for (size_t i = 0; i < bodyPredicates.size(); ++i)
    {
        str += bodyPredicates.at(i).toString();
        if (i != bodyPredicates.size()-1)
        {
            str += ",";
        }
    }
    return str;
}
