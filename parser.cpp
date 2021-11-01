//
// Created by corbi on 9/28/2021.
//
#include "Token.h"
#include "parser.h"


DatalogProgram Parser::parse() {
        DatalogProgram datalog;
        index = 0;
        if (parseTokens.at(index).getTokenType() == TokenType::SCHEMES)
        {
            ++index;
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::COLON)
        {
            ++index;
            datalog.addScheme(ParseScheme());
            std::vector<Predicate> schemeList = ParseSchemeList();
            for (size_t i = 0; i < schemeList.size(); ++i)
            {
                datalog.addScheme(schemeList.at(i));
            }
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::FACTS)
        {
            ++index;
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::COLON)
        {
            ++index;
            std::vector<Predicate> factsList = ParseFactsList();
            for (size_t i = 0; i < factsList.size(); ++i)
            {
                datalog.addFacts(factsList.at(i));
            }
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::RULES)
        {
            ++index;
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::COLON)
        {
            ++index;
            std::vector<Rule> rulesToAdd = ParseRuleList();
            for (size_t i = 0; i < rulesToAdd.size(); ++i)
            {
                datalog.addRules(rulesToAdd.at(i));
            }
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::QUERIES)
        {
            ++index;
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::COLON)
        {
            ++index;
            datalog.addQueries(ParseQuery());
            std::vector<Predicate> moreList = ParseQueryList();
            for (size_t i = 0; i < moreList.size(); ++i)
            {
                datalog.addQueries(moreList.at(i));
            }
        }
        else
        {
            throw (index);
            return datalog;
        }
        if (parseTokens.at(index).getTokenType() == TokenType::ENDOFFILE)
        {
            std::cout << "Success!";
            return datalog;
        }
        else
        {
            throw (index);
            return datalog;
        }
    }


//done
Predicate Parser::ParseScheme() {
    Predicate newScheme("");
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        Parameter theID(parseTokens.at(index).getDescription());
        newScheme.setId(theID.toString());
        ++index;
    }
    else
    {
        throw (index);
        return newScheme;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::LEFT_PAREN)
    {
        ++index;
    }
    else
    {
        throw (index);
        return newScheme;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        Parameter theItem(parseTokens.at(index).getDescription());
        newScheme.addParameter(theItem);
        ++index;
        std::vector<Parameter> idList = ParseIDList();
        for (size_t i = 0; i < idList.size(); ++i)
        {
            newScheme.addParameter(idList.at(i));
        }
    }
    else
    {
        throw (index);
        return newScheme;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        ++index;
        return newScheme;
    }
    else
    {
        throw (index);
        return newScheme;
    }
}

//done
std::vector<Parameter> Parser::ParseIDList() {
    std::vector<Parameter> parametersToAdd;
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        return parametersToAdd;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::COMMA)
    {
        ++index;
    }
    else
    {
        throw (index);
        return parametersToAdd;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        Parameter theItem(parseTokens.at(index).getDescription());
        parametersToAdd.push_back(theItem);
        ++index;
        std::vector<Parameter> restOfIds = ParseIDList();
        for (size_t i = 0; i < restOfIds.size(); ++i)
        {
            parametersToAdd.push_back(restOfIds.at(i));
        }
    }
    else
    {
        throw (index);
        return parametersToAdd;
    }
    return parametersToAdd;
}

//done
std::vector<Predicate> Parser::ParseSchemeList() {
    std::vector<Predicate> predicatesToAdd;
    if (parseTokens.at(index).getTokenType() == TokenType::FACTS)
    {
        return predicatesToAdd;
    }
    predicatesToAdd.push_back(ParseScheme());
    std::vector<Predicate> parseSomeMore = ParseSchemeList();
    for (size_t i = 0; i < parseSomeMore.size(); ++i)
    {
        predicatesToAdd.push_back(parseSomeMore.at(i));
    }
    return predicatesToAdd;
}

//done
std::vector<Predicate> Parser::ParseFactsList() {
    std::vector<Predicate> factsList;
    if (parseTokens.at(index).getTokenType() == TokenType::RULES)
    {
        return factsList;
    }
    factsList.push_back(ParseFacts());
    std::vector<Predicate> factsToAdd = ParseFactsList();
    for (size_t i = 0; i < factsToAdd.size(); ++i)
    {
        factsList.push_back(factsToAdd.at(i));
    }
    return factsList;
}

//done
Predicate Parser::ParseFacts() {
    Predicate fact("");
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        fact.setId(parseTokens.at(index).getDescription());
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::LEFT_PAREN)
    {
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::STRING)
    {
        Parameter theItem(parseTokens.at(index).getDescription());
        fact.addParameter(theItem);
        ++index;
        std::vector<Parameter> stringList = ParseStringList();
        for (size_t i = 0; i < stringList.size(); ++i)
        {
            fact.addParameter(stringList.at(i));
        }

    }
    else
    {
        throw (index);
    }

    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::PERIOD)
    {
        ++index;
        return fact;
    }
    else
    {
        throw (index);
    }
}

