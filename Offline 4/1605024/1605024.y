%{
#include<bits/stdc++.h>
#include "1605024_SymbolTable.h"


using namespace std;

int yyparse(void);
int yylex(void);


extern FILE *yyin;

const int N = 103;
SymbolTable table(N);

FILE *fp  , *logFile , *asmFile  , *optimizedAsmFile;

extern int line_count;

int error_count;

int ScopeTable::scopeTableID  = 0 ;
int labelCount = 0 , tempCount= 0;

vector< pair<string, string > > parameterList;
stack< vector<string> > asmArgStack ;
vector<string> asmVariables ;
vector< pair< string , string > > asmArrays;
string curFun;


void yyerror(char *s)
{
	cout<<"Syntax error at line "<<line_count<<endl;
}


void SymbolTableInsertion(string name , string type) {

	table.Insert(name , type) ;	
}

void updateGlobalParamList(string str) {

	string tmp = "";
	str += ',';

	for(int i =0 ; i < str.size() ; i++ ) {

		if( str[i] == ',') {
		
			string s1 = "" , s2 = "";

			int flag = 0;

			for(int j =0 ; j < tmp.size() ; j++ ) {

				if( tmp[j] == ' ') flag = 1;
				else if( flag == 0) s1 += tmp[j];
				else if( flag == 1) s2 += tmp[j];
				
			}

			tmp = "";

			parameterList.push_back(pair<string,string>(s2, s1));

		}
		else tmp += str[i];
	}
}


string toString(int num) {


	string ret = "";

	while(num) {

		ret += char((num%10) + '0');
		num/=10;
	}
	reverse(ret.begin() , ret.end());
	return ret;
}

string newTemp() {


	string var = "t" + toString(++tempCount); 
	asmVariables.push_back(var);
	return var;
}

string newLabel() {


	return  "L" + toString(++labelCount) ;
}
	
string AddAssemblyPrefix(string code) {

	string prefix = ".model small\n";
	prefix += ".stack 100h\n";
	prefix += ".data\n";


	for(int i =0 ; i < asmVariables.size() ; i++ ) {

		prefix += "\t" + asmVariables[i] + " dw ?\n";
	}

	for(int i =0 ; i < asmArrays.size() ; i++ ) {

		prefix += "\t" + asmArrays[i].first + " dw " + asmArrays[i].second + " dup (?)\n" ;
	}
	

	prefix += ".code\n\n";
	string label1 = newLabel();
	string label2 = newLabel();

	prefix +="println proc\n\
	pusha\n\
	\n\
	mov bx , 10d\n\
	xor cx , cx\n\
	xor dx , dx\n\
	\n\
	cmp ax , 0\n\
	jge " + label1 + "\n\
	neg ax\n\
	push ax\n\
	push dx\n\
	mov dx , '-'\n\
	mov ah , 2\n\
	int 21h\n\
	pop dx\n\
	pop ax\n" + 

label1 + ":\n\
	idiv bx\n\
	push dx\n\
	xor dx , dx\n\
	inc cx\n\
	cmp ax , 0\n\
	je " + label2 +"\n\
	jmp " + label1 + "\n" + 
label2 + ":\n\
	mov ah , 2\n\
	pop dx\n\
	add dx , 30h\n\
	int 21h\n\
	loop " + label2 + "\n\
	mov dl , 0ah\n\
	int 21h\n\
	mov dl , 0dh\n\
	int 21h\n\
	\n\
	popa\n\
	ret\n\
println endp\n\n";

	return prefix + code + "\tend main\n";

}
string removeFrontSpace(string name) {

	bool flag = false;
	string ret = "";
	for(int i =0 ; i < name.size() ; i++ ) {
		

		if(flag== true || name[i] != '\t') {
			flag = true;
			ret += name[i];
		}
	}
	return ret;
}


pair<string , string > process(string line) {


	string first = "";
	string second = "";

	int state = 0;
	for(int i =0 ; i < line.size(); i++ ) {

		if(line[i] == ' ') {
			state = 1;
			continue;
		}

		if( state == 0 ) first +=line[i];
		else  second += line[i];
	}
	return {first , second};
}

void optimize(string srcCode) {

	string optimizedCode = "";


	vector<string>vec;
	string line = "";

	for(int i =0 ; i < srcCode.size() ; i++ ) {
		if( srcCode[i] == '\n')	{
			if(line.size() > 0 ) vec.push_back(removeFrontSpace(line) );
			line = "";
		}
		else line += srcCode[i];
	}
	vector<string>ret;

	for(int i =0 ; i < vec.size() -1;i++ ) {
		
		pair<string,string>f = process(vec[i]);
		pair<string,string>s = process(vec[i+1]);

		if( f.first == "push" && s.first  == "pop" && f.second == s.second ) {
			i+=2;
		}
		else optimizedCode += vec[i] + '\n';
	}
	optimizedCode += vec[vec.size()-1];

	fprintf(optimizedAsmFile , "%s\n" , optimizedCode.c_str() );

}



%}

