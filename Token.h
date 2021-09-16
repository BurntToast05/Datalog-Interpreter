#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    ENDOFFILE,
    COMMENT,
    UNDEFINED
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType typeoftoken, std::string descriptiontodo, int linetoinput);

    void toString();

};

#endif // TOKEN_H

