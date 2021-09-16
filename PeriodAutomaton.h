//
// Created by corbi on 9/15/2021.
//

#ifndef PERIOD_AUTOMATON_H
#define PERIOD_AUTOMATON_H
#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PERIOD_AUTOMATON_H
