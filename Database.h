//
// Created by corbi on 11/1/2021.
//

#ifndef INC_236PROJECT1_DATABASE_H
#define INC_236PROJECT1_DATABASE_H
#include "Relation.h"
#include <map>
class Database {
private:
    std::map<std::string, Relation> databasemap;
public:
    Database() = default;
    ~Database() = default;

    void addtomap(std::string toadd, Relation relationtoadd)
    {
        databasemap.insert ( std::pair<std::string,Relation>(toadd, relationtoadd));
    }
    bool addfacttomap(std::string ID, Tuple toadd)
    {
        std::map<std::string, Relation>::iterator it = databasemap.find(ID);
        if (it != databasemap.end()) {
            if (it->second.valueinrelation(toadd) == false) {
                it->second.addTuple(toadd);
                return true;
            }
        }
            return false;
    }
    bool indatabase(std::string ID, Tuple tocheck)
    {
        std::map<std::string, Relation>::iterator it = databasemap.find(ID);
        if (it != databasemap.end()) {
            if (it->second.valueinrelation(tocheck) == false) {
                return true;
            }
            else
            {return false;}
        }
    }
    void toString();
    Relation getrelation(std::string ID)
    {
        std::map<std::string, Relation>::iterator it = databasemap.find(ID);
        return it->second;
    }
    std::map<std::string, Relation> getmap()
    {
        return databasemap;
    }
};
#endif //INC_236PROJECT1_DATABASE_H
