cmake_minimum_required(VERSION 3.27)
project(compiler_design)

set(CMAKE_CXX_STANDARD 14)

add_executable(compiler_design
        FirstandFollow.cpp
        KeywordScanner.cpp
        "Lexical Analyser.cpp"
        LL1parser.cpp
        myshell.c
        OperatorPrecedenceParser.cpp
        RecursiveDescentParser.cpp
        test.c
        test.cpp
        test2.cpp
        test3.cpp
        Test4.cpp
        Test5.cpp
)
