#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace lexer {

class Lexer {
public:
    explicit Lexer(const std::string& source);
    
    Token next_token();
    void reset();

private:
    std::string source_;
    size_t position_;
    size_t line_;
    size_t column_;
    std::unordered_map<std::string, TokenType> keywords_;

    char peek(size_t offset = 0) const;
    char advance();
    bool is_eof() const;
    bool is_whitespace(char c) const;
    bool is_digit(char c) const;
    bool is_alpha(char c) const;
    bool is_alphanumeric(char c) const;

    void skip_whitespace();
    void skip_comment();

    Token parse_identifier();
    Token parse_number();
    Token parse_string();
    Token parse_char_literal();
    Token parse_operator();
    
    void init_keywords();
};

} // namespace lexer

#endif // LEXER_H