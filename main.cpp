#include "Lexer.h"
#include "parser.h"
#include "DatalogProgram.h"
#include <fstream>
using namespace std;// std::filebuf, std::ifstream

int main(int argc, char * argv[]) {

    // check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }
    std::string outputstring;
    std::string buffer;

    while (std::getline(input, buffer)) {
        outputstring += (buffer + '\n');
    }

    Lexer* lexer = new Lexer();

    lexer->Run(outputstring);
    //lexer->toString();
    //lexer->totalTokens();
    vector<Token> tokensToParse = lexer->getTokens();

    for (size_t i = 0; i < tokensToParse.size(); ++i) {
        if (tokensToParse.at(i).getTokenType() == TokenType::COMMENT) {
            tokensToParse.erase(tokensToParse.begin() + i);
            i = i-1;
        }
    }
    Parser parser(tokensToParse);
    try {
        DatalogProgram datalogProgram = parser.parse();
        std::cout << std::endl;
        datalogProgram.toString();
        datalogProgram.printDomains();
    }
    catch (size_t& itemtocatch) {
        std::cout << "Failure!" << std::endl << "  ";
        parser.getTokenAtIndex(itemtocatch).toString();
    }

    delete lexer;

    return 0;
}