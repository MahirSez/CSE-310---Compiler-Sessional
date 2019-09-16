%{
#include<bits/stdc++.h>
#include "1605024_SymbolTable.h"


using namespace std;

int yyparse(void);
int yylex(void);


extern FILE *yyin;

SymbolTable table(103);

FILE *fp , *errorFile , *logFile;



extern int line_count;
int error_count;

int ScopeTable::scopeTableID  = 0;
void yyerror(char *s)
{
	cout<<"Syntax error at line "<<line_count<<endl;
}


void SymbolTableInsertion(string name , string type) {

	SymbolInfo *ret = table.sameScopeLookUp(name );
	if( ret == 0 ) {
		
		table.Insert(name , type) ;
	}	
	else {
		fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
		error_count++;
	}
}

string removeLTHIRD(string &str) {

	string ret = "";
	for(int i =0 ; i < str.size(); i++) {
		if( str[i] == '[') break;
		ret += str[i];
	}
	return ret;
}

void setDeclarationType(string type , string varList) {

	string tmp = "";
	varList += ',';
	
	for(int i =0 ; i < varList.size() ; i++ )	 {
		if(varList[i] == ',') {

			string str = removeLTHIRD(tmp);
			SymbolInfo* pt = table.sameScopeLookUp(str);

			if( pt->getDeclaredType() == "") {
				pt->setDeclaredType(type);
			}
			tmp = "";
		}
		else tmp += varList[i];
	}
}


vector<string> getParamList(string str) {

	str +=',';
	string tmp = "";

	vector<string> vec;
	for(int i =0 ; i < str.size() ; i++ ) {

		if( str[i] == ',') {
			string ss = "";
			for(int j =0 ; j < tmp.size() ; j++ ) {

				if( tmp[j] == ' ') break;
				else ss += tmp[j];
			}
			vec.push_back(ss);
			tmp = "";
		
		}
		else tmp += str[i];
	}
	
	return vec;
	
}


vector< pair<string, string > > parameterList;
stack< vector<string> >argStack;


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

%}

%define api.value.type { SymbolInfo* }

%token INT IF ELSE FOR WHILE FLOAT DOUBLE CHAR  RETURN VOID MAIN PRINTLN ADDOP MULOP ASSIGNOP RELOP LOGICOP NOT SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP CONST_INT CONST_FLOAT ID


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start:	program	{
			fprintf(logFile , "\tSymbol Table:\n\n");
			table.printAll();
			fprintf(logFile , "Total Lines: %d\n\n",line_count);
			fprintf(logFile , "Total Errors: %d\n\n",error_count);
			fprintf(errorFile , "Total Errors: %d\n\n",error_count);
		}

program:	program unit {

				$$ = new SymbolInfo($1->getName() + $2->getName() ) ;

				fprintf(logFile , "At line no: %d program: program unit\n\n",line_count);
				fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
			}
			| unit	{ 
				$$ = $1 ;
				fprintf(logFile , "At line no: %d program: unit\n\n",line_count);
				fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
			}
			;
	
unit:	var_declaration	{ 
			$$ = $1 ;

			fprintf(logFile , "At line no: %d unit:	var_declaration\n\n",line_count);
			fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
		}
		|	func_declaration	{

			$$ = $1 ;

			fprintf(logFile , "At line no: %d unit:	func_declaration\n\n",line_count);
			fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
		}
		|	func_definition	{

			$$ = $1 ;

			fprintf(logFile , "At line no: %d unit:	func_definition\n\n",line_count);
			fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
		}
		;
     
