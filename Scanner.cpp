#pragma once

#include "Scanner.h";
#include <cctype>;

Scanner::Scanner(std::string source_code) : source_code(source_code), start(0), current(0), line_number(0) {}

const std::vector<Token>& Scanner::scan(){
    while(start < source_code.length()){
        scan_tokens();
        start = current;
    }
    tokens.push_back(Token("", TokenType::ENDOFFILE, line_number+1, std::any()));
    return tokens;
}

void Scanner::scan_tokens(){
    char current_char = source_code[current];
    switch(current_char){
        //single char tokens
        case '+': addToken(std::string(1, current_char), TokenType::PLUS, std::any()); break;
        case '-': addToken(std::string(1, current_char), TokenType::MINUS, std::any()); break;
        case '*': addToken(std::string(1, current_char), TokenType::STAR, std::any()); break;
        case '(': addToken(std::string(1, current_char), TokenType::LEFT_PAREN, std::any()); break;
        case ')': addToken(std::string(1, current_char), TokenType::RIGHT_PAREN, std::any()); break;
        case '{': addToken(std::string(1, current_char), TokenType::LEFT_BRACE, std::any()); break;
        case '}': addToken(std::string(1, current_char), TokenType::RIGHT_BRACE, std::any()); break;
        case ',': addToken(std::string(1, current_char), TokenType::COMMA, std::any()); break;
        case ';': addToken(std::string(1, current_char), TokenType::SEMICOLON, std::any()); break;
        case '/': addToken(std::string(1, current_char), TokenType::SLASH, std::any()); break;
        //single or multi char tokens
        case '=': addToken(std::string(1, current_char), (peekAhead() == '=' ? TokenType::EQUAL_EQUAL : TokenType::EQUAL), std::any()); break;
        case '!': addToken(std::string(1, current_char), (peekAhead() == '=' ? TokenType::BANG_EQUAL : TokenType::BANG), std::any()); break;
        case '>': addToken(std::string(1, current_char), (peekAhead() == '=' ? TokenType::GREATER_EQUAL : TokenType::GREATER), std::any()); break;
        case '<': addToken(std::string(1, current_char), (peekAhead() == '=' ? TokenType::LESS_EQUAL : TokenType::LESS), std::any()); break;
        //literals

        default: 
        if(isalpha(current_char))
            hanldeString();
        else if(isdigit(current_char))
            handleNumbers();
        else
            // throw error
    }
}

char Scanner::peekAhead(int pos = 0){
    int index = current + pos;
    return (index < source_code.length() ? source_code[index] : source_code[source_code.length() - 1]);
}
void Scanner::addToken(std::string lexeme, TokenType token_type, const std::any& literal){
    tokens.push_back(Token(lexeme, token_type, line_number, literal));
}