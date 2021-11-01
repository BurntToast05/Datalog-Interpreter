//
// Created by corbi on 9/28/2021.
//

#ifndef INC_236PROJECT1_RULE_H
#define INC_236PROJECT1_RULE_H

#include <iostream>
#include "Predicate.h"
class Rule {
private:
    Predicate headPredicate = Predicate("nothing");
    std::vector<Predicate> bodyPredicates;

public:
    Rule(Predicate predicate)
    {
        headPredicate = predicate;
    };

    ~Rule() = default;

    std::string toString();
    void addPredicate(Predicate predicateToAdd)
    {
        bodyPredicates.push_back(predicateToAdd);
    }
    void setHeadPredicate(Predicate headPred)
    {
        headPredicate = headPred;
    }
    void addBodyPredicate(Predicate bodyPred)
    {
        bodyPredicates.push_back(bodyPred);
    }
};
#endif //INC_236PROJECT1_RULE_H
