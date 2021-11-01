//
// Created by corbi on 9/22/2021.
//

#ifndef INC_236PROJECT1_PARSER_H
#define INC_236PROJECT1_PARSER_H
#include"Token.h"
#include<vector>
#include "Predicate.h"
#include "DatalogProgram.h"
class Parser {
private:
    std::vector<Token> parseTokens;
    size_t index;

public:
    Parser(std::vector<Token> tokensToParse) {
        parseTokens = tokensToParse;
    };

    ~Parser() = default;

    DatalogProgram parse();
    Predicate ParseScheme();
    std::vector<Predicate> ParseSchemeList();
    std::vector<Parameter> ParseIDList();
    std::vector<Predicate> ParseFactsList();
    Predicate ParseFacts();
    std::vector<Parameter> ParseStringList();
    std::vector<Rule>  ParseRuleList();
    Rule ParseRules();
    Predicate ParseHeadPredicate();
    Predicate ParsePredicate();
    Parameter ParseParameter();
    std::vector<Parameter> ParseParameterList();
    std::vector<Predicate> ParsePredicateList();
    Predicate ParseQuery();
    std::vector<Predicate> ParseQueryList();

    Token getTokenAtIndex(size_t index)
    {
        return parseTokens.at(index);
    }

};
#endif //INC_236PROJECT1_PARSER_H
