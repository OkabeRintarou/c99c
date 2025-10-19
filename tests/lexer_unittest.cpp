#include <gtest/gtest.h>
#include "../src/lexer/lexer.h"

// Test fixture for lexer tests
class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up code here, if needed
    }

    void TearDown() override {
        // Clean up code here, if needed
    }
};

// Test basic tokens
TEST_F(LexerTest, BasicTokens) {
    std::string source = "int main() { return 0; }";
    lexer::Lexer lexer(source);

    // int
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INT);
    EXPECT_EQ(token.value, "int");

    // main
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "main");

    // (
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_LPAREN);
    EXPECT_EQ(token.value, "(");

    // )
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_RPAREN);
    EXPECT_EQ(token.value, ")");

    // {
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_LBRACE);
    EXPECT_EQ(token.value, "{");

    // return
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_RETURN);
    EXPECT_EQ(token.value, "return");

    // 0
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "0");

    // ;
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_SEMICOLON);
    EXPECT_EQ(token.value, ";");

    // }
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_RBRACE);
    EXPECT_EQ(token.value, "}");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
    EXPECT_EQ(token.value, "");
}

// Test integer literals
TEST_F(LexerTest, IntegerLiterals) {
    std::string source = "42 0x1A 077 123";
    lexer::Lexer lexer(source);

    // 42
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "42");

    // 0x1A
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "0x1A");

    // 077
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "077");

    // 123
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "123");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test floating point literals
TEST_F(LexerTest, FloatLiterals) {
    std::string source = "3.14 1.23e-4 5.0 2.5E+3";
    lexer::Lexer lexer(source);

    // 3.14
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_FLOAT);
    EXPECT_EQ(token.value, "3.14");

    // 1.23e-4
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_FLOAT);
    EXPECT_EQ(token.value, "1.23e-4");

    // 5.0
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_FLOAT);
    EXPECT_EQ(token.value, "5.0");

    // 2.5E+3
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_FLOAT);
    EXPECT_EQ(token.value, "2.5E+3");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test string literals
TEST_F(LexerTest, StringLiterals) {
    std::string source = "\"Hello, World!\" \"\" \"\\n\\t\\\"\"";
    lexer::Lexer lexer(source);

    // "Hello, World!"
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_STRING);
    EXPECT_EQ(token.value, "Hello, World!");

    // ""
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_STRING);
    EXPECT_EQ(token.value, "");

    // "\n\t\""
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_STRING);
    EXPECT_EQ(token.value, "\\n\\t\\\"");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test character literals
TEST_F(LexerTest, CharacterLiterals) {
    std::string source = "'a' '\\n' '\\\\' '\\''";
    lexer::Lexer lexer(source);

    // 'a'
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_CHAR);
    EXPECT_EQ(token.value, "a");

    // '\n'
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_CHAR);
    EXPECT_EQ(token.value, "\\n");

    // '\\'
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_CHAR);
    EXPECT_EQ(token.value, "\\\\");

    // '\''
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_CHAR);
    EXPECT_EQ(token.value, "\\'");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test identifiers
TEST_F(LexerTest, Identifiers) {
    std::string source = "variable_name _underscore camelCase _123";
    lexer::Lexer lexer(source);

    // variable_name
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "variable_name");

    // _underscore
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "_underscore");

    // camelCase
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "camelCase");

    // _123
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "_123");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test operators
TEST_F(LexerTest, Operators) {
    std::string source = "+ - * / % = == != < > <= >= && || ! & | ^ ~ << >> += -= *= /= %= &= |= ^= <<= >>=";
    lexer::Lexer lexer(source);

    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_PLUS);
    EXPECT_EQ(token.value, "+");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_MINUS);
    EXPECT_EQ(token.value, "-");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_STAR);
    EXPECT_EQ(token.value, "*");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_SLASH);
    EXPECT_EQ(token.value, "/");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_PERCENT);
    EXPECT_EQ(token.value, "%");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_ASSIGN);
    EXPECT_EQ(token.value, "=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_EQ);
    EXPECT_EQ(token.value, "==");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_NE);
    EXPECT_EQ(token.value, "!=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_LT);
    EXPECT_EQ(token.value, "<");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_GT);
    EXPECT_EQ(token.value, ">");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_LE);
    EXPECT_EQ(token.value, "<=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_GE);
    EXPECT_EQ(token.value, ">=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_AND);
    EXPECT_EQ(token.value, "&&");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_OR);
    EXPECT_EQ(token.value, "||");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_NOT);
    EXPECT_EQ(token.value, "!");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_BITWISE_AND);
    EXPECT_EQ(token.value, "&");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_BITWISE_OR);
    EXPECT_EQ(token.value, "|");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_BITWISE_XOR);
    EXPECT_EQ(token.value, "^");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_BITWISE_NOT);
    EXPECT_EQ(token.value, "~");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_LEFT_SHIFT);
    EXPECT_EQ(token.value, "<<");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_RIGHT_SHIFT);
    EXPECT_EQ(token.value, ">>");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_PLUS_ASSIGN);
    EXPECT_EQ(token.value, "+=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_MINUS_ASSIGN);
    EXPECT_EQ(token.value, "-=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_STAR_ASSIGN);
    EXPECT_EQ(token.value, "*=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_SLASH_ASSIGN);
    EXPECT_EQ(token.value, "/=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_PERCENT_ASSIGN);
    EXPECT_EQ(token.value, "%=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_AND_ASSIGN);
    EXPECT_EQ(token.value, "&=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_OR_ASSIGN);
    EXPECT_EQ(token.value, "|=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_XOR_ASSIGN);
    EXPECT_EQ(token.value, "^=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_LEFT_SHIFT_ASSIGN);
    EXPECT_EQ(token.value, "<<=");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_RIGHT_SHIFT_ASSIGN);
    EXPECT_EQ(token.value, ">>=");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test delimiters
TEST_F(LexerTest, Delimiters) {
    std::string source = "( ) { } [ ] , ; . -> ... :";
    lexer::Lexer lexer(source);

    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_LPAREN);
    EXPECT_EQ(token.value, "(");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_RPAREN);
    EXPECT_EQ(token.value, ")");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_LBRACE);
    EXPECT_EQ(token.value, "{");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_RBRACE);
    EXPECT_EQ(token.value, "}");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_LBRACKET);
    EXPECT_EQ(token.value, "[");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_RBRACKET);
    EXPECT_EQ(token.value, "]");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_COMMA);
    EXPECT_EQ(token.value, ",");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_SEMICOLON);
    EXPECT_EQ(token.value, ";");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_DOT);
    EXPECT_EQ(token.value, ".");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_ARROW);
    EXPECT_EQ(token.value, "->");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_ELLIPSIS);
    EXPECT_EQ(token.value, "...");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_COLON);
    EXPECT_EQ(token.value, ":");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test C99 keywords
