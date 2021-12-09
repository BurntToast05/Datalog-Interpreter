//
// Created by corbi on 11/1/2021.
//

#include "Relation.h"
#include <bits/stdc++.h>
using namespace std;

std::string Relation::toString() const {
    std::string str;
    for (Tuple t : values) {
        str += " ";
        for (size_t i = 0; i < header.getattributessize(); ++i) {
            str += " " + header.getAttributes(i) + "=";
            if (i == header.getattributessize() - 1) {
                str += t.getvalueat(i).toString();
            } else {
                str += t.getvalueat(i).toString() += ",";
            }
        }
        if (header.getattributessize() > 0) {
            str += "\n";
        }
    }
    return str;
}

std::string Relation::toStringRelation() const {

    return std::string();
}

Relation Relation::type1select(Relation currentFacts, size_t columnindex, std::string columntomatch) {
    Relation relationtoreturn(name, header);
    for (Tuple t : values) {
        for (Tuple q : currentFacts.getvalues()) {
            for (size_t i = 0; i < header.getattributessize(); ++i) {
                if (i == columnindex) {
                    if (q.getvalueat(i).toString() == columntomatch) {
                        relationtoreturn.addTuple(q);
                    }
                }
            }
        }
    }
    return relationtoreturn;
}

Relation Relation::type2select(Relation currentFacts, size_t columnindex, size_t columntocompare) {
    Relation relationtoreturn(name, header);
    currentFacts.updateheader(header);
    for (Tuple t : values) {
        for (Tuple q : currentFacts.getvalues()) {
            for (size_t i = 0; i < header.getattributessize(); ++i) {
                for (size_t k = 0; k < currentFacts.getheader().getattributessize(); ++k) {
                    if (i == columnindex && k == columntocompare) {
                        if (q.getvalueat(i).toString() == q.getvalueat(k).toString()) {
                            relationtoreturn.addTuple(q);
                        }
                    }
                }
            }
        }
    }
    return relationtoreturn;
}

Relation Relation::project(std::vector<int> columnstokeep) {
    Header newheader;
    Relation relationtoreturn(name, header);
    for (size_t i = 0; i < header.getattributessize(); ++i) {
        if (invect(columnstokeep, i) == true) {
            newheader.addHeader(header.getAttributes(i));
        }
    }
    for (Tuple t : values) {
        Tuple tupletoadd;
        for (size_t i = 0; i < columnstokeep.size(); ++i) {
                tupletoadd.addValues(t.getvalueat(columnstokeep.at(i)).toString());
        }
        relationtoreturn.addTuple(tupletoadd);
    }
    relationtoreturn.updateheader(newheader);
    return relationtoreturn;
}

Relation Relation::rename(std::vector<std::string> eval) {
    Header headertoadd;
    for (size_t i = 0; i < eval.size(); ++i) {
        headertoadd.addHeader(eval.at(i));
    }
    Relation relation = Relation(name, headertoadd);
    relation.updateValues(values);
    return relation;
}

Relation Relation::join(Relation rel2) {
        Header mainheader = header;
        bool donotshare = true;
        //match values
        std::vector<int> rel1columnstomatch;
        std::vector<int> rel2columnstomatch;
    for (size_t i = 0; i < header.getattributessize(); ++i) {
        for (size_t k = 0; k < rel2.getheader().getattributessize(); ++k) {
            if (header.getAttributes(i) == rel2.getheader().getAttributes(k))
            {
                rel1columnstomatch.push_back(i);
                rel2columnstomatch.push_back(k);
            }
        }
    }

        //putting together header
        std::map<std::string, int> headermap;
        for (size_t i = 0; i < mainheader.getattributessize(); ++i) {
            headermap.insert(
                    std::pair<std::string, int>(header.getAttributes(i), i));
        }
        for (size_t i = 0; i < rel2.getheader().getattributessize(); ++i) {
            if (headermap.count(rel2.getheader().getAttributes(i)) == 0) {
                mainheader.addHeader(rel2.getheader().getAttributes(i));
            }
            if (headermap.count(rel2.getheader().getAttributes(i)) > 0) {
                donotshare = false;
            }
        }
        Relation relationtoreturn = Relation(name + rel2.getname(), mainheader);
        bool addedtuple = false;
        for (Tuple t : values) {
            for (Tuple q : rel2.getvalues()) {
                bool match = false;
                bool mastermatch = true;
                /*for (size_t i = 0; i < header.getattributessize(); ++i) {
                    for (size_t k = 0; k < rel2.getheader().getattributessize(); ++k) {
                        //main if else
                        if (rel2.getheader().getAttributes(k) == header.getAttributes(i)) {
                            if (t.getvalueat(i).toString() == q.getvalueat(k).toString()) {*/
                for (size_t i = 0; i < rel1columnstomatch.size(); ++i) {
                        if (t.getvalueat(rel1columnstomatch.at(i)).toString() ==
                            q.getvalueat(rel2columnstomatch.at(i)).toString()) {
                            match = true;
                        }
                        else
                        {
                            match = false;
                        }
                        if (match == false)
                        {
                            mastermatch = false;
                        }
                }
                if (mastermatch == true) {
                    for (size_t h = 0; h < rel2.getheader().getattributessize(); ++h) {
                        Tuple tupletoadd;
                        for (size_t c = 0; c < header.getattributessize(); ++c) {
                            tupletoadd.addValues(t.getvalueat(c).toString());
                            addedtuple = true;
                        }
                        for (size_t c = 0; c < rel2.getheader().getattributessize(); ++c) {
                            if (headermap.count(rel2.getheader().getAttributes(c)) == 0) {
                                tupletoadd.addValues(q.getvalueat(c).toString());
                                addedtuple = true;
                            }
                        }
                        if (addedtuple != false) {
                            relationtoreturn.addTuple(tupletoadd);
                        }
                    }
                } else if (donotshare == true) {
                    Tuple tupletoadd;
                    for (size_t h = 0; h < rel2.getheader().getattributessize(); ++h) {
                        Tuple tupletoadd;
                        for (size_t c = 0; c < header.getattributessize(); ++c) {
                            tupletoadd.addValues(t.getvalueat(c).toString());
                        }
                        for (size_t c = 0; c < rel2.getheader().getattributessize(); ++c) {
                            if (headermap.count(rel2.getheader().getAttributes(c)) == 0) {
                                tupletoadd.addValues(q.getvalueat(c).toString());
                                addedtuple = true;
                            }
                        }
                        if (addedtuple == true) {
                            relationtoreturn.addTuple(tupletoadd);
                        }
                    }
                }
            }
        }
    return relationtoreturn;
}

Relation Relation::reorder(std::vector<Parameter> headpred) {
    Relation relationtoreturn(name, header);
    for (size_t i = 0; i < relationtoreturn.getheader().getattributessize()-1; ++i)
    {
        if (relationtoreturn.getheader().getAttributes(i) != headpred.at(i).toString()) {

            for (Tuple t : values) {
                t = t.switchvalues(i, i+1);
                relationtoreturn.addTuple(t);
            }
        }
        else
        {
            for (Tuple t : values) {
                relationtoreturn.addTuple(t);
            }
        }
    }

    return relationtoreturn;
}

