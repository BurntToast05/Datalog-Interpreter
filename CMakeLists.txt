cmake_minimum_required(VERSION 3.16.3)
project(236project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(236project1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        CommaAutomaton.h
        CommaAutomaton.cpp
        PeriodAutomaton.h
        PeriodAutomaton.cpp Q-MarkAutomaton.cpp Q-MarkAutomaton.h LeftPatrenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.h AddAutomaton.cpp SchemesAutomaton.h SchemesAutomaton.cpp FactsAutomaton.h FactsAutomaton.cpp RulesAutomaton.h RulesAutomaton.cpp QueriesAutomaton.h QueriesAutomaton.cpp IdAutomaton.h IdAutomaton.cpp CommentAutomaton.h CommentAutomaton.cpp StringAutomaton.h StringAutomaton.cpp parser.h parser.cpp DatalogProgram.h DatalogProgram.cpp Rule.h Rule.cpp Predicate.h Predicate.cpp Parameter.h Parameter.cpp Tuple.h Header.h Header.cpp Tuple.cpp Relation.h Relation.cpp Database.h Database.cpp Interpreter.cpp Interpreter.h graph.cpp graph.h)
