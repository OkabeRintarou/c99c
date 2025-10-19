# C99 Compiler

A simple C99 compiler written in C++20 with clear code structure, including lexical analysis, syntactic analysis, semantic analysis, and code generation backend.

## Features

- Lexical Analysis
- Syntax Analysis
- Semantic Analysis
- Intermediate Representation (IR)
- Code Generation
- C99 Language Support

## Structure

```
src/
  lexer/       - Lexical analyzer
  parser/      - Syntax analyzer
  semantic/    - Semantic analyzer
  ir/          - Intermediate representation
  codegen/     - Code generator
  main.cpp     - Main driver
```

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./c99c input.c -o output
```