%define api.value.type { SymbolInfo* }

%token INT IF ELSE FOR WHILE FLOAT DOUBLE CHAR  RETURN VOID MAIN PRINTLN ADDOP MULOP ASSIGNOP RELOP LOGICOP NOT SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP CONST_INT CONST_FLOAT ID


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start:	program	{

			$$ = $1;

			$$ ->code = AddAssemblyPrefix($$->code);
			fprintf(asmFile , "%s\n" , $$->code.c_str() );
			optimize($$->code);
			fprintf(logFile, "Line Count: %d\n\n" , line_count);
			fprintf(logFile, "Error Count: %d\n" , error_count);
		}

program:	program unit {

				$$ = new SymbolInfo($1->getName() + $2->getName() ) ;
				$$->code = $1->code + $2->code;

			}
			| unit	{ 
				$$ = $1 ;
			}
			;
	
unit:	var_declaration	{ 
			$$ = $1 ;
		}
 		|	func_declaration	{
			$$ = $1 ;
			
		}
		|	func_definition	{
			$$ = $1 ;
			
		}
		;
     
func_declaration:	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	{
						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "( " + $4->getName() + " );\n");

					}
					|	type_specifier ID LPAREN RPAREN SEMICOLON	{
						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "();\n");
						
					}
					;
		 
func_definition:	type_specifier ID LPAREN parameter_list RPAREN 	{

						updateGlobalParamList($4->getName());
						curFun = $2->getName();
							
						table.Insert($2->getName(), $2->getType()  );
						asmVariables.push_back($2->getName() + "_retVar");
						
					}
					compound_statement	{

						SymbolInfo *pt = table.globalLookUp(curFun);
						
						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "( " + $4->getName() + " ) " + $7->getName() );

						$$->code = "proc " + $2->getName() + "\n";
						$$->code += "\tpusha\n\n" ;

						for(int i = 0 ; i < pt->asmParameterList.size() ; i++ ) {
							$$->code += "\tpush " + pt->asmParameterList[i] + "\n";
						}

						$$->code += $7->code;

						$$->code += "\n" + $2->getName() + "_return:\n";

						for(int i = pt->asmParameterList.size()-1 ; i >=0 ; i-- ) {
							$$->code += "\tpop " + pt->asmParameterList[i] + "\n";
						}
						$$->code += "\tpopa\n";
						$$->code +=	"\tret\n";
						$$->code +=  $2->getName() + " endp\n\n";

					}
					| type_specifier ID LPAREN RPAREN {

						curFun = $2->getName();
						table.Insert($2->getName() , $2->getType()  );
						asmVariables.push_back($2->getName() + "_retVar");

					}
					compound_statement	{

						SymbolInfo *pt = table.globalLookUp(curFun);
						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "() " + $6->getName() );

						$$->code = "proc " + $2->getName() + "\n";					

						if( $2->getName() == "main" ) {
							$$->code += "\tmov ax , @data\n";
							$$->code += "\tmov ds , ax\n\n";							
						}
						else {
							$$->code += "\tpusha\n\n" ;
						}
						$$->code += $6->code;		
						$$->code += "\n" + $2->getName() + "_return:\n";				

						if( $2->getName() == "main" ) {
							
							$$->code += "\n\tmov ah, 4ch\n\tint 21h\n";
						}
						else {
							$$->code += "\tpopa\n";
							$$->code +=	"\tret\n";							
						}

						$$->code +=  $2->getName() + " endp\n\n";
					}
					;				


