//
// Created by corbi on 9/15/2021.
//

#ifndef COMMA_AUTOMATON_H
#define COMMA_AUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //COMMA_AUTOMATON_H
