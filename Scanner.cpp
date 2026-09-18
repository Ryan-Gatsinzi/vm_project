#pragma once
#include "Scanner.h"
#include <map>
#include <cctype>
#include <iostream>

Scanner::Scanner(std::string source_code) : source_code(source_code), start(0), current(0), line_number(0) {}

std::vector<Token> Scanner::scan(){
    while(start < source_code.length()){
        if(start == 0 && source_code.size() > 0) line_number++;

        scan_tokens();
        start = current;
    }
    
    
    tokens.push_back(Token("", TokenType::ENDOFFILE, line_number+1, std::any()));
    return tokens;
}

void Scanner::scan_tokens(){
    char current_char = source_code[current++];
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
        if(current_char == '"')
            handleString();
        else if(isdigit(current_char))
            handleNumber();
        else if(isalpha(current_char) || current_char == '_')
            handleIdentifier();
        else
            throw "Invalid charcater: " + current_char;
    }
}

char Scanner::peekAhead(int pos){
    int index = current + pos;
    return (index < source_code.length() ? source_code[index] : source_code[source_code.length() - 1]);
}
void Scanner::addToken(std::string lexeme, TokenType token_type, const std::any& literal){
    tokens.push_back(Token(lexeme, token_type, line_number, literal));
}

void Scanner::handleString(){
    while(peekAhead() != '"') {
        current++;
    }
        
    start++; // jump over the opening "
    std::string str = source_code.substr(start, current-start);
    current++; // jump over the closing " and avoid attempting to read a string again

    addToken(str, TokenType::STRING, str);
        
}

void Scanner::handleNumber(){
    bool decimal_found = false;
    char next_char = peekAhead();

    while(isdigit(next_char) || (next_char == '.' && !decimal_found)){
        if(next_char == '.') 
            decimal_found = true;

        current++;

        if(next_char == '\n') line_number++;

        next_char = peekAhead();
    }
    
    std::string num = source_code.substr(start, current);
    addToken(num, TokenType::NUMBER, std::stoi(num));
}

void Scanner::handleIdentifier(){
    std::map<std::string, TokenType> keywords = {
        {"and", TokenType::AND},
        {"Class", TokenType::CLASS,},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"fun", TokenType::FUN},
        {"for", TokenType::FOR},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE},
        {"eof", TokenType::ENDOFFILE},
    };
    
    char next_char = peekAhead();
    while(isalpha(next_char) || isdigit(next_char) || next_char == '_'){
        current++; //consume character
       
       if(next_char == '\n') line_number++;
        
        next_char = peekAhead();
    }

    std::string identifier = source_code.substr(start, current-start);
    TokenType token_type = (keywords.find(identifier) == keywords.end() ?  TokenType::IDENTIFIER : keywords.at(identifier));

    addToken(identifier, token_type, {});
}

std::vector<Token> Scanner::get_tokens(){ return tokens; }
