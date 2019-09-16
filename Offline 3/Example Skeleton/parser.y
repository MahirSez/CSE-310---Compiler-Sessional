%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "symbol.h"
#define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;

SymbolTable *table;


void yyerror(char *s)
{
	//write your code
}


%}

%token IF ELSE FOR WHILE

%left 
%right

%nonassoc 


%%

start: INT
	{
		cout<<line_count<<endl;
	}
	;


 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp3= fopen(argv[3],"w");
	fclose(fp3);
	
	fp2= fopen(argv[2],"a");
	fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	fclose(fp2);
	fclose(fp3);
	
	return 0;
}