parameter_list:	parameter_list COMMA type_specifier ID	{

					$$ = new SymbolInfo($1->getName() + "," + $3->getName() + " " + $4->getName() );
				}
				|	parameter_list COMMA type_specifier	{
					
					$$ = new SymbolInfo($1->getName() + "," + $3->getName());
				}
 				|	type_specifier ID	{
					
					$$ = new SymbolInfo($1->getName() + " " + $2->getName());
				}
				|	type_specifier	{
					
					$$ = $1;
				}
 				;

 		
compound_statement:	LCURL {

						table.enterScope();
						SymbolInfo *pt = table.globalLookUp(curFun);

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;

							pt->asmParameterList.push_back(name + toString(table.getCurrentScopeID() ) );
							asmVariables.push_back(name + toString(table.getCurrentScopeID() ) );
							table.Insert(name , "ID") ;
						}
						parameterList.clear();
						
					}
					statements RCURL	{
						
						$$ = new SymbolInfo("{\n" + $3->getName() + "}\n");
						$$->code = $3->code;
						table.exitScope();
					}
 		    		| LCURL RCURL	{

						table.enterScope();
						SymbolInfo *pt = table.globalLookUp(curFun);

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;

							pt->asmParameterList.push_back(name + toString(table.getCurrentScopeID() ) );
							asmVariables.push_back(name + toString(table.getCurrentScopeID() ) );
							table.Insert(name , "ID") ;
						}
						parameterList.clear();
						
						
						table.exitScope();
					}
 		    		;
 		    
var_declaration: type_specifier declaration_list SEMICOLON	{
					$$ = new SymbolInfo($1 -> getName() + " " +$2->getName()  + ";\n"  );
				}
		 		;
 		 
type_specifier: INT {	
					$$ = new SymbolInfo("int");

				}
 				| FLOAT {
					$$ = new SymbolInfo("float" );
				}
				| VOID {
					$$ = new SymbolInfo("void" );
				}
				;
 		
declaration_list:	declaration_list COMMA ID	{

						$$ = new SymbolInfo($1 -> getName() + ","  + $3->getName() );

						asmVariables.push_back($3->getName() + toString(table.getCurrentScopeID() ) ) ;
						SymbolTableInsertion($3->getName()  , $3->getType ());	

					}
					| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{

						$$ = new SymbolInfo($1 -> getName() + ","  +$3->getName() + "["  + $5->getName() + "]" , "");
						asmArrays.push_back({ $3->getName() + toString(table.getCurrentScopeID() ) , $5->getName() } );

						SymbolTableInsertion($3->getName() , $3->getType() );		
						SymbolInfo *pt = table.sameScopeLookUp($3 -> getName() );
						pt->isArray = true;
						
					}
					| 	ID	{
						
						
						$$ = $1;
						asmVariables.push_back($1->getName() + toString(table.getCurrentScopeID() ) ) ;
						SymbolTableInsertion($$->getName()  , $$->getType ());	
					}
					| 	ID LTHIRD CONST_INT RTHIRD	{

						$$ = new SymbolInfo($1 -> getName() + "["  +$3->getName() + "]" , "");
						asmArrays.push_back({$1->getName() + toString(table.getCurrentScopeID() ) , $3->getName() } ) ;

						SymbolTableInsertion($1->getName()  , $1->getType ());		
						SymbolInfo *pt = table.sameScopeLookUp($1 -> getName() );
						pt->isArray = true;
					}
					;
 		  
