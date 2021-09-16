#include "Lexer.h"
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
    lexer->toString();
    lexer->totalTokens();
    delete lexer;

    return 0;
}