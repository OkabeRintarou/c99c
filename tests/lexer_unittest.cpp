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
    
    // Skip the rest for this example
    while (token.type != lexer::TokenType::END_OF_FILE) {
        token = lexer.next_token();
    }
}

// Test floating point literals
TEST_F(LexerTest, FloatLiterals) {
    std::string source = "3.14 1.23e-4 5.0";
    lexer::Lexer lexer(source);
    
    // 3.14
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_FLOAT);
    EXPECT_EQ(token.value, "3.14");
    
    // Skip the rest for this example
    while (token.type != lexer::TokenType::END_OF_FILE) {
        token = lexer.next_token();
    }
}

// Test string literals
TEST_F(LexerTest, StringLiterals) {
    std::string source = "\"Hello, World!\"";
    lexer::Lexer lexer(source);
    
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_STRING);
    EXPECT_EQ(token.value, "Hello, World!");
}

// Test character literals
TEST_F(LexerTest, CharacterLiterals) {
    std::string source = "'a' '\\n' '\\\\'";
    lexer::Lexer lexer(source);
    
    // 'a'
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::CONSTANT_CHAR);
    EXPECT_EQ(token.value, "a");
    
    // Skip the rest for this example
    while (token.type != lexer::TokenType::END_OF_FILE) {
        token = lexer.next_token();
    }
}

// Test identifiers
TEST_F(LexerTest, Identifiers) {
    std::string source = "variable_name _underscore camelCase";
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
    
    // Skip the rest for this example
    while (token.type != lexer::TokenType::END_OF_FILE) {
        token = lexer.next_token();
    }
}

// Test keywords
TEST_F(LexerTest, Keywords) {
    std::string source = "int char if else while for return";
    lexer::Lexer lexer(source);
    
    // int
    lexer::Token token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_INT);
    EXPECT_EQ(token.value, "int");
    
    // char
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_CHAR);
    EXPECT_EQ(token.value, "char");
    
    // if
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_IF);
    EXPECT_EQ(token.value, "if");
    
    // else
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_ELSE);
    EXPECT_EQ(token.value, "else");
    
    // while
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_WHILE);
    EXPECT_EQ(token.value, "while");
    
    // for
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_FOR);
    EXPECT_EQ(token.value, "for");
    
    // return
    token = lexer.next_token();
    EXPECT_EQ(token.type, lexer::TokenType::KW_RETURN);
    EXPECT_EQ(token.value, "return");
    
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}