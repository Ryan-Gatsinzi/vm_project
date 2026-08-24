#pragma once
#include "Token.h"
#include <vector>

class Scanner{
    private:
    std::vector<Token> tokens;
    std::string source_code;
    int start, current, line_number;
    std::any literal;

    public:
    Scanner(std::string source_code);
    const std::vector<Token>& scan();
    void Scanner::scan_tokens();
    void Scanner::addToken(std::string lexeme, TokenType token_type, const std::any& literal);
    char Scanner::peekAhead(int pos = 0);
};