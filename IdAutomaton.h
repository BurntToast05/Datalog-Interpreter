//
// Created by corbi on 9/15/2021.
//

#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H
#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //IDAUTOMATON_H
