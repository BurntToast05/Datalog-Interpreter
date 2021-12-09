//
// Created by corbi on 9/28/2021.
//

#ifndef INC_236PROJECT1_PARAMETER_H
#define INC_236PROJECT1_PARAMETER_H
#include <string>
class Parameter {
    std::string parameter;
    bool isConstant;

public:
    Parameter(std::string parameterStringToAdd, bool constant) {
        parameter = parameterStringToAdd;
        isConstant = constant;
    };

    ~Parameter() = default;
    std::string toString();
    bool constantcheck()
    {
        return isConstant;
    }
};
#endif //INC_236PROJECT1_PARAMETER_H
