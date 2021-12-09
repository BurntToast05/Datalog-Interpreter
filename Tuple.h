//
// Created by corbi on 11/1/2021.
//

#ifndef INC_236PROJECT1_TUPLE_H
#define INC_236PROJECT1_TUPLE_H
//
// Created by corbi on 9/28/2021.
//
#include <iostream>
#include <vector>
class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple()=default;
    ~Tuple() = default;

    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }
    void addValues(std::string toadd)
    {
        values.push_back(toadd);
    }
    size_t getsize()
    {
        return values.size();
    }
    Tuple getvalueat(size_t index)
    {
        Tuple newtuple;
        newtuple.addValues(values.at(index));
        return newtuple;
    }
    Tuple switchvalues(size_t firstindex, size_t secondindex)
    {
        Tuple newtuple;
        std::string temp = values.at(firstindex);
        values.at(firstindex) = values.at(secondindex);
        values.at(secondindex) = temp;
        newtuple.addValues(values.at(0));
        newtuple.addValues(values.at(1));
        return newtuple;
    }
    Tuple getvalues()
    {
        Tuple newtuple;
        for (size_t i = 0; i < values.size(); ++i) {
            newtuple.addValues(values.at(i));
        }
        return newtuple;
    }

    std::string toString();
};

#endif //INC_236PROJECT1_TUPLE_H
