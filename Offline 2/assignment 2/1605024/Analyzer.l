%option noyywrap

%x COMMENT

%{
#include "SymbolTable.h"


int line_count = 1 , error_count = 0;

string type ="" , comment  = "";

int comment_init;

symbolTable table(7);

void InsertInSymbolTable() {
	bool ok = table.Insert(yytext , type);

	if(ok) {
		table.printCurrent();
	}
	else {
		table.Lookup(yytext);
		fprintf(logFile, "\tLexeme %s Found in ScopeTable# %d at position %d, %d\n\n" , yytext , scopeTableID , roID , colID);
	}
}

%}

%%




"if"		{
				type = "IF";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				
			}

"else"		{
				type = "ELSE";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"for"		{
				type = "FOR";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"while"		{
				type = "WHILE";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"do"		{
				type = "DO";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"break"		{
				type = "BREAK";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"int"		{
				type = "INT";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"char"		{
				type = "CHAR";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"float"		{
				type = "FLOAT";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"double"	{
				type = "DOUBLE";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"void"		{
				type = "VOID";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}			

"return"	{
				type = "RETURN";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"switch"	{
				type = "SWITCH";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}

"case"		{
				type = "CASE";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}	

"default"	{
				type = "DEFAULT";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}					

"continue"	{
				type = "CONTINUE";
				fprintf(tokenFile, "<%s> " ,type.c_str() );
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
			}


[0-9]+		{
				type = "CONST_INT";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}


[0-9]+(\.[0-9]*)?([eE][+-]?[0-9]+)?	|
\.[0-9]+([eE][+-]?[0-9]+)?			{

				type = "CONST_FLOAT";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}


"'\\"[ntafrbv0\\"\""]"'"	{

				type = "CONST_CHAR";
				string str = "";

				if( yytext[2] =='n') str = '\n';
				else if( yytext[2] =='t') str = '\t';
				else if( yytext[2] =='a') str = '\a';
				else if( yytext[2] =='f') str = '\f';
				else if( yytext[2] =='r') str = '\r';
				else if( yytext[2] =='b') str = '\b';
				else if( yytext[2] =='v') str = '\v';
				else if( yytext[2] =='0') str = '\0';
				else if( yytext[2] =='\\') str = '\\';
				else str = '\"';

				fprintf(tokenFile, "<%s, %s> " ,type.c_str() , str.c_str());
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext);
				InsertInSymbolTable();
			}

"'\\"."'"	{
				fprintf(logFile, "Error at line %d: Multi character constant error %s\n\n", line_count ,yytext);
				error_count++;
			}


"'\\"[ntafrbv0\\"\""] 	|
"'"\\"'"				{

				fprintf(logFile, "Error at line %d: Unterminated character %s\n\n", line_count ,yytext);
				error_count++;
			}


"'"."'"		{
				type = "CONST_CHAR";
				string str = "";
				str += yytext[1];

				fprintf(tokenFile, "<%s, %s> " ,type.c_str() , str.c_str());
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext);
				InsertInSymbolTable();
			}

"'"[^"'"\n]+"'"		{
				fprintf(logFile, "Error at line %d: Multi character constant error %s\n\n", line_count ,yytext);
				error_count++;
			}

"''"		{
				fprintf(logFile, "Error at line %d: Empty character constant error %s\n\n", line_count ,yytext);
				error_count++;	
			}


"'".?		{

				fprintf(logFile, "Error at line %d: Unterminated character %s\n\n", line_count ,yytext);
				error_count++;
			}


"+" 		|
"-" 		{
				type = "ADDOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"*" 		|
"/" 		|
"%"			{
				type = "MULOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"++" 		|
"--"		{
				type = "INCOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}


"<" 		|
"<=" 		|
">" 		|
">=" 		|
"==" 		|
"!=" 		{
				type = "RELOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"="			{
				type = "ASSIGNOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"&&" 		|
"||"		{
				type = "LOGICOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"&" 		|
"|" 		|
"^" 		|
"<<" 		|
">>" 		{
				type = "BITOP";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"!"			{
				type = "NOT";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}


"("			{
				type = "LPAREN";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

")"			{
				type = "RPAREN";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"{"			{
				type = "LCURL";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"}"			{
				type = "RCURL";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"["			{
				type = "LTHIRD";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

"]"			{
				type = "RTHIRD";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

","			{
				type = "COMMA";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

";"			{
				type = "SEMICOLON";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();
			}

[_a-zA-Z][_a-z0-9A-Z]*	{

				type = "ID";
				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,yytext);
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext );
				InsertInSymbolTable();

			}

 "\""([^"\""\n]*\\\n)*[^"\""\n]*"\""		{

				type = "STRING";
				string str = "";
				int newLineCnt = 0;

				int n = strlen(yytext);


				for(int i =0 ; i < n ; i++ ) {
					if( i +2 < n && yytext[i]=='\\' && yytext[i+1] == '\r' &&yytext[i+2] == '\n') {
						i+=2;
						newLineCnt++;
						continue;
					}
					if( i +1 < n && yytext[i]=='\\' && yytext[i+1] == '\n') {
						i+=1;
						newLineCnt++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'n') {
						str += '\n';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 't') {
						str += '\t';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'a') {
						str += '\a';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'f') {
						str += '\f';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'r') {
						str += '\r';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'b') {
						str += '\b';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == 'v') {
						str += '\v';
						i++;
						continue;
					}
					if( i + 1 < n && yytext[i]=='\\' && yytext[i+1] == '0') {
						str += '\0';
						i++;
						continue;
					}
					str += yytext[i];
				}
				

				fprintf(tokenFile, "<%s, %s> " ,type.c_str() ,str.c_str());
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext);
				line_count += newLineCnt;
			}

"\""([^"\""\n]*\\\n)*[^"\""\n]*		{

				fprintf(logFile, "Error at line %d: Unterminated string %s\n\n", line_count ,yytext);
				error_count++;
				int n = strlen(yytext);
				for(int i =0 ; i < n; i++ ) {
					if(yytext[i] == '\n') line_count++;
				}
			}			


"//"(.*|\\\n|\\\r\n)*.*	{

				type = "COMMENT";
				int n = strlen(yytext);
				
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",line_count ,type.c_str() , yytext);
				for(int i =0 ; i < n; i++ ) {
					if(yytext[i] == '\n') line_count++;
				}
				
			}



"/*"		{
				BEGIN COMMENT;
				comment = yytext;
				comment_init = line_count;
				
			}

<COMMENT>"*/"	{
				
				type = "COMMENT";
				comment += yytext;
				
				fprintf(logFile, "Line No. %d: Token <%s> Lexeme %s found\n\n",comment_init ,type.c_str() , comment.c_str());
				BEGIN INITIAL;
			}

<COMMENT>.	{
				comment += yytext;
			}

<COMMENT>\n 	{

				comment += yytext;
				line_count++;
			}


<COMMENT><<EOF>>	{

				fprintf(logFile, "Error at line %d: Unterminated comment %s\n\n", comment_init , comment.c_str());
				error_count++;				
				BEGIN INITIAL;

			}	

\.			{
				fprintf(logFile, "Error at line %d: Unrecognised character %s\n\n", line_count ,yytext);
				error_count++;
			}

[0-9]+(\.[0-9]*)*([eE][+-]?[0-9]+)?	|
(\.|[0-9])*([eE][+-]?[0-9]+)?				{

				fprintf(logFile, "Error at line %d: Too many decimal point %s\n\n", line_count ,yytext);
				error_count++;				
			}

[0-9]+(\.[0-9]*)*([eE][+-]?([0-9]|".")*)?	|
(\.|[0-9])*([eE][+-]?([0-9]|".")*)?			{

				fprintf(logFile, "Error at line %d: Ill formed number %s\n\n", line_count ,yytext);
				error_count++;			
			}

[\._a-zA-Z0-9]*	{

				fprintf(logFile, "Error at line %d: Invalid prefix on ID or invalid suffix on Number %s\n\n", line_count ,yytext);
				error_count++;
			}





[\n]		{
				line_count++;
				// fprintf(tokenFile, "\n" ); //Delete this afterwards
			}

[ \t\f\r\v]+	{}


<<EOF>>		{
				fprintf(logFile, "Total Lines: %d\n",line_count );
				fprintf(logFile, "Total Errors: %d\n",error_count );
				return 0;
			}

.			{
				fprintf(logFile, "Error at line %d: Unrecognised character %s\n", line_count ,yytext);
				error_count++;
			}



%%


int main(int argc , char *argv[])
{


	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	logFile= fopen("log.txt","w");
	tokenFile= fopen("token.txt","w");

	yyin = fin;

	yylex();

	
	fclose(yyin);
	fclose(tokenFile);
	fclose(logFile);

	return 0;
}