TEST_F(LexerTest, C99Keywords) {
    std::string source = "auto break case char const continue default do double else enum extern float for goto if inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while _Bool _Complex _Imaginary";
    lexer::Lexer lexer(source);

    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_AUTO);
    EXPECT_EQ(token.value, "auto");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_BREAK);
    EXPECT_EQ(token.value, "break");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_CASE);
    EXPECT_EQ(token.value, "case");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_CHAR);
    EXPECT_EQ(token.value, "char");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_CONST);
    EXPECT_EQ(token.value, "const");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_CONTINUE);
    EXPECT_EQ(token.value, "continue");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_DEFAULT);
    EXPECT_EQ(token.value, "default");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_DO);
    EXPECT_EQ(token.value, "do");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_DOUBLE);
    EXPECT_EQ(token.value, "double");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_ELSE);
    EXPECT_EQ(token.value, "else");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_ENUM);
    EXPECT_EQ(token.value, "enum");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_EXTERN);
    EXPECT_EQ(token.value, "extern");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_FLOAT);
    EXPECT_EQ(token.value, "float");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_FOR);
    EXPECT_EQ(token.value, "for");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_GOTO);
    EXPECT_EQ(token.value, "goto");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_IF);
    EXPECT_EQ(token.value, "if");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INLINE);
    EXPECT_EQ(token.value, "inline");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INT);
    EXPECT_EQ(token.value, "int");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_LONG);
    EXPECT_EQ(token.value, "long");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_REGISTER);
    EXPECT_EQ(token.value, "register");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_RESTRICT);
    EXPECT_EQ(token.value, "restrict");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_RETURN);
    EXPECT_EQ(token.value, "return");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_SHORT);
    EXPECT_EQ(token.value, "short");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_SIGNED);
    EXPECT_EQ(token.value, "signed");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_SIZEOF);
    EXPECT_EQ(token.value, "sizeof");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_STATIC);
    EXPECT_EQ(token.value, "static");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_STRUCT);
    EXPECT_EQ(token.value, "struct");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_SWITCH);
    EXPECT_EQ(token.value, "switch");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_TYPEDEF);
    EXPECT_EQ(token.value, "typedef");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_UNION);
    EXPECT_EQ(token.value, "union");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_UNSIGNED);
    EXPECT_EQ(token.value, "unsigned");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_VOID);
    EXPECT_EQ(token.value, "void");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_VOLATILE);
    EXPECT_EQ(token.value, "volatile");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_WHILE);
    EXPECT_EQ(token.value, "while");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW__BOOL);
    EXPECT_EQ(token.value, "_Bool");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW__COMPLEX);
    EXPECT_EQ(token.value, "_Complex");

    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW__IMAGINARY);
    EXPECT_EQ(token.value, "_Imaginary");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test comments
TEST_F(LexerTest, Comments) {
    std::string source = "int a; // This is a comment\n/* This is a \n   multi-line comment */ int b;";
    lexer::Lexer lexer(source);

    // int
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INT);
    EXPECT_EQ(token.value, "int");

    // a
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "a");

    // ;
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_SEMICOLON);
    EXPECT_EQ(token.value, ";");

    // int
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INT);
    EXPECT_EQ(token.value, "int");

    // b
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "b");

    // ;
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_SEMICOLON);
    EXPECT_EQ(token.value, ";");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

// Test preprocessor directives
TEST_F(LexerTest, PreprocessorDirectives) {
    std::string source = "#include <stdio.h>\n#define MAX 100";
    lexer::Lexer lexer(source);

    // #
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::PREPROCESSOR_HASH);
    EXPECT_EQ(token.value, "#");

    // include
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "include");

    // <
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_LT);
    EXPECT_EQ(token.value, "<");

    // stdio
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "stdio");

    // .
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::DELIMITER_DOT);
    EXPECT_EQ(token.value, ".");

    // h
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "h");

    // >
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::OP_GT);
    EXPECT_EQ(token.value, ">");

    // #
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::PREPROCESSOR_HASH);
    EXPECT_EQ(token.value, "#");

    // define
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "define");

    // MAX
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::IDENTIFIER);
    EXPECT_EQ(token.value, "MAX");

    // 100
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_INT);
    EXPECT_EQ(token.value, "100");

    // EOF
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::END_OF_FILE);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}