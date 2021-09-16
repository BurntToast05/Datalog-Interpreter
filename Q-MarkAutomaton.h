//
// Created by corbi on 9/15/2021.
//
#ifndef Q_MARK_AUTOMATON_H
#define Q_MARK_AUTOMATON_H
#include "Automaton.h"
class QMarkAutomaton : public Automaton
{
public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //Q_MARK_AUTOMATON_H
