//
// Created by corbi on 9/15/2021.
//
#include "RightParenAutomaton.h"
void RightParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}
