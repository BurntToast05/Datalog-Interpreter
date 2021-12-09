//
// Created by corbi on 11/1/2021.
//

#include "Interpreter.h"
#include "graph.h"

int rulecount = 0;
bool selfloopcheck = true;

Interpreter::Interpreter(DatalogProgram datalog) {
    datalogtointerpret = datalog;
    CreateRelations();
    //EvaluateQueries();
    ++rulecount;
    std::cout << "Dependency Graph" << std::endl;
    Graph graph = Graph(datalogtointerpret);
    graph.PrintDependency();
    std::cout << "Rule Evaluation" << std::endl;
    std::map<int, std::set<int>> scc = graph.getSCC();
    for (auto it=scc.begin(); it!=scc.end(); ++it) {
        countofrules = 0;
        std::cout << "SCC: ";
        std::string str = "";
        if (it->second.empty() == false) {
            for (auto hi = it->second.begin(); hi !=
                                               it->second.end(); ++hi) {
                auto s = std::to_string(*hi);
                str += "R" + s + ",";
            }
            str.pop_back();
            std::cout << str;
        }
        std::cout << std::endl;
        if ((it->second).size() == 1)
        {
            selfloopcheck = graph.checkSelfDependency(*(it->second).begin());
        }
        EvaluateRules(it->second);
        std::cout << str;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Query Evaluation" << std::endl;
    EvaluateQueries();
}

void Interpreter::CreateRelations() {
    schemestoAdd = datalogtointerpret.getSchemes();
    for (size_t i = 0; i < schemestoAdd.size(); ++i) {
        Header schemeheader = getHeader(schemestoAdd.at(i));
        Relation relation = Relation(schemestoAdd.at(i).getId(), schemeheader);
        relationvect.push_back(relation);
        database.addtomap(schemestoAdd.at(i).getId(), relation);
    }
    factstoAdd = datalogtointerpret.getFacts();
    for (size_t i = 0; i < factstoAdd.size(); ++i) {
        Tuple tuple = getTuple(factstoAdd.at(i));
        for (size_t k = 0; k < relationvect.size(); ++k) {
            if (factstoAdd.at(i).getId() == relationvect.at(k).getname()) {
                database.addfacttomap(factstoAdd.at(i).getId(), tuple);
            }
        }
    }
}


Header Interpreter::getHeader(Predicate &schemetoevaluate) {
    std::vector<Parameter> headervector = schemetoevaluate.getParameterVector();
    Header header;
    for (size_t i = 0; i < headervector.size(); ++i) {
        header.addHeader(headervector.at(i).toString());
    }
    return header;
}

Tuple Interpreter::getTuple(Predicate &schemetoevaluate) {
    std::vector<Parameter> tuplevector = schemetoevaluate.getParameterVector();
    Tuple tuples;
    for (size_t i = 0; i < tuplevector.size(); ++i) {
        tuples.addValues(tuplevector.at(i).toString());
    }
    return tuples;
}

void Interpreter::relationtostring() {
    database.toString();
}

void Interpreter::UpdateTuplesOnMap() {
    /*factstoAdd = datalogtointerpret.getFacts();
    for (size_t k = 0; k < factstoAdd.size(); ++k)
    {
            Tuple tuple = getTuple(factstoAdd.at(k));
            for (size_t i = 0; i < relationvect.size(); ++i)
            {
                if (factstoAdd.at(k).getId() == relationvect.at(i).getname())
                {
                    size_t h = 0;
                    for (size_t j = 0; j < relationvect.at(i).getheader().getattributessize(); ++j)
                    {
                        database.addfacttomap(relationvect.at(i).getheader().getAttributes(j), tuple.getvalueat(h));
                        ++h;
                    }
                }
            }
    }*/
}

void Interpreter::EvaluateQueries() {
    queries = datalogtointerpret.getQueries();
    for (size_t i = 0; i < queries.size(); ++i) {
        Predicate currentquery = queries.at(i);
        Relation currentrelation = database.getrelation(currentquery.getId());
        Relation relation = evaluatePredicate(currentquery);
        std::vector<std::string> mapseenvect;
        std::vector<int> columnsseenvect;
        size_t columnindex = 0;
        std::cout << currentquery.toString() << "?";
        bool nochange = true;
        bool containsvariable = false;
        for (size_t k = 0; k < currentquery.getParameterVector().size(); ++k) {
            if (currentquery.getParameters(k).constantcheck() == true) {
                relation = currentrelation.type1select(currentrelation, columnindex,
                                                       currentquery.getParameters(k).toString());
                currentrelation = relation;
                ++columnindex;
                nochange = false;
            } else {
                if (seenmap.count(currentquery.getParameters(k).toString()) > 0) {
                    int columntocompare = 0;
                    std::map<std::string, int>::iterator it = seenmap.find(currentquery.getParameters(k).toString());
                    if (it != seenmap.end()) {
                        columntocompare = it->second;
                    }
                    relation = relation.type2select(currentrelation, columnindex, columntocompare);
                    currentrelation = relation;
                    ++columnindex;
                    nochange = false;
                    containsvariable = true;
                } else {
                    seenmap.insert(std::pair<std::string, int>(currentquery.getParameters(k).toString(), columnindex));
                    mapseenvect.push_back(currentquery.getParameters(k).toString());
                    columnsseenvect.push_back(columnindex);
                    columnindex++;
                    containsvariable = true;
                }
            }
        }
        if (containsvariable == false) {
            if (!currentrelation.getvalues().empty()) {
                std::cout << " Yes(" << currentrelation.getvalues().size() << ")" << std::endl;
            } else {
                std::cout << " No" << std::endl;
            }
        } else if (containsvariable == true) {
            if (nochange == false) {
                currentrelation = currentrelation.project(columnsseenvect);
            }
            currentrelation = currentrelation.rename(mapseenvect);
            if (currentrelation.getvalues().size() > 0) {
                std::cout << " Yes(" << currentrelation.getvalues().size() << ")" << std::endl;
                std::cout << currentrelation.toString();
            } else {
                std::cout << " No" << std::endl;
            }
        }
        seenmap.clear();
    }
}


Relation Interpreter::evaluatePredicate(Predicate &pred) {
    Tuple tuple = getTuple(pred);
    Relation relationtoreturn;
    for (size_t i = 0; i < schemestoAdd.size(); ++i) {
        Header schemeheader = getHeader(schemestoAdd.at(i));
        relationtoreturn = Relation(schemestoAdd.at(i).getId(), schemeheader);
        relationvectquery.push_back(relationtoreturn);
        databasequery.addtomap(schemestoAdd.at(i).getId(), relationtoreturn);
    }
    for (size_t k = 0; k < relationvectquery.size(); ++k) {
        if (pred.getId() == relationvectquery.at(k).getname()) {
            databasequery.addfacttomap(pred.getId(), tuple);
            relationtoreturn.addTuple(tuple);
        }
    }
    return relationtoreturn;
}

bool Interpreter::EvaluateRules(std::set<int> indexes) {
    rules = datalogtointerpret.getRules();
    bool changedatabase = true;
    bool masterchange = false;
    for (int i : indexes) {
        changedatabase = false;
        Rule currentrule = rules.at(i);
        Predicate headpredicate = rules.at(i).getHeadPredicate();
        for (size_t z = 0; z < currentrule.getBodyPredicates().size(); ++z) {
            Predicate currentquery = currentrule.getBodyPredicates().at(z);
            Relation currentrelation = database.getrelation(currentquery.getId());
            Relation relation = evaluatePredicate(currentquery);
            std::vector<std::string> mapseenvect;
            std::vector<int> columnsseenvect;
            size_t columnindex = 0;
            bool nochange = true;
            bool containsvariable = false;
            for (size_t k = 0; k < currentquery.getParameterVector().size(); ++k) {
                if (currentquery.getParameters(k).constantcheck() == true) {
                    relation = currentrelation.type1select(currentrelation, columnindex,
                                                           currentquery.getParameters(k).toString());
                    currentrelation = relation;
                    ++columnindex;
                    nochange = false;
                } else {
                    if (seenmap.count(currentquery.getParameters(k).toString()) > 0) {
                        int columntocompare = 0;
                        std::map<std::string, int>::iterator it = seenmap.find(
                                currentquery.getParameters(k).toString());
                        if (it != seenmap.end()) {
                            columntocompare = it->second;
                        }
                        relation = relation.type2select(currentrelation, columnindex, columntocompare);
                        currentrelation = relation;
                        ++columnindex;
                        nochange = false;
                        containsvariable = true;
                    } else {
                        seenmap.insert(
                                std::pair<std::string, int>(currentquery.getParameters(k).toString(), columnindex));
                        mapseenvect.push_back(currentquery.getParameters(k).toString());
                        columnsseenvect.push_back(columnindex);
                        columnindex++;
                        containsvariable = true;
                    }
                }
            }
            if (containsvariable == false) {
                if (!currentrelation.getvalues().empty()) {
                    intermediaterelations.push_back(currentrelation);
                } else {
                    intermediaterelations.push_back(currentrelation);
                }
            } else if (containsvariable == true) {
                if (nochange == false) {
                    currentrelation = currentrelation.project(columnsseenvect);
                }
                currentrelation = currentrelation.rename(mapseenvect);
                if (currentrelation.getvalues().size() > 0) {
                    intermediaterelations.push_back(currentrelation);
                } else {
                    intermediaterelations.push_back(currentrelation);
                }
            }
            seenmap.clear();
        }
        std::cout << currentrule.toString() << "."<< std::endl;

        /////do stuff here for rules
        if (intermediaterelations.size() == 1) {
            Relation joinrelations = intermediaterelations.at(0);
            ///get rid of this for input 49 to work
            std::vector<int> alikecolumns;
            for (size_t l = 0; l < headpredicate.getParameterVector().size(); ++l) {
                for (size_t b = 0; b < joinrelations.getheader().getattributessize(); ++b) {
                    if (joinrelations.getheader().getAttributes(b) ==
                        headpredicate.getParameters(l).toString()) {
                        alikecolumns.push_back(b);
                    }
                }
            }
            Relation databaserelation = database.getrelation(headpredicate.getId());
            joinrelations = joinrelations.project(alikecolumns);
            //joinrelations = joinrelations.reorder(headpredicate.getParameterVector());
            std::vector<std::string> renamevect;
            for (size_t a = 0; a < databaserelation.getheader().getattributessize(); ++a) {
                renamevect.push_back(databaserelation.getheader().getAttributes(a));
            }
            joinrelations = joinrelations.rename(renamevect);
            joinrelations.updateName(headpredicate.getId());
            //// get rid of this for 49 to work
            bool seen = false;
            for (Tuple t : joinrelations.getvalues()) {
                changedatabase = database.addfacttomap(joinrelations.getname(), t);
                if (changedatabase != true)
                {
                    joinrelations.removeTuple(t);
                }
                if (changedatabase == true && seen == false)
                {
                    seen = true;
                }
            }
            if (seen == true) {
                masterchange = true;
                std::cout << joinrelations.toString();
            }
        }
        else if (intermediaterelations.size() > 1) {
            Relation previousrelation;
            Relation joinrelation;
            for (size_t q = 0; q < intermediaterelations.size(); ++q) {
                if (q <= intermediaterelations.size() - 2) {
                    if (q == 0) {
                        joinrelation = intermediaterelations.at(q).join(intermediaterelations.at(q + 1));
                    }
                    if (q > 0) {
                        joinrelation = previousrelation.join(intermediaterelations.at(q + 1));
                    }
                    joinrelation.updateName(headpredicate.getId());
                    std::vector<int> alikecolumns;
                    for (size_t l = 0; l < headpredicate.getParameterVector().size(); ++l) {
                        for (size_t b = 0; b < joinrelation.getheader().getattributessize(); ++b) {
                            if (joinrelation.getheader().getAttributes(b) ==
                                headpredicate.getParameters(l).toString()) {
                                alikecolumns.push_back(b);
                            }
                        }
                    }
                    if (q == intermediaterelations.size() - 2) {
                        joinrelation = joinrelation.project(alikecolumns);
                        Relation databaserelation = database.getrelation(headpredicate.getId());
                        //reorder function only works for 2 paramaters
                        //joinrelation = joinrelation.reorder(headpredicate.getParameterVector());
                        std::vector<std::string> renamevect;
                        for (size_t a = 0; a < databaserelation.getheader().getattributessize(); ++a) {
                            renamevect.push_back(databaserelation.getheader().getAttributes(a));
                        }
                        joinrelation = joinrelation.rename(renamevect);
                        bool seen = false;
                        for (Tuple t : joinrelation.getvalues()) {
                            changedatabase = database.addfacttomap(joinrelation.getname(), t);
                            if (changedatabase != true)
                            {
                                joinrelation.removeTuple(t);
                            }
                            if (changedatabase == true && seen == false)
                            {
                                seen = true;
                            }
                        }
                        if (seen == true) {
                            masterchange = true;
                            std::cout << joinrelation.toString();
                        }
                    }
                    previousrelation = joinrelation;
                }
            }
        }
        intermediaterelations.clear();
    }
    if (masterchange == true && (indexes.size() > 1 || selfloopcheck == true)) {
        ++countofrules;
        EvaluateRules(indexes);
    }
    if (masterchange != true || (selfloopcheck == false && indexes.size() == 1)) {
        std::cout << countofrules + 1 << " passes: ";
    }
    return masterchange;
}

void Interpreter::fixedalgorithm() {

}
