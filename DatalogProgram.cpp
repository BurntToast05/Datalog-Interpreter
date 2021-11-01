//
// Created by corbi on 9/28/2021.
//

#include <iostream>
#include <vector>
#include "DatalogProgram.h"

void DatalogProgram::toString() {
    std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
    for (size_t i = 0; i < schemes.size(); ++i)
    {
        std::cout << "  " << schemes.at(i).toString();
        std::cout << std::endl;
    }
    std::cout << "Facts(" << facts.size() << "):" << std::endl;
    for (size_t i = 0; i < facts.size(); ++i)
    {
        std::cout << "  " << facts.at(i).toString();
        std::cout << "." << std::endl;
    }
    std::cout << "Rules(" << rules.size() << "):" << std::endl;
    for (size_t i = 0; i < rules.size(); ++i)
    {
        std::cout << "  " << rules.at(i).toString();
        std::cout << "." << std::endl;
    }
    std::cout << "Queries(" << queries.size() << "):" << std::endl;
    for (size_t i = 0; i < queries.size(); ++i)
    {
        std::cout << "  " << queries.at(i).toString();
        std::cout << "?" << std::endl;
    }
}

void DatalogProgram::addScheme(Predicate schemeToAdd) {
    schemes.push_back(schemeToAdd);
}

void DatalogProgram::addFacts(Predicate factToAdd) {
    facts.push_back(factToAdd);
}

void DatalogProgram::addRules(Rule rulesToAdd) {
    rules.push_back(rulesToAdd);
}

void DatalogProgram::addQueries(Predicate query) {
    queries.push_back(query);
}

void DatalogProgram::printDomains() {
    std::vector<Predicate> listOfFacts = facts;
    std::vector<Parameter> stringParameters;
    for (size_t i = 0; i < listOfFacts.size(); ++i)
    {
        //stringParameters.push_back(listOfFacts.at(i).getParameters(i));
        for (size_t j = 0; j < listOfFacts.at(i).sizeOfParameters(); ++j)
        {
            bool inParameter = false;
            for (size_t k = 0; k < stringParameters.size(); ++k)
            {
                if (listOfFacts.at(i).getParameters(j).toString() == stringParameters.at(k).toString())
                {
                    inParameter = true;
                }
            }
            if (inParameter == false)
            {
                stringParameters.push_back(listOfFacts.at(i).getParameters(j));
                domains.insert(listOfFacts.at(i).getParameters(j).toString());
            }
        }
    }
    std::cout << "Domain(" << domains.size() << "):" << std::endl;
    for (auto it = domains.begin(); it != domains.end(); ++it) {
        std::cout << "  " << *it;
        std::cout << std::endl;
    }
}
