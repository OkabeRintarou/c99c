#include "lexer.h"
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace lexer {

Lexer::Lexer(const std::string& source)
    : source_(source), position_(0), line_(1), column_(1) {
    init_keywords();
}

void Lexer::reset() {
    position_ = 0;
    line_ = 1;
    column_ = 1;
}

Token Lexer::next_token() {
    while (!is_eof()) {
        char c = peek();
        
        if (is_whitespace(c)) {
            skip_whitespace();
            continue;
        }
        
        if (c == '/' && peek(1) == '/') {
            skip_comment();
            continue;
        }
        
        if (c == '/' && peek(1) == '*') {
            skip_comment();
            continue;
        }
        
        if (is_alpha(c) || c == '_') {
            return parse_identifier();
        }
        
        if (is_digit(c)) {
            return parse_number();
        }
        
        if (c == '"') {
            return parse_string();
        }
        
        if (c == '\'') {
            return parse_char_literal();
        }
        
        // Handle operators and delimiters
        return parse_operator();
    }
    
    return Token(TokenType::END_OF_FILE, "", line_, column_);
}

char Lexer::peek(size_t offset) const {
    if (position_ + offset >= source_.length()) {
        return '\0';
    }
    return source_[position_ + offset];
}

char Lexer::advance() {
    if (is_eof()) {
        return '\0';
    }

    char c = source_[position_++];

    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }

    return c;
}

bool Lexer::is_eof() const {
    return position_ >= source_.length();
}

bool Lexer::is_whitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::is_digit(char c) const {
    return c >= '0' && c <= '9';
}

bool Lexer::is_alpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::is_alphanumeric(char c) const {
    return is_alpha(c) || is_digit(c);
}

void Lexer::skip_whitespace() {
    while (!is_eof() && is_whitespace(peek())) {
        advance();
    }
}

void Lexer::skip_comment() {
    char c = advance(); // Skip '/'
    c = advance(); // Skip '*' or '/'

    if (c == '/') { // Single line comment
        while (!is_eof() && peek() != '\n') {
            advance();
        }
    } else { // Multi-line comment
        while (!is_eof()) {
            if (peek() == '*' && peek(1) == '/') {
                advance(); // Skip '*'
                advance(); // Skip '/'
                break;
            }
            advance();
        }
    }
}

Token Lexer::parse_identifier() {
    size_t start_pos = position_;
    size_t start_col = column_;
    
    advance(); // Remove unused variable 'c'
    while (!is_eof() && (is_alphanumeric(peek()) || peek() == '_')) {
        advance();
    }
    
    std::string value = source_.substr(start_pos, position_ - start_pos);
    
    auto it = keywords_.find(value);
    if (it != keywords_.end()) {
        return Token(it->second, value, line_, start_col);
    }
    
    return Token(TokenType::IDENTIFIER, value, line_, start_col);
}

Token Lexer::parse_number() {
    size_t start_pos = position_;
    size_t start_col = column_;
    bool is_float = false;

    // Check for hex literals (0x or 0X)
    if (peek() == '0' && !is_eof() && (peek(1) == 'x' || peek(1) == 'X')) {
        advance(); // Skip '0'
        advance(); // Skip 'x' or 'X'

        // Parse hex digits
        while (!is_eof() && (is_digit(peek()) ||
               (tolower(peek()) >= 'a' && tolower(peek()) <= 'f'))) {
            advance();
        }

        std::string value = source_.substr(start_pos, position_ - start_pos);
        return Token(TokenType::CONSTANT_INT, value, line_, start_col);
    }

    // Check for octal literals (starting with 0)
    if (peek() == '0') {
        advance(); // Skip first '0'

        // Parse octal digits
        while (!is_eof() && peek() >= '0' && peek() <= '7') {
            advance();
        }

        // If we encounter an 8 or 9, it's not a valid octal, treat as decimal
        if (!is_eof() && (peek() == '8' || peek() == '9')) {
            // Continue with decimal parsing
            while (!is_eof() && is_digit(peek())) {
                advance();
            }
        }

        std::string value = source_.substr(start_pos, position_ - start_pos);
        return Token(TokenType::CONSTANT_INT, value, line_, start_col);
    }

    // Parse decimal integer part
    while (!is_eof() && is_digit(peek())) {
        advance();
    }

    // Check for decimal point
    if (!is_eof() && peek() == '.') {
        is_float = true;
        advance(); // Skip '.'

        // Parse fractional part
        while (!is_eof() && is_digit(peek())) {
            advance();
        }
    }

    // Check for exponent
    if (!is_eof() && (peek() == 'e' || peek() == 'E')) {
        is_float = true;
        advance(); // Skip 'e' or 'E'

        // Check for sign
        if (!is_eof() && (peek() == '+' || peek() == '-')) {
            advance();
        }

        // Parse exponent digits
        while (!is_eof() && is_digit(peek())) {
            advance();
        }
    }

    std::string value = source_.substr(start_pos, position_ - start_pos);

    if (is_float) {
        return Token(TokenType::CONSTANT_FLOAT, value, line_, start_col);
    } else {
        return Token(TokenType::CONSTANT_INT, value, line_, start_col);
    }
}