statements:	statement	{
				
				$$ = $1; 
				

			}
	   		| statements statement	{

				
				
				$$ = new SymbolInfo($1->getName() + $2->getName() ) ;
				$$->code = $1->code + $2->code;
				$$->setAsmSymbol($2->getAsmSymbol());
			}
	   		;
	   
statement:	var_declaration	{

				
				$$ = $1;

			}
			| 	expression_statement	{
				
				$$ = $1;

			}
	  		|	compound_statement	{
				
				$$ = $1;

			}
	  		|	FOR LPAREN expression_statement expression_statement expression RPAREN statement	{
				
				$$ = new SymbolInfo("for( " + $3->getName() + " "+ $4->getName() + " "+ $5->getName() + " ) " + $7->getName() ) ;


				string label1 = newLabel();
				string label2 = newLabel();
				$$->code += $3->code;

				$$->code += label1 + ":\n";

				if($4->code  != "") {
					$$->code += $4->code;
					$$->code += "\tcmp " + $4->getAsmSymbol() + " , 0\n";
					$$->code += "\tje " + label2 + "\n";
				}

				$$->code += $7->code + $5->code;
				$$->code += "\tjmp " + label1 + "\n";
				$$->code += label2 + ":\n";

			}
			| 	IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {

				$$ = new SymbolInfo("if( " + $3->getName() + " ) " + $5->getName() );

				string label1 = newLabel();

				$$->code += $3->code;
				$$->code += "\tcmp " + $3->getAsmSymbol() + " , 0\n" ;
				$$->code += "\tje " + label1 + "\n";
				$$->code += $5->code;
				$$->code += label1 + ":\n";

			}
			| 	IF LPAREN expression RPAREN statement ELSE statement	{
				
				$$ = new SymbolInfo("if( " + $3->getName() + " ) " + $5->getName() + " else " + $7->getName());

				string label1 = newLabel();
				string label2 = newLabel();

				$$->code += $3->code;
				$$->code += "\tcmp " + $3->getAsmSymbol() + " , 0\n" ;
				$$->code += "\tje " + label1 + "\n";
				$$->code += $5->code;
				$$->code += "\tjmp " + label2 + "\n";
				$$->code += label1 + ":\n";
				$$->code += $7->code;
				$$->code += label2 + ":\n";
				
			}
	  		|	WHILE LPAREN expression RPAREN statement	{
				
				$$ = new SymbolInfo("while( " + $3->getName()  + " )" + $5->getName()  ) ;


				string label1 = newLabel();
				string label2 = newLabel();

				$$->code += label1 + ":\n";
				$$->code += $3->code;
				$$->code += "\tcmp " + $3->getAsmSymbol() + " , 0\n";
				$$->code += "\tje " + label2 + "\n";
				$$->code += $5->code;
				$$->code += "\tjmp " + label1 + "\n";
				$$->code += label2 + ":\n";
				
			}
	  		|	PRINTLN LPAREN ID RPAREN SEMICOLON	{
				

				$$ = new SymbolInfo("println( " + $3->getName() + " );\n");
				$$->code += "\tpush ax\n";
				$$->code += "\tmov ax , " + $3->getName() + toString(table.getScopeTableID($3->getName()) ) + "\n";
				$$->code += "\tcall println\n";
				$$->code += "\tpop ax\n";
				
			}
	  		|	RETURN expression SEMICOLON	{
				
				$$ = new SymbolInfo("return " + $2->getName() + " ;\n");

				$$->code = $2->code;
				$$->code += "\tpush " + $2->getAsmSymbol() + "\n";
				$$->code += "\tpop " + curFun + "_retVar\n";
				$$->code += "\tjmp " + curFun+ "_return\n";
				$$->setAsmSymbol(curFun + "_retVar");
			}
	  		;


	  
