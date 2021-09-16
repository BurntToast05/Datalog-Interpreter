#include "Token.h"

Token::Token(TokenType typeoftoken, std::string descriptiontodo, int linetoinput) {
    type = typeoftoken;
    description = descriptiontodo;
    line = linetoinput;
}
std::string EnumToString(TokenType token)
{
    switch (token) {
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::ENDOFFILE:
            return "EOF";
        case TokenType::STRING:
            return "STRING";
        case TokenType::ID:
            return "ID";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::RULES:
            return "RULES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::ADD:
            return "ADD";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::COLON:
            return "COLON";
    }
    return "Not an enum";
}
void Token::toString() {
    std::cout << "(" << EnumToString(type) << "," << "\"" << description << "\"," << line << ")" << std::endl;
}
