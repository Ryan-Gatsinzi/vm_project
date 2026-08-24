#pragma once
#include "Token.h"

Token::Token(std::string lexeme, TokenType token_type, int line_number, const std::any& literal) : lexeme(lexeme), token_type(token_type), line_number(line_number), literal(literal){}

std::string Token::stringifyTokenType(TokenType token_type){
    switch(token_type){
            // Single-character tokens
        case TokenType::LEFT_PAREN:    return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:   return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:    return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:   return "RIGHT_BRACE";
        case TokenType::COMMA:         return "COMMA";
        case TokenType::DOT:           return "DOT";
        case TokenType::MINUS:         return "MINUS";
        case TokenType::PLUS:          return "PLUS";
        case TokenType::SEMICOLON:     return "SEMICOLON";
        case TokenType::SLASH:         return "SLASH";
        case TokenType::STAR:          return "STAR";

        // One or two character tokens
        case TokenType::BANG:          return "BANG";
        case TokenType::BANG_EQUAL:    return "BANG_EQUAL";
        case TokenType::EQUAL:         return "EQUAL";
        case TokenType::EQUAL_EQUAL:   return "EQUAL_EQUAL";
        case TokenType::GREATER:       return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS:          return "LESS";
        case TokenType::LESS_EQUAL:    return "LESS_EQUAL";

        // Literals
        case TokenType::IDENTIFIER:    return "IDENTIFIER";
        case TokenType::STRING:        return "STRING";
        case TokenType::NUMBER:        return "NUMBER";

        // Keywords
        case TokenType::AND:           return "AND";
        case TokenType::CLASS:         return "CLASS";
        case TokenType::ELSE:          return "ELSE";
        case TokenType::FALSE:         return "FALSE";
        case TokenType::FUN:           return "FUN";
        case TokenType::FOR:           return "FOR";
        case TokenType::IF:            return "IF";
        case TokenType::NIL:           return "NIL";
        case TokenType::OR:            return "OR";
        case TokenType::PRINT:         return "PRINT";
        case TokenType::RETURN:        return "RETURN";
        case TokenType::SUPER:         return "SUPER";
        case TokenType::THIS:          return "THIS";
        case TokenType::TRUE:          return "TRUE";
        case TokenType::VAR:           return "VAR";
        case TokenType::WHILE:         return "WHILE";
        case TokenType::ENDOFFILE:     return "ENDOFFILE";
        
        default:                       return "UNKNOWN_TOKEN_TYPE";
    }         
}

void Token::setLexeme(std::string lexeme){ this->lexeme = lexeme;}

void Token::setTokenType(TokenType token_type){ this->token_type = token_type;}

void Token::setLineNumber(int line_number){ this->line_number = line_number;}

void Token::setLiteral(std::any literal){ this->literal = literal;}

std::string Token::getLexeme(){ return lexeme; }

TokenType Token::getTokenType(){return token_type;}

int Token::getLineNumber() { return line_number; }

std::any Token::getLiteral(){ return literal;}

std::string_view Token::to_string(){
    return "Lexeme: " + lexeme + "; Line number: " + std::to_string(line_number) + "; token type: " + stringifyTokenType(token_type) + "\n";
}