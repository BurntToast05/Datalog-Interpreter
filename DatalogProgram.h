//
// Created by corbi on 9/28/2021.
//

#ifndef INC_236PROJECT1_DATALOGPROGRAM_H
#define INC_236PROJECT1_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include <set>
class DatalogProgram {
    std::vector <Predicate> schemes;
    std::vector <Predicate> facts;
    std::vector <Predicate> queries;
    std::vector <Rule> rules;
    std::set<std::string> domains;
public:
    DatalogProgram() {};

    ~DatalogProgram() = default;

    void addScheme(Predicate schemeToAdd);
    void addFacts(Predicate factToAdd);
    void addQueries(Predicate queryToAdd);
    void addRules(Rule rulesToAdd);
    void printDomains();
    void toString();
};
#endif //INC_236PROJECT1_DATALOGPROGRAM_H
