//
// Created by corbi on 9/15/2021.
//
#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
std::string str = "";
void IdAutomaton::S1(const std::string& input) {
    if (str != "Scheme" && str != "Fact" && str != "Rule" && str != "Querie") {
        if (isalnum(input[index])) {
            str += input[index];
            inputRead++;
            index++;
            S1(input);
        }
        else
        {
            return;
        }
    }
    else
    {
        Serr();
    }
}


