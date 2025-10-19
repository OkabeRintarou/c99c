#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

namespace lexer {

enum class TokenType {
    // Keywords
    KW_AUTO,
    KW_BREAK,
    KW_CASE,
    KW_CHAR,
    KW_CONST,
    KW_CONTINUE,
    KW_DEFAULT,
    KW_DO,
    KW_DOUBLE,
    KW_ELSE,
    KW_ENUM,
    KW_EXTERN,
    KW_FLOAT,
    KW_FOR,
    KW_GOTO,
    KW_IF,
    KW_INLINE,
    KW_INT,
    KW_LONG,
    KW_REGISTER,
    KW_RESTRICT,
    KW_RETURN,
    KW_SHORT,
    KW_SIGNED,
    KW_SIZEOF,
    KW_STATIC,
    KW_STRUCT,
    KW_SWITCH,
    KW_TYPEDEF,
    KW_UNION,
    KW_UNSIGNED,
    KW_VOID,
    KW_VOLATILE,
    KW_WHILE,
    KW__BOOL,
    KW__COMPLEX,
    KW__IMAGINARY,

    // Identifiers
    IDENTIFIER,

    // Constants
    CONSTANT_INT,
    CONSTANT_FLOAT,
    CONSTANT_CHAR,
    CONSTANT_STRING,

    // Operators
    OP_PLUS,           // +
    OP_MINUS,          // -
    OP_STAR,           // *
    OP_SLASH,          // /
    OP_PERCENT,        // %
    OP_ASSIGN,         // =
    OP_EQ,             // ==
    OP_NE,             // !=
    OP_LT,             // <
    OP_GT,             // >
    OP_LE,             // <=
    OP_GE,             // >=
    OP_AND,            // &&
    OP_OR,             // ||
    OP_NOT,            // !
    OP_BITWISE_AND,    // &
    OP_BITWISE_OR,     // |
    OP_BITWISE_XOR,    // ^
    OP_BITWISE_NOT,    // ~
    OP_LEFT_SHIFT,     // <<
    OP_RIGHT_SHIFT,    // >>
    OP_PLUS_ASSIGN,    // +=
    OP_MINUS_ASSIGN,   // -=
    OP_STAR_ASSIGN,    // *=
    OP_SLASH_ASSIGN,   // /=
    OP_PERCENT_ASSIGN, // %=
    OP_AND_ASSIGN,     // &=
    OP_OR_ASSIGN,      // |=
    OP_XOR_ASSIGN,     // ^=
    OP_LEFT_SHIFT_ASSIGN,  // <<=
    OP_RIGHT_SHIFT_ASSIGN, // >>=

    // Delimiters
    DELIMITER_LPAREN,    // (
    DELIMITER_RPAREN,    // )
    DELIMITER_LBRACE,    // {
    DELIMITER_RBRACE,    // }
    DELIMITER_LBRACKET,  // [
    DELIMITER_RBRACKET,  // ]
    DELIMITER_COMMA,     // ,
    DELIMITER_SEMICOLON, // ;
    DELIMITER_DOT,       // .
    DELIMITER_ARROW,     // ->
    DELIMITER_ELLIPSIS,  // ...
    DELIMITER_COLON,     // :

    // Preprocessor
    PREPROCESSOR_HASH,   // #

    // End of file
    END_OF_FILE,

    // Error token
    ERROR_TOKEN
};

struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;

    Token(TokenType t, const std::string& v, size_t l, size_t c)
        : type(t), value(v), line(l), column(c) {}
};

} // namespace lexer

#endif // TOKEN_H