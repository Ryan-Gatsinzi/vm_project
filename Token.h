#pragma once

#include <any>
#include <string>
#include "TokenType.h"
class Token{
    private:
        std::string lexeme; // individual token
        TokenType token_type;
        int line_number;
        std::any literal; // might switch to void* for performance later on
        
        std::string stringifyTokenType(TokenType token_type);
    public:
        Token(std::string lexeme, TokenType token_type, int line_number, const std::any& literal);
        
        void setLexeme(std::string lexeme);
        void setTokenType(TokenType token_type);
        void setLineNumber(int line_number);
        void setLiteral(std::any literal);

        std::string getLexeme();
        TokenType getTokenType();
        int getLineNumber();
        std::any getLiteral();

        std::string_view to_string();
};