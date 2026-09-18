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
        std::vector<Token> scan();
        void scan_tokens();
        void addToken(std::string lexeme, TokenType token_type, const std::any& literal);
        
        std::vector<Token> get_tokens();
        char peekAhead(int pos = 0);
        void handleString();
        void handleNumber();
        void handleIdentifier();
};