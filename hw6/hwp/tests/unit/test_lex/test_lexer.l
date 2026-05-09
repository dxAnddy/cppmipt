%option c++
%option noyywrap
%option nodefault

%{
#include <iostream>
#include <iomanip>
#include <string>

//flex -o test.cpp test_lexer.l
//g++ test.cpp -o test
//./test < ../../code_ex/fibs_p/fibs.pcl

int error_count = 0;
const int COL_WIDTH = 20;

void print_token(const std::string& type, const char* lexeme, bool is_error = false) {
    std::ostream& out = is_error ? std::cerr : std::cout;
    out << std::left << std::setw(COL_WIDTH) << type 
        << " | Lexeme: [" << lexeme << "]" << std::endl;
}
%}

WS          [ \t\n\v]+
DIGIT       [0-9]
DIGIT1      [1-9]
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*

%%

{WS}                { }

"+"                 { print_token("TOKEN: PLUS", yytext); }
"-"                 { print_token("TOKEN: MINUS", yytext); }
"*"                 { print_token("TOKEN: MUL", yytext); }
"/"                 { print_token("TOKEN: DIV", yytext); }
"="                 { print_token("TOKEN: ASSIGN", yytext); }
"=="                { print_token("TOKEN: EQUAL", yytext); }
"!="                { print_token("TOKEN: NEQUAL", yytext); }
"<"                 { print_token("TOKEN: LESS", yytext); }
"<="                { print_token("TOKEN: LEQ", yytext); }
">"                 { print_token("TOKEN: GREATER", yytext); }
">="                { print_token("TOKEN: GEQ", yytext); }
"("                 { print_token("TOKEN: LPAREN", yytext); }
")"                 { print_token("TOKEN: RPAREN", yytext); }
"{"                 { print_token("TOKEN: LBRACE", yytext); }
"}"                 { print_token("TOKEN: RBRACE", yytext); }
";"                 { print_token("TOKEN: SCOLON", yytext); }
"?"                 { print_token("TOKEN: QUESTION", yytext); }

"while"             { print_token("KEYWORD: WHILE", yytext); }
"if"                { print_token("KEYWORD: IF", yytext); }
"else"              { print_token("KEYWORD: ELSE", yytext); }
"print"             { print_token("KEYWORD: PRINT", yytext); }

0{DIGIT}+           { print_token("ERROR: LEAD ZERO", yytext, true); error_count++; }
0|{DIGIT1}{DIGIT}* { print_token("NUMBER:", yytext); }

{IDENTIFIER}        { print_token("IDENTIFIER:", yytext); }

.                   { print_token("ERROR: UNKNOWN", yytext, true); error_count++; }

%%

int main() {
    yyFlexLexer lexer(&std::cin);
    while (lexer.yylex() != 0);
    std::cerr << "\nTotal errors: " << error_count << std::endl;
    return (error_count == 0) ? 0 : 1;
}