expression_statement:	SEMICOLON	{

							$$ = new SymbolInfo(";\n");

						}
						| 	expression SEMICOLON	{

							$$ = new SymbolInfo($1->getName() + " ;\n");
							$$->code = $1->code;
							$$->setAsmSymbol($1->getAsmSymbol());
						}
						;
	  
variable:	ID	{

				$$ = $1;

				string name = $$->getName();

				$$->setAsmSymbol($1->getName() + toString(table.getScopeTableID($1->getName())) ) ;
				
			}
	 		| ID LTHIRD expression RTHIRD {
				
				$$ = new SymbolInfo($1->getName() + "[" + $3->getName() + "]" );

				$$->code += $3->code;
				$$->code += "\tmov bx , " + $3->getAsmSymbol() + "\n";
				$$->code += "\tadd bx , bx\n";

				$$->setAsmSymbol($1->getName() + toString(table.getScopeTableID($1->getName() ) ) );
				$$->isArray = true;
			}
	 		;
	 
expression: logic_expression	{

				
				$$ = $1;

			}
			| variable ASSIGNOP logic_expression	{
				
				
				$$ = new SymbolInfo($1->getName() + " = " + $3->getName());

				$$->code += $3->code + $1->code;

				$$->code += "\tpush " + $3->getAsmSymbol() + "\n";

				if($1->isArray) {

					$$->code += "\tpop " + $1->getAsmSymbol() + "[bx]\n";
				}
				else {
					$$->code += "\tpop " + $1->getAsmSymbol() + "\n";
				}

				$$->setAsmSymbol($1->getAsmSymbol() ) ;
			}
			;
			
logic_expression:	rel_expression	{

						$$ = $1;
						
					}
					| rel_expression LOGICOP rel_expression	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());

						string var = newTemp();
						string label1 = newLabel();
						string label2 = newLabel();

						$$->code += $1->code + $3->code;

						if( $2->getName() == "&&" ) {

							$$->code += "\tcmp " + $1->getAsmSymbol() + " , 0\n";
							$$->code += "\tje " + label1 + "\n";
							$$->code += "\tcmp " + $3->getAsmSymbol() + " , 0\n";
							$$->code += "\tje " + label1 + "\n";
							$$->code += "\tmov " + var + " , 1\n";
							$$->code += "\tjmp " + label2 + "\n";
							$$->code += label1 + ":\n";
							$$->code += "\tmov " + var + " , 0\n";
							$$->code += label2 + ":\n";
						}
						else if( $2->getName() == "||") {
							
							$$->code += "\tcmp " + $1->getAsmSymbol() + " , 0\n";
							$$->code += "\tjne " + label1 + "\n";
							$$->code += "\tcmp " + $3->getAsmSymbol() + " , 0\n";
							$$->code += "\tjne " + label1 + "\n";
							$$->code += "\tmov " + var + " , 0\n";
							$$->code += "\tjmp " + label2 + "\n";
							$$->code += label1 + ":\n";
							$$->code += "\tmov " + var + " , 1\n";
							$$->code += label2 + ":\n";	
						}
						$$->setAsmSymbol(var);
					}
					;
			
rel_expression:	simple_expression {

					$$ = $1;

				}
				|	simple_expression RELOP simple_expression	{

					$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());

					string var = newTemp();
					string label1 = newLabel();
					string label2 = newLabel();

					$$->code += $1->code + $3->code;
					$$->code += "\tmov ax, " + $1->getAsmSymbol() + "\n";
					$$->code += "\tcmp ax, " + $3->getAsmSymbol() + "\n";

					if( $2->getName() == "<" )	$$->code += "\tjl " + label1 + "\n";
					else if( $2->getName() == "<=" )	$$->code += "\tjle " + label1 + "\n";
					else if( $2->getName() == ">" )	$$->code += "\tjg " + label1 + "\n";	
					else if( $2->getName() == ">=" )	$$->code += "\tjge " + label1 + "\n";
					else if( $2->getName() == "==" )	$$->code += "\tje " + label1 + "\n";
					else if( $2->getName() == "!=" )	$$->code += "\tjne " + label1 + "\n";
					
					$$->code += "\tmov " + var + " , 0\n";
					$$->code += "\tjmp "+ label2 +"\n";
					$$->code += label1 + ":\n";
					$$->code += "\tmov " + var + " , 1\n";
					$$->code += label2 + ":\n";

					$$->setAsmSymbol(var);	

				}
				;
				
