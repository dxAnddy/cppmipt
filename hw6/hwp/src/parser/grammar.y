%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{

namespace yy { class Driver; }
}

%code
{
#include "driver.hpp"

}

%token <int>         NUMBER
%token <std::string> IDENTIFIER

%token
    PLUS    "+"
    MINUS   "-"
    MUL     "*"
    DIV     "/"
    ASSIGN  "="
    EQUAL   "=="
    NEQUAL  "!="
    LESS    "<"
    LEQ     "<="
    GREATER ">"
    GEQ     ">="
    LPAREN  "("
    RPAREN  ")"
    LBRACE  "{"
    RBRACE  "}"
    SCOLON  ";"
    QUESTION "?"
    WHILE   "while"
    IF      "if"
    ELSE    "else"
    PRINT   "print"
;

%right '='
%left  EQUAL NEQUAL
%left  '<' '>' LEQ GEQ 
%left  '+' '-'
%left '+' '-'
%left '*' '/'

%start program

%%

program 



%%

void yy::parser::error(const std::string& msg) {
    driver->error(msg);
}
