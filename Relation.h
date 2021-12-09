//
// Created by corbi on 11/1/2021.
//

#ifndef INC_236PROJECT1_RELATION_H
#define INC_236PROJECT1_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <map>
#include <set>
class Relation {
private:
    std::set<Tuple> values;
    std::string name;
    Header header;

public:
    Relation(std::string nametoadd, Header headertoadd)
    {
        name = nametoadd;
        header = headertoadd;
    };
    Relation() = default;
    ~Relation() = default;

    void removeTuple(Tuple tupletoremove)
    {
        values.erase(tupletoremove);
    }
    void addTuple(Tuple tupletoadd)
    {
        values.insert(tupletoadd);
    }
    std::string toString() const;
    std::string toStringRelation() const;
    std::string getname() const {
        return name;
    }
    void updateName(std::string nametoadd) {
        name = nametoadd;
    }
    Header getheader()
    {
        return header;
    }
    void updateheaderindex(size_t index)
    {

        return ;
    }
    void updateheader(Header head)
    {
        header = head;
    }
    Relation type1select(Relation relation, size_t columnindex, std::string columntomatch);
    Relation type2select(Relation relation, size_t columnindex, size_t columntocompare);
    std::set<Tuple> getvalues()
    {
        return values;
    };
    Relation project(std::vector<int> columnstokeep);
    bool invect (std::vector<int> columns, int index)
    {
        for (size_t i = 0; i < columns.size(); ++i)
        {
            if (columns.at(i)==index)
            {
                return true;
            }
        }
        return false;
    }
    Relation rename(std::vector<std::string> eval);
    void updateValues(std::set<Tuple> valuestoadd)
    {
        values = valuestoadd;
    }
    Relation join (Relation rel2);
    Relation reorder (std::vector<Parameter> headpred);
    bool valueinrelation(Tuple t)
    {
        if (values.find(t) != values.end())
        {
            return true;
        }
        else {
            return false;
        }
    }




};
#endif //INC_236PROJECT1_RELATION_H