simple_expression:	term {

						$$ = $1;
						
					}
					|	simple_expression ADDOP term	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());

						string var = newTemp();

						$$->code += $1->code + $3->code;
						$$->code += "\tmov ax , " + $1->getAsmSymbol() + "\n";
						
						if($2->getName() == "+") $$->code += "\tadd ax , " + $3->getAsmSymbol() + "\n";
						else $$->code += "\tsub ax , " + $3->getAsmSymbol() + "\n";

						$$->code += "\tmov " + var + " , ax\n";

						$$->setAsmSymbol(var);
					}
					;
					
term:	unary_expression	{

			$$ = $1;
		}
		|  term MULOP unary_expression	{

			$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());


			$$->code += $1->code + $3->code;

			string var = newTemp();

			$$->setAsmSymbol(var);

			if($2->getName() == "*") {

				$$->code += "\tmov ax , " + $1->getAsmSymbol() + "\n";
				$$->code += "\timul " + $3->getAsmSymbol() + "\n";
				$$->code += "\tmov " + var + " , ax\n" ;

			}
			else if( $2->getName() == "/") {
				
				string label1 = newLabel();

				$$->code += "\tmov ax , " + $1->getAsmSymbol() + "\n";
				$$->code += "\txor dx , dx\n";
				$$->code += "\tcmp ax , 0\n";
				$$->code += "\tjge " + label1 + "\n";
				$$->code += "\tmov dx , -1\n";
				$$->code += label1 + ":\n";
				$$->code += "\tidiv " + $3->getAsmSymbol() + "\n";
				$$->code += "\tmov " + var + " , ax\n" ;				
			}

			else {

				string label1 = newLabel();

				$$->code += "\tmov ax , " + $1->getAsmSymbol() + "\n";
				$$->code += "\txor dx , dx\n";
				$$->code += "\tcmp ax , 0\n";
				$$->code += "\tjge " + label1 + "\n";
				$$->code += "\tmov dx , -1\n";
				$$->code += label1 + ":\n";
				$$->code += "\tidiv " + $3->getAsmSymbol() + "\n";
				$$->code += "\tmov " + var + " , dx\n" ;		
			}
		}
		;

unary_expression:	ADDOP unary_expression  {

						$$ = new SymbolInfo($1->getName() + $2->getName() );			
						$$->code += $2->code;

						if( $1->getName() == "-") {

							string var = newTemp();
							$$->code += "\tpush " + $2->getAsmSymbol() + "\n";
							$$->code += "\tpop " + var + "\n";
							$$->code += "\tneg " +  var + "\n";
							$$->setAsmSymbol(var);
						}
						else {
							
							$$->setAsmSymbol($2->getAsmSymbol() ) ;
						}
					}
					| NOT unary_expression {

						$$ = new SymbolInfo($1->getName() + $2->getName() );

						string label1 = newLabel();
						string label2 = newLabel();
						string var = newTemp();

						$$->code += $2->code;
						$$->code += "\tcmp " + $2->getAsmSymbol() + " , 0\n";
						$$->code += "\tje " + label1 + "\n";
						$$->code += "\tmov " + var + " , 0\n" ;
						$$->code += "\tjmp " + label2 + "\n";
						$$->code += label1 + ":\n";
						$$->code += "\tmov " + var + " , 1\n";
						$$->code += "\tjmp " + label2 + "\n";
						$$->code += label2 + ":\n";

						$$->setAsmSymbol(var);
					}
					| factor {

						$$ = $1;
					}
					;
	
