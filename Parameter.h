//
// Created by corbi on 9/28/2021.
//

#ifndef INC_236PROJECT1_PARAMETER_H
#define INC_236PROJECT1_PARAMETER_H
class Parameter {
    std::string parameter;

public:
    Parameter(std::string parameterStringToAdd) {
        parameter = parameterStringToAdd;
    };

    ~Parameter() = default;

    std::string toString();
};
#endif //INC_236PROJECT1_PARAMETER_H
