#include<bits/stdc++.h>
using namespace std;

extern FILE *logFile; 

class Function  {

private:
    string returnType , name;
    vector<string>parameterList;
    bool declared , defined;
public:



    vector<string>asmParameterList;
    Function(string name)  {
        declared = false;
        defined = false;    
        this->name = name;
    }
    void declare() {
        declared = 1;
    }
    void define() {
        defined = 1;
    }
    string getName() {
        return name;
    }

    bool isDeclared() {
        return declared;
    }

    bool isDefined() {
        return defined;
    }

    void setReturnType(string type) {
        returnType = type;
    }
    string getReturnType() {
        return returnType;
    }

    void addParameter(string parameter) {
        parameterList.push_back(parameter);
    }
    vector<string> getParameterList() {
        return parameterList;
    }
};


class SymbolInfo {

private:
	string name , type;
    string declared_type;
    Function* function;
    
    string asmSymbol;
public:
	SymbolInfo* nextSymbol;
    bool isArray;
    string code;

    vector<string>asmParameterList;


    SymbolInfo() {
		name = "";
		type = "";
        declared_type = "";
        asmSymbol = "";
        code = "";
        nextSymbol = NULL;
        isArray = false;
        function = 0;
    }
    SymbolInfo(string symbolName , string symbolType = "") {

		name = symbolName;
		type = symbolType;
        declared_type = "";
        asmSymbol = "";
        code = "";
		nextSymbol = NULL;
        isArray = false;
        function = 0;
    }

    void setAsmSymbol(string symbol) {
        asmSymbol = symbol;
    }
    string getAsmSymbol() {
        return asmSymbol;
    }

    void setName( string &symbolName) {
    	name = symbolName;
    }

    string getName() {
    	return name;
    }

    void setType( string &symbolType) {
    	type = symbolType;
    }

    string getType() {
    	return type;
    }


    void setDeclaredType(string type) {
        declared_type = type;
    }
    string getDeclaredType() {
        return declared_type;
    }

    void setFunction(Function *fun) {
        function = fun;
    }
    Function* getFunction() {
        return function;
    }

    ~SymbolInfo() {
    	nextSymbol = NULL;
		delete nextSymbol;
    }
};



class ScopeTable {

private:
    SymbolInfo** ara;
    int id , len;


public:

	ScopeTable* parentScope;
    static int scopeTableID;

    ScopeTable(int n) {

		len = n;

    	ara = new SymbolInfo*[n];
		for(int i =0 ; i < n ; i++ ) ara[i] = NULL;

        parentScope = NULL;
        id = ++scopeTableID;
    }


    int getHash( string& name) {

        int sum = 0;
        int prime = 23 , mod = 97;
        int prod = 1;

        for(int i =0 ; i < name.size() ; i++ ) {

            sum = (sum + name[i]* prod) %len;
            prod = (prod * prime)% mod;
        }
        return sum;
    }

    bool Insert( string name , string type) {

        int headID = getHash(name);

    


        SymbolInfo* node = new SymbolInfo(name , type);


        SymbolInfo* head  = ara[headID];


        if( head == NULL ) {
            ara[headID] = node;
            return true;
        }

        if( head->getName() == name) return false;

        while( head->nextSymbol != NULL) {
			head = head ->nextSymbol;
			if( head->getName() == name) return false;
        }

        head->nextSymbol = node;


        return true;
    }

    SymbolInfo* Lookup( string& keyName) {

		int headID = getHash(keyName);

        SymbolInfo* head  = ara[headID];

        while( head != NULL) {

            if( head->getName() == keyName) return head;
            head = head->nextSymbol;
        }

        return NULL;
    }

    bool Delete( string& keyName) {

		int headID = getHash(keyName);

        SymbolInfo* head  = ara[headID];

        if( head == NULL ) return false;

        if( head->getName() == keyName) {

            ara[headID] = head->nextSymbol;
            delete head;
            return true;
        }
   

        while( head->nextSymbol != NULL) {

			if( head->nextSymbol->getName() == keyName ) {

                SymbolInfo* node = head->nextSymbol;
                head->nextSymbol = node->nextSymbol;
                delete node;
                return true;
			}
            head = head->nextSymbol;

        }

        return false;
    }

    int getId() {
        return id;
    }

	void Print() {
        fprintf(logFile, "\tScopeTable # %d\n", id);
        for(int i =0 ; i < len ; i++ ) {


            SymbolInfo* head = ara[i];
            if( head == NULL ) continue;

            fprintf(logFile, "\t%d --> ", i);


            while( head != NULL ) {
                fprintf(logFile, "<%s, %s> ",head->getName().c_str() , head->getType().c_str() );
                head = head->nextSymbol;
            }
            fprintf(logFile, "\n" );
        }
        fprintf(logFile, "\n" );
	}

	void Erase(SymbolInfo* node) {
        if( node == NULL )return;
        Erase(node->nextSymbol);
        delete node;
	}


	~ScopeTable() {
        for(int i =0 ; i < len ; i++ )
            Erase(ara[i]);

        delete []ara;
        parentScope = NULL;
        delete parentScope ;
	}
};


class SymbolTable {

private:

    ScopeTable* current;
    int tableSize;

public:
    SymbolTable(int n) {

		current = new ScopeTable(n);
		tableSize = n;
    }

    void enterScope() {

        
        ScopeTable* node = new ScopeTable(tableSize);
        node->parentScope = current;
        current = node;

        fprintf(logFile , "\tNew ScopeTable with id %d created\n\n", current->getId() );
    }

    void exitScope() {


        fprintf(logFile , "\tScopeTable with id %d removed\n\n", current->getId() );

        ScopeTable* node = current;

        current = current->parentScope;
        delete node;
    }

    bool Insert( string name , string type) {
		return current->Insert(name , type);
    }

    bool Remove( string& keyName) {
    	return current->Delete(keyName);
    }

    SymbolInfo* globalLookUp( string keyName) {

        ScopeTable* table = current;

        while(table != NULL ) {

            SymbolInfo* node = table->Lookup(keyName);
            if( node!= NULL) return node;
            table = table->parentScope;
        }
		return NULL;
    }

    int getScopeTableID(string keyName) {

        ScopeTable *table = current;
        while( table != NULL) {
            SymbolInfo* node = table->Lookup(keyName);
            if( node!= NULL) return table->getId();
            table = table->parentScope;
        }
        return -1;
    }

    SymbolInfo* sameScopeLookUp(string keyName) {
        return current->Lookup(keyName);
    }

    void printCurrent() {

        current->Print();
    }

    void printAll() {

		ScopeTable* table = current;
        while( table != NULL ) {
			table->Print();
			table = table->parentScope;
        }
    }

    int getCurrentScopeID() {
        return current->getId();
    }

    ~SymbolTable() {
    	delete current;
    }
};