factor: variable	{	

			$$ = $1;
		}
		| ID {

			asmArgStack.push(vector<string>() );
		}	
		LPAREN argument_list RPAREN	{
			
			$$ = new SymbolInfo($1->getName() + "(" + $4->getName() + ")" );
			
			vector<string>asmArg = asmArgStack.top();
			
			asmArgStack.pop();

			$$->code += $4->code;
			SymbolInfo *pt = table.globalLookUp($1->getName());

			for(int i =0 ; i < asmArg.size() ;i++ ) {

				$$->code += "\tpush "+ asmArg[i] + "\n";
				$$->code += "\tpop " + pt->asmParameterList[i] + "\n";
			}

			$$->code += "\tcall "+ $1->getName() + "\n";

			$$->setAsmSymbol($1->getName() + "_retVar" );

		}
		|	LPAREN expression RPAREN	{
			
			$$ = new SymbolInfo("( " + $2->getName() + " )");
			$$->code = $2->code;
			$$->setAsmSymbol($2->getAsmSymbol() ) ;
		}
		| 	CONST_INT	{
			$$ = $1;
			string var = newTemp();

			$$->setAsmSymbol(var);
			$$->code = "\tmov "+ var + " , " + $$->getName() + "\n";
		}
		|	 CONST_FLOAT	{
			$$ = $1;

			string var = newTemp();

			$$->setAsmSymbol(var);
			$$->code = "\tmov "+ var + " , " + $$->getName() + "\n";
				
		}
		|	variable INCOP	{
			$$ = new SymbolInfo($1->getName() + "++" ) ;

			string var = newTemp();

			$$->code += $1->code;

			if($1->isArray) {

				$$->code += "\tpush " + $1->getAsmSymbol() + "[bx]\n";
				$$->code += "\tpop " + var + "\n";
				$$->code += "\tinc " + $1->getAsmSymbol() + "[bx]\n";
			}
			else {
				$$->code += "\tpush " + $1->getAsmSymbol() + "\n";
				$$->code += "\tpop " + var + "\n";
				$$->code += "\tinc " + $1->getAsmSymbol() + "\n";
			}
			
			$$->setAsmSymbol(var);
		}
		|	variable DECOP	{
			$$ = new SymbolInfo($1->getName() +"--" ) ;
			string var = newTemp();

			$$->code += $1->code;

			if($1->isArray) {

				$$->code += "\tpush " + $1->getAsmSymbol() + "[bx]\n";
				$$->code += "\tpop " + var + "\n";
				$$->code += "\tdec " + $1->getAsmSymbol() + "[bx]\n";
			}
			else {
				$$->code += "\tpush " + $1->getAsmSymbol() + "\n";
				$$->code += "\tpop " + var + "\n";
				$$->code += "\tdec " + $1->getAsmSymbol() + "\n";
			}
			
			$$->setAsmSymbol(var);
		}
		;
	
argument_list:	arguments	{

					$$ = $1;
				}
				|	{
					$$ = new SymbolInfo();
				}
				;
		
arguments:	arguments COMMA logic_expression	{

				$$ = new SymbolInfo($1->getName() + " , " + $3->getName());
				asmArgStack.top().push_back($3->getAsmSymbol());
			}
	      	| logic_expression	{

				$$ = $1;
				asmArgStack.top().push_back($1->getAsmSymbol());
			}
			;


%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		return 0;
	}

	logFile = fopen("1605024_log.txt" , "w");
	asmFile = fopen("1605024_code.asm" , "w");
	optimizedAsmFile = fopen("1605024_optimized_code.asm" , "w");

	yyin=fp;
	yyparse();

	fclose(fp);
	
	return 0;
}
