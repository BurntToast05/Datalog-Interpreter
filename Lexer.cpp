#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q-MarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include <algorithm>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() = default;

//todo handle lexer mem

void Lexer::CreateAutomata() {
    automata.push_back(new CommentAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    // While there are more characters to tokenize
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton *maxAutomaton = automata.at(0);
        // TODO: you need to handle whitespace inbetween tokens
        if (input.substr(0, 1) == "\n") {
            input.erase(0, 1);
            lineNumber++;
            continue;
        }
        else if (isspace(input[0]))
        {
            input.erase(0, 1);
            continue;
        }
        else {

            // Here is the "Parallel" part of the algorithm
            //   Each automaton runs with the same input
            for (size_t i = 0; i < automata.size(); ++i) {
                int inputRead = automata.at(i)->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata.at(i);
                }
            }
            // Here is the "Max" part of the algorithm
            if (maxRead > 0) {
                Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
                lineNumber = lineNumber + maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
            }
                // No automaton accepted input
                // Create single character undefined token
            else {
                maxRead = 1;
                std::string str = "";
                str += input.at(0);
                if (input.at(0) != ' ') {
                    tokens.push_back(new Token(TokenType::UNDEFINED, str, lineNumber));
                }
            }
            // Update `input` by removing characters read to create Token
            input.erase(0, maxRead);
        }
    }
    tokens.push_back(new Token(TokenType::ENDOFFILE, "", lineNumber));
}
