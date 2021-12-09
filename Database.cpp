//
// Created by corbi on 11/1/2021.
//

#include "Database.h"

void Database::toString() {
    for(auto it = databasemap.cbegin(); it != databasemap.cend(); ++it)
    {
        std::cout << "{" << (*it).first;
        std::string secondstring  = (*it).second.toString();
        std::cout <<": " << secondstring << "}\n";
    }
}

