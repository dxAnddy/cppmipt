%option c++
%option noyywrap
%option nodefault

%{
#include "grammar.tab.hh"
#include <iostream>

int error_count = 0;
%}

WS          [ \t\n\v]+
DIGIT       [0-9]
DIGIT1      [1-9]
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*

%%

{WS}                {  }

"+"                 { return yy::parser::token_type::PLUS; }
"-"                 { return yy::parser::token_type::MINUS; }
"*"                 { return yy::parser::token_type::MUL; }
"/"                 { return yy::parser::token_type::DIV; }
"="                 { return yy::parser::token_type::ASSIGN; }
"=="                { return yy::parser::token_type::EQUAL; }
"!="                { return yy::parser::token_type::NEQUAL; }
"<"                 { return yy::parser::token_type::LESS; }
"<="                { return yy::parser::token_type::LEQ; }
">"                 { return yy::parser::token_type::GREATER; }
">="                { return yy::parser::token_type::GEQ; }
"("                 { return yy::parser::token_type::LPAREN; }
")"                 { return yy::parser::token_type::RPAREN; }
"{"                 { return yy::parser::token_type::LBRACE; }
"}"                 { return yy::parser::token_type::RBRACE; }
";"                 { return yy::parser::token_type::SCOLON; }
"?"                 { return yy::parser::token_type::QUESTION; }

"while"             { return yy::parser::token_type::WHILE; }
"if"                { return yy::parser::token_type::IF; }
"else"              { return yy::parser::token_type::ELSE; }
"print"             { return yy::parser::token_type::PRINT; }

0{DIGIT}+           { 
                        std::cerr << "Error: leading zero in number '" << yytext << "'" << std::endl;
                        error_count++; 
                        return 0;
                    }

0|{DIGIT1}{DIGIT}*  { 
                        return yy::parser::token_type::NUMBER; 
                    }

{IDENTIFIER}        { 
                        return yy::parser::token_type::IDENTIFIER; 
                    }

.                   { 
                        std::cerr << "Error: unknown character '" << yytext[0] << "'" << std::endl;
                        error_count++;
                        return 0; 
                    }

%%