Token Lexer::parse_string() {
    size_t start_col = column_;
    advance(); // Skip opening quote

    std::string value;
    std::string raw_value; // For storing the raw representation
    while (!is_eof() && peek() != '"') {
        if (peek() == '\\') {
            raw_value += advance(); // Add backslash to raw value
            char escaped = advance();
            raw_value += escaped; // Add escaped character to raw value

            switch (escaped) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '\\': value += '\\'; break;
                case '"': value += '"'; break;
                default: value += escaped; break;
            }
        } else {
            char c = advance();
            value += c;
            raw_value += c;
        }
    }

    if (is_eof()) {
        return Token(TokenType::ERROR_TOKEN, "Unterminated string literal", line_, start_col);
    }

    advance(); // Skip closing quote
    return Token(TokenType::CONSTANT_STRING, raw_value, line_, start_col);
}

Token Lexer::parse_char_literal() {
    size_t start_col = column_;
    advance(); // Skip opening quote

    std::string value;
    std::string raw_value; // For storing the raw representation
    if (!is_eof() && peek() != '\'') {
        if (peek() == '\\') {
            raw_value += advance(); // Add backslash to raw value
            char escaped = advance();
            raw_value += escaped; // Add escaped character to raw value

            switch (escaped) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '\\': value += '\\'; break;
                case '\'': value += '\''; break;
                default: value += escaped; break;
            }
        } else {
            char c = advance();
            value += c;
            raw_value += c;
        }
    }

    if (is_eof() || peek() != '\'') {
        return Token(TokenType::ERROR_TOKEN, "Unterminated character literal", line_, start_col);
    }

    advance(); // Skip closing quote
    return Token(TokenType::CONSTANT_CHAR, raw_value, line_, start_col);
}

