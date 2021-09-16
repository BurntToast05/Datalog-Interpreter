//
// Created by corbi on 9/15/2021.
//
#include "CommentAutomaton.h"
#include <cctype>

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#' ) {
        index++;
        inputRead++;
        if (input[index] == '|')
        {
            inputRead++;
            index++;
            S3(input);
        }
        else
        {
            inputRead++;
            index++;
            S1(input);
        }
    }
    else {
        Serr();
    }
}
void CommentAutomaton::S1(const std::string& input) {
    if (input[index] != '\n')
    {
        inputRead++;
        index++;
        S1(input);
        return;
    }
}
void CommentAutomaton::S3(const std::string& input) {
    if (input[index] == '|')
    {
        inputRead++;
        index++;
        S5(input);
    }
    else if (input[index] == '\n' && index < static_cast<int>(input.size()))
    {
        inputRead++;
        index++;
        newLines++;
        S3(input);
    }
    else if (input[index] != '|' && index < static_cast<int>(input.size()))
    {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == static_cast<int>(input.size()))
    {
        if (input[index - 1] == '\n')
        {
            newLines++;
        }
        inputRead++;
        S4(input);
    }
}
void CommentAutomaton::S4(const std::string& input) {
    type = TokenType::UNDEFINED;
}
void CommentAutomaton::S5(const std::string& input) {
    if (input[index] == '#')
    {
        inputRead++;
        return;
    }
    else
    {
        inputRead++;
        index++;
        S3(input);
    }
}

