%{
#include "Node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* gMainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

%error-verbose

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN
%token <token> TMAIN TROTATE TFORWARD TATTACK TIF TELSE TIS_HUMAN TIS_PASSABLE TIS_RANDOM TIS_ZOMBIE TRANGED_ATTACK

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate forward attack ranged_attack if
 
/* Expressions */
%type <numeric> numeric
%type <boolean> boolean is_human is_passable is_random is_zombie

%%

main_loop	: TMAIN TLBRACE block TRBRACE
{
    gMainBlock = $3;
    $3->SetMainBlock();
};

block		: statement
{
    $$ = new NBlock();
    $$->AddStatement($1);
};
            | block statement
{
     $$->AddStatement($2);
};
/* TODO: Add support for multiple statements in a block */

statement	: rotate TSEMI | forward TSEMI | if | attack TSEMI | ranged_attack TSEMI
;
boolean     : is_human | is_passable | is_random | is_zombie
;
rotate		: TROTATE TLPAREN numeric TRPAREN
{
    $$ = new NRotate($3);
};
forward     : TFORWARD TLPAREN TRPAREN
{
    $$ = new NForward();
};
attack      : TATTACK TLPAREN TRPAREN
{
    $$ = new NAttack();
};
if          : TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE
{
    $$ = new NIf($3, $6);
};
            | TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE
{
    $$ = new NIf($3, $6, $10);
};
is_human    : TIS_HUMAN TLPAREN numeric TRPAREN
{
    $$ = new NIsHuman($3);
};
is_passable : TIS_PASSABLE TLPAREN TRPAREN
{
    $$ = new NIsPassable();
};
is_random   : TIS_RANDOM TLPAREN TRPAREN
{
    $$ = new NIsRandom();
};
is_zombie   : TIS_ZOMBIE TLPAREN numeric TRPAREN
{
    $$ = new NIsZombie($3);
};
ranged_attack : TRANGED_ATTACK TLPAREN TRPAREN
{
    $$ = new NRangedAttack();
};

numeric		: TINTEGER
{
    $$ = new NNumeric(*($1));
};

%%
