//
// Created by corbi on 11/1/2021.
//

#ifndef INC_236PROJECT1_HEADER_H
#define INC_236PROJECT1_HEADER_H

#include <iostream>
#include <vector>
#include "DatalogProgram.h"
class Header {
private:
    std::vector<std::string> attributes;

public:
    Header() = default;
    ~Header() = default;
    std::string toString();
    void addHeader(std::string headtoadd)
    {
        attributes.push_back(headtoadd);
    }
    std::string getAttributes(size_t index) const
    {
        return attributes.at(index);
    }
    std::size_t getattributessize() const {
        return attributes.size();
    }
    std::vector<std::string> attributesvect() {
        return attributes;
    }
};

#endif //INC_236PROJECT1_HEADER_H
