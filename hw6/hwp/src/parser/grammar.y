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

%nterm <Node*> expr 
%nterm <Node*> statement 
%nterm <Node*> assignment 
%nterm <Node*> print

%right '='
%left  EQUAL NEQUAL
%left  '<' '>' LEQ GEQ 
%left  '+' '-'
%left '+' '-'
%left '*' '/'
%precedence UMINUS

%start program

%%

program : statement
        | program statement

statement : assignment
          | PRINT SCOLON
          
assignment : IDENTIFIER ASSIGN expr SCOLON

expr : NUMBER
     | IDENTIFIER
     | expr PLUS expr
     | expr MINUS expr
     | expr MUL expr
     | expr DIV expr
     | MINUS expr %prec UMINUS
%%

void yy::parser::error(const std::string& msg) {
    driver->error(msg);
}
