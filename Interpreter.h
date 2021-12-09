//
// Created by corbi on 11/1/2021.
//

#ifndef INC_236PROJECT1_INTERPRETER_H
#define INC_236PROJECT1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Header.h"
#include "Tuple.h"
#include "Database.h"
class Interpreter {
private:
    DatalogProgram datalogtointerpret;
    std::vector<Header> schemeheaders;
    Database database;
    Database databasequery;
    std::vector<Relation> relationvect;
    std::vector<Relation> relationvectquery;
    std::vector<Relation> intermediaterelations;
    std::vector<Predicate> schemestoAdd;
    std::vector<Predicate> factstoAdd;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::map<std::string, int> seenmap;
    int mapindex = 0;
    int countofrules;

public:
    Interpreter(DatalogProgram datalog);
    ~Interpreter() = default;

    void CreateRelations();
    void UpdateTuplesOnMap();
    Header getHeader(Predicate &schemetoevaluate);
    Tuple getTuple(Predicate &schemetoevaluate);
    void relationtostring();
    void EvaluateQueries();
    Relation evaluatePredicate(Predicate &p);
    bool EvaluateRules(std::set<int> indexes);
    void fixedalgorithm();
};


#endif //INC_236PROJECT1_INTERPRETER_H