func_declaration:	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "( " + $4->getName() + " );\n");
						fprintf(logFile , "At line no: %d func_declaration:	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );


						string name = $2->getName();
						string type = $2->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;
						vector<string> ret1 = getParamList($4->getName() );
						

						if( pt == 0 ) {		///funtion not declared yet
							
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function($2->getName() );

							fun->declare();

							string returnType = $1->getName();
							fun->setReturnType(returnType);
							

							for(int i = 0 ; i < ret1.size() ; i++ ) {

								fun->addParameter( ret1[i] );
							}

							pt->setFunction(fun);
							break;
						}

						

						//name found in scope table
						if( pt->getFunction() ==0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();


						if( declaredFunction->getReturnType() != $1->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}


						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret1.size() != ret2.size() ) {		//parameter list size mismatch
							
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						for(int i =0 ;i < ret1.size() ; i++ ) {		//paramter type mismatch

							if( ret1[i] != ret2[i] ) {
									
								fprintf(errorFile , "Error at Line %d: Function Parameter Type Mismatch\n\n" , line_count) ;
								error_count++;
							}
						}


					}
					|	type_specifier ID LPAREN RPAREN SEMICOLON	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "();\n");
						fprintf(logFile , "At line no: %d func_declaration:	type_specifier ID LPAREN RPAREN SEMICOLON\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

						string name = $2->getName();
						string type = $2->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;

						if( pt == 0 ) {		///function not yet declared

							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function($2->getName() );

							fun->declare();

							string returnType = $1->getName();
							fun->setReturnType(returnType);
							pt->setFunction(fun);

							break;
						}


						//name found in scope table
						if( pt->getFunction() ==0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();


						if( declaredFunction->getReturnType() != $1->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function `" , line_count) ;
							error_count++;
						}


						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret2.size() != 0 ) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
						}
						
					}
					;
		 
func_definition:	type_specifier ID LPAREN parameter_list RPAREN 	{


						string name = $2->getName();
						string type = $2->getType();
						string parameters = $4->getName();

						SymbolInfo* pt = table.sameScopeLookUp( name ) ;
						vector<string> ret1 = getParamList(parameters );

						updateGlobalParamList(parameters);

						if( pt == 0 ) {		///function not yet declared
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function($2->getName() );

							fun->define();
							fun->declare();

							string returnType = $1->getName();
							fun->setReturnType(returnType);

							for(int i = 0 ; i < ret1.size() ; i++ ) {

								fun->addParameter( ret1[i] );
							}
							pt->setFunction(fun);

							break;
						}

						//name found in scope table
						if( pt->getFunction() == 0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();

						if( declaredFunction->isDefined() ) {	//Already defined

							fprintf(errorFile , "Error at Line %d: Multiple Definition of Function %s\n\n" , line_count , name.c_str()) ;
							error_count++;
							break;
						}
						declaredFunction->define();

						if( declaredFunction->getReturnType() != $1->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}

						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret1.size() != ret2.size() ) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						for(int i =0 ;i < ret1.size() ; i++ ) {		//paramter type mismatch

							if( ret1[i] != ret2[i] ) {
									
								fprintf(errorFile , "Error at Line %d: Function Parameter Type Mismatch\n\n" , line_count) ;
								error_count++;
							}
						}

					}
					compound_statement	{


						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "( " + $4->getName() + " ) " + $7->getName() );
						fprintf(logFile , "At line no: %d func_definition:	type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
						
					}
					| type_specifier ID LPAREN RPAREN {

						
						string name = $2->getName();
						string type = $2->getType();
						SymbolInfo* pt = table.sameScopeLookUp( name ) ;

						if( pt == 0 ) {		///function not yet declared
							
							table.Insert(name , type  );
							pt = table.sameScopeLookUp(name ) ;

							Function* fun = new Function($2->getName() );

							fun->define();
							fun->declare();

							string returnType = $1->getName();
							fun->setReturnType(returnType);
							
							pt->setFunction(fun);
							break;
						}
						
						//name found in scope table
						if( pt->getFunction() == 0 ) {		//the variable name is occupied by a variable

							fprintf(errorFile , "Error at Line %d: Type Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						Function* declaredFunction = pt->getFunction();

						if( declaredFunction->isDefined() ) {	//Already defined

							fprintf(errorFile , "Error at Line %d: Multiple Definistion of Function %s\n\n" , line_count , name.c_str()) ;
							error_count++;
							break;
						}
						declaredFunction->define();

						if( declaredFunction->getReturnType() != $1->getName() ) {	//return Type mismatch

							fprintf(errorFile , "Error at Line %d: Function Return Type Mismatch\n\n" , line_count) ;
							error_count++;
						}

						vector<string>ret2 = declaredFunction->getParameterList();
						
						if( ret2.size() != 0) {		//parameter list size mismatch
							fprintf(errorFile , "Error at Line %d: Function Parameter Count Mismatch\n\n" , line_count) ;
							error_count++;
							break;
						}

						

					}
					compound_statement	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + "() " + $6->getName() );
						fprintf(logFile , "At line no: %d func_definition:	type_specifier ID LPAREN RPAREN compound_statement\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
					}
					;				


parameter_list:	parameter_list COMMA type_specifier ID	{

					$$ = new SymbolInfo($1->getName() + "," + $3->getName() + " " + $4->getName() );

					fprintf(logFile , "At line no: %d parameter_list: parameter_list COMMA type_specifier ID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

				}
				|	parameter_list COMMA type_specifier	{
					
					$$ = new SymbolInfo($1->getName() + "," + $3->getName());

					fprintf(logFile , "At line no: %d parameter_list: parameter_list COMMA type_specifier\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
				}
 				|	type_specifier ID	{
					
					$$ = new SymbolInfo($1->getName() + " " + $2->getName());

					fprintf(logFile , "At line no: %d parameter_list: type_specifier ID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
				}
				|	type_specifier	{
					
					$$ = $1;
					fprintf(logFile , "At line no: %d parameter_list: type_specifier\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
				}
 				;

 		
compound_statement:	LCURL {


						table.enterScope();

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							

							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;
							string type = "ID";

							if( name == "" ) {

								fprintf(errorFile , "Error at Line %d: Parameter name missing at function definition\n\n" , line_count );
								error_count++;
								continue;
							}

							SymbolInfo *ret = table.sameScopeLookUp(name );
							if( ret == 0 ) {
								
								table.Insert(name , type) ;
								ret = table.sameScopeLookUp(name);
								ret->setDeclaredType(dec_type);
								
							}
							else {
								fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
								error_count++;
							}
						}
						parameterList.clear();
					}
					statements RCURL	{
						
	
						$$ = new SymbolInfo("{\n" + $3->getName() + "}\n");
						fprintf(logFile , "At line no: %d compound_statement: LCURL statements RCURL\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

						table.printAll();
						table.exitScope();
					}


 		    		| LCURL RCURL	{

						table.enterScope();

						for(int i= 0 ; i < parameterList.size() ; i++)	 {
							

							string name = parameterList[i].first;
							string dec_type = parameterList[i].second;
							string type = "ID";

							if( name == "" ) {

								fprintf(errorFile , "Error at Line %d: Parameter name missing at function definition\n\n" , line_count );
								error_count++;
								continue;
							}							

							SymbolInfo *ret = table.sameScopeLookUp(name );
							if( ret == 0 ) {
								
								table.Insert(name , type) ;
								ret = table.sameScopeLookUp(name);
								ret->setDeclaredType(dec_type);
								
							}
							else {
								fprintf(errorFile , "Error at Line %d: Multiple Declaration of %s\n\n" , line_count , name.c_str()) ;
								error_count++;
							}
						}
						parameterList.clear();
						
						$$ = new SymbolInfo("{\n}\n");
						fprintf(logFile , "At line no: %d compound_statement: LCURL RCURL\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

						table.printAll();
						table.exitScope();
					}
 		    		;
 		    
var_declaration: type_specifier declaration_list SEMICOLON	{

					$$ = new SymbolInfo($1 -> getName() + " " +$2->getName()  + ";\n"  );
					fprintf(logFile , "At line no: %d var_declaration: type_specifier declaration_list SEMICOLON\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

					setDeclarationType($1->getName()  , $2->getName() ) ;
				}
		 		;
 		 
type_specifier: INT {	
					$$ = new SymbolInfo("int");
					fprintf(logFile , "At line no: %d type_specifier: INT\n\n",line_count);
					fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

				}
 				| FLOAT {
					$$ = new SymbolInfo("float" );
					fprintf(logFile , "At line no: %d type_specifier: FLOAT\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
				}
				| VOID {
					$$ = new SymbolInfo("void" );
					fprintf(logFile , "At line no: %d type_specifier: VOID\n\n",line_count);
					fprintf(logFile , "%s\n\n" , $$->getName().c_str() );
				}
				;
 		
declaration_list:	declaration_list COMMA ID	{

						$$ = new SymbolInfo($1 -> getName() + ","  + $3->getName() );
						fprintf(logFile , "At line no: %d declaration_list: declaration_list COMMA ID\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

						SymbolTableInsertion($3->getName() , $3->getType() );	//error handled in function

					}
					| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{

						$$ = new SymbolInfo($1 -> getName() + ","  +$3->getName() + "["  + $5->getName() + "]" , "");
						fprintf(logFile , "At line no: %d declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
						fprintf(logFile , "%s\n\n" , $$->getName().c_str() );

						SymbolTableInsertion($3->getName() , $3->getType() );		//error handled in function

						
						SymbolInfo *pt = table.sameScopeLookUp($3 -> getName() );
						if( pt != 0)	{
							pt->isArray = true;
						}
						
					}
					| 	ID	{
						
						$$ = $1;
						fprintf(logFile , "At line no: %d declaration_list: ID\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
						SymbolTableInsertion($$->getName()  , $$->getType ());		//error handled in function
					}
					| 	ID LTHIRD CONST_INT RTHIRD	{

						$$ = new SymbolInfo($1 -> getName() + "["  +$3->getName() + "]" , "");
						fprintf(logFile , "At line no: %d declaration_list: ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

						SymbolTableInsertion($1->getName()  , $1->getType ());		//error handled in function

						SymbolInfo *pt = table.sameScopeLookUp($1 -> getName() );

						if( pt != 0 ) {	
							pt->isArray = true;
						}
					}
					;
 		  
statements:	statement	{
				
				$$ = $1; 
				fprintf(logFile , "At line no: %d statements: statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

			}
	   		| statements statement	{
				
				$$ = new SymbolInfo($1->getName() + $2->getName() ) ;
				fprintf(logFile , "At line no: %d statements: statements statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
	   		;
	   
statement:	var_declaration	{

				$$ = $1;
				fprintf(logFile , "At line no: %d statement: var_declaration\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
			| 	expression_statement	{
				
				$$ = $1;
				fprintf(logFile , "At line no: %d statement: expression_statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
	  		|	compound_statement	{
				
				$$ = $1;
				fprintf(logFile , "At line no: %d statement: compound_statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
	  		|	FOR LPAREN expression_statement expression_statement expression RPAREN statement	{
				
				$$ = new SymbolInfo("for( " + $3->getName() + " "+ $4->getName() + " "+ $5->getName() + " ) " + $7->getName() ) ;
				fprintf(logFile , "At line no: %d statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
			| 	IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {

				$$ = new SymbolInfo("if( " + $3->getName() + " ) " + $5->getName() );
				fprintf(logFile , "At line no: %d statement: IF LPAREN expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
			| 	IF LPAREN expression RPAREN statement ELSE statement	{
				
				$$ = new SymbolInfo("if( " + $3->getName() + " ) " + $5->getName() + " else " + $7->getName());
				fprintf(logFile , "At line no: %d statement: IF LPAREN expression RPAREN statement statement ELSE statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

				
			}
	  		|	WHILE LPAREN expression RPAREN statement	{
				
				$$ = new SymbolInfo("while( " + $3->getName()  + " )" + $5->getName()  ) ;
				fprintf(logFile , "At line no: %d statement: WHILE LPAREN expression RPAREN statement\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
	  		|	PRINTLN LPAREN ID RPAREN SEMICOLON	{
				
				$$ = new SymbolInfo("println( " + $3->getName() + " );\n");
				fprintf(logFile , "At line no: %d statement: PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

			}
	  		|	RETURN expression SEMICOLON	{
				
				
				$$ = new SymbolInfo("return " + $2->getName() + " ;\n");
				fprintf(logFile , "At line no: %d statement: RETURN expression SEMICOLON\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
	  		;


	  
expression_statement:	SEMICOLON	{

							$$ = new SymbolInfo(";\n");
							fprintf(logFile , "At line no: %d expression_statement: SEMICOLON\n\n",line_count);
							fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
						}
						| 	expression SEMICOLON	{

							$$ = new SymbolInfo($1->getName() + " ;\n");
							fprintf(logFile , "At line no: %d expression_statement: expression SEMICOLON\n\n",line_count);
							fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

						}
						;
	  
variable:	ID	{

				$$ = $1;
				string name = $$->getName();

				fprintf(logFile , "At line no: %d variable:	ID\n\n",line_count);
				fprintf(logFile , "%s\n\n", name.c_str() ) ;
				
				SymbolInfo *pt = table.globalLookUp(name);
				if( pt == 0 ) {
					fprintf(errorFile , "Error at Line %d : Undeclared Variable: %s\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->getFunction() != 0 ) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch , %s is declared as a Function\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->isArray) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch\n\n",line_count );
					error_count++;

					$$->setDeclaredType(pt->getDeclaredType());
					$$->isArray = true;
				}
				else $$->setDeclaredType(pt->getDeclaredType());
				
			}
	 		| ID LTHIRD expression RTHIRD {
				
				$$ = new SymbolInfo($1->getName() + "[" + $3->getName() + "]" );
				string name = $1->getName();

				fprintf(logFile , "At line no: %d variable:	ID LTHIRD expression RTHIRD\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() );

				SymbolInfo *pt = table.globalLookUp(name);
				if( pt == 0 ) {
					fprintf(errorFile , "Error at Line %d : Undeclared Variable: %s\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if( pt->getFunction() != 0 ) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch , %s is declared as a Function\n\n",line_count , name.c_str() );
					error_count++;
				}
				else if(pt->isArray == 0) {
					fprintf(errorFile , "Error at Line %d : Type Mismatch\n\n",line_count , name.c_str() );
					error_count++;

					$$->setDeclaredType(pt->getDeclaredType());
					$$->isArray = false;
				}
				else {
					$$->setDeclaredType(pt->getDeclaredType());
					$$->isArray = true;
				}

				if($3->getDeclaredType() != "int") {
					fprintf(errorFile ,"Error at Line %d : Non-integer Array Index\n\n" , line_count );
					error_count++;
				}
			}
	 		;
	 
expression: logic_expression	{

				
				$$ = $1;
				fprintf(logFile , "At line no: %d expression: logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			}
			| variable ASSIGNOP logic_expression	{
				
				
				$$ = new SymbolInfo($1->getName() + " = " + $3->getName());
				fprintf(logFile , "At line no: %d expression: variable ASSIGNOP logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
	
				if( $1->getDeclaredType() == "" || $3->getDeclaredType() == "" || $1->getDeclaredType() != $3->getDeclaredType() ) {

					fprintf(errorFile , "Error at line %d : Assignment Operation, Type Mismatch\n\n", line_count);
					error_count++;
				}

				if( $1->getDeclaredType() == "float" ||  $3->getDeclaredType() == "float" )	$$->setDeclaredType("float");
				else if( $1->getDeclaredType() == "int" ||  $3->getDeclaredType() == "int" ) $$->setDeclaredType("int");
			}
			;
			
logic_expression:	rel_expression	{

						$$ = $1;
						fprintf(logFile , "At line no: %d logic_expression:	rel_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
					}
					| rel_expression LOGICOP rel_expression	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());
						$$->setDeclaredType("int" ) ;
						fprintf(logFile , "At line no: %d logic_expression:	rel_expression LOGICOP rel_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
					}
					;
			
rel_expression:	simple_expression {

					$$ = $1;
					fprintf(logFile , "At line no: %d rel_expression: simple_expression\n\n",line_count);
					fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
				}
				|	simple_expression RELOP simple_expression	{

					$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());
					$$->setDeclaredType("int") ;
					fprintf(logFile , "At line no: %d rel_expression: simple_expression RELOP simple_expression\n\n",line_count);
					fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
				}
				;
				
simple_expression:	term {

						$$ = $1;
						fprintf(logFile , "At line no: %d simple_expression: term\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
					}
					|	simple_expression ADDOP term	{

						$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());

						
						fprintf(logFile , "At line no: %d simple_expression: simple_expression ADDOP term\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

						if( $1->getDeclaredType() == "float" ||  $3->getDeclaredType() == "float" )	$$->setDeclaredType("float");
						else if( $1->getDeclaredType() == "int" ||  $3->getDeclaredType() == "int" ) $$->setDeclaredType("int");
					}
					;
					
term:	unary_expression	{

			$$ = $1;
			fprintf(logFile , "At line no: %d term:	unary_expression\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
		}
		|  term MULOP unary_expression	{

			$$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " + $3->getName());
			fprintf(logFile , "At line no: %d term: term MULOP unary_expression\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

			if( $1->getDeclaredType() == "float" ||  $3->getDeclaredType() == "float" )	$$->setDeclaredType("float");
			else if( $1->getDeclaredType() == "int" ||  $3->getDeclaredType() == "int" ) $$->setDeclaredType("int");

			if($2->getName() == "%") {

				if($1->getDeclaredType() != "int" || $3 ->getDeclaredType() != "int") {

					fprintf(errorFile ,"Error at line %d : non-Integer operand on modulus operator\n\n",line_count );
					error_count++;
				}
				$$->setDeclaredType ("int");
			}
		}
		;

unary_expression:	ADDOP unary_expression  {

						$$ = new SymbolInfo($1->getName() + $2->getName() );
						fprintf(logFile , "At line no: %d unary_expression:	ADDOP unary_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

						$$->setDeclaredType($2->getDeclaredType());
					}
					| NOT unary_expression {

						$$ = new SymbolInfo($1->getName() + $2->getName() );
						fprintf(logFile , "At line no: %d unary_expression:	NOY unary_expression\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;

						$$->setDeclaredType("int");
					}
					| factor {

						$$ = $1;
						fprintf(logFile , "At line no: %d unary_expression: factor\n\n",line_count);
						fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
					}
					;
	
factor: variable	{	

			$$ = $1;
			fprintf(logFile , "At line no: %d factor: variable\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
		}
		| ID {	argStack.push(vector<string>() ); }	LPAREN argument_list RPAREN	{

			$$ = new SymbolInfo($1->getName() + "(" + $4->getName() + ")" );
			fprintf(logFile , "At line no: %d factor: ID LPAREN argument_list RPAREN\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			
			SymbolInfo* pt = table.globalLookUp($1->getName() );


			vector<string>arg = argStack.top();
			argStack.pop();


			if(pt == 0 ) {

				fprintf(errorFile , "Error at line: %d : Function not defined\n\n",line_count );
				error_count++;
				break;
			}

			Function *fun = pt->getFunction();

			if( fun ==0 ) {

				fprintf(errorFile , "Error at line: %d : %s is not declared as a Function\n\n",line_count , $1->getName().c_str() ); 
				error_count++;
				break;
			}

			$$->setDeclaredType(fun->getReturnType() ) ;

			if(fun->isDefined() == 0) {

				fprintf(errorFile , "Error at line: %d : Function declared, but not defined\n\n",line_count  ); 
				error_count++;
			}
			
			vector<string>param = fun->getParameterList() ;


			if(param.size() != arg.size() ) {

				fprintf(errorFile , "Error at line: %d : Function parameter count mismatch\n\n",line_count ); 
				error_count++;
				break;
			}

			for(int i =0 ; i < param.size() ; i++ ) {

				if( param[i] != arg[i] ) {

					fprintf(errorFile , "Error at line: %d : Function parameter type mismatch\n\n",line_count ); 
					error_count++;
				}
			}

		}
		|	LPAREN expression RPAREN	{
			
			$$ = new SymbolInfo("( " + $2->getName() + " )");
			fprintf(logFile , "At line no: %d factor: LPAREN expression RPAREN\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;			
			$$->setDeclaredType($2->getDeclaredType() ) ;
		}
		| 	CONST_INT	{
			$$ = $1;
			fprintf(logFile , "At line no: %d factor: CONST_INT\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;			
			$$->setDeclaredType("int");
		}
		|	 CONST_FLOAT	{
			$$ = $1;
			fprintf(logFile , "At line no: %d factor: CONST_FLOAT\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;	
			$$->setDeclaredType("float");		
		}
		|	variable INCOP	{
			$$ = new SymbolInfo($1->getName() + "++" ) ;
			fprintf(logFile , "At line no: %d factor: variable INCOP\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			$$->setDeclaredType($1->getDeclaredType() ) ;
		}
		|	variable DECOP	{
			$$ = new SymbolInfo($1->getName() +"--" ) ;
			fprintf(logFile , "At line no: %d factor: variable DECOP\n\n",line_count);
			fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
			$$->setDeclaredType($1->getDeclaredType() ) ;
		}
		;
	
argument_list:	arguments	{

					$$ = $1;
					fprintf(logFile , "At line no: %d argument_list: arguments\n\n",line_count);
					fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
				}
				|
				;
		
arguments:	arguments COMMA logic_expression	{

				$$ = new SymbolInfo($1->getName() + " , " + $3->getName());
				fprintf(logFile , "At line no: %d arguments: arguments COMMA logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;
				argStack.top().push_back($3->getDeclaredType());
			}
	      	| logic_expression	{

				$$ = $1;
				fprintf(logFile , "At line no: %d arguments: logic_expression\n\n",line_count);
				fprintf(logFile , "%s\n\n", $$->getName().c_str() ) ;	
				argStack.top().push_back($1->getDeclaredType());
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

	
	errorFile = fopen("1605024_error.txt" , "w");
	logFile = fopen("1605024_log.txt" , "w");

	yyin=fp;
	yyparse();
	

	fclose(fp);
	
	return 0;
}

