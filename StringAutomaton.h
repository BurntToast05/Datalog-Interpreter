//
// Created by corbi on 9/15/2021.
//

#ifndef INC_236PROJECT1_STRINGAUTOMATON_H
#define INC_236PROJECT1_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //INC_236PROJECT1_STRINGAUTOMATON_H