//done
std::vector<Parameter> Parser::ParseStringList() {
    std::vector<Parameter> parameterToAdd;
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        return parameterToAdd;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::COMMA)
    {
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::STRING)
    {
        parameterToAdd.push_back(parseTokens.at(index).getDescription());
        ++index;
        std::vector<Parameter> stringsToAdd = ParseStringList();
        for(size_t i = 0; i < stringsToAdd.size(); ++i)
        {
            parameterToAdd.push_back(stringsToAdd.at(i));
        }
    }
    else
    {
        throw (index);
    }
    return parameterToAdd;
}

//done
std::vector<Rule> Parser::ParseRuleList() {
    std::vector<Rule> ruleList;
    if (parseTokens.at(index).getTokenType() == TokenType::QUERIES)
    {
        return ruleList;
    }
    ruleList.push_back(ParseRules());
    std::vector<Rule> moreItems = ParseRuleList();
    for (size_t i = 0; i < moreItems.size(); ++i)
    {
        ruleList.push_back(moreItems.at(i));
    }
    return ruleList;
}

//done
Rule Parser::ParseRules() {
    Rule rules(Predicate(""));
    rules.setHeadPredicate(ParseHeadPredicate());
    if (parseTokens.at(index).getTokenType() == TokenType::COLON_DASH)
    {
        ++index;
        rules.addBodyPredicate(ParsePredicate());
        std::vector<Predicate> predicateList = ParsePredicateList();
        for (size_t i = 0; i < predicateList.size(); ++i)
        {
            rules.addBodyPredicate(predicateList.at(i));
        }
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::PERIOD)
    {
        ++index;
        return rules;
    }
    else
    {
        throw (index);
    }
}

//done?
Predicate Parser::ParseHeadPredicate() {
    Predicate headPredicate("");
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        headPredicate.setId(parseTokens.at(index).getDescription());
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::LEFT_PAREN)
    {
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        Parameter parameter(parseTokens.at(index).getDescription());
        headPredicate.addParameter(parameter);
        ++index;
        std::vector<Parameter> idList = ParseIDList();
        for (size_t i = 0; i < idList.size(); ++i)
        {
            headPredicate.addParameter(idList.at(i));
        }
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        ++index;
        return headPredicate;
    }
    else
    {
        throw (index);
    }
}

//done
Predicate Parser::ParsePredicate() {
    Predicate predicateParse("");
    if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        predicateParse.setId(parseTokens.at(index).getDescription());
        ++index;
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::LEFT_PAREN)
    {
        ++index;
        predicateParse.addParameter(ParseParameter());
        std::vector<Parameter> parameters = ParseParameterList();
        for (size_t i = 0; i < parameters.size(); ++i)
        {
            predicateParse.addParameter(parameters.at(i));
        }
    }
    else
    {
        throw (index);
    }
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        ++index;
        return predicateParse;
    }
    else
    {
        throw (index);
    }
}

//done
Parameter Parser::ParseParameter() {
    if (parseTokens.at(index).getTokenType() == TokenType::STRING)
    {
        Parameter theParameters(parseTokens.at(index).getDescription());
        ++index;
        return theParameters;
    }
    else if (parseTokens.at(index).getTokenType() == TokenType::ID)
    {
        Parameter theParameters(parseTokens.at(index).getDescription());
        ++index;
        return theParameters;
    }
    else
    {
        throw (index);
    }
}

//done
std::vector<Parameter> Parser::ParseParameterList() {
    std::vector<Parameter> parameterList;
    if (parseTokens.at(index).getTokenType() == TokenType::RIGHT_PAREN)
    {
        return parameterList;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::COMMA)
    {
        ++index;
        parameterList.push_back(ParseParameter());
        std::vector<Parameter> herestoparse = ParseParameterList();
        for (size_t i = 0; i < herestoparse.size(); ++i)
        {
            parameterList.push_back(herestoparse.at(i));
        }
    }
    else
    {
        throw (index);
    }
    return parameterList;
}

//done
std::vector<Predicate> Parser::ParsePredicateList() {
    std::vector<Predicate> parsePredList;
    if (parseTokens.at(index).getTokenType() == TokenType::PERIOD)
    {
        return parsePredList;
    }
    if (parseTokens.at(index).getTokenType() == TokenType::COMMA)
    {
        ++index;
        parsePredList.push_back(ParsePredicate());
        std::vector<Predicate> moreToParse = ParsePredicateList();
        for (size_t i = 0; i < moreToParse.size(); ++i)
        {
            parsePredList.push_back(moreToParse.at(i));
        }
    }
    else
    {
        throw (index);
    }
    return parsePredList;

}
//done
Predicate Parser::ParseQuery() {
    Predicate queryParse = ParsePredicate();
    if (parseTokens.at(index).getTokenType() == TokenType::Q_MARK)
    {
        ++index;
        return queryParse;
    }
    else
    {
        throw (index);
    }
}

//Done
std::vector<Predicate> Parser::ParseQueryList() {
    std::vector<Predicate> queryList;
    if (parseTokens.at(index).getTokenType() == TokenType::ENDOFFILE)
    {
        return queryList;
    }
    queryList.push_back(ParseQuery());
    std::vector<Predicate> moreParsing = ParseQueryList();
    for (size_t i = 0; i < moreParsing.size(); ++i)
    {
        queryList.push_back(moreParsing.at(i));
    }
    return queryList;
}
