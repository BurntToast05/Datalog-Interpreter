#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include <iostream>

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    
    void toString()
    {
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            tokens.at(i)->toString();
        }
    }
    void totalTokens(){
        std::cout << "Total Tokens = " << tokens.size();
    }

};

#endif // LEXER_H

