//
// Created by corbi on 9/28/2021.
//

#ifndef INC_236PROJECT1_PREDICATE_H
#define INC_236PROJECT1_PREDICATE_H
#include "Parameter.h"
#include <vector>
class Predicate {
    std::vector<Parameter> parameters;
    std::string id;

public:
    Predicate(std::string idToAdd) {
        id = idToAdd;
    };

    ~Predicate() = default;

    std::string toString();
    std::string getId()
    {
        return id;
    }
    void addParameter(Parameter parameterToAdd);
    Parameter getParameters(size_t index)
    {
        return parameters.at(index);
    }
    std::vector<Parameter> getParameterVector()
    {
        return parameters;
    }
    size_t sizeOfParameters()
    {
        return parameters.size();
    }
    void setId(std::string idToSet)
    {
        id = idToSet;
    }
};
#endif //INC_236PROJECT1_PREDICATE_H