Token Lexer::parse_operator() {
    size_t start_col = column_;
    char c = advance();

    // Single character operators
    switch (c) {
        case '~':
            return Token(TokenType::OP_BITWISE_NOT, "~", line_, start_col);
    }

    // Two-character operators
    switch (c) {
        case '=':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_EQ, "==", line_, start_col);
            }
            return Token(TokenType::OP_ASSIGN, "=", line_, start_col);

        case '!':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_NE, "!=", line_, start_col);
            }
            return Token(TokenType::OP_NOT, "!", line_, start_col);

        case '<':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_LE, "<=", line_, start_col);
            }
            if (!is_eof() && peek() == '<') {
                advance();
                if (!is_eof() && peek() == '=') {
                    advance();
                    return Token(TokenType::OP_LEFT_SHIFT_ASSIGN, "<<=", line_, start_col);
                }
                return Token(TokenType::OP_LEFT_SHIFT, "<<", line_, start_col);
            }
            return Token(TokenType::OP_LT, "<", line_, start_col);

        case '>':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_GE, ">=", line_, start_col);
            }
            if (!is_eof() && peek() == '>') {
                advance();
                if (!is_eof() && peek() == '=') {
                    advance();
                    return Token(TokenType::OP_RIGHT_SHIFT_ASSIGN, ">>=", line_, start_col);
                }
                return Token(TokenType::OP_RIGHT_SHIFT, ">>", line_, start_col);
            }
            return Token(TokenType::OP_GT, ">", line_, start_col);

        case '&':
            if (!is_eof() && peek() == '&') {
                advance();
                return Token(TokenType::OP_AND, "&&", line_, start_col);
            }
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_AND_ASSIGN, "&=", line_, start_col);
            }
            return Token(TokenType::OP_BITWISE_AND, "&", line_, start_col);

        case '|':
            if (!is_eof() && peek() == '|') {
                advance();
                return Token(TokenType::OP_OR, "||", line_, start_col);
            }
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_OR_ASSIGN, "|=", line_, start_col);
            }
            return Token(TokenType::OP_BITWISE_OR, "|", line_, start_col);

        case '^':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_XOR_ASSIGN, "^=", line_, start_col);
            }
            return Token(TokenType::OP_BITWISE_XOR, "^", line_, start_col);

        case '+':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_PLUS_ASSIGN, "+=", line_, start_col);
            }
            if (!is_eof() && peek() == '+') {
                advance();
                return Token(TokenType::OP_PLUS, "++", line_, start_col); // Actually increment operator
            }
            return Token(TokenType::OP_PLUS, "+", line_, start_col);

        case '-':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_MINUS_ASSIGN, "-=", line_, start_col);
            }
            if (!is_eof() && peek() == '-') {
                advance();
                return Token(TokenType::OP_MINUS, "--", line_, start_col); // Actually decrement operator
            }
            if (!is_eof() && peek() == '>') {
                advance();
                return Token(TokenType::DELIMITER_ARROW, "->", line_, start_col);
            }
            return Token(TokenType::OP_MINUS, "-", line_, start_col);

        case '*':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_STAR_ASSIGN, "*=", line_, start_col);
            }
            return Token(TokenType::OP_STAR, "*", line_, start_col);

        case '/':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_SLASH_ASSIGN, "/=", line_, start_col);
            }
            return Token(TokenType::OP_SLASH, "/", line_, start_col);

        case '%':
            if (!is_eof() && peek() == '=') {
                advance();
                return Token(TokenType::OP_PERCENT_ASSIGN, "%=", line_, start_col);
            }
            return Token(TokenType::OP_PERCENT, "%", line_, start_col);

        case '(':
            return Token(TokenType::DELIMITER_LPAREN, "(", line_, start_col);

        case ')':
            return Token(TokenType::DELIMITER_RPAREN, ")", line_, start_col);

        case '{':
            return Token(TokenType::DELIMITER_LBRACE, "{", line_, start_col);

        case '}':
            return Token(TokenType::DELIMITER_RBRACE, "}", line_, start_col);

        case '[':
            return Token(TokenType::DELIMITER_LBRACKET, "[", line_, start_col);

        case ']':
            return Token(TokenType::DELIMITER_RBRACKET, "]", line_, start_col);

        case ',':
            return Token(TokenType::DELIMITER_COMMA, ",", line_, start_col);

        case ';':
            return Token(TokenType::DELIMITER_SEMICOLON, ";", line_, start_col);

        case '.':
            if (!is_eof() && peek() == '.' && peek(1) == '.') {
                advance();
                advance();
                return Token(TokenType::DELIMITER_ELLIPSIS, "...", line_, start_col);
            }
            return Token(TokenType::DELIMITER_DOT, ".", line_, start_col);

        case '#':
            return Token(TokenType::PREPROCESSOR_HASH, "#", line_, start_col);

        case ':':
            return Token(TokenType::DELIMITER_COLON, ":", line_, start_col);

        default:
            std::string value(1, c);
            return Token(TokenType::ERROR_TOKEN, "Unknown character: " + value, line_, start_col);
    }
}

void Lexer::init_keywords() {
    keywords_ = {
        {"auto", TokenType::KW_AUTO},
        {"break", TokenType::KW_BREAK},
        {"case", TokenType::KW_CASE},
        {"char", TokenType::KW_CHAR},
        {"const", TokenType::KW_CONST},
        {"continue", TokenType::KW_CONTINUE},
        {"default", TokenType::KW_DEFAULT},
        {"do", TokenType::KW_DO},
        {"double", TokenType::KW_DOUBLE},
        {"else", TokenType::KW_ELSE},
        {"enum", TokenType::KW_ENUM},
        {"extern", TokenType::KW_EXTERN},
        {"float", TokenType::KW_FLOAT},
        {"for", TokenType::KW_FOR},
        {"goto", TokenType::KW_GOTO},
        {"if", TokenType::KW_IF},
        {"inline", TokenType::KW_INLINE},
        {"int", TokenType::KW_INT},
        {"long", TokenType::KW_LONG},
        {"register", TokenType::KW_REGISTER},
        {"restrict", TokenType::KW_RESTRICT},
        {"return", TokenType::KW_RETURN},
        {"short", TokenType::KW_SHORT},
        {"signed", TokenType::KW_SIGNED},
        {"sizeof", TokenType::KW_SIZEOF},
        {"static", TokenType::KW_STATIC},
        {"struct", TokenType::KW_STRUCT},
        {"switch", TokenType::KW_SWITCH},
        {"typedef", TokenType::KW_TYPEDEF},
        {"union", TokenType::KW_UNION},
        {"unsigned", TokenType::KW_UNSIGNED},
        {"void", TokenType::KW_VOID},
        {"volatile", TokenType::KW_VOLATILE},
        {"while", TokenType::KW_WHILE},
        {"_Bool", TokenType::KW__BOOL},
        {"_Complex", TokenType::KW__COMPLEX},
        {"_Imaginary", TokenType::KW__IMAGINARY}
    };
}

} // namespace lexer