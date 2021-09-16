//
// Created by corbi on 9/15/2021.
//
#include "StringAutomaton.h"
void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'' ) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\'' ) {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '\n' && index < static_cast<int>(input.size()))
    {
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else if (index == static_cast<int>(input.size()))
    {
        inputRead++;
        type = TokenType::UNDEFINED;
        return;
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}
void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'' ) {
        inputRead++;
        index++;
        S1(input);
    }
}