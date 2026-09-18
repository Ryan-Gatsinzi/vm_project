#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <sstream>
#include "Scanner.h"

int main(){
    std::string file_path;
    std::ifstream input_file_stream;

    std::cout << "Enter a file path: ";
    std::getline(std::cin, file_path);
    input_file_stream.open(file_path);
    
    while(!input_file_stream){
        std::cout << std::format("\tFailed to open file \"{}\". Try again: ", file_path);
        std::getline(std::cin, file_path);
    }
    
    
    std::string source_code;
    std::stringstream ss;
    ss << input_file_stream.rdbuf();
    source_code = ss.str();
    
    // lexical  analysis

    Scanner scanner{source_code};
    // std::vector<Token> tokens = scanner.scan();

    for(Token token : scanner.scan())
        std::cout << token.to_string() << std::endl;
   

}